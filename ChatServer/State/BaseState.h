//=================================================================================================
// @file IState.h
//
// @brief dummy command class of wrong argument
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "../DataTypes.h"
#include "../State/BaseState.h"
#include "../Command/CommandSet.h"
#include "../Command/CommandProcessor.h"
namespace OJT
{
	class Session;
	class ChatInformation;
	namespace State
	{
		class BaseState
		{
		public:
			BaseState(const ChatCommand::CommandProcessor& processor, const ChatCommand::CommandSet& commandSet);
			BaseState(const ChatCommand::CommandProcessor&, ChatCommand::CommandSet&& commandSet);
			virtual ~BaseState() = default;
			virtual void OnEnter(Session& session, ChatInformation& information);
			virtual void OnLineRecived(Session& session, ChatInformation& information, const Char* input);
		protected:
			ChatCommand::CommandSet CommandSet;
			const ChatCommand::CommandProcessor& CommandProcessor;
		};
	};
};
