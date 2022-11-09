# SoftTagBody-Example
Example of a module using the <code>SoftTagBody</code> metadata specifier on GameplayTag-derived fields.

## Explanation 
This plugin contains one module called <code>CommonActivityStrategy</code>.

<code>CommonActivityStrategy</code> is a collection of CDO-based tag sets that declare GameplayTags from the typed tags introduced by [WorkerActivityStrategyRuntime](https://github.com/ubytedev/GenericActivityFramework/tree/main/Source/WorkerActivityStrategyRuntime).

## When enabling this plugin
By enabling this plugin, the following tags will be registered with your Gameplay Tags Manager:

`FAgentActivityStrategyTag` ([from WorkerActivityStrategy.h](https://github.com/ubytedev/GenericActivityFramework/blob/main/Source/WorkerActivityStrategyRuntime/Public/WorkerActivityStrategy.h)) has a root tag of `"Agent.ActivityStrategy"` during the time of writing. 

```
"Agent.ActivityStrategy.Nav.Near"
"Agent.ActivityStrategy.Nav.Avoid"
```

`FCrowdActivityStrategyTag` [(from WorkerActivityStrategy.h](https://github.com/ubytedev/GenericActivityFramework/blob/main/Source/WorkerActivityStrategyRuntime/Public/WorkerActivityStrategy.h)) has a root tag of `"Crowd.ActivityStrategy"` during the time of writing.

```
"Crowd.ActivityStrategy.Combat.Endurance.Hardened"
"Crowd.ActivityStrategy.Combat.Endurance.Squishy"

"Crowd.ActivityStrategy.Combat.Detection.Stance.Proactive"
"Crowd.ActivityStrategy.Combat.Detection.Stance.Reactive"

"Crowd.ActivityStrategy.Combat.Attitude.Aggressive"
"Crowd.ActivityStrategy.Combat.Attitude.Frightened"
```

## Game-specific extension

The goal is to allow you to create game-specific augmentations to existing 'base' tag sets (such as `CommonActivityStrategy`, which now represents some form of boilerplate dependency for other projects to use).

Here's an example of what your project can add

```cpp
// [Your Alias] sub-implementation of CommonActivityStrategy tags for Agents
USTRUCT()
struct FYourAlias_CommonActivityStrategy_AgentImpl /*final*/ : public FAgentActivityStrategyFieldSetBase
{
    GENERATED_BODY()

    FYourAlias_CommonActivityStrategy_AgentImpl() {
        TSoftTagBodyStatics<TRemovePointer<decltype(this)>::Type>::InitFields<FAgentActivityStrategyTag>(this); 
    }

    static_assert(sizeof(FCommonActivityStrategyAgentTagSet::Nav_Near));
    static_assert(sizeof(FCommonActivityStrategyAgentTagSet::Nav_Avoid));
	
    UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
    FAgentActivityStrategyTag Nav_Near_GameplayLocation;

    UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
    FAgentActivityStrategyTag Nav_Avoid_GameplayLocation;

    UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
    FAgentActivityStrategyTag Nav_Near_Agent;

    UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
    FAgentActivityStrategyTag Nav_Avoid_Agent;
};
```

Which registers the following tags when paired with `TSoftTagBodyFieldRegistration`

```
"Agent.ActivityStrategy.Nav.Near.GameplayLocation"
"Agent.ActivityStrategy.Nav.Near.Agent"
"Agent.ActivityStrategy.Nav.Avoid.GameplayLocation"
"Agent.ActivityStrategy.Nav.Avoid.Agent"
```

### Optional

Where 'Agent' and 'GameplayLocation' remain entirely generic in this context.

- From GameplayLocation, it's evident that we're simply avoiding navigation near a `FVector` that might dynamically adjust itself over time)
- From Entity, it's evident that we're simply avoiding navigation near an agent.

What this means gameplay-implementation-wise is up to your project or module following its own realm of constrains.

Furthermore, this allows you to write large parts of gameplay-code without introducing any additional type dependency.

This allows you to write parts of gameplay-code that just 'generically' need to know about 'an agent'.

## Long-term vision

- Cross-project interoperability by generically writing large sums of code, without actually specifying what it means implementation-wise for the most part.

- Dynamically streaming gameplay logistics in-and-out on-demand (using Game Features)

Basically, being able to write the logistics responsible for capture-the-flag, without actually implementing what capture-the-flag means in the world.
