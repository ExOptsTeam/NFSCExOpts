#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"

DWORD WINAPI Thing(LPVOID);

DWORD HeatLevelAddr, AutoDriveAddr;
unsigned char minLaps, maxLaps, minTime, maxTime, minOpponents, maxOpponents, csBlacklist, headLightsMode, MaximumMultiplierTrack, MaximumMultiplierCanyon, TrafficLow, TrafficMed, TrafficHigh, CameraDriftMoveMode, ShowSpecialVinyls, ShowMoreRaceOptions;
int hotkeyToggleForceHeat, hotkeyForceHeatLevel, hotkeyToggleCopLights, hotkeyToggleHeadLights, hotkeyUnlockSeriesCarsAndUpgrades, hotkeyAutoDrive;
bool UnfreezeRaceWarsCircuits, ShowSubs, EnableMoreCarCategories, ShowLanguageSelectScreen, InfiniteAutosculptSliders, nlgzrgnTakeOver, EnableCameras, copLightsEnabled, RemoveNeonBarriers, UnlockStrangeRace, UnlockSeriesCarsAndUpgrades, EnableHeatLevelOverride, AlwaysRain, WindowedMode, SkipMovies, EnableSound, EnableMusic, EnableVoice, GarageZoom, GarageRotate, GarageShowcase, ShowDebugCarCustomize, Win10Fix, AugmentedDriftWithEBrake, AutoDrive, UnlockAllThings;
bool forceHeatLevel = 0, once1 = 0, once2 = 0;
float SplashScreenTimeLimit, copLightsAmount, LowBeamAmount, HighBeamAmount, MinHeatLevel, MaxHeatLevel, heatLevel, RainAmount, RoadReflection, FallingRainSize, RainIntensity, RainXing, RainFallSpeed, RainGravity, WorldAnimationSpeed, GameSpeed, CarScale;

DWORD HeatLevelsCodeCaveExit = 0x449a82;
DWORD StringReplacementCodeCaveExit = 0x57861F;

char* StringBuffer1 = "© 2006 Electronic Arts Inc. All rights reserved.^NFSC Extra Options - © 2016 nlgzrgn. No rights reserved.";
DWORD _A7EBC389_New = (DWORD)StringBuffer1;

DWORD CopsOptionCodeCaveExit = 0x84C1E1;
DWORD CopsOptionCodeCave2Exit = 0x84C20A;
DWORD CopsOptionCodeCave3Exit = 0x84C219;
DWORD LearnRaceModeCodeCaveExit = 0x85E639;

DWORD AddElementToTrackOptions = 0x84bdd0;
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

void __declspec(naked) CopsOptionCodeCave()
{
	_asm
	{
			mov RaceOptionToCreate,eax
			push 0x00000084
			jmp CopsOptionCodeCaveExit
	}
}

void __declspec(naked) CopsOptionCodeCave2()
{
	_asm
	{
			cmp RaceOptionToCreate,0x0A
			je PushCopsAddress

		PushNOSAddress:
			push 0x000013E9
			jmp CopsOptionCodeCave2Exit

		PushCopsAddress:
			push 0x000013E7
			jmp CopsOptionCodeCave2Exit
	}
}

void __declspec(naked) CopsOptionCodeCave3()
{
	_asm
	{
			cmp RaceOptionToCreate, 0x0A
			je PushCopsName

		PushNOSName:
			mov dword ptr ds : [esp + 0x38], 0x70DFDEF6
			jmp CopsOptionCodeCave3Exit

		PushCopsName:
			mov dword ptr ds : [esp + 0x38], 0x2839A51E
			jmp CopsOptionCodeCave3Exit
	}
}

void __declspec(naked) LearnRaceModeCodeCave()
{
	_asm
	{
			mov QRRaceMode, eax
			jmp LearnRaceModeCodeCaveExit
	}
}

