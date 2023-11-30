#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "DataModel/HandUpNotify.h"
#include "DataModel/ChatMsg.h"
#include "Network/WebApiClass.h"
#include "DataModel/RecvNetWorkStatus.h"
#pragma execution_character_set("utf-8")

#define MAX_MIN_VIEW 4
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , sharekey(0)
    , leftBtn(nullptr)
    , rightBtn(nullptr)
    , memberTableListShowIndex(0)
    , tableRow(-1)
{
    ui->setupUi(this);
    SELF_ID = RoomControl::Get()->roomInfo.streamId;
    qRegisterMetaType<HROOM>("HROOM");
    qRegisterMetaType<std::string>("std::string");
    connect(RoomControl::Get(), &RoomControl::RoomEvent, this, &Widget::OnRoomEvent);
    connect(RoomControl::Get(), SIGNAL(AudioStatus(const char*)), this, SLOT(OnAudioStatus(const char*)));
    QTimer::singleShot(0,[&]{

        leftBtn = new QPushButton("<<",ui->minViewWidget);
        leftBtn->raise();
        leftBtn->resize(40,40);
        leftBtn->move(0,(ui->minViewWidget->height()-40)/2);
        connect(leftBtn,SIGNAL(clicked()),this,SLOT(OnLeftClicked()));
        leftBtn->show();

        rightBtn = new QPushButton(">>",ui->minViewWidget);
        rightBtn->raise();
        rightBtn->resize(40,40);
        rightBtn->move(ui->minViewWidget->width() - 40,(ui->minViewWidget->height()-40)/2);
        connect(rightBtn,SIGNAL(clicked()),this,SLOT(OnRightClick()));
        rightBtn->show();

        for(int i = 0;i < MAX_MIN_VIEW;i++)
        {
            ViewItem* view = new ViewItem(ui->minViewWidget);
            ui->minViewWidget->layout()->addWidget(view);
            ViewItemList.append(view);
        }
    });
    ui->lblaudio->setText("1");
    ui->lblvideo->setText("1");

}

Widget::~Widget()
{
    for(auto m : memberMap)
    {
        delete m;
    }
    delete ui;
}

void Widget::OpenRoom(bool speaker, bool mic, bool cam)
{
    RoomControl::Get()->roomInfo.openMicrophoneUpload = (mic ? 0 : 1);
    RoomControl::Get()->roomInfo.openCamera = cam;
    RoomControl::Get()->roomInfo.openSpeaker = speaker;
    int ret = 0;
    AddSelfMember(ui->lblme);
    ui->lblmename->setText(RoomControl::Get()->roomInfo.nickName);
    ret = RoomControl::Get()->OpenRoom();
    qDebug() << __func__ << ret;
    if(!ret)
    {
        OpenCloseSpeaker(speaker);
    }else
    {
        AppendMsg(tr("进入房间异常%1").arg(ret));
    }
}

int Widget::OnAudioStatus(const char* data)
{
    int powValue = 0;
    QList<int> streamids;

    QJsonDocument qdoc = QJsonDocument::fromJson(data);
    QJsonObject qjson = qdoc.object();

    QJsonArray array = qjson.value("audioInfo").toArray();
    if (array.size() == 0)
    {
        return 0;
    }
    for (QJsonArray::iterator it = array.begin(); it != array.end(); ++it)
    {
        QJsonObject value = (*it).toObject();
        long powLong = value.value("pow").toInt();

        int Value = value.value("clientId").toInt();
        if (memberMap.find(Value) == memberMap.end())
        {
            continue;
        }

        if (memberMap[Value]->data.astate() == 0)
        {
            if (powLong > powValue)
            {
                streamids.insert(0, Value);
                powValue = powLong;
            }
            memberMap[Value]->db = value.value("db").toInt();

        }
    }
    for(auto id : streamids)
    {
        int row = memberTableList.indexOf(id);
        ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(memberMap[id]->db)));
    }
    return 0;
}

