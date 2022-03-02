//=================================================================================================
// @file InfoManager.cpp
//
// @brief Singletone Class of Chat Info(Chat room, user list)
// 
// @date 2022/03/02
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================

#include "InfoManager.h"
#include <memory>
void OJT::InfoManager::SetMaxSessions(UInt32 maxSessions)
{
	Sessions.reserve(maxSessions);
}
std::vector<OJT::Session>& OJT::InfoManager::GetSessions()
{
	return Sessions;
}

OJT::Session& OJT::InfoManager::AddClientSocket(SocketHandle socket)
{
	Sessions.emplace_back(socket);
	return Sessions.back();
}

OJT::InfoManager* OJT::InfoManager::GetInstance()
{
	static std::unique_ptr<InfoManager> instance = nullptr;
	if (instance == nullptr) instance = std::unique_ptr<InfoManager>(new InfoManager());
	return instance.get();
}

const OJT::ChatRoom& OJT::InfoManager::GetChatRoom(Int32 index) const
{
	return ChatRooms.at(index);
}

void OJT::InfoManager::CreateChatRoom(Int32 maxUser, const std::string& title)
{
	ChatRooms.emplace_back();
	auto& last = ChatRooms.back();
	last.SetMaxUser(maxUser);
	last.SetTitle(title);
}
