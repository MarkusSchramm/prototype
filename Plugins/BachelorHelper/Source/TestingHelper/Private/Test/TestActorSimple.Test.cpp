/**
 * @file TestActorSimple.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test for TestActorSimple.
 */

#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

#include "TestActorSimple.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorBaseNullTest,
	"prototype.BachelorHelper.TestingHelper.TestActorBase.000_NullTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorBaseNullTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorSimple> testActor = NewObject<ATestActorSimple>();
	TestNotNull(TEXT("TestActorBase should not be NULL"), testActor.Get());
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorBaseRootCompTest,
	"prototype.BachelorHelper.TestingHelper.TestActorBase.005_RootCompTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorBaseRootCompTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorSimple> testActor = NewObject<ATestActorSimple>();
	TestNotNull(TEXT("TestActorBase should have a root component"), testActor.Get()->GetRootComponent());
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorBaseAddTickTest,
	"prototype.BachelorHelper.TestingHelper.TestActorBase.010_AddTickTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorBaseAddTickTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorSimple> testActor = NewObject<ATestActorSimple>();
	TestTrue(TEXT("TestActorBase should add a tick"), testActor.Get()->AddTick());
	TestEqual(TEXT("TestActorBase should have ticked 1 time"), testActor.Get()->GetTicks(), 1);
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorBaseTickTest,
	"prototype.BachelorHelper.TestingHelper.TestActorBase.015_TickTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorBaseTickTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorSimple> testActor = NewObject<ATestActorSimple>();
	TestEqual(
		FString::Printf(TEXT("'%s' should have ticked 0 times"), *testActor->GetName()),
		testActor.Get()->GetTicks(),
		0
		);
	testActor.Get()->Tick(0.f);
	TestEqual(
		FString::Printf(TEXT("'%s' should have ticked 0 times"), *testActor->GetName()),
		testActor.Get()->GetTicks(),
		1
		);
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif