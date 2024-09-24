// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Struct.pb.h"
#include "GameFramework/Character.h"
#include "SCharacterBase.generated.h"

class Protocol::PosInfo;

UCLASS()
class UNREALGAME_API ASCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacterBase();
	
	virtual ~ASCharacterBase();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	bool IsOwnerPlayerCharacter();

	Protocol::MoveState GetMoveState() { return CurrentCharacterPosInfo->state(); }
	void SetMoveState(Protocol::MoveState InMoveState);

	Protocol::PosInfo* GetCurrentCharacterPosInfo() { return CurrentCharacterPosInfo; }
	void SetCurrentCharacterPosInfo(Protocol::PosInfo& InPosInfo);

	void SetNextCharacterPosInfo(Protocol::PosInfo& InPosInfo);

protected:
	Protocol::PosInfo* CurrentCharacterPosInfo;
	Protocol::PosInfo* NextCharacterPosInfo;

};
