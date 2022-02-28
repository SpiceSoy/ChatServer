//=================================================================================================
// @file NetworkUtill.cpp
//
// @brief utill functions in socket programming
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "NetworkUtill.h"
#include "DataTypes.h"
#include <WinSock2.h>
#include <iostream>
#include <iomanip>

Char* OJT::NetworkUtill::GetErrorMessageString(Int32 err)
{
	Char* msgBuffer = nullptr;
	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&msgBuffer, 0, NULL);
	return msgBuffer;
}

Void OJT::NetworkUtill::PrintErrorMessage(const Char* title, const Char* message)
{
	std::wcout << L"[Error] " << std::setw(10) << title << " : " << message << "\n";
}

Void OJT::NetworkUtill::PrintLastErrorMessage(const Char* title)
{
	int err = WSAGetLastError();
	Char* errMessage = NetworkUtill::GetErrorMessageString(err);
	NetworkUtill::PrintErrorMessage(title, errMessage);
	LocalFree(errMessage);
}
