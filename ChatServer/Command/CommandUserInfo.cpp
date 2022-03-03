//=================================================================================================
// @file CommandUserInfo.cpp
//
// @brief command class of viewing user info
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandUserInfo.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "Session.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandUserInfo::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	if ( information.HasId( argument ) )
	{
		const Session& targetSession = information.FindSession( argument );
		auto room = targetSession.GetChatRoom();
		if ( room != nullptr )
		{
			session.SendFormattedText(
				CONSTANT::FORMAT::USER_IN_ROOM,
				targetSession.GetId().c_str(),
				information.GetChatRoomIndex( *room ) + 1
			);
		}
		else
		{
			session.SendFormattedText(
				CONSTANT::FORMAT::USER_IN_MENU,
				targetSession.GetId().c_str()
			);
		}
		session.SendFormattedText( CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT );
	}
	else
	{
		session.SendText( CONSTANT::TEXT::ALERT_NO_ID_USER );
		session.SendFormattedText( CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT );
	}
}
