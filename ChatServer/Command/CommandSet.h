//=================================================================================================
// @file CommandSet.h
//
// @brief Define State Command Set
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "../DataTypes.h"
#include "../Command/ECommand.h"
#include "../Command/CommandElement.h"
#include <vector>

namespace OJT
{
	namespace ChatCommand
	{
		struct CommandSet
		{
			std::vector<CommandElement> Elements;
			ECommand OnNoCommand;
			ECommand OnWrongArgument;

			CommandSet(ECommand onNoCommand, ECommand onWrongArgument, std::vector<CommandElement>&& elements)
				:OnNoCommand(onNoCommand), OnWrongArgument(onWrongArgument), Elements(std::move(elements))
			{
			}
			CommandSet(ECommand onNoCommand, ECommand onWrongArgument, const std::vector<CommandElement>& elements)
				:OnNoCommand(onNoCommand), OnWrongArgument(onWrongArgument), Elements(elements)
			{
			}

			CommandSet(ECommand onNoCommand, ECommand onWrongArgument, std::initializer_list<CommandElement>&& elements)
				:OnNoCommand(onNoCommand), OnWrongArgument(onWrongArgument), Elements(elements)
			{
			}
		};

	};
};