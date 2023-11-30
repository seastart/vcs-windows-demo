#ifndef MYMEETINGLIST_H_
#define MYMEETINGLIST_H_

#include "CJsonObject/JsonUtil.h"
#include "DataModel/Conf.h"

class MyMeetingList {

public:
	int total();
	QList<Conf>& items();

	void set_total(int);
	void set_items(QList<Conf>);

	void Load(QJsonObject obj);

	static void Save(QJsonObject obj);
	static MyMeetingList* Get();
private:
	int _total;
	QList<Conf> _items;

	static MyMeetingList* _object;
};
#endif // MYMEETINGLIST_H_
