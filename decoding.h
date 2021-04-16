#pragma once
#include "fose/fose/GameMenus.h"
#include "fose/GameInterface.h"
#include "fose/GameForms.h"
#include "fose/GameOSDepend.h"
#include "fose/GameExtraData.h"
#include "fose/GameObjects.h"
#include "fose/GameRTTI.h"
#include "netimmerse.h"

#define GameHeapAlloc(size) ThisCall<void*>(0x86B930, (void*)0x1090A78, size)
#define GameHeapFree(ptr) ThisCall<void*>(0x86BA60, (void*)0x1090A78, ptr)
#define FLDZ_RET 0xCCC3EED9

NiNode* (__cdecl* GetSubNodeByName)(NiAVObject*, char*) = ((NiNode * (__cdecl*)(NiAVObject*, char*))(0x470720));
TileMenu** g_tileMenuArray = NULL;
class AnimSequenceBase;
class BSAnimGroupSequence;
extern PlayerCharacter* g_thePlayer;

enum
{
	kAddr_DoRemoveObstacle = 0x5E9AD0,
	kAddr_EnableNavMesh = 0x6C1130,
	kAddr_DisableNavMesh = 0x6C1150,
	kAddr_EquipItem = 0x7198E0,
	kAddr_TurnToFaceObject = 0x703430,
	kAddr_TurnToAngle = 0x703490,
	kAddr_TileGetFloat = 0xBECF40,
	kAddr_TileSetFloat = 0xBEE190,
	kAddr_TileSetString = 0xBF11A0,
	kAddr_ReadXML = 0xBF37B0,
	kAddr_GetItemHealthPerc = 0x47CF30,
	kAddr_GetMaxCarryWeightPerkModified = 0x6F6BC0,
	kAddr_TileFromTemplate = 0xBFD250,
};

enum MovementFlags
{
	kForward = 0x1,
	kBackward = 0x2,
	kLeft = 0x4,
	kRight = 0x8,
	kTurnLeft = 0x10,
	kTurnRight = 0x20,
	kWalking = 0x100,
	kRunning = 0x200,
	kSneaking = 0x400,
	kSwimming = 0x800,

	kNE = kForward | kRight,
	kSE = kBackward | kRight,
	kSW = kBackward | kLeft,
	kNW = kForward | kLeft,
};

struct NiPoint3
{
	float x, y, z;

	void Scale(float scale) {
		x *= scale;
		y *= scale;
		z *= scale;
	};
	void Init(NiPoint3* point)
	{
		x = point->x;
		y = point->y;
		z = point->z;
	};

	NiPoint3() : x(0.f), y(0.f), z(0.f)
	{
	};

	NiPoint3(const float x, const float y, const float z) : x(x), y(y), z(z)
	{
	};

};
class TES
{
public:
	TES();
	~TES();

	virtual void		Fn_00(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);

	UInt32								unk04;				// 04
	UInt32* gridCellArray;		// 08
	NiNode* niNode0C;			// 0C
	NiNode* niNode10;			// 10
	NiNode* niNode14;			// 14
	UInt32* tempNodeMgr;		// 18
	UInt32* directionalLight;	// 1C
	void* ptr20;				// 20
	SInt32								extGridX;			// 24
	SInt32								extGridY;			// 28
	SInt32								extCoordX;			// 2C
	SInt32								extCoordY;			// 30
	TESObjectCELL* currentInterior;	// 34
	TESObjectCELL** interiorsBuffer;	// 38
	TESObjectCELL** exteriorsBuffer;	// 3C
	UInt32								unk40[9];			// 40
	UInt32* waterManager;		// 64
	UInt32* sky;				// 68
	tList<void>	activeIMODs;		// 6C
	UInt32								unk74[3];			// 74
	float								flt80;				// 80	Abs X distance from centre of grid.
	float								flt84;				// 84	Abs Y distance from centre of grid.
	TESWorldSpace* currentWrldspc;	// 88
	tList<UInt32>						list8C;				// 8C
	tList<UInt32>						list94;				// 94
	tList<UInt32>						list9C;				// 9C
	UInt32* unkA4;				// A4
	NiSourceTexture* unkA8;				// A8
	UInt32* unkAC;				// AC
	void* ptrB0;				// B0
	UInt32								unkB4[2];			// B4
	NavMeshInfoMap* navMeshInfoMap;	// BC
	UInt32* areaBound;			// C0

	__forceinline bool GetTerrainHeight(float* posXY, float* result)
	{
		return ThisCall<bool>(0x435870, this, posXY, result);
	}
};
STATIC_ASSERT(sizeof(TES) == 0xC4);
struct EntryPointConditionInfo
{
	const char* entryPoint;	// 00
	UInt8			numTabs;		// 04
	UInt8			pad01[3];		// 05
	const char** runOn;		// 08
	UInt8			byte0C;			// 0C
	UInt8			pad0D[3];		// 0D
};

class Tile3D;
class NiControllerSequence;

class HUDMainMenu : public Menu
{
public:
	HUDMainMenu();
	~HUDMainMenu();

	struct QueuedMessage
	{
		char	msgText[0x204];			// 000
		char	iconPate[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C
	};


	enum VisibilityFlags
	{
		kActionPoints = 0x1,
		kHitPoints = 0x2,
		kRadiationMeter = 0x4,
		kEnemyHealth = 0x8,
		kQuestReminder = 0x10,
		kRegionLocation = 0x20,
		kReticleCenter = 0x40,
		kSneakMeter = 0x80,
		kMessages = 0x100,
		kInfo = 0x200,
		kSubtibles = 0x400,
		kHotkeys = 0x800,
		kXpMeter = 0x1000,
		kBreathMeter = 0x2000,
		kExplosivePositioning = 0x4000,
		kCrippledLimbIndicator = 0x8000,
	};

	struct SubtitleData;

