#include "ProbeData.h"

void ProbeDataBase::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		_isHave = true;
		JsonUtil::GetValue(obj, "losf", _losf);
		JsonUtil::GetValue(obj, "losf2", _losf2);
		JsonUtil::GetValue(obj, "miss", _miss);
		JsonUtil::GetValue(obj, "recv", _recv);
		JsonUtil::GetValue(obj, "speed", _speed);
		JsonUtil::GetValue(obj, "status", _status);
		JsonUtil::GetValue(obj, "test_data", _test_data);
	}
}


void ProbeData::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{

		JsonUtil::GetValue(obj, "type", _type);
		JsonUtil::GetValue(obj, "delay", _delay);
		JsonUtil::GetValue(obj, "network", _network);
		JsonUtil::GetValue(obj, "probe_time", _probe_time);
		JsonUtil::GetValue(obj, "signalling", _signalling);
		JsonUtil::GetValue(obj, "stream", _stream);

		_down_data.Load(obj.value("down_data").toObject());
		_up_data.Load(obj.value("up_data").toObject());
	}
}
