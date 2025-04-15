/** 
 * @file AdvancedNoiseNode.cpp
 * @author Markus Schramm
 */

#include "AdvancedNoiseNode.h"

#include "MetasoundParamHelper.h"
#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundFacade.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "MetasoundDataTypeRegistrationMacro.h"
#include "MetasoundOperatorSettings.h"
#include "MetasoundPrimitives.h"
#include "MetasoundTrigger.h"
#include "MetasoundVertex.h"
#include "DSP/Noise.h"

#define LOCTEXT_NAMESPACE "BachelorMetasound_AdvancedNoiseNode"

namespace Metasound {
	enum class EAdvancedNoiseType : uint8 {
		Pink	= 0,
		White	= 1,
		Brown	= 2,
		Green	= 3
	};

	DECLARE_METASOUND_ENUM(
		EAdvancedNoiseType,
		EAdvancedNoiseType::Pink,
		BACHELORMETASOUND_API,
		FEnumAdvancedNoiseType,
		FEnumAdvancedNoiseTypeInfo,
		FEnumAdvancedNoiseTypeReadRef,
		FEnumAdvancedNoiseTypeWriteRef
		);

	DEFINE_METASOUND_ENUM_BEGIN(EAdvancedNoiseType, FEnumAdvancedNoiseType, "AdvancedNoiseType")
		DEFINE_METASOUND_ENUM_ENTRY(
			EAdvancedNoiseType::Pink,
			"PinkDescription", "Pink Noise", "PinkDescriptionTT",
			"Pink noise or 1/f noise, spectral density is inversely proportional to the frequency of the signal"
			),
		DEFINE_METASOUND_ENUM_ENTRY(
			EAdvancedNoiseType::White,
			"WhiteDescription", "White Noise", "WhiteDescriptionTT",
			"A random signal having equal intensity at different frequencies"
			),
		DEFINE_METASOUND_ENUM_ENTRY(
			EAdvancedNoiseType::Brown,
			"BrownDescription", "Brown Noise", "BrownDescriptionTT",
			"A random signal generated from white noise having additional random frequencies"
			),
		DEFINE_METASOUND_ENUM_ENTRY(
			EAdvancedNoiseType::Green,
			"GreenDescription", "Green Noise", "GreenDescriptionTT",
			"A random signal having most intensity at 2000Hz, can be adjusted"
			),
	DEFINE_METASOUND_ENUM_END()
	
	namespace AdvancedNoiseGeneratorVertexNames {
		// Input params
		METASOUND_PARAM(InputSeed, "Seed", "Start seed for generating noise.")
		METASOUND_PARAM(InputType, "Type", "Type of Noise to Generate.")
		METASOUND_PARAM(InputFrequency, "Frequency",
			"Frequency Noise is centered on, only recognizable, if gain manually set.")
		METASOUND_PARAM(InputBandwidth, "Bandwidth",
			"Bandwidth of noise passed. 0 = all passes, 0,707 = Standard Green Noise. Only used at Green Noise!")
		METASOUND_PARAM(InputGain, "Gain (db)",
			"Gain to apply at frequency.")

		// Output params
		METASOUND_PARAM(OutAudio, "Out", "Audio output.")
	}
		
	class FAdvancedNoiseOperator : public IOperator {//TExecutableOperator<FAdvancedNoiseOperator> {
	public:
		static constexpr int32 DefaultSeed = INDEX_NONE;
		static constexpr float DefaultFrequency = 2000.f;
		static constexpr float DefaultBandwidth = 0.f;
		static constexpr float DefaultGain = 0.f;

		static const FNodeClassMetadata& GetNodeInfo();
		static FVertexInterface DeclareVertexInterface();
		static TUniquePtr<IOperator> CreateOperator(
			const FBuildOperatorParams& InParams,
			FBuildResults& OutResults
			);

		FAdvancedNoiseOperator(
			const FOperatorSettings& InSettings,
			FInt32ReadRef InSeedReadRef,
			FEnumAdvancedNoiseTypeReadRef InNoiseTypeReadRef,
			FFloatReadRef InFrequencyReadRef,
			FFloatReadRef InBandwidthReadRef,
			FFloatReadRef InGainReadRef
			);

		virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;
		virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;

		virtual FPostExecuteFunction GetPostExecuteFunction() override { return nullptr; }

		void Execute();

	protected:
		template<typename T>
		static T MakeGenerator(int32 InSeed) {
			if(InSeed == DefaultSeed) return T{};
			return T{InSeed};
		}

		template<typename T>
		void ResetAdvancedNoiseOperator(T& InOutGenerator) {
			InOutGenerator = MakeGenerator<T>(*Seed);
			OldSeed = *Seed;
		}

		template<typename T>
		FORCEINLINE void CheckAndReseed(T& InOutGenerator) {
			int32 newSeed = *Seed;
			if (OldSeed != newSeed) {
				InOutGenerator = MakeGenerator<T>(newSeed);
				OldSeed = newSeed;
			}
		}

		template<typename T>
		FORCEINLINE void Generate(T& InGenerator) {
			float* writePtr = Out->GetData();
			for (int32 i = Out->Num(); i > 0; --i) {
				*writePtr++ = InGenerator.Generate();
			}
		}
		
		FInt32ReadRef Seed;
		FEnumAdvancedNoiseTypeReadRef NoiseType;
		FFloatReadRef Frequency;
		FFloatReadRef Bandwidth;
		FFloatReadRef Gain;
		FAudioBufferWriteRef Out;
		
		int32 OldSeed;
		float OldFrequency;
		float OldBandwidth;
		float OldGain;
	};

	constexpr int32 FAdvancedNoiseOperator::DefaultSeed;
	constexpr float FAdvancedNoiseOperator::DefaultFrequency;
	constexpr float FAdvancedNoiseOperator::DefaultBandwidth;
	constexpr float FAdvancedNoiseOperator::DefaultGain;
	
	struct FAdvancedNoiseOperator_White final : public FAdvancedNoiseOperator {
		Audio::FWhiteNoise Generator;

		FAdvancedNoiseOperator_White(
			const FOperatorSettings& InSettings,
			FInt32ReadRef&& InSeed,
			FEnumAdvancedNoiseTypeReadRef&& InNoiseTypeReadRef,
			FFloatReadRef&& InFrequencyReadRef,
			FFloatReadRef&& InBandwidthReadRef,
			FFloatReadRef&& InGainReadRef
			) : FAdvancedNoiseOperator {
				InSettings,
				MoveTemp(InSeed),
				MoveTemp(InNoiseTypeReadRef),
				MoveTemp(InFrequencyReadRef),
				MoveTemp(InBandwidthReadRef),
				MoveTemp(InGainReadRef) },
				Generator {
					MakeGenerator<Audio::FWhiteNoise>(*Seed)
				}
			{}

		void Reset(const FResetParams& InParams) {
			ResetAdvancedNoiseOperator(Generator);
			Out->Zero();
		}

		void Execute() {
			CheckAndReseed(Generator);
			Generate(Generator);
		}
		
		static void ResetFunction(IOperator* InOperator, const FResetParams& InParams) {
			static_cast<FAdvancedNoiseOperator_White*>(InOperator)->Reset(InParams);
		}
		virtual FResetFunction GetResetFunction() override {
			return &FAdvancedNoiseOperator_White::ResetFunction;
		}

		static void ExecuteFunction(IOperator* InOperator) {
			static_cast<FAdvancedNoiseOperator_White*>(InOperator)->Execute();
		}
		virtual FExecuteFunction GetExecuteFunction() override {
			return &FAdvancedNoiseOperator_White::ExecuteFunction;
		}
	};

	struct FAdvancedNoiseOperator_Pink final : public FAdvancedNoiseOperator {
		Audio::FPinkNoise Generator;

		FAdvancedNoiseOperator_Pink(
			const FOperatorSettings& InSettings,
			FInt32ReadRef&& InSeed,
			FEnumAdvancedNoiseTypeReadRef&& InNoiseTypeReadRef,
			FFloatReadRef&& InFrequencyReadRef,
			FFloatReadRef&& InBandwidthReadRef,
			FFloatReadRef&& InGainReadRef
			) : FAdvancedNoiseOperator {
				InSettings,
				MoveTemp(InSeed),
				MoveTemp(InNoiseTypeReadRef),
				MoveTemp(InFrequencyReadRef),
				MoveTemp(InBandwidthReadRef),
				MoveTemp(InGainReadRef) },
				Generator {
					MakeGenerator<Audio::FPinkNoise>(*Seed)
				}
			{}

