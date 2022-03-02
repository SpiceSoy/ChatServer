//=================================================================================================
// @file ChatInformation.cpp
//
// @brief Singletone Class of Chat Info(Chat room, user list)
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================

#include "ChatInformation.h"
#include <memory>
void OJT::ChatInformation::SetMaxSessions(UInt32 maxSessions)
{
	Sessions.reserve(maxSessions);
}
std::vector<OJT::Session>& OJT::ChatInformation::GetSessions()
{
	return Sessions;
}

OJT::Session& OJT::ChatInformation::AddClientSocket(SocketHandle socket)
{
	Sessions.emplace_back(socket, this);
	auto& result = Sessions.back();
	return Sessions.back();
}

const OJT::ChatRoom& OJT::ChatInformation::GetChatRoom(Int32 index) const
{
	return ChatRooms.at(index);
}

void OJT::ChatInformation::CreateChatRoom(Int32 maxUser, const std::string& title)
{
	ChatRooms.emplace_back();
	auto& last = ChatRooms.back();
	last.SetMaxUser(maxUser);
	last.SetTitle(title);
}
