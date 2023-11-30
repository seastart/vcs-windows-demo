#pragma once

#include "CJsonObject/JsonUtil.h"
enum CallMessageType
{
    CallWaiting = 0,
    CallAccepted = 1,
    CallRejected = 2,
    CallTimeout = 3,
    CallError = 4,
    CallBusy = 5,
    CallCanceled = 6,
    CallRemoved = 7,
};
class NoJoinedMemberInfo
{
public:
	NoJoinedMemberInfo();
	~NoJoinedMemberInfo() {}

	QString Id() { return id; }
	QString MeetingID() { return meetingID; }
	QString Name() { return name; }
	QString NickName() { return nickName; }
	QString PortraitURL() { return portraitURL; }
	int Status() { return status; }
	void SetId(QString id) { this->id = id; }
	void SetMeetingID(QString id) { this->meetingID = id; }
	void SetName(QString name) { this->name = name; }
	void SetNickName(QString nickname) { this->nickName = nickname; }
	void SetPortraitURL(QString url) { this->portraitURL = url; }
	void SetStatus(int st) { this->status = st; }
	void Load2(QJsonObject obj);
	void Load(QJsonObject obj);
private:
    QString id;
    QString	meetingID;
    QString name;
    QString nickName;
    QString portraitURL;
    int     status;
};
