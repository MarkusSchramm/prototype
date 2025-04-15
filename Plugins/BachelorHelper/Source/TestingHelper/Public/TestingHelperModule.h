/**
 * @file TestingHelperModule.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTestingHelper, Log, All);

namespace BachelorHelper::TestingHelper {
	/**
	 * @interface ITestingHelperModule
	 * @brief Module interface for testing support functions in Unreal Engine.
	 * 
	 * @details This module provides helper functions and tools that facilitate testing
	 * of Unreal Engine components and systems. It offers a unified interface for integrating
	 * test methods into the engine environment.
	 * 
	 * @note Important: For the tests to work properly, the tag 'Bachelor' must be added to every
	 * actor that uses these tests.
	 * 
	 * The module is derived from IModuleInterface and follows the standard module lifecycle
	 * of the Unreal Engine.
	 * @see [IModuleInterface](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Modules)
	 */
	class TESTINGHELPER_API ITestingHelperModule : public IModuleInterface {};
}