void __declspec(naked) NewRaceMenuCodeCave()
{
	_asm
	{
			push ecx
			push ebx
			push esi

			// Choose which options to show
			mov eax, QRRaceMode
			inc eax // It decreases before the code cave

			cmp ShowMoreRaceOptions,2
			je GMCircuit

			cmp eax, 2
			je GMSprint
			cmp eax, 8
			je GMSprint
			cmp eax, 3
			je GMSprintCanyon
			cmp eax, 5
			je GMDrift
			cmp eax, 6
			je GMCanyonDrift
			cmp eax, 9
			je GMCanyon
			cmp eax, 10
			je GMPursuitTag
			cmp eax, 11
			je GMPursuitKO
			cmp eax, 14
			je GMRaceWars
			cmp eax, 7
			je GMCheckpoint
			jmp GMCircuit

			// Game Modes
		GMSprint:
			mov QRLaps, 0
			mov QRCrew, 1
			mov QRTraffic, 1
			mov QROpponents, 1
			mov QRCatchUp, 1
			mov QRNitrous, 1
			mov QRShadowOption, 1
			mov QRDifficulty, 1
			mov QRCops, 1
			jmp AddMenuElements

		GMSprintCanyon :
			mov QRLaps, 0
			mov QRCrew, 0
			mov QRTraffic, 1
			mov QROpponents, 1
			mov QRCatchUp, 1
			mov QRNitrous, 1
			mov QRShadowOption, 1
			mov QRDifficulty, 1
			mov QRCops, 1
			jmp AddMenuElements

		GMCircuit :
			mov QRLaps, 1
			mov QRCrew, 1
			mov QRTraffic, 1
			mov QROpponents, 1
			mov QRCatchUp, 0 // To fix a crash, sorry for that. :(
			mov QRNitrous, 1
			mov QRShadowOption, 1
			mov QRDifficulty, 1
			mov QRCops, 1
			jmp AddMenuElements

		GMDrift :
			mov QRLaps, 1
			mov QRCrew, 0
			mov QRTraffic, 1
			mov QROpponents, 0
			mov QRCatchUp, 0
			mov QRNitrous, 1
			mov QRShadowOption, 1
			mov QRDifficulty, 0
			mov QRCops, 1
			jmp AddMenuElements

		GMCanyonDrift :
			mov QRLaps, 0
			mov QRCrew, 0
			mov QRTraffic, 1
			mov QROpponents, 0
			mov QRCatchUp, 0
			mov QRNitrous, 1
			mov QRShadowOption, 0
			mov QRDifficulty, 0
			mov QRCops, 1
			jmp AddMenuElements

		GMCanyon :
			mov QRLaps, 0
			mov QRCrew, 0
			mov QRTraffic, 1
			mov QROpponents, 0
			mov QRCatchUp, 0
			mov QRNitrous, 1
			mov QRShadowOption, 0
			mov QRDifficulty, 1
			mov QRCops, 1
			jmp AddMenuElements

		GMPursuitTag :
			mov QRLaps, 1
			mov QRCrew, 0
			mov QRTraffic, 0
			mov QROpponents, 1
			mov QRCatchUp, 0
			mov QRNitrous, 0
			mov QRShadowOption, 0
			mov QRDifficulty, 0
			mov QRCops, 0
			jmp AddMenuElements

		GMPursuitKO :
			mov QRLaps, 0
			mov QRCrew, 0
			mov QRTraffic, 1
			mov QROpponents, 1
			mov QRCatchUp, 0
			mov QRNitrous, 0
			mov QRShadowOption, 0
			mov QRDifficulty, 0
			mov QRCops, 0
			jmp AddMenuElements

		GMRaceWars :
			mov QRLaps, 1
			mov QRCrew, 0
			mov QRTraffic, 0
			mov QROpponents, 1
			mov QRCatchUp, 1
			mov QRNitrous, 1
			mov QRShadowOption, 1
			mov QRDifficulty, 1
			mov QRCops, 1
			jmp AddMenuElements

		GMCheckpoint :
			mov QRLaps, 0
			mov QRCrew, 0
			mov QRTraffic, 1
			mov QROpponents, 0
			mov QRCatchUp, 0
			mov QRNitrous, 1
			mov QRShadowOption, 1
			mov QRDifficulty, 0
			mov QRCops, 1
			jmp AddMenuElements

			// Do the job
		AddMenuElements:

		MGameMode:

			lea eax, [esp + 0x0B]
			push eax
			mov ebx,0x00000001
			push 0 // Game Mode
			mov esi,ecx
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MTrackingMode:

			lea ecx, [esp + 0x0B]
			push ecx
			push 1 // Tracking Mode
			mov ecx,esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MShadowOption:

			cmp QRShadowOption, 1
			jne MDifficulty

			lea edx, [esp + 0x0B]
			push edx
			push 8 // Shadow Option
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MDifficulty:

			cmp QRDifficulty, 1
			jne MLaps

			lea eax, [esp + 0x0B]
			push eax
			push 9 // Difficulty
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MLaps :
			cmp QRLaps, 1
			jne MCrewMember

			lea ecx, [esp + 0x0B]
			push ecx
			push 2 // Laps
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MCrewMember:
			cmp QRCrew, 1
			jne MTraffic

			lea edx, [esp + 0x0B]
			push edx
			push 3 // Crew Member
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MTraffic:
			cmp QRTraffic, 1
			jne MCops

			lea eax, [esp + 0x0B]
			push eax
			push 4 // Traffic Level
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MCops:
			cmp QRCops, 1
			jne MOpponents

			lea ecx, [esp + 0x0B]
			push ecx
			push 10 // Cops
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MOpponents:
			cmp QROpponents, 1
			jne MCatchUp

			lea edx, [esp + 0x0B]
			push edx
			push 5 // Opponents
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MCatchUp:
			cmp QRCatchUp, 1
			jne MNos

			lea eax, [esp + 0x0B]
			push eax
			push 6 // Catch Up
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MNos:
			cmp QRNitrous, 1
			jne MExit

			lea ecx, [esp + 0x0B]
			push ecx
			push 7 // NOS
			mov ecx, esi
			mov byte ptr ds : [esp + 0x13], bl
			call AddElementToTrackOptions

		MExit:

			pop esi
			pop ebx
			pop ecx
			ret
	}
}

