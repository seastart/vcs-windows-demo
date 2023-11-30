#pragma once

#include "CJsonObject/JsonUtil.h"
#include "Room.h"
class AccountInfo
{
public:
	QString id();
	QString name();
	QString nickname();
	int type();
	QString portrait();
	QString mobile();
	int created_at();
	int updated_at();
	int state();
	QString room_id();
	Room& room();
	QString corp_nickname();
	int corp_role();
	QString corp_id();
	QString corp_name();
	int fs_used_size();
	int reg_from();

	QString relative_portrait() { return _relative_portrait; }
	void set_relative_portrait(QString v) { _relative_portrait = v; }

	void set_id(QString Value);
	void set_name(QString Value);
	void set_nickname(QString Value);
	void set_type(int Value);
	void set_portrait(QString Value);
	void set_mobile(QString Value);
	void set_created_at(int Value);
	void set_updated_at(int Value);
	void set_state(int Value);
	void set_room_id(QString Value);
	void set_room(Room Value);
	void set_corp_nickname(QString Value);
	void set_corp_role(int Value);
	void set_corp_id(QString Value);
	void set_corp_name(QString Value);
	void set_fs_used_size(int Value);
	void set_reg_from(int Value);

	void Load(QJsonObject obj);
private:
	QString _id;
	QString _name;
	QString _nickname;
	int _type;
	QString _portrait;
	QString _mobile;
	int _created_at;
	int _updated_at;
	int _state;
	QString _room_id;
	Room _room;
	QString _corp_nickname;
	int _corp_role;
	QString _corp_id;
	QString _corp_name;
	int _fs_used_size;
	int _reg_from;
	QString _relative_portrait;
};
