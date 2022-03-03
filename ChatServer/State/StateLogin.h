//=================================================================================================
// @file StateLogin.h
//
// @brief state class of login
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "State/BaseState.h"
#include "Command/CommandSet.h"
#include "Command/CommandProcessor.h"
#include "DataTypes.h"
namespace OJT
{
	class Session;
	class ChatInformation;
	namespace State
	{
		class StateLogin : public BaseState
		{
		public:
			StateLogin( const ChatCommand::CommandProcessor& processor );
			virtual ~StateLogin() = default;
			virtual void OnEnter( Session& session, ChatInformation& information ) override;
		};
	};
};
