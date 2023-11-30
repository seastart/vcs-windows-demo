#include "Conf.h"

QString Conf::id()
{
	return this->_id;
}
QString Conf::title()
{
	return this->_title;
}
QString Conf::content()
{
	return this->_content;
}
int Conf::type()
{
	return this->_type;
}
int Conf::begin_time()
{
	return this->_begin_time;
}
int Conf::end_time()
{
	return this->_end_time;
}
int Conf::duration()
{
	return this->_duration;
}
int Conf::state()
{
	return this->_state;
}
QString Conf::account_id()
{
	return this->_account_id;
}
AccountInfo& Conf::account()
{
	return this->_account;
}
QString Conf::corp_id()
{
	return this->_corp_id;
}
CorporationInfo& Conf::corporation()
{
	return this->_corporation;
}
QString Conf::room_id()
{
	return this->_room_id;
}
Room& Conf::room()
{
	return this->_room;
}
QString Conf::log_id()
{
	return this->_log_id;
}



void Conf::set_id(QString value)
{
	this->_id = value;
}
void Conf::set_title(QString value)
{
	this->_title = value;
}
void Conf::set_content(QString value)
{
	this->_content = value;
}
void Conf::set_type(int value)
{
	this->_type = value;
}
void Conf::set_begin_time(int value)
{
	this->_begin_time = value;
}
void Conf::set_end_time(int value)
{
	this->_end_time = value;
}
void Conf::set_duration(int value)
{
	this->_duration = value;
}
void Conf::set_state(int value)
{
	this->_state = value;
}
void Conf::set_account_id(QString value)
{
	this->_account_id = value;
}
void Conf::set_account(AccountInfo value)
{
	this->_account = value;
}
void Conf::set_corp_id(QString value)
{
	this->_corp_id = value;
}
void Conf::set_corporation(CorporationInfo value)
{
	this->_corporation = value;
}
void Conf::set_room_id(QString value)
{
	this->_room_id = value;
}
void Conf::set_room(Room value)
{
	this->_room = value;
}
void Conf::set_log_id(QString value)
{
	this->_log_id = value;
}

void  Conf::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "title", _title);
		JsonUtil::GetValue(obj, "content", _content);
		JsonUtil::GetValue(obj, "type", _type);
		JsonUtil::GetValue(obj, "begin_time", _begin_time);
		JsonUtil::GetValue(obj, "end_time", _end_time);
		JsonUtil::GetValue(obj, "duration", _duration);
		JsonUtil::GetValue(obj, "state", _state);
		JsonUtil::GetValue(obj, "account_id", _account_id);
		JsonUtil::GetValue(obj, "corp_id", _corp_id);
		JsonUtil::GetValue(obj, "room_id", _room_id);
		JsonUtil::GetValue(obj, "log_id", _log_id);

		_room.Load(obj.value("room").toObject());
		_corporation.Load(obj.value("corporation").toObject());
		_account.Load(obj.value("account").toObject());
	}
}
