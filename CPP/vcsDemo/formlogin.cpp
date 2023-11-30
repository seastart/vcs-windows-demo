#include "formlogin.h"
#include "ui_formlogin.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "Tools/Utils.h"
#include "CJsonObject/JsonUtil.h"
#include "Network/HttpNetwork.h"
#include "Network/WebApiClass.h"
#include "DataModel/UserData.h"
#include "widget.h"
#include <QTimer>
#pragma execution_character_set("utf-8")
FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
  ,isLogin(false)
{
    ui->setupUi(this);
    ui->ledAddr->setEditable(true);
    ui->widget->hide();
    this->resize(this->width(),260);
    showHide = false;

    connect(this,SIGNAL(RoomEnter()),this,SLOT(OnRoomEnter()));
    connect(RoomControl::Get(),SIGNAL(DirectShareEvent(int,QString)),this,SLOT(OnDirectShareEvent(int,QString)));
    LoadData();

    if(ui->ledAppid->text().isEmpty()){
        ui->ledAppid->setText("0a16828823ce41c5ad040be3ed384c14");
        ui->ledAppkey->setText("a67c660b29234e2891cc6627fc6401ce");
    }
}

FormLogin::~FormLogin()
{
    delete ui;
}

void FormLogin::on_pushButton_2_clicked()
{
    qDebug()<<__func__;
    if(showHide)
    {
        ui->widget->hide();
        this->resize(this->width(),this->height() - widlen);

    }else
    {
        ui->widget->show();
        this->resize(this->width(),this->height() + widlen);
    }
    showHide = !showHide;
}


void FormLogin::SaveData()
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("addr",ui->ledAddr->currentText());
    obj.insert("user",ui->ledUser->text());
    obj.insert("pass",ui->ledPass->text());
    obj.insert("room",ui->ledRoomno->text());
    obj.insert("roompass",ui->ledRoomNoPass->text());
    obj.insert("mic",ui->chkMic->isChecked());
    obj.insert("speaker",ui->chkSpeaker->isChecked());
    obj.insert("camera",ui->chkCam->isChecked());

    obj.insert("appid",ui->ledAppid->text());
    obj.insert("appkey",ui->ledAppkey->text());
    doc.setObject(obj);
    Utils::SaveFile("demodata.txt",doc.toJson(QJsonDocument::JsonFormat::Compact));
}


void FormLogin::LoadData()
{
   QString data = Utils::LoadFile("demodata.txt");
   if(!data.isEmpty())
   {
        QString addr,user,pass,room,roompass,appid,appkey;
        bool mic,camera,speaker;
        QJsonObject obj =JsonUtil::GetJsonObjectFromString(data.toStdString());
        JsonUtil::GetValue(obj,"addr",addr);
        JsonUtil::GetValue(obj,"user",user);
        JsonUtil::GetValue(obj,"pass",pass);
        JsonUtil::GetValue(obj,"room",room);
        JsonUtil::GetValue(obj,"roompass",roompass);
        JsonUtil::GetValue(obj,"mic",mic);
        JsonUtil::GetValue(obj,"camera",camera);
        JsonUtil::GetValue(obj,"speaker",speaker);

        JsonUtil::GetValue(obj,"appid",appid);
        JsonUtil::GetValue(obj,"appkey",appkey);

        ui->ledAppid->setText(appid);
        ui->ledAppkey->setText(appkey);
        ui->ledRoomNoPass->setText(roompass);
        ui->ledAddr->setEditText(addr);
        ui->ledUser->setText(user);
        ui->ledPass->setText(pass);
        ui->ledRoomno->setText(room);

        ui->chkCam->setChecked(camera);
        ui->chkMic->setChecked(mic);
        ui->chkSpeaker->setChecked(speaker);
   }
}

void FormLogin::on_pushButton_clicked()
{
    HttpNetwork::Get()->SetAppid(ui->ledAppid->text());
    HttpNetwork::Get()->SetAppkey(ui->ledAppkey->text());
    HttpNetwork::Get()->SetHost(ui->ledAddr->currentText());
    ui->ledmsg->setText("");
    if(isLogin)
    {
        OnRoomEnter();
        return;
    }

    QString userName = ui->ledUser->text();
    QString password = ui->ledPass->text();
    if (userName.isEmpty())
    {
        ui->ledmsg->setText(tr("手机号不能为空"));
        return;
    }
    if (password.isEmpty())
    {
        ui->ledmsg->setText(tr("密码不能为空"));
        return;
    }

    QString p;
    Utils::HmacSha1(p, HttpNetwork::Get()->PassKey().toLocal8Bit(), (userName + password).toLocal8Bit());//密码加密
    QString pString = p;
    WebApiClass::AccountLogin(userName, pString, "1", [&](QByteArray& byte) -> void {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(byte);
        QJsonObject Json = jsonDoc.object();
        int code;
        JsonUtil::GetValue(Json, "code", code);

        if (code == 200)
        {
            QJsonObject JsonData;
            JsonUtil::GetValue(Json, "data", JsonData);
            ui->ledmsg->setText("login success");
            UserData::Save(JsonData);
            HttpNetwork::Get()->SetToken(UserData::Get()->token());
            UserData* ud = UserData::Get();

            RoomControl::Get()->InitMqtt(UserData::Get()->reg().mqtt_tcp().toLocal8Bit(), UserData::Get()->token().toLocal8Bit());
            isLogin = true;
            if(ui->ledRoomno->text().isEmpty())
            {
                SaveData();
            }else
            {
                emit RoomEnter();
            }
        }
        else
        {
            QString msg;
            JsonUtil::GetValue(Json, "msg", msg);
            ui->ledmsg->setText(msg);
        }
    });
}