int Widget::OnRoomEvent(HROOM hroom, int iEventId, std::string jsonString)
{
    QString json = QString::fromStdString(jsonString);

    qDebug()<<iEventId<<__func__<< json;
    switch (iEventId)
    {
    case VCS_EVENT_ENTER:
    {
        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        int result = -1;
        JsonUtil::GetValue(JsonObject, "result", result);
        if (!result)
        {
           AppendMsg(tr("房间连接成功！~"));
        }
        else
        {
            AppendMsg(tr("流媒体连接异常，%1").arg(result));

            if(result != 5){
                AppendMsg(tr("开始从新入会"));
                RoomControl::Get()->CloseRoom();
                RoomInfo& roomInfo = RoomControl::Get()->roomInfo;
                WebApiClass::RoomEnter(RoomControl::Get()->roomInfo.roomNo, RoomControl::Get()->roomInfo.roomPass, [&](QByteArray& byte) -> void {
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(byte);
                    QJsonObject Json = jsonDoc.object();
                    int code;
                    JsonUtil::GetValue(Json, "code", code);

                    if (code == 200)
                    {
                        QJsonObject JsonData;
                        JsonUtil::GetValue(Json, "data", JsonData);
                        RoomData rd;
                        rd.Load(JsonData);
                        roomInfo.InitData();
                        roomInfo.SetRoomDataValue(rd);
                        roomInfo.SetUserDataValue(*UserData::Get());
                        //成员
                        int ret = RoomControl::Get()->OpenRoom();
                        if (ret)
                        {
                            OnCloseRoom();
                            return;
                        }
                    }
                    else
                    {
                        QString msg;
                        JsonUtil::GetValue(Json, "msg", msg);

                        OnCloseRoom();
                    }
                    });
           }
        }
        break;
    }
    case VCS_EVENT_NOTIFY_ROOM:
    {
        NotifyRoomData data;
        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        data.Load(JsonObject);

        RoomControl::Get()->roomInfo.roomShareType = data.sharing_type();

        if (RoomControl::Get()->roomInfo.lockMeeting != data.locked())
        {
            RoomControl::Get()->roomInfo.lockMeeting = data.locked();
        }
        if (data.watermark() != RoomControl::Get()->roomInfo.showWaterMark)
        {
            RoomControl::Get()->roomInfo.showWaterMark = data.watermark();
            ui->lblwater->setText(QString::number(data.watermark()));
        }
        if(data.relieve_astate() != RoomControl::Get()->roomInfo.roomAudio)
        {
            RoomControl::Get()->roomInfo.roomAudio = data.relieve_astate();
            ui->lblcanopenaudio->setText(QString::number(data.relieve_astate()));
        }

        switch (data.sharing_type())
        {
        case 0:
        {
            if(sharekey)
            {
                if(sharekey == SELF_ID)
                {
                    RoomControl::Get()->CloseShareScreen(false);
                    AppendMsg(tr("你结束了共享"));
                    sharekey = 0;
                }else if(sharekey != 0)
                {
                    CloseShareShowView(sharekey);
                    AppendMsg(tr("%1 结束了共享").arg(memberMap[sharekey]->data.nickname()));
                    sharekey = 0;
                }
            }

            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            int key = data.sharing_sdkno().toInt();
            if(sharekey == key)
            {
                break;
            }
            sharekey = key;
            if (key != RoomControl::Get()->roomInfo.streamId)
            {
                AppendMsg(tr("%1发起了共享").arg(memberMap[key]->data.nickname()));
                OnStartMemberShare(key, data.sharing_stream_id().toInt());
            }
            else
            {
                AppendMsg(tr("你发起了共享"));
                OnStartShare();

            }
            break;
        }
        default:
            break;
        }
        break;
    }
    case VCS_EVENT_NOTIFY_ENTER:
    case VCS_EVENT_NOTIFY_ACCOUNT:
    {
        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        int id = 0;
        JsonUtil::GetValue(JsonObject, "stream_id", id);
        if (memberMap.find(id) == memberMap.end())
        {
            qDebug() << QString::fromLocal8Bit("成员列表里面没有%1准备添加").arg(id);
            AddMember(QString::fromStdString(jsonString));
            break;
        }
        UpdateMember(QString::fromStdString(jsonString));
        break;
    }
    case VCS_EVENT_NOTIFY_ENDED:
    {
        if (RoomControl::Get()->RoomOpen())
        {
            OnCloseRoom();
            AppendMsg("会议已结束");
        }
        break;
    }
    case VCS_EVENT_NOTIFY_KICKOUT:
    {
        if (RoomControl::Get()->RoomOpen())
        {

            OnCloseRoom();
            AppendMsg("你被主持人踢出了会议！");
        }
        break;
    }
    case VCS_EVENT_NOTIFY_EXIT:
    {
        int id;
        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        JsonUtil::GetValue(JsonObject, "stream_id", id);

        MemberExitRoom(id);
        break;
    }
    case VCS_EVENT_NOTIFY_MYACCOUNT:
    {
        MyAccountUpdate(json);
        break;
    }
    case VCS_EVENT_SEND_STATUS:
    {
        int delay;
        int rate;
        double first_lost;
        double re_lost;
        int signal;

        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        JsonUtil::GetValue(JsonObject, "delay", delay);
        JsonUtil::GetValue(JsonObject, "rate", rate);
        JsonUtil::GetValue(JsonObject, "first_lost", first_lost);
        JsonUtil::GetValue(JsonObject, "re_lost", re_lost);
        JsonUtil::GetValue(JsonObject, "signal", signal);
        ui->lblrate->setText(QString::number(rate));
        RoomControl::Get()->SetAccountNetWork(delay, rate, first_lost, signal);
        break;
    }
    case VCS_EVENT_RECV_STATUS:
    {
        UpdateMemberRecv(QString::fromStdString(jsonString));
        break;
    }
    case VCS_EVENT_MEDIA_CONNECTED:
    {
        qDebug()<<__func__<<"VCS_EVENT_MEDIA_CONNECTED";
        break;
    }
    case VCS_EVENT_HANDUP:
    {
        HandUpNotify dun;
        dun.Load(JsonUtil::GetJsonObjectFromString(jsonString));
        AppendMsg(tr("主持人 %1 你的举手").arg(dun.result() ? tr("同意"):tr("拒绝")));
        break;
    }
    case VCS_EVENT_RECV_GEAR_CHANGE:
    {
        break;
    }
    case VCS_EVENT_RECV_AVERAGE_STATUS:
    {
        break;
    }
    case VCS_EVENT_MEDIA_STREAM_RECV:
    {
        break;
    }
    case VCS_EVENT_FRAME_CHANGE:
    {
        break;
    }
    case VCS_EVENT_DEV_CHANGED:
    {
        AppendMsg(tr("系统设备发生改变！"));
        break;
    }
    case VCS_EVENT_DEV_DEF_CHANGED:
    {
        AppendMsg(tr("系统默认设备发生改变！"));
        break;
    }
    case VCS_EVENT_CHAT:
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.c_str());
        QJsonObject Json = jsonDoc.object();
        ChatMsg cData;
        cData.Load(Json);
        AppendMsg(tr("收到%1聊天消息%2").arg(cData.account_name()).arg(cData.message()));
        break;
    }
    case VCS_EVENT_NET_STATE:
    {
        int client_id;
        int state;
        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        JsonUtil::GetValue(JsonObject, "client_id", client_id);
        JsonUtil::GetValue(JsonObject, "state", state);
        if(client_id == SELF_ID)
        {
            ui->lblgear->setText(QString::number(state));
        }else
        {
            int row = memberTableList.indexOf(client_id);
            ui->tableWidget->setItem(row,12,new QTableWidgetItem(QString::number(state)));
        }
    }
    case VCS_EVENT_AUDIO_CAP_ERROR:
    {
        int audio_cap_error;
        QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(jsonString);
        JsonUtil::GetValue(JsonObject, "audio_cap_error", audio_cap_error);

        switch (audio_cap_error)
        {
        case 1:
            AppendMsg(tr("监测到麦克风采集异常"));
            break;
        case 2:
            AppendMsg(tr("监测到扬声器播放异常"));
            break;
        case 0x11:
            AppendMsg(tr("麦克风已恢复"));
            break;
        case 0x12:
            AppendMsg(tr("扬声器已恢复"));
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    return 0;
}


void Widget::AppendMsg(QString msg)
{
    ui->textEdit->append(msg);
    qDebug()<<msg;
}

void Widget::OnCloseRoom()
{
    WebApiClass::RoomExit(RoomControl::Get()->roomInfo.roomNo);
    CloseAllPlayer();
    RoomControl::Get()->CloseRoom();
    this->deleteLater();
}

void Widget::CloseAllPlayer(bool me)
{
    VCS_SetOptParams(0x10000, 0, 0, 0, 0);

    RoomControl::Get()->Picker(0, 3);
    if (me)
    {
    RoomControl::Get()->CloseCamera();
    RoomControl::Get()->RemovePlayer((void*)memberMap[SELF_ID]->view->winId(), SELF_ID, 0);
    }
    for (auto m : memberMap)
    {
        if (m->data.stream_id() != SELF_ID && m->view && !m->data.vstate())
        {
            RoomControl::Get()->RemoveMember(m->data.stream_id(), m->streamItemId);
            RoomControl::Get()->RemovePlayer((void*)m->view->winId(), m->data.stream_id(), m->streamItemId);
        }
    }
}

void Widget::CloseShareShowView(int key)
{
    qDebug() << __func__;
    MemberModel* Model = memberMap[key];
    RoomControl::Get()->RemoveMember(Model->data.stream_id(), Model->streamItemId);
    Model->type = 0;
    UpdateVideoView(key);
    RoomControl::Get()->SetViewPlus(Model->view, false);
    AppendMsg(QString(tr("%1停止了共享")).arg(Model->data.nickname()));
}

bool Widget::UpdateVideoView(int key)
{
    if (memberMap.find(key) == memberMap.end())
    {
        qDebug() << __func__ << ",not find key:" << key;
        return false;
    }
    qDebug() << __func__ << ",key:" << key;

    bool res = false;
    MemberModel* inModel = memberMap[key];
    if (!inModel->view)
    {
        qDebug() << tr("UpdateVideoView当前不显示终端画面！~");
    }
    else if (key == SELF_ID)
    {
        qDebug() << "update me video" << inModel->data.vstate();
        if (!inModel->data.vstate())
        {
            QString msg;
            int ret = RoomControl::Get()->OpenCamera((void*)inModel->view->winId(), msg);
            if (ret)
            {
                inModel->data.set_vstate(1);
                RoomControl::Get()->roomInfo.openCamera = false;
                if (ret/* == 1*/)
                {
                    AppendMsg(msg);
                }
                RoomControl::Get()->EnableVideo(false);
                res = false;
            }
            else
            {
                inModel->view->setUpdatesEnabled(false);
                inModel->view->update();
                res = true;
            }
        }
        else {
            RoomControl::Get()->CloseCamera();

            inModel->view->setUpdatesEnabled(true);
            inModel->view->update();
            res = true;
        }
    }
    else
    {
        qDebug() << "update other video" << inModel->data.nickname() << inModel->data.vstate();
        if (!inModel->data.vstate())
        {
            if (RoomControl::Get()->Picker(key))
            {
                if (!inModel->data.streams().count())
                {
                    inModel->data.set_vstate(1);
                    return false;
                }
                Stream streamModel = inModel->data.streams().first();

                for (Stream stream : inModel->data.streams())
                {
                    if (inModel->type == stream.type())
                    {
                        streamModel = stream;
                        break;
                    }
                }
                RoomControl::Get()->SetMember(
                    inModel->data.stream_id(),
                    (void*)inModel->view->winId(),
                    streamModel.id());
                if(RoomControl::Get()->roomInfo.stream_mode == 2){

                    AppendMsg(tr("正在保存成员%1视频流，mask:%2").arg(inModel->data.nickname()).arg(streamModel.id()));

                }
                inModel->streamItemId = streamModel.id();
                inModel->view->setUpdatesEnabled(false);

                res = true;
            }
        }
        else
        {
            RoomControl::Get()->Picker(key, 1);
            RoomControl::Get()->RemoveMember(inModel->data.stream_id(), inModel->streamItemId);
            inModel->streamItemId = 0;
            inModel->view->setUpdatesEnabled(true);
            inModel->view->update();

            res = true;
        }
    }

    SetMemberVideoView(key);
    return res;
}

bool Widget::UpdateAudioView(int key)
{
    qDebug() << __func__ << ",key:" << key;
    MemberModel* inModel = memberMap[key];
    bool res = false;
    if (key == SELF_ID)
    {
        qDebug() << "update me audio" << inModel->data.astate();
        if (!inModel->data.astate())
        {
            if (RoomControl::Get()->roomInfo.openMicrophone)
            {
                RoomControl::Get()->EnableAudio(0);
            }
            else
            {
                QString msg;
                int ret = RoomControl::Get()->OpenAudio(msg);
                if (ret)
                {
                    AppendMsg(tr("麦克风打开异常")+QString::number(ret));
                }
                else
                {
                    res = true;
                }
            }
        }
        else
        {
            RoomControl::Get()->EnableAudio(inModel->data.astate());
            res = true;
        }
    }
    else
    {
        res = true;
    }
    SetMemberAudioView(key);
    return res;
}

void Widget::UpdateView(int key, bool videoChange, bool AduioChange)
{
    if (videoChange)
    {
        UpdateVideoView(key);
    }
    if (AduioChange)
    {
        UpdateAudioView(key);
    }
}
void Widget::SetMemberVideoView(int key)
{
    if (memberMap.find(key) == memberMap.end())
    {
        return;
    }

    qDebug() << __func__;
    MemberModel* model = memberMap[key];


    if (key == SELF_ID)
    {
        ui->btnCam->setText((model->data.vstate())?tr("打开摄像头"):tr("关闭摄像头"));
        ui->lblvideo->setText(QString::number(model->data.vstate()));
    }
}

void Widget::SetMemberAudioView(int key)
{
    if (memberMap.find(key) == memberMap.end())
    {
        return;
    }

    MemberModel* model = memberMap[key];
    if (key == SELF_ID)
    {
        ui->btnMic->setText((model->data.astate())?tr("打开麦克风"):tr("关闭麦克风"));
        ui->lblaudio->setText(QString::number(model->data.astate()));
    }
}

void Widget::OnStartMemberShare(int key,int shareStreamItemId)
{
    qDebug() << __func__;
    AppendMsg(tr("收到成员共享，点击共享流查看"));
    this->shareStreamItemId = shareStreamItemId;
}

void Widget::OnStartShare()
{
    char* caps;
    EnumWndCaptures(&caps);
    std::string capsJson = caps;
    QJsonDocument doc = QJsonDocument::fromJson(QString::fromLocal8Bit(caps).toStdString().data());
    QJsonArray json = doc.array();
    qDebug() << __func__ << "Share select " << caps;
    VCS_Freep((void**)&caps);

    if(json.size() == 0)
    {
        return ;
    }
    QJsonObject itemJson = json.at(0).toObject();
    CapsData data;
    data.Load(itemJson);

    if(RoomControl::Get()->roomInfo.stream_mode != 3)
    {
        OpenCloseCamera(false);
    }
    RoomControl::Get()->ShareScreen(data, 0);
}

void Widget::on_btnCam_clicked()
{
    OpenCloseCamera(!RoomControl::Get()->roomInfo.openCamera);
}

void Widget::on_btnMic_clicked()
{
    OpenCloseMic(!RoomControl::Get()->roomInfo.openMicrophoneUpload);
}


void Widget::on_btnSpeaker_clicked()
{
    OpenCloseSpeaker(!RoomControl::Get()->roomInfo.openSpeaker);
}

void Widget::OpenCloseCamera(bool v)
{
    if(RoomControl::Get()->roomInfo.openCamera == v)
    {
        return;
    }
    memberMap[SELF_ID]->data.set_vstate(!v);
    UpdateVideoView(SELF_ID);
}
void Widget::OpenCloseSpeaker(bool v)
{
    if (v)
    {
        QString msg;
        bool ret = RoomControl::Get()->OpenSpeaker(msg);
        if (!ret)
        {
            AppendMsg(msg);
        }
        else
        {
            ui->btnSpeaker->setText(tr("关闭扬声器"));
        }
    }
    else
    {
        RoomControl::Get()->CloseSpeaker();
        ui->btnSpeaker->setText(tr("开启扬声器"));
    }
}

void Widget::OpenCloseMic(int v)
{
    if(RoomControl::Get()->roomInfo.openMicrophoneUpload == v)
    {
        return;
    }
    memberMap[SELF_ID]->data.set_astate(v);
    UpdateAudioView(SELF_ID);
}



void Widget::AddMember(const QString jsonString)
{
    qDebug() << __func__;
    MemberModel* model = new MemberModel();
    StreamData data;
    data.Load(JsonUtil::GetJsonObjectFromString(jsonString.toStdString()));
    int key = data.stream_id();
    model->data = data;
    model->type = 1;
    memberMap[key] = model;

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number((data.stream_id()))));  //id
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(data.nickname()));                      //昵称
    ui->tableWidget->setItem(row,2,new QTableWidgetItem((!data.astate())?tr("打开"):tr("关闭")));  //麦克风
    ui->tableWidget->setItem(row,3,new QTableWidgetItem((!data.vstate())?tr("打开"):tr("关闭")));  //摄像头
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(model->db)));           //db
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(data.net_level())));    //网络
    ui->tableWidget->setItem(row,6,new QTableWidgetItem(QString::number(data.role())));         //角色
    ui->tableWidget->setItem(row,7,new QTableWidgetItem("0"));                                  //服务到端丢包
    ui->tableWidget->setItem(row,8,new QTableWidgetItem("0"));                                  //端到端丢包
    ui->tableWidget->setItem(row,9,new QTableWidgetItem("0"));                                  //音频包
    ui->tableWidget->setItem(row,10,new QTableWidgetItem("0"));                                  //视频包
    ui->tableWidget->setItem(row,11,new QTableWidgetItem("0"));                                  //总丢包
    ui->tableWidget->setItem(row,12,new QTableWidgetItem("0"));                                  //档位

    memberTableList << data.stream_id();

    for(auto v : ViewItemList)
    {
        if(!v->GetData())
        {
            model->view = v->GetView();
            model->viewItem = v;
            v->SetData(key);
            v->SetName(model->data.nickname());
            break;
        }
    }
    if(model->view)
    {
        UpdateView(key,true,true);
    }
}

