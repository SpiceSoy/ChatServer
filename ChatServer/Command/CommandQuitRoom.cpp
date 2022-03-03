//=================================================================================================
// @file CommandQuitRoom.cpp
//
// @brief command class of quit room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandQuitRoom.h"
#include "Constant.h"
#include "ChatInformation.h"
#include "ChatRoom.h"
#include "Session.h"
#include <string>

void OJT::ChatCommand::CommandQuitRoom::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	session.GetChatRoom()->ExitUser( session );
	session.SetChatRoom( nullptr );
	session.SetState( ESessionState::MainMenu );
}
