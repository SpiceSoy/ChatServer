
#include "EmptyState.h"
#include "../Session.h"
#include "../Constant.h"
#include "../Command/CommandSet.h"
#include "../Command/CommandElement.h"

using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::EmptyState::EmptyState(const ChatCommand::CommandProcessor& processor)
	:BaseState(processor,
		ChatCommand::CommandSet(
			ECommand::PlsCommand,
			ECommand::WrongArgument,
			{
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::MENU_EXIT,		false,	OJT::ChatCommand::ECommand::Exit},
			}
			))
{
}
void OJT::State::EmptyState::OnEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::HELP_OR_EXIT, CONSTANT::COMMAND::MENU_HELP, CONSTANT::COMMAND::MENU_EXIT);
}
