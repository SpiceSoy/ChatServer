//=================================================================================================
// @file StateFunction.cpp
//
// @brief �� ���¿��� ������ �ൿ�� �����ϴ� �Լ� �������Դϴ�.
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


// TODO: �� �� Ŭ������ �и� �ʿ�
// Ŀ�ǵ� �ؼ�.. sstream���� �ٲ� �غ�
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
	session.SendText("** �ȳ��ϼ���. �ؽ�Ʈ ä�� ���� ver 0.1�Դϴ�.\r\n");
	session.SendText("** �α��� ��ɾ�(LOGIN)�� ������ּ���.\r\n");
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
			session.SendText("** �̹� �ش� ���̵� ������ �����մϴ�.\r\n");
		}

	}
	else
	{
		session.SendText("** �α��� ��ɾ�(LOGIN)�� ������ּ���.\r\n");
	}
}

void OJT::StateFunction::OnMainMenuStateEnter(Session& session, ChatInformation& information)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("�ݰ����ϴ�. �ؽ�Ʈ ä�� ���� ver 0.1 �Դϴ�.\r\n\r\n");
	session.SendText("�̿� �� �����Ͻ� ���� ������ �Ʒ� �̸��Ϸ� ���� �ٶ��ϴ�.\r\n");
	session.SendText("�����մϴ�.\r\n\n");
	session.SendText("�ݸ��� �׿� Ŭ���̾�Ʈ ���� ������ (taehyeong.k@nm-neo.com)\r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
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
	session.SendText("H                           ��ɾ� �ȳ�\r\n");
	session.SendText("US                          �̿��� ��� ����\r\n");
	session.SendText("LT                          ��ȭ�� ��� ����\r\n");
	session.SendText("ST [���ȣ]                 ��ȭ�� ���� ����\r\n");
	session.SendText("PF [����ID]               �̿��� ���� ����\r\n");
	session.SendText("TO [����ID] [�޽���]      ���� ������\r\n");
	session.SendText("O  [�ִ��ο�] [������]      ��ȭ�� �����\r\n");
	session.SendText("J  [���ȣ]                 ��ȭ�� �����ϱ�\r\n");
	session.SendText("X                           ������ \r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
}

static Void SendUserList(OJT::Session& session)
{
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("H                           ��ɾ� �ȳ�\r\n");
	session.SendText("US                          �̿��� ��� ����\r\n");
	session.SendText("LT                          ��ȭ�� ��� ����\r\n");
	session.SendText("ST [���ȣ]                 ��ȭ�� ���� ����\r\n");
	session.SendText("PF [����ID]               �̿��� ���� ����\r\n");
	session.SendText("TO [����ID] [�޽���]      ���� ������\r\n");
	session.SendText("O  [�ִ��ο�] [������]      ��ȭ�� �����\r\n");
	session.SendText("J  [���ȣ]                 ��ȭ�� �����ϱ�\r\n");
	session.SendText("X                           ������ \r\n");
	session.SendText("---------------------------------------------------------------\r\n");
	session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
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
		session.SendText("��ɾ �Է����ֽʽÿ�.\r\n");
		session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
	}
	break;
	case COMMAND_SWITCH_NO_ARGUMENT:
	{
		session.SendText("��ɾ� ���ڰ� �̻��մϴ�.\r\n");
		session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
	}
	break;
	case COMMAND_SWITCH_H:
	{
		SendCommandHelp(session);
	}
	break;
	case COMMAND_SWITCH_US:
	{
		std::stringstream sstream; //�ӽ÷� ���
		auto& idMap = information.GetIdMap();
		session.SendText("---------------------------------------------------------------\r\n");
		for (const auto& otherSession : information.GetSessions())
		{
			sstream << " �̿���: " << std::setw(30) << std::left << otherSession->GetId() 
				<< "������: " << otherSession->GetAddress() << ":" << otherSession->GetPort() 
				<< "\r\n";
		}
		session.SendText(sstream.str().c_str());
		session.SendText("---------------------------------------------------------------\r\n");
		session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
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
		std::stringstream sstream; // Ŀ�ǵ� �б� �ӽ÷� ���� , ���� �ϳ��� ����
		sstream.str(argument);
		Int32 maxUser = 0;
		std::string title;
		sstream >> maxUser >> title;
		if (sstream.bad())
		{
			session.SendText("��ɾ� ���ڰ� �̻��մϴ�.\r\n");
			session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
		}
		else 
		{
			if (maxUser < 2 || maxUser > 20)
			{
				session.SendText("��ȭ�� �ο��� 2-20�� ���̷� �Է����ּ���.\r\n");
			}
			else 
			{
				ChatRoom& room = information.CreateChatRoom(maxUser, title);
				session.SendText("��ȭ���� �����Ǿ����ϴ�.\r\n");
				session.SetChatRoom(&room);
				room.EnterUser(session);
				session.SetState(SessionState::CHAT_ROOM);
			}
		}
	}
	break;
	case COMMAND_SWITCH_J:
	{
		std::stringstream sstream; // Ŀ�ǵ� �б� �ӽ÷� ���� , ���� �ϳ��� ����
		sstream.str(argument);
		Int32 index = 0;
		std::string title;
		sstream >> index;
		index -= 1; // 1������ ���� ����
		if (sstream.bad())
		{
			session.SendText("��ɾ� ���ڰ� �̻��մϴ�.\r\n");
			session.SendText("��ɾ� �ȳ�(H) ����(X)\r\n");
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
				session.SendText("�ش��ϴ� ��ȭ���� �����ϴ�.\r\n");
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
	sstream << "** " << session.GetId() << "���� �����̽��ϴ�. (�����ο� " << room->GetCurrentUserCount() << "/" << room->GetMaxUser() << ")\r\n";
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

