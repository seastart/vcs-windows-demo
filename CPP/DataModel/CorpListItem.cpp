#include "DataModel/CorpListItem.h"

QString CorpListItem::id()
{
	return _id;
}
QString CorpListItem::account_id()
{
	return _account_id;
}
QString CorpListItem::nickname()
{
	return _nickname;
}
QString CorpListItem::corp_id()
{
	return _corp_id;
}
int CorpListItem::role()
{
	return _role;
}
QString CorpListItem::user_id()
{
	return _user_id;
}
int CorpListItem::created_at()
{
	return _created_at;
}
CorporationInfo& CorpListItem::corporation()
{
	return _corporation;
}

void CorpListItem::set_id(QString Value)
{
	this->_id = Value;
}
void CorpListItem::set_account_id(QString Value)
{
	this->_account_id = Value;
}
void CorpListItem::set_nickname(QString Value)
{
	this->_nickname = Value;
}
void CorpListItem::set_corp_id(QString Value)
{
	this->_corp_id = Value;
}
void CorpListItem::set_role(int Value)
{
	this->_role = Value;
}
void CorpListItem::set_user_id(QString Value)
{
	this->_user_id = Value;
}
void CorpListItem::set_created_at(int Value)
{
	this->_created_at = Value;
}
void CorpListItem::set_corporation(CorporationInfo Value)
{
	this->_corporation = Value;
}

void CorpListItem::Load(QJsonObject obj)
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

		_corporation.Load(obj.value("corporation").toObject());
	}
}
