// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacterBase.h"

#include "SPlayerCharacter.h"

ASCharacterBase::ASCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

ASCharacterBase::~ASCharacterBase()
{
}

void ASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASCharacterBase::IsOwnerPlayerCharacter()
{
	return Cast<ASPlayerCharacter>(this) != nullptr;
}

void ASCharacterBase::SetMoveState(Protocol::MoveState InMoveState)
{
	if (CurrentCharacterPosInfo->state() == InMoveState)
	{
		return;		
	}

	CurrentCharacterPosInfo->set_state(InMoveState);
}

void ASCharacterBase::SetCurrentCharacterPosInfo(Protocol::PosInfo& InPosInfo)
{
	if (CurrentCharacterPosInfo->object_id() != 0)
	{
		assert(CurrentCharacterPosInfo->object_id() == InPosInfo.object_id());
	}

	CurrentCharacterPosInfo->CopyFrom(InPosInfo);

	FVector Location(InPosInfo.x(), InPosInfo.y(), InPosInfo.z());
	SetActorLocation(Location);
}

void ASCharacterBase::SetNextCharacterPosInfo(Protocol::PosInfo& InPosInfo)
{
	if (CurrentCharacterPosInfo->object_id() != 0)
	{
		assert(CurrentCharacterPosInfo->object_id() == InPosInfo.object_id());
	}

	NextCharacterPosInfo->CopyFrom(InPosInfo);

	SetMoveState(InPosInfo.state());
}
