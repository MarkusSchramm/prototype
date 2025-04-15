/**
 * @file TestingHelper\Private\Concepts.h
 * @author Markus Schramm
 * @brief Namespace-scoped concepts for reuse
 */

#pragma once

namespace BachelorHelper::TestingHelper {
	/**
	 * @brief Concept to only allow actors with tag Bachelor.
	 *
	 * So we can iterate the user-created actors only.
	 */
	template <typename T>
	concept ue_actor = std::is_base_of_v<AActor, T>;

	template <typename T>
	concept testable = requires (T x) {
		{ x.GetName() } -> std::same_as<FString>;
		{ x.GetActorLocation() } -> std::same_as<FVector>;
		{ x.GetActorRotation() } -> std::same_as<FRotator>;
		{ x.SpawnCollisionHandlingMethod } -> std::same_as<ESpawnActorCollisionHandlingMethod&>;
	};
}

#define TESTABLE_TAG FName("Testable")