#include "GameTasks.h"

const UInt32 kModelLoader_QueueReference = 0x428E90;

ModelLoader* ModelLoader::GetSingleton()
{
	return *(ModelLoader **)0x106CA70;
}

__declspec(naked) void ModelLoader::QueueReference(TESObjectREFR* refr, UInt32 arg2, UInt32 arg3)
// arg2 is encoded based on the parent cell and arg3 is most likely a boolean
{
	__asm	jmp		kModelLoader_QueueReference
}