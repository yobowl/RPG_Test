// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPG_TestHUD.generated.h"

UCLASS()
class ARPG_TestHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARPG_TestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

