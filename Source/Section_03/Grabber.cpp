// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	AActorPlayer = GetWorld()->GetFirstPlayerController();
	InitComponents();



}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (AActorPlayer != NULL) {
		AActorPlayer->GetActorEyesViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	}

	///DEBUG
	LineEndVector = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachLength;
	DebugLine(LineEndVector);

	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineEndVector);
	}


}

void UGrabber::InitComponents()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("GrabAction", IE_Pressed, this, &UGrabber::GrabAction);
		InputComponent->BindAction("ReleaseAction", IE_Pressed, this, &UGrabber::ReleaseAction);
	}
}

void UGrabber::GrabAction() {

	auto HitResult = GetFirstPhysicsBody();
	auto ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor()) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::ReleaseAction(){
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->ReleaseComponent();
	}
}

const FHitResult UGrabber::GetFirstPhysicsBody()
{
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		PlayerViewPointLocation,
		LineEndVector,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return LineTraceHit;
}

//debugging line to show reach
void UGrabber::DebugLine(FVector &LineEndVector)
{
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineEndVector,
		FColor(255, 255, 0, 100),
		false,
		0.f,
		10.f,
		2.f
	);
}

