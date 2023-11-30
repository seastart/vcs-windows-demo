#include "Room.h"

QString Room::id()
{
	return _id;
}
QString Room::no()
{
	return _no;
}
QString Room::sdk_no()
{
	return _sdk_no;
}
bool Room::access_pwd()
{
	return _access_pwd;
}
bool Room::access_whitelist()
{
	return _access_whitelist;
}
QString Room::password()
{
	return _password;
}
int Room::limited()
{
	return _limited;
}
int Room::max_video()
{
	return _max_video;
}
int Room::samplerate()
{
	return _samplerate;
}
int Room::ol_count()
{
	return _ol_count;
}
int Room::state()
{
	return _state;
}

void Room::set_id(QString value)
{
	this->_id = value;
}
void Room::set_no(QString value)
{
	this->_no = value;
}
void Room::set_sdk_no(QString value)
{
	this->_sdk_no = value;
}
void Room::set_access_pwd(bool value)
{
	this->_access_pwd = value;
}
void Room::set_access_whitelist(bool value)
{
	this->_access_whitelist = value;
}
void Room::set_password(QString value)
{
	this->_password = value;
}
void Room::set_limited(int value)
{
	this->_limited = value;
}
void Room::set_max_video(int value)
{
	this->_max_video = value;
}
void Room::set_samplerate(int value)
{
	this->_samplerate = value;
}
void Room::set_ol_count(int value)
{
	this->_ol_count = value;
}
void Room::set_state(int value)
{
	this->_state = value;
}

void Room::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "no", _no);
		JsonUtil::GetValue(obj, "sdk_no", _sdk_no);
		JsonUtil::GetValue(obj, "access_pwd", _access_pwd);
		JsonUtil::GetValue(obj, "access_whitelist", _access_whitelist);
		JsonUtil::GetValue(obj, "password", _password);
		JsonUtil::GetValue(obj, "limited", _limited);
		JsonUtil::GetValue(obj, "max_video", _max_video);
		JsonUtil::GetValue(obj, "samplerate", _samplerate);
		JsonUtil::GetValue(obj, "ol_count", _ol_count);
		JsonUtil::GetValue(obj, "state", _state);
	}
}
