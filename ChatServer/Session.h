//=================================================================================================
// @file Session.h
//
// @brief 연결 정보를 관리하는 클래스입니다.
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "SessionState.h"
#include "DataTypes.h"
#include <vector>
#include <string>
#include <stdarg.h>
namespace OJT
{
	class ChatRoom;
	class ChatInformation;
	class Session
	{
	private:
		SocketHandle Socket;
		UInt64 RecvBytes = 0;
		std::vector<Byte> ReadBuffer;

		UInt64 SendBytes = 0;
		std::vector<Byte> SendBuffer;

		SessionState State = SessionState::EMPTY;
		std::string Id;

		std::string AddressText;
		UInt16 Port;
		ChatInformation * const Information = nullptr;
		ChatRoom* Room = nullptr;
	public:
		Session(SocketHandle socket, ChatInformation* information)
			: Socket(socket), Information(information)
		{
			ReadBuffer.resize(1024);
			SendBuffer.resize(1024);
		};

		SocketHandle GetSocket() const;
		Bool HasSendBytes() const;
		const std::string& GetId() const;
		const std::string& GetAddress() const;
		UInt16 GetPort() const;
		ChatRoom* GetChatRoom() const;
		Bool IsClosed() const;
	public:
		void SetState(SessionState state);
		void ProcessSend();
		void ProcessRecive();
		void SendText(const Char* message);
		void SendFormattedText(const Char* fmt, ...);
		void Close();
		void SetId(const Char* name);
		void SetChatRoom(ChatRoom* room);
		void SetAddress(const Char* address, UInt16 port);
		void LogInput(const Char* input) const;
	private:
		void SendByte(const Byte* data, UInt64 size);
	protected:
		void OnStateChenge(SessionState newState);
		void OnReciveLine(const Char* input);
	};
};

// TODO: 버퍼 사이즈 매크로나 constexpr 로 빼기