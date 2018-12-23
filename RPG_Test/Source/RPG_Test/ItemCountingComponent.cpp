// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemCountingComponent.h"

// Sets default values for this component's properties
UItemCountingComponent::UItemCountingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemCountingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemCountingVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("Item Counting Volume not valid on %s"), *GetOwner()->GetName());
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Adding delegate to volume"));

	ItemCountingVolume->OnActorBeginOverlap.AddDynamic(this, &UItemCountingComponent::OnVolumeOverlap);
	ItemCountingVolume->OnActorEndOverlap.AddDynamic(this, &UItemCountingComponent::OnVolumeOverlap);

}


// Called every frame
void UItemCountingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UItemCountingComponent::OnVolumeOverlap(AActor* OtherActor, AActor* Actor)
{

	ItemCountingVolume->GetOverlappingActors(OverlappingItems, OverlappingFilter); //Second Parameter can be used as a filter to return aactors MATCHING the filter

	NumOfItems = OverlappingItems.Num();	//TODO make this also include counts of item stacks, possibly by creating new TArray function

	OnThresholdTrigger();

}

void UItemCountingComponent::OnVolumeOverlapEnd(AActor * OtherActor, AActor * Actor)
{

	ItemCountingVolume->GetOverlappingActors(OverlappingItems, OverlappingFilter);	//Second Parameter can be used as a filter to return aactors MATCHING the filter

	NumOfItems = OverlappingItems.Num();

	OnThresholdTrigger();

}

// Determines if the 'Trigger' for this component should 'fire' and tells Actors they have binded an action to the delegate
void UItemCountingComponent::OnThresholdTrigger()
{
	if (NumOfItems < ItemThreshold && ThresholdLessThanTrigger)
	{
		TriggerDelegate.Broadcast();
		return;
	}

	if (NumOfItems == ItemThreshold && ThresholdEqualToTrigger)
	{
		TriggerDelegate.Broadcast();
		return;
	}

	if (NumOfItems > ItemThreshold && ThresholdGreaterThanTrigger)
	{
		TriggerDelegate.Broadcast();
		return;
	}

}
