#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"
#include "FeQuickRaceOptionsHook.h"

void Init();

DWORD WINAPI Thing(LPVOID);

unsigned char minLaps, maxLaps, minTime, maxTime, minOpponents, maxOpponents, csBlacklist, headlightsMode, MaximumMultiplierTrack, MaximumMultiplierCanyon, TrafficLow, TrafficMed, TrafficHigh, CameraDriftMoveMode, ShowSpecialVinyls, ShowMoreRaceOptions, MaxUniqueOpponentCars, QRBackCamo, WindowedMode;
int hotkeyToggleForceHeat, hotkeyForceHeatLevel, hotkeyToggleCops, hotkeyToggleCopLights, hotkeyToggleHeadlights, hotkeyUnlockAllThings, hotkeyAutoDrive, StartingCash, hotkeyDriftMode, ThreadDelay, GameState, SelectableMarkerCount, hotkeyFreezeCamera;
bool ShowSubs, EnableMoreCarCategories, ShowLanguageSelectScreen, EnableDebugWorldCamera, ExOptsTeamTakeOver, EnableCameras, copLightsEnabled, RemoveNeonBarriers, UnlockStrangeRace, UnlockSeriesCarsAndUpgrades, EnableHeatLevelOverride, AlwaysRain, SkipMovies, EnableSound, EnableMusic, EnableVoice, GarageZoom, GarageRotate, GarageShowcase, ShowDebugCarCustomize, Win10Fix, AugmentedDriftWithEBrake, AutoDrive, UnlockAllThings, EnableSaveLoadHotPos, ShowHiddenTracks, ShowLightStreaks, PauseScreenBlur, HUDShakeEffect, ForceCollectorsEdition, WheelFix, X10Fix, EnableFog, SkipFirstTimeTutorials, ShowMessage, PursuitActionMode, DriftMode, SkipNISs, DebugWatchCarCamera, IsOnFocus, ShowPursuitCops, ShowNonPursuitCops, ShowAllCarsInFE, SkipCareerIntro, AllowMultipleInstances, UncensoredBustedScreen, TimeBugFix, ImmobileColFix, NFSU2StyleLookBackCamera, MoreCarsForOpponents, ShowDebugEventID, NoRevLimiter, NoCatchUp;
bool forceHeatLevel = 0, once1 = 0, once2 = 0, DebugCamStatus, ToggleCops = 1;
float SplashScreenTimeLimit, copLightsAmount, LowBeamAmount, HighBeamAmount, MinHeatLevel, MaxHeatLevel, heatLevel, RainAmount, RoadReflection, FallingRainSize, RainIntensity, RainXing, RainFallSpeed, RainGravity, WorldAnimationSpeed, GameSpeed, CarScale, SBRechargeTime, SBRechargeSpeedLimit, SBMassMultiplier, HUDUpdateRate, RadarRange, SpeedingLimit, ExcessiveSpeedingLimit, RecklessDrivingLimit, DriftRaceCollisionThreshold, DebugCameraTurboSpeed, DebugCameraSuperTurboSpeed, IdleCameraTimeout, RacePositionX, RacePositionY;
float FloatValue1pt00 = 1.0f, FloatValue10pt00 = 10.0f;
HWND windowHandle;

DWORD HeatLevelsCodeCaveExit = 0x449a82;
DWORD StringReplacementCodeCaveExit = 0x57861F;

char* StringBuffer1 = "© 2006 Electronic Arts Inc. All rights reserved.^NFSC Extra Options - © 2018 ExOpts Team. No rights reserved.";
DWORD _A7EBC389_New = (DWORD)StringBuffer1;

DWORD CopsOptionCodeCaveExit = 0x84C1E1;
DWORD CopsOptionCodeCave2Exit = 0x84C20A;
DWORD CopsOptionCodeCave3Exit = 0x84C219;
DWORD LearnRaceModeCodeCaveExit = 0x85E639;
DWORD DebugEventIDCodeCaveExit = 0x5B8AA8;
DWORD RacePositionCodeCaveExit = 0x5C3C41;
DWORD X10FixCodeCaveExit = 0x42A511;
DWORD X10FixCodeCave2Exit = 0x42A5DE;
DWORD VinylMenuCodeCaveExit = 0x85B9D9;

void(*Game_ActivateDriftMode)() = (void(*)())0x65C8B0;
void(*Game_DeactivateDriftMode)() = (void(*)())0x65C910;
void(*CameraAI_SetAction)(int EVIEW_ID, char* Action) = (void(*)(int, char*))0x48D620;
void(*Game_SetWorldHeat)(float DesiredHeatLevel) = (void(*)(float))0x65C550;
void(*Game_ForceAIControl)(int Unk) = (void(*)(int))0x65C2C0;
void(*Game_ClearAIControl)(int Unk) = (void(*)(int))0x65C330;
void(*Game_SetCopsEnabled)(bool AreCopsEnabled) = (void(*)(bool))0x6513E0;
void(*Hud_ShowMessage)(char* MessageToShow) = (void(*)(char*))0x65B1B0;
int(*FE_String_Printf)(char const*, int, char const*, ...) = (int(*)(char const*, int, char const*, ...))0x5A0910;
bool(__thiscall *PVehicle_IsGlareOn)(DWORD* PVehicle, int VehicleFXID) = (bool(__thiscall*)(DWORD*, int))0x6D8080;
void(__thiscall *PVehicle_GlareOn)(DWORD* PVehicle, int VehicleFXID) = (void(__thiscall*)(DWORD*, int))0x6C0BA0;
void(__thiscall *PVehicle_GlareOff)(DWORD* PVehicle, int VehicleFXID) = (void(__thiscall*)(DWORD*, int))0x6C0BC0;
int(__thiscall *VinylSelectablePart_CreateNewLayer)(DWORD* theThis) = (int(__thiscall*)(DWORD*))0x577790;

DWORD RaceOptionToCreate;
DWORD QRRaceMode;

bool QRLaps, QRCrew, QRTraffic, QROpponents, QRCatchUp, QRNitrous, QRShadowOption, QRDifficulty, QRCops;

void __declspec(naked) HeatLevelsCodeCave()
{
	_asm
	{
			cmp EnableHeatLevelOverride, 1
			jne dontforceMinMaxHeat

		forceMinMaxHeat :
			mov ebx, MaxHeatLevel
			mov [esi + 0xF8], ebx
			mov ebx, MinHeatLevel
			mov [esi + 0xF4], ebx

		dontforceMinMaxHeat :
			mov eax, [esi + 0xF8]
			jmp HeatLevelsCodeCaveExit

	}
}

void __declspec(naked) StringReplacementCodeCave()
{
	_asm
	{
			mov ecx, dword ptr ds : [ebx + eax * 0x08]

			cmp ExOptsTeamTakeOver, 0x00
			je continuee
			cmp ecx, 0xA7EBC389
			je ReplaceCopyrightString
			// cmp ecx, AnotherStringHashHere
			// je ReplaceAnotherString
			jmp continuee

		ReplaceCopyrightString :
			cmp once1, 0x01
			je continuee

			mov ecx, _A7EBC389_New
			mov dword ptr[ebx + eax * 0x08 + 0x04], ecx

			mov once1, 0x01
			mov ecx, 0xA7EBC389

		continuee :
			cmp ecx, edx
			jmp StringReplacementCodeCaveExit

	}
}

