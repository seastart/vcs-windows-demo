#ifndef HISTORYMEETINGLISTS_H_
#define HISTORYMEETINGLISTS_H_

#include "CJsonObject/JsonUtil.h"
#include "HistoryMeetingItem.h"

class HistoryMeetingList {

public:
	int total();
	QList<HistoryMeetingItem>& items();

	void set_total(int);
	void set_items(QList<HistoryMeetingItem>);

	void Load(QJsonObject obj);
	static void Save(QJsonObject obj);
	static HistoryMeetingList* Get();
private:
	int _total;
	QList<HistoryMeetingItem> _items;
	static HistoryMeetingList* _object;
};

#endif // HISTORYMEETINGLISTS_H_
