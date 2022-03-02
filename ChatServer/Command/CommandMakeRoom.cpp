//=================================================================================================
// @file CommandMakeRoom.cpp
//
// @brief command class of make room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandMakeRoom.h"
#include "../Constant.h"
#include "../Session.h"
#include "../ChatInformation.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandMakeRoom::Execute(const Char* argument, Session& session, ChatInformation& information)
{
	std::stringstream sstream;
	sstream.str(argument);
	Int32 maxUser = 0;
	std::string title;
	sstream >> maxUser >> title;
	if (sstream.bad())
	{
		session.SendText(CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
		session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
	}
	else
	{
		if (CONSTANT::VALUE::ROOM_MIN_USER <= maxUser && maxUser <= CONSTANT::VALUE::ROOM_MAX_USER)
		{
			ChatRoom& room = information.CreateChatRoom(maxUser, title);
			session.SendText(CONSTANT::TEXT::ROOM_CREATED);
			session.SetChatRoom(&room);
			room.EnterUser(session);
			session.SetState(SessionState::CHAT_ROOM);
		}
		else
		{
			session.SendFormattedText(
				CONSTANT::FORMAT::ALERT_ROOM_MAX_USER,
				CONSTANT::VALUE::ROOM_MIN_USER,
				CONSTANT::VALUE::ROOM_MAX_USER
			);
		}
	}
}
