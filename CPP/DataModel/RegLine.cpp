#include "RegLine.h"


void RegLine::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "name", _name);
		JsonUtil::GetValue(obj, "type", _type);
	}
}
