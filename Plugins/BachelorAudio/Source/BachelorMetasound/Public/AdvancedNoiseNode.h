/**
 * @file AdvancedNoiseNode.h
 * @author Markus Schramm
 * @brief Defines a MetaSound node facade for advanced configurable noise generation.
 *
 * The node includes parameters for noise seed, frequency shaping, bandwidth control, and output gain.
 * This class serves as a facade and interface definition for the MetaSound graph editor and runtime system.
 */

#pragma once

#include "CoreMinimal.h"
#include "MetasoundFacade.h"
#include "MetasoundVertex.h"

namespace Metasound {

	/**
	 * @class FAdvancedNoiseNode
	 * @brief MetaSound facade node for advanced procedural noise generation.
	 * 
	 * This node exposes user-configurable parameters to control procedural noise shaping.
	 * Internally, it is expected to delegate processing to a corresponding operator
	 * (not shown here), allowing flexibility in runtime behavior.
	 */
	class BACHELORMETASOUND_API FAdvancedNoiseNode final : public FNodeFacade {
	public:
		/**
		 * @brief Constructs the node with explicit default values for parameters.
		 * 
		 * @param InName The unique name of the node instance in the MetaSound graph.
		 * @param InInstanceID A globally unique identifier (GUID) for this node.
		 * @param InDefaultSeed Default seed value used for pseudo-random noise generation.
		 * @param InDefaultFrequency Central frequency of the noise shaping filter (Hz).
		 * @param InDefaultBandwidth Bandwidth of the noise spectrum (Hz).
		 * @param InDefaultGain Linear output gain multiplier.
		 */
		FAdvancedNoiseNode(
			const FVertexName& InName,
			const FGuid& InInstanceID,
			int32 InDefaultSeed,
			float InDefaultFrequency,
			float InDefaultBandwidth,
			float InDefaultGain
		);

		/**
		 * @brief Constructs the node using initialization metadata from the graph system.
		 * 
		 * @param InitData Metadata used by the MetaSound system to initialize the node.
		 */
		explicit FAdvancedNoiseNode(const FNodeInitData& InitData);

		/**
		 * @brief Gets the default noise seed value.
		 * 
		 * @return Default integer seed used for noise generation.
		 */
		FORCEINLINE int32 GetDefaultSeed() const { return DefaultSeed; }

		/**
		 * @brief Gets the default frequency value.
		 * 
		 * @return Center frequency in Hz used for shaping the noise.
		 */
		FORCEINLINE float GetDefaultFrequency() const { return DefaultFrequency; }

		/**
		 * @brief Gets the default bandwidth value.
		 * 
		 * @return Bandwidth around the center frequency in Hz.
		 */
		FORCEINLINE float GetDefaultBandwidth() const { return DefaultBandwidth; }

		/**
		 * @brief Gets the default gain value.
		 * 
		 * @return Linear amplitude multiplier for the noise output.
		 */
		FORCEINLINE float GetDefaultGain() const { return DefaultGain; }

	private:
		/** Seed value used for initializing the noise generator. */
		int32 DefaultSeed = -1;

		/** Central shaping frequency in Hz. */
		float DefaultFrequency = 2000.f;

		/** Bandwidth applied around the central frequency in Hz. */
		float DefaultBandwidth = 0.f;

		/** Output gain applied to the final noise signal. */
		float DefaultGain = 0.f;
	};

}