void Widget::UpdateMemberRecv(QString json)
{
    QJsonArray ss = JsonUtil::GetJsonArrayFromString(json.toStdString().c_str());
    for (QJsonArray::iterator it = ss.begin(); it != ss.end(); ++it)
    {
        QJsonObject stream = (*it).toObject();
        RecvNetWorkStatus s;
        s.Load(stream);
        int row = memberTableList.indexOf(s.sdkno().toInt());
        ui->tableWidget->setItem(row,7,new QTableWidgetItem(QString::number(s.lr1(),'f',2)));                            //服务到端丢包
        ui->tableWidget->setItem(row,8,new QTableWidgetItem(QString::number(s.lr2(),'f',2)));                           //端到端丢包
        ui->tableWidget->setItem(row,9,new QTableWidgetItem(QString::number(s.audio())));                                  //音频包
        ui->tableWidget->setItem(row,10,new QTableWidgetItem(QString::number(s.recv()- s.audio())));                             //视频包
        ui->tableWidget->setItem(row,11,new QTableWidgetItem(QString::number(s.recv() )));                         //总丢包
    }
}

void Widget::MemberExitRoom(int key)
{
    qDebug() << __func__;

    if (memberMap.find(key) == memberMap.end())
    {
        return;
    }

    MemberModel* model = memberMap[key];
    RoomControl::Get()->UnPicker(model->data.stream_id());

    if(model->view)
    {
        bool haveNext = false;
        for(auto m: memberMap)
        {
            if(SELF_ID != m->data.stream_id() && !m->view)
            {
                haveNext = true;
                m->view = model->view;
                m->viewItem = model->viewItem;
                model->viewItem->SetData(m->data.stream_id());
                model->viewItem->SetName(m->data.nickname());
                UpdateView(m->data.stream_id(),true,true);
            }
        }
        if(!haveNext)
        {
            model->viewItem->SetData(0);
            model->viewItem->SetName("");
        }
    }
    int row = memberTableList.indexOf(key);
    memberMap.remove(key);
    memberTableList.removeAll(key);
    ui->tableWidget->removeRow(row);
    delete model;
    return;
}


