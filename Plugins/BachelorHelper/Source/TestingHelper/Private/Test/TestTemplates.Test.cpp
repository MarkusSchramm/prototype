/**
 * @file TestTemplates.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test templates arranging UE unit tests.
 */

#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

#include "TestTemplates.h"
#include "TestActorSimple.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ATestActorSimple;
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FTestTemplatesSpawnActorTestFailureTest,
	"prototype.BachelorHelper.TestingHelper.TestTemplates.000_SpawnActorTestTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FTestTemplatesSpawnActorTestFailureTest::RunTest(const FString& Parameters) {
	MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE;
	ATestActorSimple* actor = NewObject<ATestActorSimple>();
	WorldFixture->SpawnTestActor<ATestActorSimple>(actor->GetActorLocation(), actor->GetActorRotation());
	FActorSpawnParameters expectedSpawnParameters;
	expectedSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return BachelorHelper::TestingHelper::TestActorSpawning<ATestActorSimple>(
		WorldFixture,
		*actor,
		FVector(0, 0, 0),
		FRotator(0, 0, 0),
		expectedSpawnParameters
		);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif