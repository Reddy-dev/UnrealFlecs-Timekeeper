// Elie Wiese-Namir © 2025. All Rights Reserved.

#pragma once

#include "Systems/FlecsSystemObject.h"

#include "FlecsTimeKeeperSystems.generated.h"

UCLASS()
class UFlecsTKAccumulatorSystem : public UFlecsSystemObject
{
	GENERATED_BODY()

public:
	UFlecsTKAccumulatorSystem(const FObjectInitializer& ObjectInitializer);
	
	virtual void BuildSystem(const TSolidNotNull<const UFlecsWorldInterfaceObject*> InWorld, TFlecsSystemBuilder<>& InBuilder) const override;
	virtual void RunEachIterator(const TSolidNotNull<UFlecsWorldInterfaceObject*> InWorld, flecs::iter& InIterator) override;
	
}; // class UFlecsTKAccumulatorSystem