		void Reset(const FResetParams& InParams) {
			ResetAdvancedNoiseOperator(Generator);
			Out->Zero();
		}

		void Execute() {
			CheckAndReseed(Generator);
			Generate(Generator);
		}

		static void ResetFunction(IOperator* InOperator, const FResetParams& InParams) {
			static_cast<FAdvancedNoiseOperator_Pink*>(InOperator)->Reset(InParams);
		}
		virtual FResetFunction GetResetFunction() override {
			return &FAdvancedNoiseOperator_Pink::ResetFunction;
		}

		static void ExecuteFunction(IOperator* InOperator) {
			static_cast<FAdvancedNoiseOperator_Pink*>(InOperator)->Execute();
		}
		virtual FExecuteFunction GetExecuteFunction() override {
			return &FAdvancedNoiseOperator_Pink::ExecuteFunction;
		}
	};

	struct FAdvancedNoiseOperator_Brown final : public FAdvancedNoiseOperator {
		Audio::FWhiteNoise Generator;

		FAdvancedNoiseOperator_Brown(
			const FOperatorSettings& InSettings,
			FInt32ReadRef&& InSeed,
			FEnumAdvancedNoiseTypeReadRef&& InNoiseTypeReadRef,
			FFloatReadRef&& InFrequencyReadRef,
			FFloatReadRef&& InBandwidthReadRef,
			FFloatReadRef&& InGainReadRef
			) : FAdvancedNoiseOperator {
				InSettings,
				MoveTemp(InSeed),
				MoveTemp(InNoiseTypeReadRef),
				MoveTemp(InFrequencyReadRef),
				MoveTemp(InBandwidthReadRef),
				MoveTemp(InGainReadRef) },
				Generator {
					MakeGenerator<Audio::FWhiteNoise>(*Seed)
				}
			{}

		void Reset(const FResetParams& InParams) {
			ResetAdvancedNoiseOperator(Generator);
			Out->Zero();
		}

		void Execute() {
			CheckAndReseed(Generator);
			Generate(Generator);
		}
		
		static void ResetFunction(IOperator* InOperator, const FResetParams& InParams) {
			static_cast<FAdvancedNoiseOperator_Brown*>(InOperator)->Reset(InParams);
		}
		virtual FResetFunction GetResetFunction() override {
			return &FAdvancedNoiseOperator_Brown::ResetFunction;
		}

		static void ExecuteFunction(IOperator* InOperator) {
			static_cast<FAdvancedNoiseOperator_Brown*>(InOperator)->Execute();
		}
		virtual FExecuteFunction GetExecuteFunction() override {
			return &FAdvancedNoiseOperator_Brown::ExecuteFunction;
		}
	};

	struct FAdvancedNoiseOperator_Green final : public FAdvancedNoiseOperator {
		Audio::FWhiteNoise Generator;

		FAdvancedNoiseOperator_Green(
			const FOperatorSettings& InSettings,
			FInt32ReadRef&& InSeed,
			FEnumAdvancedNoiseTypeReadRef&& InNoiseTypeReadRef,
			FFloatReadRef&& InFrequencyReadRef,
			FFloatReadRef&& InBandwidthReadRef,
			FFloatReadRef&& InGainReadRef
			) : FAdvancedNoiseOperator {
				InSettings,
				MoveTemp(InSeed),
				MoveTemp(InNoiseTypeReadRef),
				MoveTemp(InFrequencyReadRef),
				MoveTemp(InBandwidthReadRef),
				MoveTemp(InGainReadRef) },
				Generator {
					MakeGenerator<Audio::FWhiteNoise>(*Seed)
				}
			{}

		void Reset(const FResetParams& InParams) {
			ResetAdvancedNoiseOperator(Generator);
			Out->Zero();
		}

		void Execute() {
			CheckAndReseed(Generator);
			Generate(Generator);
		}
		
