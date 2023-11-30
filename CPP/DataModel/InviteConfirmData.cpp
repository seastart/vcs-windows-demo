#include "InviteConfirmData.h"

InviteConfirmData::InviteConfirmData()
{

}

void InviteConfirmData::Load(QJsonObject obj)
{
    if (!obj.isEmpty())
    {
        JsonUtil::GetValue(obj, "invite_id", _invite_id);
        JsonUtil::GetValue(obj, "initiator_id", _initiator_id);
        JsonUtil::GetValue(obj, "receiver_id", _receiver_id);
        JsonUtil::GetValue(obj, "room_no", _room_no);
        JsonUtil::GetValue(obj, "response", _response);
    }
}
