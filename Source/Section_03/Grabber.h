// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_03_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitComponents();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DebugLine(FVector &LineEndVector);

private:
	UPROPERTY(EditAnywhere)
	float ReachLength = 200.f;
	bool bIsDebuggingEnabled = false;

	FVector OUT PlayerViewPointLocation;
	FRotator OUT PlayerViewPointRotation;
	FHitResult OUT LineTraceHit;

	FVector LineEndVector;

	AActor* AActorPlayer = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	void GrabAction();
	void ReleaseAction();

	const FHitResult GetFirstPhysicsBody();
};