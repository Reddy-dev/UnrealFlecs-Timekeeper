// Elie Wiese-Namir © 2025. All Rights Reserved.

#include "FlecsTimeKeeperSystems.h"

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
		.With<FFlecsTKAccumulator&>() // 0
		.With<FFlecsTKTickCountComponent&>(); // 1
}

void UFlecsTKAccumulatorSystem::RunEachIterator(const TSolidNotNull<UFlecsWorldInterfaceObject*> InWorld,
	flecs::iter& InIterator)
{
	const auto AccumulatorField = InIterator.field<FFlecsTKAccumulator>(0);
	const auto TickCountField = InIterator.field<FFlecsTKTickCountComponent>(1);
}
