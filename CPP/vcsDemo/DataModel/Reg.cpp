#include "Reg.h"



void Reg::set_addr(QString value)
{
	this->_addr = value;
}
void Reg::set_port(int value)
{
	this->_port = value;
}

void Reg::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "addr", _addr);
		if (_addr.isEmpty())
		{
			JsonUtil::GetValue(obj, "address", _addr);
		}
		JsonUtil::GetValue(obj, "port", _port);
		JsonUtil::GetValue(obj, "mqtt_address", _mqtt_address);
		JsonUtil::GetValue(obj, "mqtt_port", _mqtt_port);
		JsonUtil::GetValue(obj, "mqtt_tcp", _mqtt_tcp);
		JsonUtil::GetValue(obj, "mqtt_ws", _mqtt_ws);
		JsonUtil::GetValue(obj, "server_id", _server_id);
	}
}
