/**
 * @file AudioPlayerPawnModule.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAudioPlayerPawnModule, Log, All);

namespace BachelorAudio::AudioPlayerPawn {
    /**
	* @interface IAudioPlayerPawnModule
	* @brief Module interface for controlling sound effects in Unreal Engine.
	* 
	* @details This module provides ActorComponents, Interfaces, and Models
	* that are used for precise control of sound effects related to Unreal Engine GameObjects.
	* It allows for easy integration of audio functionality into various game objects
	* through a consistent API.
	* 
	* The module is derived from IModuleInterface and follows the standard module lifecycle
	* of the Unreal Engine.
    * @see [IModuleInterface](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Modules)
    */
    class AUDIOPLAYERPAWN_API IAudioPlayerPawnModule : public IModuleInterface {};
}
