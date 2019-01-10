// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG_Test/RPG_TestCharacter.h"
#include "CoreMinimal.h"
#include "Item.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class RPG_TEST_API AHealthPotion : public AItem
{
	GENERATED_BODY()
	
public:

	void UseItem(TSubclassOf<ARPG_TestCharacter> Target);

	UPROPERTY(EditDefaultsOnly)
	int32 HealAmount = 10;


};
