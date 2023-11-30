#ifndef HANDUPNOTIFY_H
#define HANDUPNOTIFY_H

#include "../CJsonObject/JsonUtil.h"
class HandUpNotify
{
public:
	QString account_id() { return _account_id; }
	QString account_name() { return _account_name; }
	int hus() { return _hus; }
	int result() { return _result; }
	QString room_id() { return _room_id; }

	void account_id(QString v) { _account_id = v; }
	void account_name(QString v) { _account_name = v; }
	void hus(int v) { _hus = v; }
	void result(int v) { _result = v; }
	void room_id(QString v) { _room_id = v; }

	void Load(QJsonObject obj);
private:
	QString _account_id;
	QString _account_name;
	int _hus;
	int _result;
	QString _room_id;
};

#endif // HANDUPNOTIFY_H
