// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EsneGameMode.h"
#include "EsneCharacter.h"
#include "EsneHUD.h"
#include "UObject/ConstructorHelpers.h"

AEsneGameMode::AEsneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    static ConstructorHelpers::FClassFinder<AEsneHUD> HudBPClass(TEXT("/Game/ThirdPerson/Blueprints/EsneHUD_BP"));
    if (HudBPClass.Class != NULL)
    {
        HUDClass = HudBPClass.Class;
    }
}
