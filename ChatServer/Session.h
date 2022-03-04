//=================================================================================================
// @file Session.h
//
// @brief class to managing user information, network
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
	namespace State
	{
		class BaseState;
	};
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

		std::string Id;
		std::string AddressText;
		UInt16 Port;

		ChatInformation* const Information = nullptr;
		ChatRoom* Room = nullptr;
		State::BaseState* State = nullptr;
	public:
		Session( SocketHandle socket, ChatInformation* information );

		SocketHandle GetSocket() const;
		Bool HasSendBytes() const;
		const std::string& GetId() const;
		const std::string& GetAddress() const;
		UInt16 GetPort() const;
		ChatRoom* GetChatRoom() const;
		Bool IsClosed() const;
	public:
		void SetState( ESessionState state );
		void ProcessSend();
		void ProcessReceive();
		void SendText( const Char* message );
		void SendFormattedText( const Char* fmt, ... );
		void Close();
		void SetId( const Char* name );
		void SetChatRoom( ChatRoom* room );
		void SetAddress( const Char* address, UInt16 port );
		void LogInput( const Char* input ) const;
	private:
		void SendByte( const Byte* data, UInt64 size );
	protected:
		void OnLineReceived( const Char* input );
	};
};