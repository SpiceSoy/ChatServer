//=================================================================================================
// @file CommandExit.cpp
//
// @brief command class of exit server
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandExit.h"
#include "../Constant.h"
#include "../Session.h"

void OJT::ChatCommand::CommandExit::Execute(const Char* argument, Session& session, ChatInformation& information)
{
	session.SendText(CONSTANT::TEXT::GOODBYE_USER);
	session.Close();
}
