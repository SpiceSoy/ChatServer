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
const std::vector<std::unique_ptr<OJT::Session>>& OJT::ChatInformation::GetSessions()
{
	return Sessions;
}

OJT::Session& OJT::ChatInformation::AddClientSocket(SocketHandle socket)
{
	Sessions.emplace_back(std::make_unique<Session>(socket, this));
	auto& result = *Sessions.back();
	return result;
}

Bool OJT::ChatInformation::HasChatRoom(Int32 index) const
{
	return index >= 0  && index < ChatRooms.size();
}

OJT::ChatRoom& OJT::ChatInformation::GetChatRoom(Int32 index) const
{
	return *ChatRooms.at(index);
}

void OJT::ChatInformation::SetId(Session& session, const std::string& id)
{
	IdMap.insert(std::make_pair(id, &session));
}

Bool OJT::ChatInformation::HasId(const std::string& id) const
{
	return IdMap.count(id);
}

const std::map<std::string, OJT::Session*>& OJT::ChatInformation::GetIdMap() const
{
	return IdMap;
}

OJT::ChatRoom& OJT::ChatInformation::CreateChatRoom(Int32 maxUser, const std::string& title)
{
	ChatRooms.emplace_back(std::make_unique<ChatRoom>(this));
	auto& last = *ChatRooms.back();
	last.SetMaxUser(maxUser);
	last.SetTitle(title);
	return last;
}
