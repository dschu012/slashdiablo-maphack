#include "ItemProperties.h"

#undef min
#undef max

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

/* https://github.com/lolet/D2Ex2/blob/master/D2Stubs.cpp#L295 */

Patch* itemPropertiesPatch = new Patch(Jump, D2CLIENT, { 0x5612C, 0x2E3FC }, (int)D2CLIENT_Properties, 6);
Patch* itemPropertiesStringDamagePatch = new Patch(Call, D2CLIENT, { 0x55D7B, 0x2E04B }, (int)D2CLIENT_GetPropertyStringDamage_STUB, 5);
Patch* itemPropertiesStringPatch = new Patch(Call, D2CLIENT, { 0x55D9D, 0x2E06D }, (int)D2CLIENT_GetPropertyString_STUB, 5);


void ItemProperties::OnLoad() {
	itemPropertiesPatch->Install();
	itemPropertiesStringDamagePatch->Install();
	itemPropertiesStringPatch->Install();
}

void ItemProperties::OnUnload() {
	itemPropertiesPatch->Remove();
	itemPropertiesStringDamagePatch->Remove();
	itemPropertiesStringPatch->Remove();
}


static D2ItemsTxt* GetArmorText(UnitAny* pItem) {
	ItemText* itemTxt = D2COMMON_GetItemText(pItem->dwTxtFileNo);
	int armorTxtRecords = *p_D2COMMON_ArmorTxtRecords;
	for (int i = 0; i < armorTxtRecords; i++) {
		D2ItemsTxt* armorTxt = &(*p_D2COMMON_ArmorTxt)[i];
		if (strcmp(armorTxt->szCode, itemTxt->szCode) == 0) {
			return armorTxt;
		}
	}
}

void __stdcall ItemProperties::DrawProperties(wchar_t *wTxt)
{
	//Maybe print stuff like base/min/max rolls of armor and such...
	UnitAny* pItem = *p_D2CLIENT_SelectedInvItem;
	if (!pItem) return;
	//Any Armor ItemTypes.txt
	if (D2COMMON_IsMatchingType(pItem, ITEM_TYPE_ALLARMOR)) {
		int aLen = 0;
		aLen = wcslen(wTxt);
		D2ItemsTxt* armorTxt = GetArmorText(pItem);
		DWORD base = D2COMMON_GetBaseStat(pItem, STAT_DEFENSE, 0);
		DWORD min = armorTxt->dwMinAc;
		DWORD max = armorTxt->dwMaxAc;
		if (pItem->pItemData->dwFlags & ITEM_ETHEREAL) {
			min = floor(min * 1.50);
			max = floor(max * 1.50);
			//hack... if not in range we assume it is ebugged
			if (!(base <= max && base >= min)) {
				min = floor(min * 1.50);
				max = floor(max * 1.50);
			}
		}
		swprintf_s(wTxt + aLen, 1024 - aLen, L"%sBase Defense: %d [%d-%d]%s\n", L"ÿc9", base, min, (max+1), L"ÿc3");
	}
}

static RunesTxt* GetRunewordTxtById(int rwId)
{
	int n = *(D2COMMON_GetRunesTxtRecords());
	for (int i = 1; i < n; ++i)
	{
		RunesTxt* pTxt = &(*p_D2COMMON_RunesTxt)[i];
		if (!pTxt)
			break;
		if (pTxt->dwRwId == rwId)
			return pTxt;
	}
	return 0;
}


static ItemsTxtStat* GetAllStatModifier(ItemsTxtStat* pStats, int nStats, int nStat, ItemsTxtStat* pOrigin)
{
	for (int i = 0; i<nStats; ++i) {
		if (pStats[i].dwProp == 0xffffffff)
			break;
		if (pStats[i].dwProp == pOrigin->dwProp)
			continue;

		PropertiesTxt * pProp = &(*p_D2COMMON_sgptDataTable)->pProperties[pStats[i].dwProp];
		if (!pProp)
			break;

		for (int j = 0; j < 7; ++j)
		{
			if (pProp->wStat[j] == 0xFFFF)
				break;
			if (pProp->wStat[j] == nStat)
				return &pStats[i];
		}
	}
	return 0;
}

