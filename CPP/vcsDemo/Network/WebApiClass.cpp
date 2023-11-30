#include "WebApiClass.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "DataModel/UserData.h"

#include "../Tools/Utils.h"
#include <QUuid>
void WebApiClass::ConferenceStop(QString conf_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;
	map.insert("conf_id", conf_id);


	HttpNetwork::OnPost("conference/stop", map, function);
}

void WebApiClass::RoomExit(QString room_no, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;
	map.insert("room_no", room_no);


	HttpNetwork::OnPost("room/exit", map, function);
}

void WebApiClass::FileAdd(QString name, int size, QByteArray unique, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;
	map.insert("name", name);
	map.insert("size", QString::number(size));
	map.insert("unique", QString(unique));

	HttpNetwork::OnPost("file/add", map, function);
}

QByteArray WebApiClass::CorporationMembersSync(QString corp_id)
{

	QMap<QString, QString> map;
	map.insert("corp_id", corp_id);
	map.insert("limit", "999");

	return HttpNetworkSync::OnPost("corporation/members", map);
}
void WebApiClass::RoomEnter(QString room_no, QString pass, std::function<void(QByteArray& byte)> function)
{
	QString device_id = Utils::GetMac();
    QString line;
	QMap<QString, QString> map = {
		{ "room_no", room_no },
		{ "device_id", device_id}
	};
	if (!line.isEmpty())
	{
		map.insert("line_id", line);
	}
	if (!pass.isEmpty())
	{
		map.insert("password", pass);
	}

	HttpNetwork::OnPost("room/enter", map, function);
}

void WebApiClass::RoomGet(QString room_no, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "room_no", room_no }
	};

	HttpNetwork::OnPost("room/get", map, function);
}

void WebApiClass::RoomKickout(QString room_id, QString account_id, bool reenter, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "room_id", room_id },
		{ "account_id", account_id },
		{ "reenter", reenter ? "true" : "false" }
	};

	HttpNetwork::OnPost("room/kickout", map, function);
}

void WebApiClass::RoomLock(QString room_id, bool lock, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "room_id", room_id },
	{ "lock", lock ? "true" : "false" }
	};

	HttpNetwork::OnPost("room/lock", map, function);
}


void WebApiClass::ConferenceGet(QString conf_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "conf_id", conf_id }
	};

	HttpNetwork::OnPost("conference/get", map, function);
}

void WebApiClass::ConferenceGet_Members(QString conf_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "conf_id", conf_id }
	};

	HttpNetwork::OnPost("conference/get-members", map, function);
}

void WebApiClass::ConferenceMy_Involved(QString corp_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "corp_id", corp_id }
	};

	HttpNetwork::OnPost("conference/my-involved", map, function);
}

void WebApiClass::CorporationMembers(QString corp_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "corp_id", corp_id },
	{ "limit", "999" }
	};

	HttpNetwork::OnPost("corporation/members", map, function);
}
#include <QMap>
void WebApiClass::ConferenceDelete(QString conf_id, bool stopMeeting, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "conf_id", conf_id }
	};
	QMap<QString, QString> map2;
	map2.insert("conf_id", conf_id);
	if (stopMeeting)
	{
		QByteArray byte = HttpNetworkSync::OnPost("conference/stop", map2);
		QJsonDocument jsonDoc = QJsonDocument::fromJson(byte);
		QJsonObject Json = jsonDoc.object();
		int code;
		JsonUtil::GetValue(Json, "code", code);
		if (code != 200)
		{
			QString msg;
			JsonUtil::GetValue(Json, "msg", msg);
			qDebug() << QString::fromLocal8Bit("退出会议出现问题!~%1").arg(msg);
			if (function != nullptr)
			{
				function(byte);
			}
			return;
		}
	}

	HttpNetwork::OnPost("conference/delete", map, function);
}

void WebApiClass::ConferenceLog_Members(QString conf_id, QString log_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "conf_id", conf_id },
		{"log_id",log_id }
	};

	HttpNetwork::OnPost("conference/log-members", map, function);
}

void WebApiClass::ConferenceMy_Logs(QString conf_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "conf_id", conf_id }
	};

	HttpNetwork::OnPost("conference/my-logs", map, function);
}

