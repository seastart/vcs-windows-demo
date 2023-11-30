#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QShowEvent>
#include <QMap>
#include "vcs/RoomControl.h"
#include "DataModel/StreamData.h"
#include "view/viewitem.h"
class MemberModel : public QObject
{
    Q_OBJECT

public:
    StreamData data;

    int state = 0;

    QWidget* view = nullptr;
    ViewItem* viewItem = nullptr;

    int type = 0;

    int isScreeShare = 0;

    int streamItemId = 0;

    int db = -60;
};

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void OpenRoom(bool speaker, bool mic, bool cam);

private slots:
    int OnRoomEvent(HROOM hroom, int iEventId, std::string jsonString);
    void on_btnCam_clicked();
    int OnAudioStatus(const char*);
    void on_btnexit_clicked();

    void on_rbtn1s_clicked();

    void on_rbtn10s_clicked();

    void OnRightClick();
    void OnLeftClicked();
    void on_btnMic_clicked();

    void on_btnSpeaker_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_btnShare_clicked();

    void on_btnstopshare_clicked();

    void on_btntrack_clicked();

    void on_btnshareview_clicked();

    void on_btnhechengview_clicked();

    void on_btntest_clicked();

private:
    void AppendMsg(QString msg);
    void OnCloseRoom();
    void CloseAllPlayer(bool me = true);
    void CloseShareShowView(int key);
    bool UpdateVideoView(int key);
    bool UpdateAudioView(int key);
    void UpdateView(int key, bool videoChange = true, bool AduioChange = true);
    void SetMemberVideoView(int key);
    void SetMemberAudioView(int key);

    void OnStartMemberShare(int key,int shareStreamItemId);
    void OnStartShare();

    void OpenCloseCamera(bool v);
    void OpenCloseSpeaker(bool v);
    void OpenCloseMic(int v);

    void AddMember(const QString jsonString);
    void UpdateMember(const QString jsonString);
    void AddSelfMember(QWidget* memberView);
    void MyAccountUpdate(const QString jsonString);
    bool IsChangeData( int id,StreamData& data,bool& VstateChange,bool& AudioChange,bool& RoleChange,bool& NicknameChange);
    void MemberExitRoom(int key);

    void UpdateMemberRecv(QString);
    void ReLoadMemberView(QList<int>);

    int RowGetStreamId(int);
private:
    Ui::Widget *ui;
    int SELF_ID ;
    int sharekey;
    QPushButton* leftBtn;
    QPushButton* rightBtn;
    QList<int> memberTableList;
    int memberTableListShowIndex;
    QMap<int, MemberModel*> memberMap;
    QList<ViewItem*> ViewItemList;
    int tableRow;
    int shareStreamItemId;
};
#endif // WIDGET_H
