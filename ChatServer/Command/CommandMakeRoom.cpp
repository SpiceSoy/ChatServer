//=================================================================================================
// @file CommandMakeRoom.cpp
//
// @brief command class of make room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandMakeRoom.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "Session.h"
#include "StringUtill.h"
#include <string>

void OJT::ChatCommand::CommandMakeRoom::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	Int32 maxUser = -9999;
	std::string number;
	std::string title;
	StringUtill::SplitString( argument, number, title );
	maxUser = std::atoi( number.c_str() );
	if ( !StringUtill::ValidText( number ) || !StringUtill::ValidText( title ) )
	{
		session.SendText( CONSTANT::TEXT::ALERT_ARGUMENT_WRONG );
		session.SendFormattedText( CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT );
	}
	else
	{
		if ( CONSTANT::VALUE::ROOM_MIN_USER <= maxUser && maxUser <= CONSTANT::VALUE::ROOM_MAX_USER )
		{
			ChatRoom* currentChatRoom = session.GetChatRoom();
			if ( currentChatRoom != nullptr ) currentChatRoom->ExitUser( session );

			ChatRoom& room = information.CreateChatRoom( maxUser, title );
			session.SendText( CONSTANT::TEXT::ROOM_CREATED );
			session.SetChatRoom( &room );
			room.EnterUser( session );
			session.SetState( ESessionState::ChatRoom );
		}
		else
		{
			session.SendFormattedText(
				CONSTANT::FORMAT::ALERT_ROOM_MAX_USER,
				CONSTANT::VALUE::ROOM_MIN_USER,
				CONSTANT::VALUE::ROOM_MAX_USER
			);
		}
	}
}
