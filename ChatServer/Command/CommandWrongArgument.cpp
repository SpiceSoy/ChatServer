//=================================================================================================
// @file CommandWrongArgument.cpp
//
// @brief dummy command class of wrong argument
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandWrongArgument.h"
#include "../Constant.h"
#include "../Session.h"

void OJT::ChatCommand::CommandWrongArgument::Execute(const Char* argument, Session& session, ChatInformation& information) const
{
	session.SendText(CONSTANT::TEXT::ALERT_ARGUMENT_WRONG);
}
