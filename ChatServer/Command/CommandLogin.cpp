//=================================================================================================
// @file CommandWhisper.cpp
//
// @brief command class of whisper
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandLogin.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "Session.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandLogin::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	if ( information.HasId( argument ) )
	{
		session.SendText( CONSTANT::TEXT::ALREADY_LOGIN );

	}
	else
	{
		session.SetState( ESessionState::MainMenu );
		session.SetId( argument );
		information.SetId( session, argument );
		session.SendText( CONSTANT::TEXT::LINE );
		session.SendFormattedText( CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION );
		session.SendText( CONSTANT::TEXT::WRITER_INFO );
		session.SendText( CONSTANT::TEXT::LINE );
	}
}
