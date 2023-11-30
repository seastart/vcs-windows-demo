#ifndef CHATMSG_H_
#define CHATMSG_H_

#include "CJsonObject/JsonUtil.h"


class ChatMsg {
public:
	ChatMsg();
	~ChatMsg() {}

	const QString& account_id() { return _account_id; }
	void set_account_id(const QString& account_id) {
		_account_id = account_id;
	}

	const QString& room_id() { return _room_id; }
	void set_room_id(const QString& room_id) {
		_room_id = room_id;
	}

	const QString& account_name() { return _account_name; }
	void set_account_name(const QString& account_name) {
		_account_name = account_name;
	}

	const QString& account_portrait() { return _account_portrait; }
	void set_account_portrait(const QString& account_portrait) {
		_account_portrait = account_portrait;
	}

	const QString& target_id() { return _target_id; }
	void set_target_id(const QString& target_id) {
		_target_id = target_id;
	}

	const QString& target_name() { return _target_name; }
	void set_target_name(const QString& target_name) {
		_target_name = target_name;
	}

	const QString& message() { return _message; }
	void set_message(const QString& message) {
		_message = message;
	}

	const int& type() { return _type; }
	void set_type(const int& type) {
		_type = type;
	}

	void Load(QJsonObject obj);

private:
	QString _account_id;
	QString _room_id;
	QString _account_name;
	QString _account_portrait;
	QString _target_id;
	QString _target_name;
	QString _message;
	int _type;
}; // class ChatMsg

#endif // CHATMSG_H_
