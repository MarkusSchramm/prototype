/**
 * @file VolumeNode.h
 * @brief MetaSound operator and node for applying real-time volume control.
 *
 * This file defines a MetaSound-compatible operator and node that wraps the
 * FBachelorVolume DSP processor, allowing amplitude scaling in MetaSound graphs.
 */

#pragma once

#include "CoreMinimal.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundParamHelper.h"
#include "DSP/BachelorVolume.h"

namespace BachelorMetasound {
	/**
	 * @class FVolumeOperator
	 * @brief MetaSound operator for real-time volume (gain) processing.
	 * 
	 * Applies linear amplitude scaling to incoming audio using the BachelorDSP::FBachelorVolume processor.
	 * This operator is designed for integration within Unreal Engine's MetaSound system.
	 */
	class FVolumeOperator final : public Metasound::TExecutableOperator<FVolumeOperator> {
	public:
		/**
		 * @brief Constructs a volume operator with references to input parameters.
		 * 
		 * @param InSettings MetaSound operator settings (e.g., block size, sample rate).
		 * @param InAudioInput Audio input buffer to be processed.
		 * @param InAmplitude Scalar amplitude (gain multiplier).
		 */
		FVolumeOperator(
			const Metasound::FOperatorSettings& InSettings, 
			const Metasound::FAudioBufferReadRef& InAudioInput, 
			const Metasound::FFloatReadRef& InAmplitude
		);

		/**
		 * @brief Provides static metadata describing the node for editor/runtime registration.
		 * 
		 * @return Reference to class metadata structure.
		 */
		static const Metasound::FNodeClassMetadata& GetNodeInfo();

		/**
		 * @brief Describes the MetaSound inputs and outputs for this operator.
		 * 
		 * @return Reference to a vertex interface structure defining ports.
		 */
		static const Metasound::FVertexInterface& GetVertexInterface();

		/**
		 * @brief Factory method to create a new volume operator instance.
		 * 
		 * @param InParams Parameters needed to build the operator (e.g., input map).
		 * @param OutResults Contains success/failure status and any build messages.
		 * @return Unique pointer to a valid MetaSound operator.
		 */
		static TUniquePtr<Metasound::IOperator> CreateOperator(
			const Metasound::FBuildOperatorParams& InParams, 
			Metasound::FBuildResults& OutResults
		);

		/**
		 * @brief Binds graph inputs to internal data references.
		 * 
		 * @param InOutVertexData The input vertex map passed from MetaSound runtime.
		 */
		virtual void BindInputs(Metasound::FInputVertexInterfaceData& InOutVertexData) override;

		/**
		 * @brief Binds graph outputs to internal output reference.
		 * 
		 * @param InOutVertexData The output vertex map passed from MetaSound runtime.
		 */
		virtual void BindOutputs(Metasound::FOutputVertexInterfaceData& InOutVertexData) override;

		/**
		 * @brief Executes volume processing on the audio buffer per block.
		 */
		void Execute();

	private:
		/** Instance of the BachelorDSP volume processor. */
		BachelorDSP::FBachelorVolume VolumeDSPProcessor;

		/** Reference to input audio buffer from the MetaSound graph. */
		Metasound::FAudioBufferReadRef AudioInput;

		/** Reference to output buffer for processed (volume-scaled) audio. */
		Metasound::FAudioBufferWriteRef AudioOutput;

		/** Gain value applied to the audio signal. */
		Metasound::FFloatReadRef Amplitude;
	};

	/**
	 * @class FVolumeNode
	 * @brief MetaSound node facade for the volume processor.
	 * 
	 * Registers the FVolumeOperator for use in the MetaSound editor and runtime.
	 */
	class FVolumeNode final : public Metasound::FNodeFacade {
	public:
		/**
		 * @brief Constructs the volume node facade.
		 * 
		 * @param InitData Node instance metadata (e.g., name, ID).
		 */
		explicit FVolumeNode(const Metasound::FNodeInitData& InitData)
			: Metasound::FNodeFacade(
				InitData.InstanceName, 
				InitData.InstanceID, 
				Metasound::TFacadeOperatorClass<FVolumeOperator>())
		{}
	};

}