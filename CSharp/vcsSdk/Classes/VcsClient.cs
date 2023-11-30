using System;
using System.Collections.Generic;
using System.Net;
using System.Text;
using vcsSdk.Sdk;

namespace vcsSdk.Classes
{
    public class VcsClient
    {
        public IntPtr Handle { get; private set; }

        public string AccountId { get; }
        public string Token { get; }
        public IPEndPoint EndPoint { get;}
        private VcsNative.RoomEvent RoomEvent;

        public VcsClient(string accId,string token,IPEndPoint endpoint,VcsNative.RoomEvent roomEvent)
        {
            AccountId = accId;
            Token = token;
            EndPoint = endpoint;
            RoomEvent = roomEvent;

            Handle=VcsNative.VCS_CreateClient(AccountId, Token, EndPoint.Address.ToString(), EndPoint.Port, this.RoomEvent, IntPtr.Zero);
        }

        public void Open()
        {
            VcsNative.VCS_Open(Handle);
        }

        public void Close()
        {
            if (Handle != IntPtr.Zero)
            {
                VcsNative.VCS_Close(Handle);
                Handle = IntPtr.Zero;
            }
        }

        public void Invite(string tarId,string roomNo)
        {
            VcsNative.VCS_Invite(Handle, tarId, roomNo);
        }

        public void InviteConfirm(string id,string initiatorId,string roomNo,int resp)
        {
            VcsNative.VCS_InviteConfirm(Handle, id, initiatorId, roomNo, resp);
        }
    }
}

