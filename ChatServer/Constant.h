//=================================================================================================
// @file Constant.h
//
// @brief Strings for constant strings(command info, alarm, format, etc...)
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "DataTypes.h"
#include <string>
namespace OJT
{
	namespace CONSTANT
	{
		namespace TEXT
		{
			constexpr const Char* LINE = "---------------------------------------------------------------\r\n";
			constexpr const Char* PLS_LOGIN = "** �α��� ��ɾ�(LOGIN)�� ������ּ���.\r\n";
			constexpr const Char* WRITER_INFO = 
				"�̿� �� �����Ͻ� ���� ������ �Ʒ� �̸��Ϸ� ���� �ٶ��ϴ�.\r\n"
				"�����մϴ�.\r\n\n"
				"�ݸ��� �׿� Ŭ���̾�Ʈ ���� ������ (taehyeong.k@nm-neo.com)\r\n";
			constexpr const Char* ALREADY_LOGIN =
				"** �̹� �ش� ���̵� ������ �����մϴ�.\r\n";
			constexpr const Char* TOOLTIP_HELP = "��ɾ� �ȳ�";
			constexpr const Char* TOOLTIP_USER_LIST = "�̿��� ��� ����";
			constexpr const Char* TOOLTIP_ROOM_LIST = "��ȭ�� ��� ����";
			constexpr const Char* TOOLTIP_ROOM_INFO = "��ȭ�� ���� ����";
			constexpr const Char* TOOLTIP_USER_INFO = "�̿��� ���� ����";
			constexpr const Char* TOOLTIP_WHISPER = "���� ������";
			constexpr const Char* TOOLTIP_MAKE_ROOM = "��ȭ�� �����";
			constexpr const Char* TOOLTIP_ENTER_ROOM = "��ȭ�� ����";
			constexpr const Char* TOOLTIP_QUIT_ROOM = "��ȭ�� ������";
			constexpr const Char* TOOLTIP_EXIT = "������";

			constexpr const Char* TOOLTIP_ARG_ROOM_INFO= "[���ȣ]";
			constexpr const Char* TOOLTIP_ARG_USER_INFO = "[����ID]";
			constexpr const Char* TOOLTIP_ARG_WHISPER = "[����ID] [�޽���]";
			constexpr const Char* TOOLTIP_ARG_MAKE_ROOM = "[�ִ��ο�] [������]";
			constexpr const Char* TOOLTIP_ARG_ENTER_ROOM = "[���ȣ]";
			constexpr const Char* TOOLTIP_ARG_LOGIN = "[ID]";
			constexpr const Char* TOOLTIP_ARG_NO_ARG = "";

			constexpr const Char* ALERT_ARGUMENT_WRONG = "��ɾ� ���ڰ� �̻��մϴ�.\r\n";
			constexpr const Char* ALERT_PLS_COMMAND = "��ɾ �Է����ּ���.\r\n";
			constexpr const Char* ALERT_NO_ROOM_NUM = "�ش� ��ȣ�� ���� �������� �ʽ��ϴ�.\r\n";
			constexpr const Char* ALERT_NO_ID_USER = "�ش� ID�� ���� ������ �������� �ʽ��ϴ�.\r\n";

			constexpr const Char* ROOM_CREATED = "��ȭ���� �����Ǿ����ϴ�.\r\n";
			constexpr const Char* GOODBYE_USER = "������ �����մϴ�. �̿����ּż� �����մϴ�.\r\n";
		};
		namespace FORMAT
		{
			constexpr const Char* WELCOME = "** �ȳ��ϼ���. �ؽ�Ʈ ä�� ���� ver %s�Դϴ�.\r\n";
			constexpr const Char* HELP_OR_EXIT = "��ɾ� �ȳ�(%s) ����(%s)\r\n";
			constexpr const Char* TOOLTIP = "%3s %-24s %s\r\n";
			constexpr const Char* USER_LIST = "�̿���: %-30s������: %s:%d\r\n";
			constexpr const Char* ROOM_LIST = "[%3d] (%2d/%2d) %s\r\n";
			constexpr const Char* ROOM_CREATE_TIME= "�����ð�: %02d:%02d:%02d\r\n";
			constexpr const Char* ROOM_ENTRY_USERS = "  ������: %-30s �����ð�: %02d:%02d:%02d\r\n";
			constexpr const Char* USER_IN_ROOM= "%s���� ���� %d�� �濡 �������Դϴ�.\r\n";
			constexpr const Char* USER_IN_MENU = "%s���� ���� ���� �޴����� ������Դϴ�.\r\n";
			constexpr const Char* WHISPER = "# %s���� ���� ==> %s\r\n";
			constexpr const Char* ALERT_ROOM_MAX_USER = "��ȭ�� �ο��� %d-%d�� ���̷� �Է����ּ���.\r\n";
			constexpr const Char* USER_ENTER_ROOM = "** %s���� ���������ϴ�. (���� �ο� %d/%d)\r\n";
			constexpr const Char* SERVER_SIDE_USER_LOG = "%s:%d [%s] %s\r\n";
			constexpr const Char* CHAT = "%s> %s\r\n";
		};
		namespace COMMAND
		{
			constexpr const Char* LOGIN = "LOGIN";
			constexpr const Char* MENU_HELP = "H";
			constexpr const Char* MENU_USER_LIST = "US";
			constexpr const Char* MENU_ROOM_LIST = "LT";
			constexpr const Char* MENU_ROOM_INFO = "ST";
			constexpr const Char* MENU_USER_INFO = "PF";
			constexpr const Char* MENU_WHISPER = "TO";
			constexpr const Char* MENU_MAKE_ROOM = "O";
			constexpr const Char* MENU_ENTER_ROOM = "J";
			constexpr const Char* MENU_EXIT = "X";

