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
#include "ChatInformation.h"
#include "NetworkUtill.h"
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
	Int32 sentBytes = send(Socket, (const char*)SendBuffer.data(), SendBytes, 0);
	if (sentBytes == SOCKET_ERROR)
	{
		NetworkUtill::PrintLastErrorMessage("send", __FILE__, __LINE__);
		Close();
	}
	else 
	{
		memcpy_s(SendBuffer.data(), SendBytes - sentBytes, SendBuffer.data() + sentBytes, SendBytes - sentBytes); //메모리 땡기기
		SendBytes -= sentBytes;
	}
}

void OJT::Session::ProcessRecive()
{
	Int32 recivedBytes = recv(Socket, ((char*)ReadBuffer.data()) + RecvBytes, sizeof(Char), 0); // 이름 겹쳐서 로컬변수 전문 작성
	Char* expectEnd = reinterpret_cast<Char*>(ReadBuffer.data() + RecvBytes);
	if (recivedBytes == 0 || recivedBytes == SOCKET_ERROR)
	{
		Close();
	}
	else 
	{
		if (expectEnd[0] == '\n')
		{
			expectEnd[0] = '\0';
			if (expectEnd != reinterpret_cast<Char*>(ReadBuffer.data())) *(expectEnd - 1) = '\0';
			OnReciveLine(reinterpret_cast<const Char*>(ReadBuffer.data()));
			RecvBytes = 0;
		}
		else
		{
			RecvBytes += recivedBytes;
			bool expectedOver = ReadBuffer.size() < RecvBytes * 1.5;
			if (expectedOver) ReadBuffer.resize(ReadBuffer.size() * 2);
		}
	}
}

void OJT::Session::SendText(const Char* message)
{
	SendByte(reinterpret_cast<const Byte*>(message), strlen(message) * sizeof(Char));
}

void OJT::Session::Close()
{
	if (Socket == 0) return;
	closesocket(this->Socket);
	if(Room != nullptr) Room->ExitUser(*this);
	State = SessionState::CLOSE;
}

const std::string& OJT::Session::GetId() const
{
	return Id;
}

const std::string& OJT::Session::GetAddress() const
{
	return AddressText;
}

UInt16 OJT::Session::GetPort() const
{
	return Port;
}

OJT::ChatRoom* OJT::Session::GetChatRoom() const
{
	return Room;
}

Bool OJT::Session::IsClosed() const
{
	return State == SessionState::CLOSE;
}

void OJT::Session::SetId(const Char* name)
{
	Id = name;
}

void OJT::Session::SetChatRoom(ChatRoom* room)
{
	Room = room;
}

void OJT::Session::SetAddress(const Char* address, UInt16 port)
{
	AddressText = address;
	Port = port;
} 

void OJT::Session::SendByte(const Byte* data, UInt64 size)
{
	if (IsClosed()) return;
	bool willOver = SendBytes + size > SendBuffer.size();
	if (willOver) SendBuffer.resize(SendBuffer.size() * 2);
	memcpy_s(SendBuffer.data() + SendBytes, size, data, size);
	SendBytes += size;
}

void OJT::Session::LogInput(const Char* input) const
{
	std::cout << AddressText << ":" << Port << "[" << Id << "] " << input << "\r\n";
}

void OJT::Session::OnStateChenge(SessionState newState)
{
	switch (newState)
	{
		case SessionState::WAIT_LOGIN: StateFunction::OnWaitLoginStateEnter(*this, *Information); break;
		case SessionState::MAIN_MENU: StateFunction::OnMainMenuStateEnter(*this, *Information); break;
		case SessionState::CHAT_ROOM: StateFunction::OnChatRoomStateEnter(*this, *Information); break;
	}
}

void OJT::Session::OnReciveLine(const Char* input)
{
	LogInput(input);
	switch (State)
	{
		case SessionState::WAIT_LOGIN: StateFunction::OnWaitLoginStateReciveLine(*this, *Information, input); break;
		case SessionState::MAIN_MENU: StateFunction::OnMainMenuStateReciveLine(*this, *Information, input); break;
		case SessionState::CHAT_ROOM: StateFunction::OnChatRoomStateReciveLine(*this, *Information, input); break;
	}
}
