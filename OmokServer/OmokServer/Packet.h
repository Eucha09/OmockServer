﻿#pragma once

#include "PacketID.h"
#include "ErrorCode.h"

#pragma pack(push, 1)
struct PktHeader
{
	short TotalSize;
	short Id;
	unsigned char Reserve;
};

struct PktBase
{
	short ErrorCode = (short)ERROR_CODE::NONE;
	void SetError(ERROR_CODE error) { ErrorCode = (short)error; }
};

// 패킷은 여기다 정의, 그리고 PacketID.h에 ID(상수값) 지정

//- 로그인 요청
const int MAX_USER_ID_SIZE = 16;
const int MAX_USER_PASSWORD_SIZE = 16;
struct PktLogInReq
{
	char szID[MAX_USER_ID_SIZE] = { 0, };
	char szPW[MAX_USER_PASSWORD_SIZE] = { 0, };
};

struct PktLogInRes : PktBase
{
};

//- 룸에 들어가기 요청
const int MAX_ROOM_TITLE_SIZE = 16;
struct PktRoomEnterReq
{
	//bool IsCreate;
	short RoomIndex;
};

const int MAX_ROOM_USER_COUNT = 4;
struct PktRoomEnterRes : PktBase
{
	unsigned char UserCount = 0;
	char UserIDList[MAX_USER_ID_SIZE * MAX_ROOM_USER_COUNT] = { 0, };
};

//- 룸에 있는 유저에게 새로 들어온 유저 정보 통보
struct PktRoomEnterUserInfoNtf
{
	unsigned char UserID_len;
	char UserID[MAX_USER_ID_SIZE] = { 0, };
};

//- 룸 나가기 요청
struct PktRoomLeaveReq {};

struct PktRoomLeaveRes : PktBase
{
};

//- 룸에서 나가는 유저 통보
struct PktRoomLeaveUserInfoNtf
{
	unsigned char UserID_len;
	char UserID[MAX_USER_ID_SIZE] = { 0, };
};

//- 룸 채팅
const int MAX_ROOM_CHAT_MSG_SIZE = 256;
struct PktRoomChatReq
{
	short Msg_len;
	wchar_t Msg[MAX_ROOM_CHAT_MSG_SIZE] = { 0, };
};

struct PktRoomChatRes : PktBase
{
};

struct PktRoomChatNtf
{
	unsigned char UserID_len;
	char UserID[MAX_USER_ID_SIZE] = { 0, };
	short Mag_len;
	wchar_t Msg[MAX_ROOM_CHAT_MSG_SIZE] = { 0, };
};
#pragma pack(pop)