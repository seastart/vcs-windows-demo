#include "CorpListData.h"

int CorpListData::total()
{
	return _total;
}
QList<CorpListItem>& CorpListData::items()
{
	return _items;
}

void  CorpListData::set_total(int value)
{
	this->_total = value;
}
void  CorpListData::set_items(QList<CorpListItem> value)
{

	this->_items = value;
}

void CorpListData::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "total", _total);
		QJsonArray jsonArray = obj.value("items").toArray();
		for (QJsonArray::iterator it = jsonArray.begin(); it != jsonArray.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			CorpListItem s;
			s.Load(stream);
			_items.append(s);
		}
	}
}
