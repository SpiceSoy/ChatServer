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
#include "../DataTypes.h" // �̰� �����η� ��� �ٲٴ��� �����
namespace OJT
{
	class Session;
	class ChatInformation;
	namespace ChatCommand
	{
		class ICommand
		{
		public:
			virtual void Execute(const Char* argument, Session& session, ChatInformation& information) = 0;
		};
	};
};