		static void ResetFunction(IOperator* InOperator, const FResetParams& InParams) {
			static_cast<FAdvancedNoiseOperator_Green*>(InOperator)->Reset(InParams);
		}
		virtual FResetFunction GetResetFunction() override {
			return &FAdvancedNoiseOperator_Green::ResetFunction;
		}

		static void ExecuteFunction(IOperator* InOperator) {
			static_cast<FAdvancedNoiseOperator_Green*>(InOperator)->Execute();
		}
		virtual FExecuteFunction GetExecuteFunction() override {
			return &FAdvancedNoiseOperator_Green::ExecuteFunction;
		}
	};

	FAdvancedNoiseOperator::FAdvancedNoiseOperator(
		const FOperatorSettings& InSettings,
		FInt32ReadRef InSeedReadRef,
		FEnumAdvancedNoiseTypeReadRef InNoiseTypeReadRef,
		FFloatReadRef InFrequencyReadRef,
		FFloatReadRef InBandwidthReadRef,
		FFloatReadRef InGainReadRef
		) : Seed{ MoveTemp(InSeedReadRef) },
			NoiseType{ MoveTemp(InNoiseTypeReadRef) },
			Frequency{ MoveTemp(InFrequencyReadRef) },
			Bandwidth{ MoveTemp(InBandwidthReadRef) },
			Gain{ MoveTemp(InGainReadRef) },
			Out{ FAudioBufferWriteRef::CreateNew(InSettings) },
			OldSeed(*Seed),
			OldFrequency(*Frequency),
			OldBandwidth(*Bandwidth),
			OldGain(*Gain)
		{}

