//=================================================================================================
// @file StateFunction.h
//
// @brief �� ���¿��� ������ �ൿ�� �����ϴ� �Լ� �������Դϴ�.
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
	namespace StateFunction // �������� Ŭ������ ������ �ϴٰ� �� ������ �ƴ� �� ���Ƽ� �Լ��� �ذ�
	{
		void OnWaitLoginStateEnter(Session& session, ChatInformation& information);
		void OnWaitLoginStateReciveLine(Session& session, ChatInformation& information, const Char* input);

		void OnMainMenuStateEnter(Session& session, ChatInformation& information);
		void OnMainMenuStateReciveLine(Session& session, ChatInformation& information, const Char* input);

		void OnChatRoomStateEnter(Session& session, ChatInformation& information);
		void OnChatRoomStateReciveLine(Session& session, ChatInformation& information, const Char* input);
	};
};
