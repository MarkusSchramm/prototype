/**
 * @file TestingHelperModuleImpl.h
 * @author Markus Schramm
 */

#pragma once

#include "TestingHelperModule.h"

namespace BachelorHelper::TestingHelper {
	/**
	 * @class FTestingHelperModule
	 * @brief Concrete implementation of the module
	 * @see ITestingHelperModule
	 */
	class FTestingHelperModule : public ITestingHelperModule {
	public:
		/**
		 * @brief Called when Module is started.
		 * @see [Super::StartupModule](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Modules/IModuleInterface/StartupModule?application_version=5.3#remarks)
		 *
		 * Sets bool bIsInit true.
		 */
		virtual void StartupModule() override;

		/**
		 * @brief Called when Module is shutdown.
		 * @see [Super::ShutdownModule()](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Modules/IModuleInterface/ShutdownModule?application_version=5.3#remarks)
		 *
		 * Sets bool bIsInit false.
		 */
		virtual void ShutdownModule() override;

		/**
		 * @brief Called when Module is shutdown.
		 * @return True if StartupModule called succesfully
		 */
		bool IsInitialized() const;

	private:
		bool bIsInit = false;
	};
}

/**
 * @def TESTINGHELPER_MODULE
 * @brief Shortcut for accessing the module
 */
#define TESTINGHELPER_MODULE BachelorHelper::TestingHelper::FTestingHelperModule