	UInt32 unk028;
	TileImage* hitPointsMeter;
	TileText* hitPointsJustifyRightText;
	TileRect* hitPoints_CompassWindow_IconGroup034;
	TileRect* hitPoints_CompassWindow_IconGroup038;
	TileRect* hitPoints_CompassWindow_IconGroup03C;
	TileImage* hitPoints_CompassWindow;
	TileImage* actionPoints_Meter044;
	TileText* actionPoints_JustifyRightText048;
	TileText* actionPoints_JustifyRightText04C;
	TileImage* actionPoints_Meter050;
	TileImage* actionPoints_MeterBackground;
	TileText* actionPoints_JustifyRightText058;
	TileRect* questReminder_QuestStages;
	TileRect* questReminder_QuestAdded;
	TileText* regionLocation_JustifyLeftText064;
	TileText* regionLocation_JustifyLeftText068;
	TileImage* raditionMeter_RadiationBracket;
	TileImage* raditionMeter_RadiationPointer;
	TileText* raditionMeter_RadiationTextValue;
	TileText* raditionMeter_RadiationText;
	TileImage* enemyHealth_EnemyHealthBracket;
	TileImage* enemyHealth_Meter;
	TileText* enemyHealth_JustifyCenterText;
	TileText* sneakLabel;
	TileImage* messages_messageIcon;
	TileText* messages_JustifyLeftText;
	TileImage* messages_MessageBracket;
	TileText* tile098;
	TileRect* tileTakePrompt;
	TileText* tile0A0;
	TileImage* tile0A4;
	TileText* itemName;
	TileText* tileLockedStr;
	TileText* tileEmptyContainerStr;
	TileText* tilePickupWeightStr;
	TileText* tilePickupWG;
	TileText* tilePickupValueStr;
	TileText* tilePickupVAL;
	TileImage* tilePickupBorder;
	TileRect* hotkeys_hotkeySelector;
	TileText* hotkeys_JustifyCenterText;
	TileImage* hitPoints_leftBracket;
	TileImage* actionPoints_rightBracket;
	TileImage* xpMeter_XPBracket;
	TileText* xpMeter_XPAmount;
	TileText* xpMeter_XPLabel;
	TileImage* xpMeter_XPPointer;
	TileText* xpMeter_XPLastLevel;
	TileText* xpMeter_XPNextLevel;
	TileText* xpMeter_XPLevelUp;
	TileImage* reticleCenter_ReticleCenter;
	TileImage* crippledFace;
	TileImage* crippleHead;
	TileImage* crippledTorso;
	TileImage* crippledLeftArm;
	TileImage* crippledRightArm;
	TileImage* crippledLeftLeg;
	TileImage* crippledRightLeg;
	TileRect* actionPoints;
	TileRect* hitPoints;
	TileRect* radiationMeter;
	TileRect* enemyHealth;
	TileRect* questReminder;
	TileRect* regionLocation;
	TileRect* reticleCenter;
	TileRect* sneakMeter;
	TileRect* messages;
	TileRect* info;
	TileRect* subtibles;
	TileRect* hotkeys;
	TileRect* xpMeter;
	Tile3D* breathMeter;
	TileRect* Explosive_positioning;
	TileRect* crippledLimbIndicator;
	TileImage* cndArrows;
	UInt32 unk158;							// 158
	float flt15C;							// 15C
	tList<QueuedMessage> queuedMessages;	// 160
	UInt32 currMsgKey;						// 168
	SubtitleData* subtitlesArr[4];			// 16C
	char* subtitleString;					// 17C
	UInt32 unk180[2];						// 180
	TESObjectREFR* crosshairRef;			// 188
	UInt32 visibilityFlags;					// 18C
	UInt32 visibilityOverrides;				// 190
	UInt32 unk194;							// 194
	TileRect* hotkeys_HotkeySelector;		// 198
	TileRect* hotkeys_HotkeySelector_Item0;	// 19C
	UInt32 unk1D0;							// 1A0
	TileRect* hotkeys_HotkeySelector_Item2;	// 1A4
	TileRect* hotkeys_HotkeySelector_Item3;	// 1A8
	TileRect* hotkeys_HotkeySelector_Item4;	// 1AC
	TileRect* hotkeys_HotkeySelector_Item5;	// 1B0
	TileRect* hotkeys_HotkeySelector_Item6;	// 1B4
	TileRect* hotkeys_HotkeySelector_Item7;	// 1B8
	UInt32 unk1BC[4];						// 1BC
	UInt8 isUsingScope;						// 1CC
	UInt8 byte1CD;							// 1CD
	UInt8 byte1CE;							// 1CE
	UInt8 byte1CF;							// 1CF
	NiControllerSequence* niContSeq;
	UInt8 byte204;
	UInt8 autoDisplayObjectives;
	UInt8 pad206[2];
	UInt32 unk208;
	UInt32 unk20C;
	UInt32 unk210;
	UInt32 unk214;
	UInt32 maxCompassAngle;
	Actor* healthTarget;
	UInt32 unk220;
	void* unk224[12];
	UInt32 unk244;
	UInt32 unk248[4];
	UInt32 list258[2];
	UInt8 byte260;
	UInt8 byte261;
	UInt8 pad262[2];
	static HUDMainMenu* GetSingleton() { return *(HUDMainMenu * *)0x10762B4; }
};
STATIC_ASSERT(sizeof(HUDMainMenu) == 0x244);

// 08
struct TypeSignature
{
	char	signature[8];
};

class ImageSpaceModifierInstanceForm;
class ImageSpaceModifierInstanceRB;

struct VATSCameraData
{
	tList<void>						targetsList;	// 00
	UInt32							mode;			// 08
	UInt32							unk0C;			// 0C
	BGSCameraShot*					camShot;		// 10
	float							flt14;			// 14
	float							flt18;			// 18
	UInt32							unk1C;			// 1C
	UInt32							unk20;			// 20
	UInt32							unk24;			// 24
	ImageSpaceModifierInstanceForm* isModInstForm;	// 28
	ImageSpaceModifierInstanceRB* isModInstRB;		// 2C
	UInt32							unk30;			// 30
	/*NiObject*/void*				object34;		// 34
	UInt8							byte38;			// 38
	UInt8							pad39[3];		// 39
	UInt32							unk3C;			// 3C
	UInt32							unk40;			// 40
	UInt32							unk44;			// 44
	void Free() { ThisCall(0x7CF2A0, this); }
};
STATIC_ASSERT(sizeof(VATSCameraData) == 0x48);

__declspec(naked) ExtraContainerChanges::EntryDataList* TESObjectREFR::GetContainerChangesList()
{
	__asm
	{
		push	kExtraData_ContainerChanges
		add		ecx, 0x40
		call	BaseExtraList::GetByType
		test	eax, eax
		jz		done
		mov		eax, [eax + 0xC]
		test	eax, eax
		jz		done
		mov		eax, [eax]
		done:
		retn
	}
}

__declspec(naked) ContChangesEntry* ExtraContainerChanges::EntryDataList::FindForItem(TESForm *item)
{
	__asm
	{
		mov		edx, [esp+4]
	listIter:
		mov		eax, [ecx]
		test	eax, eax
		jz		listNext
		cmp		[eax+8], edx
		jz		done
	listNext:
		mov		ecx, [ecx+4]
		test	ecx, ecx
		jnz		listIter
		xor		eax, eax
	done:
		retn	4
	}
}

__declspec(naked) void Actor::EquipItemAlt(void *itemEntry, bool noUnequip, bool noMessage)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		push	ecx
		mov		[ebp-4], ecx
		mov		ecx, [ebp+8]
		mov		eax, [ecx+8]
		test	eax, eax
		jz		done
		mov		dl, [eax+4]
		cmp		dl, kFormType_Armor
		jz		countOne
		cmp		dl, kFormType_Book
		jz		countOne
		cmp		dl, kFormType_AlchemyItem
		jz		countOne
		cmp		dl, kFormType_Ammo
		jz		countMax
		cmp		dl, kFormType_Weapon
		jnz		done
		cmp		byte ptr [eax+0xF4], 0xA
		jb		countOne
	countMax:
		mov		edx, [ecx+4]
		jmp		doEquip
	countOne:
		mov		edx, 1
	doEquip:
		movzx	ecx, byte ptr [ebp+0x10]
		push	ecx
		movzx	ecx, byte ptr [ebp+0xC]
		push	ecx
		push	1
		mov		ecx, [ebp+8]
		mov		ecx, [ecx]
		test	ecx, ecx
		jz		noXData
		mov		ecx, [ecx]
	noXData:
		push	ecx
		push	edx
		push	eax
		mov		ecx, [ebp-4]
		mov		eax, kAddr_EquipItem
		call	eax
	done:
		mov		esp, ebp
		pop		ebp
		retn	0xC
	}
}

__declspec(naked) float ExtraContainerChanges::Data::GetInventoryWeight()
{
	static const UInt32 kAddr_GetInventoryWeight = 0x0;
	__asm
	{
		mov		dword ptr[ecx + 8], 0xBF800000
		mov		eax, kAddr_GetInventoryWeight
		call	eax
		retn
	}
}

__declspec(naked) void Actor::TurnToFaceObject(TESObjectREFR *target)
{
	__asm
	{
		mov		eax, [esp+4]
		push	0
		
		push	dword ptr [eax+0x34]
		push	dword ptr [eax+0x30]
		push	dword ptr [eax+0x2C]
		mov		eax, kAddr_TurnToFaceObject
		call	eax
		retn	4
	}
}

__declspec(naked) float Tile::GetValueFloat(UInt32 id)
{
	static const UInt32 procAddr = kAddr_TileGetFloat;
	__asm	jmp		procAddr
}

__declspec(naked) void Tile::FakeClick()
{
	__asm
	{
		push	esi
		mov		esi, ecx
		push	1
		push	0x3F800000
		push	kTileValue_clicked
		mov		eax, kAddr_TileSetFloat
		call	eax
		push	1
		push	0
		push	kTileValue_clicked
		mov		ecx, esi
		mov		eax, kAddr_TileSetFloat
		call	eax
		pop		esi
		retn
	}
}

__declspec(naked) Tile* Tile::ReadXML(const char* xmlPath)
{
	static const UInt32 procAddr = kAddr_ReadXML;
	__asm	jmp		procAddr
}


void ConsoleManager::AppendToSentHistory(const char* str)
{
	String* string = (String*)GameHeapAlloc(sizeof(String));
	string->Init(0);
	string->Set(str);

	TextNode* textNode = (TextNode*)GameHeapAlloc(sizeof(TextNode));
	textNode->text.Init(0);
	textNode->text.Set(str);

	this->inputHistory.Append(textNode);
}

ConsoleManager::TextList* ConsoleManager::TextList::Append(ConsoleManager::TextNode* append)
{
	append->prev = 0;
	append->next = this->first;
	if (this->first)
	{
		this->first->prev = append;
	}
	else
	{
		this->last = append;
	}
	this->first = append;
	++this->count;
	return this;
}

enum KeyState
{
	isHeld = 0x0,
	isPressed = 0x1,
	isDepressed = 0x2,
	isChanged = 0x3,
};

enum ControlCode
{
	Forward = 0x0,
	Backward = 0x1,
	Left = 0x2,
	Right = 0x3,
	Attack = 0x4,
	Activate = 0x5,
	Aim = 0x6,
	ReadyItem = 0x7,
	Crouch = 0x8,
	Run = 0x9,
	AlwaysRun = 0xA,
	AutoMove = 0xB,
	Jump = 0xC,
	TogglePOV = 0xD,
	MenuMode = 0xE,
	Rest = 0xF,
	VATS_ = 0x10,
	Hotkey1 = 0x11,
	AmmoSwap = 0x12,
	Hotkey3 = 0x13,
	Hotkey4 = 0x14,
	Hotkey5 = 0x15,
	Hotkey6 = 0x16,
	Hotkey7 = 0x17,
	Hotkey8 = 0x18,
	QuickSave = 0x19,
	QuickLoad = 0x1A,
	Grab = 0x1B,
	Escape_ = 0x1C,
	Console = 0x1D,
	Screenshot = 0x1E,
};

bool OSInputGlobals::GetControlState(ControlCode code, KeyState state)
{
	return ThisCall<bool>(0xBE97A0, this, code, state);
}

void OSInputGlobals::SetControlHeld(ControlCode code)
{
	ThisCall(0xBE9590, this, code);
}


VATSCameraData* g_VATSCameraData = (VATSCameraData*)0x108D098;
void(__thiscall* DestroyVATSCamStructs)(VATSCameraData* cam, int a2, int a3) = (void(__thiscall*)(VATSCameraData*, int, int))0x7D0710;

void StopVATSCam()
{
	// removes the hud prompt of the VATS target for some reason
	ThisCall(0x7CFB90, g_VATSCameraData, 0);

	DestroyVATSCamStructs(g_VATSCameraData, 0, 1);
	g_VATSCameraData->Free();
	*(byte*)0x108D018 = 1;
}

bool IsVATSKillCamActive()
{
	// g_vatsCamStruct->mode
	return *(int*)(0x108D0A0) == 4;
}

class TESTopicInfo;
class DialogMenu : public Menu			// 1009
{
public:
	DialogMenu();
	~DialogMenu();