void Widget::UpdateMember(const QString jsonString)
{
    StreamData data;
    data.Load(JsonUtil::GetJsonObjectFromString(jsonString.toStdString()));
    int key = data.stream_id();
    bool vstateChange,audioChange,roleChange,nicknameChange;
    IsChangeData(key,data,vstateChange,audioChange,roleChange,nicknameChange);
    memberMap[key]->data = data;

    int row = memberTableList.indexOf(key);
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(data.nickname()));                      //昵称
    ui->tableWidget->setItem(row,2,new QTableWidgetItem((!data.astate())?tr("打开"):tr("关闭")));  //麦克风
    ui->tableWidget->setItem(row,3,new QTableWidgetItem((!data.vstate())?tr("打开"):tr("关闭")));  //摄像头
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(data.net_level())));     //网络
    ui->tableWidget->setItem(row,6,new QTableWidgetItem(QString::number(data.role())));          //角色


    if (vstateChange || audioChange)
    {
        UpdateView(key, vstateChange, audioChange);
    }
}

bool Widget::IsChangeData( int id,StreamData& data,bool& vstateChange,bool& audioChange,bool& roleChange,bool& nicknameChange)
{
    audioChange = vstateChange = roleChange = nicknameChange = false;
    MemberModel* model = memberMap[id];
    if (data.astate() != model->data.astate())
    {
        audioChange = true;
    }
    if (data.vstate() != model->data.vstate())
    {
        vstateChange = true;
    }
    if (data.role() != model->data.role())
    {
        roleChange = true;
    }
    if (data.nickname() != model->data.nickname())
    {
        nicknameChange = true;
    }
    return audioChange || vstateChange || roleChange || nicknameChange;
}

void Widget::MyAccountUpdate(const QString json)
{
    int vFirst = false;
    int astate;
    int vstate;
    bool vstateChange = false;
    bool AudioChange = false;
    QJsonObject JsonObject = JsonUtil::GetJsonObjectFromString(json.toStdString());
    AudioChange = JsonUtil::GetValue(JsonObject, "astate", astate);
    vstateChange = JsonUtil::GetValue(JsonObject, "vstate", vstate);
    JsonUtil::GetValue(JsonObject, "first", vFirst);

    MemberModel* model = memberMap[SELF_ID];
    if (AudioChange)
    {
        if (model->data.astate() != astate)
        {
            int ret = 1;
            if (astate == 0)
            {
                if (!vFirst)
                {
                    AudioChange = true;

                }
            }
            else
            {
                AppendMsg(tr("主持人已将您的麦克风关闭"));
            }

            model->data.set_astate(astate);
        }
        else
        {
            AudioChange = false;
        }
    }
    if (vstateChange)
    {
        if (model->data.vstate() != vstate)
        {
            int ret = 1;

            if (vstate == 0)
            {
                if (!vFirst)
                {
                }
            }
            else
            {
                AppendMsg(tr("主持人已将您的摄像头关闭"));

            }
            model->data.set_vstate(vstate);
        }
        else
        {
            vstateChange = false;
        }
    }

    if (vstateChange)
    {
        UpdateVideoView(SELF_ID);
    }
    if (AudioChange)
    {
        UpdateAudioView(SELF_ID);
    }
    int role = 0;
    bool ret = JsonUtil::GetValue(JsonObject, "role", role);
    if (ret && role != RoomControl::Get()->roomInfo.role)
    {
        int oldRole = RoomControl::Get()->roomInfo.role;
        RoomControl::Get()->SetMyRole(role);
        model->data.set_role(role);
        ui->lblrole->setText(QString::number(role));
    }

    QString nickname = "";
    bool has_nickName = JsonUtil::GetValue(JsonObject, "nickname", nickname);
    if (has_nickName)
    {
        RoomControl::Get()->MyUpdateNickName(nickname);
        ui->lblmename->setText(nickname);
    }
}


