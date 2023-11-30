#pragma once

#include <QObject>
#include "Conf.h"
#include "Room.h"
#include "CorporationInfo.h"
class HistoryMeetingItem
{
public:
	QString id();
	QString conf_id();
	Conf& conf();
	QString title();
	QString content();
	int begin_at();
	int end_at();
	int duration();
	int state();
	QString room_id();
	Room& room();
	QString corp_id();
	CorporationInfo corp();

	void set_id(QString);
	void set_conf_id(QString);
	void set_conf(Conf);
	void set_title(QString);
	void set_content(QString);
	void set_begin_at(int);
	void set_end_at(int);
	void set_duration(int);
	void set_state(int);
	void set_room_id(QString);
	void set_room(Room);
	void set_corp_id(QString);
	void set_corp(CorporationInfo);

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _conf_id;
	Conf _conf;
	QString _title;
	QString _content;
	int _begin_at;
	int _end_at;
	int _duration;
	int _state;
	QString _room_id;
	Room _room;
	QString _corp_id;
	CorporationInfo _corp;
};
