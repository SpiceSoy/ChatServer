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
#include "State/MenuState.h"
#include "State/LoginState.h"
#include "State/ChatRoomState.h"
#include "State/EmptyState.h"
#include <memory>
#include <algorithm>

OJT::ChatInformation::ChatInformation()
{
	States.emplace_back(std::make_unique<State::MenuState>(CommandProcessor));
	States.emplace_back(std::make_unique<State::LoginState>(CommandProcessor));
	States.emplace_back(std::make_unique<State::ChatRoomState>(CommandProcessor));
	States.emplace_back(std::make_unique<State::EmptyState>(CommandProcessor)); // 더미 / 클로즈
	States.emplace_back(std::make_unique<State::EmptyState>(CommandProcessor)); // 더미 / 엠티
}

void OJT::ChatInformation::SetMaxSessions(UInt32 maxSessions)
{
}
const std::list<std::unique_ptr<OJT::Session>>& OJT::ChatInformation::GetSessions() const
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

Int32 OJT::ChatInformation::GetChatRoomIndex(ChatRoom& room) const
{
	ChatRoom* roomAddr = &room;
	auto it = std::find_if(ChatRooms.begin(), ChatRooms.end(), [roomAddr](auto& a) { return a.get() == roomAddr; });
	auto index = std::distance(ChatRooms.begin(), it);
	return index;
}

const std::vector<std::unique_ptr<OJT::ChatRoom>>& OJT::ChatInformation::GetChatRooms() const
{
	return ChatRooms;
}

void OJT::ChatInformation::SetId(Session& session, const std::string& id)
{
	IdMap.insert(std::make_pair(id, &session));
}

Bool OJT::ChatInformation::HasId(const std::string& id) const
{
	return IdMap.count(id);
}

OJT::Session& OJT::ChatInformation::FindSession(const std::string& id) const
{
	return *IdMap.at(id);
}

const std::map<std::string, OJT::Session*>& OJT::ChatInformation::GetIdMap() const
{
	return IdMap;
}

void OJT::ChatInformation::EraseClosedSessions()
{
	auto it = Sessions.begin();
	std::for_each(it, Sessions.end(), [this](const std::unique_ptr<Session>& a) { if(a.get()->IsClosed()) IdMap.erase(a->GetId()); });
	auto newEnd = std::remove_if(Sessions.begin(), Sessions.end(), [](const std::unique_ptr<Session>& a) {return a.get()->IsClosed(); });
	Sessions.erase(newEnd, Sessions.end());
}

void OJT::ChatInformation::EraseEmptyChatRooms()
{
	auto it = ChatRooms.begin();
	auto newEnd = std::remove_if(ChatRooms.begin(), ChatRooms.end(), [](const std::unique_ptr<ChatRoom>& a) {return a.get()->GetCurrentUserCount() == 0; });
	ChatRooms.erase(newEnd, ChatRooms.end());
}

OJT::State::BaseState* OJT::ChatInformation::GetState(SessionState state) const
{
	Int32 index = static_cast<Int32>(state);
	return States[index].get();
}

OJT::ChatRoom& OJT::ChatInformation::CreateChatRoom(Int32 maxUser, const std::string& title)
{
	ChatRooms.emplace_back(std::make_unique<ChatRoom>(this));
	auto& last = *ChatRooms.back();
	last.SetMaxUser(maxUser);
	last.SetTitle(title);
	return last;
}
