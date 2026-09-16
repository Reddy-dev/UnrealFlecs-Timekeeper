// Elie Wiese-Namir © 2026. All Rights Reserved.

#include "Misc/AutomationTest.h"
#include "UnrealFlecsTests/Fixtures/FlecsWorldFixture.h"

#include "UnrealFlecsConfigMacros.h"

#if WITH_AUTOMATION_TESTS && ENABLE_UNREAL_FLECS_TESTS

#include "FlecsEndTickEvent.h"
#include "FlecsTimeKeeperSystems.h"
#include "FlecsTimeKeeperTypes.h"
#include "Worlds/FlecsWorld.h"

FLECS_TEST_CLASS_WITH_FLAGS_AND_TAGS(FlecsTimekeeperTests,
	"Timekeeper",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter
	| EAutomationTestFlags::CriticalPriority,
	"[Flecs][Timekeeper]")
{
protected:
	virtual EWorldType::Type WorldType() const override
	{
		return EWorldType::Game;
	}

public:
	TEST_METHOD(ComponentsAreRegisteredWithDependencies)
	{
		const FFlecsComponentHandle TickCount = World()->RegisterComponentType<FFlecsTKTickCountComponent>();
		const FFlecsComponentHandle EndTickCount = World()->RegisterComponentType<FFlecsTKEndTickCountComponent>();
		const FFlecsComponentHandle RateAccumulator = World()->RegisterComponentType<FFlecsTKRateAccumulator>();
		const FFlecsComponentHandle EndTickEvent = World()->RegisterComponentType<FFlecsEndTickEvent>();

		ASSERT_THAT(IsTrue(TickCount.IsValid()));
		ASSERT_THAT(IsTrue(EndTickCount.IsValid()));
		ASSERT_THAT(IsTrue(RateAccumulator.IsValid()));
		ASSERT_THAT(IsTrue(EndTickEvent.IsValid()));
		ASSERT_THAT(IsTrue(EndTickCount.HasPair(flecs::With, TickCount.GetFlecsId())));
		ASSERT_THAT(IsTrue(RateAccumulator.HasPair(flecs::With, TickCount.GetFlecsId())));
	}

	TEST_METHOD(TickCountConvertsToDateTime)
	{
		const FDateTime Expected(2026, 9, 15, 13, 45);
		const FFlecsTKTickCountComponent TickCount{Expected.GetTicks(), 0};

		ASSERT_THAT(AreEqual(Expected, TickCount.ToDateTime()));
	}

	TEST_METHOD(AccumulatorAdvancesMultipleTicksAndPreservesRemainder)
	{
		UFlecsTKAccumulatorSystem* System = World()->RegisterFlecsObject<UFlecsTKAccumulatorSystem>();
		const FFlecsEntityHandle Entity = World()->CreateEntity()
			.Set(FFlecsTKTickCountComponent{10, 10})
			.Set(FFlecsTKRateAccumulator{0.25, 1.0, 3});

		System->RunSystem(2.5);

		const FFlecsTKTickCountComponent& TickCount = Entity.Get<FFlecsTKTickCountComponent>();
		const FFlecsTKRateAccumulator& Accumulator = Entity.Get<FFlecsTKRateAccumulator>();
		ASSERT_THAT(AreEqual(int64{16}, TickCount.TickCount));
		ASSERT_THAT(IsTrue(FMath::IsNearlyEqual(Accumulator.AccumulatedTime, 0.75)));
	}

	TEST_METHOD(AccumulatorWaitsUntilTickRateIsReached)
	{
		UFlecsTKAccumulatorSystem* System = World()->RegisterFlecsObject<UFlecsTKAccumulatorSystem>();
		const FFlecsEntityHandle Entity = World()->CreateEntity()
			.Set(FFlecsTKTickCountComponent{42, 10})
			.Set(FFlecsTKRateAccumulator{0.1, 1.0, 5});

		System->RunSystem(0.5);

		const FFlecsTKTickCountComponent& TickCount = Entity.Get<FFlecsTKTickCountComponent>();
		const FFlecsTKRateAccumulator& Accumulator = Entity.Get<FFlecsTKRateAccumulator>();
		ASSERT_THAT(AreEqual(int64{42}, TickCount.TickCount));
		ASSERT_THAT(IsTrue(FMath::IsNearlyEqual(Accumulator.AccumulatedTime, 0.6)));
	}

	TEST_METHOD(EndTickSystemEmitsOnlyForReachedEndTicks)
	{
		UFlecsTKEndTickCountSystem* System = World()->RegisterFlecsObject<UFlecsTKEndTickCountSystem>();
		const FFlecsEntityHandle PendingEntity = World()->CreateEntity()
			.Set(FFlecsTKTickCountComponent{9, 0})
			.Set(FFlecsTKEndTickCountComponent{10});
		const FFlecsEntityHandle ReachedEntity = World()->CreateEntity()
			.Set(FFlecsTKTickCountComponent{10, 0})
			.Set(FFlecsTKEndTickCountComponent{10});

		int32 PendingEventCount = 0;
		int32 ReachedEventCount = 0;
		PendingEntity.GetEntity().observe<FFlecsEndTickEvent>([&PendingEventCount]()
		{
			++PendingEventCount;
		});
		ReachedEntity.GetEntity().observe<FFlecsEndTickEvent>([&ReachedEventCount]()
		{
			++ReachedEventCount;
		});

		System->RunSystem();

		ASSERT_THAT(AreEqual(0, PendingEventCount));
		ASSERT_THAT(AreEqual(1, ReachedEventCount));
	}
}; // FlecsTimekeeperTests

#endif // WITH_AUTOMATION_TESTS && ENABLE_UNREAL_FLECS_TESTS