static ItemsTxtStat* GetItemsTxtStatByMod(ItemsTxtStat* pStats, int nStats, int nStat, int nStatParam)
{
	if (nStat == STAT_SKILLONKILL || nStat == STAT_SKILLONHIT || nStat == STAT_SKILLONSTRIKING || nStat == STAT_SKILLONDEATH ||
		nStat == STAT_SKILLONLEVELUP || nStat == STAT_SKILLWHENSTRUCK || nStat == STAT_CHARGED ||
		nStat == STAT_MINIMUMCOLDDAMAGE || nStat == STAT_MINIMUMLIGHTNINGDAMAGE || nStat == STAT_MINIMUMFIREDAMAGE || nStat == STAT_MINIMUMPOISONDAMAGE || nStat == STAT_MINIMUMMAGICALDAMAGE) // Skip skills without ranges
		return 0;
	for (int i = 0; i<nStats; ++i) {
		if (pStats[i].dwProp == 0xffffffff)
			break;
		PropertiesTxt * pProp = &(*p_D2COMMON_sgptDataTable)->pProperties[pStats[i].dwProp];
		if (!pProp)
			break;
		if (pProp->wStat[0] == 0xFFFF && pProp->nFunc[0] == 7 && (nStat == STAT_ENHANCEDDAMAGE || nStat == STAT_ENHANCEDMINIMUMDAMAGE || nStat == STAT_ENHANCEDMAXIMUMDAMAGE ||
			nStat == STAT_MAXENHANCEDDMGPERTIME || nStat == STAT_MAXENHANCEDDMGPERLEVEL))
			return &pStats[i];
		else if (pProp->wStat[0] == 0xFFFF && pProp->nFunc[0] == 6 && (nStat == STAT_MAXIMUMDAMAGE || nStat == STAT_SECONDARYMAXIMUMDAMAGE ||
			nStat == STAT_MAXDAMAGEPERTIME || nStat == STAT_MAXDAMAGEPERLEVEL))
			return &pStats[i];
		else if (pProp->wStat[0] == 0xFFFF && pProp->nFunc[0] == 5 && (nStat == STAT_MINIMUMDAMAGE || nStat == STAT_SECONDARYMINIMUMDAMAGE))
			return &pStats[i];
		for (int j = 0; j < 7; ++j)
		{
			if (pProp->wStat[j] == 0xFFFF)
				break;
			if (pProp->wStat[j] == nStat && pStats[i].dwPar == nStatParam)
				return &pStats[i];
		}
	}
	return 0;
}

