#include "RecvNetWorkStatus.h"

void RecvNetWorkStatus::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "audio", _audio);
		JsonUtil::GetValue(obj, "comp", _comp);
		JsonUtil::GetValue(obj, "losf", _losf);
		JsonUtil::GetValue(obj, "lr1", _lr1);
		JsonUtil::GetValue(obj, "lr2", _lr2);
		JsonUtil::GetValue(obj, "recv", _recv);
		JsonUtil::GetValue(obj, "sdkno", _sdkno);
		_video = _recv - _audio;
	}

}
