//=================================================================================================
// @file CommandWhisper.cpp
//
// @brief command class of whisper
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandWhisper.h"
#include "../Constant.h"
#include "../Session.h"
#include "../ChatInformation.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandWhisper::Execute(const Char* argument, Session& session, ChatInformation& information) const
{
	std::stringstream sstream;
	sstream.str(argument);
	std::string id;
	std::string text;
	sstream >> id >> text;
	if (sstream.bad())
	{
		session.SendText(CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
	}
	else if (information.HasId(id))
	{
		sstream.clear();
		Session& targetSession = information.FindSession(id);
		targetSession.SendFormattedText(CONSTANT::FORMAT::WHISPER, session.GetId().c_str(), text.c_str());
	}
	else
	{
		session.SendText(CONSTANT::TEXT::ALERT_NO_ID_USER);
	}
}
