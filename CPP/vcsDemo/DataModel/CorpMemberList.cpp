#include "CorpMemberList.h"


int CorpMemberList::total()
{
	return _total;
}
QList<CorpMemberItem>& CorpMemberList::items()
{
	return _items;
}

void  CorpMemberList::set_total(int value)
{
	this->_total = value;
}
void  CorpMemberList::set_items(QList<CorpMemberItem> value)
{

	this->_items = value;
}

void CorpMemberList::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "total", _total);
		QJsonArray jsonArray = obj.value("items").toArray();
		for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			CorpMemberItem s;
			s.Load(stream);
			_items.append(s);
		}
	}
}

void CorpMemberList::Save(QJsonObject obj)
{
	_object = new CorpMemberList();
	_object->Load(obj);
}
CorpMemberList* CorpMemberList::Get()
{
	return _object;
}

CorpMemberList* CorpMemberList::_object = nullptr;
