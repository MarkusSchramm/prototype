// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestActorBase.h"
#include "TestActorSimple.generated.h"

/**
 * @class ATestActorSimple
 * @brief A utility class for creating and managing test actors with root component.
 * @see [AActor] (https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor?application_version=5.3)
 */
UCLASS()
class TESTINGHELPER_API ATestActorSimple final : public ATestActorBase {
	GENERATED_BODY()

public:
	/**
	 * @brief Constructs a new ATestActorBase.
	 * 
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	ATestActorSimple();

	/**
	 * @brief Constructs a new ATestActorBase with object initializer.
	 * @param ObjectInitializer for init about commandline or automation.
	 *
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	explicit ATestActorSimple(const FObjectInitializer& ObjectInitializer);

	virtual ~ATestActorSimple() override;

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
};
