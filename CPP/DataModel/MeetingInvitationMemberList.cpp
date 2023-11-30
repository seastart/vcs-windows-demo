#include "MeetingInvitationMemberList.h"

void MeetingInvitationMemberList::Load(QJsonObject obj)
{
	if (!obj.isEmpty())
	{
		JsonUtil::GetValue(obj, "code", _code);

		QJsonArray ss = obj.value("data").toArray();
		for (QJsonArray::iterator it = ss.begin(); it != ss.end(); ++it)
		{
			QJsonObject stream = (*it).toObject();
			MeetingInvitationMemberItem s;
			s.Load(stream);
			_data.append(s);
		}
	}
}
