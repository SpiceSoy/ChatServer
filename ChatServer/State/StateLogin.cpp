//=================================================================================================
// @file StateLogin.h
//
// @brief state class of login
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================



#include "State/StateLogin.h"
#include "Session.h"
#include "Constant.h"
#include "Command/CommandSet.h"
#include "Command/CommandElement.h"

using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::StateLogin::StateLogin( const ChatCommand::CommandProcessor& processor )\
	:BaseState( processor,
		ChatCommand::CommandSet(
			ECommand::PlsLogin,
			ECommand::WrongArgument,
			{
				ChatCommand::CommandElement{	OJT::CONSTANT::COMMAND::LOGIN, true, OJT::ChatCommand::ECommand::Login },
			}
			) )
{

}

void OJT::State::StateLogin::OnEnter( Session& session, ChatInformation& information )
{
	session.SendFormattedText( CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION );
	session.SendText( CONSTANT::TEXT::PLS_LOGIN );
}
