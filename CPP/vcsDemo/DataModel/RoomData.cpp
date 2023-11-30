#include "RoomData.h"

QString RoomData::stream_host()
{
	return _stream_host;
}
int RoomData::stream_port()
{
	return _stream_port;
}
QString RoomData::stream_ws_url()
{
	return _stream_ws_url;
}
QString RoomData::wb_host()
{
	return _wb_host;
}
QString RoomData::meeting_host()
{
	return _meeting_host;
}
int RoomData::meeting_port()
{
	return _meeting_port;
}
QString RoomData::meeting_ws_url()
{
	return _meeting_ws_url;
}
QString RoomData::session()
{
	return _session;
}
QString RoomData::sdk_no()
{
	return _sdk_no;
}
int RoomData::role()
{
	return _role;
}
QString RoomData::title()
{
	return _title;
}
Room& RoomData::room()
{
	return _room;
}
int RoomData::type()
{
	return _type;
}
AccountInfo& RoomData::account()
{
	return _account;
}
Conf& RoomData::conf()
{
	return _conf;
}

void RoomData::set_stream_host(QString value)
{
	this->_stream_host = value;
}
void RoomData::set_stream_port(int value)
{
	this->_stream_port = value;
}
void RoomData::set_stream_ws_url(QString value)
{
	this->_stream_ws_url = value;
}
void RoomData::set_wb_host(QString value)
{
	this->_wb_host = value;
}
void RoomData::set_meeting_host(QString value)
{
	this->_meeting_host = value;
}
void RoomData::set_meeting_port(int value)
{
	this->_meeting_port = value;
}
void RoomData::set_meeting_ws_url(QString value)
{
	this->_meeting_ws_url = value;
}
void RoomData::set_session(QString value)
{
	this->_session = value;
}
void RoomData::set_sdk_no(QString value)
{
	this->_sdk_no = value;
}
void RoomData::set_role(int value)
{
	this->_role = value;
}
void RoomData::set_title(QString value)
{
	this->_title = value;
}
void RoomData::set_room(Room value)
{
	this->_room = value;
}
void RoomData::set_type(int value)
{
	this->_type = value;
}
void RoomData::set_account(AccountInfo value)
{
	this->_account = value;
}
void RoomData::set_conf(Conf value)
{
	this->_conf = value;
}

void RoomData::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "stream_host", _stream_host);
		JsonUtil::GetValue(obj, "stream_port", _stream_port);
		JsonUtil::GetValue(obj, "stream_ws_url", _stream_ws_url);
		JsonUtil::GetValue(obj, "wb_host", _wb_host);
		JsonUtil::GetValue(obj, "meeting_host", _meeting_host);
		JsonUtil::GetValue(obj, "meeting_port", _meeting_port);
		JsonUtil::GetValue(obj, "meeting_ws_url", _meeting_ws_url);
		JsonUtil::GetValue(obj, "session", _session);
		JsonUtil::GetValue(obj, "sdk_no", _sdk_no);

		JsonUtil::GetValue(obj, "role", _role);
		JsonUtil::GetValue(obj, "title", _title);
		JsonUtil::GetValue(obj, "type", _type);
		JsonUtil::GetValue(obj, "meeting_server_id", _meeting_server_id);

		_room.Load(obj.value("room").toObject());
		_account.Load(obj.value("account").toObject());
		_conf.Load(obj.value("conf").toObject());
	}
}
