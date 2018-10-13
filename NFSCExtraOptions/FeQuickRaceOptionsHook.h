#include "stdio.h"
#include <Windows.h>
#include <cstdint>

#define Tweak_TrafficAllowInRace 0xA61290
#define NoCatchUpThing 0x4A59C5
#define gTheDALManager 0xA8AD30
#define FEQuickRaceOptions_sInstance 0xBBAA54
DWORD j_malloc = 0x6A1560;

signed int(__thiscall *FeQuickRaceOptions_CreateWidget)(DWORD *_this, signed int a2, unsigned __int8 *a3) = (signed int(__thiscall*)(DWORD*, signed int, unsigned __int8*))0x84bdd0;
int(__thiscall *FeQuickRaceOptions_RefreshWidgets)(DWORD *_this) = (int(__thiscall*)(DWORD*))0x84B6F0;
int(__thiscall *DALManager_GetInt)(DWORD *_this, int a2, int *a3, int a4, int a5, int a6) = (int(__thiscall*)(DWORD*, int, int*, int, int, int))0x4A0490;
int(__thiscall *DALManager_SetInt)(DWORD *_this, int a2, int a3, int a4, int a5, int a6) = (int(__thiscall*)(DWORD*, int, int, int, int, int))0x4A04E0;
int(__thiscall *VectorScroller_SetVisibleItemsCount)(DWORD *_this, DWORD *a2) = (int(__thiscall*)(DWORD*, DWORD*))0x5766B0;
int(__thiscall *FEWidget_SetTitle)(DWORD *_this, DWORD *a2) = (int(__thiscall*)(DWORD*, DWORD*))0x592C90;
int(__thiscall *FEQuickRaceStateManager_Start)(DWORD *_this) = (int(__thiscall*)(DWORD*))0x845E10;
int(__thiscall *FEStateManager_SetInitialOption)(DWORD *_this) = (int(__thiscall*)(DWORD*))0x59B2E0;
DWORD*(__thiscall *FEObject_Clone)(DWORD *_this, bool a2) = (DWORD*(__thiscall*)(DWORD*, bool))0x5FEB80;
DWORD*(__cdecl *FE_Object_FindObject)(const char *pkg_name, unsigned int obj_hash) = (DWORD*(__cdecl*)(const char*, unsigned int))0x5A0250;
unsigned int(__cdecl *bStringHash)(const char *text) = (unsigned int(__cdecl*)(const char*))0x471050;

enum QROptions
{
	GameMode,
	RankedMode,
	Laps,
	CrewMember,
	TrafficLevel,
	AIOpponents,
	CatchUp,
	NOS,
	ShadowOption,
	Difficulty,
	HeatLevel
};

enum GameMode
{
	Default,
	Circuit,
	Sprint,
	CanyonSprint,
	Drag,
	Drift,
	CanyonDrift,
	Checkpoint,
	Speedtrap,
	CanyonDuel,
	PursuitTag,
	PursuitKnockout,
	Encounter,
	Challenge,
	RaceWars
};

