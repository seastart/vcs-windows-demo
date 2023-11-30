#include "CorpMemberItem.h"

QString CorpMemberItem::id()
{
	return _id;
}
QString CorpMemberItem::account_id()
{
	return _account_id;
}
AccountInfo& CorpMemberItem::account()
{
	return _account;
}
QString CorpMemberItem::nickname()
{
	return _nickname;
}
QString CorpMemberItem::corp_id()
{
	return _corp_id;
}
CorporationInfo& CorpMemberItem::corporation()
{
	return _corporation;
}
int CorpMemberItem::role()
{
	return _role;
}
QString CorpMemberItem::user_id()
{
	return _user_id;
}
int CorpMemberItem::created_at()
{
	return _created_at;
}

void CorpMemberItem::set_id(QString value)
{
	this->_id = value;
}
void CorpMemberItem::set_account_id(QString value)
{
	this->_account_id = value;
}
void CorpMemberItem::set_account(AccountInfo value)
{
	this->_account = value;
}
void CorpMemberItem::set_nickname(QString value)
{
	this->_nickname = value;
}
void CorpMemberItem::set_corp_id(QString value)
{
	this->_corp_id = value;
}
void CorpMemberItem::set_corporation(CorporationInfo value)
{
	this->_corporation = value;
}
void CorpMemberItem::set_role(int value)
{
	this->_role = value;
}
void CorpMemberItem::set_user_id(QString value)
{
	this->_user_id = value;
}
void CorpMemberItem::set_created_at(int value)
{
	this->_created_at = value;
}

void CorpMemberItem::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "account_id", _account_id);
		JsonUtil::GetValue(obj, "nickname", _nickname);
		JsonUtil::GetValue(obj, "corp_id", _corp_id);
		JsonUtil::GetValue(obj, "role", _role);
		JsonUtil::GetValue(obj, "user_id", _user_id);
		JsonUtil::GetValue(obj, "created_at", _created_at);

		_account.Load(obj.value("account").toObject());
		_corporation.Load(obj.value("corporation").toObject());
	}
}
