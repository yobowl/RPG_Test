// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPotion.h"

void AHealthPotion::UseItem(TSubclassOf<ARPG_TestCharacter> Target)
{
	if (!Target) { return; }

	Cast<ARPG_TestCharacter>(Target)->AddHealth(HealAmount);

}