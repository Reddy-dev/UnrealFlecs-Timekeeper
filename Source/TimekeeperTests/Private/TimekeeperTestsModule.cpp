#include "Modules/ModuleManager.h"
#include "General/FlecsModuleRegistry.h"

class FTimekeeperTestsModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE::Flecs::FFlecsModuleRegistry::Get().RegisterUnrealFlecsModule("TimekeeperTests");
	}
};

IMPLEMENT_MODULE(FTimekeeperTestsModule, TimekeeperTests)