void WebApiClass::ConferenceMy_Corps(std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;

	HttpNetwork::OnPost("corporation/my-corps", map, function);
}

void WebApiClass::StopConferenceMy_Corps()
{
	HttpNetwork::ClearUrlPost(HttpNetwork::Get()->Host() + "corporation/my-corps");
}
void WebApiClass::AccountPortrait(QString url, QString url2, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{ "portrait", url },
	{ "relative_portrait", url2 },
	};

	HttpNetwork::OnPost("account/update", map, function);
}

void WebApiClass::AccountVcode(QString used_for, QString mobile, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "used_for", used_for },
		{ "mobile", mobile },
	};

	HttpNetwork::OnPost("account/vcode", map, function);
}

void WebApiClass::AccountReset_Password(QString new_password, QString vcode, QString name, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "new_password", new_password },
		{ "vcode", vcode },
		{ "name", name },
	};

	HttpNetwork::OnPost("account/reset-password", map, function);
}

void WebApiClass::AccountLogin(QString loginname, QString password, QString dev_type, std::function<void(QByteArray& byte)> function)
{
	QString device_id = Utils::GetMac();
	QMap<QString, QString> map = {
		{ "loginname", loginname },
		{ "password", password },
		{ "dev_type", dev_type },
		{ "device_id", device_id },
	};

	HttpNetwork::OnPost("account/login", map, function);
}

void WebApiClass::AccountRegister(QString name, QString password, QString nickname, QString mobile, QString vcode, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "name", name },
		{ "password", password },
		{ "nickname", nickname },
		{ "mobile", mobile },
		{ "vcode", vcode },
	};

	HttpNetwork::OnPost("account/register", map, function);
}

void WebApiClass::AccountUpdateNickname(QString nickname, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{ "nickname", nickname },
	};

	HttpNetwork::OnPost("account/update", map, function);
}

void WebApiClass::ConferenceCreate(QMap<QString, QString> map, std::function<void(QByteArray& byte)> function)
{
	HttpNetwork::OnPost("conference/create", map, function);
}

void WebApiClass::ConferenceUpdate(QMap<QString, QString> map, std::function<void(QByteArray& byte)> function)
{
	HttpNetwork::OnPost("conference/update", map, function);
}


void WebApiClass::ConferenceSetMembers(QString conf_id, QStringList userList, std::function<void(QByteArray& byte)> function)
{
	UserData* ud = UserData::Get();
	QJsonDocument doc;
	QJsonArray qj;
	QJsonObject obj;
	obj.insert("id", ud->account().id());
	obj.insert("role", 1);
	qj.append(obj);

	userList.removeAll(ud->account().id());
	foreach(QString s, userList)
	{
		QJsonObject obj1;
		obj1.insert("id", s);
		obj1.insert("role", 0);
		qj.append(obj1);
	}
	doc.setArray(qj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));

	QMap<QString, QString> map = {
	{"conf_id", conf_id },
	{"members",dataToString},
	};
	HttpNetwork::OnPost("conference/update", map, function);
}

void WebApiClass::AccountSetWhitelist(QString acc_id, QStringList userList, std::function<void(QByteArray& byte)> function)
{
	UserData* ud = UserData::Get();
	QJsonDocument doc;
	QJsonArray qj;
	QJsonObject obj;
	obj.insert("id", ud->account().id());
	obj.insert("role", 1);
	qj.append(obj);

	userList.removeAll(ud->account().id());
	foreach(QString s, userList)
	{
		QJsonObject obj1;
		obj1.insert("id", s);
		obj1.insert("role", 0);
		qj.append(obj1);
	}
	doc.setArray(qj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));

	QMap<QString, QString> map = {
	{"members",dataToString},
	};
	HttpNetwork::OnPost("account/set-whitelist", map, function);
}


void WebApiClass::CorporationCreate(QString corp_name, QString logo, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;
	map.insert("name", corp_name);
	map.insert("logo", logo);

	QByteArray byte = HttpNetworkSync::OnPost("corporation/create", map);
	QJsonDocument jsonDoc = QJsonDocument::fromJson(byte);
	QJsonObject Json = jsonDoc.object();
	int code;
	JsonUtil::GetValue(Json, "code", code);

	if (code != 200)
	{
		QString msg;
		JsonUtil::GetValue(Json, "msg", msg);
		qDebug() << QString::fromLocal8Bit("创建企业出现问题!~%1").arg(msg);
		if (function != nullptr)
		{
			function(byte);
		}
		return;
	}
	QString id = Json.value("data").toObject().value("id").toString();

	AccountSwitch_Corp(id, function);
}

