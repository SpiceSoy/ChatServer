//=================================================================================================
// @file ChatInformation.h
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
#include <memory>
namespace OJT
{
	class ChatInformation
	{
		std::vector<std::unique_ptr<Session>> Sessions;
		std::vector<std::unique_ptr<ChatRoom>> ChatRooms;
		std::map<std::string, Session*> IdMap;
	public:
		ChatInformation() = default;
		ChatInformation(const ChatInformation&) = delete;
		ChatInformation(ChatInformation&&) = delete;
	public:
		void SetMaxSessions(UInt32 maxSessions);
		const std::vector<std::unique_ptr<Session>>& GetSessions();
		Session& AddClientSocket(SocketHandle socket);
		const ChatRoom& GetChatRoom(Int32 index) const;
		void SetId(Session& session, const std::string& id);
		Bool HasId(const std::string& id) const;
		const std::map<std::string, Session*>& GetIdMap() const;
	public:
		ChatRoom& CreateChatRoom(Int32 maxUser, const std::string& title);
	};
};