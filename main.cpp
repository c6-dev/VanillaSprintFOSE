#include "utility.h"
#include "decoding.h"
#include "main.h"
#include "Version.h"

extern "C"
{
	BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpreserved)
	{
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			VSHandle = hModule;
			DisableThreadLibraryCalls(hModule);
		}
		return TRUE;
	}

	bool FOSEPlugin_Query(const FOSEInterface* fose, PluginInfo* info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Vanilla Sprint";
		info->version = PLUGIN_VERSION;
		return versionCheck(fose);
	}

	bool FOSEPlugin_Load(const FOSEInterface* fose)
	{
		if (fose->isEditor) return false;
		auto commandExtender = GetModuleHandle("CommandExtender.dll");
		auto callbackEx = (MainLoopAddCallbackEx)GetProcAddress(commandExtender, "MainLoopAddCallbackEx");
		callbackEx(DeferredInit, NULL, 1, 1);
		callbackEx(DeferredUpdate, NULL, 0, 1);
		return true;
	}
};



void DeferredInit()
{
	g_thePlayer = PlayerCharacter::GetSingleton();
	g_interfaceManager = InterfaceManager::GetSingleton();
	g_inputGlobals = *(OSInputGlobals**)0x011795C4;
	g_playerProcess = ((Actor*)g_thePlayer)->baseProcess;
	g_playerAVOwner = &((Actor*)g_thePlayer)->avOwner;

}
int currentMult, baseMult, ap;
void DeferredUpdate()
{
	if (g_interfaceManager->currentMode == 2) return;
	currentMult = g_playerAVOwner->GetActorValue(eActorVal_SpeedMultiplier);
	baseMult = g_playerAVOwner->GetBaseActorValue(eActorVal_SpeedMultiplier);
	ap = (int)g_playerAVOwner->GetActorValue(12);
	if ((g_inputGlobals->GetKeyState(0x11, KeyState::isHeld)) && (g_inputGlobals->GetKeyState(0x2A, KeyState::isHeld)) && ap > 2) {
		if (currentMult < (baseMult * 2)) g_thePlayer->ModActorValue(eActorVal_SpeedMultiplier, 3, 0);
		g_thePlayer->DamageActorValue(eActorVal_ActionPoints, -0.2, NULL);
	}
	else if (currentMult > baseMult) {
		g_thePlayer->ModActorValue(eActorVal_SpeedMultiplier, -3, 0);
	}
	else if (!(g_inputGlobals->GetKeyState(0x11, KeyState::isHeld)) && !(g_inputGlobals->GetKeyState(0x2A, KeyState::isHeld))) {
		g_thePlayer->SetActorValueInt(eActorVal_SpeedMultiplier, baseMult);
	}
	g_playerProcess->unk2C->flags &= ~0x3000;
}

bool versionCheck(const FOSEInterface* fose)
{
	if (fose->isEditor) return false;
	if (fose->foseVersion < FOSE_VERSION_INTEGER)
	{
		_ERROR("FOSE version too old (got %08X expected at least %08X)", fose->foseVersion, FOSE_VERSION_INTEGER);
		return false;
	}
	if (fose->runtimeVersion != FALLOUT_VERSION)
	{
		_ERROR("incorrect runtime version (got %08X need %08X)", fose->runtimeVersion, FALLOUT_VERSION);
		return false;
	}
	return true;
}