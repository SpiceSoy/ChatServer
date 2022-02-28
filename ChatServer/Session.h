//=================================================================================================
// @file Session.h
//
// @brief session info struct
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
#include <array>
namespace OJT
{
	struct Session
	{
		Session(SocketHandle socket)
			: Socket(socket), ReadBuffer{ 0, }
		{
		};
		SocketHandle Socket;
		UInt64 RecvBytes = 0;
		std::array<Byte, 512> ReadBuffer;

		UInt64 SendBufferCsr = 0;
		UInt64 SendStartCsr = 0;
		UInt64 SendBytes = 0;
		std::array<Byte, 1024> SendBuffer;
	};
};