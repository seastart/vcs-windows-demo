QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataModel/AccountInfo.cpp \
    DataModel/CapsData.cpp \
    DataModel/ChatMsg.cpp \
    DataModel/Conf.cpp \
    DataModel/CorpListData.cpp \
    DataModel/CorpListItem.cpp \
    DataModel/CorpMemberItem.cpp \
    DataModel/CorpMemberList.cpp \
    DataModel/CorporationInfo.cpp \
    DataModel/HandUpNotify.cpp \
    DataModel/HistoryMeetingItem.cpp \
    DataModel/HistoryMeetingList.cpp \
    DataModel/HistoryMeetingMemberItem.cpp \
    DataModel/HistoryMeetingMemberList.cpp \
    DataModel/InviteConfirmData.cpp \
    DataModel/InviteData.cpp \
    DataModel/MeetingInvitationMemberItem.cpp \
    DataModel/MeetingInvitationMemberList.cpp \
    DataModel/MyMeetingList.cpp \
    DataModel/NoJoinedMemberInfo.cpp \
    DataModel/NotifyRoomData.cpp \
    DataModel/ProbeData.cpp \
    DataModel/RecvNetWorkStatus.cpp \
    DataModel/Reg.cpp \
    DataModel/RegLine.cpp \
    DataModel/Room.cpp \
    DataModel/RoomData.cpp \
    DataModel/RoomDataMain.cpp \
    DataModel/Stream.cpp \
    DataModel/StreamData.cpp \
    DataModel/UploadData.cpp \
    DataModel/UserData.cpp \
    Network/HttpNetwork.cpp \
    Network/HttpNetworkSync.cpp \
    Network/WebApiClass.cpp \
    formlogin.cpp \
    main.cpp \
    Tools/Utils.cpp \
    vcs/EnumDevice.cpp \
    vcs/RoomControl.cpp \
    vcs/VideoDevice.cpp \
    view/viewitem.cpp \
    widget.cpp

HEADERS += \
    CJsonObject/JsonUtil.h \
    DataModel/AccountInfo.h \
    DataModel/CapsData.h \
    DataModel/ChatMsg.h \
    DataModel/Conf.h \
    DataModel/CorpListData.h \
    DataModel/CorpListItem.h \
    DataModel/CorpMemberItem.h \
    DataModel/CorpMemberList.h \
    DataModel/CorporationInfo.h \
    DataModel/HandUpNotify.h \
    DataModel/HistoryMeetingItem.h \
    DataModel/HistoryMeetingList.h \
    DataModel/HistoryMeetingMemberItem.h \
    DataModel/HistoryMeetingMemberList.h \
    DataModel/InviteConfirmData.h \
    DataModel/InviteData.h \
    DataModel/MeetingInvitationMemberItem.h \
    DataModel/MeetingInvitationMemberList.h \
    DataModel/MyMeetingList.h \
    DataModel/NoJoinedMemberInfo.h \
    DataModel/NotifyRoomData.h \
    DataModel/ProbeData.h \
    DataModel/RecvNetWorkStatus.h \
    DataModel/Reg.h \
    DataModel/RegLine.h \
    DataModel/Room.h \
    DataModel/RoomData.h \
    DataModel/RoomDataMain.h \
    DataModel/Stream.h \
    DataModel/StreamData.h \
    DataModel/UploadData.h \
    DataModel/UserData.h \
    Network/HttpNetwork.h \
    Network/HttpNetworkSync.h \
    Network/WebApiClass.h \
    formlogin.h \
    Tools/Utils.h \
    vcs/EnumDevice.h \
    vcs/RoomControl.h \
    vcs/VideoDevice.h \
    view/viewitem.h \
    widget.h

FORMS += \
    formlogin.ui \
    view/viewitem.ui \
    widget.ui


LIBS += -L$$PWD//vcs/lib -lvcs
INCLUDEPATH += $$PWD/vcs/include
