/**
 * @file AudioPawnWalking.cpp
 * @author Markus Schramm
 */

#include "Actors/AudioPawnWalking.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioPawnWalkingComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAudioPawnWalking::AAudioPawnWalking() {
	ConstructAsThirdPerson();
	AudioComponent = CreateDefaultSubobject<UAudioPawnWalkingComponent>(TEXT("AudioManager"));
	AudioComponent->RegisterComponent();
}

AAudioPawnWalking::AAudioPawnWalking(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	ConstructAsThirdPerson();
	AudioComponent = CreateDefaultSubobject<UAudioPawnWalkingComponent>(TEXT("AudioManager"));
	AudioComponent->RegisterComponent();
}

AAudioPawnWalking::~AAudioPawnWalking() {

}

void AAudioPawnWalking::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AAudioPawnWalking::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	SetupInputAsThirdPerson(PlayerInputComponent); // no super call because enhanced input
}

void AAudioPawnWalking::BeginPlay() {
	Super::BeginPlay();
	BeginPlayAsThirdPerson();
}

void AAudioPawnWalking::Move(const FInputActionValue& Value) {
	MoveAsThirdPerson(Value);
}

void AAudioPawnWalking::Look(const FInputActionValue& Value) {
	LookAsThirdPerson(Value);
}

void AAudioPawnWalking::ConstructAsThirdPerson() {
	// Start ThirdPersonTemplate
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	// End ThirdPersonTemplate
}

void AAudioPawnWalking::BeginPlayAsThirdPerson() const {
	//Start ThirdPersonTemplate
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
	}
	//End ThirdPersonTemplate
}

void AAudioPawnWalking::SetupInputAsThirdPerson(UInputComponent* PlayerInputComponent) {
	//Start ThirdPersonTemplate
	if (UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Started,
			this,
			&ACharacter::Jump
			);
		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Completed,
			this,
			&ACharacter::StopJumping
			);
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AAudioPawnWalking::Move
			);
		EnhancedInputComponent->BindAction(
			LookAction,
			ETriggerEvent::Triggered,
			this,
			&AAudioPawnWalking::Look
			);
		} else {
			UE_LOG(
				LogTemp,
				Error,
				TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."),
				*GetNameSafe(this)
				);
		}
	//End ThirdPersonTemplate
}

void AAudioPawnWalking::MoveAsThirdPerson(const FInputActionValue& Value) {
	//Start ThirdPersonTemplate
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
	//End ThirdPersonTemplate
}

void AAudioPawnWalking::LookAsThirdPerson(const FInputActionValue& Value) {
	//Start ThirdPersonTemplate
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	//End ThirdPersonTemplate
}