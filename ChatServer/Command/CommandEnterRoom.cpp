//=================================================================================================
// @file CommandEnterRoom.cpp
//
// @brief command class of enter room
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandEnterRoom.h"
#include "../Constant.h"
#include "../Session.h"
#include "../ChatInformation.h"
#include "../ChatRoom.h"
#include <sstream>

void OJT::ChatCommand::CommandEnterRoom::Execute(const Char* argument, Session& session, ChatInformation& information) const
{
	std::stringstream sstream; // Ŀ�ǵ� �б� �ӽ÷� ���� , ���� �ϳ��� ����
	sstream.str(argument);
	Int32 index = 0;
	std::string title;
	sstream >> index;
	index -= 1; // 1������ ���� ����
	if (sstream.bad())
	{
		session.SendText(CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
		session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
	}
	else
	{
		if (information.HasChatRoom(index))
		{
			ChatRoom& room = information.GetChatRoom(index);
			if (room.GetCurrentUserCount() >= room.GetMaxUser())
			{
				session.SendText(CONSTANT::TEXT::ALERT_NO_SPACE);
			}
			else 
			{
				session.SetChatRoom(&room);
				room.EnterUser(session);
				session.SetState(SessionState::CHAT_ROOM);
			}
		}
		else
		{
			session.SendText(CONSTANT::TEXT::ALERT_NO_ROOM_NUM);
		}
	}
}
