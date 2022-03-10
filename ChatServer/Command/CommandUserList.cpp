//=================================================================================================
// @file CommandUserList.cpp
//
// @brief command class of viewing user list
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandUserList.h"
#include "Constant.h"
#include "Session.h"
#include "ChatInformation.h"
#include <string>

void OJT::ChatCommand::CommandUserList::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	auto& idMap = information.GetIdMap();
	//session.SendText( CONSTANT::TEXT::LINE );
	session.SendFormattedText(CONSTANT::FORMAT::TITLE_LINE, "이용자", " 목록");
	for ( const auto& otherSession : information.GetSessions() )
	{
		session.SendFormattedText(
			CONSTANT::FORMAT::USER_LIST,
			otherSession->GetId().c_str(),
			otherSession->GetAddress().c_str(),
			otherSession->GetPort() );
	}
	session.SendText( CONSTANT::TEXT::LINE );
	session.SendFormattedText( CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT );
}
