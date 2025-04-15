/**
 * @file IAttachedNotifyManager.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAttachedNotifyManager.generated.h"

enum class EAudioCharCompType : uint8;

/**
 * @interface UAttachedNotifyManager
 * @brief Interface for managing attached sound notifications during animations
 * 
 * This interface provides functionality for playing sounds at specific bone locations
 * in response to animation notify events. It can be implemented by any class that needs
 * to handle sound playback triggered by UAnimNotifySoundAttached or similar notify classes.
 */
UINTERFACE(BlueprintType)
class UAttachedNotifyManager : public UInterface {
	GENERATED_BODY()
};

/**
 * @interface IAttachedNotifyManager
 * @brief Implementation interface for handling attached sound notifications
 * 
 * If you want this Interface to be overrideable in C++ and Blueprints, you have to follow this Syntax:
 * Implementation:  virtual PlaySoundOnNotifyAttached_Implementation(EAudioCharCompType Type, FName Bone) override;
 * Check:			GetOwner()->GetClass()->ImplementsInterface(UAttachedNotifyManager::StaticClass());
 * Execution:		IAttachedNotifyManager::Execute_PlaySoundOnNotifyAttached(ContextObject, Type, Bone);
 */
class AUDIOPLAYERPAWN_API IAttachedNotifyManager {
	GENERATED_BODY()

public:
	/**
	 * Plays a sound attached to a specific bone
	 * 
	 * @param Type The type of audio component to use, defined in EAudioCharCompType enum
	 * @param Bone The name of the bone to attach the sound to
	 * 
	 * Implementing classes should handle sound asset selection based on Type and play
	 * the sound at the specified bone location on the character/object.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Audio | Animation")
	void PlaySoundOnNotifyAttached(EAudioCharCompType Type, FName Bone);
};