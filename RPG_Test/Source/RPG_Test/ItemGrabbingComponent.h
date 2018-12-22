// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Classes/Engine/World.h"
#include "Components/SceneComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemGrabbingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_TEST_API UItemGrabbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemGrabbingComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics", meta = (AllowPrivateAccess = "true"))
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	//returns HitResult of raytrace (TraceHit)
	FHitResult Grab();

	//returns HitResult of raytrace (TraceHit)
	FHitResult Pickup();

	//releases grabbed objects
	void Release();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Grabbing")
	FHitResult TraceHit;

	UPROPERTY(BlueprintReadWrite, Category = "Grabbing")
	USceneComponent* Camera;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Grabbing")
	float GrabbingDistance = 200;

	FVector CameraLocation;
	FRotator CameraRotation;

	FVector TraceEnd;

	void ObjectRayCast();

	FCollisionQueryParams GrabbingParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());




};
