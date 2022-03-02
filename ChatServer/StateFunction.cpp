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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#define ARRAYSIZE(A) sizeof(A) / sizeof((A)[0])

constexpr UInt64 commandBufferSize = 50;
constexpr UInt64 chatBufferSize = 1024;

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
	session.SendText("** 안녕하세요. 텍스트 채팅 서버 ver 0.1입니다.\r\n");
	session.SendText("** 로그인 명령어(LOGIN)를 사용해주세요.\r\n");
}

void OJT::StateFunction::OnWaitLoginStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	const Char* command = nullptr;
	const Char* argument = nullptr;
	SplitCommand(input, &command, &argument);
	if (StartWith(command, "LOGIN") && ValidArgument(argument) )
	{
		if (!information.HasId(argument))
		{
			session.SetState(SessionState::MAIN_MENU);
			session.SetId(argument);
			information.SetId(session, argument);
		} 
		else 
		{
			session.SendText("** 이미 해당 아이디가 서버에 존재합니다.\r\n");
		}

	}
	else
	{
		session.SendText("** 로그인 명령어(LOGIN)를 사용해주세요.\r\n");
	}
}

void OJT::StateFunction::OnMainMenuStateEnter(Session& session, ChatInformation& information)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("반갑습니다. 텍스트 채팅 서버 ver 0.1 입니다.\r\n\r\n");
	session.SendText("이용 중 불편하신 점이 있으면 아래 이메일로 문의 바랍니다.\r\n");
	session.SendText("감사합니다.\r\n\n");
	session.SendText("넷마블 네오 클라이언트 직무 김태형 (taehyeong.k@nm-neo.com)\r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("명령어 안내(H) 종료(X)\r\n");
}

// return 
// first : commandIndex -1 = UNCOMMNAD -2 = NO_ARGUMENT
// second : argument Ptr
static constexpr Int32 COMMAND_SWITCH_UNCOMMAND = -1;
static constexpr Int32 COMMAND_SWITCH_NO_ARGUMENT = -2;
static std::pair<Int32, const Char*> CommandSwitch(const Char* input, const Char* commands[], bool shouldArgument[], int commandCount)
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
static constexpr Int32 COMMAND_SWITCH_J = 7;
static constexpr Int32 COMMAND_SWITCH_X = 8;
static Void SendCommandHelp(OJT::Session& session)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("H                           명령어 안내\r\n");
	session.SendText("US                          이용자 목록 보기\r\n");
	session.SendText("LT                          대화방 목록 보기\r\n");
	session.SendText("ST [방번호]                 대화방 정보 보기\r\n");
	session.SendText("PF [상대방ID]               이용자 정보 보기\r\n");
	session.SendText("TO [상대방ID] [메시지]      쪽지 보내기\r\n");
	session.SendText("O  [최대인원] [방제목]      대화방 만들기\r\n");
	session.SendText("J  [방번호]                 대화방 참여하기\r\n");
	session.SendText("X                           끝내기 \r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("명령어 안내(H) 종료(X)\r\n");
}

static Void SendUserList(OJT::Session& session)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("H                           명령어 안내\r\n");
	session.SendText("US                          이용자 목록 보기\r\n");
	session.SendText("LT                          대화방 목록 보기\r\n");
	session.SendText("ST [방번호]                 대화방 정보 보기\r\n");
	session.SendText("PF [상대방ID]               이용자 정보 보기\r\n");
	session.SendText("TO [상대방ID] [메시지]      쪽지 보내기\r\n");
	session.SendText("O  [최대인원] [방제목]      대화방 만들기\r\n");
	session.SendText("J  [방번호]                 대화방 참여하기\r\n");
	session.SendText("X                           끝내기 \r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("명령어 안내(H) 종료(X)\r\n");
}


