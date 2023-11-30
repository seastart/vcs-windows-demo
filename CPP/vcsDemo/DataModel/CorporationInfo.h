#pragma once
#include "CJsonObject/JsonUtil.h"
#include "AccountInfo.h"
class CorporationInfo
{
public:

	void set_id(QString value);
	void set_name(QString value);
	void set_account_id(QString value);
	void set_created_at(int value);
	void set_vas_time(bool value);
	void set_vas_conc(bool value);
	void set_reg_from(int value);
	void set_app_id(QString value);
	void set_account(AccountInfo value);

	QString id();
	QString name();
	QString account_id();
	int created_at();
	bool vas_time();
	bool vas_conc();
	int reg_from();
	QString app_id();
	AccountInfo& account();

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _name;
	QString _account_id;
	int _created_at;
	bool _vas_time;
	bool _vas_conc;
	int _reg_from;
	QString _app_id;
	AccountInfo _account;
};
