#pragma once

#include <QObject>
#include "CJsonObject/JsonUtil.h"

class Reg
{
public:

	void set_addr(QString value);
	void set_port(int value);
	void set_mqtt_address(QString value) { _mqtt_address = value; }
	void set_mqtt_ws(QString value) { _mqtt_ws = value; }
	void set_mqtt_tcp(QString value) { _mqtt_tcp = value; }
	void set_mqtt_port(int value) { _mqtt_port = value; }
	void set_server_id(QString value) { _server_id = value; }

	QString server_id() { return _server_id; }
	QString addr() { return _addr; }
	int port() { return _port; }
	QString mqtt_address() { return _mqtt_address; }
	QString mqtt_ws() { return _mqtt_ws; }
	QString mqtt_tcp() { return _mqtt_tcp; }
	int mqtt_port() { return _mqtt_port; }
	void Load(QJsonObject obj);
private:
	QString _server_id;
	QString _addr;
	QString _mqtt_address;
	QString _mqtt_tcp;
	QString _mqtt_ws;
	int _mqtt_port;
	int _port;
};
