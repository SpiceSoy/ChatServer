//=================================================================================================
// @file StringUtill.h
//
// @brief utill functions for text
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "DataTypes.h"
#include <string>
namespace OJT
{
	namespace StringUtill
	{
		Bool SplitString( const std::string& input, std::string& left, std::string& right );
		Bool ValidText( const Char* input);
		Bool ValidText( const std::string& input );
	};
}