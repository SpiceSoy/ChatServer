//=================================================================================================
// @file SessionState.h
//
// @brief enum class description for Session State
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================

#pragma once
namespace OJT
{
	enum class SessionState
	{
		EMPTY,
		WAIT_LOGIN,
		MAIN_MENU,
		CHAT_ROOM,
	};
}