#include "RoomDataMain.h"

Room& RoomDataMain::room()
{
	return _room;
}
Conf& RoomDataMain::conf()
{
	return _conf;
}

void RoomDataMain::set_room(Room value)
{
	this->_room = value;
}
void RoomDataMain::set_conf(Conf value)
{
	this->_conf = value;
}

void RoomDataMain::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		_room.Load(obj.value("room").toObject());
		_conf.Load(obj.value("conf").toObject());
	}
}
