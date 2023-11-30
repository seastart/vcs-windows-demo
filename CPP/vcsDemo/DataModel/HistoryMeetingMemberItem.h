#pragma once

#include <QObject>
#include "CJsonObject/JsonUtil.h"
#include "Conf.h"
#include "AccountInfo.h"
class HistoryMeetingMemberItem
{
public:
	QString id();
	QString log_id();
	QString conf_id();
	Conf& conf();
	QString room_id();
	QString account_id();
	AccountInfo& account();
	QString account_nickname();
	int begin_at();
	int state();
	int role();
	int deleted_at();
	int astate();
	int vstate();

	void set_id(QString);
	void set_log_id(QString);
	void set_conf_id(QString);
	void set_conf(Conf);
	void set_room_id(QString);
	void set_account_id(QString);
	void set_account(AccountInfo);
	void set_account_nickname(QString);
	void set_begin_at(int);
	void set_state(int);
	void set_role(int);
	void set_deleted_at(int);
	void set_astate(int);
	void set_vstate(int);

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _log_id;
	QString _conf_id;
	Conf _conf;
	QString _room_id;
	QString _account_id;
	AccountInfo _account;
	QString _account_nickname;
	int _begin_at;
	int _state;
	int _role;
	int _deleted_at;
	int _astate;
	int _vstate;
};
