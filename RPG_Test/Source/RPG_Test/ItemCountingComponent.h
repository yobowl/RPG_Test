// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemCountingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_TEST_API UItemCountingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemCountingComponent();

	// Volume which this component references to check for items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume")
	ATriggerVolume* ItemCountingVolume = nullptr;

	UFUNCTION()
	void OnVolumeOverlap(class AActor* OtherActor, class AActor* Actor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Number of items before the volume will check for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threshold Count")
	int32 ItemThreshold = 1;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