void OJT::StateFunction::OnMainMenuStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	static const Char* commands[] = { "H", "US", "LT", "ST", "PF", "TO", "O", "J", "X" };
	static bool shouldArgument[] = { 0,0,0,1,1,1,1,1,0 };
	auto ret = CommandSwitch(input, commands, shouldArgument, ARRAYSIZE(commands));
	Int32 commandIndex = ret.first;
	const Char* argument = ret.second;
	switch (commandIndex)
	{
	case COMMAND_SWITCH_UNCOMMAND:
	{
		session.SendText("명령어를 입력해주십시오.\r\n");
		session.SendText("명령어 안내(H) 종료(X)\r\n");
	}
	break;
	case COMMAND_SWITCH_NO_ARGUMENT:
	{
		session.SendText("명령어 인자가 이상합니다.\r\n");
		session.SendText("명령어 안내(H) 종료(X)\r\n");
	}
	break;
	case COMMAND_SWITCH_H:
	{
		SendCommandHelp(session);
	}
	break;
	case COMMAND_SWITCH_US:
	{
		std::stringstream sstream; //임시로 사용
		auto& idMap = information.GetIdMap();
		session.SendText("---------------------------------------------------------------\r\n");
		for (const auto& otherSession : information.GetSessions())
		{
			sstream << " 이용자: " << std::setw(30) << std::left << otherSession->GetId() 
				<< "접속지: " << otherSession->GetAddress() << ":" << otherSession->GetPort() 
				<< "\r\n";
		}
		session.SendText(sstream.str().c_str());
		session.SendText("---------------------------------------------------------------\r\n");
		session.SendText("명령어 안내(H) 종료(X)\r\n");
	}
	break;
	case COMMAND_SWITCH_LT:
	{
	}
	break;
	case COMMAND_SWITCH_ST:
	{
	}
	break;
	case COMMAND_SWITCH_PF:
	{
	}
	break;
	case COMMAND_SWITCH_TO:
	{
	}
	break;
	case COMMAND_SWITCH_O:
	{
		std::stringstream sstream; // 커맨드 읽기 임시로 설정 , 이후 하나로 통일
		sstream.str(argument);
		Int32 maxUser = 0;
		std::string title;
		sstream >> maxUser >> title;
		if (sstream.bad())
		{
			session.SendText("명령어 인자가 이상합니다.\r\n");
			session.SendText("명령어 안내(H) 종료(X)\r\n");
		}
		else 
		{
			if (maxUser < 2 || maxUser > 20)
			{
				session.SendText("대화방 인원을 2-20명 사이로 입력해주세요.\r\n");
			}
			else 
			{
				ChatRoom& room = information.CreateChatRoom(maxUser, title);
				session.SendText("대화방이 개설되었습니다.\r\n");
				session.SetChatRoom(&room);
				room.EnterUser(session);
				session.SetState(SessionState::CHAT_ROOM);
			}
		}
	}
	break;
	case COMMAND_SWITCH_J:
	{
		std::stringstream sstream; // 커맨드 읽기 임시로 설정 , 이후 하나로 통일
		sstream.str(argument);
		Int32 index = 0;
		std::string title;
		sstream >> index;
		index -= 1; // 1번부터 시작 보정
		if (sstream.bad())
		{
			session.SendText("명령어 인자가 이상합니다.\r\n");
			session.SendText("명령어 안내(H) 종료(X)\r\n");
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
				session.SendText("해당하는 대화방이 없습니다.\r\n");
			}
		}
	}
	break;
	case COMMAND_SWITCH_X:
	{
	}
	break;

	default:
		break;
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
	room->BroadCastText(session.GetId().c_str());
	std::stringstream sstream;
	sstream << "** " << session.GetId() << "님이 들어오셨습니다. (현재인원 " << room->GetCurrentUserCount() << "/" << room->GetMaxUser() << ")\r\n";
	room->BroadCastText(sstream.str().c_str());
}

void OJT::StateFunction::OnChatRoomStateReciveLine(Session& session, ChatInformation& information, const Char* input)
{
	ChatRoom* room = session.GetChatRoom();
	if (room == nullptr)
	{
		session.SetState(SessionState::MAIN_MENU);
		return;
	}

	std::stringstream sstream;
	sstream << session.GetId() << "> " << input  << "\r\n";
	room->BroadCastText(sstream.str().c_str());
}

