//=================================================================================================
// @file CommandRoomList.cpp
//
// @brief command class of viewing room list
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandRoomList.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "ChatRoom.h"
#include "Session.h"
#include <string>

void OJT::ChatCommand::CommandRoomList::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	auto& idMap = information.GetIdMap();
	session.SendText( CONSTANT::TEXT::LINE );
	Int32 roomIndex = 1;
	for ( const auto& room : information.GetChatRooms() )
	{
		session.SendFormattedText( CONSTANT::FORMAT::ROOM_LIST,
			roomIndex,
			room->GetCurrentUserCount(),
			room->GetMaxUser(),
			room->GetTitle().c_str()
		);
		roomIndex++;
	}
	session.SendText( CONSTANT::TEXT::LINE );
}
