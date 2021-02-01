#pragma once
#include <BML/BMLAll.h>

extern "C" {
	__declspec(dllexport) IMod* BMLEntry(IBML* bml);
}

class Statistica : public IMod
{
public:
	Statistica(IBML* bml) : IMod(bml) {}

	virtual CKSTRING GetID() override { return "Statistica"; }
	virtual CKSTRING GetVersion() override { return "0.0.2"; }
	virtual CKSTRING GetName() override { return "Statistica"; }
	virtual CKSTRING GetAuthor() override { return "Swung0x48"; }
	virtual CKSTRING GetDescription() override { return "Get game stats."; }
	DECLARE_BML_VERSION;

private:
	virtual void OnLoad() override;
};

