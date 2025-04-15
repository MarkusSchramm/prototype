//@TODO: rework comments && overthink init
/**
 * @file AudioPlayerPawnModuleImpl.h
 * @author Markus Schramm
 */

#pragma once

#include "AudioPlayerPawnModule.h"

namespace BachelorAudio::AudioPlayerPawn {
	/**
	 * @class FAudioPlayerPawnModule
	 * @brief Concrete implementation of the module
	 * @see IBachelorAudioModule
	 */
	class AUDIOPLAYERPAWN_API FAudioPlayerPawnModule : public IAudioPlayerPawnModule {
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
 * @def AUDIOCHARACTER_MODULE
 * @brief Shortcut for accessing the module
 */
#define AUDIOPLAYERPAWN_MODULE BachelorAudio::AudioPlayerPawn::FAudioPlayerPawnModule
