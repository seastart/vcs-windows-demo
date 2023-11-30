#include "UserData.h"

AccountInfo& UserData::account()
{
	return _account;
}
QString UserData::token()
{
	return _token;
}
CorporationInfo& UserData::corp()
{
	return _corp;
}
int UserData::corp_role()
{
	return _corp_role;
}
Reg& UserData::reg()
{
	return _reg;
}

void UserData::set_account(AccountInfo value)
{
	this->_account = value;
}
void UserData::set_token(QString value)
{

	this->_token = value;
}
void UserData::set_corp(CorporationInfo value)
{

	this->_corp = value;
}
void UserData::set_corp_role(int value)
{

	this->_corp_role = value;
}
void UserData::set_reg(Reg value)
{

	this->_reg = value;
}

void UserData::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "token", _token);
		JsonUtil::GetValue(obj, "corp_role", _corp_role);

		_reg.Load(obj.value("reg").toObject());
		_corp.Load(obj.value("corp").toObject());
		_account.Load(obj.value("account").toObject());
	}
}

void UserData::Save(QJsonObject obj)
{
	_object = new UserData();
	_object->Load(obj);
}
UserData* UserData::Get()
{
	return _object;
}

UserData* UserData::_object = nullptr;
