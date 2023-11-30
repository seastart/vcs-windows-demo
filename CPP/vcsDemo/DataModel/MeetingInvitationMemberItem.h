#pragma once

#include <QObject>
#include "CJsonObject/JsonUtil.h"
#include "AccountInfo.h"

class MeetingInvitationMemberItem {
public:

	AccountInfo& account() { return _account; }
	void set_account(const AccountInfo& account) {
		_account = account;
	}

	const int& role() { return _role; }
	void set_role(const int& role) {
		_role = role;
	}

	void Load(QJsonObject json);

private:
	AccountInfo _account;
	int _role;
}; // class Data
