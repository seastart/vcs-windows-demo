#ifndef CORPMEMBERLIST_H_
#define CORPMEMBERLIST_H_

#include "CJsonObject/JsonUtil.h"
#include "CorpMemberItem.h"
class CorpMemberList {

public:
	int total();
	QList<CorpMemberItem>& items();

	void set_total(int);
	void set_items(QList<CorpMemberItem>);

	void Load(QJsonObject obj);
	static void Save(QJsonObject obj);
	static CorpMemberList* Get();
private:
	int _total;
	QList<CorpMemberItem> _items;
	static CorpMemberList* _object;
};
#endif // CORPMEMBERLIST_H_