	void FAdvancedNoiseOperator::BindInputs(FInputVertexInterfaceData& InOutVertexData) {
		using namespace AdvancedNoiseGeneratorVertexNames;
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputSeed), Seed);
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputType), NoiseType);
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputFrequency), Frequency);
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputBandwidth), Bandwidth);
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputGain), Gain);
	}

	void FAdvancedNoiseOperator::BindOutputs(FOutputVertexInterfaceData& InOutVertexData) {
		using namespace AdvancedNoiseGeneratorVertexNames;
		InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutAudio), Out);
	}
	
	FVertexInterface FAdvancedNoiseOperator::DeclareVertexInterface() {
    	using namespace AdvancedNoiseGeneratorVertexNames; 
    	static const FVertexInterface Interface(
    	FInputVertexInterface(
    			TInputDataVertex<int32>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputSeed), DefaultSeed),
    			TInputDataVertex<FEnumAdvancedNoiseType>(
    				METASOUND_GET_PARAM_NAME_AND_METADATA(InputType), (int32)EAdvancedNoiseType::Pink
    				),
    			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputFrequency), 2000.f),
    			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputBandwidth), 0.f),
    			TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputGain), 0.f)
			),
		FOutputVertexInterface(
    				TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutAudio))
    			)
			);
    	return Interface;
	}
	
	const FNodeClassMetadata& FAdvancedNoiseOperator::GetNodeInfo() {
		auto InitNodeInfo = []() -> FNodeClassMetadata {
			FNodeClassMetadata Info;
			Info.ClassName = { TEXT("UE"), TEXT("Noise"), TEXT("Generators") };
			Info.MajorVersion = 1;
			Info.MinorVersion = 0;
			Info.DisplayName = METASOUND_LOCTEXT("Metasound_AdvancedNoiseNodeDisplayNameX", "Advanced Noise");
			Info.Description = METASOUND_LOCTEXT("Metasound_AdvancedNoiseNodeDescription",
				"Advanced Noise Generator that produces different types of noise, and gives Control over Gain and Frequency.");
			Info.Author = PluginAuthor;
			Info.PromptIfMissing = PluginNodeMissingPrompt;
			Info.DefaultInterface = DeclareVertexInterface();
			return Info;
		};
		static const FNodeClassMetadata Info = InitNodeInfo();
		return Info;
	}

	FAdvancedNoiseNode::FAdvancedNoiseNode(
		const FVertexName& InName,
		const FGuid& InInstanceID,
		int32 InDefaultSeed,
		float InDefaultFrequency,
		float InDefaultBandwidth,
		float InDefaultGain
		) : FNodeFacade(InName, InInstanceID, TFacadeOperatorClass<FAdvancedNoiseOperator>()),
			DefaultSeed(InDefaultSeed),
			DefaultFrequency(InDefaultFrequency),
			DefaultBandwidth(InDefaultBandwidth),
			DefaultGain(InDefaultGain) {}

	FAdvancedNoiseNode::FAdvancedNoiseNode(const FNodeInitData& InInitData)
		: FAdvancedNoiseNode(
			InInitData.InstanceName,
			InInitData.InstanceID,
			FAdvancedNoiseOperator::DefaultSeed,
			FAdvancedNoiseOperator::DefaultFrequency,
			FAdvancedNoiseOperator::DefaultBandwidth,
			FAdvancedNoiseOperator::DefaultGain
			) {}

	TUniquePtr<IOperator> FAdvancedNoiseOperator::CreateOperator(
		const FBuildOperatorParams& InParams,
		FBuildResults& OutResults
		) {
		using namespace AdvancedNoiseGeneratorVertexNames;
		const FAdvancedNoiseNode& Node = static_cast<const FAdvancedNoiseNode&>(InParams.Node);
		const FDataReferenceCollection& InputCol = InParams.InputData.ToDataReferenceCollection();
		const FOperatorSettings& Settings = InParams.OperatorSettings;
		const FInputVertexInterface& InputInterface = InParams.Node.GetVertexInterface().GetInputInterface();

		// Static property pin, only used for factory.
		FEnumAdvancedNoiseTypeReadRef Type
			= InputCol.GetDataReadReferenceOrConstructWithVertexDefault<FEnumAdvancedNoiseType>(
				InputInterface, METASOUND_GET_PARAM_NAME(InputType), Settings);
		FInt32ReadRef Seed = InputCol.GetDataReadReferenceOrConstructWithVertexDefault<int32>(
			InputInterface, METASOUND_GET_PARAM_NAME(InputSeed), Settings);
		FFloatReadRef Frequency = InputCol.GetDataReadReferenceOrConstructWithVertexDefault<float>(
			InputInterface, METASOUND_GET_PARAM_NAME(InputFrequency), Settings);
		FFloatReadRef Bandwidth = InputCol.GetDataReadReferenceOrConstructWithVertexDefault<float>(
			InputInterface, METASOUND_GET_PARAM_NAME(InputBandwidth), Settings);
		FFloatReadRef Gain = InputCol.GetDataReadReferenceOrConstructWithVertexDefault<float>(
			InputInterface, METASOUND_GET_PARAM_NAME(InputGain), Settings);
	
		switch (*Type)
		{
		default:
		case EAdvancedNoiseType::White:
			return MakeUnique<FAdvancedNoiseOperator_White>(
				InParams.OperatorSettings,
				MoveTemp(Seed),
				MoveTemp(Type),
				MoveTemp(Frequency),
				MoveTemp(Bandwidth),
				MoveTemp(Gain));
		case EAdvancedNoiseType::Pink:
			return MakeUnique<FAdvancedNoiseOperator_Pink>(
				InParams.OperatorSettings,
				MoveTemp(Seed),
				MoveTemp(Type),
				MoveTemp(Frequency),
				MoveTemp(Bandwidth),
				MoveTemp(Gain));
		case EAdvancedNoiseType::Brown:
			return MakeUnique<FAdvancedNoiseOperator_Brown>(
				InParams.OperatorSettings,
				MoveTemp(Seed),
				MoveTemp(Type),
				MoveTemp(Frequency),
				MoveTemp(Bandwidth),
				MoveTemp(Gain));
		case EAdvancedNoiseType::Green:
			return MakeUnique<FAdvancedNoiseOperator_Green>(
				InParams.OperatorSettings,
				MoveTemp(Seed),
				MoveTemp(Type),
				MoveTemp(Frequency),
				MoveTemp(Bandwidth),
				MoveTemp(Gain));
		}
		checkNoEntry();
		return nullptr;
	}
	METASOUND_REGISTER_NODE(FAdvancedNoiseNode)
}


#undef LOCTEXT_NAMESPACE