void __stdcall ItemProperties::OnPropertyBuild(wchar_t * wOut, int nStat, UnitAny * pItem, int nStatParam)
{
	if (pItem && pItem->dwType == UNIT_ITEM) {
		ItemsTxtStat* stat = 0;
		ItemsTxtStat* all_stat = 0; // Stat for common modifer like all-res, all-stats
		switch (pItem->pItemData->dwQuality) {
		case ITEM_QUALITY_SET:
		{
			SetItemsTxt * pTxt = &(*p_D2COMMON_sgptDataTable)->pSetItems[pItem->pItemData->dwQuality2];
			if (!pTxt)
				break;
			stat = GetItemsTxtStatByMod(pTxt->hStats, 9 + 10, nStat, nStatParam);
			if (stat)
				all_stat = GetAllStatModifier(pTxt->hStats, 9 + 10, nStat, stat);
		}
		case ITEM_QUALITY_UNIQUE:
		{
			if (pItem->pItemData->dwQuality == ITEM_QUALITY_UNIQUE) {
				UniqueItemsTxt * pTxt = &(*p_D2COMMON_sgptDataTable)->pUniqueItems[pItem->pItemData->dwQuality2];
				if (!pTxt)
					break;
				stat = GetItemsTxtStatByMod(pTxt->hStats, 12, nStat, nStatParam);
				if (stat)
					all_stat = GetAllStatModifier(pTxt->hStats, 12, nStat, stat);
			}
			if (stat) {
				int statMin = stat->dwMin;
				int statMax = stat->dwMax;

				if (all_stat) {
					statMin += all_stat->dwMin;
					statMax += all_stat->dwMax;
				}
				if (statMin < statMax) {
					int	aLen = wcslen(wOut);
					int leftSpace = 128 - aLen > 0 ? 128 - aLen : 0;

					if (nStat == STAT_LIFEPERLEVEL || nStat == STAT_MANAPERLEVEL || nStat == STAT_MAXENHANCEDDMGPERLEVEL || nStat == STAT_MAXDAMAGEPERLEVEL)
					{
						statMin = D2COMMON_GetBaseStatSigned(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0) * statMin >> 3;
						statMax = D2COMMON_GetBaseStatSigned(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0) * statMax >> 3;
					}
					if (leftSpace)
						swprintf_s(wOut + aLen, leftSpace, L" %s[%d - %d]%s", L"ÿc9", statMin, statMax, L"ÿc3");
				}
			}
		} break;
		default:
		{
			if (pItem->pItemData->dwFlags & ITEM_RUNEWORD) {
				RunesTxt* pTxt = GetRunewordTxtById(pItem->pItemData->wPrefix[0]);
				if (!pTxt)
					break;
				stat = GetItemsTxtStatByMod(pTxt->hStats, 7, nStat, nStatParam);
				if (stat) {
					int statMin = stat->dwMin;
					int statMax = stat->dwMax;

					all_stat = GetAllStatModifier(pTxt->hStats, 7, nStat, stat);

					if (all_stat) {
						statMin += all_stat->dwMin;
						statMax += all_stat->dwMax;
					}

					if (stat->dwMin != stat->dwMax) {
						int	aLen = wcslen(wOut);
						int leftSpace = 128 - aLen > 0 ? 128 - aLen : 0;

						if (nStat == STAT_LIFEPERLEVEL || nStat == STAT_MANAPERLEVEL || nStat == STAT_MAXENHANCEDDMGPERLEVEL || nStat == STAT_MAXDAMAGEPERLEVEL)
						{
							statMin = D2COMMON_GetBaseStatSigned(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0) * statMin >> 3;
							statMax = D2COMMON_GetBaseStatSigned(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0) * statMax >> 3;
						}
						if (leftSpace)
							swprintf_s(wOut + aLen, leftSpace, L" %s[%d - %d]%s", L"ÿc9", statMin, statMax, L"ÿc3");
					}
				}
			}
			else if (pItem->pItemData->dwQuality == ITEM_QUALITY_MAGIC || pItem->pItemData->dwQuality == ITEM_QUALITY_RARE || pItem->pItemData->dwQuality == ITEM_QUALITY_RARE)
			{
				//TODO
				int nAffixes = *p_D2COMMON_AutoMagicTxt - D2COMMON_GetAffixTxt(1); // Number of affixes without Automagic
				int min = 0, max = 0;
				int type = D2COMMON_GetItemType(pItem);
				for (int i = 1;; ++i) {
					if (!pItem->pItemData->wAutoPrefix && i > nAffixes) // Don't include Automagic.txt affixes if item doesn't use them
						break;
					AutoMagicTxt* pTxt = D2COMMON_GetAffixTxt(i);
					if (!pTxt)
						break;
					//Skip if stat level is > 99 or affix is prelod
					if (pTxt->dwLevel > 99 || !pTxt->wVersion)
						continue;
					//Skip if stat is not spawnable
					if (pItem->pItemData->dwQuality < ITEM_QUALITY_CRAFT && !pTxt->wSpawnable)
						continue;
					//Skip for rares+
					if (pItem->pItemData->dwQuality >= ITEM_QUALITY_RARE && !pTxt->nRare)
						continue;
					//Firstly check Itemtype
					bool found_itype = false;
					bool found_etype = false;

					for (int j = 0; j < 5; ++j)
					{
						if (!pTxt->wEType[j] || pTxt->wEType[j] == 0xFFFF)
							break;
						if (D2COMMON_IsMatchingType(pItem, pTxt->wEType[j])) {
							found_etype = true;
							break;
						}
					}
					if (found_etype) // next if excluded type
						continue;

					for (int j = 0; j < 7; ++j)
					{
						if (!pTxt->wIType[j] || pTxt->wIType[j] == 0xFFFF)
							break;
						if (D2COMMON_IsMatchingType(pItem, pTxt->wIType[j])) {
							found_itype = true;
							break;
						}
					}
					if (!found_itype)
						continue;

					stat = GetItemsTxtStatByMod(pTxt->hMods, 3, nStat, nStatParam);
					if (!stat)
						continue;
					min = min == 0 ? stat->dwMin : MIN(stat->dwMin, min);
					max = MAX(stat->dwMax, max);
					//DEBUGMSG(L"%s: update min to %d, and max to %d (record #%d)", wOut, min, max, i)
				}
				if (min < max) {
					int	aLen = wcslen(wOut);
					int leftSpace = 128 - aLen > 0 ? 128 - aLen : 0;
					if (nStat == STAT_LIFEPERLEVEL || nStat == STAT_MANAPERLEVEL || nStat == STAT_MAXENHANCEDDMGPERLEVEL || nStat == STAT_MAXDAMAGEPERLEVEL)
					{
						min = D2COMMON_GetBaseStatSigned(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0) * min >> 3;
						max = D2COMMON_GetBaseStatSigned(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0) * max >> 3;
					}
					if (leftSpace)
						swprintf_s(wOut + aLen, leftSpace, L" %s[%d - %d]%s", L"ÿc9", min, max, L"ÿc3");
				}
			}

		} break;

		}
	}
}

