#pragma once

#include "fose\PluginAPI.h"
#include "fose\GameAPI.h"
#include "fose\GameObjects.h"



bool versionCheck(const FOSEInterface* fose);
void DeferredInit();
void DeferredUpdate();

HMODULE VSHandle;

PlayerCharacter* g_thePlayer = NULL;
DataHandler* g_dataHandler;
InterfaceManager* g_interfaceManager = NULL;
OSInputGlobals* g_inputGlobals = NULL;
BaseProcess* g_playerProcess = NULL;
ActorValueOwner* g_playerAVOwner = NULL;
typedef void (*MainLoopAddCallbackEx)(void* cmdPtr, void* thisObj, UInt32 callCount, UInt32 callDelay);