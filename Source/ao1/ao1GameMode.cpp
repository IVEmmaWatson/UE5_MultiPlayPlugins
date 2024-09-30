// Copyright Epic Games, Inc. All Rights Reserved.

#include "ao1GameMode.h"
#include "ao1Character.h"
#include "UObject/ConstructorHelpers.h"

Aao1GameMode::Aao1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
