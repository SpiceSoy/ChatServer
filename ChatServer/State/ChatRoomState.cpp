#include "ChatRoomState.h"
#include "../ChatRoom.h"
#include "../Session.h"
#include "../Constant.h"
#include "../Command/CommandSet.h"
#include "../Command/CommandElement.h"


using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::ChatRoomState::ChatRoomState(const ChatCommand::CommandProcessor& processor)
	:BaseState(processor,
		ChatCommand::CommandSet(
			ECommand::SendRoomChat,
			ECommand::WrongArgument,
			{
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_QUIT_ROOM, false,	OJT::ChatCommand::ECommand::QuitRoom},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_EXIT,		false,	OJT::ChatCommand::ECommand::Exit},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_HELP,		false,	OJT::ChatCommand::ECommand::HelpInRoom},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_MAKE_ROOM, true,	OJT::ChatCommand::ECommand::MakeRoom},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_ROOM_INFO, false,	OJT::ChatCommand::ECommand::RoomInfo},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_ROOM_LIST, false,	OJT::ChatCommand::ECommand::RoomList},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_USER_INFO, true,	OJT::ChatCommand::ECommand::UserInfo},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_USER_LIST, false,	OJT::ChatCommand::ECommand::UserList},
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::CHATROOM_WHISPHER,	true,	OJT::ChatCommand::ECommand::Whisper},
			}
			))
{
}

void OJT::State::ChatRoomState::OnEnter(Session& session, ChatInformation& information)
{
	ChatRoom* room = session.GetChatRoom();
	if (room == nullptr)
	{
		session.SetState(SessionState::MAIN_MENU);
		return;
	}
	room->BroadCastFormattedText(
		OJT::CONSTANT::FORMAT::USER_ENTER_ROOM,
		session.GetId().c_str(),
		room->GetCurrentUserCount(),
		room->GetMaxUser()
	);
}
