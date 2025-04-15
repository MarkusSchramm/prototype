/**
 * @file TestTemplates.h
 * @author Markus Schramm
 * @brief Test-templates and namespace-scoped functions for reuse
 */

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"
#include "TestActorBase.h"
#include "WorldFixture.h"
#include "Concepts.h"

namespace BachelorHelper::TestingHelper {
	/**
	 * @brief Builds the corresponding string reference to spawn collision method.
	 * @param SpawnCollisionMethod applied spawn collision method
	 * @param SpawnCollisionMethodString corresponding string as reference
	 * @see [ESpawnActorCollisionHandlingMethod](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/FActorSpawnParameters)
	 */
	inline void BuildSpawnCollisionMethodString(
		const ESpawnActorCollisionHandlingMethod SpawnCollisionMethod,
		FString& SpawnCollisionMethodString
		) {
		SpawnCollisionMethodString.Empty();
		switch(SpawnCollisionMethod) {
		case ESpawnActorCollisionHandlingMethod::Undefined:
			SpawnCollisionMethodString = "NOT DEFINED";
			break;
		case ESpawnActorCollisionHandlingMethod::AlwaysSpawn:
			SpawnCollisionMethodString = "ALWAYS SPAWN";
			break;
		case ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn:
			SpawnCollisionMethodString = "ADJUST IF POSSIBLE BUT ALWAYS SPAWN";
			break;
		case ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding:
			SpawnCollisionMethodString = "ADJUST IF POSSIBLE BUT DONT SPAWN IF COLLIDING";
			break;
		case ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding:
			SpawnCollisionMethodString = "DONT SPAWN IF COLLIDING";
			break;
		default:
			SpawnCollisionMethodString = "NOT DEFINED";
			break;
		}
	}

	/**
	 * @brief Helper function for testing of actor spawn collision method on test run.
	 * @param TestActor
	 * @param FoundActor
	 * @param ExpectedSpawnCollisionMethod
	 * @return success (true) -> actor spawned with correct spawn collision method; else logs error and returns false
	 * @see [ESpawnActorCollisionHandlingMethod](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/FActorSpawnParameters)
	 */
	inline bool TestCollisionMethod(
	const AActor& TestActor,
	const AActor& FoundActor,
	const ESpawnActorCollisionHandlingMethod ExpectedSpawnCollisionMethod
	) {
		FString expectedCollisionString = "";
		FString currentCollisionString = "";
		if(TestActor.SpawnCollisionHandlingMethod != ExpectedSpawnCollisionMethod) {
			BuildSpawnCollisionMethodString(ExpectedSpawnCollisionMethod, expectedCollisionString);
			BuildSpawnCollisionMethodString(TestActor.SpawnCollisionHandlingMethod, currentCollisionString);
			UE_LOGFMT(
				LogTestingHelper,
				Error,
				"TestSpawnCollisionMethod: {name} should spawn with {expected}. Current: {current}",
				*TestActor.GetName(),
				expectedCollisionString,
				currentCollisionString
			);
			expectedCollisionString = "";
			currentCollisionString = "";
			return false;
		}
		if(FoundActor.SpawnCollisionHandlingMethod != TestActor.SpawnCollisionHandlingMethod) {
			BuildSpawnCollisionMethodString(FoundActor.SpawnCollisionHandlingMethod, expectedCollisionString);
			BuildSpawnCollisionMethodString(TestActor.SpawnCollisionHandlingMethod, currentCollisionString);
			UE_LOGFMT(
				LogTestingHelper,
				Error,
				"CompareSpawnCollisionMethod: {name} should spawn with {expected}. As well as {found}: {current}",
				*FoundActor.GetName(),
				expectedCollisionString,
				*TestActor.GetName(),
				currentCollisionString
				);
			expectedCollisionString = "";
			currentCollisionString = "";
			return false;
		}
		return true;
	}

