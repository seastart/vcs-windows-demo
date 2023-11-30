#include "HistoryMeetingMemberList.h"


int HistoryMeetingMemberList::total()
{
	return _total;
}
QList<HistoryMeetingMemberItem>& HistoryMeetingMemberList::items()
{
	return _items;
}

void  HistoryMeetingMemberList::set_total(int value)
{
	this->_total = value;
}
void  HistoryMeetingMemberList::set_items(QList<HistoryMeetingMemberItem> value)
{

	this->_items = value;
}

void HistoryMeetingMemberList::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "total", _total);
		QJsonArray jsonArray = obj.value("items").toArray();
		for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			HistoryMeetingMemberItem s;
			s.Load(stream);
			_items.append(s);
		}
	}
}
