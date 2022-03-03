
#include "MenuState.h"
#include "../Session.h"
#include "../Constant.h"
#include "../Command/CommandSet.h"
#include "../Command/CommandElement.h"

using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::MenuState::MenuState(const ChatCommand::CommandProcessor& processor)
	:BaseState(processor, 
		ChatCommand::CommandSet(
			ECommand::PlsCommand, 
			ECommand::WrongArgument, 
			{
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_ENTER_ROOM, true,	OJT::ChatCommand::ECommand::EnterRoom},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_EXIT,		false,	OJT::ChatCommand::ECommand::Exit},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_HELP,		false,	OJT::ChatCommand::ECommand::HelpInMenu},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_MAKE_ROOM, true,	OJT::ChatCommand::ECommand::MakeRoom},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_ROOM_INFO, true,	OJT::ChatCommand::ECommand::RoomInfo},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_ROOM_LIST, false,	OJT::ChatCommand::ECommand::RoomList},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_USER_INFO, true,	OJT::ChatCommand::ECommand::UserInfo},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_USER_LIST, false,	OJT::ChatCommand::ECommand::UserList},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_WHISPER,	true,	OJT::ChatCommand::ECommand::Whisper},
			}
		))
{
}
void OJT::State::MenuState::OnEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
}
