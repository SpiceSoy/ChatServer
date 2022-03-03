//=================================================================================================
// @file StateFunction.cpp
//
// @brief 각 상태에서 수행할 행동을 정의하는 함수 모음집입니다.
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


// TODO: 이 후 클래스로 분리 필요
// 커맨드 해석.. sstream으로 바꿀 준비
#include "StateFunction.h"
#include "SessionState.h"
#include "Session.h"
#include "ChatInformation.h"
#include "Constant.h"
#include "Command/ICommand.h"
#include "Command/Commands.h"
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <string>


//커맨드 구분을 위한 static 변수, 함수를 선언한 곳입니다.
#pragma region CommandSwitch 
static const OJT::ChatCommand::CommandEnterRoom  _commandEnterRoom;
static const OJT::ChatCommand::CommandExit		 _commandExit;
static const OJT::ChatCommand::CommandHelpInMenu _commandHelpInMenu;
static const OJT::ChatCommand::CommandHelpInRoom _commandHelpInRoom;
static const OJT::ChatCommand::CommandMakeRoom   _commandMakeRoom;
static const OJT::ChatCommand::CommandQuitRoom   _commandQuitRoom;
static const OJT::ChatCommand::CommandRoomInfo   _commandRoomInfo;
static const OJT::ChatCommand::CommandRoomList   _commandRoomList;
static const OJT::ChatCommand::CommandUserInfo   _commandUserInfo;
static const OJT::ChatCommand::CommandUserList   _commandUserList;
static const OJT::ChatCommand::CommandWhisper    _commandWhisper;
static const OJT::ChatCommand::CommandWrongArgument _commandWrongArg;
static const OJT::ChatCommand::CommandPlsCommand _commandPlsCommand;
static const OJT::ChatCommand::CommandSendRoomChat _commandSendRoomChat;
static const OJT::ChatCommand::CommandLogin _commandLogin;
static const OJT::ChatCommand::CommandPlsLogin _commandPlsLogin;

static const std::unordered_map<const Char*, const OJT::ChatCommand::ICommand*> loginCommandMap = {
	std::make_pair(OJT::CONSTANT::COMMAND::LOGIN, &_commandLogin),
	std::make_pair(OJT::CONSTANT::COMMAND::WRONG_ARGUMENT, &_commandWrongArg),
	std::make_pair(OJT::CONSTANT::COMMAND::NO_COMMAND, &_commandPlsLogin)
};

static const std::unordered_map<const Char*, const OJT::ChatCommand::ICommand*> menuCommandMap = {
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_ENTER_ROOM, &_commandEnterRoom),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_EXIT, &_commandExit),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_HELP, &_commandHelpInMenu),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_MAKE_ROOM, &_commandMakeRoom),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_ROOM_INFO, &_commandRoomInfo),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_ROOM_LIST, &_commandRoomList),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_USER_INFO, &_commandUserInfo),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_USER_LIST, &_commandUserList),
	std::make_pair(OJT::CONSTANT::COMMAND::MENU_WHISPER, &_commandWhisper),
	std::make_pair(OJT::CONSTANT::COMMAND::WRONG_ARGUMENT, &_commandWrongArg),
	std::make_pair(OJT::CONSTANT::COMMAND::NO_COMMAND, &_commandPlsCommand)
};

static const std::unordered_map<const Char*, const OJT::ChatCommand::ICommand*> chatRoomCommandMap = {
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_QUIT_ROOM, &_commandQuitRoom),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_EXIT, &_commandExit),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_HELP, &_commandHelpInMenu),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_MAKE_ROOM, &_commandMakeRoom),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_ROOM_INFO, &_commandRoomInfo),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_ROOM_LIST, &_commandRoomList),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_USER_INFO, &_commandUserInfo),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_USER_LIST, &_commandUserList),
	std::make_pair(OJT::CONSTANT::COMMAND::CHATROOM_WHISPHER, &_commandWhisper),
	std::make_pair(OJT::CONSTANT::COMMAND::WRONG_ARGUMENT, &_commandWrongArg),
	std::make_pair(OJT::CONSTANT::COMMAND::NO_COMMAND, &_commandSendRoomChat)
};

