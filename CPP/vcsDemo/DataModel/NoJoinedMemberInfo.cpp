#include "NoJoinedMemberInfo.h"

NoJoinedMemberInfo::NoJoinedMemberInfo()
{
	status = -1;
}



void NoJoinedMemberInfo::Load2(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "status", status);
		JsonUtil::GetValue(obj, "id", id);
		JsonUtil::GetValue(obj, "name", name);
		JsonUtil::GetValue(obj, "room_no", meetingID);
		JsonUtil::GetValue(obj, "portrait", portraitURL);
		JsonUtil::GetValue(obj, "nickname", nickName);
	}
}

void NoJoinedMemberInfo::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "iStatus", status);
		JsonUtil::GetValue(obj, "strId", id);
		JsonUtil::GetValue(obj, "strMeetingID", meetingID);
		JsonUtil::GetValue(obj, "strName", name);
		JsonUtil::GetValue(obj, "strPortraitURL", portraitURL);
		JsonUtil::GetValue(obj, "strNickName", nickName);
	}
}
