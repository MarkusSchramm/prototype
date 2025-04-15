/** 
 * @file BachelorMetasoundModule.h
 * @author Markus Schramm
 */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBachelorMetasound, Log, All);

namespace BachelorAudio {
    /**
     * @interface IBachelorMetasoundModule
     * @brief Abstract module interface, derived from [IModuleInterface](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Modules)
     */
    class BACHELORMETASOUND_API IBachelorMetasoundModule : public IModuleInterface {};
}