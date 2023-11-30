#include "AccountInfo.h"

QString AccountInfo::id()
{
	return _id;
}
QString AccountInfo::name()
{
	return _name;
}
QString AccountInfo::nickname()
{
	return _nickname;
}
int AccountInfo::type()
{
	return _type;
}
QString AccountInfo::portrait()
{
	return _portrait;
}
QString AccountInfo::mobile()
{
	return _mobile;
}
int AccountInfo::created_at()
{
	return _created_at;
}
int AccountInfo::updated_at()
{
	return _updated_at;
}
int AccountInfo::state()
{
	return _state;
}
QString AccountInfo::room_id()
{
	return _room_id;
}
Room& AccountInfo::room()
{
	return _room;
}
QString AccountInfo::corp_nickname()
{
	return _corp_nickname;
}
int AccountInfo::corp_role()
{
	return _corp_role;
}
QString AccountInfo::corp_id()
{
	return _corp_id;
}
QString AccountInfo::corp_name()
{
	return _corp_name;
}
int AccountInfo::fs_used_size()
{
	return _fs_used_size;
}
int AccountInfo::reg_from()
{
	return _reg_from;
}

void AccountInfo::set_id(QString Value)
{
	this->_id = Value;
}
void AccountInfo::set_name(QString Value)
{
	this->_name = Value;
}
void AccountInfo::set_nickname(QString Value)
{
	this->_nickname = Value;
}
void AccountInfo::set_type(int Value)
{
	this->_type = Value;
}
void AccountInfo::set_portrait(QString Value)
{
	this->_portrait = Value;
}
void AccountInfo::set_mobile(QString Value)
{
	this->_mobile = Value;
}
void AccountInfo::set_created_at(int Value)
{
	this->_created_at = Value;
}
void AccountInfo::set_updated_at(int Value)
{
	this->_updated_at = Value;
}
void AccountInfo::set_state(int Value)
{
	this->_state = Value;
}
void AccountInfo::set_room_id(QString Value)
{
	this->_room_id = Value;
}
void AccountInfo::set_room(Room Value)
{
	this->_room = Value;
}
void AccountInfo::set_corp_nickname(QString Value)
{
	this->_corp_nickname = Value;
}
void AccountInfo::set_corp_role(int Value)
{
	this->_corp_role = Value;
}
void AccountInfo::set_corp_id(QString Value)
{
	this->_corp_id = Value;
}
void AccountInfo::set_corp_name(QString Value)
{
	this->_corp_name = Value;
}
void AccountInfo::set_fs_used_size(int Value)
{
	this->_fs_used_size = Value;
}
void AccountInfo::set_reg_from(int Value)
{
	this->_reg_from = Value;
}

void AccountInfo::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "name", _name);
		JsonUtil::GetValue(obj, "nickname", _nickname);
		JsonUtil::GetValue(obj, "type", _type);
		JsonUtil::GetValue(obj, "portrait", _portrait);
		JsonUtil::GetValue(obj, "mobile", _mobile);
		JsonUtil::GetValue(obj, "created_at", _created_at);
		JsonUtil::GetValue(obj, "updated_at", _updated_at);
		JsonUtil::GetValue(obj, "room_id", _room_id);
		JsonUtil::GetValue(obj, "corp_nickname", _corp_nickname);
		JsonUtil::GetValue(obj, "corp_role", _corp_role);
		JsonUtil::GetValue(obj, "corp_id", _corp_id);
		JsonUtil::GetValue(obj, "corp_name", _corp_name);
		JsonUtil::GetValue(obj, "fs_used_size", _fs_used_size);
		JsonUtil::GetValue(obj, "reg_from", _reg_from);

		JsonUtil::GetValue(obj, "relative_portrait", _relative_portrait);
		_room.Load(obj.value("room").toObject());
	}
}
