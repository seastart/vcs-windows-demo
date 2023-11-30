#pragma once
#include "CJsonObject/JsonUtil.h"
#include "DataModel/AccountInfo.h"
#include "DataModel/CorporationInfo.h"
class CorpMemberItem
{
public:
	QString id();
	QString account_id();
	AccountInfo& account();
	QString nickname();
	QString corp_id();
	CorporationInfo& corporation();
	int role();
	QString user_id();
	int created_at();

	void set_id(QString);
	void set_account_id(QString);
	void set_account(AccountInfo);
	void set_nickname(QString);
	void set_corp_id(QString);
	void set_corporation(CorporationInfo);
	void set_role(int);
	void set_user_id(QString);
	void set_created_at(int);

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _account_id;
	AccountInfo _account;
	QString _nickname;
	QString _corp_id;
	CorporationInfo _corporation;
	int _role;
	QString _user_id;
	int _created_at;
};
