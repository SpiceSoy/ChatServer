#include "BaseState.h"
OJT::State::BaseState::BaseState(const ChatCommand::CommandProcessor& processor, const ChatCommand::CommandSet& commandSet)
	: CommandProcessor(processor), CommandSet(commandSet)
{

}

OJT::State::BaseState::BaseState(const ChatCommand::CommandProcessor& processor, ChatCommand::CommandSet&& commandSet)
	: CommandProcessor(processor), CommandSet(std::move(commandSet))
{

}

void OJT::State::BaseState::OnEnter(Session& session, ChatInformation& information)
{
}

void OJT::State::BaseState::OnLineRecived(Session& session, ChatInformation& information, const Char* input)
{
	CommandProcessor.ExecuteCommand(session, information, input, this->CommandSet);
}