			constexpr const Char* CHATROOM_HELP = "/H";
			constexpr const Char* CHATROOM_USER_LIST = "/US";
			constexpr const Char* CHATROOM_ROOM_LIST = "/LT";
			constexpr const Char* CHATROOM_ROOM_INFO = "/ST";
			constexpr const Char* CHATROOM_USER_INFO = "/PF";
			constexpr const Char* CHATROOM_WHISPHER = "/TO";
			constexpr const Char* CHATROOM_MAKE_ROOM = "/O";
			constexpr const Char* CHATROOM_QUIT_ROOM = "/Q";
			constexpr const Char* CHATROOM_EXIT = "/X";

			constexpr const Char* WRONG_ARGUMENT = "_WRONG_WRONG_";
			constexpr const Char* NO_COMMAND = "_NO_COMMAND_";
		};

		namespace VALUE
		{
			constexpr const Char* VERSION = "0.1";
			constexpr const Int32 ROOM_MAX_USER = 20;
			constexpr const Int32 ROOM_MIN_USER = 2;

			constexpr const Char* LOGIN_COMMANDS[] = {
				COMMAND::LOGIN,
			};
			constexpr const Char* LOGIN_ARGS[] = {
				TEXT::TOOLTIP_ARG_LOGIN,
			};
			constexpr Int32 LOGIN_COMMAND_COUNT = sizeof(OJT::CONSTANT::VALUE::LOGIN_COMMANDS) / sizeof(OJT::CONSTANT::VALUE::LOGIN_COMMANDS[0]);

			constexpr const Char* MENU_COMMANDS[] = {
				COMMAND::MENU_HELP,
				COMMAND::MENU_USER_LIST,
				COMMAND::MENU_ROOM_LIST,
				COMMAND::MENU_ROOM_INFO,
				COMMAND::MENU_USER_INFO,
				COMMAND::MENU_WHISPER,
				COMMAND::MENU_MAKE_ROOM,
				COMMAND::MENU_ENTER_ROOM,
				COMMAND::MENU_EXIT,
			};
			constexpr const Char* MENU_ARGS[] = {
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_ROOM_INFO,
				TEXT::TOOLTIP_ARG_USER_INFO,
				TEXT::TOOLTIP_ARG_WHISPER,
				TEXT::TOOLTIP_ARG_MAKE_ROOM,
				TEXT::TOOLTIP_ARG_ENTER_ROOM,
				TEXT::TOOLTIP_ARG_NO_ARG,
			};
			constexpr const Char* MENU_TOOLTIP[] = {
				TEXT::TOOLTIP_HELP,
				TEXT::TOOLTIP_USER_LIST,
				TEXT::TOOLTIP_ROOM_LIST,
				TEXT::TOOLTIP_ROOM_INFO,
				TEXT::TOOLTIP_USER_INFO,
				TEXT::TOOLTIP_WHISPER,
				TEXT::TOOLTIP_MAKE_ROOM,
				TEXT::TOOLTIP_ENTER_ROOM,
				TEXT::TOOLTIP_EXIT,
			};
			constexpr Int32 MENU_COMMAND_COUNT = sizeof(OJT::CONSTANT::VALUE::MENU_COMMANDS) / sizeof(OJT::CONSTANT::VALUE::MENU_COMMANDS[0]);
			constexpr const Char* CHATROOM_COMMANDS[] = {
				COMMAND::CHATROOM_HELP,
				COMMAND::CHATROOM_USER_LIST,
				COMMAND::CHATROOM_ROOM_LIST,
				COMMAND::CHATROOM_ROOM_INFO,
				COMMAND::CHATROOM_USER_INFO,
				COMMAND::CHATROOM_WHISPHER,
				COMMAND::CHATROOM_MAKE_ROOM,
				COMMAND::CHATROOM_QUIT_ROOM,
				COMMAND::CHATROOM_EXIT,
			};
			constexpr const Char* CHATROOM_ARGS[] = {
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_ROOM_INFO,
				TEXT::TOOLTIP_ARG_USER_INFO,
				TEXT::TOOLTIP_ARG_WHISPER,
				TEXT::TOOLTIP_ARG_MAKE_ROOM,
				TEXT::TOOLTIP_ARG_NO_ARG,
				TEXT::TOOLTIP_ARG_NO_ARG,
			};
			constexpr const Char* CHATROOM_TOOLTIP[] = {
				TEXT::TOOLTIP_HELP,
				TEXT::TOOLTIP_USER_LIST,
				TEXT::TOOLTIP_ROOM_LIST,
				TEXT::TOOLTIP_ROOM_INFO,
				TEXT::TOOLTIP_USER_INFO,
				TEXT::TOOLTIP_WHISPER,
				TEXT::TOOLTIP_MAKE_ROOM,
				TEXT::TOOLTIP_QUIT_ROOM,
				TEXT::TOOLTIP_EXIT,
			};
			constexpr Int32 CHATROOM_COMMAND_COUNT = sizeof(OJT::CONSTANT::VALUE::CHATROOM_COMMANDS) / sizeof(OJT::CONSTANT::VALUE::CHATROOM_COMMANDS[0]);

		};
	};
};

#pragma once