int __fastcall FEQuickRaceOptions_SetupRaceHook(DWORD *_this, int _GameMode)
{
	DWORD *v1 = _this;
	unsigned char v3 = 1;

	_GameMode++; // To fix decreasing in setup function

	v3 = 1;
	FeQuickRaceOptions_CreateWidget(v1, QROptions::GameMode, &v3);

	if ((*(int*)NoCatchUpThing) == 0) // To fix a crash
	{
		v3 = 1;
		FeQuickRaceOptions_CreateWidget(v1, QROptions::RankedMode, &v3);

		v3 = 1;
		FeQuickRaceOptions_CreateWidget(v1, QROptions::ShadowOption, &v3);
	}

	v3 = 1;
	FeQuickRaceOptions_CreateWidget(v1, QROptions::Difficulty, &v3);

	v3 = 1;
	FeQuickRaceOptions_CreateWidget(v1, QROptions::CrewMember, &v3);
	
	if (_GameMode != GameMode::Sprint
		&& _GameMode != GameMode::CanyonSprint
		&& _GameMode != GameMode::CanyonDrift
		&& _GameMode != GameMode::CanyonDuel
		&& _GameMode != GameMode::Checkpoint
		&& _GameMode != GameMode::Speedtrap
		&& _GameMode != GameMode::Encounter)
	{
		v3 = 1;
		FeQuickRaceOptions_CreateWidget(v1, QROptions::Laps, &v3);

		if (_GameMode == GameMode::PursuitTag)
		{
			DWORD *OptionStringPtr = (DWORD *)v1[94];
			DWORD TimeStringHash = 0xBB194258; // Time (Minutes)
			FEWidget_SetTitle(OptionStringPtr, &TimeStringHash);
		}
	}

	if (*(bool*)Tweak_TrafficAllowInRace)
	{
		v3 = 1;
		FeQuickRaceOptions_CreateWidget(v1, QROptions::TrafficLevel, &v3);
	}

	if (_GameMode != GameMode::PursuitTag
		&& _GameMode != GameMode::PursuitKnockout)
	{
		v3 = 1;
		FeQuickRaceOptions_CreateWidget(v1, QROptions::HeatLevel, &v3);
	}

	
	v3 = 1;
	FeQuickRaceOptions_CreateWidget(v1, QROptions::AIOpponents, &v3);

	if ((*(int*)NoCatchUpThing) != 0)
	{
		v3 = 1;
		FeQuickRaceOptions_CreateWidget(v1, QROptions::CatchUp, &v3);
	}
	
	v3 = 1;
	FeQuickRaceOptions_CreateWidget(v1, QROptions::NOS, &v3);

	_GameMode--; // Decrease it again, to prevent any further issues

	return 1;
}

DWORD FeQuickRaceOptions_SetupCodeCaveExit = 0x85E691;

void __declspec(naked) FeQuickRaceOptions_SetupCodeCave()
{
	_asm
	{
		mov edx,eax
		mov ecx,esi
		call FEQuickRaceOptions_SetupRaceHook
		jmp FeQuickRaceOptions_SetupCodeCaveExit
	}
}

DWORD HeatLevelOptionCodeCaveExit_NoMenuOption = 0x84C40D;
DWORD HeatLevelOptionCodeCaveExit_CreateWidgetOption = 0x84C35C;
DWORD CreateQROptionLevelToggleFEWidget = 0x84B550;

void __declspec(naked) HeatLevelOptionCodeCave()
{
	_asm
	{
		push 0x84
		call j_malloc
		add esp, 4
		mov [esp + 0x34], eax
		test eax, eax
		mov dword ptr [esp + 0x40], 0x18
		jz NoNewMem
		push 1
		push 0
		push 0
		push 0x8CD8D487 // High
		push 0x31BFE5C8 // Medium
		push 0x70DFDA39 // Low
		push 0x8CDC3937 // None
		push 4			// Number of options
		push 5095		// 5089 = DALOptions::SetCopDensity, 5095 = DALOptions::SetCopsOn
		lea ecx, [esp + 0x3C]
		push ecx
		mov ecx, eax
		mov dword ptr [esp + 0x40], 0x2839A51E // Cops (No Heat Level string in Carbon)
		call CreateQROptionLevelToggleFEWidget
		jmp OptionThings

		NoNewMem :
			xor eax, eax

		OptionThings :
			mov ecx, [esp + 0x4C]
			mov [esi + 0x180], eax
			movzx ecx, byte ptr [ecx]
			mov edx, [eax]
			push ecx
			or ebx, 0xFFFFFFFF
			mov ecx, eax
			mov[ esp + 0x44], ebx
			call dword ptr [edx + 0x24]
			push 0x50
			call j_malloc
			mov edi, eax
			add esp, 4
			mov [esp + 0x4C], edi
			test edi, edi
			mov dword ptr [esp + 0x40], 19
			jz JzJump
			mov edx, [esi + 0x180]
			push edx
			push 0x9E94A4 // OPTION_11
			jmp HeatLevelOptionCodeCaveExit_CreateWidgetOption

		JzJump:
			jmp HeatLevelOptionCodeCaveExit_NoMenuOption
	}
}