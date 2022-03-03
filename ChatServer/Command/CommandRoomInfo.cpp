//=================================================================================================
// @file CommandRoomInfo.cpp
//
// @brief command class of viewing room info
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandRoomInfo.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "ChatRoom.h"
#include "Session.h"
#include <sstream>
#include <string>


void OJT::ChatCommand::CommandRoomInfo::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	std::stringstream sstream; //임시로 사용
	constexpr Int32 NOT_IN_ROOM = -1;
	Int32 roomIndex = NOT_IN_ROOM;
	ChatRoom* targetRoom = nullptr;

	if ( argument ) sstream.str( argument );
	sstream >> roomIndex;
	roomIndex -= 1;

	if ( sstream.bad() || !argument )
	{
		targetRoom = session.GetChatRoom();
		if ( targetRoom != nullptr ) roomIndex = information.GetChatRoomIndex( *targetRoom );
	}
	else
	{
		if( information.HasChatRoom(roomIndex) ) targetRoom = &information.GetChatRoom( roomIndex );
	}
	if ( targetRoom != nullptr && information.HasChatRoom( roomIndex ) )
	{
		session.SendText( CONSTANT::TEXT::LINE );
		session.SendFormattedText( CONSTANT::FORMAT::ROOM_LIST,
			roomIndex + 1,
			targetRoom->GetCurrentUserCount(),
			targetRoom->GetMaxUser(),
			targetRoom->GetTitle().c_str()
		);
		std::time_t createTime = std::chrono::system_clock::to_time_t( targetRoom->GetCreatedTime() );
		std::tm createTm;
		localtime_s( &createTm, &createTime );
		session.SendFormattedText( CONSTANT::FORMAT::ROOM_CREATE_TIME, createTm.tm_hour, createTm.tm_min, createTm.tm_sec );
		for ( const auto& member : targetRoom->GetSessions() )
		{
			std::time_t entryTime = std::chrono::system_clock::to_time_t( targetRoom->GetCreatedTime() );
			std::tm entryTm;
			localtime_s( &entryTm, &entryTime );
			session.SendFormattedText( CONSTANT::FORMAT::ROOM_ENTRY_USERS, member->GetId().c_str(), createTm.tm_hour, createTm.tm_min, createTm.tm_sec );
		}
		session.SendText( sstream.str().c_str() );
		session.SendText( CONSTANT::TEXT::LINE );
	}
	else
	{
		session.SendText( CONSTANT::TEXT::ALERT_NO_ROOM_NUM );
	}
}
