#pragma once
#include "CJsonObject/JsonUtil.h"

class Stream
{

public:
    int angle();
    int bitrate();
    int channel();
    int channel_type();
    int codec();
    int fps();
    int height();
    int id();
    int name();
    int state();
    int type();
    int width();

    void set_angle(int value);
    void set_bitrate(int value);
    void set_channel(int value);
    void set_channel_type(int value);
    void set_codec(int value);
    void set_fps(int value);
    void set_height(int value);
    void set_id(int value);
    void set_name(int value);
    void set_state(int value);
    void set_type(int value);
    void set_width(int value);

	void Load(QJsonObject obj);
private:
	int _angle;
	int _bitrate;
	int _channel;
	int _channel_type;
	int _codec;
	int _fps;
	int _height;
	int _id;
	int _name;
	int _state;
	int _type;
	int _width;
};
class Stream;
