#include "StreamData.h"

void StreamData::Load(QJsonObject qjson)
{
	if (!qjson.isEmpty())
	{
		JsonUtil::GetValue(qjson, "address", _address);
		JsonUtil::GetValue(qjson, "astate", _astate);
		JsonUtil::GetValue(qjson, "delay", _delay);
		JsonUtil::GetValue(qjson, "down_lost", _down_lost);
		JsonUtil::GetValue(qjson, "down_rate", _down_rate);
		JsonUtil::GetValue(qjson, "id", _id);
		JsonUtil::GetValue(qjson, "mode", _mode);
		JsonUtil::GetValue(qjson, "name", _name);
		JsonUtil::GetValue(qjson, "net_level", _net_level);
		JsonUtil::GetValue(qjson, "nickname", _nickname);
		JsonUtil::GetValue(qjson, "port", _port);
		JsonUtil::GetValue(qjson, "portrait", _portrait);
		JsonUtil::GetValue(qjson, "role", _role);
		JsonUtil::GetValue(qjson, "shared_picture", _shared_picture);
		JsonUtil::GetValue(qjson, "stream_id", _stream_id);
		JsonUtil::GetValue(qjson, "tag", _tag);
		JsonUtil::GetValue(qjson, "terminal_type", _terminal_type);
		JsonUtil::GetValue(qjson, "up_lost", _up_lost);
		JsonUtil::GetValue(qjson, "up_rate", _up_rate);
		JsonUtil::GetValue(qjson, "vstate", _vstate);
		JsonUtil::GetValue(qjson, "hus", _hus);
		JsonUtil::GetValue(qjson, "up_level", _up_level);
		JsonUtil::GetValue(qjson, "relative_portrait", _relative_portrait);

		QJsonArray ss = qjson.value("streams").toArray();
		for (QJsonArray::iterator it = ss.begin(); it != ss.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			Stream s;
			s.Load(stream);
			_streams.append(s);
		}
	}
}

int StreamData::hus()
{
	return  _hus;
}
QString StreamData::address()
{
	return _address;
}
int StreamData::astate()
{
	return _astate;
}
int  StreamData::delay()
{
	return _delay;
}
int StreamData::down_lost()
{
	return _down_lost;
}
int StreamData::down_rate()
{
	return  _down_rate;
}
QString StreamData::id()
{
	return _id;
}
int StreamData::mode()
{
	return  _mode;
}
QString StreamData::name()
{
	return _name;
}
int StreamData::net_level()
{
	return _net_level;
}
QString StreamData::nickname()
{
	return  _nickname;
}
int StreamData::port()
{
	return _port;
}
QString StreamData::portrait()
{
	return  _portrait;
}
int StreamData::role()
{
	return _role;
}
QString StreamData::shared_picture()
{
	return _shared_picture;
}
int StreamData::stream_id()
{
	return _stream_id;
}
QString StreamData::tag()
{
	return  _tag;
}
int StreamData::terminal_type()
{
	return  _terminal_type;
}
int StreamData::up_lost()
{
	return  _up_lost;
}
int StreamData::up_rate()
{
	return  _up_rate;
}
int StreamData::vstate()
{
	return _vstate;
}
QList<Stream> StreamData::streams()
{
	return _streams;
}

int StreamData::up_level()
{
	return _up_level;
}

void StreamData::set_hus(int v)
{
	this->_hus = v;
}

void StreamData::set_up_level(int v)
{
	this->_up_level = v;
}

void StreamData::set_address(QString v)
{
	this->_address = v;
}

void StreamData::set_astate(int v)
{
	this->_astate = v;
}
void StreamData::set_delay(int v)
{
	this->_delay = v;
}
void StreamData::set_down_lost(int v)
{
	this->_down_lost = v;
}
void StreamData::set_down_rate(int v)
{
	this->_down_rate = v;
}
void StreamData::set_id(QString v)
{
	this->_id = v;
}
void StreamData::set_mode(int v)
{
	this->_mode = v;
}
void StreamData::set_name(QString v)
{
	this->_name = v;
}
void StreamData::set_net_level(int v)
{
	this->_net_level = v;
}
void StreamData::set_nickname(QString v)
{
	this->_nickname = v;
}
void StreamData::set_port(int v)
{
	this->_port = v;
}
void StreamData::set_portrait(QString v)
{
	this->_portrait = v;
}
void StreamData::set_role(int v)
{
	this->_role = v;
}
void StreamData::set_shared_picture(QString v)
{
	this->_shared_picture = v;
}
void StreamData::set_stream_id(int v)
{
	this->_stream_id = v;
}
void StreamData::set_tag(QString v)
{
	this->_tag = v;
}
void StreamData::set_terminal_type(int v)
{
	this->_terminal_type = v;
}
void StreamData::set_up_lost(int v)
{
	this->_up_lost = v;
}
void StreamData::set_up_rate(int v)
{
	this->_up_rate = v;
}
void StreamData::set_vstate(int v)
{
	this->_vstate = v;
}
void StreamData::set_streams(QList<Stream> v)
{
	this->_streams = v;
}
