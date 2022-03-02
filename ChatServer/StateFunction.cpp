//=================================================================================================
// @file StateFunction.cpp
//
// @brief �� ���¿��� ������ �ൿ�� �����ϴ� �Լ� �������Դϴ�.
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
	session.SendText("** �ȳ��ϼ���. �ؽ�Ʈ ä�� ���� ver 0.1�Դϴ�.\r\n");
	session.SendText("** �α��� ��ɾ�(LOGIN)�� ������ּ���.\r\n");
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
		session.SendText("** �α��� ��ɾ�(LOGIN)�� ������ּ���.\r\n");
	}
}

void OJT::StateFunction::OnMainMenuStateEnter(Session& session)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("�ݰ����ϴ�. �ؽ�Ʈ ä�� ���� ver 0.1 �Դϴ�.\r\n\r\n");
	session.SendText("�̿� �� �����Ͻ� ���� ������ �Ʒ� �̸��Ϸ� ���� �ٶ��ϴ�.\r\n");
	session.SendText("�����մϴ�.\r\n\n");
	session.SendText("�ݸ��� �׿� Ŭ���̾�Ʈ ���� ������ (taehyeong.k@nm-neo.com)\r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
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