	int stage;
	int field_2C;
	TileImage* tile030;		// 030
	TileText* tile034;		// 034
	TileText* tile038;		// 038
	TileImage* tile03C;		// 03C
	ListBox<int>		topicList;		// 040
	void* unk070;		// 070
	UInt32				unk074;			// 074
	TESTopicInfo* info078;		// 078
	UInt32				unk07C;			// 07C
	TESObjectREFR* partnerRef;	// 080
	float unk084[2];			// 84
	void* unk08C;				// 8C
	void* unk090;				// 90
	TESTopicInfo* infos094[16];	// 94
	void* unk0D4;				// D4
	UInt32 unk0D8[3];			// D8
	TESTopicInfo* infos0E4[8];	// E4
	int unk104;					// 104
	int field_108;				// 108
	int lastMenuClickTime;		// 10C
	TESTopicInfo* infos110[6];	// 110
	float unk128;				// 128
	void* unk12C;				// 12C
	char byte130;				// 130
	char byte131;				// 131
	char byte132;				// 132
	char byte133;				// 133
	UInt32 unk134;				// 134
	char isBarterMenuShown;		// 138
	char byte139;				// 139
	char byte13A;				// 13A
	char byte13B;				// 13B

	bool IsShowingText();
};

bool DialogMenu::IsShowingText()
{
	return tile->GetValueFloat(*(UInt32*)0x1076128); // g_dialogMenu_TraitShowingText
}


double Actor::GetHealthPercent()
{
	return ((double(__thiscall*)(Actor * actor))(0x6F65E0))(this);
}

bool(__stdcall* TESBoundObject__Activate)(TESBoundObject* obj, Actor* actor, char a3, int a4, int a5) = (bool(__stdcall*)(TESBoundObject*, Actor*, char, int, int))0x4B2430;
TESForm* (__cdecl* GetDefaultObject)(int id) = (TESForm * (__cdecl*)(int id))0x508E40;

enum Scancodes
{
	_Escape = 0x1,
	One = 0x2,
	Two = 0x3,
	Three = 0x4,
	Four = 0x5,
	Five = 0x6,
	Six = 0x7,
	Seven = 0x8,
	Eight = 0x9,
	Nine = 0xA,
	Zero = 0xB,
	Minus = 0xC,
	Equals = 0xD,
	Backspace = 0xE,
	Tab = 0xF,
	Q = 0x10,
	W = 0x11,
	E = 0x12,
	R = 0x13,
	T = 0x14,
	Y = 0x15,
	U = 0x16,
	I = 0x17,
	O = 0x18,
	P = 0x19,
	LeftBracket = 0x1A,
	RightBracket = 0x1B,
	Enter = 0x1C,
	LeftControl = 0x1D,
	A = 0x1E,
	S = 0x1F,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	SemiColon = 0x27,
	Apostrophe = 0x28,
	Tilde = 0x29,
	LeftShift = 0x2A,
	BackSlash = 0x2B,
	Z = 0x2C,
	X = 0x2D,
	C = 0x2E,
	V = 0x2F,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	Comma = 0x33,
	Period = 0x34,
	ForwardSlash = 0x35,
	RightShift = 0x36,
	NumStar = 0x37,
	LeftAlt = 0x38,
	SpaceBar = 0x39,
	CapsLock = 0x3A,
	F1 = 0x3B,
	F2 = 0x3C,
	F3 = 0x3D,
	F4 = 0x3E,
	F5 = 0x3F,
	F6 = 0x40,
	F7 = 0x41,
	F8 = 0x42,
	F9 = 0x43,
	F10 = 0x44,
	NumLock = 0x45,
	ScrollLock = 0x46,
	Num7 = 0x47,
	Num8 = 0x48,
	Num9 = 0x49,
	NumMinus = 0x4A,
	Num4 = 0x4B,
	Num5 = 0x4C,
	Num6 = 0x4D,
	NumPlus = 0x4E,
	Num1 = 0x4F,
	Num2 = 0x50,
	Num3 = 0x51,
	Num0 = 0x52,
	NumPeriod = 0x53,
	F11 = 0x57,
	F12 = 0x58,
	NumEnter = 0x9C,
	RightControl = 0x9D,
	NumSlash = 0xB5,
	PrintScrn = 0xB7,
	RightAlt = 0xB8,
	Home = 0xC7,
	UpArrow = 0xC8,
	PageUp = 0xC9,
	LeftArrow = 0xCB,
	RightArrow = 0xCD,
	End_ = 0xCF,
	DownArrow = 0xD0,
	PageDown = 0xD1,
	Delete_ = 0xD3,
	LeftMouse = 0x100,
	RightMouse = 0x101,
	MiddleMouse = 0x102,
	MouseButton3 = 0x103,
	MouseButton4 = 0x104,
	MouseButton5 = 0x105,
	MouseButton6 = 0x106,
	MouseButton7 = 0x107,
	MouseWheelUp = 0x108,
	MouseWheelDown = 0x109,
};

struct TimeGlobal
{
	float unk0;
	float fpsLimit;
	float unk8;
	float secondsPassed;
	int msPassed;
	float unk14;
	byte isChangeTimeMultSlowly;
	byte unk19;
	byte unk1A;
	byte unk1B;
	float unk1C;
	float unk20;
	float unk24;
};

class Tile3D;
class BGSSaveLoadFileEntry;
struct StartMenuOption;
class StartMenu : public Menu
{
public:
	~StartMenu();
	StartMenu();

	enum StartMenuFlags
	{
		AreOptionsInitialised = 0x20,
	};

	UInt32 unk028[(0x1A0 - 0x28) >> 2];
	UInt32 flags;
	UInt32 unk1A4[(0x1D0 - 0x1A4) >> 2];
	static StartMenu* GetSingleton() { return *(StartMenu * *)0x10770AC; };
};
STATIC_ASSERT(sizeof(StartMenu) == 0x1D0);

// 10
struct StartMenuOption
{
	// which menus the option should be shown in
	enum WhichMenus
	{
		kMainMenu = 0x1,
		kPauseMenu = 0x2,
		kSettingsMenu = 0x4,
		kGameplayMenu = 0x8,
		kDisplayMenu = 0x10,
		kAudioMenu = 0x20,
		kControlsMenu = 0x40,
		kNewGameMenu = 0x80,
		kContinueGameMenu = 0x100,
		kQuitGameMenu = 0x2000,
	};

	UInt32* vtable;
	char* displayString;
	void (*callback)(void);	// 08
	UInt32 flags;

	static StartMenuOption* Create(char* str, void (*callback)(void), UInt32 flags)
	{
		StartMenuOption* option = (StartMenuOption*)GameHeapAlloc(sizeof(StartMenuOption));
		option->vtable = (UInt32*)kVtbl_StartMenuOption;
		option->displayString = str;
		option->callback = callback;
		option->flags = flags;

		return option;
	}
};

// 30
struct StartMenuUserOption : StartMenuOption
{
	enum UserOptionType
	{
		// kToggleCycles will show a right arrow at max value which will cycle it back to the lowest value
		kToggleCycles = 0,
		kToggleNoCycle = 1,
		kSlider = 2
	};

	const char* templateName;					// 10
	UInt32 currValue;							// 14
	UInt32 defaultValue;						// 18
	UserOptionType type;						// 1C
	UInt32 numOptions;							// 20
	UInt32 buttonWidth;							// 24
	const char** currValueName;					// 28
	void (*onSelection)(StartMenuUserOption*);	// 2C

	static StartMenuUserOption* Create(char* str, void (*callback)(StartMenuUserOption*), WhichMenus flags, int type, int numOptions, int buttonWidth, char* optionNames, ...)
	{
		StartMenuUserOption* option = (StartMenuUserOption*)GameHeapAlloc(sizeof(StartMenuUserOption));
		return ((StartMenuUserOption * (__cdecl*)(StartMenuUserOption * option, char* str, void (*callback)(StartMenuUserOption*), StartMenuUserOption::WhichMenus flags, int type, int numOptions, int buttonWidth, char* optionNames, ...))(0x67A6C0))(option, str, callback, flags, type, numOptions, buttonWidth, optionNames);
	}

	void UpdateVisibility() { ThisCall(0x67C780, StartMenu::GetSingleton(), this, NULL); };
};

BSSimpleArray<StartMenuOption>* g_settingsMenuOptions = (BSSimpleArray<StartMenuOption>*)0xF6B3B8;

union Color
{
	UInt32 rgba;
	struct
	{
		UInt8 a, b, g, r;
	};
};


class Setting;
struct SystemColorManager
{
	enum SystemColorNodes
	{
		kHUDMain = 0x1,
		kHUDAlt = 0x2,
		kTerminal = 0x3,
		kPipBoy = 0x4,
		kStartMenu = 0x5,
	};

	// 0C
	class SystemColor
	{
	public:
		SystemColor();
		~SystemColor();

		virtual void	Destructor(bool doFree);
		virtual UInt32	GetColor();
		virtual void	SetColor(UInt32 newColor);
		virtual bool	IsHard();
		virtual bool	IsSoft();

		String		traitName;

		void SetColorRGB(UInt32 r, UInt32 g, UInt32 b);
	};

	// 10
	class HardSystemColor : public SystemColor
	{
	public:
		HardSystemColor();
		~HardSystemColor();

		UInt32		color;		// 0C
	};

	// 10
	class SoftSystemColor : public SystemColor
	{
	public:
		SoftSystemColor();
		~SoftSystemColor();

		Setting* setting;	// 0C
	};

	DList<SystemColor>	sysColors;
	UInt32				unk0C;

	static SystemColorManager* GetSingleton() { return *(SystemColorManager * *)0x1075B2C; };
	int GetColor(SystemColorNodes node) { return ThisCall<int>(0x621640, this, node); };
	void SetColor(SystemColorNodes node, UInt32 color) { ThisCall(0x621690, this, node, color); };
};


