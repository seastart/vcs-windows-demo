#include "HistoryMeetingList.h"

int HistoryMeetingList::total()
{
	return _total;
}
QList<HistoryMeetingItem>& HistoryMeetingList::items()
{
	return _items;
}

void  HistoryMeetingList::set_total(int value)
{
	this->_total = value;
}
void  HistoryMeetingList::set_items(QList<HistoryMeetingItem> value)
{

	this->_items = value;
}

void HistoryMeetingList::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "total", _total);
		QJsonArray jsonArray = obj.value("items").toArray();
		for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			HistoryMeetingItem s;
			s.Load(stream);
			_items.append(s);
		}
	}
}

void HistoryMeetingList::Save(QJsonObject obj)
{
	_object = new HistoryMeetingList();
	_object->Load(obj);
}
HistoryMeetingList* HistoryMeetingList::Get()
{
	return _object;
}

HistoryMeetingList* HistoryMeetingList::_object = nullptr;
