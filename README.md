# Strive SAMMI integration

This is a fork of Procdox's Framebar viewer mod that should send game state information to SAMMI similarly to super-continent's excellent GGXRD-mod. This is very much a work in progress.

## Manual Installation
Download the `Standalone.zip` file from releases, and extract the contents into the win64 directory of GGST. If you are upgrading, delete the existing "cache" folder as it can cause issues if it is out of date.

e.g. ```C:\Program Files (x86)\Steam\steamapps\common\GUILTY GEAR STRIVE\RED\Binaries\Win64```

This does not require any pak mods installed via unverum.

## TODO:
- Get it to compile
- Everything else

## Disabling
The simplest way to disable this and any other ue4ss mods is to delete or remove the ```dwmapi.dll``` file from the game files. If this file is not present, the rest of the mod will not be loaded when the game is launched.

## Disclaimer
This is not a standard mod that extends or patches Unreal pak data, but instead relies on code injection. While it is designed to only provide functionality in training mode, it may violate TOS with Arc Systems. Using this may result in actions against your account on their part.

I make no guarantees on account standing, game stability, or the mental stability of the user after practicing perfect frame traps that may come as a result of this mod.

I advise disabling this mod (as detailed above) and restarting the game before playing online.

## Compiling from source
Start by downloading the project, you will need a github account with permissions to download the Unreal repository to do so (see the dependent UE4SS repository for instructions on this)
With either method, you may need to first manually run ```git submodule update --init --recursive``` on the RE-U4SS submodule.
### Auto Build
Requires powershell 7.4.1 or newer and MSVC build tools
The project can be built automatically using ```Scripts/build_project.ps1```.
Then you can run any of the package_*.ps1 or deploy_*.ps1 scripts in the same folder.
- The package_*.ps1 scripts will only create the unverum or standalone file structure in the Packages folder. Afterwords they can be manually installed.
- The deploy_*.ps1 scripts can be modified to point at your game/unverum install. They will automatically clean the target, build the package, and install the mod.

### Manual Build
1. Navigate to ```RE-UE4SS/VS_Solution``` and run ```generate_vs_solution.bat```
2. Open the solution ```Output/UE4SSMods.sln``` in MSVC (I use 2022)
3. Build all
4. There will be several files you need to copy to the game files
    1. ```Output/Output/<build>/UE4SS/bin/UE4SS.dll``` to ```Win64/```
    2. ```Output/Output/<build>/bin/proxy/bin/dwmapi.dll``` to ```Win64/```
    3. ```Output/StriveFrameData/<build>/StriveFrameData.dll``` to ```Win64/Mods/StriveFrameData/dlls/```
