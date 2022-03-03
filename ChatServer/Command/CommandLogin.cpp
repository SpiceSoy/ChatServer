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
#include "StringUtill.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandLogin::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	std::string id;
	std::string text;
	StringUtill::SplitString( argument, id, text );
	if ( !StringUtill::ValidText( id ) )
	{
		session.SendText( CONSTANT::TEXT::ALERT_ARGUMENT_WRONG );
	}
	else if ( StringUtill::ValidText( text ) )
	{
		session.SendText( CONSTANT::TEXT::ALERT_ID_CANT_BLACK );
	}
	else if ( information.HasId( id ) )
	{
		session.SendText( CONSTANT::TEXT::ALREADY_LOGIN );
	}
	else
	{
		session.SetState( ESessionState::MainMenu );
		session.SetId( id.c_str() );
		information.SetId( session, id.c_str() );
		session.SendText( CONSTANT::TEXT::LINE );
		session.SendFormattedText( CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION );
		session.SendText( CONSTANT::TEXT::WRITER_INFO );
		session.SendText( CONSTANT::TEXT::LINE );
	}
}
