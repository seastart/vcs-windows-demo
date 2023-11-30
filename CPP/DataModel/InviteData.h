#ifndef INVITEDATA_H
#define INVITEDATA_H

#include "CJsonObject/JsonUtil.h"

class InviteData {
public:
    InviteData();
    ~InviteData() {}

    const QString& account_id() { return _account_id; }
    void set_account_id(const QString& account_id) {
        _account_id = account_id;
    }

    const QString& invite_id() { return _invite_id; }
    void set_invite_id(const QString& invite_id) {
        _invite_id = invite_id;
    }

    const QString& room_no() { return _room_no; }
    void set_room_no(const QString& room_no) {
        _room_no = room_no;
    }

    const QString& room_name() { return _room_name; }
    void set_room_name(const QString& room_name) {
        _room_name = room_name;
    }

    const QString& account_name() { return _account_name; }
    void set_account_name(const QString& account_name) {
        _account_name = account_name;
    }

    const QString& target_id() { return _target_id; }
    void set_target_id(const QString& target_id) {
        _target_id = target_id;
    }

    const QString& room_pwd() { return _room_pwd; }
    void set_room_pwd(const QString& room_pwd) {
        _room_pwd = room_pwd;
    }

    void Load(QJsonObject obj);

private:
    QString _account_id;
    QString _invite_id;
    QString _room_no;
    QString _account_name;
    QString _target_id;
    QString _room_name;
    QString _room_pwd;

}; // class InviteData

#endif // INVITEDATA_H
