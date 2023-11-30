#pragma once

#include "CJsonObject/JsonUtil.h"
#include "CorporationInfo.h"
class CorpListItem
{

public:
	QString id();
	QString account_id();
	QString nickname();
	QString corp_id();
	int role();
	QString user_id();
	int created_at();
	CorporationInfo& corporation();

	void set_id(QString Value);
	void set_account_id(QString Value);
	void set_nickname(QString Value);
	void set_corp_id(QString Value);
	void set_role(int Value);
	void set_user_id(QString Value);
	void set_created_at(int Value);
	void set_corporation(CorporationInfo Value);

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _account_id;
	QString _nickname;
	QString _corp_id;
	int _role;
	QString _user_id;
	int _created_at;
	CorporationInfo _corporation;
};
