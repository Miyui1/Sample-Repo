// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TrialAndErrorCPPGameMode.h"
#include "TrialAndErrorCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATrialAndErrorCPPGameMode::ATrialAndErrorCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DemoContent/ThirdPersonCPP/Blueprints/MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
