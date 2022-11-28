// Copyright ubyte digital 2022. All Right Reserved. https://ubyte.dev

#pragma once

#include "Modules/ModuleManager.h"
#include "CommonActivityStrategyTags.h"
#include "ProjectDescriptor.h"
#include "Interfaces/IProjectManager.h"

// Must *never* be later then ELoadingPhase::PostDefault
class FCommonActivityStrategyModule : public IModuleInterface
{
public:
	//~ Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ End IModuleInterface

	/** Get the native tag registration this module holds onto */
	TSharedPtr<FCommonActivityStrategyTagRegistration> GetTagRegistration() const
	{
		return TagRegistration;
	}

private:
	// Tag registration for the tags introduced by this module
	TSharedPtr<FCommonActivityStrategyTagRegistration> TagRegistration;
};

void FCommonActivityStrategyModule::StartupModule()
{
	TagRegistration = MakeShared<FCommonActivityStrategyTagRegistration>();

	// Lambda for a deferred check whether this tag registration would've been successful or not.
	// (It would be better to have UHT-style compile-time validation instead of this, but keep this for now.)
	auto CheckTagRegistrationLambda = []()
	{
		const FModuleDescriptor* ThisModule = IProjectManager::Get().GetCurrentProject()->Modules.FindByPredicate(
			[](const FModuleDescriptor& ModuleDescriptor)
			{
				return ModuleDescriptor.Name == UE_MODULE_NAME;
			});
		
		if (ThisModule)
		{
			if (!(ThisModule->Type == EHostType::Runtime || ThisModule->Type == EHostType::RuntimeAndProgram))
			{
				checkf(false, TEXT("Make sure module '%s' is a Runtime or RuntimeAndProgram for this tag registration to work correctly"), UE_MODULE_NAME);
			}
			if (ThisModule->LoadingPhase > ELoadingPhase::PostDefault)
			{
				checkf(false, TEXT("Tag registration would fail. Module '%s' should never have a loading phase later than ELoadingPhase::PostDefault, such as PostEngineInit"));
			}
		}
	};
	
	// Deferred check whether this tag registration would've been successful or not.
	FCoreDelegates::OnAllModuleLoadingPhasesComplete.AddLambda(MoveTemp(CheckTagRegistrationLambda));
}

void FCommonActivityStrategyModule::ShutdownModule()
{
	TagRegistration.Reset();
}

IMPLEMENT_MODULE(FCommonActivityStrategyModule, CommonActivityStrategy);

