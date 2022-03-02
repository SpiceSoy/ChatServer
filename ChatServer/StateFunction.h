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
	namespace StateFunction // �������� Ŭ������ ������ �ϴٰ� �� ������ �ƴ� �� ���Ƽ� �Լ��� �ذ�
	{
		void OnWaitLoginStateEnter(Session& session);
		void OnWaitLoginStateReciveLine(Session& session, const Char* input);

		void OnMainMenuStateEnter(Session& session);
		void OnMainMenuStateReciveLine(Session& session, const Char* input);

		void OnChatRoomStateEnter(Session& session);
		void OnChatRoomStateReciveLine(Session& session, const Char* input);
	};
};
