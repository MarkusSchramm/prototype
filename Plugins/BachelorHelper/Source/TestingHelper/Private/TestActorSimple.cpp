/**
* @file TestActorSimple.h
 * @author Markus Schramm
 */

#include "TestActorSimple.h"

// Sets default values
ATestActorSimple::ATestActorSimple() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ATestActorSimple::ATestActorSimple(const FObjectInitializer& ObjectInitializer) {}
ATestActorSimple::~ATestActorSimple() {}

// Called when the game starts or when spawned
void ATestActorSimple::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ATestActorSimple::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

