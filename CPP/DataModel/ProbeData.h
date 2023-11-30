#pragma once
#include "CJsonObject/JsonUtil.h"
class ProbeDataBase
{
public:
	ProbeDataBase()
	{
		_isHave = false;
	}

	bool isHave() { return _isHave; }
	int losf() { return _losf; }
	double losf2() { return _losf2; }
	int miss() { return _miss; }
	int recv() { return _recv; }
	int speed() { return _speed; }
	int status() { return _status; }
	int test_data() { return _test_data; }

	void set_losf(int value) { this->_losf = value; }
	void set_losf2(int value) { this->_losf2 = value; }
	void set_miss(int value) { this->_miss = value; }
	void set_recv(int value) { this->_recv = value; }
	void set_speed(int value) { this->_speed = value; }
	void set_status(int value) { this->_status = value; }
	void set_test_data(int value) { this->_test_data = value; }

	void Load(QJsonObject obj);
private:
	int _losf;
	double _losf2;
	int _miss;
	int _recv;
	int _speed;
	int _status;
	int _test_data;
	bool _isHave;
};

class ProbeData
{
public:

	int type() { return _type; }
	int delay() { return _delay; }
	int network() { return _network; }
	int probe_time() { return _probe_time; }
	int signalling() { return _signalling; }
	int stream() { return _stream; }
	ProbeDataBase& down_data() { return _down_data; }
	ProbeDataBase& up_data() { return _up_data; }

	void set_type(int value) { this->_type = value; }
	void set_delay(int value) { this->_delay = value; }
	void set_network(int value) { this->_network = value; }
	void set_probe_time(int value) { this->_probe_time = value; }
	void set_signalling(int value) { this->_signalling = value; }
	void set_stream(int value) { this->_stream = value; }
	void set_down_data(ProbeDataBase value) { this->_down_data = value; }
	void set_up_data(ProbeDataBase value) { this->_up_data = value; }

	void Load(QJsonObject obj);
private:
	int _type;
	int _delay;
	int _network;
	int _probe_time;
	int _signalling;
	int _stream;
	ProbeDataBase _down_data;
	ProbeDataBase _up_data;
};
