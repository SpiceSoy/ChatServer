//=================================================================================================
// @file ChatInformation.h
//
// @brief class to manage Chat Info(Chat room, user list)
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
#include "Session.h"
#include "State/BaseState.h"
#include "SessionState.h"
#include "ChatRoom.h"
#include "Command/CommandProcessor.h"
#include <map>
#include <vector>
#include <list>
#include <memory>
namespace OJT
{
	class ChatInformation
	{
		std::list<std::unique_ptr<Session>> Sessions;
		std::vector<std::unique_ptr<ChatRoom>> ChatRooms;
		std::map<std::string, Session*> IdMap;
		std::vector<std::unique_ptr<State::BaseState>> States;
		ChatCommand::CommandProcessor CommandProcessor;
	public:
		ChatInformation();
		ChatInformation( const ChatInformation& ) = delete;
		ChatInformation( ChatInformation&& ) = delete;
	public:
		void SetMaxSessions( UInt32 maxSessions );
		const std::list<std::unique_ptr<Session>>& GetSessions() const;

		Bool HasChatRoom( Int32 index ) const;
		ChatRoom& GetChatRoom( Int32 index ) const;
		Int32 GetChatRoomIndex( ChatRoom& room ) const;
		const std::vector<std::unique_ptr<ChatRoom>>& GetChatRooms() const;

		void SetId( Session& session, const std::string& id );
		Bool HasId( const std::string& id ) const;

		const std::map<std::string, Session*>& GetIdMap() const;
		State::BaseState* GetState( ESessionState state ) const;

		Session& FindSession( const std::string& id ) const;

		void EraseEmptyChatRooms();
		void EraseClosedSessions();
	public:
		Session& AddClientSocket( SocketHandle socket );
		ChatRoom& CreateChatRoom( Int32 maxUser, const std::string& title );
	};
};