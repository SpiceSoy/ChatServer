//=================================================================================================
// @file StringUtill.cpp
//
// @brief utill functions for text
// 
// @date 2022/03/03
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "StringUtill.h"

Bool OJT::StringUtill::SplitString( const std::string& text, std::string& left, std::string& right )
{
	UInt64 spaceIndex = text.find_first_of( ' ' );
	left = text.substr(0,  spaceIndex );
	if( spaceIndex != text.npos ) right = text.substr( spaceIndex + 1, text.length() - (spaceIndex + 1) );
	return right.length() != 0;
}

Bool OJT::StringUtill::ValidText( const Char* input )
{
	return input != nullptr && *input != '\0' && *input != '\n' && *input != ' ';
}

Bool OJT::StringUtill::ValidText( const std::string& input )
{
	return input.length() != 0 && input[ 0 ] != '\0' && input[ 0 ] != '\n' && input[ 0 ] != ' ';
}
