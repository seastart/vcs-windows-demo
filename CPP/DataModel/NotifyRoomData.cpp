#include "NotifyRoomData.h"

NotifyRoomData::NotifyRoomData() :
	_astate(0),
	_sharing_type(0),
	_state(0),
	_type(0),
	_vstate(0),
	_wb(false)
{}

void NotifyRoomData::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "astate", _astate);
		JsonUtil::GetValue(obj, "id", _id);
		JsonUtil::GetValue(obj, "sdk_no", _sdk_no);
		JsonUtil::GetValue(obj, "sharing_acc_id", _sharing_acc_id);
		JsonUtil::GetValue(obj, "sharing_pic_url", _sharing_pic_url);
		JsonUtil::GetValue(obj, "sharing_sdkno", _sharing_sdkno);
		JsonUtil::GetValue(obj, "sharing_type", _sharing_type);
		JsonUtil::GetValue(obj, "state", _state);
		JsonUtil::GetValue(obj, "type", _type);
		JsonUtil::GetValue(obj, "vstate", _vstate);
		JsonUtil::GetValue(obj, "wb", _wb);
		JsonUtil::GetValue(obj, "watermark", _watermark);
		JsonUtil::GetValue(obj, "locked", _locked);
		JsonUtil::GetValue(obj, "sharing_stream_id", _sharing_stream_id);
		JsonUtil::GetValue(obj, "sharing_relative_pic_url", _sharing_relative_pic_url);

	}
}