void __declspec(naked) PauseBlurCodeCave()
{
	_asm
	{
			cmp dword ptr ds : [0xA8AD18], 0x00 //on pause screen
			je originalcode
			cmp dword ptr ds : [0xA590A0], 0x1F41 //not on photo mode
			je originalcode
			fadd dword ptr [FloatValue1pt00]

		originalcode :
			ret
	}
}

void __declspec(naked) PauseBlurCodeCave2()
{
	_asm
	{
			cmp dword ptr ds : [0xA8AD18], 0x00 //on pause screen
			je originalcode
			cmp dword ptr ds : [0xA590A0], 0x1F41 //not on photo mode
			je originalcode
			fadd dword ptr [FloatValue10pt00]

		originalcode :
			ret
	}
}

void __declspec(naked) DebugEventIDCodeCave()
{
	char const *EventID;

	_asm mov EventID, eax;

	FE_String_Printf("WorldMapMain.fng", 0x39F35F28, EventID);

	_asm mov eax, EventID;
	_asm
	{
		push eax
		push 0x9D4C5C // TRACK_MAP_%s
		jmp DebugEventIDCodeCaveExit
	}
}

void __declspec(naked) RacePositionCodeCave()
{
	_asm
	{
		mov edx,0xC380000 // -256.0f
		mov RacePositionX,edx
		lea edx, [esp+0x38]
		push edx
		jmp RacePositionCodeCaveExit
	}
}

void __declspec(naked) RacePositionCodeCave2()
{
	_asm pushad;
		
	RacePositionX += 160.0f;
	RacePositionY = -2980.0f;

	_asm
	{
		popad
		push eax
		mov eax, RacePositionX
		mov [ecx], eax
		mov eax, RacePositionY
		mov [ecx+4], eax
		pop eax
		mov al,01
		add esp,0x0C
		ret 4
	}
}

void __declspec(naked) TrackRegionCodeCave()
{
	_asm
	{
		movzx eax, byte ptr ds:[eax + 0x29]
		cmp al,05
		jg sanjuan
		cmp al,0xFF
		jne caveexit

		sanjuan:
		mov al,00 // add to San Juan

		caveexit:
		pop esi
		ret
	}
}

void __declspec(naked) X10FixCodeCave()
{
	_asm
	{
		mov edi, [esi + 0x00F4]
		cmp edi, 0x0A // If heat level is 10 or more
		jl originalcode // If less, do nothing

		mov edi, 0x09 // Read x9 Bounty Reward

		originalcode:
		jmp X10FixCodeCaveExit // 0042A511
	}
}

void __declspec(naked) X10FixCodeCave2()
{
	_asm
	{
		//Simple Method: Replaces any Combo Timer >=120s to 10s.
		cmp ecx, 0x42F00000 // if 120 seconds or higher
		jl originalcode
		mov ecx, 0x41200000 // 10 seconds

		originalcode:
		mov dword ptr ds : [esi + 0x148], ecx

			jmp X10FixCodeCave2Exit
	}
}

int Return0Hook()
{
	return 0;
}

float Return0fHook()
{
	return 0.0f;
}

