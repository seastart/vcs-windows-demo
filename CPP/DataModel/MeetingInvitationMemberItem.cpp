#include "MeetingInvitationMemberItem.h"

void MeetingInvitationMemberItem::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "role", _role);
		_account.Load(obj.value("account").toObject());
	}
}
