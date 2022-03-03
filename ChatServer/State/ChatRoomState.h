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
		class ChatRoomState : public BaseState
		{
		public:
			ChatRoomState(const ChatCommand::CommandProcessor& processor);
			virtual ~ChatRoomState() = default;
			virtual void OnEnter(Session& session, ChatInformation& information) override;
		};
	};
};