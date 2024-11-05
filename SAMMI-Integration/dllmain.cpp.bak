#include <stdio.h>
#include <Mod/CppUserModBase.hpp>

class MyAwesomeMod : public RC::CppUserModBase
{
public:
    MyAwesomeMod() : CppUserModBase()
    {
        ModName = STR("SAMMI-Integration");
        ModVersion = STR("1.0");
        ModDescription = STR("This is my awesome mod");
        ModAuthors = STR("TheLettuceClub");
        // Do not change this unless you want to target a UE4SS version
        // other than the one you're currently building with somehow.
        //ModIntendedSDKVersion = STR("2.6");
        
        printf("Sammi says hello\n");
    }

    ~MyAwesomeMod() override
    {
    }

    auto on_update() -> void override
    {
    }
};

#define MY_AWESOME_MOD_API __declspec(dllexport)
extern "C"
{
    MY_AWESOME_MOD_API RC::CppUserModBase* start_mod()
    {
        return new MyAwesomeMod();
    }

    MY_AWESOME_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}
