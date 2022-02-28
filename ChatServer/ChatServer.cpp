//=================================================================================================
// @file ChatServer.cpp
//
// @brief chat server main class
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "ChatServer.h"
#include "NetworkUtill.h"
#include "Session.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

OJT::ChatServer::ChatServer()
{
	Sessions.reserve(MAX_SESSION_SIZE);
}

OJT::ChatServer::~ChatServer()
{
}

void OJT::ChatServer::Initialize(UInt16 port)
{
	ListenPort = port;
	InitializeSocket();
	CreateListenSocket();
	BindListenSocket();
}

void OJT::ChatServer::InitializeSocket()
{
	std::cout << "Initialize Socket\n";
	int ret = 0;
	WORD version = MAKEWORD(2, 2);
	WSADATA wsaData;
	ZeroMemory(&wsaData, sizeof(wsaData));
	ret = WSAStartup(version, &wsaData);
	if (ret != 0)
	{
		NetworkUtill::PrintLastErrorMessage("Init");
		exit(0);
	}
}

void OJT::ChatServer::CreateListenSocket()
{
	std::cout << "Create Listen Socket\n";
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		NetworkUtill::PrintLastErrorMessage("CreateListen");
		exit(0);
	}
}

void OJT::ChatServer::BindListenSocket()
{
	std::cout << "Bind Listen Socket\n";
	SOCKADDR_IN serverAddress;
	ZeroMemory(&serverAddress, sizeof(SOCKADDR_IN));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(ListenPort);
	int ret = bind(ListenSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));
	if (ret == SOCKET_ERROR)
	{
		NetworkUtill::PrintLastErrorMessage("Bind");
		exit(0);
	}
}

void OJT::ChatServer::StartListen()
{
	std::cout << "Start Listen\n";
	int ret = listen(ListenSocket, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		NetworkUtill::PrintLastErrorMessage("StartListen");
		exit(0);
	}
	ChangeNoneBlockingOption(ListenSocket, true);
}

void OJT::ChatServer::Select()
{
	fd_set read;
	fd_set write;
	fd_set except;
	FD_ZERO(&read);
	FD_ZERO(&write);
	FD_ZERO(&except);
	
	FD_SET(ListenSocket, &read);
	for (Session& session : Sessions)
	{
		if (session.RecvBytes > 0 || true) FD_SET(session.Socket, &read);
		if (session.SendBytes > 0) FD_SET(session.Socket, &write);
	}

	int ret = select(NULL, &read, &write, NULL, NULL); // time == NULL : 무한히 기다림
	if (ret == SOCKET_ERROR) NetworkUtill::PrintLastErrorMessage("Select");

	//Accept
	if (FD_ISSET(ListenSocket, &read))
	{
		SOCKET clientSocket;
		SOCKADDR_IN clientAddr;
		INT32 addrLength = sizeof(clientAddr);
		clientSocket = accept(ListenSocket, (SOCKADDR*)&clientAddr, &addrLength);
		if(clientSocket == INVALID_SOCKET) NetworkUtill::PrintLastErrorMessage("Accept");
		else 
		{
			char buffer[512];
			ZeroMemory(buffer, sizeof(buffer));
			const char* addrString = inet_ntop(AF_INET, (SOCKADDR*)&clientAddr.sin_addr, buffer, sizeof(buffer));
			std::cout << "Connection : IP Address = " << addrString << "\n";
			std::cout << addrString << "\n";
			Session& clientSession = AddClientSocket(clientSocket);
			//SendOption(clientSession);
			SendText(clientSession, "** 안녕하세요. 텍스트 채팅서버 ver 0.1 입니다. \r\n");
			SendText(clientSession, "** 로그인 명령어(LOGIN)를 사용해주세요.\r\n");
		}
	}
	//Recv
	for (Session& session : Sessions)
	{
		if (!FD_ISSET(session.Socket, &read)) continue;
		ret = recv(session.Socket, ((char*)session.ReadBuffer.data()) + session.RecvBytes, sizeof(Char), 0);
		Char* expectEnd = reinterpret_cast<Char*>(session.ReadBuffer.data() + session.RecvBytes);
		if (expectEnd[0] == '\n')
		{
			expectEnd[1] = 0;
			std::cout << "echo : " << (const Char*)session.ReadBuffer.data();
			session.RecvBytes = 0;
		}
		else 
		{
			session.RecvBytes += ret;
		}
	}
	//Send
	for (Session& session : Sessions)
	{
		if (!FD_ISSET(session.Socket, &write)) continue;

		Int64 currentSize = session.SendStartCsr + session.SendBytes > session.SendBuffer.size() ? session.SendBuffer.size() - session.SendStartCsr : session.SendBytes;
		ret = send(session.Socket, (const char*)session.SendBuffer.data() + session.SendStartCsr, currentSize, 0);
		session.SendStartCsr = (session.SendStartCsr + currentSize) % session.SendBuffer.size();
		session.SendBytes -= currentSize;
	}
}

OJT::Session& OJT::ChatServer::AddClientSocket(SocketHandle socket)
{
	Sessions.emplace_back(socket);
	return Sessions.back();
}

void OJT::ChatServer::SendOption(Session& session)
{
	Byte options[3] = { 255, 252, 34 };
	SendByte(session, options, 3);
}

void OJT::ChatServer::SendText(Session& session, const Char* message)
{
	SendByte(session, (Byte*)message, strlen(message) * sizeof(Char));
}

void OJT::ChatServer::SendByte(Session& session, Byte* data, UInt64 size)
{
	if (session.SendBytes == 0)
	{
		session.SendStartCsr = 0;
		session.SendBufferCsr = 0;
	}
	Int64 csrMessage = 0;
	Int64 remainSize = size;
	session.SendBytes += remainSize;
	while (remainSize != 0)
	{
		Int64 currentSendSize = 0;
		if (session.SendBufferCsr + session.SendBytes > session.SendBuffer.size()) // 버퍼 넘치면
		{
			currentSendSize = session.SendBufferCsr + session.SendBytes - session.SendBuffer.size();
		}
		else
		{
			currentSendSize = remainSize;
		}

		memcpy_s(session.SendBuffer.data() + session.SendBufferCsr, currentSendSize, data + csrMessage, currentSendSize);
		session.SendBufferCsr = (session.SendBufferCsr + currentSendSize) % session.SendBuffer.size();
		csrMessage += currentSendSize;
		remainSize -= currentSendSize;
	}
}

void OJT::ChatServer::ChangeNoneBlockingOption(SocketHandle socket, Bool isNoneBlocking)
{
	u_long on = isNoneBlocking;
	int ret = ioctlsocket(socket, FIONBIO, &on);
	if (ret == SOCKET_ERROR) NetworkUtill::PrintLastErrorMessage("ioctlsocket");
}

Int32 OJT::ChatServer::Process()
{
	std::cout << "Start Server Process\n";
	StartListen();
	while (true)
	{
		Select();
	}
	return 0;
}
