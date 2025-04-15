/**
 * @file WorldFixture.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test for FWorldFixture.
 */

#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

#include "WorldFixture.h"
#include "TestActorSimple.h"
#include "TestTemplates.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureNullTestStack,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.000_NullTest_Stack",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureNullTestStack::RunTest(const FString& Parameters) {
	WORLD_FIXTURE WorldFixture;
	TestNotNull(TEXT("'WorldFixture' should be not NULL"), &WorldFixture);
	TestNotNull(TEXT("'WorldFixture->GetWorld()' should be not NULL"), WorldFixture.GetWorld());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureNullTestRawPointer,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.005_NullTest_RawPointer",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureNullTestRawPointer::RunTest(const FString& Parameters) {
	POINTER_RAW_WORLD_FIXTURE WorldFixture = nullptr;
	TestNull(TEXT("'WorldFixture' should be NULL"), WorldFixture);
	WorldFixture = MAKE_RAW_WORLD_FIXTURE;
	TestNotNull(TEXT("'WorldFixture' should be not NULL"), WorldFixture);
	RESET_RAW_WORLD_FIXTURE;
	TestNull(TEXT("'WorldFixture' should be NULL"), WorldFixture);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureNullTestRawPointerShort,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.010_NullTest_RawPointerShort",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureNullTestRawPointerShort::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_RAW_WORLD_FIXTURE;
	TestNotNull(TEXT("'WorldFixture' should be not NULL"), WorldFixture);
	RESET_RAW_WORLD_FIXTURE;
	TestNull(TEXT("'WorldFixture' should be NULL"), WorldFixture);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureNullTestUniquePointer,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.015_NullTest_UniquePointer",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureNullTestUniquePointer::RunTest(const FString& Parameters) {
	POINTER_UNIQUE_WORLD_FIXTURE WorldFixture = nullptr;
	TestNull(TEXT("'WorldFixture' should be NULL"), WorldFixture.Get());
	WorldFixture = MAKE_UNIQUE_WORLD_FIXTURE;
	TestNotNull(TEXT("'WorldFixture' should be not NULL"), WorldFixture.Get());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureNullTestUniquePointerShort,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.020_NullTest_UniquePointerShort",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureNullTestUniquePointerShort::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	TestNotNull(TEXT("'WorldFixture' should be not NULL"), WorldFixture.Get());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureGetWorldTest,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.025_GetWorldTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureGetWorldTest::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	TestNotNull(TEXT("World should be not NULL"), WorldFixture->GetWorld());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureSpawnTestActorTest_Simple,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.030_SpawnTestActorTest_Simple",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureSpawnTestActorTest_Simple::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	AActor* testActor = WorldFixture->SpawnTestActor<ATestActorSimple>();
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return TestTrue(TEXT(""), TestActorSpawning<ATestActorSimple>(
		WorldFixture,
		*testActor,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnParams
		));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureSpawnTestActorTest_Location,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.035_SpawnTestActorTest_Location",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureSpawnTestActorTest_Location::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	const FVector& testLocation = FVector(200, 100, 70);
	AActor* testActor = WorldFixture->SpawnTestActor<ATestActorSimple>(testLocation);
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return TestActorSpawning<ATestActorBase>(
		WorldFixture,
		*testActor,
		testLocation,
		FRotator::ZeroRotator,
		spawnParams
		);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureSpawnTestActorTest_Rotation,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.040_SpawnTestActorTest_Rotation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureSpawnTestActorTest_Rotation::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	const FVector& testLocation = FVector::ZeroVector;
	const FRotator& testRotation = FRotator(15,40,20);
	AActor* testActor = WorldFixture->SpawnTestActor<ATestActorSimple>(testLocation, testRotation);
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return TestActorSpawning<ATestActorSimple>(
		WorldFixture,
		*testActor,
		testLocation,
		testRotation,
		spawnParams
		);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureSpawnTestActorTest_LocationAndRotation,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.045_SpawnTestActorTest_LocationAndRotation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureSpawnTestActorTest_LocationAndRotation::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	const FVector& testLocation = FVector(200, 100, 70);
	const FRotator& testRotation = FRotator(15,40,20);
	AActor* testActor = WorldFixture->SpawnTestActor<ATestActorSimple>(testLocation, testRotation);
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return BachelorHelper::TestingHelper::TestActorSpawning<ATestActorBase>(
		WorldFixture,
		*testActor,
		testLocation,
		testRotation,
		spawnParams
		);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureSpawnTestActorTest_Params,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.050_SpawnTestActorTest_Params",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureSpawnTestActorTest_Params::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	FActorSpawnParameters testParams;
	testParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	AActor* testActor = WorldFixture->SpawnTestActorWithParams<ATestActorSimple>(testParams);
	return BachelorHelper::TestingHelper::TestActorSpawning<ATestActorBase>(
		WorldFixture,
		*testActor,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		testParams
		);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureSpawnTestActorTest_Complex,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.055_SpawnTestActorTest_Complex",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureSpawnTestActorTest_Complex::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	FVector testLocation = FVector(200,100,70);
	FRotator testRotation = FRotator(15,40,20);
	FActorSpawnParameters testParams;
	testParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	AActor* testActor = WorldFixture->SpawnTestActorComplex<ATestActorSimple>(testLocation, testRotation, testParams);
	return BachelorHelper::TestingHelper::TestActorSpawning<ATestActorSimple>(
		WorldFixture,
		*testActor,
		testLocation,
		testRotation,
		testParams
		);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureTickWorldTestSimple,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.060_TickWorldTest_Simple",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureTickWorldTestSimple::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	WorldFixture->GetWorld()->SetShouldTick(false);
	TestTrue(TEXT("World should tick with 0.016s"),WorldFixture->TickWorld());
	TestEqual(TEXT("World delta should be 0.016s"), WorldFixture->GetWorld()->GetDeltaSeconds(), .016f);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureTickWorldTestMax,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.065_TickWorldTest_Max",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureTickWorldTestMax::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	WorldFixture->GetWorld()->SetShouldTick(false);
	TestTrue(TEXT("World should tick with 0.4ms at max"),WorldFixture->TickWorld(1.f));
	TestNotEqual(TEXT("World delta should not be 1s"),  WorldFixture->GetWorld()->GetDeltaSeconds(), 1.f);
	TestEqual(TEXT("World delta should be 0.4s"),  WorldFixture->GetWorld()->GetDeltaSeconds(), .4f);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureTickWorldTestMin,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.070_TickWorldTest_Min",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureTickWorldTestMin::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	WorldFixture->GetWorld()->SetShouldTick(false);
	TestTrue(TEXT("World should tick variable --> at 0.0005s"),WorldFixture->TickWorld(0.f));
	TestNotEqual(TEXT("World delta should not be 0s"),  WorldFixture->GetWorld()->GetDeltaSeconds(), 0.f);
	TestEqual(TEXT("World delta should be 0.0005s"),  WorldFixture->GetWorld()->GetDeltaSeconds(), .0005f);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FWorldFixtureDestroyActorTest,
	"prototype.BachelorHelper.TestingHelper.WorldFixture.075_DestroyActorTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FWorldFixtureDestroyActorTest::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	AActor* testActor = WorldFixture->SpawnTestActor<ATestActorSimple>();
	TestTrue(TEXT("Actor should be destroyed"), WorldFixture->DestroyTestActor(testActor));
	testActor = nullptr;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif