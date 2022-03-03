//=================================================================================================
// @file StateChatRoom.h
//
// @brief state class of chatting room
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "State/StateChatRoom.h"
#include "ChatRoom.h"
#include "Constant.h"
#include "Command/CommandSet.h"
#include "Command/CommandElement.h"
#include "Session.h"


using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::StateChatRoom::StateChatRoom( const ChatCommand::CommandProcessor& processor )
	:BaseState( processor,
		ChatCommand::CommandSet(
			ECommand::SendRoomChat,
			ECommand::WrongArgument,
			{
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_QUIT_ROOM,	false,	OJT::ChatCommand::ECommand::QuitRoom	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_EXIT,			false,	OJT::ChatCommand::ECommand::Exit		},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_HELP,			false,	OJT::ChatCommand::ECommand::HelpInRoom	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_MAKE_ROOM,	true,	OJT::ChatCommand::ECommand::MakeRoom	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_ROOM_INFO,	false,	OJT::ChatCommand::ECommand::RoomInfo	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_ROOM_LIST,	false,	OJT::ChatCommand::ECommand::RoomList	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_USER_INFO,	true,	OJT::ChatCommand::ECommand::UserInfo	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_USER_LIST,	false,	OJT::ChatCommand::ECommand::UserList	},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_WHISPHER,		true,	OJT::ChatCommand::ECommand::Whisper		},
				ChatCommand::CommandElement{ OJT::CONSTANT::COMMAND::CHATROOM_INVITE_ROOM,	true,	OJT::ChatCommand::ECommand::InviteRoom	},
			}
			) )
{
}

void OJT::State::StateChatRoom::OnEnter( Session& session, ChatInformation& information )
{
	ChatRoom* room = session.GetChatRoom();
	if ( room == nullptr )
	{
		session.SetState( ESessionState::MainMenu );
		return;
	}
	room->BroadCastFormattedText(
		OJT::CONSTANT::FORMAT::USER_ENTER_ROOM,
		session.GetId().c_str(),
		room->GetCurrentUserCount(),
		room->GetMaxUser()
	);
}
