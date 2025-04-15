/**
 * @file TestingHelperModuleImpl.Test.cpp
 * @author Markus Schramm
 * @brief Contains atomic unit test for module management.
 */

#include "TestingHelperModule.h"
#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#if WITH_EDITOR
#include "Tests/AutomationEditorCommon.h"
#endif

#include "TestingHelperModuleImpl.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FTestingHelperModuleImplLoadModuleTest,
	"prototype.BachelorHelper.TestingHelper.TestingHelperModuleImpl.000_LoadModuleTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FTestingHelperModuleImplLoadModuleTest::RunTest(const FString& Parameters) {
	FModuleManager& moduleManager = FModuleManager::Get();
	IModuleInterface* module = moduleManager.LoadModule("TestingHelper");
	TestNotNull(TEXT("Module should load successfully"), module);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FTestingHelperModuleImplValidateModuleTest,
	"prototype.BachelorHelper.TestingHelper.TestingHelperModuleImpl.005_ValidateModuleTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
)

bool FTestingHelperModuleImplValidateModuleTest::RunTest(const FString& Parameters) {
	TESTINGHELPER_MODULE& module = FModuleManager::GetModuleChecked<TESTINGHELPER_MODULE>("TestingHelper");
	TestTrue(TEXT("Module should be initialized"), module.IsInitialized());
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif