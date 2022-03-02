//=================================================================================================
// @file StateFunction.h
//
// @brief 각 상태에서 수행할 행동을 정의하는 함수 모음집입니다.
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
namespace OJT
{
	struct Session;
	class ChatInformation;
	namespace StateFunction // 상태패턴 클래스로 뽑을까 하다가 그 정도는 아닌 것 같아서 함수로 해결
	{
		void OnWaitLoginStateEnter(Session& session, ChatInformation& information);
		void OnWaitLoginStateReciveLine(Session& session, ChatInformation& information, const Char* input);

		void OnMainMenuStateEnter(Session& session, ChatInformation& information);
		void OnMainMenuStateReciveLine(Session& session, ChatInformation& information, const Char* input);

		void OnChatRoomStateEnter(Session& session, ChatInformation& information);
		void OnChatRoomStateReciveLine(Session& session, ChatInformation& information, const Char* input);
	};
};
