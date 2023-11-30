#ifndef INVITECONFIRMDATA_H
#define INVITECONFIRMDATA_H

#include "CJsonObject/JsonUtil.h"

class InviteConfirmData
{
public:
    InviteConfirmData();
    ~InviteConfirmData(){}

    const QString& invite_id() { return _invite_id;}
    void set_invite_id(const QString& invite_id) {
         _invite_id = invite_id;
    }

    const QString& initiator_id() { return _initiator_id;}
    void set_initiator_id(const QString& initiator_id) {
         _initiator_id = initiator_id;
    }

    const QString& room_no() { return _room_no;}
    void set_room_no(const QString& room_no) {
         _room_no = room_no;
    }

    const QString& receiver_id() { return _receiver_id;}
    void set_receiver_id(const QString& receiver_id) {
         _receiver_id = receiver_id;
    }

    const int& response() { return _response;}
    void set_response(const int& response) {
         _response = response;
    }

    void Load(QJsonObject obj);

private:
    QString _invite_id;
    QString _initiator_id;
    QString _room_no;
    QString _receiver_id;
    int _response;
};

#endif // INVITECONFIRMDATA_H