	/**
	 * @brief Helper function for testing of actor spawn location on test run.
	 * @param TestActor
	 * @param FoundActor
	 * @param ExpectedLocation
	 * @return success (true) -> actor spawned with correct location; else logs error and returns false
	 */
	inline bool TestSpawnLocation(
	const AActor& TestActor,
	const AActor& FoundActor,
	const FVector& ExpectedLocation
	) {
		const auto testLocation = TestActor.GetActorLocation();
		if(!testLocation.Equals(ExpectedLocation)) {
			UE_LOGFMT(
				LogTestingHelper,
				Error,
				"TestSpawnLocation: {name} should spawn with {expected}. Current: {current}",
				*TestActor.GetName(),
				*testLocation.ToString(),
				*ExpectedLocation.ToString()
				);
			return false;
		}
		const auto foundLocation = FoundActor.GetActorLocation();
		if(!foundLocation.Equals(testLocation)) {
			UE_LOGFMT(
				LogTestingHelper,
				Error,
				"CompareSpawnLocation: {name} should spawn with {expected}. As well as {found}: {current}",
				*FoundActor.GetName(),
				*foundLocation.ToString(),
				*TestActor.GetName(),
				*testLocation.ToString()
				);
			return false;
		}
		return true;
	}

	/**
	 * @brief Helper function for testing of actor spawn rotation on test run.
	 * @param TestActor
	 * @param FoundActor
	 * @param ExpectedRotation
	 * @return success (true) -> actor spawned with correct rotation; else logs error and returns false
	 */
	inline bool TestSpawnRotation(
	const AActor& TestActor,
	const AActor& FoundActor,
	const FRotator& ExpectedRotation
	) {
		const auto testRotation = TestActor.GetActorRotation();
		if(!testRotation.Equals(ExpectedRotation)) {
			UE_LOGFMT(
				LogTestingHelper,
				Error,
				"TestSpawnRotation: {name} should spawn with {expected}. Current: {current}",
				*TestActor.GetName(),
				*testRotation.ToString(),
				*ExpectedRotation.ToString()
					);
			return false;
		}
		const auto foundRotation = FoundActor.GetActorRotation();
		if(!foundRotation.Equals(testRotation)) {
			UE_LOGFMT(
				LogTestingHelper,
				Error,
				"CompareSpawnRotation: {name} should spawn with {expected}. As well as {found}: {current}",
				*FoundActor.GetName(),
				*foundRotation.ToString(),
				*TestActor.GetName(),
				*testRotation.ToString()
				);
			return false;
		}
		return true;
	}


	
	/**
	 * @brief Helper template for testing of actor spawning in a world fixture on test run.
	 * @tparam T Actor to spawn, needed for GameplayStatics to get all actors of this class. Do not use AActor!
	 * @param WorldFixture reference to unique pointer of World
	 * @param TestActor actor test should run on
	 * @param ExpectedTestLocation 
	 * @param ExpectedTestRotation
	 * @param ExpectedSpawnParams for now only SpawnCollision type is tested
	 * @return success (true) -> actor spawned; else logs error returns false
	 * @see [ESpawnActorCollisionHandlingMethod](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/FActorSpawnParameters)
	 */
	template <ue_actor T>
	bool TestActorSpawning(
		const POINTER_UNIQUE_WORLD_FIXTURE& WorldFixture,
		const testable auto& TestActor,
		const FVector& ExpectedTestLocation,
		const FRotator& ExpectedTestRotation,
		const FActorSpawnParameters& ExpectedSpawnParams
	){
		if(!TestActor.ActorHasTag(TESTABLE_TAG)) return false;
		// standard actors like world settings on a new world -> our actor is 7th
		if(TestActor.IsA(ATestActorBase::StaticClass())) {
			TArray<AActor*> FoundActors;
			FoundActors.Empty();
			UGameplayStatics::GetAllActorsWithTag(WorldFixture->GetWorld(), TESTABLE_TAG, FoundActors);
			if(FoundActors.Num() != 1) {
				UE_LOGFMT(
					LogTestingHelper,
					Error,
					"CompareTestActorsNum: There should only be 1 {name}. Current: {numActorsFound}	",
					*FoundActors.Last()->GetName(),
					FoundActors.Num()
					);
				return false;
			}
			if(!TestCollisionMethod(TestActor,*FoundActors.Last(),
				ExpectedSpawnParams.SpawnCollisionHandlingOverride)) return false;
			if(!TestSpawnLocation(TestActor,*FoundActors.Last(), ExpectedTestLocation)) return false;
			if(!TestSpawnRotation(TestActor,*FoundActors.Last(), ExpectedTestRotation)) return false;
			FoundActors.Empty();
			return true;
		}
		// standard actors like world settings on a new world -> our actor is 7th
		UE_LOGFMT(
			LogTestingHelper,
			Error,
			"Actor Spawn Test: AActor cannot be used",
			);
		return false;
	}
}