BOOL __stdcall ItemProperties::OnDamagePropertyBuild(UnitAny* pItem, DamageStats* pDmgStats, int nStat, wchar_t * wOut)
{
	wchar_t newDesc[128];

	// Ignore a max stat, use just a min dmg prop to gen the property string
	if (nStat == STAT_MAXIMUMFIREDAMAGE || nStat == STAT_MAXIMUMCOLDDAMAGE || nStat == STAT_MAXIMUMLIGHTNINGDAMAGE || nStat == STAT_MAXIMUMMAGICALDAMAGE ||
		nStat == STAT_MAXIMUMPOISONDAMAGE || nStat == STAT_POISONDAMAGELENGTH || nStat == STAT_ENHANCEDMAXIMUMDAMAGE)
		return TRUE;

	int stat_min, stat_max;
	wchar_t* szProp = 0;
	bool ranged = true;
	if (nStat == STAT_MINIMUMFIREDAMAGE) {
		if (pDmgStats->nFireDmgRange == 0)
			return FALSE;
		stat_min = pDmgStats->nMinFireDmg;
		stat_max = pDmgStats->nMaxFireDmg;
		if (stat_min >= stat_max) {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODFIREDAMAGE);
			ranged = false;
		}
		else {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODFIREDAMAGERANGE);
		}
	}
	else if (nStat == STAT_MINIMUMCOLDDAMAGE) {
		if (pDmgStats->nColdDmgRange == 0)
			return FALSE;
		stat_min = pDmgStats->nMinColdDmg;
		stat_max = pDmgStats->nMaxColdDmg;
		if (stat_min >= stat_max) {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODCOLDDAMAGE);
			ranged = false;
		}
		else {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODCOLDDAMAGERANGE);
		}
	}
	else if (nStat == STAT_MINIMUMLIGHTNINGDAMAGE) {
		if (pDmgStats->nLightDmgRange == 0)
			return FALSE;
		stat_min = pDmgStats->nMinLightDmg;
		stat_max = pDmgStats->nMaxLightDmg;
		if (stat_min >= stat_max) {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODLIGHTNINGDAMAGE);
			ranged = false;
		}
		else {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODLIGHTNINGDAMAGERANGE);
		}
	}
	else if (nStat == STAT_MINIMUMMAGICALDAMAGE) {
		if (pDmgStats->nMagicDmgRange == 0)
			return FALSE;
		stat_min = pDmgStats->nMinMagicDmg;
		stat_max = pDmgStats->nMaxMagicDmg;
		if (stat_min >= stat_max) {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODMAGICDAMAGE);
			ranged = false;
		}
		else {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODMAGICDAMAGERANGE);
		}
	}
	else if (nStat == STAT_MINIMUMPOISONDAMAGE) {
		if (pDmgStats->nPsnDmgRange == 0)
			return FALSE;
		if (pDmgStats->nPsnCount <= 0)
			pDmgStats->nPsnCount = 1;

		pDmgStats->nPsnLen = pDmgStats->nPsnLen / pDmgStats->nPsnCount;

		pDmgStats->nMinPsnDmg = stat_min = ((pDmgStats->nMinPsnDmg * pDmgStats->nPsnLen) + 128) / 256;
		pDmgStats->nMaxPsnDmg = stat_max = ((pDmgStats->nMaxPsnDmg * pDmgStats->nPsnLen) + 128) / 256;

		if (stat_min >= stat_max) {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODPOISONDAMAGE);
			swprintf_s(newDesc, 128, szProp, stat_max, pDmgStats->nPsnLen / 25); // Per frame
		}
		else {
			szProp = D2LANG_GetLocaleText(D2STR_STRMODPOISONDAMAGERANGE);
			swprintf_s(newDesc, 128, szProp, stat_min, stat_max, pDmgStats->nPsnLen / 25);
		}
		wcscat_s(wOut, 1024, newDesc);
		return TRUE;
	}
	else if (nStat == STAT_SECONDARYMAXIMUMDAMAGE) {
		if (pDmgStats->dword14)
			return TRUE;
		return pDmgStats->nDmgRange;
	}
	else if (nStat == STAT_MINIMUMDAMAGE || nStat == STAT_MAXIMUMDAMAGE || nStat == STAT_SECONDARYMINIMUMDAMAGE) {
		if (pDmgStats->dword14)
			return TRUE;
		if (!pDmgStats->nDmgRange)
			return FALSE;

		stat_min = pDmgStats->nMinLightDmg;
		stat_max = pDmgStats->nMaxLightDmg;

		if (stat_min >= stat_max) {
			pDmgStats->dword14 = TRUE;
			pDmgStats->nDmgRange = 0;
			return FALSE;
		}
		else {
			pDmgStats->dword14 = TRUE;
			szProp = D2LANG_GetLocaleText(D2STR_STRMODMINDAMAGERANGE);

		}
	}
	else if (nStat == STAT_ENHANCEDMINIMUMDAMAGE) {
		if (!pDmgStats->nDmgPercentRange)
			return false;
		stat_min = pDmgStats->nMinDmgPercent;
		stat_max = (int)(D2LANG_GetLocaleText(10023)); // "Enhanced damage"
		szProp = L"+%d%% %s\n";
	}

	if (!szProp)
		return FALSE;

	if (ranged) {
		swprintf_s(newDesc, 128, szProp, stat_min, stat_max);
	}
	else {
		swprintf_s(newDesc, 128, szProp, stat_max);
	}

	// <!--
	if (newDesc[wcslen(newDesc) - 1] == L'\n')
		newDesc[wcslen(newDesc) - 1] = L'\0';
	if (newDesc[wcslen(newDesc) - 1] == L'\n')
		newDesc[wcslen(newDesc) - 1] = L'\0';
	OnPropertyBuild(newDesc, nStat, pItem, NULL);
	// Beside this add-on the function is almost 1:1 copy of Blizzard's one -->
	wcscat_s(wOut, 1024, newDesc);
	wcscat_s(wOut, 1024, L"\n");
	return TRUE;
}

