//=================================================================================================
// @file CommandEnterRoom.cpp
//
// @brief command class of enter room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandEnterRoom.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "ChatRoom.h"
#include "Session.h"
#include <sstream>

void OJT::ChatCommand::CommandEnterRoom::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	// 커맨드 읽기 임시로 설정 , 이후 하나로 통일
	std::stringstream sstream; 
	sstream.str( argument );
	Int32 index = 0;
	std::string title;
	sstream >> index;
	// 1번부터 시작 보정
	index -= 1; 
	if ( sstream.bad() )
	{
		session.SendText( CONSTANT::TEXT::ALERT_ARGUMENT_WRONG );
		session.SendFormattedText( CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT );
	}
	else
	{
		if ( information.HasChatRoom( index ) )
		{
			ChatRoom& room = information.GetChatRoom( index );
			if ( room.GetCurrentUserCount() >= room.GetMaxUser() )
			{
				session.SendText( CONSTANT::TEXT::ALERT_NO_SPACE );
			}
			else
			{
				session.SendText(CONSTANT::TEXT::ROOM_ENTER);
				session.SetChatRoom( &room );
				room.EnterUser( session );
				session.SetState( ESessionState::ChatRoom );
			}
		}
		else
		{
			session.SendText( CONSTANT::TEXT::ALERT_NO_ROOM_NUM );
		}
	}
}
