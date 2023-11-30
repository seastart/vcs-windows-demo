#pragma once
#include "CJsonObject/JsonUtil.h"
class Room
{
public:
	QString id();
	QString no();
	QString sdk_no();
	bool access_pwd();
	bool access_whitelist();
	QString password();
	int limited();
	int max_video();
	int samplerate();
	int ol_count();
	int state();

	void set_id(QString);
	void set_no(QString);
	void set_sdk_no(QString);
	void set_access_pwd(bool);
	void set_access_whitelist(bool);
	void set_password(QString);
	void set_limited(int);
	void set_max_video(int);
	void set_samplerate(int);
	void set_ol_count(int);
	void set_state(int);

	void Load(QJsonObject obj);

private:
	QString _id;
	QString _no;
	QString _sdk_no;
	bool _access_pwd;
	bool _access_whitelist;
	QString _password;
	int _limited;
	int _max_video;
	int _samplerate;
	int _ol_count;
	int _state;
};
