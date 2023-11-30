#include "DataModel/CorporationInfo.h"

void CorporationInfo::set_id(QString value)
{
	this->_id = value;
}
void CorporationInfo::set_name(QString value)
{
	this->_name = value;
}
void CorporationInfo::set_account_id(QString value)
{
	this->_account_id = value;
}
void CorporationInfo::set_created_at(int value)
{
	this->_created_at = value;
}
void CorporationInfo::set_vas_time(bool value)
{
	this->_vas_time = value;
}
void CorporationInfo::set_vas_conc(bool value)
{
	this->_vas_conc = value;
}
void CorporationInfo::set_reg_from(int value)
{
	this->_reg_from = value;
}
void CorporationInfo::set_app_id(QString value)
{
	this->_app_id = value;
}

void CorporationInfo::set_account(AccountInfo value)
{
	this->_account = value;
}


QString CorporationInfo::id()
{
	return _id;
}
QString CorporationInfo::name()
{
	return _name;
}
QString CorporationInfo::account_id()
{
	return _account_id;
}
int CorporationInfo::created_at()
{
	return _created_at;
}
bool CorporationInfo::vas_time()
{
	return _vas_time;
}
bool CorporationInfo::vas_conc()
{
	return _vas_conc;
}
int CorporationInfo::reg_from()
{
	return _reg_from;
}
QString CorporationInfo::app_id()
{
	return _app_id;
}

AccountInfo& CorporationInfo::account()
{
	return _account;
}


void CorporationInfo::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "name", _name);
		JsonUtil::GetValue(obj, "account_id", _account_id);
		JsonUtil::GetValue(obj, "created_at", _created_at);
		JsonUtil::GetValue(obj, "vas_time", _vas_time);
		JsonUtil::GetValue(obj, "vas_conc", _vas_conc);
		JsonUtil::GetValue(obj, "reg_from", _reg_from);
		JsonUtil::GetValue(obj, "app_id", _app_id);

		_account.Load(obj.value("account").toObject());
	}
}
