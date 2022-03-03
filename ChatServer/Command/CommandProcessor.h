//=================================================================================================
// @file CommandRoomList.h
//
// @brief command class of viewing room list
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "../DataTypes.h"
#include "../Command/ICommand.h"
#include "../Command/ECommand.h"
#include "../Command/CommandSet.h"
#include <tuple>
#include <vector>
#include <memory>
namespace OJT
{
	namespace ChatCommand
	{
		class CommandProcessor
		{
		private:
			std::vector<std::unique_ptr<ICommand>> commands;
		public:
			CommandProcessor();
			void ExecuteCommand(
				Session& session,
				ChatInformation& info,
				const Char* input,
				const CommandSet& commandSet) const;
		private:
			std::pair<ECommand, const Char*> SwitchCommand(const Char* input, const CommandSet& commandSet) const;
			static Bool SplitCommand(const Char* input, const Char*& command, const Char*& argument);
			static Bool IsStartedWith(const Char* input, const Char* command);
			static Bool IsValidArgument(const Char* argument);

			
		};
	};
};