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
#include <set>
#include <vector>
#include <string>
namespace OJT
{
	class ChatInformation;
	class Session;
	class ChatRoom
	{
	private:
		Int32 MaxUser;
		std::set<Session*> Sessions;
		std::string Title;
		ChatInformation* const Information = nullptr;
	public:
		ChatRoom(ChatInformation* information);
		~ChatRoom() = default;

		const std::string& GetTitle() const;
		void SetTitle(const std::string& title);

		Int32 GetMaxUser() const;
		void SetMaxUser(Int32 maxUser);

		const std::set<Session*>& GetSessions() const;
		Int32 GetCurrentUserCount() const;
	public:
		void EnterUser(Session& session);
		void ExitUser(Session& session);
		void BroadCastText(const Char* text);
	};
}