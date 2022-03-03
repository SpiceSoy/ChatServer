//=================================================================================================
// @file StateEmpty.h
//
// @brief dummy State class of wrong argument
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
		class StateEmpty : public BaseState
		{
		public:
			StateEmpty( const ChatCommand::CommandProcessor& processor );
			virtual ~StateEmpty() = default;
			virtual void OnEnter( Session& session, ChatInformation& information ) override;
		};
	};
};
