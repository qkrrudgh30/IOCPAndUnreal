// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealGame.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, UnrealGame, "UnrealGame" );

USSendBuffer::USSendBuffer(int32 InBufferSize)
{
	Buffer.SetNum(InBufferSize);
}

USSendBuffer::~USSendBuffer()
{
}

void USSendBuffer::CopyData(void* InData, int32 InLength)
{
	::memcpy(Buffer.GetData(), InData, InLength);
	WriteSize = InLength;
}

void USSendBuffer::Close(uint32 InWriteSize)
{
	WriteSize = InWriteSize;
}
