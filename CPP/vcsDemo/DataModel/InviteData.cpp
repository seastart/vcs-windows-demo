#include "InviteData.h"
InviteData::InviteData()
{

}

void InviteData::Load(QJsonObject obj)
{
    if (!obj.isEmpty())
    {
        JsonUtil::GetValue(obj, "account_id", _account_id);
        JsonUtil::GetValue(obj, "invite_id", _invite_id);
        JsonUtil::GetValue(obj, "account_name", _account_name);
        JsonUtil::GetValue(obj, "room_name", _room_name);
        JsonUtil::GetValue(obj, "room_no", _room_no);
        JsonUtil::GetValue(obj, "target_id", _target_id);
        JsonUtil::GetValue(obj, "room_pwd", _room_pwd);
    }
}
