//=================================================================================================
// @file StateEmpty.cpp
//
// @brief dummy State class of close, end
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "State/StateEmpty.h"
#include "Constant.h"
#include "Command/CommandSet.h"
#include "Command/CommandElement.h"
#include "Session.h"

using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::StateEmpty::StateEmpty( const ChatCommand::CommandProcessor& processor )
	:BaseState( processor,
		ChatCommand::CommandSet(
			ECommand::PlsCommand,
			ECommand::WrongArgument,
			{
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_EXIT,		false,	OJT::ChatCommand::ECommand::Exit},
			}
			) )
{
}
void OJT::State::StateEmpty::OnEnter( Session& session, ChatInformation& information )
{
	session.SendFormattedText( CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT );
}
