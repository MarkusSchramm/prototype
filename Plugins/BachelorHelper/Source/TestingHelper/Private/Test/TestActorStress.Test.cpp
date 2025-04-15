/**
 * @file TestActorStress.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test for TestActorStress.
 */


#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

#include "TestActorStress.h"
#include "TestActorSimple.h"
#include "TestingHelperModule.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorStressNullTest,
	"prototype.BachelorHelper.TestingHelper.TestActorStress.000_NullTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorStressNullTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorStress> testActor = NewObject<ATestActorStress>();
	TestNotNull(TEXT("TestActorStress should not be NULL"), testActor.Get());
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorStressIterationsDefaultTest,
	"prototype.BachelorHelper.TestingHelper.TestActorStress.005_IterationsDefaultTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorStressIterationsDefaultTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorStress> testActor = NewObject<ATestActorStress>();
	TestEqual(TEXT("TestActorStress should have 100 iterations"), testActor.Get()->GetIterations(), 100);
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorStressIterationsCustom,
	"prototype.BachelorHelper.TestingHelper.TestActorStress.010_IterationsCustom",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorStressIterationsCustom::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorStress> testActor = NewObject<ATestActorStress>();
	TestEqual(TEXT("TestActorStress should have 100 iterations"), testActor.Get()->GetIterations(), 100);
	TestTrue(TEXT("Iterations should be set to 5"), testActor.Get()->SetIterations(5));
	TestEqual(TEXT("TestActorStress should have 5 iterations"), testActor.Get()->GetIterations(), 5);
	testActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	ATestActorStressTickTest,
	"prototype.BachelorHelper.TestingHelper.TestActorStress.015_StressTickTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool ATestActorStressTickTest::RunTest(const FString& Parameters) {
	TWeakObjectPtr<ATestActorStress> testActor = NewObject<ATestActorStress>();
	TWeakObjectPtr<ATestActorSimple> simpleActor = NewObject<ATestActorSimple>();

	double start = FPlatformTime::Seconds();
	simpleActor.Get()->Tick(.016f);
	double end = FPlatformTime::Seconds();
	double tickTimeShort = end - start;

	start = FPlatformTime::Seconds();
	testActor.Get()->Tick(.016f);
	end = FPlatformTime::Seconds();
	double tickTimeLong = end - start;
	UE_LOG(LogTestingHelper, Log, TEXT("Short: %f\tLong:%f"), tickTimeShort, tickTimeLong);

	TestTrue(TEXT("TestActorBase tick should be less than testActorStress"), tickTimeLong > tickTimeShort);
	
	
	testActor.Reset();
	simpleActor.Reset();
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif