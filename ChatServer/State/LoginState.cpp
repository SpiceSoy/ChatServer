#include "LoginState.h"
#include "../Session.h"
#include "../Constant.h"
#include "../Command/CommandSet.h"
#include "../Command/CommandElement.h"

using OJT::ChatCommand::ECommand;
using namespace OJT::CONSTANT;
OJT::State::LoginState::LoginState(const ChatCommand::CommandProcessor& processor)\
	:BaseState(processor,
		ChatCommand::CommandSet(
			ECommand::PlsLogin,
			ECommand::WrongArgument,
			{
				ChatCommand::CommandElement{OJT::CONSTANT::COMMAND::LOGIN, true,	OJT::ChatCommand::ECommand::Login},
			}
			))
{

}

void OJT::State::LoginState::OnEnter(Session& session, ChatInformation& information)
{
	session.SendFormattedText(CONSTANT::FORMAT::WELCOME, CONSTANT::VALUE::VERSION);
	session.SendText(CONSTANT::TEXT::PLS_LOGIN);
}
