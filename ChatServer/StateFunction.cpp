//=================================================================================================
// @file StateFunction.cpp
//
// @brief 각 상태에서 수행할 행동을 정의하는 함수 모음집입니다.
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "StateFunction.h"
#include "SessionState.h"
#include "Session.h"
#include <iostream>

constexpr UInt64 commandBufferSize = 50;
constexpr UInt64 chatBufferSize = 1024;

static void SplitCommand(const Char* input, const Char** command, const Char** argument)
{
	Int64 csr = 0;
	while (input[csr] != 0)
	{
		if (input[csr] == ' ')
		{
			*command = input;
			*argument = input + (csr + 1);
			return;
		}
		csr++;
	}
}
static Bool StartWith(const Char* input, const Char* command)
{
	Int64 csr = 0;
	while (toupper(input[csr]) == toupper(command[csr])) csr++;
	return (input[csr] == ' ' || input[csr] == '\r' || input[csr] == '\n' || input[csr] == '\0') && command[csr] == '\0';
}
static Bool ValidArgument(const Char* argument)
{
	return *argument != '\0' && *argument != '\n' && *argument != ' ';
}

void OJT::StateFunction::OnWaitLoginStateEnter(Session& session)
{
	session.SendText("** 안녕하세요. 텍스트 채팅 서버 ver 0.1입니다.\r\n");
	session.SendText("** 로그인 명령어(LOGIN)를 사용해주세요.\r\n");
}

void OJT::StateFunction::OnWaitLoginStateReciveLine(Session& session, const Char* input)
{
	const Char* command = nullptr;
	const Char* argument = nullptr;
	SplitCommand(input, &command, &argument);
	if (StartWith(command, "LOGIN") && ValidArgument(argument))
	{
		std::cout << "Login : " << argument;
		session.SetState(SessionState::MAIN_MENU);
	}
	else 
	{
		session.SendText("** 로그인 명령어(LOGIN)를 사용해주세요.\r\n");
	}
}

void OJT::StateFunction::OnMainMenuStateEnter(Session& session)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("반갑습니다. 텍스트 채팅 서버 ver 0.1 입니다.\r\n\r\n");
	session.SendText("이용 중 불편하신 점이 있으면 아래 이메일로 문의 바랍니다.\r\n");
	session.SendText("감사합니다.\r\n\n");
	session.SendText("넷마블 네오 클라이언트 직무 김태형 (taehyeong.k@nm-neo.com)\r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("명령어 안내(H) 종료(X)\r\n");
}

void OJT::StateFunction::OnMainMenuStateReciveLine(Session& session, const Char* input)
{
}

void OJT::StateFunction::OnChatRoomStateEnter(Session& session)
{
}

void OJT::StateFunction::OnChatRoomStateReciveLine(Session& session, const Char* input)
{
}
