#ifndef CORPLISTDATA_H_
#define CORPLISTATA_H_

#include "CJsonObject/JsonUtil.h"
#include "CorpListItem.h"
class CorpListData {

public:
	int total();
	QList<CorpListItem>& items();

	void set_total(int);
	void set_items(QList<CorpListItem>);

	void Load(QJsonObject obj);
private:
	int _total;
	QList<CorpListItem> _items;
};
#endif // CORPLISTDATA_H_
