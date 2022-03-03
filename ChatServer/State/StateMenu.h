//=================================================================================================
// @file MenuState.h
//
// @brief state class of menu
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
		class StateMenu : public BaseState
		{
		public:
			StateMenu( const ChatCommand::CommandProcessor& processor );
			virtual ~StateMenu() = default;
			virtual void OnEnter( Session& session, ChatInformation& information ) override;
		};
	};
};
