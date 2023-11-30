#include "HistoryMeetingItem.h"

QString HistoryMeetingItem::id()
{
	return _id;
}
QString HistoryMeetingItem::conf_id()
{
	return _conf_id;
}
Conf& HistoryMeetingItem::conf()
{
	return _conf;
}
QString HistoryMeetingItem::title()
{
	return _title;
}
QString HistoryMeetingItem::content()
{
	return _content;
}
int HistoryMeetingItem::begin_at()
{
	return _begin_at;
}
int HistoryMeetingItem::end_at()
{
	return _end_at;
}
int HistoryMeetingItem::duration()
{
	return _duration;
}
int HistoryMeetingItem::state()
{
	return _state;
}
QString HistoryMeetingItem::room_id()
{
	return _room_id;
}
Room& HistoryMeetingItem::room()
{
	return _room;
}
QString HistoryMeetingItem::corp_id()
{
	return _corp_id;
}
CorporationInfo	HistoryMeetingItem::corp()
{
	return _corp;
}

void HistoryMeetingItem::set_id(QString value)
{
	this->_id = value;
}
void HistoryMeetingItem::set_conf_id(QString value)
{
	this->_conf_id = value;
}
void HistoryMeetingItem::set_conf(Conf value)
{
	this->_conf = value;
}
void HistoryMeetingItem::set_title(QString value)
{
	this->_title = value;
}
void HistoryMeetingItem::set_content(QString value)
{
	this->_content = value;
}
void HistoryMeetingItem::set_begin_at(int value)
{
	this->_begin_at = value;
}
void HistoryMeetingItem::set_end_at(int value)
{
	this->_end_at = value;
}
void HistoryMeetingItem::set_duration(int value)
{
	this->_duration = value;
}
void HistoryMeetingItem::set_state(int value)
{
	this->_state = value;
}
void HistoryMeetingItem::set_room_id(QString value)
{
	this->_room_id = value;
}
void HistoryMeetingItem::set_room(Room value)
{
	this->_room = value;
}
void HistoryMeetingItem::set_corp_id(QString value)
{
	this->_corp_id = value;
}
void HistoryMeetingItem::set_corp(CorporationInfo value)
{
	this->_corp = value;
}

void HistoryMeetingItem::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "conf_id", _conf_id);
		JsonUtil::GetValue(obj, "title", _title);
		JsonUtil::GetValue(obj, "content", _content);
		JsonUtil::GetValue(obj, "begin_at", _begin_at);
		JsonUtil::GetValue(obj, "end_at", _end_at);
		JsonUtil::GetValue(obj, "duration", _duration);
		JsonUtil::GetValue(obj, "state", _state);
		JsonUtil::GetValue(obj, "room_id", _room_id);
		JsonUtil::GetValue(obj, "corp_id", _corp_id);

		_conf.Load(obj.value("conf").toObject());
		_room.Load(obj.value("room").toObject());
		_corp.Load(obj.value("corp").toObject());
	}
}
