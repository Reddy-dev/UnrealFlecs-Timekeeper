// Fill out your copyright notice in the Description page of Project Settings.

#include "FlecsTimeKeeperTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlecsTimeKeeperTypes)

REGISTER_FLECS_COMPONENT(FFlecsTKTickCountComponent);
REGISTER_FLECS_COMPONENT(FFlecsTKAccumulator);

FDateTime FFlecsTKTickCountComponent::ToDateTime() const
{
	return FDateTime(TickCount);
}
