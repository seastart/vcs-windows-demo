#ifndef STREAMDATA_H
#define STREAMDATA_H

#include "CJsonObject/JsonUtil.h"
#include "Stream.h"

class StreamData
{
public:
	void Load(QJsonObject qdoc);

	QString address();
	int astate();
	int  delay();
	int down_lost();
	int down_rate();
	QString id();
	int mode();
	QString name();
	int net_level();
	QString nickname();
	int port();
	QString portrait();
	QString relative_portrait() { return _relative_portrait; }
	int role();
	QString shared_picture();
	int stream_id();
	QString tag();
	int terminal_type();
	int up_lost();
	int up_rate();
	int vstate();
	int hus();
	int up_level();
	QList<Stream> streams();

	void set_up_level(int);
	void set_address(QString);
	void set_astate(int);
	void set_delay(int);
	void set_down_lost(int);
	void set_down_rate(int);
	void set_id(QString);
	void set_mode(int);
	void set_name(QString);
	void set_net_level(int);
	void set_nickname(QString);
	void set_port(int);
	void set_portrait(QString);
	void set_relative_portrait(QString s) { _relative_portrait = s; }
	void set_role(int);
	void set_shared_picture(QString);
	void set_stream_id(int);
	void set_tag(QString);
	void set_terminal_type(int);
	void set_up_lost(int);
	void set_up_rate(int);
	void set_vstate(int);
	void set_hus(int);
	void set_streams(QList<Stream>);
private:
	int _up_level;
	QString _address;
	int _astate;
	int  _delay;
	int _down_lost;
	int _down_rate;
	QString _id;
	int _mode;
	QString _name;
	int _net_level;
	QString _nickname;
	int _port;
	QString _portrait;
	QString _relative_portrait;
	int _role;
	QString _shared_picture;
	int _stream_id;
	QString _tag;
	int _terminal_type;
	int _up_lost;
	int _up_rate;
	int _vstate;
	int _hus;
	QList<Stream> _streams;
};

#endif // STREAMDATA_H
