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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#define ARRAYSIZE(A) sizeof(A) / sizeof((A)[0])

constexpr UInt64 commandBufferSize = 50;
constexpr UInt64 chatBufferSize = 1024;
constexpr UInt32 userWidth = 30;

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

void OJT::StateFunction::OnWaitLoginStateEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION);
	session.SendText(CONSTANT::TEXT::PLS_LOGIN);
}

void OJT::StateFunction::OnWaitLoginStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	const Char* command = nullptr;
	const Char* argument = nullptr;
	SplitCommand(input, &command, &argument);
	if (StartWith(command, CONSTANT::COMMAND::LOGIN) && ValidArgument(argument) )
	{
		if (!information.HasId(argument))
		{
			session.SetState(SessionState::MAIN_MENU);
			session.SetId(argument);
			information.SetId(session, argument);
			session.SendText(CONSTANT::TEXT::LINE);
			session.SendFormattedText(CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION);
			session.SendText(CONSTANT::TEXT::WRITER_INFO);
			session.SendText(CONSTANT::TEXT::LINE);
		} 
		else 
		{
			session.SendText(CONSTANT::TEXT::ALREADY_LOGIN);
		}

	}
	else
	{
		session.SendText(CONSTANT::TEXT::PLS_LOGIN);
	}
}

void OJT::StateFunction::OnMainMenuStateEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
}

// return 
// first : commandIndex -1 = UNCOMMNAD -2 = NO_ARGUMENT
// second : argument Ptr
static constexpr Int32 COMMAND_SWITCH_UNCOMMAND = -1;
static constexpr Int32 COMMAND_SWITCH_NO_ARGUMENT = -2;
static std::pair<Int32, const Char*> CommandSwitch(const Char* input, const Char* const commands[], const bool shouldArgument[], int commandCount)
{
	for (Int32 i = 0; i < commandCount; i++)
	{
		const Char* command = nullptr;
		const Char* argument = nullptr;
		SplitCommand(input, &command, &argument);
		if (StartWith(input, commands[i]))
		{
			if (shouldArgument[i])
			{
				if (ValidArgument(argument))
				{
					return std::make_pair(i, argument);
				}
				else
				{
					return std::make_pair(COMMAND_SWITCH_NO_ARGUMENT, nullptr);
				}
			}
			else
			{
				return std::make_pair(i, nullptr);
			}
		}
	}
	return std::make_pair(COMMAND_SWITCH_UNCOMMAND, nullptr);
}

static constexpr Int32 COMMAND_SWITCH_H = 0;
static constexpr Int32 COMMAND_SWITCH_US = 1;
static constexpr Int32 COMMAND_SWITCH_LT = 2;
static constexpr Int32 COMMAND_SWITCH_ST = 3;
static constexpr Int32 COMMAND_SWITCH_PF = 4;
static constexpr Int32 COMMAND_SWITCH_TO = 5;
static constexpr Int32 COMMAND_SWITCH_O = 6;
static constexpr Int32 COMMAND_SWITCH_J_Q = 7;
static constexpr Int32 COMMAND_SWITCH_X = 8;
static Void SendCommandHelp(OJT::Session& session , bool inRoom)
{
	session.SendText(OJT::CONSTANT::TEXT::LINE);
	if (inRoom)
	{
		for (Int32 i = 0; i < ARRAYSIZE(OJT::CONSTANT::VALUE::CHATROOM_COMMANDS); i++)
		{
			session.SendFormattedText(OJT::CONSTANT::FORMAT::TOOLTIP,
				OJT::CONSTANT::VALUE::CHATROOM_COMMANDS[i],
				OJT::CONSTANT::VALUE::CHATROOM_ARGS[i],
				OJT::CONSTANT::VALUE::CHATROOM_TOOLTIP[i]
			);
		}
	}
	else 
	{
		for (Int32 i = 0; i < ARRAYSIZE(OJT::CONSTANT::VALUE::MENU_COMMANDS); i++)
		{
			session.SendFormattedText(OJT::CONSTANT::FORMAT::TOOLTIP,
				OJT::CONSTANT::VALUE::MENU_COMMANDS[i],
				OJT::CONSTANT::VALUE::MENU_ARGS[i],
				OJT::CONSTANT::VALUE::MENU_TOOLTIP[i]
			);
		}
	}
	session.SendText(OJT::CONSTANT::TEXT::LINE);
	session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
}

