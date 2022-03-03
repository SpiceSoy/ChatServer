//=================================================================================================
// @file CommandWrongArgument.cpp
//
// @brief dummy command class of wrong argument
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandSendRoomChat.h"
#include "../Constant.h"
#include "../Session.h"
#include "../ChatRoom.h"

void OJT::ChatCommand::CommandSendRoomChat::Execute(const Char* argument, Session& session, ChatInformation& information) const
{
	ChatRoom* room = session.GetChatRoom();
	room->BroadCastFormattedText(CONSTANT::FORMAT::CHAT, session.GetId().c_str(), argument);
}
