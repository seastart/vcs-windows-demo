#include "ChatMsg.h"

ChatMsg::ChatMsg()
{
	_type = 0;
}

void ChatMsg::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "account_id", _account_id);
		JsonUtil::GetValue(obj, "room_id", _room_id);
		JsonUtil::GetValue(obj, "account_name", _account_name);
		JsonUtil::GetValue(obj, "account_portrait", _account_portrait);
		JsonUtil::GetValue(obj, "target_id", _target_id);
		JsonUtil::GetValue(obj, "message", _message);
		JsonUtil::GetValue(obj, "type", _type);
	}
}
