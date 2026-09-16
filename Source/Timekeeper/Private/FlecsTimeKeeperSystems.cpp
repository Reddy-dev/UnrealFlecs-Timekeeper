// Elie Wiese-Namir © 2025. All Rights Reserved.

#include "FlecsTimeKeeperSystems.h"

#include "FlecsEndTickEvent.h"
#include "FlecsTimeKeeperTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlecsTimeKeeperSystems)

UFlecsTKAccumulatorSystem::UFlecsTKAccumulatorSystem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UFlecsTKAccumulatorSystem::BuildSystem(const TSolidNotNull<const UFlecsWorldInterfaceObject*> InWorld,
                                            TFlecsSystemBuilder<>& InBuilder) const
{
	InBuilder
		.Phase(EFlecsPhaseType::OnStore)
		.With<FFlecsTKRateAccumulator&>() // 0
		.With<FFlecsTKTickCountComponent&>(); // 1
}

void UFlecsTKAccumulatorSystem::RunEachIterator(const TSolidNotNull<UFlecsWorldInterfaceObject*> InWorld,
	flecs::iter& InIterator)
{
	const double DeltaTime = InIterator.delta_time();
	
	const auto AccumulatorField = InIterator.field<FFlecsTKRateAccumulator>(0);
	const auto TickCountField = InIterator.field<FFlecsTKTickCountComponent>(1);
	
	for (const FFlecsId EntityIndex : InIterator)
	{
		auto& [AccumulatedTime, TickRate, TickCountPerRate] = AccumulatorField[EntityIndex];
		FFlecsTKTickCountComponent& TickCount = TickCountField[EntityIndex];

		AccumulatedTime += DeltaTime;
		
		while (AccumulatedTime >= TickRate)
		{
			AccumulatedTime -= TickRate;
			TickCount.TickCount += TickCountPerRate;
		}
	}
}

UFlecsTKEndTickCountSystem::UFlecsTKEndTickCountSystem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UFlecsTKEndTickCountSystem::BuildSystem(const TSolidNotNull<const UFlecsWorldInterfaceObject*> InWorld,
	TFlecsSystemBuilder<>& InBuilder) const
{
	InBuilder
		.Phase(EFlecsPhaseType::PostFrame)
		.With<const FFlecsTKTickCountComponent>() // 0
		.With<const FFlecsTKEndTickCountComponent>() // 1
		.Write(flecs::Wildcard)
		.DetectChanges();
}

void UFlecsTKEndTickCountSystem::OnBuildSystem(const FFlecsSystemHandle& InSystemHandle)
{
	Super::OnBuildSystem(InSystemHandle);
	
	//InSystemHandle.AddPair(flecs::DependsOn, 
}

void UFlecsTKEndTickCountSystem::RunEachIterator(const TSolidNotNull<UFlecsWorldInterfaceObject*> InWorld,
                                                 flecs::iter& InIterator)
{
	if (!InIterator.changed())
	{
		InIterator.next();
		return;
	}
	
	const auto TickCountComponent
		= InIterator.field<const FFlecsTKTickCountComponent>(0);
	const auto EndTickCountComponent 
		= InIterator.field<const FFlecsTKEndTickCountComponent>(1);
	
	for (const FFlecsId EntityIndex : InIterator)
	{
		const auto& [TickCount, StartTickCount] = TickCountComponent[EntityIndex];
		const auto& [EndTickCount] = EndTickCountComponent[EntityIndex];
		
		const FFlecsEntityHandle EntityHandle = InIterator.entity(EntityIndex);
		
		if (TickCount >= EndTickCount)
		{
			EntityHandle.Emit<FFlecsEndTickEvent>();
		}
	}
}