static void SplitCommand(const Char* input, const Char** command, const Char** argument)
{
	Int64 csr = 0;
	*command = input;
	while (input[csr] != 0)
	{
		if (input[csr] == ' ')
		{
			*argument = input + (csr + 1);
			return;
		}
		csr++;
	}
}

static Bool StartWith(const Char* input, const Char* command)
{
	Int64 csr = 0;
	while (input[csr] != 0 && command[csr] != 0 &&toupper(input[csr]) == toupper(command[csr])) csr++;
	return (input[csr] == ' ' || input[csr] == '\r' || input[csr] == '\n' || input[csr] == '\0') && command[csr] == '\0';
}
static Bool ValidArgument(const Char* argument)
{
	return *argument != '\0' && *argument != '\n' && *argument != ' ';
}

static std::pair<const Char*, const Char*> CommandSwitch(const Char* input, const Char* const commands[], const Char* const shouldArgument[], int commandCount)
{
	for (Int32 i = 0; i < commandCount; i++)
	{
		const Char* command = nullptr;
		const Char* argument = nullptr;
		SplitCommand(input, &command, &argument);
		if (StartWith(input, commands[i]))
		{
			if (shouldArgument[i] == OJT::CONSTANT::TEXT::TOOLTIP_ARG_NO_ARG)
			{
				return std::make_pair(commands[i], nullptr);
			}
			else
			{
				if (ValidArgument(argument))
				{
					return std::make_pair(commands[i], argument);
				}
				else
				{
					return std::make_pair(OJT::CONSTANT::COMMAND::WRONG_ARGUMENT, nullptr);
				}
			}
		}
	}
	return std::make_pair(OJT::CONSTANT::COMMAND::NO_COMMAND, input);
}

#pragma endregion

static void ExecuteCommand(
	OJT::Session& session,
	OJT::ChatInformation& info,
	const Char* input,
	const Char* const commands[],
	const Char* const shouldArgument[],
	int commandCount,
	const std::unordered_map<const Char*, const OJT::ChatCommand::ICommand*>& commandMap) //
{
	auto ret = CommandSwitch(input, commands, shouldArgument, commandCount);
	const Char* command = ret.first;
	const Char* argument = ret.second;
	commandMap.at(command)->Execute(argument, session, info);
}

void OJT::StateFunction::OnWaitLoginStateEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION);
	session.SendText(CONSTANT::TEXT::PLS_LOGIN);
}

void OJT::StateFunction::OnWaitLoginStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	ExecuteCommand(
		session,
		information,
		input,
		CONSTANT::VALUE::LOGIN_COMMANDS,
		CONSTANT::VALUE::LOGIN_ARGS,
		CONSTANT::VALUE::LOGIN_COMMAND_COUNT,
		loginCommandMap
	);
}

void OJT::StateFunction::OnMainMenuStateEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
}

void OJT::StateFunction::OnMainMenuStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	ExecuteCommand(
		session,
		information,
		input,
		CONSTANT::VALUE::MENU_COMMANDS,
		CONSTANT::VALUE::MENU_ARGS,
		CONSTANT::VALUE::MENU_COMMAND_COUNT,
		menuCommandMap
	);
}

void OJT::StateFunction::OnChatRoomStateEnter(Session& session, ChatInformation& information)
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

//어차피 Execute 밖에 안쓸거면 std::function으로 감싸는게 제일 편할수도 있다. 물어보기.
void OJT::StateFunction::OnChatRoomStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	ExecuteCommand(
		session,
		information,
		input,
		CONSTANT::VALUE::CHATROOM_COMMANDS,
		CONSTANT::VALUE::CHATROOM_ARGS,
		CONSTANT::VALUE::CHATROOM_COMMAND_COUNT,
		chatRoomCommandMap
	);
}

