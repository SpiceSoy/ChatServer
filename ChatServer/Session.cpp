//=================================================================================================
// @file Session.cpp
//
// @brief session info struct
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Session.h"
#include "StateFunction.h"
#include <WinSock2.h>
#include <iostream>

SocketHandle OJT::Session::GetSocket() const
{
	return Socket;
}

Bool OJT::Session::HasSendBytes() const
{
	return SendBytes;
}

void OJT::Session::SetState(SessionState state)
{
	State = state;
	OnStateChenge(State);
}

void OJT::Session::ProcessSend()
{
	Int64 currentSize = SendStartCsr + SendBytes > SendBuffer.size() ? SendBuffer.size() - SendStartCsr : SendBytes;
	Int32 ret = send(Socket, (const char*)SendBuffer.data() + SendStartCsr, currentSize, 0);
	SendStartCsr = (SendStartCsr + currentSize) % SendBuffer.size();
	SendBytes -= currentSize;
}

void OJT::Session::ProcessRecive()
{
	Int32 ret = recv(Socket, ((char*)ReadBuffer.data()) + RecvBytes, sizeof(Char), 0);
	Char* expectEnd = reinterpret_cast<Char*>(ReadBuffer.data() + RecvBytes);
	if (expectEnd[0] == '\n')
	{
		expectEnd[1] = 0;
		OnReciveLine(reinterpret_cast<const Char*>(ReadBuffer.data()));
		RecvBytes = 0;
	}
	else
	{
		RecvBytes += ret;
	}
}

void OJT::Session::SendText(const Char* message)
{
	SendByte(reinterpret_cast<const Byte*>(message), strlen(message) * sizeof(Char));
}

void OJT::Session::Close()
{
	if(Socket != 0) closesocket(this->Socket);
	State = SessionState::CLOSE;
}

void OJT::Session::SendByte(const Byte* data, UInt64 size)
{
	if (SendBytes == 0)
	{
		SendStartCsr = 0;
		SendBufferCsr = 0;
	}
	Int64 csrMessage = 0;
	Int64 remainSize = size;
	SendBytes += remainSize;
	while (remainSize != 0)
	{
		Int64 currentSendSize = 0;
		if (SendBufferCsr + SendBytes > SendBuffer.size()) // ���� ��ġ��
		{
			currentSendSize = SendBufferCsr + SendBytes - SendBuffer.size();
		}
		else
		{
			currentSendSize = remainSize;
		}

		memcpy_s(SendBuffer.data() + SendBufferCsr, currentSendSize, data + csrMessage, currentSendSize);
		SendBufferCsr = (SendBufferCsr + currentSendSize) % SendBuffer.size();
		csrMessage += currentSendSize;
		remainSize -= currentSendSize;
	}
}

void OJT::Session::OnStateChenge(SessionState newState)
{
	switch (newState)
	{
		case SessionState::WAIT_LOGIN: StateFunction::OnWaitLoginStateEnter(*this); break;
		case SessionState::MAIN_MENU: StateFunction::OnMainMenuStateEnter(*this); break;
		case SessionState::CHAT_ROOM: StateFunction::OnChatRoomStateEnter(*this); break;
	}
}

void OJT::Session::OnReciveLine(const Char* input)
{
	switch (State)
	{
		case SessionState::WAIT_LOGIN: StateFunction::OnWaitLoginStateReciveLine(*this, input); break;
		case SessionState::MAIN_MENU: StateFunction::OnMainMenuStateReciveLine(*this, input); break;
		case SessionState::CHAT_ROOM: StateFunction::OnChatRoomStateReciveLine(*this, input); break;
	}
}