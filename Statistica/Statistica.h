#pragma once
#include <BML/BMLAll.h>
#include <thread>
#include <chrono>
#include "Hiperf_Timer.h"
extern "C" {
	__declspec(dllexport) IMod* BMLEntry(IBML* bml);
}

class Statistica : public IMod
{
public:
	Statistica(IBML* bml) : IMod(bml) {}

	virtual CKSTRING GetID() override { return "Statistica"; }
	virtual CKSTRING GetVersion() override { return "0.0.5"; }
	virtual CKSTRING GetName() override { return "Statistica"; }
	virtual CKSTRING GetAuthor() override { return "Swung0x48"; }
	virtual CKSTRING GetDescription() override { return "Get game stats."; }
	DECLARE_BML_VERSION;

	CKDWORD _inputLat = 0;
	VxMatrix proj_mat_;
	BGui::Gui* gui_ = nullptr;
	BGui::Panel* panel_ = nullptr;
private:
	Hiperf_Timer hiperf_timer_;
	bool on_start_level_ = false;
	
	virtual void OnLoad() override;
	virtual void OnProcess() override;
	virtual void OnBallNavInactive() override;
	virtual void OnLoadObject(CKSTRING filename, BOOL isMap, CKSTRING masterName,
		CK_CLASSID filterClass, BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials,
		BOOL dynamic, XObjectArray* objArray, CKObject* masterObj) override;
	virtual void OnStartLevel() override;
	virtual void OnPreEndLevel() override;
	virtual void OnCounterActive() override;
	virtual void OnCounterInactive() override;
	virtual void OnPauseLevel() override;
	virtual void OnUnpauseLevel() override;
	virtual void OnUnload() override;
	virtual void OnPreCheckpointReached() override;
	virtual void OnPreStartMenu() override;
};

