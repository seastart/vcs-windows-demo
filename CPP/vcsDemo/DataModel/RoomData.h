#ifndef ROOMDATA_H_
#define ROOMDATA_H_

#include "CJsonObject/JsonUtil.h"
#include "Room.h"
#include "AccountInfo.h"
#include "Conf.h"
class RoomData
{
public:
	QString stream_host();
	int stream_port();
	QString stream_ws_url();
	QString wb_host();
	QString meeting_host();
	int meeting_port();
	QString meeting_ws_url();
	QString session();
	QString sdk_no();
	int role();
	QString title();
	Room& room();
	int type();
	AccountInfo& account();
	Conf& conf();
	QString& meeting_server_id() { return _meeting_server_id; }

	void set_meeting_server_id(QString v) { _meeting_server_id = v; }
	void set_stream_host(QString);
	void set_stream_port(int);
	void set_stream_ws_url(QString);
	void set_wb_host(QString);
	void set_meeting_host(QString);
	void set_meeting_port(int);
	void set_meeting_ws_url(QString);
	void set_session(QString);
	void set_sdk_no(QString);
	void set_role(int);
	void set_title(QString);
	void set_room(Room);
	void set_type(int);
	void set_account(AccountInfo);
	void set_conf(Conf);

	void Load(QJsonObject obj);
private:
	QString _stream_host;
	int _stream_port;
	QString _stream_ws_url;
	QString _wb_host;
	QString _meeting_host;
	int _meeting_port;
	QString _meeting_ws_url;
	QString _session;
	QString _sdk_no;
	int _role;
	QString _title;
	Room _room;
	int _type;
	AccountInfo _account;
	Conf _conf;
	QString _meeting_server_id;

};
#endif // ROOMDATA_H_
