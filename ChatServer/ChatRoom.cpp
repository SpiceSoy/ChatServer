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
#include "ChatInformation.h"
#include <string>
#include <vector>


OJT::ChatRoom::ChatRoom(ChatInformation* information)
	: Information(information), CreatedTime(std::chrono::system_clock::now()), MaxUser(2)
{
}

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

const std::set<OJT::Session*>& OJT::ChatRoom::GetSessions() const
{
	return Sessions;
}

std::chrono::system_clock::time_point OJT::ChatRoom::GetEntryTime(const Session& session) const
{
	return EntryTime.at(&session);
}

std::chrono::system_clock::time_point OJT::ChatRoom::GetCreatedTime() const
{
	return CreatedTime;
}

Int32 OJT::ChatRoom::GetCurrentUserCount() const
{
	return Sessions.size();
}

void OJT::ChatRoom::EnterUser(Session& session)
{
	Sessions.emplace(&session);
	EntryTime.insert(std::make_pair(&session, std::chrono::system_clock::now()));
}

void OJT::ChatRoom::ExitUser(Session& session)
{
	Sessions.erase(&session);
}

void OJT::ChatRoom::BroadCastText(const Char* text)
{
	for (Session* session : Sessions)
	{
		session->SendText(text);
	}
}

