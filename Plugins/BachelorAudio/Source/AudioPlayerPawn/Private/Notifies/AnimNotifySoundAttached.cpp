/**
 * @file AnimNotifySoundAttached.h
 * @author Markus Schramm
 */

#include "Notifies/AnimNotifySoundAttached.h"

#include "Interfaces/IAttachedNotifyManager.h"
#include "Interfaces/IAudioPawnWalkingProvider.h"

void UAnimNotifySoundAttached::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference
) {
	Super::Notify(MeshComp, Animation, EventReference);
	AActor* owner = MeshComp->GetOwner();
	if(!owner || !owner->GetClass()->ImplementsInterface(UAudioPawnWalkingProvider::StaticClass())) return;
	IAttachedNotifyManager::Execute_PlaySoundOnNotifyAttached(owner, Type, BoneName);
}
