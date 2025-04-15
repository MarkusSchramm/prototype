/**
 * @file TestActorBase.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "TestActorBase.h"
#include "TestActorStress.generated.h"

/**
 * @class ATestActorStress
 * @brief A utility class for creating and managing test actors with expensive calculations in automation tests.
 * @see ATestActorBase
 */
UCLASS()
class TESTINGHELPER_API ATestActorStress final : public ATestActorBase {
	GENERATED_BODY()

public:
	/**
	 * @brief Constructs a new ATestActorStress.
	 * 
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	ATestActorStress();

	/**
	 * @brief Constructs a new ATestActorStress with object initializer.
	 * @param ObjectInitializer for init about commandline or automation.
	 *
	 * Creates a new AActor for testing, initializes it for gameplay,
	 * and performs necessary setup for actor initialization.
	 */
	explicit ATestActorStress(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Destructs a ATestActorStress.
	 * 
	 * Right now only for logging and tracing purposes
	 */
	virtual ~ATestActorStress() override;

protected:
	/**
	 * @brief ATestActorStress::BeginPlay.
	 * 
	 * Right Now only for logging and tracing purposes.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief ATestActorStress::Tick sets as many times as iterations a new actor location.
	 * @param DeltaTime Delta actor should Tick.
	 * 
	 * For logging and tracing purposes
	 * Tick performs some heavy math operations to simulate stress.
	 * Action will be iterated based on uint32 Iterations.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief ATestActorStress::GetIterations gives number of max iterations of actor
	 * @return Returns uint32 Iterations.
	 * 
	 * For logging and tracing purposes
	 */
	uint32 GetIterations() const;

	/**
	 * @brief ATestActorStress::SetIterations sets new uint32 iterations.
	 * @return Returns false, if uint32 Tick is overflown.
	 * 
	 * For logging and tracing purposes
	 */
	bool SetIterations(uint32 NewIterations) const;

private:
	/**
	 * Number of iterations to perform.
	 * Marked as mutable to allow modification from const methods.
	 */
	mutable uint32 Iterations;
	float MovementRadius;
	float MovementSpeed;
};