__declspec(naked) void Tile::SetFloat(UInt32 id, float fltVal, bool bPropagate)
{
	static const UInt32 procAddr = kAddr_TileSetFloat;
	__asm	jmp		procAddr
}

__declspec(naked) void Tile::SetString(UInt32 id, const char* strVal, bool bPropagate)
{
	static const UInt32 procAddr = kAddr_TileSetString;
	__asm	jmp		procAddr
}

bool TESObjectWEAP::IsMeleeWeapon()
{
	return (this->eWeaponType <= EWeaponType::kWeapType_TwoHandMelee);
}

class EqualStringMatcher
{
	char* content;
public:
	EqualStringMatcher(char* str)
	{
		content = str;
	}
	bool Accept(char* item) { return strcmpi(item, content) == 0; };
};
class BSGameSound;
class BSWin32AudioListener;
class BSWin32Audio
{
public:
	BSWin32Audio();
	~BSWin32Audio();

	virtual void	Destroy(bool doFree);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual BSGameSound* CreateGameSound(const char* filePath);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);

	UInt32					unk004[3];		// 004
	BSWin32AudioListener* listener;		// 010
	UInt32					unk014[3];		// 014
	bool					(*unk20)(UInt32*, UInt32*, UInt32*, UInt32*);	// 020
	bool					(*unk24)(UInt32*, UInt32*, UInt32*, UInt32*);	// 024
	bool					(*unk28)(UInt32*);	// 028
	UInt32(*unk2C)(UInt32*, TESSound*, UInt32*);	// 02C
	void					(*unk30)(void);	// 030
	void					(*unk34)(void);	// 034

	static BSWin32Audio* GetSingleton() { return *(BSWin32Audio * *)0x11790C8; };
};

// 0C
struct Sound
{
	UInt32 unk00;
	UInt8 byte04;
	UInt8 pad05[3];
	UInt32 unk08;

	Sound() : unk00(0xFFFFFFFF), byte04(0), unk08(0) {}

	Sound(const char* soundPath, UInt32 flags)
	{
		ThisCall(0xBCFCD0, BSWin32Audio::GetSingleton(), this, soundPath, flags);
	}

	void Play()
	{
		ThisCall(0xBD00C0, this, 0);
	}

	Sound& operator= (Sound other)
	{
		unk00 = other.unk00;
		byte04 = other.byte04;
		unk08 = other.unk08;
	}
};

void PlayGameSound(const char* soundPath)
{
	Sound sound(soundPath, 0x121);
	sound.Play();
}

// 018
class ExtraSound : public BSExtraData
{
public:
	ExtraSound();
	virtual ~ExtraSound();

	Sound	sound; // 00C
};

// 2C
struct HackingText
{
	String str;
	Tile* tileText;
	int* unk0C;
	UInt32 displayRate;
	UInt32 flashOnDuration;
	UInt32 flashOffDuration;
	UInt32 nextDisplayTime;
	UInt32 nextBlinkTime;
	UInt32 currentlyDisplayedText;
	UInt8 flags28;
	UInt8 allOfLineIsDisplayed;
};
STATIC_ASSERT(sizeof(HackingText) == 0x2C);

class HackingMenu : public Menu
{
public:
	HackingMenu();
	~HackingMenu();

	enum Stages
	{
		kFailed = 3,
		kSuccess = 4
	};

	HackingText* lines[39];
	UInt32 unk0C4[7];
	HackingText bottomLine;
	Tile* tile10C[8];
	Sound UIHackingFanHumLP;
	Sound UIHackingPassGood;
	Sound UIHackingPassBad;
	Sound UIHackingCharScroll;
	Sound UIHackingCharEnter;
	UInt32 tileChildList168[3];
	UInt32 tileChildList174[3];
	tList<char> words;
	UInt32 tileChildList188[3];
	TESObjectREFR* targetBaseRef;
	TESObjectREFR* targetRef;
	UInt32 correctAnswer;
	UInt32 attemptsRemaining;
	UInt32 maxAttemptsRemaining;
	UInt32 wordsRemaining;
	UInt32 correctAnswerLength;
	UInt32* unk1B0;
	UInt32 topTextHeight;
	UInt32 topTextLineHeight;
	UInt32 highlightedCharacterXIndex;
	UInt32 activeTile;
	UInt32 stage;
	TileImage* tile1C8;
	UInt32 unk1CC;
	UInt32 transitionToComputersMenuTime;
	UInt32* unk1D4;
	UInt8 shouldNotHighlightWordOnHover;
	UInt8 hasAllowanceBeenReplenished;
	UInt8 byte1DA;
	UInt8 pad1DB;

	static HackingMenu* GetSingleton() { return *(HackingMenu * *)(0x11D95B8); }
};
STATIC_ASSERT(sizeof(HackingMenu) == 0x1DC);

enum FormID
{
	kCGTutorialSCRIPT = 0x59C86,
};

void DisableScript(Script* script)
{
	if (script)
	{
		script->info.dataLength = 0;
	}
}

struct NiPoint2
{
	float x, y;
};

// 230
class MapMenu : public Menu				// 1023
{
public:
	MapMenu();
	~MapMenu();

	enum MapMenuTabs
	{
		kLocalMap = 0x20,
		kWorldMap = 0x21,
		kQuests = 0x22,
		kMisc = 0x23,
		kRadio = 0x24,
	};

	TileText* tile028;		// 028	MM_MainRect\MM_HeadlineRect\MM_Headline_LocationInfo
	TileText* tile02C;		// 02C	MM_MainRect\MM_HeadlineRect\MM_Headline_TimeDateInfo
	TileImage* tile030;		// 030	MM_MainRect\MM_LocalMap_ClipWindow\MM_LocalMap_ParentImage
	TileImage* tile034;		// 034	MM_MainRect\MM_LocalMap_ClipWindow\MM_LocalMapCursor
	TileImage* tile038;		// 038	MM_MainRect\MM_WorldMap_ClipWindow\MM_WorldMap_ParentImage
	TileImage* tile03C;		// 03C	MM_MainRect\MM_WorldMap_ClipWindow\MM_WorldMapCursor
	TileRect* mapSelectionRectangle;		// 040	MM_MainRect\MM_Highlight_ClipWindow\MM_MapHighlightBox
	TileImage* tile044;		// 044	MM_MainRect\MM_QuestsList
	TileImage* tile048;		// 048	MM_MainRect\MM_NotesList
	TileImage* tile04C;		// 04C	MM_MainRect\MM_NotesList\MM_Notes_SelectedNoteHighlight
	TileImage* tile050;		// 050	MM_MainRect\MM_RadioStationList
	TileImage* tile054;		// 054	MM_MainRect\MM_ButtonRect\MM_ButtonA
	TileImage* tile058;		// 058	MM_MainRect\MM_ButtonRect\MM_ButtonX
	TileRect* tile05C;		// 05C	MM_MainRect\MM_DataRect
	TileImage* tile060;		// 060	MM_MainRect\MM_DataRect\MM_DataTextRect
	TileImage* tile064;		// 064	MM_MainRect\MM_DataRect\MM_QuestObjectivesList
	TileImage* tile068;		// 068	MM_MainRect\MM_WaveformRect\MM_Waveform
	TileRect* tile06C;		// 06C	MM_Tabline
	UInt8							currentTab;		// 080
	UInt8							pad081[3];		// 081
	TileImage* tilePlacedMarker; // 084
	UInt32 unk088;
	UInt8 isShowAllNotes;
	UInt8 byte08D;
	UInt8 byte08E;
	UInt8 byte08F;
	BGSNote* currentNote;
	UInt32 timeNoteViewed;
	UInt32 someSoundsList[4];
	BSSimpleArray<String>			arr0A8;			// 0A8
	Sound* maybeHolotapeSound;
	UInt8 isHolotapeVoicePlaying;
	UInt8 pad0BD;
	UInt8 pad0BE;
	UInt8 pad0BF;
	float holotapeTotalTime;
	UInt32 time0C4;
	float radioVolume;
	TESQuest* selectedQuest;
	BGSQuestObjective* currentObjective;
	TileImage* mapMarker;		// 0D4
	tList<TESObjectREFR>			mapMarkerList;	// 0D8
	tList<TESObjectREFR>			doorList;		// 0E0
	float							flt0E8;			// 0E8
	float							flt0EC;			// 0EC
	float							flt0F0;			// 0F0
	float							flt0F4;			// 0F4
	UInt32							unk0F8[4];		// 0F8
	TESObjectCELL* cell108;		// 108
	TESWorldSpace* wspc10C;		// 10C
	UInt32							unk110;			// 110
	TESObjectREFR* lastExtDoor;	// 114
	TESObjectREFR* selectedMarker;// 118
	TESObjectCELL* cell11C;		// 11C
	NiPoint2						clickStartPos;	// 120
	UInt32							unk128;			// 128
	bool							fogOfWar;		// 12C
	UInt8							pad12D[3];		// 12D
	ListBox<TESQuest>				questList;		// 130
	ListBox<BGSNote>				noteList;		// 160
	ListBox<TESObjectREFR>			radioRefList;	// 190
	ListBox<BGSQuestObjective>		objectiveList;	// 1C0
	BSSimpleArray<Tile>				arr1E0;			// 1E0

	static MapMenu* GetSingleton() { return *(MapMenu * *)0x1076BB8; };
};
STATIC_ASSERT(sizeof(MapMenu) == 0x1F0);


class NiTexturingProperty;
struct FontHeightData
{
	float		heightBase;
	float		heightwGap;
}
s_fontHeightDatas[90];

// 54
struct FontInfo
{
	struct BufferData
	{
		float			lineHeight;		// 0000
		UInt32			unk0004[73];	// 0004
		UInt32			unk0128[458];	// 0128
		float			baseHeight;		// 0850
		float			flt0854;		// 0854
		float			flt0858;		// 0858
	};

