/**
 * @file AudioPawnFlying.cpp
 * @author Markus Schramm
 */


#include "Actors/AudioPawnFlying.h"

#include "Builders/CubeBuilder.h"
#include "Components/AudioPawnFlyingComponent.h"
#include "GeometryCollection/GeometryCollectionUtility.h"

AAudioPawnFlying::AAudioPawnFlying() {
	GetMeshComponent()->SetSimulatePhysics(true);
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioPawnFlyingComponent>(TEXT("Flying Audio"));
	AudioComponent->SetupAttachment(RootComponent);
}

AAudioPawnFlying::AAudioPawnFlying(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {
	GetMeshComponent()->SetSimulatePhysics(true);
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioPawnFlyingComponent>(TEXT("Flying Audio"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AAudioPawnFlying::BeginPlay() {
	Super::BeginPlay();
	
}

void AAudioPawnFlying::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

