/**
 * @file NotchFilterMetasound.h
 * @brief MetaSound operator and node for real-time audio notch filtering.
 *
 * This file defines a MetaSound operator and facade node that wraps the FNotchFilter DSP processor,
 * enabling real-time audio filtering through MetaSound graphs in Unreal Engine.
 */

#pragma once

#include "CoreMinimal.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundParamHelper.h"
#include "DSP/NotchFilter.h"

namespace BachelorMetasound {

	/**
	 * @class FNotchFilterOperator
	 * @brief MetaSound operator for applying a notch filter to audio buffers.
	 * 
	 * This operator connects to a MetaSound graph, receives audio and filter parameters,
	 * and processes the audio stream using an internal BachelorDSP::FNotchFilter instance.
	 */
	class FNotchFilterOperator final : public Metasound::TExecutableOperator<FNotchFilterOperator> {
	public:
		/**
		 * @brief Constructs a notch filter operator with references to graph inputs.
		 * 
		 * @param InSettings Operator settings including block size and sample rate.
		 * @param InAudioInput Input audio stream (read reference).
		 * @param InSampleFrequency Sample rate used for DSP computation.
		 * @param InCutoffFrequency Frequency to attenuate.
		 * @param InBandwidthCoefficients Controls the width of the notch.
		 */
		FNotchFilterOperator(
			const Metasound::FOperatorSettings& InSettings,
			const Metasound::FAudioBufferReadRef& InAudioInput,
			const Metasound::FFloatReadRef& InSampleFrequency,
			const Metasound::FFloatReadRef& InCutoffFrequency,
			const Metasound::FFloatReadRef& InBandwidthCoefficients
		);

		/**
		 * @brief Returns metadata for editor and runtime description of the node.
		 */
		static const Metasound::FNodeClassMetadata& GetNodeInfo();

		/**
		 * @brief Describes the inputs and outputs of the operator in the MetaSound graph.
		 */
		static const Metasound::FVertexInterface& GetVertexInterface();

		/**
		 * @brief Factory method for creating an instance of the operator.
		 * 
		 * @param InParams Parameters for operator instantiation.
		 * @param OutResults Result output container (includes errors, warnings).
		 * @return Unique pointer to a new operator instance.
		 */
		static TUniquePtr<Metasound::IOperator> CreateOperator(
			const Metasound::FBuildOperatorParams& InParams,
			Metasound::FBuildResults& OutResults
		);

		/**
		 * @brief Binds MetaSound graph inputs to internal references.
		 * 
		 * @param InOutVertexData Vertex interface data (runtime-bound).
		 */
		virtual void BindInputs(Metasound::FInputVertexInterfaceData& InOutVertexData) override;

		/**
		 * @brief Binds MetaSound graph outputs to internal references.
		 * 
		 * @param InOutVertexData Vertex interface data (runtime-bound).
		 */
		virtual void BindOutputs(Metasound::FOutputVertexInterfaceData& InOutVertexData) override;

		/**
		 * @brief Called every block to process the input buffer with the notch filter.
		 */
		void Execute();

	private:
		/** Instance of the notch filter DSP processor. */
		BachelorDSP::FNotchFilter NotchFilterProcessor;

		/** Input audio stream reference. */
		Metasound::FAudioBufferReadRef AudioInput;

		/** Output audio stream reference. */
		Metasound::FAudioBufferWriteRef AudioOutput;

		/** Sampling frequency input (used to update filter coefficients). */
		Metasound::FFloatReadRef SampleFrequency;

		/** Center frequency for the notch filter. */
		Metasound::FFloatReadRef CutoffFrequency;

		/** Width of the frequency range to attenuate. */
		Metasound::FFloatReadRef BandwidthCoefficients;
	};

	/**
	 * @class FNotchFilterNode
	 * @brief MetaSound node facade for use in the Unreal MetaSound graph editor.
	 * 
	 * Wraps the FNotchFilterOperator and provides editor integration.
	 */
	class FNotchFilterNode final : public Metasound::FNodeFacade {
	public:
		/**
		 * @brief Constructor for the notch filter node.
		 * 
		 * @param InitData Initialization metadata including node name and instance ID.
		 */
		explicit FNotchFilterNode(const Metasound::FNodeInitData& InitData)
			: Metasound::FNodeFacade(
				InitData.InstanceName,
				InitData.InstanceID,
				Metasound::TFacadeOperatorClass<FNotchFilterOperator>()
			) {}
	};

}