	struct ButtonIcon;

	UInt8						isLoaded;	// 00
	UInt8						pad01[3];	// 01
	char* filePath;	// 04
	UInt8						fontID;		// 08
	UInt8						pad09[3];	// 09
	NiTexturingProperty* texProp;	// 0C
	UInt32						unk10[7];	// 10
	float						flt2C;		// 2C
	float						flt30;		// 30
	UInt32						unk34;		// 34
	BufferData* bufferData;// 38
	UInt32						unk3C[2];	// 3C
	BSSimpleArray<ButtonIcon>	arr44;		// 44
};
STATIC_ASSERT(sizeof(FontInfo) == 0x54);


// 164 (24)
class FontManager
{
public:
	FontManager();
	~FontManager();

	FontInfo* fontInfos[8];		// 00
	UInt8			byte20;				// 20
	UInt8			pad21[3];			// 21
	FontInfo* extraFonts[80];	// 24

	//	outDims.x := width (pxl); outDims.y := height (pxl); outDims.z := numLines
	static FontManager* GetSingleton() { return *(FontManager * *)0x11796F8; };
};

struct FontTextReplaced;
void(__thiscall* Font__CheckForVariablesInText)(void*, const char* input, FontTextReplaced* a3) = (void(__thiscall*)(void*, const char*, FontTextReplaced*))0xBF6B80;
struct __declspec(align(4)) FontTextReplaced
{
	String str;
	UInt32 wrapWidth;
	UInt32 unk00C;
	UInt32 unk010;
	UInt32 unk014;
	UInt32 unk018;
	UInt8 byte1C;
	UInt8 gap1D[3];
	tList<void> list20;

	FontTextReplaced()
	{
		str.m_bufLen = 0;
		str.m_data = 0;
		str.m_dataLen = 0;
		wrapWidth = 0;
		unk00C = 0;
		unk010 = 0;
		unk014 = 0;
		unk018 = 0;
		byte1C = 0;
		list20.Init();
	};

	~FontTextReplaced()
	{
		str.Set(NULL);
		list20.RemoveAll();
	}

	void GetVariableEscapedText(const char* input) { Font__CheckForVariablesInText(FontManager::GetSingleton()->fontInfos[0], input, this); }
};

STATIC_ASSERT(sizeof(FontTextReplaced) == 0x28);

class BookMenu : public Menu
{
public:
	BookMenu();
	~BookMenu();
	TileImage* tile28;
	TileImage* tile2C;
	Actor* activator;
	TESObjectBOOK* bookObject;
	UInt32 unk38;
};

Tile* (__cdecl* GetMenuTile)(UInt32 id) = (Tile * (__cdecl*)(UInt32))0xBEAF00;
Menu* (__thiscall* TileList__GetMenu)(Tile*) = (Menu * (__thiscall*)(Tile*))0xBEAB90;
void(__thiscall* Menu__RegisterTile)(Menu*, Tile*, bool) = (void(__thiscall*)(Menu*, Tile*, bool))0xBFC570;
void(__thiscall* Menu__HideTitle)(Menu*, bool) = (void(__thiscall*)(Menu*, bool))0xBFD010;
void ShowBookMenu(const char* text)
{
	static TESObjectBOOK* dummyBook = NULL;
	if (!dummyBook)
	{
		// The flags of BookMenu->bookObject are checked in member functions, so use a dummy book that has the correct flags
		dummyBook = (TESObjectBOOK*)GameHeapAlloc(sizeof(TESObjectBOOK));
		dummyBook->flags = 0;
	}

	Tile* prevBookMenu = GetMenuTile(kMenuType_Book);
	if (prevBookMenu) prevBookMenu->Destroy(true);

	float newDepth = StdCall<float>(0xBFCB40);

	Tile* tile = InterfaceManager::GetSingleton()->menuRoot->ReadXML("Data\\Menus\\book_menu.xml");
	BookMenu* menu = (BookMenu*)TileList__GetMenu(tile);

	if (menu && menu->GetID() == kMenuType_Book)
	{
		menu->bookObject = dummyBook;
		Menu__RegisterTile(menu, tile, 0);

		if (menu->tile28 && menu->tile2C)
		{
			float stackingType = tile->GetValueFloat(kTileValue_stackingtype);
			if (stackingType == 6006.0 || stackingType == 102.0)
			{
				tile->SetFloat(kTileValue_depth, newDepth, 1);
			}

			Tile* root = menu->tile;

			// is scroll
			root->SetFloat(kTileValue_user0, 0);

			// can be taken
			root->SetFloat(kTileValue_user3, 0);

			// set description
			root->SetString(kTileValue_user2, text);

			//force page/scroll adjust
			root->SetFloat(kTileValue_user6, 0);

			Menu__HideTitle(menu, 0);
		}
	}
	else if (menu)
	{
		menu->Destructor(true);
	}
}

float (*GetWeaponDamage)(TESObjectWEAP* weapon, float condition) = (float (*)(TESObjectWEAP*, float))0x5843D0;
float(__cdecl* ScaleArmorDTDRByCondition)(UInt16 dtDR, float condition) = (float(__cdecl*)(UInt16, float))0x582720;
float GetPlayerWeaponDamage()
{
	float equippedDamage = 0;

	ContChangesEntry* entry = (ContChangesEntry*)g_thePlayer->baseProcess->GetWeaponInfo();
	if (entry)
	{
		TESObjectWEAP* weap = (TESObjectWEAP*)entry->type;
		float condition = entry->GetItemHealthPerc() / 100.0F;

		equippedDamage = GetWeaponDamage(weap, condition);
	}

	return equippedDamage;
}

__declspec(naked) float ExtraContainerChanges::EntryData::GetItemHealthPerc(bool arg1)
{
	static const UInt32 procAddr = kAddr_GetItemHealthPerc;
	__asm	jmp		procAddr
}

ExtraDataList* ExtraContainerChanges::EntryData::GetEquippedExtra()
{
	if (extendData)
	{
		ExtraDataList* xData;
		ListNode<ExtraDataList>* xdlIter = extendData->Head();
		do
		{
			xData = xdlIter->data;
			if (xData && xData->HasType(kExtraData_Worn))
				return xData;
		} while (xdlIter = xdlIter->next);
	}
	return NULL;
}

class BSGameSound;
class BSWin32AudioListener;
class BSAudioManagerThread;

// 254
class BSSoundInfo
{
public:
	BSSoundInfo();
	~BSSoundInfo();

	UInt32			unk000[72];		// 000
	const char* filePath;		// 120
	UInt32			unk124[76];		// 124
};

// 188
class BSAudioManager
{
public:
	BSAudioManager();
	~BSAudioManager();

	enum Volumes
	{
		kMaster = 0,
		kFoot,
		kVoice,
		kEffects,
		kMusic,
		kRadio,
		kVATSCamera,
	};

	virtual void				Destroy(bool doFree);

	struct AudioManagerStruct
	{
		UInt32 type;
		UInt32 unk04;
		UInt32 unk08;
		AudioManagerStruct* ptr0C;
		UInt32 unk10;
		NiPoint3 pos;
	};

	struct UnkC
	{
		UInt32 ptr00;
		UInt32 unk04;
		UInt32 count08;
	};

	struct Unk24
	{
		UInt32 count00;
		UInt8 isInitialized;
		UInt8 gap04[3];
		AudioManagerStruct* ptr08;
		UInt32 time0C;
	};

	enum AudioFlags
	{
		kAudioFlags_2D = 0x1,
		kAudioFlags_3D = 0x2,
		kAudioFlags_UseMissingVoiceAssetIfMissing = 0x4,
		kAudioFlags8 = 0x8,
		kAudioFlags_Loop = 0x10,
		kAudioFlags20 = 0x20,
		kAudioFlags_RandomFrequencyShift = 0x40,
		kAudioFlags80 = 0x80,
		kAudioFlags100 = 0x100,
		kAudioFlags800 = 0x800,
		kAudioFlagsMaybeUnderwater = 0x2000,
		kAudioFlags4000 = 0x4000,
		kAudioFlags10000 = 0x10000,
		kAudioFlags20000 = 0x20000,
		kAudioFlags40000 = 0x40000,
		kAudioFlags_Radio100000 = 0x100000,
		kAudioFlags200000 = 0x200000,
		kAudioFlags_Radio400000 = 0x400000,
		kAudioFlags_Modulated = 0x80000,
		kAudioFlags1000000 = 0x1000000,
		kAudioFlags_EnvelopeFast = 0x2000000,
		kAudioFlags_EnvelopeSlow = 0x4000000,
		kAudioFlags_2DRadius = 0x8000000,
		kAudioFlags20000000 = 0x20000000,
		kAudioFlags40000000 = 0x40000000,
	};

