#include "HistoryMeetingMemberItem.h"


QString HistoryMeetingMemberItem::id()
{
	return _id;
}
QString HistoryMeetingMemberItem::log_id()
{
	return _log_id;
}
QString HistoryMeetingMemberItem::conf_id()
{
	return _conf_id;
}
Conf& HistoryMeetingMemberItem::conf()
{
	return _conf;
}
QString HistoryMeetingMemberItem::room_id()
{
	return _room_id;
}
QString HistoryMeetingMemberItem::account_id()
{
	return _account_id;
}
AccountInfo& HistoryMeetingMemberItem::account()
{
	return _account;
}
QString HistoryMeetingMemberItem::account_nickname()
{
	return _account_nickname;
}
int HistoryMeetingMemberItem::begin_at()
{
	return _begin_at;
}
int HistoryMeetingMemberItem::state()
{
	return _state;
}
int HistoryMeetingMemberItem::role()
{
	return _role;
}
int HistoryMeetingMemberItem::deleted_at()
{
	return _deleted_at;
}
int HistoryMeetingMemberItem::astate()
{
	return _astate;
}
int HistoryMeetingMemberItem::vstate()
{
	return _vstate;
}

void HistoryMeetingMemberItem::set_id(QString value)
{
	this->_id = value;
}
void HistoryMeetingMemberItem::set_log_id(QString value)
{
	this->_log_id = value;
}
void HistoryMeetingMemberItem::set_conf_id(QString value)
{
	this->_conf_id = value;
}
void HistoryMeetingMemberItem::set_conf(Conf value)
{
	this->_conf = value;
}
void HistoryMeetingMemberItem::set_room_id(QString value)
{
	this->_room_id = value;
}
void HistoryMeetingMemberItem::set_account_id(QString value)
{
	this->_account_id = value;
}
void HistoryMeetingMemberItem::set_account(AccountInfo value)
{
	this->_account = value;
}
void HistoryMeetingMemberItem::set_account_nickname(QString value)
{
	this->_account_nickname = value;
}
void HistoryMeetingMemberItem::set_begin_at(int value)
{
	this->_begin_at = value;
}
void HistoryMeetingMemberItem::set_state(int value)
{
	this->_state = value;
}
void HistoryMeetingMemberItem::set_role(int value)
{
	this->_role = value;
}
void HistoryMeetingMemberItem::set_deleted_at(int value)
{
	this->_deleted_at = value;
}
void HistoryMeetingMemberItem::set_astate(int value)
{
	this->_astate = value;
}
void HistoryMeetingMemberItem::set_vstate(int value)
{
	this->_vstate = value;
}

void HistoryMeetingMemberItem::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "log_id", _log_id);
		JsonUtil::GetValue(obj, "conf_id", _conf_id);
		JsonUtil::GetValue(obj, "room_id", _room_id);
		JsonUtil::GetValue(obj, "account_id", _account_id);
		JsonUtil::GetValue(obj, "account_nickname", _account_nickname);
		JsonUtil::GetValue(obj, "begin_at", _begin_at);
		JsonUtil::GetValue(obj, "state", _state);
		JsonUtil::GetValue(obj, "role", _role);
		JsonUtil::GetValue(obj, "deleted_at", _deleted_at);
		JsonUtil::GetValue(obj, "astate", _astate);
		JsonUtil::GetValue(obj, "vstate", _vstate);

		_conf.Load(obj.value("conf").toObject());
		_account.Load(obj.value("account").toObject());
	}
}
