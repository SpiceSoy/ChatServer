//=================================================================================================
// @file CommandPlsLoginhisper.cpp
//
// @brief command class of alert login
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "../Command/CommandPlsLogin.h"
#include "../Constant.h"
#include "../Session.h"
#include "../ChatInformation.h"
#include <sstream>
#include <string>

void OJT::ChatCommand::CommandPlsLogin::Execute(const Char* argument, Session& session, ChatInformation& information) const
{
	session.SendText(CONSTANT::TEXT::PLS_LOGIN);
}
