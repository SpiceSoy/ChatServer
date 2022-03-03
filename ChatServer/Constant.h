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
			constexpr const Char* PLS_LOGIN = "** 로그인 명령어(LOGIN)를 사용해주세요.\r\n";
			constexpr const Char* WRITER_INFO = 
				"이용 중 불편하신 점이 있으면 아래 이메일로 문의 바랍니다.\r\n"
				"감사합니다.\r\n\n"
				"넷마블 네오 클라이언트 직무 김태형 (taehyeong.k@nm-neo.com)\r\n";
			constexpr const Char* ALREADY_LOGIN =
				"** 이미 해당 아이디가 서버에 존재합니다.\r\n";
			constexpr const Char* TOOLTIP_HELP = "명령어 안내";
			constexpr const Char* TOOLTIP_USER_LIST = "이용자 목록 보기";
			constexpr const Char* TOOLTIP_ROOM_LIST = "대화방 목록 보기";
			constexpr const Char* TOOLTIP_ROOM_INFO = "대화방 정보 보기";
			constexpr const Char* TOOLTIP_USER_INFO = "이용자 정보 보기";
			constexpr const Char* TOOLTIP_WHISPER = "쪽지 보내기";
			constexpr const Char* TOOLTIP_MAKE_ROOM = "대화방 만들기";
			constexpr const Char* TOOLTIP_ENTER_ROOM = "대화방 들어가기";
			constexpr const Char* TOOLTIP_QUIT_ROOM = "대화방 나가기";
			constexpr const Char* TOOLTIP_EXIT = "끝내기";

			constexpr const Char* TOOLTIP_ARG_ROOM_INFO= "[방번호]";
			constexpr const Char* TOOLTIP_ARG_USER_INFO = "[상대방ID]";
			constexpr const Char* TOOLTIP_ARG_WHISPER = "[상대방ID] [메시지]";
			constexpr const Char* TOOLTIP_ARG_MAKE_ROOM = "[최대인원] [방제목]";
			constexpr const Char* TOOLTIP_ARG_ENTER_ROOM = "[방번호]";
			constexpr const Char* TOOLTIP_ARG_LOGIN = "[ID]";
			constexpr const Char* TOOLTIP_ARG_NO_ARG = "";

			constexpr const Char* ALERT_ARGUMENT_WRONG = "명령어 인자가 이상합니다.\r\n";
			constexpr const Char* ALERT_PLS_COMMAND = "명령어를 입력해주세요.\r\n";
			constexpr const Char* ALERT_NO_ROOM_NUM = "해당 번호의 방이 존재하지 않습니다.\r\n";
			constexpr const Char* ALERT_NO_ID_USER = "해당 ID를 가진 유저가 존재하지 않습니다.\r\n";

			constexpr const Char* ROOM_CREATED = "대화방이 개설되었습니다.\r\n";
			constexpr const Char* GOODBYE_USER = "연결을 종료합니다. 이용해주셔서 감사합니다.\r\n";
		};
		namespace FORMAT
		{
			constexpr const Char* WELCOME = "** 안녕하세요. 텍스트 채팅 서버 ver %s입니다.\r\n";
			constexpr const Char* HELP_OR_EXIT = "명령어 안내(%s) 종료(%s)\r\n";
			constexpr const Char* TOOLTIP = "%3s %-24s %s\r\n";
			constexpr const Char* USER_LIST = "이용자: %-30s접속지: %s:%d\r\n";
			constexpr const Char* ROOM_LIST = "[%3d] (%2d/%2d) %s\r\n";
			constexpr const Char* ROOM_CREATE_TIME= "개설시간: %02d:%02d:%02d\r\n";
			constexpr const Char* ROOM_ENTRY_USERS = "  참여자: %-30s 참여시간: %02d:%02d:%02d\r\n";
			constexpr const Char* USER_IN_ROOM= "%s님은 현재 %d번 방에 참여중입니다.\r\n";
			constexpr const Char* USER_IN_MENU = "%s님은 현재 메인 메뉴에서 대기중입니다.\r\n";
			constexpr const Char* WHISPER = "# %s님의 쪽지 ==> %s\r\n";
			constexpr const Char* ALERT_ROOM_MAX_USER = "대화방 인원을 %d-%d명 사이로 입력해주세요.\r\n";
			constexpr const Char* USER_ENTER_ROOM = "** %s님이 들어오였습니다. (현재 인원 %d/%d)\r\n";
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
