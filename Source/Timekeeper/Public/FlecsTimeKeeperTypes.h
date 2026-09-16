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
	
	NO_DISCARD FDateTime ToDateTime() const;
	
}; // struct FFlecsTKTickCountComponent

FLECS_COMPONENT_TRAITS(FFlecsTKTickCountComponent)
{
	
}; // struct FLECS_COMPONENT_TRAITS(FFlecsTKTickCountComponent)

USTRUCT()
struct FFlecsTKTickCountEndComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int64 EndTickCount;
}; // struct FFlecsTKTickCountEndComponent 

FLECS_COMPONENT_TRAITS(FFlecsTKTickCountEndComponent)
{
	using WithTypes = TTuple<FFlecsTKTickCountComponent>;
}; // struct FLECS_COMPONENT_TRAITS(FFlecsTKTickCountEndComponent)

// is the component necessary for automatic tick
USTRUCT()
struct FFlecsTKAccumulator
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	float AccumulatedTime;
}; // struct FFlecsTKAccumulator 

FLECS_COMPONENT_TRAITS(FFlecsTKAccumulator)
{
	
}; // struct FLECS_COMPONENT_TRAITS(FFlecsTKAccumulator)
