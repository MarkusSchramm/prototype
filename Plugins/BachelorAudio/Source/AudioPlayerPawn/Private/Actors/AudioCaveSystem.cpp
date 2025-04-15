// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/AudioCaveSystem.h"

#include "AudioPlayerPawnModule.h"
#include "Components/AudioComponent.h"
#include "Subsystems/AudioProfilerSubsystem.h"

// Sets default values
AAudioCaveSystem::AAudioCaveSystem() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAudioCaveSystem::BeginPlay() {
	Super::BeginPlay();
	for(int32 i = 0; i < PoolSize; ++i) {
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("comp added"));
		UAudioComponent* audioSourceComponent = NewObject<UAudioComponent>(this);
		audioSourceComponent->RegisterComponent();
		audioSourceComponent->AttachToComponent(
			RootComponent,
			FAttachmentTransformRules::KeepRelativeTransform
			);
		AudioComponentPool.Add(audioSourceComponent);
	}
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AAudioCaveSystem::SpawnAudioSource,
		CustomSpawnTime,
		false
		);
}

// Called every frame
void AAudioCaveSystem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ProcessPendingSoundDrops();
}

void AAudioCaveSystem::SpawnAudioSource() {
	if(DropSounds.Num() < 1) {
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("Not enough"));
		return;
	}
	int32 index = FMath::RandRange(0, DropSounds.Num() - 1);
	UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("dropsounds: %d"), DropSounds.Num());
	USoundBase* selectedSound = DropSounds[index];
	if(selectedSound == nullptr) {
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("Not there"));
		return;
	}
	UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("sound: %s"), *selectedSound->GetName());
	UAudioComponent* availableAudioSource = GetAvailableAudioComponent();
	if(availableAudioSource == nullptr) {
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("Not comp"));
		return;
	}
	availableAudioSource->SetSound(selectedSound);
	UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("compsounds: %s"), *availableAudioSource->GetName());
	FVector startLocation = GetActorLocation();
	FVector randomDirection = FMath::VRand().GetSafeNormal2D();
	randomDirection.Z = FMath::RandRange(.1f, 1.f);
	randomDirection.Normalize();
	FVector endLocation = startLocation + randomDirection * MaxRoofTraceDistance;
	FHitResult hitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECC_Visibility
		);
	FVector newLocation;
	if(DrawDebugLines) {
		DrawDebugLine(
			GetWorld(),
			startLocation,
			bHit ? newLocation : endLocation,
			bHit ? FColor::Green : FColor::Red,
			false,
			2.f
			);
	}
	if(!bHit) {
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("Not hit"));
		return;
	}
	newLocation = hitResult.Location;
	availableAudioSource->SetWorldLocation(newLocation);
	DropComponentToGroundAndPlay(availableAudioSource, newLocation);
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AAudioCaveSystem::SpawnAudioSource,
		CustomSpawnTime,
		false
		);
}

void AAudioCaveSystem::DropComponentToGroundAndPlay(
	UAudioComponent* AudioComponent,
	FVector StartLocation
	) {
	FVector endLocation = StartLocation - FVector(0.f,0.f, MaxGroundTraceDistance);
	FHitResult hitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		StartLocation,
		endLocation,
		ECC_Visibility
		);
	if(DrawDebugLines) {
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			bHit ? hitResult.Location : endLocation,
			bHit ? FColor::Green : FColor::Red,
			false,
			2.f
			);
	}
	if(!bHit) {
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("Not dropped"));
		return;
	}
	float distanceToFall = (hitResult.Location - StartLocation).Size();
	if(distanceToFall < MinFallingDistance) {
		if(!DrawDebugLines) return;
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			hitResult.Location,
			FColor::Blue,
			false,
			2.f
			);
		return;
	}
	FSoundDropInfo DropInfo;
	DropInfo.AudioComponent = AudioComponent;
	DropInfo.StartLocation = StartLocation;
	DropInfo.EndLocation = hitResult.Location;
	DropInfo.StartTime = GetWorld()->GetTimeSeconds();
	DropInfo.Duration = distanceToFall / FallSpeedModifier;
	PendingDrops.Add(DropInfo);
	AudioComponent->Play();
	UE_CLOG(AudioComponent->IsPlaying(), LogAudioPlayerPawnModule, Warning, TEXT("%s plays"), *AudioComponent->GetName());
}

void AAudioCaveSystem::SetMood_Implementation(float MoodScalar) {
	for(const auto& drop : PendingDrops) {
		drop.AudioComponent->SetFloatParameter(FName("MoodScalarIn"), FMath::Clamp(MoodScalar, 0.f, 1.f));
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Mood scalar set to %f"), MoodScalar));
		}
	}
}

void AAudioCaveSystem::SetEnergy_Implementation(float EnergyScalar) {
	for(const auto& drop : PendingDrops) {
		drop.AudioComponent->SetFloatParameter(FName("EnergyScalarIn"), FMath::Clamp(EnergyScalar, 0.f, 1.f));
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Energy scalar set to %f"), EnergyScalar));
		}
	}
}

void AAudioCaveSystem::SetRain_Implementation(float RainScalar) {
	for(const auto& drop : PendingDrops) {
		drop.AudioComponent->SetFloatParameter(FName("RainScalarIn"), FMath::Clamp(RainScalar, 0.f, 1.f));
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Rain scalar set to %f"), RainScalar));
		}
	}
}

void AAudioCaveSystem::SetWind_Implementation(float WindScalar) {
	for(const auto& drop : PendingDrops) {
		drop.AudioComponent->SetFloatParameter(FName("WindScalarIn"), FMath::Clamp(WindScalar, 0.f, 1.f));
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Wind scalar set to %f"), WindScalar));
		}
	}
}

void AAudioCaveSystem::SetTemperature_Implementation(float TemperatureScalar) {
	for(const auto& drop : PendingDrops) {
		drop.AudioComponent->SetFloatParameter(FName("TemperatureScalarIn"), FMath::Clamp(TemperatureScalar, 0.f, 1.f));
		if(auto subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAudioProfilerSubsystem>()) {
			subsystem->AddBookmark(FString::Printf(TEXT("Temperature scalar set to %f"), TemperatureScalar));
		}
	}
}

void AAudioCaveSystem::ProcessPendingSoundDrops() {
	for (int32 index = 0; index < PendingDrops.Num(); index++) {
		FSoundDropInfo& Drop = PendingDrops[index];
		float elapsedTime = GetWorld()->GetTimeSeconds() - Drop.StartTime;
		if(elapsedTime > Drop.Duration) {
			Drop.AudioComponent->SetWorldLocation(Drop.EndLocation);
			int32 soundIndex = FMath::RandRange(0, ImpactSounds.Num() - 1);
			USoundBase* selectedSound = ImpactSounds[soundIndex];
			Drop.AudioComponent->SetSound(selectedSound);
			Drop.AudioComponent->Play();
			PendingDrops.RemoveAtSwap(index);
			index--;
		} else {
			FVector newLocation = FMath::Lerp(
				Drop.StartLocation,
				Drop.EndLocation,
				elapsedTime / Drop.Duration
				);
			Drop.AudioComponent->SetWorldLocation(newLocation);
		}
	}
}

UAudioComponent* AAudioCaveSystem::GetAvailableAudioComponent() {
	for(UAudioComponent* audioSourceComponent : AudioComponentPool) {
		if(!audioSourceComponent->IsPlaying()) return audioSourceComponent;
		UE_LOG(LogAudioPlayerPawnModule, Warning, TEXT("plays"));
	}
	return nullptr;
}