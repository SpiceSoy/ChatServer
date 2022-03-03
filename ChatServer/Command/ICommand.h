//=================================================================================================
// @file ICommand.h
//
// @brief interface of commands (H, Q, LOGIN, etc..)
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
namespace OJT
{
	class Session;
	class ChatInformation;
	namespace ChatCommand
	{
		class ICommand
		{
		public:
			ICommand() = default;
			virtual ~ICommand() = default;
			virtual void Execute( const Char* argument, Session& session, ChatInformation& information ) const = 0;
		};
	};
};
