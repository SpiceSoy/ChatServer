//=================================================================================================
// @file CommandWrongArgument.cpp
//
// @brief dummy command class of wrong argument
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandPlsCommand.h"
#include "Constant.h"
#include "Session.h"

void OJT::ChatCommand::CommandPlsCommand::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	session.SendText( OJT::CONSTANT::TEXT::ALERT_PLS_COMMAND );
	session.SendFormattedText( OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT );
}
