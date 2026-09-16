// Copyright Epic Games, Inc. All Rights Reserved.

#include "Timekeeper.h"

#include "General/FlecsModuleRegistry.h"

#define LOCTEXT_NAMESPACE "FTimekeeperModule"

void FTimekeeperModule::StartupModule()
{
	using namespace UE::Flecs;
	
	FFlecsModuleRegistry& ModuleRegistry = FFlecsModuleRegistry::Get();
	
	ModuleRegistry.RegisterUnrealFlecsPlugin("Timekeeper", EUnrealFlecsRegistrationScopeType::Plugin);
	ModuleRegistry.RegisterUnrealFlecsModule("Timekeeper", EUnrealFlecsRegistrationScopeType::Plugin);
}

void FTimekeeperModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTimekeeperModule, Timekeeper)