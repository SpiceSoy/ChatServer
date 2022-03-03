//=================================================================================================
// @file CommandPlsLogin.h
//
// @brief command class of alert login
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/ICommand.h"
namespace OJT
{
	namespace ChatCommand
	{
		class CommandPlsLogin : public ICommand
		{
		public:
			virtual void Execute ( const Char* argument, Session& session, ChatInformation& information ) const override;
		};
	};
};