void Init()
{
	CIniReader iniReader("NFSCExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyToggleForceHeat = iniReader.ReadInteger("Hotkeys", "HeatLevelHack", 118); // F7
	hotkeyForceHeatLevel = iniReader.ReadInteger("Hotkeys", "ChangeHeatLevel", 33); // PageUp
	hotkeyToggleCops = iniReader.ReadInteger("Hotkeys", "ToggleCops", 145); // Scroll Lock
	hotkeyToggleCopLights = iniReader.ReadInteger("Hotkeys", "CopLights", 79); // O
	hotkeyToggleHeadlights = iniReader.ReadInteger("Hotkeys", "Headlights", 72); // H
	hotkeyFreezeCamera = iniReader.ReadInteger("Hotkeys", "FreezeCamera", 19); // Pause/Break
	hotkeyUnlockAllThings = iniReader.ReadInteger("Hotkeys", "UnlockAllThings", 119); // F8
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); // F6
	hotkeyDriftMode = iniReader.ReadInteger("Hotkeys", "PhysSwitch", 75); // K
	EnableSaveLoadHotPos = iniReader.ReadInteger("Hotkeys", "EnableSaveLoadHotPos", 1) == 1;

	// LapControllers
	minLaps = iniReader.ReadInteger("LapControllers", "Minimum", 0);
	maxLaps = iniReader.ReadInteger("LapControllers", "Maximum", 127);
	minTime = iniReader.ReadInteger("LapControllers", "MinTimePursuitTag", 0);
	maxTime = iniReader.ReadInteger("LapControllers", "MaxTimePursuitTag", 127);
	
	// OpponentControllers
	minOpponents = iniReader.ReadInteger("OpponentControllers", "Minimum", 0);
	maxOpponents = iniReader.ReadInteger("OpponentControllers", "Maximum", 19);
	MaxUniqueOpponentCars = iniReader.ReadInteger("OpponentControllers", "MaxUniqueOpponentCars", 3);
	MoreCarsForOpponents = iniReader.ReadInteger("OpponentControllers", "MoreCarsForOpponents", 0) == 1;
	
	// TrafficControllers
	TrafficLow = iniReader.ReadInteger("TrafficControllers", "Low", 3);
	TrafficMed = iniReader.ReadInteger("TrafficControllers", "Medium", 10);
	TrafficHigh = iniReader.ReadInteger("TrafficControllers", "High", 50);

	// Menu
	ShowMoreRaceOptions = iniReader.ReadInteger("Menu", "ShowMoreRaceOptions", 0);
	ShowSubs = iniReader.ReadInteger("Menu", "ShowSubs", 0) == 1;
	EnableMoreCarCategories = iniReader.ReadInteger("Menu", "ShowMoreCarCategories", 0) == 1;
	ShowLanguageSelectScreen = iniReader.ReadInteger("Menu", "ShowLanguageSelectScreen", 0) == 1;
	ShowSpecialVinyls = iniReader.ReadInteger("Menu", "ShowSpecialVinyls", 0);
	ShowDebugCarCustomize = iniReader.ReadInteger("Menu", "ShowDebugCarCustomize", 0) == 1;
	ShowDebugEventID = iniReader.ReadInteger("Menu", "ShowDebugEventID", 0) == 1;
	ShowHiddenTracks = iniReader.ReadInteger("Menu", "ShowHiddenTracks", 1) == 1;
	QRBackCamo = iniReader.ReadInteger("Menu", "QuickRaceBackgroundCamo", 3);
	csBlacklist = iniReader.ReadInteger("Menu", "ChallengeSeriesBlacklist", 19);
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	ShowLightStreaks = iniReader.ReadInteger("Menu", "ShowLightStreaks", 1) == 1;
	PauseScreenBlur = iniReader.ReadInteger("Menu", "PauseScreenBlur", 1) == 1;
	HUDShakeEffect = iniReader.ReadInteger("Menu", "HUDShakeEffect", 1) == 1;
	GarageZoom = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteZoom", 0) == 1;
	GarageRotate = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteRotation", 0) == 1;
	GarageShowcase = iniReader.ReadInteger("Menu", "ShowcaseCamAlwaysEnable", 0) == 1;
	ExOptsTeamTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 0) == 1;
	EnableDebugWorldCamera = iniReader.ReadInteger("Gameplay", "EnableDebugCamera", 0) == 1;
	NFSU2StyleLookBackCamera = iniReader.ReadInteger("Gameplay", "ShowHUDOnLookBack", 0) == 1;
	CameraDriftMoveMode = iniReader.ReadInteger("Gameplay", "SmartLookaheadCameraMode", 1);
	GameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	WorldAnimationSpeed = iniReader.ReadFloat("Gameplay", "WorldAnimationSpeed", 45.0f);
	HUDUpdateRate = iniReader.ReadFloat("Gameplay", "HUDUpdateRate", 1.0f);
	DebugCameraTurboSpeed = iniReader.ReadFloat("Gameplay", "DebugCamTurboSpeed", 3.06f);
	DebugCameraSuperTurboSpeed = iniReader.ReadFloat("Gameplay", "DebugCamSuperTurboSpeed", 7.16f);
	IdleCameraTimeout = iniReader.ReadFloat("Gameplay", "IdleCameraTimeout", 20.0f);
	CarScale = iniReader.ReadFloat("Gameplay", "CarScale", 1.0f);
	RemoveNeonBarriers = iniReader.ReadInteger("Gameplay", "RemoveNeonBarriers", 0) == 1;
	StartingCash = iniReader.ReadInteger("Gameplay", "StartingCash", 5000);
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 0) == 1;
	ForceCollectorsEdition = iniReader.ReadInteger("Gameplay", "ForceCollectorsEdition", 1) == 1;
	ShowAllCarsInFE = iniReader.ReadInteger("Gameplay", "ShowAllCarsInFE", 0);
	NoCatchUp = iniReader.ReadInteger("Gameplay", "NoCatchUp", 0) == 1;
	NoRevLimiter = iniReader.ReadInteger("Gameplay", "NoRevLimiter", 0) == 1;
	SelectableMarkerCount = iniReader.ReadInteger("Gameplay", "SelectableMarkerCount", 2);
	SBRechargeTime = iniReader.ReadFloat("Gameplay", "SBRechargeTime", 25.0f);
	SBRechargeSpeedLimit = iniReader.ReadFloat("Gameplay", "SBRechargeSpeedLimit", 80.0f);
	SBMassMultiplier = iniReader.ReadFloat("Gameplay", "SBMassMultiplier", 2.0f);
	
	// Drift
	MaximumMultiplierTrack = iniReader.ReadInteger("Drift", "MaximumMultiplierTrack", 10);
	MaximumMultiplierCanyon = iniReader.ReadInteger("Drift", "MaximumMultiplierCanyon", 20);
	AugmentedDriftWithEBrake = iniReader.ReadInteger("Drift", "AugmentedDriftWithEBrake", 0) == 1;
	DriftRaceCollisionThreshold = iniReader.ReadFloat("Drift", "DriftRaceCollisionThreshold", 3.5f);

	// Pursuit
	EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 0) == 1;
	MinHeatLevel = iniReader.ReadFloat("Pursuit", "MinimumHeatLevel", 1.00f);
	MaxHeatLevel = iniReader.ReadFloat("Pursuit", "MaximumHeatLevel", 10.00f);
	PursuitActionMode = iniReader.ReadInteger("Pursuit", "PursuitActionMode", 0) == 1;
	ShowPursuitCops = iniReader.ReadInteger("Pursuit", "ShowPursuitCops", 1) == 1;
	ShowNonPursuitCops = iniReader.ReadInteger("Pursuit", "ShowNonPursuitCops", 1) == 1;
	RadarRange = iniReader.ReadFloat("Pursuit", "RadarRange", 300.0f);
	UncensoredBustedScreen = iniReader.ReadInteger("Pursuit", "UncensoredBustedScreen", 0) == 1;
	SpeedingLimit = iniReader.ReadFloat("Pursuit", "SpeedingLimit", 67.00f);
	ExcessiveSpeedingLimit = iniReader.ReadFloat("Pursuit", "ExcessiveSpeedingLimit", 80.50f);
	RecklessDrivingLimit = iniReader.ReadFloat("Pursuit", "RecklessDrivingLimit", 89.40f);

	// Weather
	AlwaysRain = iniReader.ReadInteger("Weather", "AlwaysRain", 0) == 1;
	EnableFog = iniReader.ReadInteger("Weather", "EnableFog", 0) == 1;
	RainAmount = iniReader.ReadFloat("Weather", "GeneralRainAmount", 1.0f);
	RoadReflection = iniReader.ReadFloat("Weather", "RoadReflectionAmount", 1.0f);
	FallingRainSize = iniReader.ReadFloat("Weather", "RainSize", 0.01f);
	RainIntensity = iniReader.ReadFloat("Weather", "RainIntensity", 0.45f);
	RainXing = iniReader.ReadFloat("Weather", "RainCrossing", 0.02f);
	RainFallSpeed = iniReader.ReadFloat("Weather", "RainSpeed", 0.03f);
	RainGravity = iniReader.ReadFloat("Weather", "RainGravity", 0.35f);

	// Fixes
	Win10Fix = iniReader.ReadInteger("Fixes", "CrashFix", 1) == 1;
	WheelFix = iniReader.ReadInteger("Fixes", "DisappearingWheelsFix", 1) == 1;
	X10Fix = iniReader.ReadInteger("Fixes", "ZeroBountyFix", 1) == 1;
	ImmobileColFix = iniReader.ReadInteger("Fixes", "ImmobileColFix", 0) == 1;

	// Misc
	WindowedMode = iniReader.ReadInteger("Misc", "WindowedMode", 0);
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) == 1;
	SkipNISs = iniReader.ReadInteger("Misc", "SkipNISs", 0) == 1;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) == 1;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) == 1;
	EnableVoice = iniReader.ReadInteger("Misc", "EnableVoice", 1) == 1;
	ShowMessage = iniReader.ReadInteger("Misc", "ShowMessage", 1) == 1;
	// SkipCareerIntro = iniReader.ReadInteger("Misc", "SkipCareerIntro", 0) == 1;
	AllowMultipleInstances = iniReader.ReadInteger("Misc", "AllowMultipleInstances", 0) == 1;
	ThreadDelay = iniReader.ReadInteger("Misc", "ThreadDelay", 10);

	// Bypass Debugger Detection
	injector::MakeJMP(0x46CD80, 0x46CD70, true);
	injector::MakeJMP(0x86B1D0, 0x46CD70, true);

	// Restrictions
	minLaps %= 128;
	maxLaps %= 128;
	minTime %= 128;
	maxTime %= 128;

	minOpponents %= 30;
	maxOpponents %= 30;

	MaximumMultiplierTrack %= 128;
	MaximumMultiplierCanyon %= 128;

	headlightsMode %= 3;
	
	TrafficLow %= 101;
	TrafficMed %= 101;
	TrafficHigh %= 101;

	ShowSpecialVinyls %= 3;

	SelectableMarkerCount--;
	SelectableMarkerCount %= 6;
	SelectableMarkerCount++;

	QRBackCamo %= 10;
	
	// Allow Multiple Instances
	if (AllowMultipleInstances)
	{
		injector::MakeRangedNOP(0x6B8E7F, 0x6B8E87, true);
		injector::MakeRangedNOP(0x6B8E96, 0x6B8E9E, true);
	}

	// Lap Controllers
	injector::WriteMemory<unsigned char>(0x4ac7fd, maxLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac811, maxLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac803, minLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac80b, minLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac819, maxTime, true); // P Tag Max Time
	injector::WriteMemory<unsigned char>(0x4ac82d, maxTime, true); // P Tag Max Time
	injector::WriteMemory<unsigned char>(0x4ac827, minTime, true); // P Tag Min Time
	injector::WriteMemory<unsigned char>(0x4ac81f, minTime, true); // P Tag Min Time
	
	// Opponent Controllers
	injector::MakeNOP(0x4a5bb8, 7, true); // Enable crew on controllers
	injector::WriteMemory<unsigned char>(0x4ac884, minOpponents, true); // Min - Crew Off
	injector::WriteMemory<unsigned char>(0x4ac897, minOpponents, true); // Min - Crew On
	injector::WriteMemory<unsigned char>(0x4ac890, maxOpponents, true); // Max - Crew Off
	injector::WriteMemory<unsigned char>(0x4ac87d, maxOpponents, true); // Max - Crew On
	injector::WriteMemory<unsigned char>(0x4ac8df, maxOpponents, true); // Max - P Tag
	injector::WriteMemory<unsigned char>(0x4ac8e9, maxOpponents, true); // Max - P Tag
	injector::WriteMemory<unsigned char>(0x4ac8c5, maxOpponents, true); // Max - Canyon S
	injector::WriteMemory<unsigned char>(0x4ac8d7, maxOpponents, true); // Max - Canyon S
	//injector::WriteMemory<unsigned char>(0x668ae7, maxOpponents, true); // Fix Crew Member option until 10 opponents?? (Cancelled, limits everything with 10)

	// Maximum Unique Opponent Cars
	injector::WriteMemory<unsigned char>(0x66943E, MaxUniqueOpponentCars, true);
	injector::WriteMemory<unsigned char>(0x6695C2, MaxUniqueOpponentCars, true);

	// Traffic Density Controllers (0-100)
	injector::WriteMemory<unsigned char>(0x7A9E40, TrafficLow, true); // Low (3)
	injector::WriteMemory<unsigned char>(0x7A9E44, TrafficMed, true); // Medium (10)
	injector::WriteMemory<unsigned char>(0x7A9E48, TrafficHigh, true); // High (50)

	// Tweaked Race Options Menus
	if (ShowMoreRaceOptions)
	{
		// Add 10th option to Quick Race Settings
		injector::WriteMemory<unsigned char>(0x84bdee, 0x0A, true);
		injector::WriteMemory(0x84c458, &HeatLevelOptionCodeCave, true);

		// Unfreeze Opponent Count for Race Wars Circuit Events
		injector::WriteMemory<unsigned char>(0x84b9a4, 0xEB, true);
		
		// AI Opponents in Checkpoint Mode
		injector::WriteMemory<unsigned char>(0x668EAF, 0xEB, true);

		// Enable Leaderboard in Checkpoint Mode
		injector::MakeNOP(0x5dc785, 2, true);

		// Can Change Active Crew Member Before Any Race
		injector::WriteMemory<unsigned char>(0x4A2923, 0xEB, true);
		injector::WriteMemory<unsigned char>(0x4A2924, 0x0A, true);

		// Crew Member in Any Race
		// injector::WriteMemory<unsigned char>(0x61BAA2, 0xB1, true);
		// injector::WriteMemory<unsigned char>(0x61BAA3, 0x01, true);

		injector::MakeJMP(0x84B861, 0x84B92B, true);

		// Hook Race Options Menu
		injector::MakeJMP(0x85E62D, FeQuickRaceOptions_SetupCodeCave, true);

		// Show Crew Member Power Meter in Any Race
		injector::WriteMemory<unsigned char>(0x4CD6C2, 0xEB, true);
		injector::WriteMemory<unsigned char>(0x4CD6C3, 0x24, true);

		// More than 1 AI Opponent in Canyon (Buggy) (FOR FUN)
		injector::WriteMemory<unsigned char>(0x668EDD, 0xEB, true);
		injector::WriteMemory<unsigned char>(0x668EDE, 0x07, true);

		// Force-Enable Game Mode Selection??
		if (ShowMoreRaceOptions==2) injector::MakeRangedNOP(0x84b771, 0x84b799, true);
	}
	

	// Show Subtitles
	if (ShowSubs)
	{
		injector::MakeNOP(0x5b687a, 2, true);
		injector::MakeNOP(0x5bb8f0, 2, true);
		injector::MakeNOP(0x5bbafb, 2, true);
	}

	// More Car Categories
	if (EnableMoreCarCategories)
	{
		injector::WriteMemory<unsigned char>(0x844A53, 0x80, true);
		injector::WriteMemory<unsigned char>(0x844A54, 0xFC, true);
		injector::WriteMemory<unsigned char>(0x844A55, 0x01, true);
		injector::WriteMemory<int>(0x844A20, 256, true);
		injector::WriteMemory<int>(0x86205A, 256, true);
	}

	// Language Select Screen
	if (ShowLanguageSelectScreen)
	{
		injector::WriteMemory<DWORD>(0x5BD584, 0x5BD4D0, true);
		injector::WriteMemory<DWORD>(0x5BD59C, 0x5BD424, true);

		// Show all languages
		injector::MakeNOP(0x85E14B, 2, true);
		injector::WriteMemory<unsigned char>(0x85E1CF, 0x0B, true);
	}

	// Challenge Series Bin
	injector::WriteMemory<unsigned char>(0x4a9f3c, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4aa009, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4aa08a, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4aa73b, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4b9c58, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4cb833, csBlacklist, true);

	// Splash Screen Time Limit
	injector::WriteMemory<float>(0x9C79A4 ,SplashScreenTimeLimit, true);

	// Disable Light Streaks
	if (!ShowLightStreaks)
	{
		injector::MakeNOP(0x869CD6, 2, true);
	}

	// Enable Drift Camera View Everywhere
	if (EnableCameras)
	{
		injector::MakeNOP(0x4C4EE3, 2, true);
		injector::MakeNOP(0x4C4F3F, 2, true);
	}

	// Fix headlights OFF
	injector::WriteMemory<float>(0x7CBE97, 0, true); // Left Headlight
	injector::WriteMemory<float>(0x7CBE9F, 0, true); // Right Headlight

	// Load cop lights preferences
	if (copLightsEnabled)
	{
		injector::WriteMemory<float>(0x7cbed9, copLightsAmount, true); // Red Flashing Lights
		injector::WriteMemory<float>(0x7cbee1, copLightsAmount, true); // Blue Flashing Lights
		injector::WriteMemory<float>(0x7cbee9, copLightsAmount, true); // White Flashing Lights
	}

	// Remove Barriers
	if (RemoveNeonBarriers)
	{
		injector::WriteMemory<unsigned char>(0x9d85c8, 0x59, true); // BARRIER_SPLINE_4501
		injector::WriteMemory<unsigned char>(0x9d85dc, 0x59, true); // BARRIER_SPLINE_4500
		injector::WriteMemory<unsigned char>(0x9d85f0, 0x59, true); // BARRIER_SPLINE_4091
		injector::WriteMemory<unsigned char>(0x9d8604, 0x59, true); // BARRIER_SPLINE_4090
		injector::WriteMemory<unsigned char>(0x9d8618, 0x59, true); // BARRIER_SPLINE_306
		injector::WriteMemory<unsigned char>(0x9d862c, 0x59, true); // BARRIER_SPLINE_305
		injector::WriteMemory<unsigned char>(0x9d8b34, 0x59, true); // BARRIER_SPLINE_%d
	}

	// Starting Cash
	injector::WriteMemory<int>(0x4C4CC7, StartingCash, true);
	injector::WriteMemory<int>(0x4C4CD7, StartingCash + 10000, true);

	// Force Collector's Edition
	if (ForceCollectorsEdition)
	{
		injector::WriteMemory<unsigned char>(0xA631E8, 0x01, true);
	}

	// Load Any Save Game
	injector::WriteMemory<unsigned char>(0x89584b, 0xEB, true);

	// Remove 10 save games limit
	injector::MakeRangedNOP(0x5B729E, 0x5B72A0, true); // Let user create a new save game instead of showing "Too many saves" dialog.
	injector::WriteMemory<unsigned char>(0x5AC479, 0xEB, true); // List all save games

	// Drift Multipliers
	injector::WriteMemory<unsigned char>(0x6be947, MaximumMultiplierTrack, true);
	injector::WriteMemory<unsigned char>(0x6ab943, MaximumMultiplierCanyon, true);
	injector::WriteMemory<unsigned char>(0x6ab945, MaximumMultiplierCanyon, true);

	// Drift Race Collision Threshold
	injector::WriteMemory<float>(0xA62F10, DriftRaceCollisionThreshold, true);

	// Heat Level Overrides EnableHeatLevelOverride
	injector::MakeNOP(0x449a7c, HeatLevelsCodeCaveExit - 0x449a7c, true); // Clean the unused code
	injector::MakeJMP(0x449a7c, HeatLevelsCodeCave, true); // Prepare the game for advanced force heat level hack

	// Rain Options
	if (AlwaysRain)
	{
		injector::WriteMemory<unsigned char>(0xB74D20, 0x01, true);
		injector::WriteMemory<unsigned char>(0x7D83C9, 0xEB, true); // Road Reflection Fix?? 7d8403??
	}
	injector::WriteMemory<float>(0xA798D4, RoadReflection, true);
	injector::WriteMemory<float>(0xA7984C, FallingRainSize, true);
	injector::WriteMemory<float>(0xA797D0, RainAmount, true);
	injector::WriteMemory<float>(0xA79850, RainIntensity, true);
	injector::WriteMemory<float>(0xA797E0, RainXing, true);
	injector::WriteMemory<float>(0xA797E4, RainFallSpeed, true);
	injector::WriteMemory<float>(0xA797E8, RainGravity, true);

	// Fog
	if (EnableFog)
	{
		injector::WriteMemory<unsigned char>(0xB74D64, 0x01, true);
	}

	// Quick Race Background Camo
	injector::WriteMemory<unsigned char>(0x9C8777, QRBackCamo + 0x30, true);

	// Disable HUD Shake
	if (!HUDShakeEffect)
	{
		injector::MakeJMP(0x5D53B4, 0x5D548C, true);
	}

	// Pause Screen Blur (thx Aero_)
	if (PauseScreenBlur)
	{
		injector::MakeJMP(0x73ECA6, PauseBlurCodeCave, true);
		injector::MakeJMP(0x73ECB6, PauseBlurCodeCave, true);
		injector::MakeJMP(0x73ECC6, PauseBlurCodeCave2, true);
		injector::MakeJMP(0x73ECD6, PauseBlurCodeCave2, true);
	}

	// Misc Options (Like MW Mod Loader)
	if (WindowedMode != 0)
	{
		injector::WriteMemory<unsigned char>(0xAB0AD4, 1, true);
	}
	
	if (SkipMovies)
	{
		injector::WriteMemory<unsigned char>(0xA9E6D8, SkipMovies, true);
	}

	if (SkipNISs)
	{
		injector::WriteMemory<unsigned char>(0xA9E64E, SkipNISs, true);
	}
	
	if (!EnableSound)
	{
		injector::WriteMemory<unsigned char>(0xA631B8, EnableSound, true);
	}
	
	if (!EnableMusic)
	{
		injector::WriteMemory<unsigned char>(0xA631BC, EnableMusic, true);
	}
	
	if (!EnableVoice)
	{
		injector::WriteMemory<unsigned char>(0xA631C0, EnableVoice, true);
	}
	
	if (SkipCareerIntro) //doesn't work
	{
		injector::WriteMemory<unsigned char>(0xA9E6C1, 1, true); // SkipCareerIntro
	}

	// Save Game loading fixes (Crash, 0% Progress, No cars, etc.)
	if (Win10Fix)
	{
		injector::MakeNOP(0x59606D, 2, true);
		injector::MakeNOP(0x5960A9, 2, true);
	}

	// Add Special vinyls to shop
	if (ShowSpecialVinyls)
	{
		if (ShowSpecialVinyls == 1)
		{
			// Unhide special category
			injector::MakeNOP(0x588BA8, 2, true);
			injector::MakeNOP(0x588BAD, 2, true);
		}
		
		if (ShowSpecialVinyls == 2)
		{
			// Unhide virus??
			injector::WriteMemory<DWORD>(0x577669, 0xDEADCAFE, true);
		}
		
		// Make all vinyls editable
		injector::MakeNOP(0x577FF1, 2, true);
		injector::MakeNOP(0x577FF8, 2, true);

		// Make all vinyls deformable
		injector::MakeNOP(0x577A11, 2, true);
		injector::MakeNOP(0x577A18, 2, true);

		// Make logos colorable
		injector::MakeNOP(0x577FA3, 2, true);
		injector::MakeNOP(0x577FAA, 2, true);

		// Hide "2 to change color"
		injector::MakeNOP(0x8411BF, 2, true);
		injector::MakeNOP(0x8411C6, 2, true);

		// Remove Vinyl - Car Specifications 
		injector::MakeNOP(0x588B8B, 2, true);
		injector::MakeNOP(0x588B96, 2, true);
		//injector::MakeNOP(0x588BA3, 2, true); // (breaks crew logo selection)
	}

	// Add Debug Car Customize to main menu
	if (ShowDebugCarCustomize)
	{
		injector::WriteMemory<unsigned char>(0xA9E680, 1, true);
	}

	// Drift Camera Movement (SmartLookAheadCamera)
	switch (CameraDriftMoveMode)
	{
	case 0: // Disable for all
			injector::WriteMemory<unsigned char>(0x48539C, 0xB3, true); // Drift
			injector::WriteMemory<unsigned char>(0x48539D, 0x00, true);
			injector::WriteMemory<unsigned char>(0x485398, 0xB3, true); // Others
			injector::WriteMemory<unsigned char>(0x485399, 0x00, true);
		break;

	case 1: default: // Enable for Drift, disable for others (Default behaviour)
			injector::WriteMemory<unsigned char>(0x48539C, 0xB3, true); // Drift
			injector::WriteMemory<unsigned char>(0x48539D, 0x01, true);
			injector::WriteMemory<unsigned char>(0x485398, 0xB3, true); // Others
			injector::WriteMemory<unsigned char>(0x485399, 0x00, true);
		break;

	case 2: // Disable for Drift, enable for others
			injector::WriteMemory<unsigned char>(0x48539C, 0xB3, true); // Drift
			injector::WriteMemory<unsigned char>(0x48539D, 0x00, true);
			injector::WriteMemory<unsigned char>(0x485398, 0xB3, true); // Others
			injector::WriteMemory<unsigned char>(0x485399, 0x01, true);
		break;

	case 3: // Enable for all
			injector::WriteMemory<unsigned char>(0x48539C, 0xB3, true); // Drift
			injector::WriteMemory<unsigned char>(0x48539D, 0x01, true);
			injector::WriteMemory<unsigned char>(0x485398, 0xB3, true); // Others
			injector::WriteMemory<unsigned char>(0x485399, 0x01, true);
		break;
	}

	// NIS Like Drift With Handbrake
	if (AugmentedDriftWithEBrake)
	{
		injector::WriteMemory<unsigned char>(0xA9E65B, 0x01, true);
	}

	// Fix Invisible Wheels
	if (WheelFix) injector::WriteMemory<unsigned char>(0x7BDDBC, 0x01, true);

	// Garage Hacks
	if (GarageZoom)
	{
		// Code cleanup
		injector::MakeRangedNOP(0x493A04, 0x493A0B, true);
		injector::MakeRangedNOP(0x493a27, 0x493A4B, true);
		
		// Fix mouse wheel and photo mode zoom
		injector::WriteMemory<unsigned char>(0x493A1D, 0xC7, true); // mov dword ptr ds:
		injector::WriteMemory<unsigned char>(0x493A1E, 0x86, true);
		injector::WriteMemory<DWORD>(0x493A1F, 0x160, true); // [esi+0x160],
		injector::WriteMemory<DWORD>(0x493A23, 0x00000000, true); // 0
	}
	if (GarageRotate)
	{
		injector::MakeNOP(0x4939C3, 5, true);
		injector::WriteMemory<unsigned char>(0x4939C3, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x4939C4, 0x01, true);
	}
	if (GarageShowcase)
	{
		injector::MakeNOP(0x83EFBB, 5, true);
		injector::WriteMemory<unsigned char>(0x83EFBB, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x83EFBC, 0x01, true);
	}

	// Unlock All Things
	if (UnlockAllThings)
	{
		injector::WriteMemory<unsigned char>(0xA9E6C0, 0x01, true);
	}

	// Pursuit Action Game Mode - Harder Pursuits in Quick Races
	if (PursuitActionMode)
	{
		// Replace Race Table (0x2283ECAF) with Heat Table (0xD4B0CC11)
		injector::WriteMemory<DWORD>(0x403386, 0xD4B0CC11, true);
		injector::WriteMemory<DWORD>(0x40AC86, 0xD4B0CC11, true);

		// Replace Race Support (0xE5332008) with Heat Support (0xF3918F68)
		injector::WriteMemory<DWORD>(0x4033A6, 0xF3918F68, true);
		injector::WriteMemory<DWORD>(0x40ACEA, 0xF3918F68, true);

		// Can Spawn Roadblocks in Quick Race
		injector::MakeNOP(0x41D012, 6, true);

		// Cops Can Call Support in Quick Race :
		injector::WriteMemory<unsigned char>(0x41D24A, 0xEB, true);

		// Other fixes ??
		injector::MakeNOP(0x41D298, 2, true);

	}

	// Selectable Marker Count
	injector::WriteMemory<unsigned char>(0x84E937, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84E8E7, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84E894, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84E877, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84E0C4, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84E1F9, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84DF0A, SelectableMarkerCount, true);
	injector::WriteMemory<unsigned char>(0x84E24C, SelectableMarkerCount, true);

	// Debug Cam Speed
	injector::WriteMemory<float>(0xA4F74C, DebugCameraTurboSpeed, true);
	injector::WriteMemory<float>(0xA4F750, DebugCameraSuperTurboSpeed, true);

	// Speedbreaker
	injector::WriteMemory<float>(0xA71270, SBRechargeTime, true);
	injector::WriteMemory<float>(0xA71274, SBRechargeSpeedLimit, true);
	injector::WriteMemory<float>(0xA71278, SBMassMultiplier, true);

	// Infractions
	injector::WriteMemory<float>(0x9D8094, SpeedingLimit, true);
	injector::WriteMemory<float>(0x9D8090, ExcessiveSpeedingLimit, true);
	injector::WriteMemory<float>(0x9D8098, RecklessDrivingLimit, true);

	// HUD Update Rate
	injector::WriteMemory<float>(0xA7127C, HUDUpdateRate, true);

	// Idle Camera Timeout
	injector::WriteMemory<float>(0x9C71EC, IdleCameraTimeout, true);

	// Uncensored Busted Screen
	if (UncensoredBustedScreen)
	{
		injector::WriteMemory<unsigned char>(0x66F881, 0x00, true); // FacePixelation::mPixelationOn = 0
		injector::WriteMemory<unsigned char>(0x66F806, 0x00, true);
	}

	// Show Non Pursuit Cops
	injector::WriteMemory<unsigned char>(0xA607D0, ShowNonPursuitCops, true);
	
	// Show Pursuit Cops
	injector::WriteMemory<unsigned char>(0xA607D1, ShowPursuitCops, true);

	// Radar Range
	injector::WriteMemory<float>(0xA590A4, RadarRange, true);

	// More Stock Cars for Newly Created Save Games
	if (ShowAllCarsInFE != 0)
	{
		injector::WriteMemory<unsigned char>(0xA9E6C3, 0x01, true);
		injector::WriteMemory<unsigned char>(0x4AE10F, ShowAllCarsInFE, true); // Add them to desired category
	}

	// No Rev Limiter
	if (NoRevLimiter)
	{
		injector::WriteMemory(0x9E5A4C, &Return0Hook, true);
	}

	// No Catch Up
	if (NoCatchUp)
	{
		// AIPerpVehicle::GetCatchupCheat
		injector::WriteMemory(0x9C4ABC, &Return0fHook, true);

		// DALOptions::GetCatchUp
		injector::WriteMemory<unsigned char>(0x4A59C4, 0xBA, true);
		injector::WriteMemory<int>(0x4A59C5, 0, true);
		injector::MakeNOP(0x4A59C9, 3, true);

	}

	// Immobile collisions fix
	if (ImmobileColFix)
	{
		injector::MakeRangedNOP(0x6E9502, 0x6E9508, true);
		injector::WriteMemory<short>(0x6E9502, 0x00B1, true);

		injector::MakeRangedNOP(0x6E94B3, 0x6E94B9, true);
		injector::WriteMemory<short>(0x6E94B3, 0x00B2, true);

		injector::WriteMemory<unsigned char>(0x6E94CF, 0, true); // RigidBody::IsImmobile
	}

	// More Opponent Cars
	if (MoreCarsForOpponents)
	{
		injector::MakeRangedNOP(0x444CB6, 0x444CBA, true); // force RandomOpponent = 1
		injector::MakeRangedNOP(0x667C13, 0x667C18, true); // force RandomOpponent = 1
		injector::WriteMemory<unsigned char>(0x667C13, 0xB0, true); // Game_FindPerformanceCandidates
		injector::WriteMemory<unsigned char>(0x667C14, 0x01, true); // Opponents can use bonus cars and cop cars
	}

	// Don't hide HUD on Look Back Cam
	if (NFSU2StyleLookBackCamera)
	{
		injector::WriteMemory<int>(0x48686B, 0, true);
	}

	// Show Debug Event ID
	if (ShowDebugEventID)
	{
		injector::MakeJMP(0x5B8AA2, DebugEventIDCodeCave, true);
		injector::WriteMemory<int>(0x5CF3D0, 0x2400000, true);
	}

	// X10 Bounty Fix
	if (X10Fix)
	{
		// Fix 0 Bounty
		injector::MakeRangedNOP(0x42A50B, X10FixCodeCaveExit, true);
		injector::MakeJMP(0x42A50B, X10FixCodeCave, true);

		// Fix combo timer
		injector::MakeRangedNOP(0x42A5D8, X10FixCodeCave2Exit, true);
		injector::MakeJMP(0x42A5D8, X10FixCodeCave2, true);
	}

	// Show Hidden Tracks
	if (ShowHiddenTracks)
	{
		// IsQuickRaceLocked - Nop lock jumps
		//injector::MakeJMP(0x4A229A, 0x4A22E0, true); 
		injector::MakeRangedNOP(0x4A22B8, 0x4A22BA, true); // GetIsChallengeSeriesRace
		injector::MakeRangedNOP(0x4A22C3, 0x4A22C5, true); // GetNeverInQuickRace
		injector::MakeRangedNOP(0x4A22CE, 0x4A22D0, true); // GetIsDDayRace
		injector::MakeRangedNOP(0x4A22DE, 0x4A22E0, true); // IsRaceExcluded
		injector::WriteMemory<unsigned short>(0x647CFB, 0x01B0, true); // IsQuickRaceUnlocked

		// unlock races
		injector::MakeRangedNOP(0x4A81C4, 0x4A81CA, true);
		injector::MakeRangedNOP(0x4A81D1, 0x4A81D3, true);
		injector::MakeRangedNOP(0x4A81E2, 0x4A81E4, true);

		// fake x and y coords for some races
		injector::MakeJMP(0x5C3C3C, RacePositionCodeCave, true);
		injector::MakeJMP(0x613996, RacePositionCodeCave2, true);

		// change null regions
		injector::MakeJMP(0x63C49A, TrackRegionCodeCave, true);

		// race end crash fix
		//injector::MakeRangedNOP(0x4A231E, 0x4A2320, true);
	}

	// World Animation Speed
	injector::WriteMemory<float>(0xA798B4, WorldAnimationSpeed, true);

	// Game Speed
	injector::WriteMemory<float>(0xA712AC, GameSpeed, true);

	// Car size hack
	injector::WriteMemory<float>(0x7AD540, CarScale, true); // Length
	injector::WriteMemory<float>(0x7AD572, CarScale, true); // Width
	injector::WriteMemory<float>(0x7AD5A4, CarScale, true); // Height

	// String Replacement
	injector::MakeJMP(0x57861A, StringReplacementCodeCave, true);

    // Other Things
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Thing, NULL, 0, NULL);
}

