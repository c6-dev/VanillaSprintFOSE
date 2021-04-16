#pragma once
#include "fose/fose/GameForms.h"
class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	static ModelLoader* GetSingleton();
	void QueueReference(TESObjectREFR* refr, UInt32 arg2, UInt32 arg3);
};