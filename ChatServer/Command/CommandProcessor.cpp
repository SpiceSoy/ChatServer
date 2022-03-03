//=================================================================================================
// @file CommandRoomList.cpp
//
// @brief command class of viewing room list
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/ECommand.h"
#include "../Command/CommandProcessor.h"
#include "../Constant.h"
#include "../ChatInformation.h"
#include "../ChatRoom.h"
#include "../Session.h"
#include <sstream>
#include <string>

OJT::ChatCommand::CommandProcessor::CommandProcessor()
{
	commands.emplace_back(std::make_unique<CommandEnterRoom>());
	commands.emplace_back(std::make_unique<CommandExit>());
	commands.emplace_back(std::make_unique<CommandHelpInMenu>());
	commands.emplace_back(std::make_unique<CommandHelpInRoom>());
	commands.emplace_back(std::make_unique<CommandMakeRoom>());
	commands.emplace_back(std::make_unique<CommandQuitRoom>());
	commands.emplace_back(std::make_unique<CommandRoomInfo>());
	commands.emplace_back(std::make_unique<CommandRoomList>());
	commands.emplace_back(std::make_unique<CommandUserInfo>());
	commands.emplace_back(std::make_unique<CommandUserList>());
	commands.emplace_back(std::make_unique<CommandWhisper>());
	commands.emplace_back(std::make_unique<CommandWrongArgument>());
	commands.emplace_back(std::make_unique<CommandSendRoomChat>());
	commands.emplace_back(std::make_unique<CommandPlsCommand>());
	commands.emplace_back(std::make_unique<CommandLogin>());
	commands.emplace_back(std::make_unique<CommandPlsLogin>());
	//commands.emplace_back(std::make_unique<CommandInvite>());
}

void OJT::ChatCommand::CommandProcessor::ExecuteCommand(Session& session, ChatInformation& info, const Char* input, const CommandSet& commandSet) const
{
	auto ret = SwitchCommand(input, commandSet);
	ECommand command = ret.first;
	const Char* argument = ret.second;
	this->commands.at(static_cast<Int32>(ret.first))->Execute(argument, session, info);
}

std::pair<OJT::ChatCommand::ECommand, const Char*> OJT::ChatCommand::CommandProcessor::SwitchCommand(const Char* input, const CommandSet& commandSet) const
{
	for(const CommandElement& set : commandSet.Elements)
	{
		const Char* command = nullptr;
		const Char* argument = nullptr;
		SplitCommand(input, command, argument);

		if (IsStartedWith(input, set.prefix))
		{
			if (set.shouldArgument)
			{
				if (IsValidArgument(argument))
				{
					return std::make_pair(set.command, argument);
				}
				else
				{
					return std::make_pair(commandSet.OnWrongArgument, nullptr);
				}
			}
			else
			{
				return std::make_pair(set.command, argument);
			}
		}
	}
	return std::make_pair(commandSet.OnNoCommand, input);
}

Bool OJT::ChatCommand::CommandProcessor::SplitCommand(const Char* input, const Char*& command, const Char*& argument)
{
	Int64 csr = 0;
	command = input;
	while (input[csr] != 0)
	{
		if (input[csr] == ' ')
		{
			argument = input + (csr + 1);
			return true;
		}
		csr++;
	}
	return false;
}

Bool OJT::ChatCommand::CommandProcessor::IsStartedWith(const Char* input, const Char* command)
{
	Int64 csr = 0;
	while (input[csr] != 0 && command[csr] != 0 && toupper(input[csr]) == toupper(command[csr])) csr++;
	return (input[csr] == ' ' || input[csr] == '\r' || input[csr] == '\n' || input[csr] == '\0') && command[csr] == '\0';
}

Bool OJT::ChatCommand::CommandProcessor::IsValidArgument(const Char* argument)
{
	return *argument != '\0' && *argument != '\n' && *argument != ' ';
}
