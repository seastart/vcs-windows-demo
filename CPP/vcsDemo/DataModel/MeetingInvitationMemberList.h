#ifndef MEETINGINVITATIONMEMBERLIST_H_
#define MEETINGINVITATIONMEMBERLIST_H_

#include "CJsonObject/JsonUtil.h"
#include "MeetingInvitationMemberItem.h"

class MeetingInvitationMemberList {
public:

	const int& code() { return _code; }
	void set_code(const int& code) {
		_code = code;
	}

	const QList<MeetingInvitationMemberItem>& data() { return _data; }
	void set_data(const QList<MeetingInvitationMemberItem>& data) {
		_data = data;
	}

	void Load(QJsonObject obj);
private:
	int _code;
	QList<MeetingInvitationMemberItem> _data;
};

#endif // MEETINGINVITATIONMEMBERLIST_H_
