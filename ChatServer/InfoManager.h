//=================================================================================================
// @file InfoManager.h
//
// @brief Singletone Class of Chat Info(Chat room, user list)
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
#include "Session.h"
#include "ChatRoom.h"
#include <map>
#include <vector>
namespace OJT
{
	class InfoManager
	{
		std::vector<Session> Sessions;
		std::vector<ChatRoom> ChatRooms;
		std::map<std::string, Int32> IdMap;
	private:
		InfoManager() = default;
		InfoManager(const InfoManager&) = delete;
		InfoManager(InfoManager&&) = delete;
	public:
		void SetMaxSessions(UInt32 maxSessions);
		std::vector<Session>& GetSessions();
		Session& AddClientSocket(SocketHandle socket);
		static InfoManager* GetInstance();
		const ChatRoom& GetChatRoom(Int32 index) const;
	public:
		void CreateChatRoom(Int32 maxUser, const std::string& title);
	};
};