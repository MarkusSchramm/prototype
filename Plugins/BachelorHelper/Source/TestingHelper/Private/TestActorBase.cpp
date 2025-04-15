/**
 * @file TestActorBase.cpp
 * @author Markus Schramm
 */

#include "TestActorBase.h"
#include "Concepts.h"
#include "TestingHelperModule.h"
#include "Trace/Trace.h"

ATestActorBase::ATestActorBase() : Ticks(0) {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Constructor");
		PrimaryActorTick.bCanEverTick = true;
		USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
		RootComponent = NewRootComponent;
		Tags.Add(TESTABLE_TAG);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Constructor.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s' constructed"), *GetName());
	}
}

ATestActorBase::ATestActorBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Ticks(0) {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::ConstructorWithObjInit");
		PrimaryActorTick.bCanEverTick = true;
		USceneComponent* NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
		RootComponent = NewRootComponent;
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::ConstructorWithObjInit.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s'BaseWithInit constructed"), *GetName());
	}
}

ATestActorBase::~ATestActorBase() {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Destructor");
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Destructor.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s'Base destructed"), *GetName());
	}
}

void ATestActorBase::BeginPlay() {
	Super::BeginPlay();
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::BeginPlay");
		Ticks = 0;
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::BeginPlay.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s'Base begun play"), *GetName());
	}
}

void ATestActorBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Tick");
		AddTick();
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::Tick.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s'Base ticked"), *GetName());
	}
}

uint32 ATestActorBase::GetTicks() const {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::GetTicks.Log");
		UE_LOG(LogTestingHelper, Log, TEXT("'%s'Base ticks (%d) ordered"), *GetName(), Ticks);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::GetTicks");
		return Ticks;
	}
}

bool ATestActorBase::AddTick() {
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::AddTick.Log");
		UE_LOG(
			LogTestingHelper,
			Log,
			TEXT("'%s'Base add 1 tick (Before: %d)"), *GetName(), Ticks
			);
	}
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("ATestActorBase::AddTick");
		if (Ticks == 0xFFFFFFFF) {
			Ticks = 0;
			UE_LOG(LogTestingHelper, Error, TEXT("Overflow-Error on 'uint32 Ticks' from TestActor"));
			return false;
		}
		++Ticks;
		return true;
	}
}

