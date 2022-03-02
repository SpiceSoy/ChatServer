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
#include <array>
#include <string>
namespace OJT
{
	class Session
	{
	private:
		SocketHandle Socket;
		UInt64 RecvBytes = 0;
		std::array<Byte, 512> ReadBuffer;

		UInt64 SendBufferCsr = 0;
		UInt64 SendStartCsr = 0;
		UInt64 SendBytes = 0;
		std::array<Byte, 1024> SendBuffer;

		SessionState State = SessionState::EMPTY;
		int RoomNumber = 0;
		std::string Id;
		
	public:
		Session(SocketHandle socket)
			: Socket(socket), ReadBuffer{ 0, }
		{
		};

		SocketHandle GetSocket() const;
		Bool HasSendBytes() const;

	public:
		void SetState(SessionState state);
		void ProcessSend();
		void ProcessRecive();
		void SendText(const Char* message);
	private:
		void SendByte(const Byte* data, UInt64 size);
	protected:
		void OnStateChenge(SessionState newState);
		void OnReciveLine(const Char* input);
	};
};

// TODO: 버퍼 사이즈 매크로나 constexpr 로 빼기