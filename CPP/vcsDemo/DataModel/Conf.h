#pragma once

#include <QObject>
#include "CJsonObject/JsonUtil.h"
#include "AccountInfo.h"
#include "CorporationInfo.h"
#include "Room.h"
class Conf
{
public:
	QString id();
	QString title();
	QString content();
	int type();
	int begin_time();
	int end_time();
	int duration();
	int state();
	QString account_id();
	AccountInfo& account();
	QString corp_id();
	CorporationInfo& corporation();
	QString room_id();
	Room& room();
	QString log_id();

	void set_id(QString);
	void set_title(QString);
	void set_content(QString);
	void set_type(int);
	void set_begin_time(int);
	void set_end_time(int);
	void set_duration(int);
	void set_state(int);
	void set_account_id(QString);
	void set_account(AccountInfo);
	void set_corp_id(QString);
	void set_corporation(CorporationInfo);
	void set_room_id(QString);
	void set_room(Room);
	void set_log_id(QString);

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _title;
	QString _content;
	int _type;
	int _begin_time;
	int _end_time;
	int _duration;
	int _state;
	QString _account_id;
	AccountInfo _account;
	QString _corp_id;
	CorporationInfo _corporation;
	QString _room_id;
	Room _room;
	QString _log_id;
};