DWORD WINAPI Thing(LPVOID)
{
	while (true)
	{
		Sleep(ThreadDelay);

		GameState = *(int*)0xA99BBC; // 3 = FE, 4&5 = Loading screen, 6 = Gameplay
		windowHandle = *(HWND*)0xAB0AD8;
		IsOnFocus = !(*(bool*)0xAB0B3C);

		// Windowed Mode Related Fixes
		if (WindowedMode == 2 && windowHandle && !once2)
		{
			RECT o_cRect, n_cRect, n_wRect;
			GetClientRect(windowHandle, &o_cRect);

			DWORD wStyle = GetWindowLongPtr(windowHandle, GWL_STYLE) | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW;
			SetWindowLongPtr(windowHandle, GWL_STYLE, wStyle);

			// make window change style
			SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

			GetWindowRect(windowHandle, &n_wRect);
			GetClientRect(windowHandle, &n_cRect);
			int n_wWidth = n_wRect.right - n_wRect.left;
			int n_wHeight = n_wRect.bottom - n_wRect.top;
			int dif_wWidth = o_cRect.right - n_cRect.right;
			int dif_wHeight = o_cRect.bottom - n_cRect.bottom;
			int newWidth = n_wWidth + dif_wWidth;
			int newHeight = n_wHeight + dif_wHeight;

			SetWindowPos(windowHandle, NULL, 0, 0, newWidth, newHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

			once2 = 1;
		}

		// Ultimate Force Heat Level
		if ((GetAsyncKeyState(hotkeyToggleForceHeat) & 1) && (GameState == 6) && IsOnFocus) //When pressed "Toggle Force Heat"
		{
			forceHeatLevel = !forceHeatLevel; // Toggle option
			if (forceHeatLevel)
			{
				EnableHeatLevelOverride = 1;
				heatLevel = MinHeatLevel - 1;
				if (ShowMessage) Hud_ShowMessage("^Ultimate Force Heat Level hack is enabled.");
			}
			else
			{
				// Re-read the override boolean from config file
				CIniReader iniReader("NFSCExtraOptionsSettings.ini");
				EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 1) == 1;
				if (ShowMessage) Hud_ShowMessage("^Ultimate Force Heat Level hack is disabled.");
			}

			while ((GetAsyncKeyState(hotkeyToggleForceHeat) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		if ((GetAsyncKeyState(hotkeyForceHeatLevel) & 1) && forceHeatLevel && (GameState == 6) && IsOnFocus) // Set Heat Level
		{
			
			heatLevel = (int)(floorf(heatLevel) - floorf(MinHeatLevel) + 1) % (int)(floorf(MaxHeatLevel) - floorf(MinHeatLevel) + 1) + MinHeatLevel;

			Game_SetWorldHeat(heatLevel); // Use direct function call to set the heat level

			while ((GetAsyncKeyState(hotkeyForceHeatLevel) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		if ((GetAsyncKeyState(hotkeyToggleCops) & 1) && forceHeatLevel && (GameState == 6) && IsOnFocus) // Toggle Cops
		{
			ToggleCops = !ToggleCops;
			Game_SetCopsEnabled(ToggleCops);

			if (ToggleCops)
			{
				if (ShowMessage) Hud_ShowMessage("^Cops are now enabled.");
			}
			else
			{
				if (ShowMessage) Hud_ShowMessage("^Cops are now disabled.");
			}

			while ((GetAsyncKeyState(hotkeyToggleCops) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}


		// Cop Lights
		if ((GetAsyncKeyState(hotkeyToggleCopLights) & 1) && (GameState == 6) && IsOnFocus) // When pressed "Toggle Police Lights" key
		{
			copLightsEnabled = !copLightsEnabled;

			DWORD* PlayerPVehicle = *(DWORD**)0x00A9F168;

			if (PlayerPVehicle)
			{
				if (copLightsEnabled) // Enable cop lights - more proper method
				{
					if (!PVehicle_IsGlareOn(PlayerPVehicle, 0x7000)) PVehicle_GlareOn(PlayerPVehicle, 0x7000);
				}
				else // Disable cop lights
				{
					if (PVehicle_IsGlareOn(PlayerPVehicle, 0x7000)) PVehicle_GlareOff(PlayerPVehicle, 0x7000);
				}
			}

			while ((GetAsyncKeyState(hotkeyToggleCopLights) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Headlights
		if ((GetAsyncKeyState(hotkeyToggleHeadlights) & 1) && (GameState == 6) && IsOnFocus) // When pressed "Toggle Head Lights" key
		{
			headlightsMode = !headlightsMode;

			DWORD* PlayerPVehicle = *(DWORD**)0x00A9F168;

			if (PlayerPVehicle)
			{
				if (headlightsMode) // Enable headlights - more proper method
				{
					if (!PVehicle_IsGlareOn(PlayerPVehicle, 7))
					{
						injector::WriteMemory<unsigned char>(0x6C63A6, 7, true);
						PVehicle_GlareOn(PlayerPVehicle, 7);
						//injector::WriteMemory<unsigned char>(0x74A555, 0x75, true); // enable dynamic light
					}
				}
				else // Disable headlights
				{
					if (PVehicle_IsGlareOn(PlayerPVehicle, 7))
					{
						injector::WriteMemory<unsigned char>(0x6C63A6, 0, true);
						PVehicle_GlareOff(PlayerPVehicle, 7);
						//injector::WriteMemory<unsigned char>(0x74A555, 0xEB, true); // disable dynamic light
					}
				}
			}

			while ((GetAsyncKeyState(hotkeyToggleHeadlights) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Freeze Camera
		if ((GetAsyncKeyState(hotkeyFreezeCamera) & 1) && IsOnFocus)
		{
			*(bool*)0xA888D8 = !(*(bool*)0xA888D8);

			while ((GetAsyncKeyState(hotkeyFreezeCamera) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// UnlockAllThings
		if ((GetAsyncKeyState(hotkeyUnlockAllThings) & 1) && IsOnFocus) //When pressed "Unlock All Things"
		{
			UnlockAllThings = !UnlockAllThings; // Toggle option
			CIniReader iniReader("NFSCExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "UnlockAllThings", UnlockAllThings);

			if (UnlockAllThings)
			{
				injector::WriteMemory<unsigned char>(0xA9E6C0, 0x01, true);
			}
			else
			{
				injector::WriteMemory<unsigned char>(0xA9E6C0, 0x00, true);
			}

			while ((GetAsyncKeyState(hotkeyUnlockAllThings) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// .hot Save And Load
		if (EnableSaveLoadHotPos && (GameState == 6) && IsOnFocus)
		{
			// Save
			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(49) & 0x8000)
			{
				*(unsigned int*)0xb74bf8 = 1; 
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 1.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(50) & 0x8000)
			{
				*(unsigned int*)0xb74bf8 = 2;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 2.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(51) & 0x8000)
			{
				*(unsigned int*)0xb74bf8 = 3;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 3.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(52) & 0x8000)
			{
				*(unsigned int*)0xb74bf8 = 4;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 4.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(53) & 0x8000)
			{
				*(unsigned int*)0xb74bf8 = 5;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 5.");
			}


			// Load
			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(49) & 0x8000)
			{
				*(unsigned int*)0xb74bfC = 1;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 1.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(50) & 0x8000)
			{
				*(unsigned int*)0xb74bfC = 2;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 2.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(51) & 0x8000)
			{
				*(unsigned int*)0xb74bfC = 3;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 3.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(52) & 0x8000)
			{
				*(unsigned int*)0xb74bfC = 4;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 4.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(53) & 0x8000)
			{
				*(unsigned int*)0xb74bfC = 5;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 5.");
			}
		}

		// AutoDrive
		if ((GetAsyncKeyState(hotkeyAutoDrive) & 1) && (GameState == 6) && IsOnFocus)
		{
			AutoDrive = !AutoDrive;

			if (AutoDrive)
			{
				Game_ForceAIControl(1);
			}
			else
			{
				Game_ClearAIControl(1);
			}

			while ((GetAsyncKeyState(hotkeyAutoDrive) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Drift Mode
		if ((GetAsyncKeyState(hotkeyDriftMode) & 1) && (GameState == 6) && IsOnFocus) //When pressed "Phys Switch"
		{
			DriftMode = !DriftMode; // Toggle option

			if (DriftMode)
			{
				Game_ActivateDriftMode();
				if (ShowMessage) Hud_ShowMessage("^Drift physics are enabled.");
			}
			else
			{
				Game_DeactivateDriftMode();
				if (ShowMessage) Hud_ShowMessage("^Drift physics are disabled.");
			}

			while ((GetAsyncKeyState(hotkeyDriftMode) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Debug Camera
		if (EnableDebugWorldCamera && (GameState == 6) && IsOnFocus)
		{
			if ((GetAsyncKeyState(VK_BACK) & 1))
			{
				DebugCamStatus = !DebugCamStatus;
				if (DebugCamStatus) CameraAI_SetAction(1, "CDActionDebug");
				else CameraAI_SetAction(1, "CDActionDrive");

				while ((GetAsyncKeyState(VK_BACK) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}

			if ((GetAsyncKeyState(VK_NEXT) & 1)) // Page Down : Toggle Debug Watch Car Camera
			{
				DebugWatchCarCamera = !DebugWatchCarCamera;
				*(unsigned char*)0xA88914 = 1;

				if (DebugWatchCarCamera)
				{
					*(unsigned char*)0xA888F1 = 1;
					CameraAI_SetAction(1, "CDActionDebugWatchCar");
				}

				else
				{
					CameraAI_SetAction(1, "CDActionDrive");
					*(unsigned char*)0xA888F1 = 0;
				}

				while ((GetAsyncKeyState(VK_NEXT) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}

			if ((GetAsyncKeyState(VK_ADD) & 1) && DebugWatchCarCamera) // + : Next car
			{
				*(unsigned char*)0xA88914 += 1;

				while ((GetAsyncKeyState(VK_ADD) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}

			if ((GetAsyncKeyState(VK_SUBTRACT) & 1) && DebugWatchCarCamera) // - : Previous car
			{
				*(unsigned char*)0xA88914 -= 1;

				while ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}
		}
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x87E926) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).", "NFSC Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
	
}

