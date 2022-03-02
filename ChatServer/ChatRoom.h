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
#include <map>
#include <vector>
#include <string>
#include <chrono>
namespace OJT
{
	class ChatInformation;
	class Session;
	class ChatRoom
	{
	private:
		Int32 MaxUser;
		std::set<Session*> Sessions;
		std::map<const Session*, std::chrono::system_clock::time_point> EntryTime; //sessions와 합칠까 고려하다가 세션 자체에만 접근이 필요할 것 같아 분리
		std::string Title;
		ChatInformation* const Information = nullptr;
		std::chrono::system_clock::time_point CreatedTime;
	public:
		ChatRoom(ChatInformation* information);
		~ChatRoom() = default;

		const std::string& GetTitle() const;
		void SetTitle(const std::string& title);

		Int32 GetMaxUser() const;
		void SetMaxUser(Int32 maxUser);

		const std::set<Session*>& GetSessions() const;
		std::chrono::system_clock::time_point GetEntryTime(const Session& session) const;
		std::chrono::system_clock::time_point GetCreatedTime() const;
		Int32 GetCurrentUserCount() const;
	public:
		void EnterUser(Session& session);
		void ExitUser(Session& session);
		void BroadCastText(const Char* text);
	};
}