//=================================================================================================
// @file CommandRoomList.cpp
//
// @brief command class of viewing room list
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandInviteRoom.h"
#include "../Constant.h"
#include "../ChatInformation.h"
#include "../ChatRoom.h"
#include "../Session.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandInviteRoom::Execute(const Char* argument, Session& session, ChatInformation& information) const
{
	std::stringstream sstream;
	sstream.str(argument);
	std::string id;
	sstream >> id;
	if (sstream.bad())
	{
		session.SendText(CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
		session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
	}
	else if (information.HasId(id))
	{
		sstream.clear();
		Session& targetSession = information.FindSession(id);
		ChatRoom* room = session.GetChatRoom();
		if (room)
		{
			Int32 index = information.GetChatRoomIndex(*room);
			targetSession.SendFormattedText(CONSTANT::FORMAT::INVITE_ROOM, session.GetId().c_str(), index + 1);
		}
		else 
		{
			session.SendText(CONSTANT::TEXT::ALERT_NO_IN_ROOM);
		}
	}
	else
	{
		session.SendText(CONSTANT::TEXT::ALERT_NO_ID_USER);
	}
}
