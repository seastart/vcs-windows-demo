#pragma once

#include <QObject>
#include <functional>
#include <unordered_map>
#include <QStringList>
#include "HttpNetwork.h"
#include "HttpNetworkSync.h"
class WebApiClass : public QObject
{
	Q_OBJECT

public:
	WebApiClass() {};
	~WebApiClass() {};
public:

	static QByteArray CorporationMembersSync(QString corp_id);

	static void CorporationMembers(QString corp_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void CorporationCreate(QString corp_name, QString logo, std::function<void(QByteArray& byte)> function = nullptr);

	static void CorporationUpdate_Member(QString corp_id, QString acc_name, QString name, std::function<void(QByteArray& byte)> function = nullptr);

	static void CorporationDelete_Member(QString corp_id, QString acc_name, std::function<void(QByteArray& byte)> function = nullptr);

	static void CorporationAdd_Member(QString acc_name, int role, QString nickname, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceGet(QString conf_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceGet_Members(QString conf_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceMy_Involved(QString corp_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceDelete(QString conf_id, bool stopMeeting = true, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceLog_Members(QString conf_id, QString log_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceMy_Logs(QString conf_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceMy_Corps(std::function<void(QByteArray& byte)> function = nullptr);
	static void StopConferenceMy_Corps();
	static void ConferenceStop(QString conf_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceCreate(QMap<QString, QString> map, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceUpdate(QMap<QString, QString> map, std::function<void(QByteArray& byte)> function = nullptr);

	static void ConferenceSetMembers(QString conf_id, QStringList userList, std::function<void(QByteArray& byte)> function = nullptr);

	static void RoomExit(QString room_no, std::function<void(QByteArray& byte)> function = nullptr);

	static void RoomEnter(QString room_no, QString pass = "", std::function<void(QByteArray& byte)> function = nullptr);

	static void RoomGet(QString room_no, std::function<void(QByteArray& byte)> function = nullptr);

	static void RoomKickout(QString room_id, QString account_id, bool reenter, std::function<void(QByteArray& byte)> function = nullptr);

	static void RoomLock(QString room_id, bool lock, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountPortrait(QString url, QString url2, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountVcode(QString used_for, QString mobile, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountReset_Password(QString pString, QString vcode, QString name, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountLogin(QString loginname, QString password, QString dev_type, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountRegister(QString name, QString password, QString nickname, QString mobile, QString vcode, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountUpdateNickname(QString name, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountSetWhitelist(QString acc_id, QStringList userList, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountSwitch_Corp(QString corp_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountFeedback(QString content, std::function<void(QByteArray& byte)> function = nullptr);

	static void AccountGetUrlByLineid(std::function<void(QByteArray& byte)> function = nullptr);

	static QByteArray AccountGetSync();

	static void FileAdd(QString name, int size, QByteArray unique, std::function<void(QByteArray& byte)> function = nullptr);

	static QByteArray ServerRegSync(QString line_id);

	static void ServerReg(QString line_id, std::function<void(QByteArray& byte)> function = nullptr);

	static void ServerLines(std::function<void(QByteArray& byte)> function = nullptr);

	static void StopServerLines();

	static void ServerStream(QString roomNo, std::function<void(QByteArray& byte)> function = nullptr);
	static void StopServerStream();



	static void RoomSet_Room_Move_Host(QString room_id, QString source_id, QString target_id, std::function<void(QByteArray& byte)> function = nullptr);
	static void RoomSet_Room_Recovery_Host(QString room_id, QString source_id, QString tarid, std::function<void(QByteArray& byte)> function = nullptr);
	static void RoomSet_Room_Union_Host(QString room_id, QString source_id, QString target_id, bool, std::function<void(QByteArray& byte)> function = nullptr);
};
