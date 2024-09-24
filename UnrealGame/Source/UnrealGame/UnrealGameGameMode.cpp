// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealGameGameMode.h"
#include "UnrealGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealGameGameMode::AUnrealGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
