// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EsnePlayerController.h"
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

	// set default hud class
	static ConstructorHelpers::FClassFinder<AEsneHUD> HudBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_EsneHUD"));
	if (HudBPClass.Class != NULL)
	{
		HUDClass = HudBPClass.Class;
	}
    
    PlayerControllerClass = AEsnePlayerController::StaticClass();
    
}
