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

#define PrintLastErrorMessageInFile(title)  OJT::NetworkUtill::PrintLastErrorMessage(title, __FILE__, __LINE__)
namespace OJT
{
	namespace NetworkUtill // TODO: 정적 클래스로 쓸지, 네임스페이스 전역함수로 쓸지 물어보기 (후자의 경우 폴더 수정 필요)
	{
		Char* GetErrorMessageString( Int32 err );
		Void PrintErrorMessage( const Char* title, const Char* message, const Char* file, Int32 line );
		Void PrintLastErrorMessage( const Char* title, const Char* file, Int32 line );

	};
}