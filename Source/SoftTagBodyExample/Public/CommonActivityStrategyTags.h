// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

#pragma once

#include "CoreMinimal.h"
#include "SoftTagBodyStatics.h"
#include "WorkerActivityStrategy.h"
#include "CommonActivityStrategyTags.generated.h"

// This example builds on WorkerActivityStrategy, which is a gameplay concept extending GenericActivityFramework

USTRUCT()
struct FCommonActivityStrategyAgentTagSet /*final*/ : public FAgentActivityStrategyFieldSetBase
{
	GENERATED_BODY()

	// This constructor attempts to fill all soft tag body properties with its corresponding tag value.
	FCommonActivityStrategyAgentTagSet() { TSoftTagBodyStatics<TRemovePointer<decltype(this)>::Type>::InitFields<FAgentActivityStrategyTag>(this); }
	
	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FAgentActivityStrategyTag Nav;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FAgentActivityStrategyTag Nav_Near;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FAgentActivityStrategyTag Nav_Avoid;
};

USTRUCT()
struct FCommonActivityStrategyCrowdTagSet /*final*/ : public FCrowdActivityStrategyFieldSetBase
{
	GENERATED_BODY()
	
	// This constructor attempts to fill all soft tag body properties with its corresponding tag value.
	FCommonActivityStrategyCrowdTagSet() { TSoftTagBodyStatics<TRemovePointer<decltype(this)>::Type>::InitFields<FCrowdActivityStrategyTag>(this); }
	
	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true, TagDevComment = "Tag dev comment that's used when this property gets registered as native gameplay tag. "))
	FCrowdActivityStrategyTag Combat;
	
	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Combat_Endurance;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Combat_Endurance_Hardened;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Combat_Endurance_Squishy;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection_Stance;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection_Stance_Proactive;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection_Stance_Reactive;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection_Attitude;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection_Attitude_Aggressive;

	UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
	FCrowdActivityStrategyTag Detection_Attitude_Frightened;
};

// As long as one instance remains, the tags remain registered with the gameplay tags module.
struct FCommonActivityStrategyTagRegistration : TSharedFromThis<FCommonActivityStrategyTagRegistration>
{
	const TSoftTagBodyFieldRegistration<FCommonActivityStrategyCrowdTagSet, FCrowdActivityStrategyTag> CrowdRegistration;
	const TSoftTagBodyFieldRegistration<FCommonActivityStrategyAgentTagSet, FAgentActivityStrategyTag> AgentRegistration;
};
