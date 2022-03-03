//=================================================================================================
// @file ECommand.h
//
// @brief enum class of identify commands
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/ICommand.h"
#include "Command/CommandEnterRoom.h"
#include "Command/CommandExit.h"
#include "Command/CommandHelpInMenu.h"
#include "Command/CommandHelpInRoom.h"
#include "Command/CommandMakeRoom.h"
#include "Command/CommandQuitRoom.h"
#include "Command/CommandRoomInfo.h"
#include "Command/CommandRoomList.h"
#include "Command/CommandUserInfo.h"
#include "Command/CommandUserList.h"
#include "Command/CommandWhisper.h"
#include "Command/CommandWrongArgument.h"
#include "Command/CommandSendRoomChat.h"
#include "Command/CommandPlsCommand.h"
#include "Command/CommandLogin.h"
#include "Command/CommandPlsLogin.h"
#include "Command/CommandInviteRoom.h"

namespace OJT
{
	namespace ChatCommand
	{
		enum class ECommand
		{
			EnterRoom,
			Exit,
			HelpInMenu,
			HelpInRoom,
			MakeRoom,
			QuitRoom,
			RoomInfo,
			RoomList,
			UserInfo,
			UserList,
			Whisper,
			WrongArgument,
			SendRoomChat,
			PlsCommand,
			Login,
			PlsLogin,
			InviteRoom,
		};
	};
};