#pragma once

#include "CJsonObject/JsonUtil.h"
class RegLine
{
public:

	QString id() { return _id; }
	QString name() { return _name; }
	int type() { return _type; }

	void set_name(QString value) { this->_id = value; }
	void set_id(QString value) { this->_name = value; }
	void set_type(int value) { this->_type = value; }

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _name;
	int _type;

};
