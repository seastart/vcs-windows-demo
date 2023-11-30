#include "HandUpNotify.h"

void HandUpNotify::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "account_id", _account_id);
		JsonUtil::GetValue(obj, "account_name", _account_name);
		JsonUtil::GetValue(obj, "hus", _hus);
		JsonUtil::GetValue(obj, "result", _result);
		JsonUtil::GetValue(obj, "room_id", _room_id);
	}
}
