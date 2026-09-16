// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ObjectTypes/FFlecsSceneComponentTag.h"

#include "FlecsTimeKeeperTypes.generated.h"

USTRUCT()
struct FFlecsTKTickCountComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int64 TickCount;
	
	UPROPERTY()
	int64 StartTickCount;
	
	NO_DISCARD FDateTime ToDateTime() const;
	
}; // struct FFlecsTKTickCountComponent

FLECS_COMPONENT_TRAITS(FFlecsTKTickCountComponent)
{
	
}; // struct FLECS_COMPONENT_TRAITS(FFlecsTKTickCountComponent)

USTRUCT()
struct FFlecsTKEndTickCountComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int64 EndTickCount;
}; // struct FFlecsTKEndTickCountComponent

FLECS_COMPONENT_TRAITS(FFlecsTKEndTickCountComponent)
{
	using WithTypes = TTuple<FFlecsTKTickCountComponent>;
}; // struct FLECS_COMPONENT_TRAITS(FFlecsTKEndTickCountComponent)

// is the component necessary for automatic tick
USTRUCT()
struct FFlecsTKRateAccumulator
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY()
	double AccumulatedTime;
	
	UPROPERTY()
	double TickRate;
	
	UPROPERTY()
	int64 TickCountPerRate = 1;
	
}; // struct FFlecsTKRateAccumulator 

FLECS_COMPONENT_TRAITS(FFlecsTKRateAccumulator)
{
	using WithTypes = TTuple<FFlecsTKTickCountComponent>;
}; // struct FLECS_COMPONENT_TRAITS(FFlecsTKRateAccumulator)
