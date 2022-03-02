//=================================================================================================
// @file ChatRoom.cpp
//
// @brief chat room class
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "ChatRoom.h"
#include <string>
#include <vector>


const std::string& OJT::ChatRoom::GetTitle() const
{
	return Title;
}

void OJT::ChatRoom::SetTitle(const std::string& title)
{
	Title = title;
}

Int32 OJT::ChatRoom::GetMaxUser() const
{
	return MaxUser;
}

void OJT::ChatRoom::SetMaxUser(Int32 maxUser)
{
	MaxUser = maxUser;
}

Int32 OJT::ChatRoom::GetCurrentUserCount() const
{
	return Sessions.size();
}

void OJT::ChatRoom::EnterUser(UInt32 sessionIndex)
{
	Sessions.emplace(sessionIndex);
}

void OJT::ChatRoom::ExitUser(UInt32 sessionIndex)
{
	Sessions.erase(sessionIndex);
}