	UInt32 unk004;
	UInt32 unk008;
	BSAudioManager::UnkC unk00C;
	BSAudioManager::UnkC unk018;
	BSAudioManager::Unk24 unk024;
	BSAudioManager::Unk24 unk034;
	BSAudioManager::Unk24 unk044;
	NiTPointerMap<BSGameSound>	playingSounds;		// 054
	NiTPointerMap<BSSoundInfo>	playingSoundInfos1;	// 064
	NiTPointerMap<BSSoundInfo>	playingSoundInfos2;	// 074
	NiTPointerMap<NiAVObject>	soundPlayingObjects;// 084
	DList<BSGameSound>			gameSounds;			// 094
	UInt32						unk0A0;				// 0A0
	UInt32						unk0A4;				// 0A4
	float						flt0A8;				// 0A8
	_RTL_CRITICAL_SECTION criticalSectionAC;
	_RTL_CRITICAL_SECTION criticalSectionC4;
	_RTL_CRITICAL_SECTION criticalSectionDC;
	_RTL_CRITICAL_SECTION criticalSectionF4;
	_RTL_CRITICAL_SECTION criticalSection10C;
	UInt32 unk124;
	UInt32 unk128;
	UInt32 unk12C;
	UInt32 time130;
	UInt8 byte134;
	UInt8 byte135;
	UInt8 gap136[2];
	UInt32 threadID;
	BSAudioManagerThread* audioMgrThread;	// 13C
	float						volumes[12];		// 140
	//	0	Master
	//	1	Foot
	//	2	Voice
	//	3	Effects
	//	4	Music
	//	5	Radio
	UInt32						unk170[4];			// 170
	UInt32						nextMapKey;			// 180
	UInt8 ignoreTimescale;
	UInt8 byte185;
	UInt8 byte186;
	UInt8 byte187;

	static BSAudioManager* GetSingleton() { return (BSAudioManager*)0x11F6EF0; };
};
STATIC_ASSERT(sizeof(BSAudioManager) == 0x188);

enum PromptType
{
	kTake = 0x1,
	kOpen = 0x2,
	kSit = 0x3,
	kActivate = 0x4,
	kSleep = 0x5,
	kRead = 0x6,
	kTalk = 0x7,
	kOpenDoor = 0x8,
	kHorse = 0x9,
	kCrown = 0xA,
	kVampire = 0xB,
	kEquip = 0xC,
	kUnequip = 0xD,
	kDrink = 0xE,
	kEat = 0xF,
	kRecharge = 0x10,
	kBrew = 0x11,
	kApply = 0x12,
	kRepair = 0x13,
};

enum AnimAction
{
	kNone = 0xFFFFFFFF,
	kEquip_Weapon = 0x0,
	kUnequip_Weapon = 0x1,
	kAttack = 0x2,
	kAttack_Eject = 0x3,
	kAttack_Follow_Through = 0x4,
	kAttack_Throw = 0x5,
	kAttack_Throw_Attach = 0x6,
	kBlock = 0x7,
	kRecoil = 0x8,
	kReload = 0x9,
	kStagger = 0xA,
	kDodge = 0xB,
	kWait_For_Lower_Body_Anim = 0xC,
	kWait_For_Special_Idle = 0xD,
	kForce_Script_Anim = 0xE,
};

bool Actor::IsInReloadAnim()
{
	auto action = this->baseProcess->GetCurrentAnimAction();
	return action == kReload;
}

_declspec(naked) double Actor::GetMaxCarryWeightPerkModified()
{
	static const UInt32 procAddr = kAddr_GetMaxCarryWeightPerkModified;
	__asm	jmp		procAddr
}

__declspec(naked) Tile* Menu::AddTileFromTemplate(Tile* destTile, const char* templateName, UInt32 arg3)
{
	static const UInt32 procAddr = kAddr_TileFromTemplate;
	__asm	jmp		procAddr
}

// mapping of item type ID to whether they can be taken or not
const bool kInventoryType[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

__declspec(naked) SInt32 __fastcall GetFormCount(TESContainer::FormCountList *formCountList, ExtraContainerChanges::EntryDataList *objList, TESForm *form)
{
	__asm
	{
		push	esi
		push	edi
		mov		esi, [esp+0xC]
		xor		edi, edi
	contIter:
		mov		eax, [ecx]
		test	eax, eax
		jz		contNext
		cmp		[eax+4], esi
		jnz		contNext
		add		edi, [eax]
	contNext:
		mov		ecx, [ecx+4]
		test	ecx, ecx
		jnz		contIter
		jmp		doXtra
	xtraIter:
		mov		ecx, [edx]
		test	ecx, ecx
		jz		xtraNext
		cmp		[ecx+8], esi
		jnz		xtraNext
		mov		esi, ecx
		test	edi, edi
		jz		noCont
		call	ExtraContainerChanges::EntryData::HasExtraLeveledItem
		test	al, al
		jnz		noCont
		mov		eax, [esi+4]
		add		eax, edi
		js		retnZero
		jmp		done
	noCont:
		mov		eax, [esi+4]
		test	eax, eax
		jge		done
	retnZero:
		xor		eax, eax
		jmp		done
	xtraNext:
		mov		edx, [edx+4]
	doXtra:
		test	edx, edx
		jnz		xtraIter
		mov		eax, edi
	done:
		pop		edi
		pop		esi
		retn	4
	}
}

__declspec(naked) SInt32 TESObjectREFR::GetItemCount(TESForm *form)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		push	ecx
		push	ecx
		call	TESObjectREFR::GetContainer
		test	eax, eax
		jz		done
		mov		ecx, [ebp-4]
		add		eax, 4
		mov		[ebp-4], eax
		call	TESObjectREFR::GetContainerChangesList
		mov		edx, [ebp+8]
		cmp		byte ptr [edx+4], kFormType_BGSListForm
		jz		itemList
		push	edx
		mov		edx, eax
		mov		ecx, [ebp-4]
		call	GetFormCount
		jmp		done
	itemList:
		mov		[ebp-8], eax
		push	esi
		push	edi
		lea		esi, [edx+0x18]
		xor		edi, edi
	iterHead:
		mov		eax, [esi]
		test	eax, eax
		jz		iterNext
		push	eax
		mov		edx, [ebp-8]
		mov		ecx, [ebp-4]
		call	GetFormCount
		add		edi, eax
	iterNext:
		mov		esi, [esi+4]
		test	esi, esi
		jnz		iterHead
		mov		eax, edi
		pop		edi
		pop		esi
	done:
		mov		esp, ebp
		pop		ebp
		retn	4
	}
}

bool TESForm::HasScript()
{
	TESScriptableForm* scriptable = DYNAMIC_CAST(this, TESForm, TESScriptableForm);
	return scriptable && scriptable->script;
}

__declspec(naked) ContChangesEntry *TESObjectREFR::GetContainerChangesEntry(TESForm *itemForm)
{
	__asm
	{
		xor		eax, eax
		test	byte ptr [ecx+0x4A], 0x20
		jz		done
		mov		ecx, [ecx+0x44]
	xtraIter:
		cmp		byte ptr [ecx+4], kExtraData_ContainerChanges
		jz		found
		mov		ecx, [ecx+8]
		test	ecx, ecx
		jnz		xtraIter
	done:
		retn	4
	found:
		mov		eax, [ecx+0xC]
		test	eax, eax
		jz		done
		mov		eax, [eax]
		test	eax, eax
		jz		done
		mov		ecx, eax
		mov		edx, [esp+4]
	itemIter:
		mov		eax, [ecx]
		test	eax, eax
		jz		itemNext
		cmp		[eax+8], edx
		jz		done
	itemNext:
		mov		ecx, [ecx+4]
		test	ecx, ecx
		jnz		itemIter
		xor		eax, eax
		retn	4
	}
}

void TESObjectREFR::RemoveItemTarget(TESForm* itemForm, TESObjectREFR* target, SInt32 quantity, bool keepOwner)
{
	if IS_ID(itemForm, BGSListForm)
	{
		ListNode<TESForm>* lstIter = ((BGSListForm*)itemForm)->list.Head();
		do
		{
			if (lstIter->data)
				RemoveItemTarget(lstIter->data, target, quantity, keepOwner);
		} while (lstIter = lstIter->next);
	}
	else if (kInventoryType[itemForm->typeID])
	{
		SInt32 total = GetItemCount(itemForm);
		if (total < 1) return;
		if ((quantity > 0) && (quantity < total))
			total = quantity;
		if (itemForm->HasScript())
		{
			ContChangesEntry* entry = GetContainerChangesEntry(itemForm);
			if (entry && entry->extendData)
			{
				ExtraDataList* xData;
				SInt32 subCount;
				while ((total > 0) && (xData = entry->extendData->GetFirstItem()))
				{
					subCount = xData->GetCount();
					if (subCount < 1)
						continue;
					if (subCount > total)
						subCount = total;
					RemoveItem(itemForm, xData, subCount, keepOwner, 0, target, 0, 0, 1, 0);
					total -= subCount;
				}
			}
		}
		if (total > 0)
			RemoveItem(itemForm, NULL, total, keepOwner, 0, target, 0, 0, 1, 0);
	}
}

void Actor::PlayPickupOrEquipSound(TESForm* item, bool isPickup, bool isEquip)
{
	ThisCall(0x6F7D90, this, item, isPickup, isEquip);
}

TESObjectREFR* TESObjectREFR::ResolveAshpile()
{
	// handle actors who were turned to ashpiles
	if IS_TYPE(baseForm, TESObjectACTI)
	{
		ExtraAshPileRef* xAshPileRef = GetExtraType(extraDataList, AshPileRef);
		if (xAshPileRef)
			return xAshPileRef->sourceRef;
	}
	return this;
}

ExtraLock::Data* TESObjectREFR::GetLockData()
{
	return ThisCall<ExtraLock::Data*>(0x4E75F0, this);
}

float TESForm::GetWeight()
{
	TESWeightForm* weightForm = DYNAMIC_CAST(this, TESForm, TESWeightForm);
	if (weightForm)
	{
		return weightForm->weight;
	}
	else
	{
		if (IS_TYPE(this, TESObjectREFR))
		{
			return ((TESObjectREFR*)this)->baseForm->GetWeight();
		}
	}
	return 0.0F;
}

UInt32 TESForm::GetItemValue()
{
	if (typeID == kFormType_AlchemyItem) return ((AlchemyItem*)this)->value;
	TESValueForm* valForm = DYNAMIC_CAST(this, TESForm, TESValueForm);
	return valForm ? valForm->value : 0;
}

