#include "MyMeetingList.h"

int MyMeetingList::total()
{
	return _total;
}
QList<Conf>& MyMeetingList::items()
{
	return _items;
}

void  MyMeetingList::set_total(int value)
{
	this->_total = value;
}
void  MyMeetingList::set_items(QList<Conf> value)
{

	this->_items = value;
}

void MyMeetingList::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "total", _total);
		QJsonArray jsonArray = obj.value("items").toArray();
		for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			Conf s;
			s.Load(stream);
			_items.append(s);
		}
	}
}


void MyMeetingList::Save(QJsonObject obj)
{
	_object = new MyMeetingList();
	_object->Load(obj);
}
MyMeetingList* MyMeetingList::Get()
{
	return _object;
}

MyMeetingList* MyMeetingList::_object = nullptr;
