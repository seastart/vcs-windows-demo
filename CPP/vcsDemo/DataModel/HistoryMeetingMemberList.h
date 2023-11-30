#ifndef HISTORYMEETINGMEMBERLIST_H_
#define HISTORYMEETINGMEMBERLIST_H_

#include "CJsonObject/JsonUtil.h"
#include "HistoryMeetingMemberItem.h"
class HistoryMeetingMemberList {

public:
	int total();
	QList<HistoryMeetingMemberItem>& items();

	void set_total(int);
	void set_items(QList<HistoryMeetingMemberItem>);

	void Load(QJsonObject obj);
private:
	int _total;
	QList<HistoryMeetingMemberItem> _items;
};

#endif // HISTORYMEETINGMEMBERLIST_H_
