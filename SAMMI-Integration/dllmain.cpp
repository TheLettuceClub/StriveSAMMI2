#include <stdio.h>
#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObject.hpp>

using namespace RC;
using namespace RC::Unreal;

class SAMMInteg : public RC::CppUserModBase
{
public:
    SAMMInteg() : CppUserModBase()
    {
        ModName = STR("SAMMI-Integration");
        ModVersion = STR("1.0");
        ModDescription = STR("This is my awesome mod");
        ModAuthors = STR("TheLettuceClub");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        // ModIntendedSDKVersion = STR("2.6");

        Output::send<LogLevel::Verbose>(STR("SAMMI integration says hi\n"));
    }

    auto on_unreal_init() -> void override
    {
        // You are allowed to use the 'Unreal' namespace in this function and anywhere else after this function has fired.
        auto Object = UObjectGlobals::StaticFindObject<UObject *>(nullptr, nullptr, STR("/Script/CoreUObject.Object"));
        Output::send<LogLevel::Verbose>(STR("Object Name: {}\n"), Object->GetFullName());
    }

    ~SAMMInteg() override
    {
    }

    auto on_update() -> void override
    {
    }
};

#define SAMMI_INTEGRATION_API __declspec(dllexport)
extern "C"
{
    SAMMI_INTEGRATION_API RC::CppUserModBase *start_mod()
    {
        return new SAMMInteg();
    }

    SAMMI_INTEGRATION_API void uninstall_mod(RC::CppUserModBase *mod)
    {
        delete mod;
    }
}
