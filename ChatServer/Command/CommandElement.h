//=================================================================================================
// @file CommandElement.h
//
// @brief command element to define commands argument, prefix
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/ECommand.h"
#include "DataTypes.h"

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