// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGrabbingComponent.h"


// Sets default values for this component's properties
UItemGrabbingComponent::UItemGrabbingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Create Physics Handle which implements "grabbing"
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle_Component"));
}


// Called when the game starts
void UItemGrabbingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemGrabbingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	ObjectRayCast();
	
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(TraceEnd);
	}

	// ...
}

//Ray-Traces for objects within Grabbing Distance
void UItemGrabbingComponent::ObjectRayCast()
{

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	TraceEnd = CameraLocation + CameraRotation.Vector()*GrabbingDistance;

	//DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Red, false, -1.f, uint8(000),10.f);
	//UE_LOG(LogTemp,Warning,TEXT("Location: %s,   Rotation: %s"), *CameraLocation.ToString(), *CameraRotation.ToString())

	//GetWorld()->LineTraceSingleByChannel(TraceHit, CameraLocation, TraceEnd, ECollisionChannel::ECC_Visibility);
	GetWorld()->LineTraceSingleByObjectType(TraceHit, CameraLocation, TraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), GrabbingParams);
	

}

//Grabs an object to be able to move it
FHitResult UItemGrabbingComponent::Grab()
{

	if (!TraceHit.Actor.IsValid()) { return TraceHit; }

	PhysicsHandle->GrabComponent(TraceHit.GetComponent(), NAME_None, TraceHit.GetActor()->GetActorLocation(), false);

	return TraceHit;


}


FHitResult UItemGrabbingComponent::Pickup()
{


	return TraceHit;
}


void UItemGrabbingComponent::Release()
{

	if (PhysicsHandle->GrabbedComponent) { PhysicsHandle->ReleaseComponent(); }

}