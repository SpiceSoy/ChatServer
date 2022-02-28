//=================================================================================================
// @file ChatServer.h
//
// @brief chat server main class
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
#include "Session.h"
#include <vector>
namespace OJT
{
	class ChatServer
	{
	public:
		ChatServer();
		~ChatServer();

		void Initialize(UInt16 port);
		Int32 Process();
	private:
		UInt16 ListenPort = 0;
		SocketHandle ListenSocket = 0;
		static constexpr UInt32 MAX_SESSION_SIZE = 64;
		std::vector<Session> Sessions;
		void InitializeSocket();
		void CreateListenSocket();
		void BindListenSocket();
		void StartListen();
		void Select();
		Session& AddClientSocket(SocketHandle socket);
		void SendOption(Session& session);
		void SendText(Session& session, const Char* message);
		void SendByte(Session& session, Byte* data, UInt64 size);

		static void ChangeNoneBlockingOption(SocketHandle socket, Bool isNoneBlocking);
	};
}