void Widget::AddSelfMember(QWidget* memberView)
{
    qDebug() << __func__;
    StreamData data;

    data.set_stream_id(SELF_ID);
    data.set_id(RoomControl::Get()->roomInfo.userId);
    data.set_vstate(1);
    data.set_astate(1);
    data.set_terminal_type(1);
    data.set_hus(0);
    data.set_portrait(RoomControl::Get()->roomInfo.portrait);
    data.set_portrait(RoomControl::Get()->roomInfo.portrait);
    data.set_role(RoomControl::Get()->roomInfo.role);
    data.set_nickname(RoomControl::Get()->roomInfo.nickName);

    std::string key = data.id().toStdString();

    MemberModel* model = new MemberModel();

    model->view = memberView;
    model->data = data;
    model->type = 1;

    memberMap[SELF_ID] = model;
}
#include "formlogin.h"
void Widget::on_btnexit_clicked()
{
    FormLogin* f= new FormLogin();
    f->show();
    OnCloseRoom();
}


void Widget::on_rbtn1s_clicked()
{
  RoomControl::Get()->SetStatInterval(1);
}


void Widget::on_rbtn10s_clicked()
{

    RoomControl::Get()->SetStatInterval(10);
}

void Widget::OnRightClick()
{
    if(memberTableListShowIndex + 4 > memberTableList.size())
    {
        AppendMsg(tr("没有下一页了"));
        return;
    }

    memberTableListShowIndex += 4;
    QList<int> reloadList;
    for(int i = memberTableListShowIndex;i<memberTableList.size();i++)
    {
        reloadList<<memberTableList[i];
        if(reloadList.size() >= 4)
        {
            break;
        }
    }
    ReLoadMemberView(reloadList);
}

