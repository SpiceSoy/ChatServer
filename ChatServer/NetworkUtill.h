//=================================================================================================
// @file NetworkUtilll.h
//
// @brief utill functions in socket programming
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
namespace OJT
{
	namespace NetworkUtill
	{
		Char* GetErrorMessageString(Int32 err);
		Void PrintErrorMessage(const Char* title, const Char* message);
		Void PrintLastErrorMessage(const Char* title);

	};
}