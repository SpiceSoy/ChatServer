//=================================================================================================
// @file CommandSendRoomChat.cpp
//
// @brief command class to send chat to room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandSendRoomChat.h"
#include "Constant.h"
#include "ChatRoom.h"
#include "Session.h"

void OJT::ChatCommand::CommandSendRoomChat::Execute( const Char* argument, Session& session, ChatInformation& information ) const
{
	ChatRoom* room = session.GetChatRoom();
	room->BroadCastFormattedText( CONSTANT::FORMAT::CHAT, session.GetId().c_str(), argument );
}
