# Strive SAMMI integration

This is a fork of Sevoii's Framebar viewer mod that will also send game state information to SAMMI similarly to super-continent's excellent [GGXRD-mod](https://github.com/super-continent/ggxrd-mod). This is very much a work in progress. The overall goal is to be as compatible as possible with bot Sevoii's framedata viewer and SAMMI implementations that worked with Xrd. To that end, this mod **fully replaces** Sevoii's and should **not** be installed alongside it.

## Installation
Download the `Standalone.zip` file from releases, and extract the contents into the win64 directory of GGST.

e.g. ```C:\Program Files (x86)\Steam\steamapps\common\GUILTY GEAR STRIVE\RED\Binaries\Win64```

If you have Sevoii's framedata viewer installed **remove it**, as this mod does the same thing but is incompatible for various reasons.
If you already have some ue4ss mods, you'll probably still want to update the other dlls that I provide, as I'm building against the latest version and not a specific release. Additionally, make sure to add "SAMMI-Integration : 1" to you Mods.txt in the Mods directory.

## TODO:
- Aquire the correct data from each frame update and parse it into good format.
- Figure out how to send SAMMI data (packet? web request??).
- Figure out how to detect hits, object creations and round ends.
- Optimize.
- Add configuration entries for enable/disable and poll rate.
- Steam.

## Disabling
The simplest way to disable this and any other ue4ss mods is to delete or remove the ```dwmapi.dll``` file from the game files. If this file is not present, the rest of the mod will not be loaded when the game is launched.

## Disclaimer
This is not a standard mod that extends or patches Unreal pak data, but instead relies on code injection. While it is designed to only provide functionality in training mode, it may violate TOS with Arc Systems. Using this may result in actions against your account on their part.

I make no guarantees on account standing, game stability, or the mental stability of the user after practicing perfect frame traps that may come as a result of this mod.

I advise disabling this mod (as detailed above) and restarting the game before playing online.

## Compiling from source
TBD
