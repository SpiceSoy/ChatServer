//=================================================================================================
// @file CommandHelpInRoom.cpp
//
// @brief command class of help in room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandHelpInRoom.h"
#include "../Constant.h"
#include "../Session.h"

void OJT::ChatCommand::CommandHelpInRoom::Execute(const Char* argument, Session& session, ChatInformation& information)
{
	session.SendText(CONSTANT::TEXT::LINE);
	for (Int32 i = 0; i < CONSTANT::VALUE::CHATROOM_COMMAND_COUNT; i++)
	{
		session.SendFormattedText(CONSTANT::FORMAT::TOOLTIP,
			CONSTANT::VALUE::CHATROOM_COMMANDS[i],
			CONSTANT::VALUE::CHATROOM_ARGS[i],
			CONSTANT::VALUE::CHATROOM_TOOLTIP[i]
		);
	}
	session.SendText(CONSTANT::TEXT::LINE);
	session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
}
