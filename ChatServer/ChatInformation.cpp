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
#include <algorithm>

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

void OJT::ChatInformation::SetId(Session& session, const std::string& id)
{
	Int32 index = std::distance(Sessions.data(), &session);
	IdMap.insert(std::make_pair(id, index));
}

Bool OJT::ChatInformation::HasId(const std::string& id) const
{
	return IdMap.count(id);
}

const std::map<std::string, Int32>& OJT::ChatInformation::GetIdMap() const
{
	return IdMap;
}

void OJT::ChatInformation::CreateChatRoom(Int32 maxUser, const std::string& title)
{
	ChatRooms.emplace_back();
	auto& last = ChatRooms.back();
	last.SetMaxUser(maxUser);
	last.SetTitle(title);
}
