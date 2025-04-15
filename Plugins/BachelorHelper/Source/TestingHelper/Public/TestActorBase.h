/**
 * @file TestActorBase.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActorBase.generated.h"

/**
 * @class ATestActorBase
 * @brief A utility class for creating and managing test actors in automation tests.
 * @see [AActor] (https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor?application_version=5.3)
 *
 *  Do not instantiate, use child classes or derive from here.
 */
UCLASS(Abstract)
class TESTINGHELPER_API ATestActorBase : public AActor {
	GENERATED_BODY()

public:
	/**
	 * @brief Constructs a new ATestActorBase.
	 * 
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	ATestActorBase();

	/**
	 * @brief Constructs a new ATestActorBase with object initializer.
	 * @param ObjectInitializer for init about commandline or automation.
	 *
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	 explicit ATestActorBase(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Destructs a ATestActorBase.
	 * 
	 * Right now only for logging and tracing purposes
	 */
	virtual ~ATestActorBase() override;

protected:
	/**
	 * @brief ATestActorBase::BeginPlay sets private variable Tick to 0.
	 * @see [AActor::BeginPlay](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor/BeginPlay?application_version=5.3)
	 * 
	 * For logging and tracing purposes
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief ATestActorBase::Tick calls AddTick.
	 * @see [AActor::BeginPlay](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor/Tick?application_version=5.3)
	 * 
	 * For logging and tracing purposes
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief ATestActorBase::AddTick increments uint32 Tick.
	 * @return Returns false, if uint32 Tick is overflown.
	 * 
	 * For logging and tracing purposes
	 */
	bool AddTick();

	/**
	 * @brief ATestActorBase::GetTicks gives number of actual ticks of actor
	 * @return Returns uint32 Ticks.
	 * 
	 * For logging and tracing purposes
	 */
	uint32 GetTicks() const;

protected:
	uint32 Ticks;
};
