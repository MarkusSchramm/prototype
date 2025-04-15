/**
 * @file WorldFixture.h
 * @author Markus Schramm
 */

#pragma once

#include "GameFramework/WorldSettings.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/EngineBaseTypes.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "EngineUtils.h"
#include "TestingHelperModule.h"

namespace BachelorHelper::TestingHelper {
	/**
	 * @class FWorldFixture
	 * @brief A utility class for creating and managing test worlds in automation tests.
	 *
	 * FWorldFixture creates a temporary game world that can be used for testing purposes.
	 * It handles world initialization, actor spawning, and proper cleanup when tests are complete.
	 */
	class TESTINGHELPER_API FWorldFixture final {
	public:
		/**
		 * @brief Constructs a new FWorldFixture with an optional URL.
		 * @param URL Optional URL to use when initializing the world.
		 * 
		 * Creates a new UWorld for testing, initializes it for gameplay,
		 * and performs necessary setup for actor initialization.
		 */
		explicit FWorldFixture(const FURL& URL = FURL()) {
			if(GEngine == nullptr) return;
			static uint32 WorldCounter = 0;
			const FString WorldName = FString::Printf(TEXT("TestWorld_%d"), WorldCounter++);
			if(UWorld* World = UWorld::CreateWorld(
				EWorldType::Game,
				false,
				*WorldName,
				GetTransientPackage())
				) {
				FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);
				WorldContext.SetCurrentWorld(World);
				World->InitializeActorsForPlay(URL);
				if(IsValid(World->GetWorldSettings())) {
					World->GetWorldSettings()->NotifyBeginPlay();
					World->GetWorldSettings()->NotifyMatchStarted();
				}
				World->BeginPlay();
				WeakWorld = MakeWeakObjectPtr(World);
				UE_LOG(LogTestingHelper, Log, TEXT("'%s' constructed"), *WeakWorld->GetName());
			}
		}

		/**
		 * @brief Destroys the FWorldFixture and cleans up the test world.
		 * 
		 * Tears down the world, destroys all actors in the world,
		 * and cleans up the world context.
		 */
		~FWorldFixture() {
			UWorld* World = WeakWorld.Get();
			if(World != nullptr && GEngine != nullptr) {
				UE_LOG(LogTestingHelper, Log, TEXT("'%s' begin destruction"), *WeakWorld->GetName());
				World->BeginTearingDown();
				for(auto It = TActorIterator<AActor>(World); It; ++It) { It->Destroy(); }
				GEngine->DestroyWorldContext(World);
				World->DestroyWorld(false);
				UE_LOG(LogTestingHelper, Log, TEXT("WorldFixture destructed"));
			}
		}

		/**
		 * @brief Gets the current test world.
		 * @return A pointer to the UWorld being used for testing.
		 */		
		UWorld* GetWorld() const {
			UE_LOG(LogTestingHelper, Log, TEXT("'%s' pointer ordered"), *WeakWorld->GetName());
			return WeakWorld.Get();
		}

		/**
		 * @brief Ticks (updates) the test world by the specified delta time.
		 * @param DeltaTime The time to advance the world simulation, in seconds. Defaults to 0.016s (about 60fps).
		 * @return true if the world was ticked successfully, false otherwise.
		 */
		bool TickWorld(float DeltaTime = .016f) const {
			if(!WeakWorld.IsValid()) return false;
			WeakWorld->Tick(LEVELTICK_All, DeltaTime);
			float actualDelta = GetWorld()->GetDeltaSeconds();
			UE_LOG(LogTestingHelper, Log, TEXT("Ticking TestWorld with %fms --> FPS: %f"), actualDelta, 1.f / actualDelta);
			return true;
		}

		/**
		 * @brief Spawns a test actor of the specified type at the given location and rotation.
		 * @tparam T The class of actor to spawn.
		 * @param Location The world location to spawn the actor at. Defaults to origin.
		 * @param Rotation The rotation to spawn the actor with. Defaults to zero rotation.
		 * @return A pointer to the newly spawned actor, or nullptr if spawning failed.
		 */
		template<class T>
		T* SpawnTestActor(
			const FVector& Location = FVector::ZeroVector,
			const FRotator& Rotation = FRotator::ZeroRotator
			) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			const auto actor = WeakWorld->SpawnActor<T>(Location, Rotation, SpawnParams);
			UE_LOG(LogTestingHelper, Log, TEXT("'%s' spawned"), *actor->GetName());
			UE_LOG(LogTestingHelper, Log, TEXT("Location:\t[x] %f\t[y] %f\t[z] %f"), Location.X, Location.Y, Location.Z);
			UE_LOG(LogTestingHelper, Log, TEXT("Rotation:\t[roll] %f\t[pitch] %f\t[yaw] %f"), Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
			return actor;
		}

