//=================================================================================================
// @file Session.cpp
//
// @brief session info struct
// 
// @date 2022/02/28
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Session.h"
#include "ChatInformation.h"
#include "NetworkUtill.h"
#include "Constant.h"
#include <WinSock2.h>
#include <iostream>
#include <array>

OJT::Session::Session( SocketHandle socket, ChatInformation* information )
	: Socket( socket ), Information( information ), Port( 0 )
{
	ReadBuffer.resize( 1024 );
	SendBuffer.resize( 1024 );
};
SocketHandle OJT::Session::GetSocket() const
{
	return Socket;
}

Bool OJT::Session::HasSendBytes() const
{
	return SendBytes;
}

void OJT::Session::SetState( ESessionState state )
{
	State = Information->GetState( state );
	if ( State != nullptr ) State->OnEnter( *this, *Information );
}

void OJT::Session::ProcessSend()
{
	Int32 sentBytes = send( Socket, (const char*)SendBuffer.data(), SendBytes, 0 );
	if ( sentBytes == SOCKET_ERROR )
	{
		NetworkUtill::PrintLastErrorMessage( "send", __FILE__, __LINE__ );
		Close();
	}
	else
	{
		//메모리 땡기기
		memcpy_s( SendBuffer.data(), SendBytes - sentBytes, SendBuffer.data() + sentBytes, SendBytes - sentBytes );
		SendBytes -= sentBytes;
	}
}

void OJT::Session::ProcessReceive()
{
	// 이름 겹쳐서 로컬변수 전문 작성
	Int32 receivedBytes = recv( Socket, ( (char*)ReadBuffer.data() ) + RecvBytes, ReadBuffer.size() * sizeof( Byte ), 0);
	Char* expectEnd = reinterpret_cast<Char*>( ReadBuffer.data() + RecvBytes + receivedBytes - 1 );
	if ( receivedBytes == 0 || receivedBytes == SOCKET_ERROR )
	{
		Close();
	}
	else
	{
		{
			//RecvBytes += receivedBytes;
			Byte* csrBegin = ReadBuffer.data();
			Byte* csr = ReadBuffer.data() + RecvBytes;
			Byte* csrEnd = ReadBuffer.data() + RecvBytes + receivedBytes;

			while (csr != csrEnd)
			{
				if (*csr == '\0' && csr != csrBegin)
				{
					OnLineReceived(reinterpret_cast<const Char*>(csrBegin));
					csr++;
					csrBegin = csr;
				}
				else if (*csr == '\n')
				{
					*csr = '\0';
					if (csr != ReadBuffer.data() && *(csr - 1) == '\r') *(csr - 1) = '\0';
					OnLineReceived(reinterpret_cast<const Char*>(csrBegin));
					csr++;
					csrBegin = csr;
				}
				else if (*csr == '\b')
				{
					if (RecvBytes != 0 && csr != csrBegin)
					{
						RecvBytes -= 1;
						memcpy_s(csr - 1, csrEnd - csr + 1, csr + 1, csrEnd - csr + 1);
						csrEnd -= 1;
					}
				}
				else
				{
					csr++;
				}
			}
			if(csrBegin != csrEnd)
			{
				memcpy_s(ReadBuffer.data(), csrEnd - csrBegin, csrBegin, csrEnd - csrBegin);
				RecvBytes = csrEnd - csrBegin;
			}
			else
			{ 
				RecvBytes = 0;
			}
		}

	}
}

void OJT::Session::SendText( const Char* message )
{
	SendByte( reinterpret_cast<const Byte*>( message ), strlen( message ) * sizeof( Char ) );
}

void OJT::Session::SendFormattedText( const Char* fmt, ... )
{
	std::array<Char, 2048> buffer;
	va_list va;
	va_start( va, fmt );
	vsprintf_s( buffer.data(), 2048, fmt, va );
	SendText( buffer.data() );
	va_end( va );
}

void OJT::Session::Close()
{
	if ( Socket == 0 ) return;
	closesocket( this->Socket );
	if ( Room != nullptr ) Room->ExitUser( *this );
	SetState( ESessionState::Closed );
}

const std::string& OJT::Session::GetId() const
{
	return Id;
}

const std::string& OJT::Session::GetAddress() const
{
	return AddressText;
}

UInt16 OJT::Session::GetPort() const
{
	return Port;
}

OJT::ChatRoom* OJT::Session::GetChatRoom() const
{
	return Room;
}

Bool OJT::Session::IsClosed() const
{
	return State == Information->GetState( ESessionState::Closed );
}

void OJT::Session::SetId( const Char* name )
{
	Id = name;
}

void OJT::Session::SetChatRoom( ChatRoom* room )
{
	Room = room;
}

void OJT::Session::SetAddress( const Char* address, UInt16 port )
{
	AddressText = address;
	Port = port;
}

void OJT::Session::SendByte( const Byte* data, UInt64 size )
{
	if ( IsClosed() ) return;
	bool willOver = SendBytes + size > SendBuffer.size();
	if ( willOver ) SendBuffer.resize( SendBuffer.size() * 2 );
	memcpy_s( SendBuffer.data() + SendBytes, size, data, size );
	SendBytes += size;
}

void OJT::Session::LogInput( const Char* input ) const
{
	printf_s( OJT::CONSTANT::FORMAT::SERVER_SIDE_USER_LOG, AddressText.c_str(), Port, Id.c_str(), input );
}


void OJT::Session::OnLineReceived( const Char* input )
{
	LogInput( input );
	if ( State != nullptr ) State->OnLineReceived( *this, *Information, input );
}