void FormLogin::OnRoomEnter()
{
    WebApiClass::RoomEnter(ui->ledRoomno->text(),ui->ledRoomNoPass->text(), [&](QByteArray& byte) -> void {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(byte);
        QJsonObject Json = jsonDoc.object();
        int code;
        JsonUtil::GetValue(Json, "code", code);

        if (code == 200)
        {
            ui->ledmsg->setText("room enter success");
            QJsonObject JsonData;
            JsonUtil::GetValue(Json, "data", JsonData);
            RoomData rd;
            rd.Load(JsonData);

            RoomInfo& roomInfo = RoomControl::Get()->roomInfo;
            roomInfo.InitData();
            roomInfo.SetRoomDataValue(rd);
            roomInfo.SetUserDataValue(*UserData::Get());

            roomInfo.nickName = UserData::Get()->account().nickname();
            SaveData();

            Widget* w = new Widget();
            w->show();
            w->OpenRoom(ui->chkSpeaker->isChecked(),ui->chkMic->isChecked(),ui->chkCam->isChecked());

            this->close();
        }
        else
        {
            QString msg;
            JsonUtil::GetValue(Json, "msg", msg);
            ui->ledmsg->setText(msg);
        }
    });
}

void FormLogin::on_btnTest_clicked()
{
    RoomControl::Get()->test();
}

#include <QMessageBox>
#include "vcs/EnumDevice.h"
void FormLogin::on_pushButton_3_clicked()
{
    VideoDeviceList devices;
    bool ret = EnumDevice::Video(devices);
}



void FormLogin::on_rbtn1_clicked()
{
    RoomControl::Get()->roomInfo.stream_mode = 1;
}


void FormLogin::on_rbtn2_clicked()
{
    RoomControl::Get()->roomInfo.stream_mode = 2;
    ui->chkCam->setChecked(false);
    ui->chkSpeaker->setChecked(false);
    ui->chkMic->setChecked(false);
}


void FormLogin::on_rbtn3_clicked()
{
    RoomControl::Get()->roomInfo.stream_mode = 3;
}


void FormLogin::on_btnRegiester_clicked()
{

    HttpNetwork::Get()->SetAppid(ui->ledAppid->text());
    HttpNetwork::Get()->SetAppkey(ui->ledAppkey->text());
    HttpNetwork::Get()->SetHost(ui->ledAddr->currentText());

    QString name = ui->ledUser->text();
    QString pass = ui->ledPass->text();
    QString p;
    Utils::HmacSha1(p,HttpNetwork::Get()->PassKey().toLocal8Bit(), (name + pass).toLocal8Bit());
    QMap<QString, QString> map;
    map.insert("name", name);
    map.insert("password", p);
    map.insert("nickname", name);

    HttpNetwork::OnPost("account/register", map, [&](QByteArray& byte) -> void {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(byte);
        QJsonObject Json = jsonDoc.object();
        int code;
        JsonUtil::GetValue(Json, "code", code);
        qDebug()<<"account/register"<<byte;
        if (code == 200)
        {
            ui->ledmsg->setText(tr("注册成功"));
        }else
        {
            QString msg;
            JsonUtil::GetValue(Json,"msg",msg);
            ui->ledmsg->setText(tr("注册异常:")+QString::number(code)+msg);
        }
    });
}

#include <QScreen>
void FormLogin::on_btnDirShare_clicked()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QString r = QString("%1,%2,%3,%4").arg(screen->availableGeometry().x()).arg(screen->geometry().y()).arg(screen->geometry().width()).arg(screen->geometry().height());
    QJsonDocument doc ;
    QJsonObject obj;;
    obj.insert("bitrate",3000);
    obj.insert("dynaframe",1);
    obj.insert("nickname",tr("刘志慧"));
    obj.insert("fps",10);
    obj.insert("streamtimeout",120);
    obj.insert("rect",r);
    doc.setObject(obj);
    RoomControl::Get()->StartDirectShare(ui->ledAddr->currentText()
                 ,QString::fromUtf8(doc.toJson(QJsonDocument::JsonFormat::Compact)).toLocal8Bit());
}


void FormLogin::on_btnStopDirShare_clicked()
{
    RoomControl::Get()->StopDirectShare();
}

void FormLogin::OnDirectShareEvent(int t,QString s){

}