void WebApiClass::AccountSwitch_Corp(QString corp_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{"corp_id",corp_id},
	};
	HttpNetwork::OnPost("account/switch-corp", map, function);
}

void WebApiClass::AccountFeedback(QString content, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{"dev_type","1"},
		{"content",content}
	};
	HttpNetwork::OnPost("account/feedback", map, function);
}

void WebApiClass::AccountGetUrlByLineid(std::function<void(QByteArray& byte)> function)
{
    QString line;
	QMap<QString, QString> map;
	if (!line.isEmpty())
	{
		map.insert("line_id", line);
	}
	HttpNetwork::OnPost("account/get-url-by-lineid", map, function);
}

QByteArray WebApiClass::AccountGetSync()
{
	QMap<QString, QString> map;

	return HttpNetworkSync::OnPost("account/get", map);
}


QByteArray WebApiClass::ServerRegSync(QString line_id)
{
	QMap<QString, QString> map;
	map.insert("line_id", line_id);

	return HttpNetworkSync::OnPost("server/reg", map);
}

void WebApiClass::ServerReg(QString line_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;
	map.insert("line_id", line_id);

	HttpNetwork::OnPost("server/reg", map, function);
}


void WebApiClass::ServerLines(std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map;
	HttpNetwork::OnPost("server/lines", map, function);
}

void WebApiClass::StopServerLines()
{
	HttpNetwork::ClearUrlPost(HttpNetwork::Get()->Host() + "server/lines");
}

void WebApiClass::ServerStream(QString roomNo, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{"room_no",roomNo}
	};
	HttpNetwork::OnPost("server/stream", map, function);
}
void WebApiClass::StopServerStream()
{
	HttpNetwork::ClearUrlPost(HttpNetwork::Get()->Host() + "server/stream");
}

void WebApiClass::RoomSet_Room_Move_Host(QString room_id, QString source_id, QString target_id, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{"room_id",room_id},
	{"source_id",source_id},
	{"target_id",target_id},
	{"msg_id",QUuid::createUuid().toString()},
	};
	HttpNetwork::OnPost("room/set-room-move-host", map, function);
}

void WebApiClass::RoomSet_Room_Recovery_Host(QString room_id, QString source_id, QString tarid, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{"room_id",room_id},
	{"source_id",source_id},
	{"target_id",tarid},
	{"msg_id",QUuid::createUuid().toString()},
	};
	HttpNetwork::OnPost("room/set-room-recovery-host", map, function);
}

void WebApiClass::RoomSet_Room_Union_Host(QString room_id, QString source_id, QString target_id, bool v, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{"room_id",room_id},
	{"source_id",source_id},
	{"target_id",target_id},
	{"state",v ? "1" : "0"},
	{"msg_id",QUuid::createUuid().toString()},
	};
	HttpNetwork::OnPost("room/set-room-union-host", map, function);
}

void WebApiClass::CorporationAdd_Member(QString acc_name, int role, QString nickname, std::function<void(QByteArray& byte)> function)
{
	QString corp_id = UserData::Get()->corp().id();
	QMap<QString, QString> map = {
		{"corp_id",corp_id},
		{"acc_name",acc_name},
		{"role",QString::number(role)},
		{"nickname",nickname},
	};
	HttpNetwork::OnPost("corporation/add-member", map, function);
}

void WebApiClass::CorporationUpdate_Member(QString corp_id, QString acc_name, QString nickname, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
		{"corp_id",corp_id},
		{"acc_id",acc_name},
		{"nickname",nickname},
	};
	HttpNetwork::OnPost("corporation/update-member", map, function);
}

void WebApiClass::CorporationDelete_Member(QString corp_id, QString acc_name, std::function<void(QByteArray& byte)> function)
{
	QMap<QString, QString> map = {
	{"corp_id",corp_id},
	{"acc_id",acc_name},
	};
	HttpNetwork::OnPost("corporation/delete-member", map, function);
}