__declspec(naked) void __fastcall D2CLIENT_Properties()
{
	__asm
	{
		push eax
		call ItemProperties::DrawProperties
		add esp, 0x808
		ret 12
	}
}

__declspec(naked) void D2CLIENT_GetPropertyStringDamage_STUB()
{
	__asm
	{
		push[esp + 8]			// wOut
		push[esp + 8]			// nStat
		push eax				// pStats
		push[esp - 0x20 + 12]	// pItem
		call ItemProperties::OnDamagePropertyBuild
		ret 8
	}
}

__declspec(naked) void D2CLIENT_GetPropertyString_STUB() {
	static DWORD rtn = 0; // if something is stupid but works then it's not stupid!
	__asm
	{
		pop rtn
		// Firstrly generate string using old function
		call D2CLIENT_ParseStats_J
		push rtn

		push[esp - 4] // preserve nStatParam

		push eax // Store result
		mov eax, [esp - 0x10 + 8 + 4] // pItem
		push ecx
		push edx

		// Then pass the output to our func
		push[esp + 12] // nStatParam
		push eax // pItem
		push ebx // nStat
		push esi // wOut

		call ItemProperties::OnPropertyBuild

		pop edx
		pop ecx
		pop eax

		add esp, 4 // clean nStatParam

		ret
	}
}