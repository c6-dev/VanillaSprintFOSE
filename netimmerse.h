#pragma once
#include "fose/NiTypes.h"
class BSFadeNode;
class NiMultiTargetTransformController;
class NiTextKeyExtraData;
class NiControllerManager;
class NiDefaultAVObjectPalette;
class NiSourceTexture;
class bhkNiCollisionObject;
class hkpWorldObject;
struct hkVector4;
class NiLight;
class BSCubeMapCamera;
class NiFrustumPlanes;
class NiCullingProcess;
class NiTexture;
class NiSkinPartition;
class NiSkinInstance;
class NiSourceCubeMap;
class NiRenderedCubeMap;
class NiDepthStencilBuffer;
class NiRenderTargetGroup;
class NiGeometryData;
class NiRenderedTexture;
class NiTriStrips;
class NiParticles;
class NiLines;
class IDirect3DDevice9;
class NiDX9RenderState;
class NiUnsharedGeometryGroup;
class NiNode;
class TESObjectREFR;
class Tile;
class BSPortalGraph;
class NiTriShape;
struct NiSphere;
class NiProperty;
class NiInterpolator;
class NiControllerSequence;

class NiMemObject
{
	NiMemObject();
	~NiMemObject();
};

// 08
class NiRefObject : public NiMemObject
{
public:
	NiRefObject();
	~NiRefObject();

	virtual void	Destructor(bool freeThis);
	virtual void	Free(void);

	UInt32		m_uiRefCount;	// 04
};

// 08
class NiObject : public NiRefObject
{
public:
	NiObject();
	~NiObject();

	virtual NiRTTI* GetType();
	virtual NiNode* GetNiNode();
	virtual BSFadeNode* GetFadeNode();
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(UInt32 arg);
	virtual void	Unk_13(UInt32 arg);
	virtual void	Unk_14(UInt32 arg);
	virtual void	Unk_15(UInt32 arg);
	virtual void	Unk_16(UInt32 arg);
	virtual void	Unk_17(UInt32 arg);
	virtual void	Unk_18(UInt32 arg);
	virtual void	Unk_19(UInt32 arg);
	virtual void	Unk_1A(UInt32 arg);
	virtual void	Unk_1B(UInt32 arg);
	virtual void	Unk_1C(void);
	virtual void	Unk_1D(void);
	virtual void	Unk_1E(UInt32 arg);
	virtual UInt32	Unk_1F(void);
	virtual void	Unk_20(void);
	virtual void	Unk_21(UInt32 arg);
	virtual void	Unk_22(void);
};
class NiExtraData : public NiObject
{
public:
	NiExtraData();
	~NiExtraData();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);

	UInt32			unk08;		// 08
};
class NiTimeController;
class NiExtraData;
// 18
class NiObjectNET : public NiObject
{
public:
	NiObjectNET();
	~NiObjectNET();

	const char* m_blockName;				// 08
	NiTimeController* m_controller;				// 0C
	NiExtraData** m_extraDataList;			// 10
	UInt16				m_extraDataListLen;			// 14
	UInt16				m_extraDataListCapacity;	// 16

	void DumpExtraData();
};

// 9C
class NiAVObject : public NiObjectNET
{
public:
	NiAVObject();
	~NiAVObject();