		/**
		 * @brief Spawns a test actor of the specified type with custom spawn parameters.
		 * @tparam T The class of actor to spawn.
		 * @param SpawnParams The parameters to use when spawning the actor.
		 * @return A pointer to the newly spawned actor, or nullptr if spawning failed.
		 */
		template<class T>
		T* SpawnTestActorWithParams(
			const FActorSpawnParameters& SpawnParams
			) {
			const auto actor = WeakWorld->SpawnActor<T>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			UE_LOG(LogTestingHelper, Log, TEXT("'%s_WithParams' spawned"), *actor->GetName());
			UE_LOG(LogTestingHelper, Log, TEXT("Location:\t[x] 0\t[y] 0\t[z] 0"));
			UE_LOG(LogTestingHelper, Log, TEXT("Rotation:\t[roll] 0\t[pitch] 0\t[yaw] 0"));
			return actor;
		}

		/**
		 * @brief Spawns a test actor with full control over location, rotation, and spawn parameters.
		 * @tparam T The class of actor to spawn.
		 * @param Location The world location to spawn the actor at.
		 * @param Rotation The rotation to spawn the actor with.
		 * @param SpawnParams The parameters to use when spawning the actor.
		 * @return A pointer to the newly spawned actor, or nullptr if spawning failed.
		 */
		template<class T>
		T* SpawnTestActorComplex(
			const FVector& Location,
			const FRotator& Rotation,
			const FActorSpawnParameters& SpawnParams
			) {
			const auto actor = WeakWorld->SpawnActor<T>(Location, Rotation, SpawnParams);
			UE_LOG(LogTestingHelper, Log, TEXT("'%s_Complex' spawned"), *actor->GetName());
			UE_LOG(LogTestingHelper, Log, TEXT("Location:\t[x] %f\t[y] %f\t[z] %f"), Location.X, Location.Y, Location.Z);
			UE_LOG(LogTestingHelper, Log, TEXT("Rotation:\t[roll] %f\t[pitch] %f\t[yaw] %f"), Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
			return actor;
		}

		/**
		 * @brief Destroys a test actor that was previously spawned.
		 * @param ActorToDestroy The actor to destroy.
		 * @return true if the actor was successfully destroyed, false otherwise.
		 */
		bool DestroyTestActor(AActor* ActorToDestroy) const {
			UE_LOG(LogTestingHelper, Log, TEXT("'%s' destroyed"), *ActorToDestroy->GetName());
			return WeakWorld->DestroyActor(ActorToDestroy);
		}

	private:
		// Weak pointer to the test world to prevent memory leaks.
		TWeakObjectPtr<UWorld> WeakWorld;
	};
}

/**
 *	@defgroup WorldFixtureDefs
 *	@brief Macros used for worldfixture creation.
 *	@see WORLD_FIXTURE
 *	@see POINTER_RAW_WORLD_FIXTURE
 *	@see MAKE_RAW_WORLD_FIXTURE
 *	@see MAKE_AND_INIT_RAW_WORLD_FIXTURE
 *	@see RESET_RAW_WORLD_FIXTURE
 *	@see POINTER_UNIQUE_WORLD_FIXTURE
 *	@see MAKE_UNIQUE_WORLD_FIXTURE
 *	@see MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE
 */

/**
 * @def WORLD_FIXTURE
 * @brief Shorthand for the FWorldFixture class.
 */
#define WORLD_FIXTURE BachelorHelper::TestingHelper::FWorldFixture

/**
 * @def POINTER_RAW_WORLD_FIXTURE
 * @brief Shorthand for a raw pointer to FWorldFixture.
 */
#define POINTER_RAW_WORLD_FIXTURE BachelorHelper::TestingHelper::FWorldFixture*

/**
 * @def MAKE_RAW_WORLD_FIXTURE
 * @brief Creates a new raw FWorldFixture pointer.
 */
#define MAKE_RAW_WORLD_FIXTURE new BachelorHelper::TestingHelper::FWorldFixture()

/**
 * @def MAKE_AND_INIT_RAW_WORLD_FIXTURE
 * @brief Creates and initializes a raw FWorldFixture pointer named WorldFixture.
 */
#define MAKE_AND_INIT_RAW_WORLD_FIXTURE BachelorHelper::TestingHelper::FWorldFixture* WorldFixture = new BachelorHelper::TestingHelper::FWorldFixture()

/**
 * @def RESET_RAW_WORLD_FIXTURE
 * @brief Deletes the WorldFixture and sets it to nullptr.
 */
#define RESET_RAW_WORLD_FIXTURE delete WorldFixture; WorldFixture = nullptr

/**
 * @def POINTER_UNIQUE_WORLD_FIXTURE
 * @brief Creates a new unique FWorldFixture pointer.
 */
#define POINTER_UNIQUE_WORLD_FIXTURE TUniquePtr<BachelorHelper::TestingHelper::FWorldFixture>

/**
 * @def MAKE_UNIQUE_WORLD_FIXTURE
 * @brief Creates a new unique FWorldFixture pointer.
 */
#define MAKE_UNIQUE_WORLD_FIXTURE MakeUnique<BachelorHelper::TestingHelper::FWorldFixture>()

/**
 * @def MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE
 * @brief Creates and initializes a unique FWorldFixture pointer named WorldFixture.
 */
#define MAKE_AND_INIT_UNIQUE_WORLD_FIXTURE TUniquePtr<BachelorHelper::TestingHelper::FWorldFixture> WorldFixture = MakeUnique<BachelorHelper::TestingHelper::FWorldFixture>()