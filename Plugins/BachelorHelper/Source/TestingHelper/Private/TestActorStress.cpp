/**
 * @file TestActorStress.cpp
 * @author Markus Schramm
 */

#include "TestActorStress.h"
#include "TestingHelperModule.h"

ATestActorStress::ATestActorStress()
	: Iterations(100), MovementRadius(0.f), MovementSpeed(0.f) {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::Constructor");
		PrimaryActorTick.bCanEverTick = true;
		MovementRadius = FMath::RandRange(100.f, 10000.f);
		MovementSpeed = FMath::RandRange(0.1f, 10.f);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::Constructor.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s' constructed"), *GetName());
		UE_LOG(LogTestingHelper, Log, TEXT("INITIAL VALUES"));
		UE_LOG(LogTestingHelper, Log, TEXT("Iterations:\t%d"), Iterations);
		UE_LOG(LogTestingHelper, Log, TEXT("Radius:\t%f"), MovementRadius);
		UE_LOG(LogTestingHelper, Log, TEXT("Speed:\t%f"), MovementSpeed);
	}
}

ATestActorStress::ATestActorStress(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Iterations(100), MovementRadius(0.f), MovementSpeed(0.f) {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStressWithObjInt::Constructor");
		PrimaryActorTick.bCanEverTick = true;
		MovementRadius = FMath::RandRange(100.f, 10000.f);
		MovementSpeed = FMath::RandRange(0.1f, 10.f);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStressWithObjInt::Constructor.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s'WithObjInt constructed"), *GetName());
		UE_LOG(LogTestingHelper, Log, TEXT("INITIAL VALUES"));
		UE_LOG(LogTestingHelper, Log, TEXT("Iterations:\t%d"), Iterations);
		UE_LOG(LogTestingHelper, Log, TEXT("Radius:\t%f"), MovementRadius);
		UE_LOG(LogTestingHelper, Log, TEXT("Speed:\t%f"), MovementSpeed);
	}
}

ATestActorStress::~ATestActorStress() {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::Destructor");
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::Destructor.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s' destructed"), *GetName());
	}
}

void ATestActorStress::BeginPlay() {
	Super::BeginPlay();
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::BeginPlay");
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::BeginPlay.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s' begun play"), *GetName());
	}
}

void ATestActorStress::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::Tick");
		for (uint32 i = 0; i < Iterations; i++) {
			// expensive location calculation
			const float X = FMath::Sin(GetGameTimeSinceCreation() * MovementSpeed) * MovementRadius;
			const float Y = FMath::Cos(GetGameTimeSinceCreation() * MovementSpeed) * MovementRadius;
			FVector NewLocation(X, Y, GetActorLocation().Z);
			SetActorLocation(NewLocation);

			// dummy physics
			FVector Gravity(0, 0, -980.0f);
			FVector Velocity = GetVelocity() + Gravity * DeltaTime;
			float Friction = 0.98f;
			Velocity *= Friction;
		}
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Tick.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s' ticked"), *GetName());
	}
}

uint32 ATestActorStress::GetIterations() const {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::GetIterations.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s' iterations (%d) ordered"), *GetName(), Iterations);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::GetIterations");
		return Iterations;
	}
}

bool ATestActorStress::SetIterations(uint32 NewIterations) const {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::SetIterations.Log");
		UE_LOG(
			LogTestingHelper,
			Log,
			TEXT("'%s' set iterations to %d (Before: %d)"), *GetName(), NewIterations, Iterations
			);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorStress::SetIterations");
		if (NewIterations == 0xFFFFFFFF) {
			UE_LOG(LogTestingHelper, Error, TEXT("Overflow-Error on 'uint32 NewIterations'"));
			return false;
		}
		Iterations = NewIterations;
		return true;
	}
}