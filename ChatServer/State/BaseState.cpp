//=================================================================================================
// @file BaseState.cpp
//
// @brief state class for child states
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "State/BaseState.h"
OJT::State::BaseState::BaseState( const ChatCommand::CommandProcessor& processor, const ChatCommand::CommandSet& commandSet )
	: CommandProcessor( processor ), CommandSet( commandSet )
{

}

OJT::State::BaseState::BaseState( const ChatCommand::CommandProcessor& processor, ChatCommand::CommandSet&& commandSet )
	: CommandProcessor( processor ), CommandSet( std::move( commandSet ) )
{

}

void OJT::State::BaseState::OnEnter( Session& session, ChatInformation& information )
{
}

void OJT::State::BaseState::OnLineReceived( Session& session, ChatInformation& information, const Char* input )
{
	CommandProcessor.ExecuteCommand( session, information, input, this->CommandSet );
}
