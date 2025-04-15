/**
 * @file AnimNotifySoundAttached.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Definitions/AudioCharDefinitions.h"
#include "AnimNotifySoundAttached.generated.h"

enum class EAudioCharCompType : uint8;
/**
 * @class UAnimNotifySoundAttached
 * @brief Animation notification class for playing sounds attached to specific bones
 * 
 * This class extends UAnimNotify to provide functionality for playing sounds
 * attached to specific bones on a skeletal mesh during animation playback.
 * When triggered, it will play the associated sound at the location of the specified bone.
 */
UCLASS()
class AUDIOPLAYERPAWN_API UAnimNotifySoundAttached : public UAnimNotify {
	GENERATED_BODY()

public:
	/**
	 * Triggered when the animation reaches the notify point
	 * 
	 * @param MeshComp The skeletal mesh component that triggered this notify
	 * @param Animation The animation sequence that contains this notify
	 * @param EventReference Reference to the anim notify event
	 * 
	 * Override implementation handles playing the sound at the specified bone location
	 */
	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference
		) override;

private:
	/** 
	 * Name of the bone to attach the sound to
	 * If empty, the sound will play at audio component position, attached at construction
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimNotify, meta = (AllowPrivateAccess = "true"))
	FName BoneName = FName("");

	/** 
	 * Type of component to attach sound to
	 * If empty, the sound will not play
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimNotify, meta = (AllowPrivateAccess = "true"))
	EAudioCharCompType Type = EAudioCharCompType::FootL;
};