enum ScriptBlockTypes
{
	kScript_GameMode = 0x0,
	kScript_MenuMode = 0x1,
	kScript_OnActivate = 0x2,
	kScript_OnAdd = 0x3,
	kScript_OnEquip = 0x4,
	kScript_OnUnequip = 0x5,
	kScript_OnDrop = 0x6,
	kScript_SayToDone = 0x7,
	kScript_OnHit = 0x8,
	kScript_OnHitWith = 0x9,
	kScript_OnDeath = 0xA,
	kScript_OnMurder = 0xB,
	kScript_OnCombatEnd = 0xC,
	kScript_Function = 0xD,
	kScript_OnPackageStart = 0xF,
	kScript_OnPackageDone = 0x10,
	kScript_ScriptEffectStart = 0x11,
	kScript_ScriptEffectFinish = 0x12,
	kScript_ScriptEffectUpdate = 0x13,
	kScript_OnPackageChange = 0x14,
	kScript_OnLoad = 0x15,
	kScript_OnMagicEffectHit = 0x16,
	kScript_OnSell = 0x17,
	kScript_OnTrigger = 0x18,
	kScript_OnStartCombat = 0x19,
	kScript_OnTriggerEnter = 0x1A,
	kScript_OnTriggerLeave = 0x1B,
	kScript_OnActorEquip = 0x1C,
	kScript_OnActorUnequip = 0x1D,
	kScript_OnReset = 0x1E,
	kScript_OnOpen = 0x1F,
	kScript_OnClose = 0x20,
	kScript_OnGrab = 0x21,
	kScript_OnRelease = 0x22,
	kScript_OnDestructionStageChange = 0x23,
};

class ScriptBlockIterator
{
	UInt8		*dataPtr;
	UInt32		length;
	UInt32		currOffset;
	UInt8		*typePtr;
	UInt32		nextOpOffset;

	bool EvalBlock()
	{
		if (*(UInt16*)(dataPtr + currOffset) != 0x10) return false;
		currOffset += 2;
		UInt16 opSize = *(UInt16*)(dataPtr + currOffset);
		currOffset += 2;
		typePtr = dataPtr + currOffset;
		nextOpOffset = currOffset + opSize;
		currOffset += 2;
		currOffset += *(UInt16*)(dataPtr + currOffset) + opSize - 6;
		if (*(UInt32*)(dataPtr + currOffset) == 0x11)
		{
			currOffset += 4;
			return true;
		}
		return false;
	}

public:
	bool End() const {return !length;}

	void Next()
	{
		if (currOffset < length)
		{
			if (EvalBlock()) return;
			typePtr = NULL;
		}
		length = 0;
	}

	UInt8 *TypePtr() const {return typePtr;}
	UInt32 NextOpOffset() const {return nextOpOffset;}
	UInt32 NextBlockOffset() const {return currOffset;}

	ScriptBlockIterator(UInt8 *_dataPtr, UInt32 _length) : dataPtr(_dataPtr), length(_length), currOffset(4)
	{
		if (!dataPtr || (*(UInt32*)dataPtr != 0x1D) || !EvalBlock())
		{
			length = 0;
			typePtr = NULL;
		}
	}
};

bool TESObjectREFR::HasOpenCloseActivateScriptBlocks()
{
	TESForm* form = baseForm;
	Script* script;
	if IS_TYPE(form, Script)
		script = (Script*)form;
	else
	{
		TESScriptableForm* scriptable = DYNAMIC_CAST(form, TESForm, TESScriptableForm);
		script = scriptable ? scriptable->script : NULL;
		if (!script) return false;
	}
	UInt8* typePtr;
	for (ScriptBlockIterator blockIter(script->data, script->info.dataLength); !blockIter.End(); blockIter.Next())
	{
		typePtr = blockIter.TypePtr();

		if (*typePtr == kScript_OnActivate || *typePtr == kScript_OnOpen || *typePtr == kScript_OnClose)
		{
			return true;
		}
	}
	return false;
}

void TESObjectREFR::DisableScriptedActivate(bool disable)
{
	ExtraScript* xScript = GetExtraType(this->extraDataList, Script);
	if (!xScript || !xScript->script || !xScript->eventList) return;
	Script* script = xScript->script;
	UInt8* dataPtr = script->data, * endPtr = dataPtr + script->info.dataLength;
	dataPtr += 4;
	UInt16 lookFor = disable ? 0x100D : 0x2210, replace = disable ? 0x2210 : 0x100D, *opcode, length;
	while (dataPtr < endPtr)
	{
		opcode = (UInt16*)dataPtr;
		dataPtr += 2;
		length = *(UInt16*)dataPtr;
		dataPtr += 2;
		if (*opcode == 0x10)
		{
			if (*(UInt16*)dataPtr != 2)
			{
				dataPtr += 2;
				length = *(UInt16*)dataPtr + 6;
			}
		}
		else
		{
			if (*opcode == 0x1C)
			{
				opcode = (UInt16*)dataPtr;
				dataPtr += 2;
				length = *(UInt16*)dataPtr;
				dataPtr += 2;
			}
			if (*opcode == lookFor)
				* opcode = replace;
		}
		dataPtr += length;
	}
}

enum XboxControlCode
{
	kXboxCtrl_DPAD_UP = 0x1,
	kXboxCtrl_DPAD_DOWN = 0x2,
	kXboxCtrl_DPAD_LEFT = 0x3,
	kXboxCtrl_DPAD_RIGHT = 0x4,
	kXboxCtrl_START = 0x5,
	kXboxCtrl_BACK = 0x6,
	kXboxCtrl_LS_BUTTON = 0x7,
	kXboxCtrl_RS_BUTTON = 0x8,
	kXboxCtrl_BUTTON_A = 0x9,
	kXboxCtrl_BUTTON_B = 0xA,
	kXboxCtrl_BUTTON_X = 0xB,
	kXboxCtrl_BUTTON_Y = 0xC,
	kXboxCtrl_BUTTON_LT = 0xD,
	kXboxCtrl_BUTTON_RT = 0xE,
	kXboxCtrl_LB = 0xF,
	kXboxCtrl_RB = 0x10,
	kXboxCtrl_L3 = 0x11,
	kXboxCtrl_R3 = 0x12,
};

struct XINPUT_GAMEPAD_EX
{
	UInt32		eventCount;		// 00
	UInt16		wButtons;		// 04
	UInt8		bLeftTrigger;	// 06
	UInt8		bRightTrigger;	// 07
	SInt16		sThumbLX;		// 08
	SInt16		sThumbLY;		// 0A
	SInt16		sThumbRX;		// 0C
	SInt16		sThumbRY;		// 0E

	static XINPUT_GAMEPAD_EX* GetCurrent() { return (XINPUT_GAMEPAD_EX*)0x11795A0; };
	static XINPUT_GAMEPAD_EX* GetPrevious() { return (XINPUT_GAMEPAD_EX*)0x11795B0; };
};

bool __fastcall GetXIControlPressed(UInt32 ctrlID)
{
	XINPUT_GAMEPAD_EX* curr = XINPUT_GAMEPAD_EX::GetCurrent();
	XINPUT_GAMEPAD_EX* prev = XINPUT_GAMEPAD_EX::GetPrevious();

	switch (ctrlID)
	{
	case kXboxCtrl_DPAD_UP:
		return (curr->wButtons & 1) && !(prev->wButtons & 1);
	case kXboxCtrl_DPAD_DOWN:
		return (curr->wButtons & 2) && !(prev->wButtons & 2);
	case kXboxCtrl_DPAD_RIGHT:
		return (curr->wButtons & 8) && !(prev->wButtons & 8);
	case kXboxCtrl_DPAD_LEFT:
		return (curr->wButtons & 4) && !(prev->wButtons & 4);
	case kXboxCtrl_BACK:
		return (curr->wButtons & 0x20) && !(prev->wButtons & 0x20);
	default:
		return false;
	}
}

bool __fastcall GetXIControlHeld(UInt32 ctrlID)
{
	XINPUT_GAMEPAD_EX* curr = XINPUT_GAMEPAD_EX::GetCurrent();

	switch (ctrlID)
	{
	case kXboxCtrl_DPAD_UP:
		return (curr->wButtons & 1);
	case kXboxCtrl_DPAD_DOWN:
		return (curr->wButtons & 2);
	case kXboxCtrl_DPAD_RIGHT:
		return (curr->wButtons & 8);
	case kXboxCtrl_DPAD_LEFT:
		return (curr->wButtons & 4);
	default:
		return false;
	}
}

void Actor::EquipRef(TESObjectREFR* item)
{
	ExtraContainerChanges::EntryDataList* entryList = (ExtraContainerChanges::EntryDataList*)this->GetContainerChangesList();
	if (entryList)
	{
		auto toEquip = entryList->FindForItem(item->baseForm);
		if (toEquip) g_thePlayer->EquipItemAlt(toEquip, false, true);
	}
}


void SetTileComponentValue(Tile* tile, const char* path, float value)
{
	Tile::Value* val = tile->GetComponentValue(path);
	if (val)
	{
		val->parent->SetFloat(val->id, value, true);
	}
}

void SetTileComponentValue(Tile* tile, const char* path, const char* str)
{
	Tile::Value* val = tile->GetComponentValue(path);
	if (val)
	{
		val->parent->SetString(val->id, str, true);
	}
}