static Void CommandLogic(OJT::Session& session, OJT::ChatInformation& information, const Char* input, const Char* argument, Int32 commandIndex, bool inRoom) //TODO: 리팩토링 예정
{
	using namespace OJT;
	switch (commandIndex)
	{
	case COMMAND_SWITCH_NO_ARGUMENT:
	{
		session.SendText(OJT::CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
		session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
	}
	break;
	case COMMAND_SWITCH_H:
	{
		SendCommandHelp(session, inRoom);
	}
	break;
	case COMMAND_SWITCH_US:
	{
		std::stringstream sstream; //임시로 사용
		auto& idMap = information.GetIdMap();
		session.SendText(OJT::CONSTANT::TEXT::LINE);
		for (const auto& otherSession : information.GetSessions())
		{
			session.SendFormattedText(
				CONSTANT::FORMAT::USER_LIST,
				otherSession->GetId().c_str(),
				otherSession->GetAddress().c_str(),
				otherSession->GetPort());
		}
		session.SendText(sstream.str().c_str());
		session.SendText(OJT::CONSTANT::TEXT::LINE);
		session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
	}
	break;
	case COMMAND_SWITCH_LT:
	{
		std::stringstream sstream; //임시로 사용
		auto& idMap = information.GetIdMap();
		session.SendText(OJT::CONSTANT::TEXT::LINE);
		Int32 roomIndex = 1;
		for (const auto& room : information.GetChatRooms())
		{
			session.SendFormattedText(OJT::CONSTANT::FORMAT::ROOM_LIST,
				roomIndex,
				room->GetCurrentUserCount(),
				room->GetMaxUser(),
				room->GetTitle().c_str()
			);
			roomIndex++;
		}
		session.SendText(sstream.str().c_str());
		session.SendText(OJT::CONSTANT::TEXT::LINE);
		session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
	}
	break;
	case COMMAND_SWITCH_ST:
	{
		std::stringstream sstream; //임시로 사용
		sstream.str(argument);
		constexpr Int32 NOT_IN_ROOM = -1;
		Int32 roomIndex = NOT_IN_ROOM;
		ChatRoom* targetRoom = nullptr;
		sstream >> roomIndex;
		roomIndex -= 1;
		if (sstream.bad())
		{
			targetRoom = session.GetChatRoom();
			if (targetRoom != nullptr) roomIndex = information.GetChatRoomIndex(*targetRoom);
		}
		else
		{
			targetRoom = &information.GetChatRoom(roomIndex);
		}
		if (targetRoom != nullptr && information.HasChatRoom(roomIndex))
		{
			session.SendText(OJT::CONSTANT::TEXT::LINE);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::ROOM_LIST,
				roomIndex,
				targetRoom->GetCurrentUserCount(),
				targetRoom->GetMaxUser(),
				targetRoom->GetTitle().c_str()
			);
			std::time_t createTime = std::chrono::system_clock::to_time_t(targetRoom->GetCreatedTime());
			std::tm createTm;
			localtime_s(&createTm, &createTime);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::ROOM_CREATE_TIME, createTm.tm_hour, createTm.tm_min, createTm.tm_sec);
			for (const auto& member : targetRoom->GetSessions())
			{
				std::time_t entryTime = std::chrono::system_clock::to_time_t(targetRoom->GetCreatedTime());
				std::tm entryTm;
				localtime_s(&entryTm, &entryTime);
				session.SendFormattedText(OJT::CONSTANT::FORMAT::ROOM_ENTRY_USERS, member->GetId(), createTm.tm_hour, createTm.tm_min, createTm.tm_sec);
			}
			session.SendText(sstream.str().c_str());
			session.SendText(OJT::CONSTANT::TEXT::LINE);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
		else
		{
			session.SendText(OJT::CONSTANT::TEXT::ALERT_NO_ROOM_NUM);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
	}
	break;
	case COMMAND_SWITCH_PF:
	{
		if (information.HasId(argument))
		{
			const Session& targetSession = information.FindSession(argument);
			auto room = targetSession.GetChatRoom();
			if (room != nullptr)
			{
				session.SendFormattedText(
					OJT::CONSTANT::FORMAT::USER_IN_ROOM, 
					targetSession.GetId().c_str(), 
					information.GetChatRoomIndex(*room) + 1
				);
			}
			else
			{
				session.SendFormattedText(
					OJT::CONSTANT::FORMAT::USER_IN_MENU,
					targetSession.GetId().c_str()
				);
			}
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
		else
		{
			session.SendText(OJT::CONSTANT::TEXT::ALERT_NO_ID_USER);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
	}
	break;
	case COMMAND_SWITCH_TO:
	{
		std::stringstream sstream;
		sstream.str(argument);
		std::string id;
		std::string text;
		sstream >> id >> text;
		if (sstream.bad())
		{
			session.SendText(OJT::CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
		else if (information.HasId(id))
		{
			sstream.clear();
			Session& targetSession = information.FindSession(id);
			targetSession.SendFormattedText(OJT::CONSTANT::FORMAT::WHISPER, session.GetId().c_str(), text);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
		else
		{
			session.SendText(OJT::CONSTANT::TEXT::ALERT_NO_ID_USER);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
	}
	break;
	case COMMAND_SWITCH_O:
	{
		std::stringstream sstream;
		sstream.str(argument);
		Int32 maxUser = 0;
		std::string title;
		sstream >> maxUser >> title;
		if (sstream.bad())
		{
			session.SendText(OJT::CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
			session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
		}
		else
		{
			if (OJT::CONSTANT::VALUE::ROOM_MIN_USER <= maxUser && maxUser <= OJT::CONSTANT::VALUE::ROOM_MAX_USER)
			{
				ChatRoom& room = information.CreateChatRoom(maxUser, title);
				session.SendText(OJT::CONSTANT::TEXT::ROOM_CREATED);
				session.SetChatRoom(&room);
				room.EnterUser(session);
				session.SetState(SessionState::CHAT_ROOM);
			}
			else
			{
				session.SendFormattedText(
					OJT::CONSTANT::FORMAT::ALERT_ROOM_MAX_USER,
					OJT::CONSTANT::VALUE::ROOM_MIN_USER,
					OJT::CONSTANT::VALUE::ROOM_MAX_USER
					);
			}
		}
	}
	break;
	case COMMAND_SWITCH_J_Q:
	{
		if (inRoom) // /Q
		{
			session.GetChatRoom()->ExitUser(session);
			session.SetChatRoom(nullptr);
			session.SetState(SessionState::MAIN_MENU);
		}
		else // J
		{
			std::stringstream sstream; // 커맨드 읽기 임시로 설정 , 이후 하나로 통일
			sstream.str(argument);
			Int32 index = 0;
			std::string title;
			sstream >> index;
			index -= 1; // 1번부터 시작 보정
			if (sstream.bad())
			{
				session.SendText(OJT::CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
				session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
			}
			else
			{
				if (information.HasChatRoom(index))
				{
					ChatRoom& room = information.GetChatRoom(index);
					session.SetChatRoom(&room);
					room.EnterUser(session);
					session.SetState(SessionState::CHAT_ROOM);
				}
				else
				{
					session.SendText(OJT::CONSTANT::TEXT::ALERT_NO_ROOM_NUM);
				}
			}
		}
	}
	break;
	case COMMAND_SWITCH_X:
	{
		session.SendText(OJT::CONSTANT::TEXT::GOODBYE_USER);
		session.Close();
	}
	break;
	default:
		break;
	}
}

void OJT::StateFunction::OnMainMenuStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	static constexpr const Char* commands[] = { "H", "US", "LT", "ST", "PF", "TO", "O", "J", "X" };
	static constexpr bool shouldArgument[] = { 0,0,0,1,1,1,1,1,0 };
	auto ret = CommandSwitch(input, commands, shouldArgument, ARRAYSIZE(commands));
	Int32 commandIndex = ret.first;
	const Char* argument = ret.second;
	if (commandIndex != COMMAND_SWITCH_UNCOMMAND)
	{
		CommandLogic(session, information, input, argument, commandIndex, false);
	}
	else
	{
		session.SendText(OJT::CONSTANT::TEXT::ALERT_PLS_COMMAND);
		session.SendFormattedText(OJT::CONSTANT::FORMAT::HELP_OR_EXIT, OJT::CONSTANT::COMMAND::MENU_HELP, OJT::CONSTANT::COMMAND::MENU_EXIT);
	}
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

void OJT::StateFunction::OnChatRoomStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	ChatRoom* room = session.GetChatRoom();
	if (room == nullptr)
	{
		session.SetState(SessionState::MAIN_MENU);
		return;
	}

	static constexpr const Char* commands[] = { "/H", "/US", "/LT", "/ST", "/PF", "/TO", "/O", "/Q", "/X" };
	static constexpr bool shouldArgument[] = { 0,0,0,1,1,1,1,0,0 };
	auto ret = CommandSwitch(input, commands, shouldArgument, ARRAYSIZE(commands));
	Int32 commandIndex = ret.first;
	const Char* argument = ret.second;
	if (commandIndex != COMMAND_SWITCH_UNCOMMAND)
	{
		CommandLogic(session, information, input, argument, commandIndex, true);
	}
	else
	{
		std::stringstream sstream;
		sstream << session.GetId() << "> " << input << "\r\n";
		room->BroadCastText(sstream.str().c_str());
	}
}

