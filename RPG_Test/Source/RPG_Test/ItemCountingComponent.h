// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemCountingComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FThresholdReached);

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

	UPROPERTY(BlueprintAssignable)
	// This delegate is what owning actors should bind to
	FThresholdReached TriggerDelegate;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Trigger this component when the Number of Items equals the Item Threshold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	bool ThresholdEqualToTrigger = false;

	// Trigger this component when the Number of Items is less than the Item Threshold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	bool ThresholdLessThanTrigger = false;

	// Trigger this component when the Number of Items is greater than the Item Threshold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	bool ThresholdGreaterThanTrigger = false;

	// Number of items before the volume will check for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	int32 ItemThreshold = 1;

	// Number of items currently in the Volume
	UPROPERTY(VisibleAnywhere, Category = "Items")
	int32 NumOfItems = 0;

	UPROPERTY(VisibleAnywhere, Category = "Items")
	TArray<AActor*> OverlappingItems;

	// defualt value SHOULD be None, unless filtering is desired
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TSubclassOf<AActor> OverlappingFilter = nullptr;

	UFUNCTION()
	void OnVolumeOverlap(class AActor* OtherActor, class AActor* Actor);

	UFUNCTION()
	void OnVolumeOverlapEnd(class AActor* OtherActor, class AActor* Actor);

	// This function determines if the threshold trigger delegate should be executed based on the threshold trigger values
	UFUNCTION()
	void OnThresholdTrigger();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
