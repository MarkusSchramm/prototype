/**
 * @file VolumeNode.cpp
 * @brief MetaSound operator and node for applying real-time volume control.
 *
 * This file defines a MetaSound-compatible operator and node that wraps the
 * FBachelorVolume DSP processor, allowing amplitude scaling in MetaSound graphs.
 */

#include "VolumeNode.h"

#define LOCTEXT_NAMESPACE "BluSumMetasound_VolumeNode"

namespace BachelorMetasound::VolumeNode {
	// Input params
	METASOUND_PARAM(InParamNameAudioInput, "In", "Audio input.")
	METASOUND_PARAM(InParamNameAmplitude, "Amplitude", "The amount of amplitude to apply to the input signal.")

	// Output params
	METASOUND_PARAM(OutParamNameAudio, "Out", "Audio output.")
}

BachelorMetasound::FVolumeOperator::FVolumeOperator(const Metasound::FOperatorSettings& InSettings,
	const Metasound::FAudioBufferReadRef& InAudioInput, const Metasound::FFloatReadRef& InAmplitude)
	:	Amplitude(InAmplitude),
		AudioInput(InAudioInput),
		AudioOutput(Metasound::FAudioBufferWriteRef::CreateNew(InSettings)) {}

const Metasound::FNodeClassMetadata& BachelorMetasound::FVolumeOperator::GetNodeInfo() {
	auto InitNodeInfo = []() -> Metasound::FNodeClassMetadata {
			Metasound::FNodeClassMetadata Info;
			Info.ClassName = { TEXT("UE"), TEXT("Volume"), TEXT("Audio") };
			Info.MajorVersion = 1;
			Info.MinorVersion = 0;
			Info.DisplayName = LOCTEXT("DSPTemplate_VolumeDisplayName", "Volume");
			Info.Description = LOCTEXT("DSPTemplate_VolumeNodeDescription", "Applies volume to the audio input.");
			Info.Author = Metasound::PluginAuthor;
			Info.PromptIfMissing = Metasound::PluginNodeMissingPrompt;
			Info.DefaultInterface = GetVertexInterface();
			Info.CategoryHierarchy = { LOCTEXT("DSPTemplate_VolumeNodeCategory", "Utils") };
			return Info;
		};
	static const Metasound::FNodeClassMetadata Info = InitNodeInfo();
	return Info;
}

const Metasound::FVertexInterface& BachelorMetasound::FVolumeOperator::GetVertexInterface() {
	using namespace Metasound;
	using namespace VolumeNode;
	static const FVertexInterface Interface(
		FInputVertexInterface(
			TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(VolumeNode::InParamNameAudioInput)),
			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(VolumeNode::InParamNameAmplitude), 1.0f)
		),

		FOutputVertexInterface(
			TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(VolumeNode::OutParamNameAudio))
		)
	);
	return Interface;
}

TUniquePtr<Metasound::IOperator> BachelorMetasound::FVolumeOperator::CreateOperator(
	const Metasound::FBuildOperatorParams& InParams, Metasound::FBuildResults& OutResults) {
	using namespace Metasound;
	using namespace VolumeNode;
	FAudioBufferReadRef AudioIn
		= InParams.InputData.GetOrConstructDataReadReference<FAudioBuffer>(
			METASOUND_GET_PARAM_NAME(InParamNameAudioInput), 
			InParams.OperatorSettings
		);
	FFloatReadRef InAmplitude
		= InParams.InputData.GetOrCreateDefaultDataReadReference<float>(
			METASOUND_GET_PARAM_NAME(InParamNameAmplitude), 
			InParams.OperatorSettings
		);
	return MakeUnique<FVolumeOperator>(InParams.OperatorSettings, AudioIn, InAmplitude);
}

void BachelorMetasound::FVolumeOperator::BindInputs(Metasound::FInputVertexInterfaceData& InOutVertexData) {
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(VolumeNode::InParamNameAudioInput), AudioInput);
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(VolumeNode::InParamNameAmplitude), Amplitude);
}

void BachelorMetasound::FVolumeOperator::BindOutputs(Metasound::FOutputVertexInterfaceData& InOutVertexData) {
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(VolumeNode::OutParamNameAudio), AudioOutput);
}

void BachelorMetasound::FVolumeOperator::Execute() {
	const float* InputAudio = AudioInput->GetData();
	float* OutputAudio = AudioOutput->GetData();

	const int32 NumSamples = AudioInput->Num();

	VolumeDSPProcessor.SetAmplitude(*Amplitude);
	VolumeDSPProcessor.Process(InputAudio, OutputAudio, NumSamples);
}

namespace BachelorMetasound {
	METASOUND_REGISTER_NODE(FVolumeNode)
}

#undef LOCTEXT_NAMESPACE