	virtual void	Unk_23(UInt32 arg1);
	virtual void	Unk_24(NiMatrix33* arg1, NiVector3* arg2, bool arg3);
	virtual void	Unk_25(UInt32 arg1);
	virtual void	Unk_26(UInt32 arg1);
	virtual void	Unk_27(UInt32 arg1);
	virtual void	Unk_28(UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual void	Unk_29(UInt32 arg1, UInt32 arg2);
	virtual void	Unk_2A(UInt32 arg1, UInt32 arg2);
	virtual void	Unk_2B(UInt32 arg1, UInt32 arg2);
	virtual void	Unk_2C(UInt32 arg1);
	virtual void	Unk_2D(UInt32 arg1);
	virtual void	UpdateTransform(UInt32 arg1);
	virtual void	Unk_2F(void);
	virtual void	UpdateBounds(UInt32 arg1);
	virtual void	Unk_31(UInt32 arg1, UInt32 arg2);
	virtual void	Unk_32(UInt32 arg1);
	virtual void	Unk_33(UInt32 arg1);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(UInt32 arg1);

	NiAVObject* m_parent;				// 18
	bhkNiCollisionObject* m_collisionObject;		// 1C
	NiSphere* m_kWorldBound;			// 20
	NiProperty*		m_propertyList[3];			// 24
	UInt32					m_flags;				// 30
	NiMatrix33				m_localRotate;			// 34
	NiVector3				m_localTranslate;		// 58
	float					m_localScale;			// 64
	NiMatrix33				m_worldRotate;			// 68
	NiVector3				m_worldTranslate;		// 8C
	float					m_worldScale;			// 98

	void DumpProperties();
	void DumpParents();
};

class NiCamera : NiAVObject
{
	float worldToCam[4][4];
	NiFrustum frustum;
	float minNearPlaneDist;
	float maxFarNearRatio;
	NiViewport viewPort;
	float LODAdjust;
};
STATIC_ASSERT(sizeof(NiCamera) == 0x114);

class NiNode : public NiAVObject {
public:
	NiTArray<NiAVObject*>	m_children;		// 9C

	NiAVObject* GetBlock(const char* blockName);
	NiNode* GetNode(const char* nodeName);
};
STATIC_ASSERT(sizeof(NiNode) == 0xAC);

// 34
class NiTimeController : public NiObject
{
public:
	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	SetTarget(NiNode* pTarget);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);

	UInt16								flags;				// 08
	UInt16								unk0A;				// 0A
	float								frequency;			// 0C
	float								phaseTime;			// 10
	float								flt14;				// 14
	float								flt18;				// 18
	float								flt1C;				// 1C
	float								flt20;				// 20
	float								flt24;				// 24
	float								flt28;				// 28
	NiNode* target;			// 2C
	NiMultiTargetTransformController* multiTargetCtrl;	// 30

};

// 7C
class NiControllerManager : public NiTimeController
{
public:
	virtual void	Unk_2D(void);

	NiTArray<NiControllerSequence*>					sequences;		// 34
	void* ptr44;			// 44
	UInt32											unk48;			// 48
	UInt32											unk4C;			// 4C
	NiTMapBase<const char*, NiControllerSequence*>	seqStrMap;		// 50
	UInt32											unk60;			// 60
	NiTArray<void*>* arr64;			// 64
	UInt32											unk68;			// 68
	UInt32											unk6C;			// 6C
	UInt32											unk70;			// 70
	UInt32											unk74;			// 74
	NiDefaultAVObjectPalette* defObjPlt;		// 78
};
STATIC_ASSERT(sizeof(NiControllerManager) == 0x7C);

// 74
class NiControllerSequence : public NiObject
{
public:
	virtual void	Unk_23(void);

	struct ControlledBlock
	{
		NiInterpolator* interpolator;
		NiMultiTargetTransformController* multiTargetCtrl;
		// More
	};

	const char* sequenceName;			// 08
	UInt32				numControlledBlocks;	// 0C
	UInt32				arrayGrowBy;			// 10
	ControlledBlock** controlledBlocks;		// 14
	const char** unkNodeName;			// 18
	float				weight;					// 1C
	NiTextKeyExtraData* textKeyData;			// 20
	UInt32				cycleType;				// 24
	float				frequency;				// 28
	float				startTime;				// 2C
	float				stopTime;				// 30
	float				flt34;					// 34
	float				flt38;					// 38
	float				flt3C;					// 3C
	NiControllerManager* manager;				// 40
	UInt32				unk44;					// 44
	float				offset;					// 48
	float				flt4C;					// 4C
	float				flt50;					// 50
	float				flt54;					// 54
	UInt32				unk58;					// 58
	const char* rootNodeName;			// 5C
	UInt32				unk60[5];				// 60
};
STATIC_ASSERT(sizeof(NiControllerSequence) == 0x74);

// 3C
class TESAnimGroup : public NiRefObject
{
public:
	UInt32			unk08[2];	// 08
	UInt8			index;		// 10
	UInt8			unk11;		// 11
	UInt8			unk12[1];	// 12
	UInt32			unk14[10];	// 14
};

// 78
class BSAnimGroupSequence : public NiControllerSequence
{
public:
	TESAnimGroup* animGroup;		// 74
};