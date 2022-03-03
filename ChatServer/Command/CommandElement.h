//=================================================================================================
// @file Commands.h
//
// @brief total header for chat commands
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "../DataTypes.h"
#include "../Command/ECommand.h"

namespace OJT
{
	namespace ChatCommand
	{
		struct CommandElement
		{
			const Char* prefix;
			bool shouldArgument;
			ECommand command;
		};
	};
};