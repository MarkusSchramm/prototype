/**
 * @file NotchFilterNode.cpp
 * @brief MetaSound operator and node for real-time audio notch filtering.
 *
 * This file defines a MetaSound operator and facade node that wraps the FNotchFilter DSP processor,
 * enabling real-time audio filtering through MetaSound graphs in Unreal Engine.
 */


#include "NotchFilterNode.h"

#define LOCTEXT_NAMESPACE "BluSumMetasound_NotchFilterNode"

namespace BachelorMetasound::NotchFilterNode {
	// Input params
	METASOUND_PARAM(InParamNameAudioInput, "In", "Audio input.")
	METASOUND_PARAM(InParamNameFrequency, "Frequency", "Frequency of sample.")
	METASOUND_PARAM(InParamNameCutoff, "Cutoff", "Cutoff frequency.")
	METASOUND_PARAM(InParamNameBandwidth, "Bandwidth", "Bandwidth coefficient.")
	// Output params
	METASOUND_PARAM(OutParamNameAudio, "Out", "Audio output.")
}

BachelorMetasound::FNotchFilterOperator::FNotchFilterOperator(
    const Metasound::FOperatorSettings& InSettings, 
    const Metasound::FAudioBufferReadRef& InAudioInput, 
    const Metasound::FFloatReadRef& InSampleFrequency, 
    const Metasound::FFloatReadRef& InCutoffFrequency, 
    const Metasound::FFloatReadRef& InBandwidthCoefficients
) : AudioInput(InAudioInput),
	AudioOutput(Metasound::FAudioBufferWriteRef::CreateNew(InSettings)),
	SampleFrequency(InSampleFrequency),
	CutoffFrequency(InCutoffFrequency),
	BandwidthCoefficients(InBandwidthCoefficients) {}

const Metasound::FNodeClassMetadata& BachelorMetasound::FNotchFilterOperator::GetNodeInfo() {
	auto InitNodeInfo = []() -> Metasound::FNodeClassMetadata {
		Metasound::FNodeClassMetadata Info;
		Info.ClassName = { TEXT("UE"), TEXT("Notch"), TEXT("Audio") };
		Info.MajorVersion = 1;
		Info.MinorVersion = 0;
		Info.DisplayName = LOCTEXT("BluSumMetasound_NotchFilterDisplayName", "Notch Filter");
		Info.Description = LOCTEXT("BluSumMetasound_NotchFilterNodeDescription", "Applies notch filter to the audio input.");
		Info.Author = Metasound::PluginAuthor;
		Info.PromptIfMissing = Metasound::PluginNodeMissingPrompt;
		Info.DefaultInterface = GetVertexInterface();
		Info.CategoryHierarchy = { LOCTEXT("BluSumMetasound_NotchFilterNodeCategory", "Filters") };
		return Info;
		};
	static const Metasound::FNodeClassMetadata Info = InitNodeInfo();
	return Info;
}

const Metasound::FVertexInterface& BachelorMetasound::FNotchFilterOperator::GetVertexInterface() {
	using namespace Metasound;
	using namespace NotchFilterNode;
	static const FVertexInterface Interface(
		FInputVertexInterface(
			TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput)),
			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameFrequency), 20000.f),
			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameCutoff), 20000.f),
			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameBandwidth), 0.f)
		),

		FOutputVertexInterface(
			TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutParamNameAudio))
		)
	);
	return Interface;
}

TUniquePtr<Metasound::IOperator> BachelorMetasound::FNotchFilterOperator::CreateOperator(
	const Metasound::FBuildOperatorParams& InParams, 
	Metasound::FBuildResults& OutResults
) {
		using namespace Metasound;
		using namespace NotchFilterNode;
		FAudioBufferReadRef AudioIn
			= InParams.InputData.GetOrConstructDataReadReference<FAudioBuffer>(
				METASOUND_GET_PARAM_NAME(InParamNameAudioInput),
				InParams.OperatorSettings
			);
		FFloatReadRef InFrequency
			= InParams.InputData.GetOrCreateDefaultDataReadReference<float>(
				METASOUND_GET_PARAM_NAME(InParamNameFrequency),
				InParams.OperatorSettings
			);
		FFloatReadRef InCutoff
			= InParams.InputData.GetOrCreateDefaultDataReadReference<float>(
				METASOUND_GET_PARAM_NAME(InParamNameCutoff),
				InParams.OperatorSettings
			);
		FFloatReadRef InBandwidth
			= InParams.InputData.GetOrCreateDefaultDataReadReference<float>(
				METASOUND_GET_PARAM_NAME(InParamNameBandwidth),
				InParams.OperatorSettings
			);
		return MakeUnique<FNotchFilterOperator>(
			InParams.OperatorSettings, 
			AudioIn, 
			InFrequency, 
			InCutoff, 
			InBandwidth);
}

void BachelorMetasound::FNotchFilterOperator::BindInputs(Metasound::FInputVertexInterfaceData& InOutVertexData) {
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(NotchFilterNode::InParamNameAudioInput), AudioInput);
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(NotchFilterNode::InParamNameFrequency), SampleFrequency);
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(NotchFilterNode::InParamNameCutoff), CutoffFrequency);
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(NotchFilterNode::InParamNameBandwidth), BandwidthCoefficients);
}

void BachelorMetasound::FNotchFilterOperator::BindOutputs(Metasound::FOutputVertexInterfaceData& InOutVertexData) {
	InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(NotchFilterNode::OutParamNameAudio), AudioOutput);
}

void BachelorMetasound::FNotchFilterOperator::Execute() {
	const float* InputAudio = AudioInput->GetData();
	float* OutputAudio = AudioOutput->GetData();

	const int32 NumSamples = AudioInput->Num();

	NotchFilterProcessor.SetValues(
		*SampleFrequency, 
		*CutoffFrequency, 
		*BandwidthCoefficients);
	NotchFilterProcessor.Process(InputAudio, OutputAudio, NumSamples);
}

namespace BachelorMetasound {
	METASOUND_REGISTER_NODE(FNotchFilterNode)
}

#undef LOCTEXT_NAMESPACE