void Widget::OnLeftClicked()
{
    if(memberTableListShowIndex <= 0)
    {
        AppendMsg(tr("没有上一页了"));
        return;
    }
    if(memberTableList.size() < memberTableListShowIndex)
    {
        memberTableListShowIndex = memberTableList.size() - 4;
    }else
    {
        memberTableListShowIndex -= 4;
    }
    if(memberTableListShowIndex < 0)
    {
        memberTableListShowIndex = 0;
    }
    QList<int> reloadList;
    qDebug()<<__func__<<memberTableListShowIndex;
    for(int i = memberTableListShowIndex;i<memberTableList.size();i++)
    {
        reloadList<<memberTableList[i];
        if(reloadList.size() >= 4)
        {
            break;
        }
    }
    ReLoadMemberView(reloadList);
}

void Widget::ReLoadMemberView(QList<int> list)
{
    qDebug()<<__func__<<list.size();
    RoomControl::Get()->Picker(0, 3);

    for(int i = 0;i<list.size();i++)
    {

        int oldkey = ViewItemList[i]->GetData();
        if(oldkey)
        {
            RoomControl::Get()->RemoveMember(oldkey,memberMap[oldkey]->streamItemId);
        }

        int newkey = list[i];
        ViewItem* v = ViewItemList[i];
        MemberModel* m = memberMap[newkey];
        m->view = v->GetView();
        m->viewItem = v;
        v->SetData(m->data.stream_id());
        v->SetName(m->data.nickname());
        UpdateView(m->data.stream_id(),true,true);

        if(oldkey)
        {
            memberMap[oldkey]->viewItem = nullptr;
            memberMap[oldkey]->view = nullptr;
        }
    }

    for(int i = list.size();i<ViewItemList.size();i++)
    {
        int oldkey = ViewItemList[i]->GetData();
        RoomControl::Get()->RemoveMember(oldkey,memberMap[oldkey]->streamItemId);
        memberMap[oldkey]->viewItem = nullptr;
        memberMap[oldkey]->view = nullptr;
        ViewItemList[i]->SetData(0);
        ViewItemList[i]->SetName("");
        ViewItemList[i]->GetView()->setUpdatesEnabled(true);
        ViewItemList[i]->GetView()->update();

    }
}




