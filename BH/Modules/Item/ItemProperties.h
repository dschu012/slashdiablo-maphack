#pragma once
#include "../Module.h"
#include "../../Constants.h"
#include "../../Config.h"


class ItemProperties : public Module {
public:

	ItemProperties() : Module("ItemProperties") {};

	void OnLoad();
	void OnUnload();

	static void __stdcall DrawProperties(wchar_t *wTxt);
	static void __stdcall OnPropertyBuild(wchar_t* wOut, int nStat, UnitAny* pItem, int nStatParam);
	static BOOL __stdcall OnDamagePropertyBuild(UnitAny* pItem, DamageStats* pStats, int nStat, wchar_t* wOut);
	
};

void __fastcall D2CLIENT_Properties();
void D2CLIENT_GetPropertyStringDamage_STUB();
void D2CLIENT_GetPropertyString_STUB();
