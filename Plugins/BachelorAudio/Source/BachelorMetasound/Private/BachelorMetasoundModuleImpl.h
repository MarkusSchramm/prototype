/**
 * @file BachelorMetasoundModuleImpl.h
 * @author Markus Schramm
 */

#pragma once

#include "BachelorMetasoundModule.h"

namespace BachelorAudio::BachelorMetasound {
	/**
	 * @class FBachelorMetasoundModule
	 * @brief Concrete implementation of the module
	 * @see IBachelorAudioModule
	 */
	class BACHELORMETASOUND_API FBachelorMetasoundModule : public IBachelorMetasoundModule {
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
		 * @return True if StartupModule called successfully
		 */
		bool IsInitialized() const;

	private:
		bool bIsInit = false;
	};
}

/**
 * @def BACHELORAUDIO_MODULE
 * @brief Shortcut for accessing the module
 */
#define BACHELORMETASOUND_MODULE BachelorAudio::BachelorMetasound::FBachelorMetasoundModule