NiAVObject* NiNode::GetBlock(const char* blockName)
{
	if (StrEqualCI(m_blockName, blockName))
		return this;
	NiAVObject* found = NULL;
	for (NiTArray<NiAVObject*>::Iterator iter(m_children); !iter.End(); ++iter)
	{
		if (!*iter) continue;
		if (iter->GetNiNode())
			found = ((NiNode*)*iter)->GetBlock(blockName);
		else if (StrEqualCI(iter->m_blockName, blockName))
			found = *iter;
		else continue;
		if (found) break;
	}
	return found;
}
NiAVObject* TESObjectREFR::GetNiBlock(const char* blockName)
{
	NiNode* rootNode = GetNiNode();
	return rootNode ? rootNode->GetBlock(blockName) : NULL;
}

__declspec(naked) bool ExtraContainerChanges::EntryData::HasExtraLeveledItem()
{
	__asm
	{
		mov		ecx, [ecx]
		test	ecx, ecx
		jz		retnFalse
		iterHead :
		mov		edx, [ecx]
			test	edx, edx
			jz		iterNext
			test	byte ptr[edx + 0xD], 0x80
			jz		iterNext
			mov		al, 1
			retn
			iterNext :
		mov		ecx, [ecx + 4]
			test	ecx, ecx
			jnz		iterHead
			retnFalse :
		xor al, al
			retn
	}
}

__declspec(naked) SInt32 TESContainer::GetCountForForm(TESForm* form)
{
	__asm
	{
		push	esi
		lea		esi, [ecx + 4]
		xor eax, eax
		mov		edx, [esp + 8]
		iterHead:
		mov		ecx, [esi]
			test	ecx, ecx
			jz		iterNext
			cmp[ecx + 4], edx
			jnz		iterNext
			add		eax, [ecx]
			iterNext:
		mov		esi, [esi + 4]
			test	esi, esi
			jnz		iterHead
			pop		esi
			retn	4
	}
}

__declspec(naked) bool TESForm::IsItemPlayable()
{
	__asm
	{
		mov		al, [ecx + 4]
		cmp		al, kFormType_Armor
		jz		armor
		cmp		al, kFormType_Weapon
		jz		weapon
		cmp		al, kFormType_Ammo
		jz		ammo
		mov		al, 1
		retn
		armor :
		test[ecx + 0x78], 0x40
			setz	al
			retn
			weapon :
		test[ecx + 0x100], 0x80
			setz	al
			retn
			ammo :
		test[ecx + 0xA0], 2
			setz	al
			retn
	}
}

void TESObjectREFR::GetInventoryItems(InventoryItemsMap* map)
{
	TESContainer* container = GetContainer();
	if (!container) return;

	ExtraContainerChanges::EntryDataList* entryList = GetContainerChangesList();
	if (!entryList) return;

	map->Clear();

	TESContainer::FormCount* formCount;
	TESForm* item;
	SInt32 contCount, countDelta;
	ContChangesEntry* entry;

	ListNode<TESContainer::FormCount>* contIter = container->formCountList.Head();
	do
	{
		if (!(formCount = contIter->data)) continue;
		item = formCount->form;
		if ((item->typeID == kFormType_LeveledItem) || map->HasKey(item))
			continue;
		contCount = container->GetCountForForm(item);
		if (entry = entryList->FindForItem(item))
		{
			countDelta = entry->countDelta;
			if (entry->HasExtraLeveledItem())
				contCount = countDelta;
			else contCount += countDelta;
		}
		if (contCount > 0)
			map->Emplace(item, contCount, entry);
	} while (contIter = contIter->next);

	if (entryList)
	{
		ListNode<ContChangesEntry>* xtraIter = entryList->Head();
		do
		{
			if (!(entry = xtraIter->data)) continue;
			item = entry->type;
			if (map->HasKey(item))
				continue;
			countDelta = entry->countDelta;
			if (countDelta > 0)
				map->Emplace(item, countDelta, entry);
		} while (xtraIter = xtraIter->next);
	}

	if (this->IsActor())
	{
		Actor* actor = (Actor*)this;
		ExtraDroppedItemList* xDropped = GetExtraType(actor->extraDataList, DroppedItemList);
		if (xDropped)
		{
			ListNode<TESObjectREFR>* iter = xDropped->itemRefs.Head();
			do
			{
				if (iter->data) map->Emplace(iter->data, -1, nullptr);
			} while (iter = iter->next);
		}
	}
}

bool IsLockedRef(TESObjectREFR* ref)
{
	if (auto lock = ref->GetLockData())
	{
		return lock->IsLocked();
	}
	return false;
}

enum ActorValueCode
{
	kAVCode_ActionPoints = 12,
	kAVCode_CarryWeight = 0xD,
	kAVCode_InventoryWeight = 0x2E,
};

enum NiTypes
{
	kNiType_NiControllerManager = 0x1091F04,
};

void TESObjectREFR::PlayGroup(const char* name)
{
	auto node = this->GetNiNode();
	if (!node) return;

	node = node->GetNiNode();
	if (!node) return;

	auto child = node->m_children[0];
	if (!child) return;

	NiControllerManager* controllerManager = CdeclCall<NiControllerManager*>(0x424D50, kNiType_NiControllerManager, child->m_controller);
	if (!controllerManager)
	{
		controllerManager = CdeclCall<NiControllerManager*>(0x424D50, kNiType_NiControllerManager, node->m_controller);
	}
	if (!controllerManager) return;

	UInt32 niMemObject;
	auto sequenceKey = ThisCall<UInt32>(0x422920, &niMemObject, name);
	auto animSequence = ThisCall<BSAnimGroupSequence*>(0x44DBF0, controllerManager, sequenceKey); // NiControllerManager::LookupSequence
	ThisCall(0x422950, &niMemObject);

	if (animSequence)
	{
		StdCall(0x44DB50, animSequence, 0, 0, 1.0, 0.0, 0);
		animSequence->offset = FLT_MIN;
		controllerManager->flags |= 8;
	}
}

void TESObjectREFR::RemoveOwnership()
{
	this->extraDataList.RemoveByType(kExtraData_Ownership);
}

void Tile::SetChangeFlags(int flags)
{
	ThisCall(0xBEE370, this, flags);
}

class BSBound : public NiExtraData
{
public:
	NiVector3		centre;			// 0C
	NiVector3		dimensions;		// 18
};

DListNode<Tile>* Tile::GetNthChild(UInt32 index)
{
	return children.Tail()->Regress(index);
}
__declspec(naked) float __vectorcall GetDistance2D(TESObjectREFR* ref1, TESObjectREFR* ref2)
{
	__asm
	{
		movq	xmm0, qword ptr[ecx + 0x2C]
		movq	xmm1, qword ptr[edx + 0x2C]
		subps	xmm0, xmm1
		mulps	xmm0, xmm0
		movss	xmm1, xmm0
		psrlq	xmm0, 0x20
		addss	xmm1, xmm0
		sqrtss	xmm0, xmm1
		retn
	}
}
__declspec(naked) TESWorldSpace* TESObjectREFR::GetParentWorld()
{
	__asm
	{
		mov		eax, [ecx + 0x3C]
		test	eax, eax
		jnz		getWorld
		push	kExtraData_PersistentCell
		add		ecx, 0x40
		call	BaseExtraList::GetByType
		test	eax, eax
		jz		done
		mov		eax, [eax + 0xC]
		getWorld:
		mov		eax, [eax + 0xC0]
			done :
			retn
	}
}
bool Actor::IsInCombatWith(Actor* target)
{
	return ThisCall<bool>(0x703950, this, target);
}
__declspec(naked) bool __fastcall TESObjectREFR::GetInSameCellOrWorld(TESObjectREFR* target)
{
	__asm
	{
		mov		eax, [ecx + 0x3C]
		test	eax, eax
		jnz		hasCell1
		push	edx
		push	kExtraData_PersistentCell
		add		ecx, 0x40
		call	BaseExtraList::GetByType
		pop		edx
		test	eax, eax
		jz		done
		mov		eax, [eax + 0xC]
		hasCell1:
		mov		ecx, [edx + 0x3C]
			test	ecx, ecx
			jnz		hasCell2
			push	eax
			push	kExtraData_PersistentCell
			lea		ecx, [edx + 0x40]
			call	BaseExtraList::GetByType
			pop		edx
			test	eax, eax
			jz		done
			mov		ecx, [eax + 0xC]
			mov		eax, edx
			hasCell2 :
		cmp		eax, ecx
			jz		retnTrue
			mov		eax, [eax + 0xC0]
			test	eax, eax
			jz		done
			cmp		eax, [ecx + 0xC0]
			retnTrue:
		setz	al
			done :
		retn
	}
}

__declspec(naked) float __vectorcall GetDistance3D(TESObjectREFR* ref1, TESObjectREFR* ref2)
{
	__asm
	{
		movups	xmm0, [ecx + 0x2C]
		movups	xmm1, [edx + 0x2C]
		subps	xmm0, xmm1
		mulps	xmm0, xmm0
		movhlps	xmm1, xmm0
		addss	xmm1, xmm0
		psrlq	xmm0, 0x20
		addss	xmm1, xmm0
		sqrtss	xmm0, xmm1
		retn
	}
}
bool Actor::IsSneaking() {
	return actorMover && ((actorMover->GetMovementFlags() & 0xC00) == 0x400);
}
__declspec(naked) float __vectorcall TESObjectREFR::GetDistance(TESObjectREFR* target)
{
	__asm
	{
		push	ecx
		push	edx
		call	TESObjectREFR::GetInSameCellOrWorld
		pop		edx
		pop		ecx
		test	al, al
		jz		fltMax
		jmp		GetDistance3D
		fltMax :
		movss	xmm0, kFltMax
			retn
	}
}
bool IsFactionEnemy(Actor* a1, Actor* a2) {
	UInt8 out;
	return ThisCall<UInt8>(0x70B780, a1, a2, &out) == 1;
}