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
#include "InfoManager.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

OJT::ChatServer::ChatServer()
{
	InfoManager* inst = InfoManager::GetInstance();
	inst->SetMaxSessions(MAX_SESSION_SIZE);
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
		PrintLastErrorMessageInFile("Init");
		exit(0);
	}
}

void OJT::ChatServer::CreateListenSocket()
{
	std::cout << "Create Listen Socket\n";
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		PrintLastErrorMessageInFile("CreateListen");
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
		PrintLastErrorMessageInFile("Bind");
		exit(0);
	}
}

void OJT::ChatServer::StartListen()
{
	std::cout << "Start Listen\n";
	int ret = listen(ListenSocket, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		PrintLastErrorMessageInFile("StartListen");
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

	InfoManager* info = InfoManager::GetInstance();

	for (Session& session : info->GetSessions())
	{
		FD_SET(session.GetSocket(), &read);
		if (session.HasSendBytes()) FD_SET(session.GetSocket(), &write);
	}

	int ret = select(NULL, &read, &write, NULL, NULL); // time == NULL : 무한히 기다림
	if (ret == SOCKET_ERROR) PrintLastErrorMessageInFile("Select");

	//Accept
	if (FD_ISSET(ListenSocket, &read))
	{
		SOCKET clientSocket;
		SOCKADDR_IN clientAddr;
		INT32 addrLength = sizeof(clientAddr);
		clientSocket = accept(ListenSocket, (SOCKADDR*)&clientAddr, &addrLength);
		if (clientSocket == INVALID_SOCKET) PrintLastErrorMessageInFile("Accept");
		else
		{
			char buffer[512];
			ZeroMemory(buffer, sizeof(buffer));
			const char* addrString = inet_ntop(AF_INET, (SOCKADDR*)&clientAddr.sin_addr, buffer, sizeof(buffer));

			UInt16 port = ntohs(clientAddr.sin_port);

			Session& clientSession = info->AddClientSocket(clientSocket);
			clientSession.SetAddress(addrString, port);
			clientSession.SetState(SessionState::WAIT_LOGIN);
			clientSession.LogInput("connected");
		}
	}
	//Recv
	for (Session& session : info->GetSessions())
	{
		if (!FD_ISSET(session.GetSocket(), &read)) continue;
		session.ProcessRecive();
	}
	//Send
	for (Session& session : info->GetSessions())
	{
		if (!FD_ISSET(session.GetSocket(), &write)) continue;
		session.ProcessSend();
	}
}

void OJT::ChatServer::ChangeNoneBlockingOption(SocketHandle socket, Bool isNoneBlocking)
{
	u_long on = isNoneBlocking;
	int ret = ioctlsocket(socket, FIONBIO, &on);
	if (ret == SOCKET_ERROR) PrintLastErrorMessageInFile("ioctlsocket");
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
