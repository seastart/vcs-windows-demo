#ifndef ROOMDATAMAIN_H_
#define ROOMDATAMAIN_H_

#include "CJsonObject/JsonUtil.h"
#include "Room.h"
#include "Conf.h"
class RoomDataMain {

public:
	Room& room();
	Conf& conf();

	void set_room(Room);
	void set_conf(Conf);

	void Load(QJsonObject obj);

private:
	Room _room;
	Conf _conf;
};
#endif // ROOMDATAMAIN_H_