void Widget::on_tableWidget_cellClicked(int row, int column)
{
    tableRow = row;
    QString name = ui->tableWidget->item(row,1)->text();
    ui->lblSelect->setText(name);
}


void Widget::on_btnShare_clicked()
{
    RoomControl::Get()->StartShare(3);
}


void Widget::on_btnstopshare_clicked()
{
    RoomControl::Get()->StopShare();
}


void Widget::on_btntrack_clicked()
{
    if(tableRow < 0||tableRow >= ui->tableWidget->rowCount())
    {
        AppendMsg(tr("请选择一个用户！"));
        return;
    }
    QString s = ui->ledtrack->text();
    QStringList ls = s.split(",");
    int streamid = RowGetStreamId(tableRow);
    RoomControl::Get()->Picker(streamid,3);
    int oldtrack = 0;
    for(auto ss : ls)
    {
        int track = ss.toInt();
        QWidget* w = new QWidget();
        w->resize(640,480);
        w->show();
        oldtrack |= (1 << track);
        RoomControl::Get()->SetTrack(streamid,oldtrack);
        RoomControl::Get()->SetView(streamid,track,(void*)w->winId());
        w->setUpdatesEnabled(false);
    }
}

int Widget::RowGetStreamId(int i)
{
    return memberTableList[i];
}

void Widget::on_btnshareview_clicked()
{
    if(!sharekey)
    {
        AppendMsg(tr("没有人在共享"));
        return ;
    }

    QWidget* w = new QWidget();
    w->resize(640,480);
    w->show();
    if (memberMap.find(sharekey) == memberMap.end())
    {
        qDebug() << "Model is null" ;
        return;
    }
    MemberModel* Model = memberMap[sharekey];

    RoomControl::Get()->Picker(Model->data.stream_id(), 3);
    RoomControl::Get()->RemoveMember(Model->data.stream_id(), Model->streamItemId);

    qDebug()<<__func__<<sharekey<<shareStreamItemId;
    RoomControl::Get()->SetMember(
        Model->data.stream_id(),
        (void*)w->winId(),
        shareStreamItemId | VCS_PICKER_TRACKMASK_SYNC);
    if(RoomControl::Get()->roomInfo.stream_mode == 2){
        AppendMsg(tr("正在保存共享流"));
    }
    Model->view->setUpdatesEnabled(false);
    Model->view->update();

    Model->streamItemId = shareStreamItemId;
    RoomControl::Get()->SetViewPlus(Model->view, true);

}


void Widget::on_btnhechengview_clicked()
{
    QWidget* w = new QWidget();
    w->resize(640,480);
    w->show();
    RoomControl::Get()->Picker(1, 3);
    RoomControl::Get()->SetMember(
        1,
        (void*)w->winId(),
        1 | VCS_PICKER_TRACKMASK_SYNC);
}

void Widget::on_btntest_clicked()
{

}

