#include "DataModel/Stream.h"

int Stream::angle() { return _angle; }
int Stream::bitrate() { return _bitrate; }
int Stream::channel() { return _channel; }
int Stream::channel_type() { return _channel_type; }
int Stream::codec() { return _codec; }
int Stream::fps() { return _fps; }
int Stream::height() { return _height; }
int Stream::id() { return _id; }
int Stream::name() { return _name; }
int Stream::state() { return _state; }
int Stream::type() { return _type; }
int Stream::width() { return _width; }

void Stream::set_angle(int value) { this->_angle = value; }
void Stream::set_bitrate(int value) { this->_bitrate = value; }
void Stream::set_channel(int value) { this->_channel = value; }
void Stream::set_channel_type(int value) { this->_channel_type = value; }
void Stream::set_codec(int value) { this->_codec = value; }
void Stream::set_fps(int value) { this->_fps = value; }
void Stream::set_height(int value) { this->_height = value; }
void Stream::set_id(int value) { this->_id = value; }
void Stream::set_name(int value) { this->_name = value; }
void Stream::set_state(int value) { this->_state = value; }
void Stream::set_type(int value) { this->_type = value; }
void Stream::set_width(int value) { this->_width = value; }

void Stream::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "angle", _angle);
		JsonUtil::GetValue(obj, "bitrate", _bitrate);
		JsonUtil::GetValue(obj, "channel", _channel);
		JsonUtil::GetValue(obj, "channel_type", _channel_type);
		JsonUtil::GetValue(obj, "codec", _codec);
		JsonUtil::GetValue(obj, "fps", _fps);
		JsonUtil::GetValue(obj, "height", _height);
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "name", _name);
		JsonUtil::GetValue(obj, "state", _state);
		JsonUtil::GetValue(obj, "type", _type);
		JsonUtil::GetValue(obj, "width", _width);
	}
}