void __declspec(naked) StringReplacementCodeCave()
{
	_asm
	{
			mov ecx, dword ptr ds : [ebx + eax * 0x08]

			cmp nlgzrgnTakeOver, 0x00
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


void Init()
{
	CIniReader iniReader("NFSCExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyToggleForceHeat = iniReader.ReadInteger("Hotkeys", "HeatLevelHack", 118); //F7
	hotkeyForceHeatLevel = iniReader.ReadInteger("Hotkeys", "ChangeHeatLevel", 33); //PageUp
	hotkeyToggleCopLights = iniReader.ReadInteger("Hotkeys", "CopLights", 79); // O
	hotkeyToggleHeadLights = iniReader.ReadInteger("Hotkeys", "HeadLights", 72); // H
	hotkeyUnlockSeriesCarsAndUpgrades = iniReader.ReadInteger("Hotkeys", "UnlockSeriesCarsAndUpgrades", 119); // F8
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); // F6


	// LapControllers
	minLaps = iniReader.ReadInteger("LapControllers", "Minimum", 0);
	maxLaps = iniReader.ReadInteger("LapControllers", "Maximum", 127);
	minTime = iniReader.ReadInteger("LapControllers", "MinTimePursuitTag", 0);
	maxTime = iniReader.ReadInteger("LapControllers", "MaxTimePursuitTag", 127);
	
	// OpponentControllers
	minOpponents = iniReader.ReadInteger("OpponentControllers", "Minimum", 0);
	maxOpponents = iniReader.ReadInteger("OpponentControllers", "Maximum", 19);
	UnfreezeRaceWarsCircuits = iniReader.ReadInteger("OpponentControllers", "UnfreezeRaceWarsCircuits", 1) == 1;

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
	InfiniteAutosculptSliders = iniReader.ReadInteger("Menu", "InfiniteAutosculptSliders", 0) == 1;
	csBlacklist = iniReader.ReadInteger("Menu", "ChallengeSeriesBlacklist", 19);
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	GarageZoom = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteZoom", 0) == 1;
	GarageRotate = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteRotation", 0) == 1;
	GarageShowcase = iniReader.ReadInteger("Menu", "ShowcaseCamAlwaysEnable", 0) == 1;
	nlgzrgnTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 0) == 1;
	CameraDriftMoveMode = iniReader.ReadInteger("Gameplay", "SmartLookaheadCameraMode", 0);
	GameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	WorldAnimationSpeed = iniReader.ReadFloat("Gameplay", "WorldAnimationSpeed", 45.0f);
	CarScale = iniReader.ReadFloat("Gameplay", "CarScale", 1.0f);
	copLightsEnabled = iniReader.ReadInteger("Gameplay", "CopLightsMode", 0) == 1;
	copLightsAmount = iniReader.ReadFloat("Gameplay", "CopLightsBrightness", 1.00f);
	headLightsMode = iniReader.ReadInteger("Gameplay", "HeadLightsMode", 2);
	LowBeamAmount = iniReader.ReadFloat("Gameplay", "LowBeamBrightness", 0.75f);
	HighBeamAmount = iniReader.ReadFloat("Gameplay", "HighBeamBrightness", 1.00f);
	RemoveNeonBarriers = iniReader.ReadInteger("Gameplay", "RemoveNeonBarriers", 0) == 1;
	UnlockStrangeRace = iniReader.ReadInteger("Gameplay", "UnlockStrangeRace", 0) == 1;
	UnlockSeriesCarsAndUpgrades = iniReader.ReadInteger("Gameplay", "UnlockSeriesCarsAndUpgrades", 0) == 1;
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 0) == 1;

	// Drift
	MaximumMultiplierTrack = iniReader.ReadInteger("Drift", "MaximumMultiplierTrack", 10);
	MaximumMultiplierCanyon = iniReader.ReadInteger("Drift", "MaximumMultiplierCanyon", 20);
	AugmentedDriftWithEBrake = iniReader.ReadInteger("Drift", "AugmentedDriftWithEBrake", 0) == 1;

	// Pursuit
	EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 0) == 1;
	MinHeatLevel = iniReader.ReadFloat("Pursuit", "MinimumHeatLevel", 1.00f);
	MaxHeatLevel = iniReader.ReadFloat("Pursuit", "MaximumHeatLevel", 10.00f);

	// Weather
	AlwaysRain = iniReader.ReadInteger("Weather", "AlwaysRain", 0) == 1;
	RainAmount = iniReader.ReadFloat("Weather", "GeneralRainAmount", 1.0f);
	RoadReflection = iniReader.ReadFloat("Weather", "RoadReflectionAmount", 1.0f);
	FallingRainSize = iniReader.ReadFloat("Weather", "RainSize", 0.01f);
	RainIntensity = iniReader.ReadFloat("Weather", "RainIntensity", 0.45f);
	RainXing = iniReader.ReadFloat("Weather", "RainCrossing", 0.02f);
	RainFallSpeed = iniReader.ReadFloat("Weather", "RainSpeed", 0.03f);
	RainGravity = iniReader.ReadFloat("Weather", "RainGravity", 0.35f);

	// Misc
	WindowedMode = iniReader.ReadInteger("Misc", "WindowedMode", 0) == 1;
	Win10Fix = iniReader.ReadInteger("Misc", "Win10Fix", 1) == 1;
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) == 1;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) == 1;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) == 1;
	EnableVoice = iniReader.ReadInteger("Misc", "EnableVoice", 1) == 1;

	// Restrictions
	if (minLaps < 0 || minLaps > 127) minLaps = 1;
	if (maxLaps < 0 || maxLaps > 127) maxLaps = 8;
	if (minTime < 0 || minTime > 127) minTime = 3;
	if (maxTime < 0 || maxTime > 127) maxTime = 7;

	if (minOpponents < 0 || minOpponents > 29) minOpponents = 0;
	if (maxOpponents < 0 || maxOpponents > 29) maxOpponents = 7;

	if (MaximumMultiplierTrack < 1 || MaximumMultiplierTrack > 127) MaximumMultiplierTrack = 10;
	if (MaximumMultiplierCanyon < 1 || MaximumMultiplierCanyon > 127) MaximumMultiplierCanyon = 20;

	if (MaxHeatLevel < 1 || MaxHeatLevel < MinHeatLevel || MaxHeatLevel > 10) MaxHeatLevel = 5;
	if (MinHeatLevel < 1 || MaxHeatLevel < MinHeatLevel || MinHeatLevel > 10) MinHeatLevel = 1;
	if (headLightsMode > 2) headLightsMode = 2;

	if (TrafficLow < 0 || TrafficLow > 100) TrafficLow = 3;
	if (TrafficMed < 0 || TrafficMed > 100) TrafficMed = 10;
	if (TrafficHigh < 0 || TrafficHigh > 100) TrafficHigh = 50;

	if (ShowSpecialVinyls > 2) ShowSpecialVinyls = 2;
	
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

	// Unfreeze Opponent Count for Race Wars Circuit Events
	if (UnfreezeRaceWarsCircuits)
	{
		injector::WriteMemory<unsigned char>(0x84b9a4, 0xEB, true);
	}

	// Traffic Density Controllers (0-100)
	injector::WriteMemory<unsigned char>(0x7A9E40, TrafficLow, true); // Low (3)
	injector::WriteMemory<unsigned char>(0x7A9E44, TrafficMed, true); // Medium (10)
	injector::WriteMemory<unsigned char>(0x7A9E48, TrafficHigh, true); // High (50)


	// Tweaked Race Options Menus
	if (ShowMoreRaceOptions)
	{
		// Add 10th option to Quick Race Settings
		injector::WriteMemory<unsigned char>(0x84bdee, 0x0A, true);
		injector::WriteMemory<DWORD>(0x84c458, 0x84c1dc, true);

		// Reuse NOS Option to put things together
		injector::MakeJMP(0x84c1dc, CopsOptionCodeCave, true);
		injector::MakeJMP(0x84c205, CopsOptionCodeCave2, true);
		injector::MakeNOP(0x84c211, CopsOptionCodeCave3Exit - 0x84c211, true);
		injector::MakeJMP(0x84c211, CopsOptionCodeCave3, true);

		// Use a Reworked Circuit Menu for All
		injector::MakeRangedNOP(0x85E62D, 0x85E639, true);
		injector::MakeJMP(0x85E62D, LearnRaceModeCodeCave, true);
		injector::MakeCALL(0x85E63B, NewRaceMenuCodeCave, true);

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

	// Infinite Autosculpt
	if (InfiniteAutosculptSliders)
	{
		injector::MakeNOP(0x57331E, 5, true);
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

	// Enable Drift Camera View Everywhere
	if (EnableCameras)
	{
		injector::MakeNOP(0x4C4EE3, 2, true);
		injector::MakeNOP(0x4C4F3F, 2, true);
	}

	// Load headlights preferences
	switch (headLightsMode)
	{
		case 0:
			injector::WriteMemory<float>(0x7cbf96, 0, true); // Left HeadLight
			injector::WriteMemory<float>(0x7cbf77, 0, true); // Right HeadLight
			break;
		case 1:
			injector::WriteMemory<float>(0x7cbf96, LowBeamAmount, true); // Left HeadLight
			injector::WriteMemory<float>(0x7cbf77, LowBeamAmount, true); // Right HeadLight
			break;
		case 2: default:
			injector::WriteMemory<float>(0x7cbf96, HighBeamAmount, true); // Left HeadLight
			injector::WriteMemory<float>(0x7cbf77, HighBeamAmount, true); // Right HeadLight
			break;
	}

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

	// Unlock a strange Canyon Race
	if (UnlockStrangeRace)
	{
		injector::MakeNOP(0x61C237, 6, true);
	}
	
	// Unlock Series Cars & Upgrades Option From NFSC Unlocker
	if (UnlockSeriesCarsAndUpgrades)
	{
		injector::WriteMemory<unsigned char>(0x49ECD2, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x49ECD3, 0x01, true);
	}

	// Load Any Save Game
	injector::WriteMemory<unsigned char>(0x89584b, 0xEB, true);

	// Drift Multipliers
	injector::WriteMemory<unsigned char>(0x6be947, MaximumMultiplierTrack, true);
	injector::WriteMemory<unsigned char>(0x6ab943, MaximumMultiplierCanyon, true);
	injector::WriteMemory<unsigned char>(0x6ab945, MaximumMultiplierCanyon, true);

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

	// Misc Options (Like MW Mod Loader)
	if (WindowedMode)
	{
		injector::WriteMemory<unsigned char>(0xAB0AD4, WindowedMode, true);
	}
	
	if (SkipMovies)
	{
		injector::WriteMemory<unsigned char>(0xA9E6D8, SkipMovies, true);
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

	// Save Game loading fixes (Crash, 0% Progress, No cars, etc.)
	if (Win10Fix)
	{
		injector::MakeNOP(0x59606D, 2, true);
		injector::MakeNOP(0x5960A9, 2, true);
	}

	// Add Special vinyls to shop
	if (ShowSpecialVinyls)
	{
		if (ShowSpecialVinyls == 1) injector::WriteMemory<unsigned char>(0x588BA7, 0x16, true); // Show Special category
		
		injector::MakeNOP(0x588BBA, 2, true); // Show Virus Category (Will be hidden if Special is shown)

		// Remove Vinyl - Car Specifications
		injector::MakeNOP(0x588B8B, 2, true);
		injector::MakeNOP(0x588B96, 2, true);
		injector::MakeNOP(0x588BA3, 2, true);
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
	injector::WriteMemory<unsigned char>(0x7BDDBC, 0x01, true);

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
		Sleep(0);
		HeatLevelAddr = (*(DWORD*)0xAA7724) + 0x14; // Heat Level Pointer
		AutoDriveAddr = (*(DWORD*)0xA9FFF8) + 0x8; // AutoDrive (AIControl)
		
		//Advanced Force Heat Level
		if ((GetAsyncKeyState(hotkeyToggleForceHeat) & 1)) //When pressed "Toggle Force Heat"
		{
			forceHeatLevel = !forceHeatLevel; // Toggle option
			if (forceHeatLevel)
			{
				EnableHeatLevelOverride = 1;
				heatLevel = MinHeatLevel - 1;
			}
			else
			{
				// Re-read the override boolean from config file
				CIniReader iniReader("NFSCExtraOptionsSettings.ini");
				EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 1) == 1;
			}

			while ((GetAsyncKeyState(hotkeyToggleForceHeat) & 0x8000) > 0) { Sleep(0); }
		}

		if ((GetAsyncKeyState(hotkeyForceHeatLevel) & 1)) //When pressed "Forced Heat Level"
		{
			if (forceHeatLevel && HeatLevelAddr)
			{
				heatLevel = (int)(floorf(heatLevel) - floorf(MinHeatLevel) + 1) % (int)(floorf(MaxHeatLevel) - floorf(MinHeatLevel) + 1) + MinHeatLevel;

				injector::WriteMemory<float>(HeatLevelAddr, heatLevel - 0.005f, true); //Change it and leave .005 for make increment happen
			}

			while ((GetAsyncKeyState(hotkeyForceHeatLevel) & 0x8000) > 0) { Sleep(0); }
		}


		// Cop Lights
		if ((GetAsyncKeyState(hotkeyToggleCopLights) & 1)) // When pressed "Toggle Police Lights" key
		{
			copLightsEnabled = !copLightsEnabled;
			CIniReader iniReader("NFSCExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "CopLightsMode", copLightsEnabled);

			if (copLightsEnabled) // Enable cop lights - more proper method
			{
				injector::WriteMemory<float>(0x7cbed9, copLightsAmount, true); // Red Flashing Lights
				injector::WriteMemory<float>(0x7cbee1, copLightsAmount, true); // Blue Flashing Lights
				injector::WriteMemory<float>(0x7cbee9, copLightsAmount, true); // White Flashing Lights
			}
			else // Disable cop lights
			{
				injector::WriteMemory<float>(0x7cbed9, 0, true); // Red Flashing Lights
				injector::WriteMemory<float>(0x7cbee1, 0, true); // Blue Flashing Lights
				injector::WriteMemory<float>(0x7cbee9, 0, true); // White Flashing Lights
			}

			while ((GetAsyncKeyState(hotkeyToggleCopLights) & 0x8000) > 0) { Sleep(0); }
		}

		// Headlights
		if ((GetAsyncKeyState(hotkeyToggleHeadLights) & 1)) // When pressed "Toggle Head Lights" key
		{
			headLightsMode = (headLightsMode + 1) % 3; // 0, 1 or 2
			CIniReader iniReader("NFSCExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "HeadLightsMode", headLightsMode);

			switch (headLightsMode)
			{
				case 0:
					injector::WriteMemory<float>(0x7cbf96, 0, true); // Left HeadLight
					injector::WriteMemory<float>(0x7cbf77, 0, true); // Right HeadLight
					break;
				case 1:
					injector::WriteMemory<float>(0x7cbf96, LowBeamAmount, true); // Left HeadLight
					injector::WriteMemory<float>(0x7cbf77, LowBeamAmount, true); // Right HeadLight
					break;
				case 2: default:
					injector::WriteMemory<float>(0x7cbf96, HighBeamAmount, true); // Left HeadLight
					injector::WriteMemory<float>(0x7cbf77, HighBeamAmount, true); // Right HeadLight
					break;
			}

			while ((GetAsyncKeyState(hotkeyToggleHeadLights) & 0x8000) > 0) { Sleep(0); }
		}

		// Unlock Series Cars & Upgrades
		if ((GetAsyncKeyState(hotkeyUnlockSeriesCarsAndUpgrades) & 1)) //When pressed "Unlock Series Cars & Upgrades"
		{
			UnlockSeriesCarsAndUpgrades = !UnlockSeriesCarsAndUpgrades; // Toggle option
			CIniReader iniReader("NFSCExtraOptionsSettings.ini");
			iniReader.WriteInteger("Gameplay", "UnlockSeriesCarsAndUpgrades", UnlockSeriesCarsAndUpgrades);

			if (UnlockSeriesCarsAndUpgrades)
			{
				injector::WriteMemory<unsigned char>(0x49ECD2, 0xB0, true);
				injector::WriteMemory<unsigned char>(0x49ECD3, 0x01, true);
			}
			else
			{
				injector::WriteMemory<unsigned char>(0x49ECD2, 0x33, true);
				injector::WriteMemory<unsigned char>(0x49ECD3, 0xC0, true);
			}

			while ((GetAsyncKeyState(hotkeyUnlockSeriesCarsAndUpgrades) & 0x8000) > 0) { Sleep(0); }
		}

		// .hot Save And Load
		if ((GetAsyncKeyState(VK_LSHIFT) & 1)) // Save
		{
			while ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 0)
			{
				Sleep(0);
				if (GetAsyncKeyState(49) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x01, true); while ((GetAsyncKeyState(49) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(50) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x02, true); while ((GetAsyncKeyState(50) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(51) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x03, true); while ((GetAsyncKeyState(51) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(52) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x04, true); while ((GetAsyncKeyState(52) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(53) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x05, true); while ((GetAsyncKeyState(53) & 0x8000) > 0) Sleep(0); }
			}
		}

		if ((GetAsyncKeyState(VK_LCONTROL) & 1)) // Load
		{
			while ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) > 0)
			{
				Sleep(0);
				if (GetAsyncKeyState(49) & 1) { injector::WriteMemory<unsigned char>(0xb74bfc, 0x01, true); while ((GetAsyncKeyState(49) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(50) & 1) { injector::WriteMemory<unsigned char>(0xb74bfc, 0x02, true); while ((GetAsyncKeyState(50) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(51) & 1) { injector::WriteMemory<unsigned char>(0xb74bfc, 0x03, true); while ((GetAsyncKeyState(51) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(52) & 1) { injector::WriteMemory<unsigned char>(0xb74bfc, 0x04, true); while ((GetAsyncKeyState(52) & 0x8000) > 0) Sleep(0); }
				if (GetAsyncKeyState(53) & 1) { injector::WriteMemory<unsigned char>(0xb74bfc, 0x05, true); while ((GetAsyncKeyState(53) & 0x8000) > 0) Sleep(0); }
			}
		}

		// AutoDrive
		if ((GetAsyncKeyState(hotkeyAutoDrive) & 1))
		{
			if (AutoDriveAddr)
			{
				AutoDrive = !AutoDrive;
				injector::WriteMemory<bool>(AutoDriveAddr, AutoDrive, true);
			}

			while ((GetAsyncKeyState(hotkeyAutoDrive) & 0x8000) > 0) { Sleep(0); }
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

