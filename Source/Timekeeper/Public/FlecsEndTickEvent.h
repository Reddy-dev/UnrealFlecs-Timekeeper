// Elie Wiese-Namir © 2025. All Rights Reserved.

#pragma once

#include "Properties/FlecsComponentProperties.h"

#include "FlecsEndTickEvent.generated.h"

USTRUCT(BlueprintType)
struct TIMEKEEPER_API FFlecsEndTickEvent
{
	GENERATED_BODY()
	
}; // FFlecsEndTickEvent 

FLECS_COMPONENT_TRAITS(FFlecsEndTickEvent)
{
	static constexpr bool UseLowId = false;
}; // FLECS_COMPONENT_TRAITS(FFlecsEndTickEvent)

