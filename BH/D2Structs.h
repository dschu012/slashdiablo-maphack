#pragma once
#ifndef _D2STRUCTS_H
#define _D2STRUCTS_H

#include <windows.h>

#pragma warning ( push )
#pragma warning ( disable: 4201 )
#pragma optimize ( "", off )

struct UnitAny;
struct Room1;
struct Room2;
struct Level;
struct Act;
struct ActMisc;
struct RosterUnit;
struct OverheadMsg;

struct InventoryInfo {
	int nLocation;
	int nMaxXCells;
	int nMaxYCells;
};

struct GameStructInfo {
	BYTE _1[0x1B];					//0x00
	char szGameName[0x18];			//0x1B
	char szGameServerIp[0x56];		//0x33
	char szAccountName[0x30];		//0x89
	char szCharName[0x18];			//0xB9
	char szRealmName[0x18];			//0xD1
	BYTE _2[0x158];					//0xE9
	char szGamePassword[0x18];		//0x241
};

struct AutomapCell {
	DWORD fSaved;					//0x00
	WORD nCellNo;					//0x04
	WORD xPixel;					//0x06
	WORD yPixel;					//0x08
	WORD wWeight;					//0x0A
	AutomapCell *pLess;				//0x0C
	AutomapCell *pMore;				//0x10
};

struct GfxCell {
	DWORD flags;					//0x00
	DWORD width;					//0x04
	DWORD height;					//0x08
	DWORD xoffs;					//0x0C
	DWORD yoffs;					//0x10
	DWORD _2;						//0x14
	DWORD lpParent;					//0x18
	DWORD length;					//0x1C
	BYTE cols;						//0x20
};

struct InteractStruct {
	DWORD dwMoveType;			//0x00
	UnitAny* lpPlayerUnit;		//0x04
	UnitAny* lpTargetUnit;		//0x08
	DWORD dwTargetX;			//0x0C
	DWORD dwTargetY;			//0x10
	DWORD _1;					//0x14
	DWORD _2;					//0x18
};

struct CellFile {
	DWORD dwVersion;				//0x00
	struct {
		WORD dwFlags;
		BYTE mylastcol;
		BYTE mytabno:1;
	};								//0x04
	DWORD eFormat;					//0x08
	DWORD termination;				//0x0C
	DWORD numdirs;					//0x10
	DWORD numcells;					//0x14
	GfxCell *cells[1];				//0x18
};

struct CellContext {
	DWORD nCellNo;					//0x00
	DWORD _1[12];					//0x04
	CellFile* pCellFile;			//0x34
};

struct AutomapLayer {
	DWORD nLayerNo;					//0x00
	DWORD fSaved;					//0x04
	AutomapCell *pFloors;			//0x08
	AutomapCell *pWalls;			//0x0C
	AutomapCell *pObjects;			//0x10
	AutomapCell *pExtras;			//0x14
	AutomapLayer *pNextLayer;		//0x18
};

struct AutomapLayer2 {
	DWORD _1[2];					//0x00
	DWORD nLayerNo;					//0x08
};

struct LevelText {
	DWORD dwLevelNo;				//0x00
	DWORD _1[60];					//0x04
	BYTE _2;						//0xF4
	char szName[40];				//0xF5
	char szEntranceText[40];		//0x11D
	char szLevelDesc[41];			//0x145
	wchar_t wName[40];				//0x16E
	wchar_t wEntranceText[40];		//0x1BE
	BYTE nObjGroup[8];				//0x196
	BYTE nObjPrb[8];				//0x19E
};

struct ControlPreferences
{
	DWORD dwType;//0x00
	// ..
};

struct ControlText {
	wchar_t* wText; //0x00
	wchar_t* wText2;//0x04
	DWORD _1[3];	//0x08
	DWORD dwColor;	//0x14
	DWORD _2;		//0x18
	ControlText* pNext;//0x1C
};

struct Control {
   DWORD dwType;					//0x00
   CellFile *pCellFile;				//0x04
   DWORD dwDisabled;				//0x08
   DWORD dwPosX;					//0x0C
   DWORD dwPosY;					//0x10
   DWORD dwSizeX;					//0x14
   DWORD dwSizeY;					//0x18
   VOID (__fastcall *Initialize)(Control* pControl);//0x1c
   DWORD _3;						//0x20
   DWORD *_4;						//0x24
   DWORD *_5;						//0x28
   DWORD _6;						//0x2C
   DWORD *_7;						//0x30
   DWORD *_8;						//0x34
   DWORD _9;						//0x38
   Control* pNext;					//0x3C
   DWORD _10;						//0x40
   DWORD dwMaxLength;				//0x44
   union {
	   ControlText* pFirstText;		//0x48
	   DWORD dwScrollEntries;		//0x48
   };
   union {
       ControlText* pLastText;		//0x4C
	   DWORD dwScrollPosition;		//0x4C
   };
   ControlText* pSelectedText;		//0x50
   DWORD dwSelectEnd;				//0x54
   DWORD dwSelectStart;				//0x58
   wchar_t wText[0x1A];				//0x5C
   Control* pChildControl;			//0x90
};

struct MonStatsTxt // size 0x1A8
{
	WORD	wId;						//0x00
	WORD	wBaseId;					//0x02
	WORD	wNextInClass;				//0x04
	WORD	wNameStr;					//0x06
	WORD	wDescStr;					//0x08
	WORD	_1a;						//0x0A
	struct {
		BYTE	bisSpawn : 1;						//1
		BYTE	bisMelee : 1;						//2
		BYTE	bnoRatio : 1;						//3
		BYTE	bOpenDoors : 1;					//4
		BYTE	bSetBoss : 1;						//5
		BYTE	bBossXfer : 1;					//6
		BYTE	bBossXfer2 : 1;					//7
		BYTE	bPrimeEvil : 1;					//8
		BYTE	bNPC : 1;							//9
		BYTE	bInteract : 1;					//10
		BYTE	binTown : 1;						//11
		BYTE	blUndead : 1;						//12
		BYTE	bhUndead : 1;						//13
		BYTE	bDemon : 1;						//14
		BYTE	bFlying : 1;						//15
		BYTE	bKillable : 1;					//16
		BYTE	bSwitchAI : 1;					//17
		BYTE	bNoMultiShot : 1;					//18
		BYTE	bNeverCount : 1;					//19
		BYTE	bPetIgnore : 1;					//20
		BYTE	bDeathDmg : 1;					//21
		BYTE	bGenericSpawn : 1;				//22
		BYTE	bZoo : 1;							//23
		BYTE	bPlaceSpawn : 1;					//24
		BYTE	bInventory : 1;					//25
		BYTE	bEnabled : 1;						//26
		BYTE	bNoShldBlock : 1;					//27
		BYTE	bNoAura : 1;						//28
		BYTE	bRangedType : 1;					//29
	} dwFlags;							//0x0C
	DWORD	dwCode;						//0x10
	WORD	wMonSound;					//0x14
	WORD	wUMonSound;					//0x16
	WORD	wMonStatsEx;				//0x18
	WORD	wMonProp;					//0x1A
	WORD	wMonType;					//0x1C
	WORD	wAI;						//0x1E
	WORD	wSpawn;						//0x20
	BYTE	bSpawnX;					//0x22
	BYTE	bSpawnY;					//0x23
	WORD	bSpawnMode;					//0x24
	WORD	wMinion1;					//0x26
	WORD	wMinion2;					//0x28
	WORD	_1;							//0x2A
	BYTE	bPartyMin;					//0x2C
	BYTE	bPartyMax;					//0x2D
	BYTE	bRarity;					//0x2E
	BYTE	bMinGrp;					//0x2F
	BYTE	bMaxGrp;					//0x30
	BYTE	bSparsePopulate;			//0x31
	WORD	wVelocity;					//0x32
	WORD	wRun;						//0x34
	WORD	_2;							//0x36
	WORD	_2b;						//0x38
	WORD	wMissA1;					//0x3A
	WORD	wMissA2;					//0x3C
	WORD	wMissS1;					//0x3E
	WORD	wMissS2;					//0x40
	WORD	wMissS3;					//0x42
	WORD	wMissS4;					//0x44
	WORD	wMissC;						//0x46
	WORD	wMissSQ;					//0x48
	WORD	_3;							//0x4A
	BYTE	bAlign;						//0x4C
	BYTE	bTransLvl;					//0x4D
	BYTE	bThreat;					//0x4E
	BYTE	bAIdel;						//0x4F
	BYTE	bAIdel_N;					//0x50
	BYTE	bAIdel_H;					//0x51
	BYTE	bAiDist;					//0x52
	BYTE	bAiDist_N;					//0x53
	WORD	bAiDist_H;					//0x54
	WORD	wAiP1;						//0x56
	WORD	wAiP1_N;					//0x58
	WORD	wAiP1_H;					//0x5A
	WORD	wAiP2;						//0x5C
	WORD	wAiP2_N;					//0x5E
	WORD	wAiP2_H;					//0x60
	WORD	wAiP3;						//0x62
	WORD	wAiP3_N;					//0x64
	WORD	wAiP3_H;					//0x66
	WORD	wAiP4;						//0x68
	WORD	wAiP4_N;					//0x6A
	WORD	wAiP4_H;					//0x6C
	WORD	wAiP5;						//0x6E
	WORD	wAiP5_N;					//0x70
	WORD	wAiP5_H;					//0x72
	WORD	wAiP6;						//0x74
	WORD	wAiP6_N;					//0x76
	WORD	wAiP6_H;					//0x78
	WORD	wAiP7;						//0x7A
	WORD	wAiP7_N;					//0x7C
	WORD	wAiP7_H;					//0x7E
	WORD	wAiP8;						//0x80
	WORD	wAiP8_N;					//0x82
	WORD	wAiP8_H;					//0x84
	WORD	wTreasureClass1;			//0x86
	WORD	wTreasureClass2;			//0x88
	WORD	wTreasureClass3;			//0x8A
	WORD	wTreasureClass4;			//0x8C
	WORD	wTreasureClass1_N;			//0x8E
	WORD	wTreasureClass2_N;			//0x90
	WORD	wTreasureClass3_N;			//0x92
	WORD	wTreasureClass4_N;			//0x94
	WORD	wTreasureClass1_H;			//0x96
	WORD	wTreasureClass2_H;			//0x98
	WORD	wTreasureClass3_H;			//0x9A
	WORD	wTreasureClass4_H;			//0x9C
	BYTE	bTCQuestId;					//0x9E
	BYTE	bTCQuestCP;					//0x9F
	BYTE	bDrain;						//0xA0
	BYTE	bDrain_N;					//0xA1
	BYTE	bDrain_H;					//0xA2
	BYTE	bToBlock;					//0xA3
	BYTE	bToBlock_N;					//0xA4
	BYTE	bToBlock_H;					//0xA5
	WORD	bCrit;						//0xA6
	WORD	wSkillDamage;				//0xA8
	WORD	wLevel;						//0xAA
	WORD	wLevel_N;					//0xAC
	WORD	wLevel_H;					//0xAE
	WORD	wMinHP;						//0xB0
	WORD	wMinHP_N;					//0xB2
	WORD	wMinHP_H;					//0xB4
	WORD	wMaxHP;						//0xB6
	WORD	wMaxHP_N;					//0xB8
	WORD	wMaxHP_H;					//0xBA
	WORD	wAC;						//0xBC
	WORD	wAC_N;						//0xBE
	WORD	wAC_H;						//0xC0
	WORD	wA1TH;						//0xC2
	WORD	wA1TH_N;					//0xC4
	WORD	wA1TH_H;					//0xC6
	WORD	wA2TH;						//0xC8
	WORD	wA2TH_N;					//0xCA
	WORD	wA2TH_H;					//0xCC
	WORD	wS1TH;						//0xCE
	WORD	wS1TH_N;					//0xD0
	WORD	wS1TH_H;					//0xD2
	WORD	wExp;						//0xD4
	WORD	wExp_N;						//0xD6
	WORD	wExp_H;						//0xD8
	WORD	wA1MinD;					//0xDA
	WORD	wA1MinD_N;					//0xDC
	WORD	wA1MinD_H;					//0xDE
	WORD	wA1MaxD;					//0xE0
	WORD	wA1MaxD_N;					//0xE2
	WORD	wA1MaxD_H;					//0xE4
	WORD	wA2MinD;					//0xE6
	WORD	wA2MinD_N;					//0xE8
	WORD	wA2MinD_H;					//0xEA
	WORD	wA2MaxD;					//0xEC
	WORD	wA2MaxD_N;					//0xEE
	WORD	wA2MaxD_H;					//0xF0
	WORD	wS1MinD;					//0xF2
	WORD	wS1MinD_N;					//0xF4
	WORD	wS1MinD_H;					//0xF6
	WORD	wS1MaxD;					//0xF8
	WORD	wS1MaxD_N;					//0xFA
	WORD	wS1MaxD_H;					//0xFC
	BYTE	bEl1Mode;					//0xFE
	BYTE	bEl2Mode;					//0xFF
	BYTE	bEl3Mode;					//0x100
	BYTE	bEl1Type;					//0x101
	BYTE	bEl2Type;					//0x102
	BYTE	bEl3Type;					//0x103
	BYTE	bEl1Pct;					//0x104
	BYTE	bEl1Pct_N;					//0x105
	BYTE	bEl1Pct_H;					//0x106
	BYTE	bEl2Pct;					//0x107
	BYTE	bEl2Pct_N;					//0x108
	BYTE	bEl2Pct_H;					//0x109
	BYTE	bEl3Pct;					//0x10A
	BYTE	bEl3Pct_N;					//0x10B
	BYTE	bEl3Pct_H;					//0x10C
	BYTE	_4;							//0x10D
	WORD	wEl1MinD;					//0x10E
	WORD	wEl1MinD_N;					//0x110
	WORD	wEl1MinD_H;					//0x112
	WORD	wEl2MinD;					//0x114
	WORD	wEl2MinD_N;					//0x116
	WORD	wEl2MinD_H;					//0x118
	WORD	wEl3MinD;					//0x11A
	WORD	wEl3MinD_N;					//0x11C
	WORD	wEl3MinD_H;					//0x11E
	WORD	wEl1MaxD;					//0x120
	WORD	wEl1MaxD_N;					//0x122
	WORD	wEl1MaxD_H;					//0x124
	WORD	wEl2MaxD;					//0x126
	WORD	wEl2MaxD_N;					//0x128
	WORD	wEl2MaxD_H;					//0x12A
	WORD	wEl3MaxD;					//0x12C
	WORD	wEl3MaxD_N;					//0x12E
	WORD	wEl3MaxD_H;					//0x130
	WORD	wEl1Dur;					//0x132
	WORD	wEl1Dur_N;					//0x134
	WORD	wEl1Dur_H;					//0x136
	WORD	wEl2Dur;					//0x138
	WORD	wEl2Dur_N;					//0x13A
	WORD	wEl2Dur_H;					//0x13C
	WORD	wEl3Dur;					//0x13E
	WORD	wEl3Dur_N;					//0x140
	WORD	wEl3Dur_H;					//0x142
	WORD	wResDmg;					//0x144
	WORD	wResDmg_N;					//0x146
	WORD	wResDmg_H;					//0x148
	WORD	wResMagic;					//0x14A
	WORD	wResMagic_N;				//0x14C
	WORD	wResMagic_H;				//0x14E
	WORD	wResFire;					//0x150
	WORD	wResFire_N;					//0x152
	WORD	wResFire_H;					//0x154
	WORD	wResLight;					//0x156
	WORD	wResLight_N;				//0x158
	WORD	wResLight_H;				//0x15A
	WORD	wResCold;					//0x15C
	WORD	wResCold_N;					//0x15E
	WORD	wResCold_H;					//0x160
	WORD	wResPoison;					//0x162
	WORD	wResPoison_N;				//0x164
	WORD	wResPoiosn_H;				//0x166
	BYTE	bColdEffect;				//0x168
	BYTE	bColdEffect_N;				//0x169
	WORD	bColdEffect_H;				//0x16A
	DWORD	dwSendSkills;				//0x16C
	WORD	wSkill1;					//0x170
	WORD	wSkill2;					//0x172
	WORD	wSkill3;					//0x174
	WORD	wSkill4;					//0x176
	WORD	wSkill5;					//0x178
	WORD	wSkill6;					//0x17A
	WORD	wSkill7;					//0x17C
	WORD	wSkill8;					//0x17E
	DWORD   _5[6];						//0x180
	BYTE	bSk1lvl;					//0x198
	BYTE	bSk2lvl;					//0x199
	BYTE	bSk3lvl;					//0x19A
	BYTE	bSk4lvl;					//0x19B
	BYTE	bSk5lvl;					//0x19C
	BYTE	bSk6lvl;					//0x19D
	BYTE	bSk7lvl;					//0x19E
	BYTE	bSk8lvl;					//0x19F
	DWORD	dwDamageRegen;				//0x1A0
	BYTE	bSplEndDeath;				//0x1A4
	BYTE	bSplGetModeChart;			//0x1A5
	BYTE	bSplEndGeneric;				//0x1A6
	BYTE	bSplClientEnd;				//0x1A7
};

#pragma pack(push)
#pragma pack(1)

struct DamageStats
{
	DWORD nMinDmg;
	DWORD nMaxDmg;
	DWORD dword8;
	DWORD dwordC;
	BOOL nDmgRange;
	DWORD dword14;
	DWORD nMinDmgPercent;
	DWORD nMaxDmgPercent;
	DWORD dword20;
	DWORD dword24;
	BOOL nDmgPercentRange;
	DWORD dword2C;
	DWORD nMinColdDmg;
	DWORD nMaxColdDmg;
	DWORD dword38;
	DWORD dword3C;
	DWORD nColdDmgRange;
	DWORD dword44;
	DWORD nMinLightDmg;
	DWORD nMaxLightDmg;
	DWORD dword50;
	DWORD dword54;
	DWORD nLightDmgRange;
	DWORD dword5C;
	DWORD nMinFireDmg;
	DWORD nMaxFireDmg;
	DWORD dword68;
	DWORD dword6C;
	DWORD nFireDmgRange;
	DWORD dword74;
	DWORD nMinPsnDmg;
	DWORD nMaxPsnDmg;
	DWORD nPsnLen;
	DWORD nPsnCount;
	DWORD nPsnDmgRange;
	DWORD dword8C;
	DWORD nMinMagicDmg;
	DWORD nMaxMagicDmg;
	DWORD dword98;
	DWORD dword9C;
	DWORD nMagicDmgRange;
	DWORD dwordA4;
};

struct RoomTile {
	Room2* pRoom2;				//0x00
	RoomTile* pNext; 			//0x04
	DWORD _2[2];				//0x08
	DWORD *nNum; 				//0x10
};

struct RosterUnit {
	char szName[16];				//0x00
	DWORD dwUnitId;					//0x10
	DWORD dwPartyLife;				//0x14
	DWORD _1;						//0x18
	DWORD dwClassId;                //0x1C
	WORD wLevel;					//0x20
	WORD wPartyId;  				//0x22
	DWORD dwLevelId;                //0x24
	DWORD Xpos;						//0x28
	DWORD Ypos;						//0x2C
	DWORD dwPartyFlags;				//0x30
	BYTE * _5;						//0x34
	DWORD _6[11];					//0x38
	WORD _7;						//0x64
	char szName2[16];				//0x66
	WORD _8;						//0x76
	DWORD _9[2];					//0x78
	RosterUnit * pNext;				//0x80
};

struct QuestInfo {
	void *pBuffer;					//0x00
	DWORD _1;						//0x04
};

struct Waypoint {
	BYTE flags;						//0x00
};

struct PlayerData {
	char szName[0x10];				//0x00
	QuestInfo *pNormalQuest;		//0x10
	QuestInfo *pNightmareQuest;		//0x14
	QuestInfo *pHellQuest;			//0x18
	Waypoint *pNormalWaypoint;		//0x1c
	Waypoint *pNightmareWaypoint;	//0x20
	Waypoint *pHellWaypoint;		//0x24
};

struct CollMap {
	DWORD dwPosGameX;				//0x00
	DWORD dwPosGameY;				//0x04
	DWORD dwSizeGameX;				//0x08
	DWORD dwSizeGameY;				//0x0C
	DWORD dwPosRoomX;				//0x10
	DWORD dwPosRoomY;				//0x14
	DWORD dwSizeRoomX;				//0x18
	DWORD dwSizeRoomY;				//0x1C
	WORD *pMapStart;				//0x20
	WORD *pMapEnd;					//0x22
};

struct PresetUnit {
	DWORD _1;						//0x00
	DWORD dwTxtFileNo;				//0x04
	DWORD dwPosX;					//0x08
	PresetUnit* pPresetNext;		//0x0C
	DWORD _3;						//0x10
	DWORD dwType;					//0x14
	DWORD dwPosY;					//0x18
};

struct Level {
	DWORD _1[4];			//0x00
	Room2* pRoom2First;		//0x10
	DWORD _2[2];			//0x14
	DWORD dwPosX;			//0x1C
	DWORD dwPosY;			//0x20
	DWORD dwSizeX;			//0x24
	DWORD dwSizeY;			//0x28
	DWORD _3[96];			//0x2C
	Level* pNextLevel;		//0x1AC
	DWORD _4;				//0x1B0
	ActMisc* pMisc;			//0x1B4
	DWORD _5[6];			//0x1BC
	DWORD dwLevelNo;		//0x1D0
};

struct Room2 {
	DWORD _1[2];			//0x00
	Room2** pRoom2Near;		//0x08
	DWORD _2[5];			//0x0C
	struct {
		DWORD dwRoomNumber; //0x00
		DWORD _1;			//0x04
		DWORD* pdwSubNumber;//0x08
	} *pType2Info;			//0x20
	Room2* pRoom2Next;		//0x24
	DWORD dwRoomFlags;		//0x28
	DWORD dwRoomsNear;		//0x2C
	Room1* pRoom1;			//0x30
	DWORD dwPosX;			//0x34
	DWORD dwPosY;			//0x38
	DWORD dwSizeX;			//0x3C
	DWORD dwSizeY;			//0x40
	DWORD _3;				//0x44
	DWORD dwPresetType;		//0x48
	RoomTile* pRoomTiles;	//0x4C
	DWORD _4[2];			//0x50
	Level* pLevel;			//0x58
	PresetUnit* pPreset;	//0x5C
};

#pragma pack(pop)

struct Room1 {
	Room1** pRoomsNear; 	//0x00
	DWORD _1[3];			//0x04
	Room2* pRoom2;			//0x10
	DWORD _2[3];			//0x14
	CollMap* Coll;			//0x20
	DWORD dwRoomsNear;		//0x24
	DWORD _3[9];			//0x28
	DWORD dwXStart;			//0x4C
	DWORD dwYStart;			//0x50
	DWORD dwXSize;			//0x54
	DWORD dwYSize;			//0x58
	DWORD _4[6];			//0x5C
	UnitAny* pUnitFirst;	//0x74
	DWORD _5;				//0x78
	Room1* pRoomNext;		//0x7C
};

struct ActMisc {
	DWORD _1[37];			//0x00
	DWORD dwStaffTombLevel; //0x94
	DWORD _2[245];			//0x98
	Act* pAct;				//0x46C
	DWORD _3[3];			//0x470
	Level* pLevelFirst;		//0x47C
};

struct Act {
	DWORD _1[3];			//0x00
	DWORD dwMapSeed;		//0x0C
	Room1* pRoom1;			//0x10
	DWORD dwAct;			//0x14
	DWORD _2[12];			//0x18
	ActMisc* pMisc;			//0x48
};

struct Path {
	WORD xOffset;					//0x00
	WORD xPos;						//0x02
	WORD yOffset;					//0x04
	WORD yPos;						//0x06
	DWORD _1[2];					//0x08
	WORD xTarget;					//0x10
	WORD yTarget;					//0x12
	DWORD _2[2];					//0x14
	Room1 *pRoom1;					//0x1C
	Room1 *pRoomUnk;				//0x20
	DWORD _3[3];					//0x24
	UnitAny *pUnit;					//0x30
	DWORD dwFlags;					//0x34
	DWORD _4;						//0x38
	DWORD dwPathType;				//0x3C
	DWORD dwPrevPathType;			//0x40
	DWORD dwUnitSize;				//0x44
	DWORD _5[4];					//0x48
	UnitAny *pTargetUnit;			//0x58
	DWORD dwTargetType;				//0x5C
	DWORD dwTargetId;				//0x60
	BYTE bDirection;				//0x64
};

struct ItemPath {
	DWORD _1[3];					//0x00
	DWORD dwPosX;					//0x0C
	DWORD dwPosY;					//0x10
	//Use Path for the rest
};

struct Stat {
	WORD wSubIndex;					//0x00
	WORD wStatIndex;				//0x02
	DWORD dwStatValue;				//0x04
};

// Credits to SVR, http://phrozenkeep.hugelaser.com/forum/viewtopic.php?f=8&t=31458&p=224066
struct StatList {
	DWORD _1;						//0x00
	UnitAny* pUnit;					//0x04
	DWORD dwUnitType;				//0x08
	DWORD dwUnitId;					//0x0C
	DWORD dwFlags;					//0x10
	DWORD _2[4];					//0x14
	Stat *pStat;					//0x24
	WORD wStatCount1;				//0x28
	WORD wnSize;					//0x2A
	StatList *pPrevLink;			//0x2C
	DWORD _3;						//0x30
	StatList *pPrev;				//0x34
	DWORD _4;						//0x38
	StatList *pNext;				//0x3C
	StatList *pSetList;				//0x40
	DWORD _5;						//0x44
	Stat *pSetStat;					//0x48
	WORD wSetStatCount;				//0x4C
};

struct InventoryStore
{
	DWORD pFirstItem;				//0x00
	DWORD pLastItem;				//0x04
	BYTE Width;						//0x08
	BYTE Height;					//0x09
	BYTE unk[2];					//0x0A
	DWORD pArray;					//0x0C UnitAny* [height][width]
};

struct Inventory {
	DWORD dwSignature;				//0x00
	BYTE *bGame1C;					//0x04
	UnitAny *pOwner;				//0x08
	UnitAny *pFirstItem;			//0x0C
	UnitAny *pLastItem;				//0x10
	InventoryStore *pStores;		//0x14 InventoryStore* [count]
	DWORD dwStoresCount;			//0x18
	DWORD dwLeftItemUid;			//0x1C
	UnitAny *pCursorItem;			//0x20
	DWORD dwOwnerId;				//0x24
	DWORD dwItemCount;				//0x28
};

struct Light {
	DWORD _1[3];					//0x00
	DWORD dwType;					//0x0C
	DWORD _2[7];					//0x10
	DWORD dwStaticValid;			//0x2C
	int *pnStaticMap;				//0x30
};

struct SkillInfo {
	WORD wSkillId;					//0x00
};

struct Skill {
	SkillInfo *pSkillInfo;			//0x00
	Skill *pNextSkill;				//0x04
	DWORD _1[8];					//0x08
	DWORD dwSkillLevel;				//0x28
	DWORD _2[2];					//0x2C
	DWORD dwFlags;					//0x30
};

struct Info {
	BYTE *pGame1C;					//0x00
	Skill *pFirstSkill;				//0x04
	Skill *pLeftSkill;				//0x08
	Skill *pRightSkill;				//0x0C
};

struct ItemData {
	DWORD dwQuality;				//0x00
	DWORD _1[2];					//0x04
	DWORD dwItemFlags;				//0x0C 1 = Owned by player, 0xFFFFFFFF = Not owned
	DWORD _2[2];					//0x10
	DWORD dwFlags;					//0x18
	DWORD _3[3];					//0x1C
	DWORD dwQuality2;				//0x28
	DWORD dwItemLevel;				//0x2C
	WORD wVersion;					//0x30
	WORD wRarePrefix;				//0x32
	WORD wRareSuffix;				//0x34
	WORD wAutoPrefix;				//0x36
	WORD wPrefix[3];				//0x38
	WORD wSuffix[3];				//0x3E
	BYTE BodyLocation;				//0x44
	BYTE ItemLocation;				//0x45 Non-body/belt location (Body/Belt == 0xFF)
	BYTE EarLevel;					//0x46
	BYTE VarGfx;					//0x47
	CHAR personalizedName[16];		//0x4A
	WORD _10;						//0x5A
	Inventory *pOwnerInventory;		//0x5C
	UnitAny *pPrevInvItem;			//0x60
	UnitAny *pNextInvItem;			//0x64
	BYTE _11;						//0x68
	BYTE NodePage;					//0x69 Actual location, this is the most reliable by far
	WORD _12;						//0x6A
	DWORD _13[6];					//0x6C
	UnitAny *pOwner;				//0x84
};

struct ItemText {
	wchar_t szName2[0x40];			//0x00
	union {
		DWORD dwCode;
		char szCode[4];
	};								//0x40
	BYTE _uncharted1[0x54];			//0x44
	DWORD speed;					//0x98
	BYTE _uncharted2[0x18];			//0x9C
	WORD nLocaleTxtNo;				//0xB4
	BYTE _uncharted3[0x0E];			//0xB6
	WORD rangeadder;				//0xC4
	BYTE _uncharted4[0x09];			//0xC6
	BYTE xSize;						//0xCF
	BYTE ySize;						//0xD0
	BYTE _uncharted5[0x0d];			//0xD1
	BYTE nType;						//0xDE
	BYTE _uncharted6[0x0d];			//0xDF
	BYTE fQuest;					//0xEC
	BYTE _uncharted7[0x12];			//0xED
	BYTE reqlvl;					//0xFF 
	BYTE magiclvl;					//0x100
};

struct MonsterText {
	BYTE _1[0x6];					//0x00
	WORD nLocaleTxtNo;				//0x06
	WORD flag;						//0x08
	WORD _1a;						//0x0A
	union {
		DWORD flag1;				//0x0C
		struct {
			BYTE flag1a;			//0x0C
			BYTE flag1b;			//0x0D
			BYTE flag1c[2];			//0x0E
		};
	};
	BYTE _2[0x22];					//0x10
	WORD velocity;					//0x32
	BYTE _2a[0x52];					//0x34
	WORD tcs[3][4];					//0x86
	BYTE _2b[0x52];					//0x9E
	wchar_t szDescriptor[0x3c];		//0xF0
	BYTE _3[0x1a0];					//0x12C
};

struct MonsterData {
	MonStatsTxt* pMonStatsTxt;				//0x00
	BYTE Components[16];					//0x04
	WORD NameSeed;							//0x14
	struct
	{
		BYTE fUnk : 1;
		BYTE fNormal : 1;
		BYTE fChamp : 1;
		BYTE fBoss : 1;
		BYTE fMinion : 1;
	};				//0x16
	BYTE dwLastMode;				//0x17
	DWORD dwDuriel;					//0x18
	BYTE anEnchants[9];				//0x1C
	WORD wUniqueNo;					//0x26
	DWORD _5;						//0x28
	struct {
		wchar_t wName[28];
	};								//0x2C
};

struct ObjectTxt {
	char szName[0x40];				//0x00
	wchar_t wszName[0x40];			//0x40
	BYTE _1[4];						//0xC0
	BYTE nSelectable0;				//0xC4
	BYTE _2[0x87];					//0xC5
	BYTE nOrientation;				//0x14C
	BYTE _2b[0x19];					//0x14D
	BYTE nSubClass;					//0x166
	BYTE _3[0x11];					//0x167
	BYTE nParm0;					//0x178
	BYTE _4[0x39];					//0x179
	BYTE nPopulateFn;				//0x1B2
	BYTE nOperateFn;				//0x1B3
	BYTE _5[8];						//0x1B4
	DWORD nAutoMap;					//0x1BB
};

struct ObjectData {
	ObjectTxt *pTxt;				//0x00
	union {
		BYTE Type;					//0x04 (0x0F would be a Exp Shrine)
		struct {
			BYTE _1:7;
			BYTE ChestLocked:1;
		};
	};
	DWORD _2[8];					//0x08
	char szOwner[0x10];				//0x28
};

struct ObjectPath {
	Room1 *pRoom1;					//0x00
	DWORD _1[2];					//0x04
	DWORD dwPosX;					//0x0C
	DWORD dwPosY;					//0x10
	//Leaving rest undefined, use Path
};

struct UnitAny {
	DWORD dwType;					//0x00
	DWORD dwTxtFileNo;				//0x04
	DWORD _1;						//0x08
	DWORD dwUnitId;					//0x0C
	DWORD dwMode;					//0x10
	union
	{
		PlayerData *pPlayerData;
		ItemData *pItemData;
		MonsterData *pMonsterData;
		ObjectData *pObjectData;
		//TileData *pTileData doesn't appear to exist anymore
	};								//0x14
	DWORD dwAct;					//0x18
	Act *pAct;						//0x1C
	DWORD dwSeed[2];				//0x20
	DWORD _2;						//0x28
	union
	{
		Path *pPath;
		ItemPath *pItemPath;
		ObjectPath *pObjectPath;
	};								//0x2C
	DWORD _3[5];					//0x30
	DWORD dwGfxFrame;				//0x44
	DWORD dwFrameRemain;			//0x48
	WORD wFrameRate;				//0x4C
	WORD _4;						//0x4E
	BYTE *pGfxUnk;					//0x50
	DWORD *pGfxInfo;				//0x54
	DWORD _5;						//0x58
	StatList *pStats;				//0x5C
	Inventory *pInventory;			//0x60
	Light *ptLight;					//0x64
	DWORD _6[9];					//0x68
	WORD wX;						//0x8C
	WORD wY;						//0x8E
	DWORD _7;						//0x90
	DWORD dwOwnerType;				//0x94
	DWORD dwOwnerId;				//0x98
	DWORD _8[2];					//0x9C
	OverheadMsg* pOMsg;				//0xA4
	Info *pInfo;					//0xA8
	DWORD _9[6];					//0xAC
	DWORD dwFlags;					//0xC4
	DWORD dwFlags2;					//0xC8
	DWORD _10[5];					//0xCC
	UnitAny *pChangedNext;			//0xE0
	UnitAny *pRoomNext;				//0xE4
	UnitAny *pListNext;				//0xE8 -> 0xD8
};

struct BnetData {
	DWORD dwId;					//0x00
	DWORD dwId2;				//0x04	
	BYTE _12[13];				//0xC0
	//DWORD dwId3;				//0x14
	//WORD Unk3;					//0x18	
	BYTE _13[6];				//0xC0
	char szGameName[22];		//0x1A
	char szGameIP[16];			//0x30
	DWORD _2[15];				//0x40
	DWORD dwId4;				//0x80
	BYTE _3[5];					//0x84
	char szAccountName[48];		//0x88
	char szPlayerName[24];		//0xB8
	char szRealmName[8];		//0xD0
	BYTE _4[273];				//0xD8
	BYTE nCharClass;			//0x1E9
	BYTE nCharFlags;			//0x1EA
	BYTE nMaxLvlDifference;		//0x1EB
	BYTE _5[31];				//0x1EC
	BYTE nDifficulty;			//0x20B
	void *_6;					//0x20C
	DWORD _7[3];				//0x210
	WORD _8;					//0x224
	BYTE _9[7];					//0x226
	char szRealmName2[24];		//0x227
	char szGamePass[24];		//0x23F
	char szGameDesc[256];		//0x257
	WORD _10;					//0x348
	BYTE _11;					//0x34B
};


struct WardenClientRegion_t {
	DWORD cbAllocSize; //+00
	DWORD offsetFunc1; //+04
	DWORD offsetRelocAddressTable; //+08
	DWORD nRelocCount; //+0c
	DWORD offsetWardenSetup; //+10
	DWORD _2[2];
	DWORD offsetImportAddressTable; //+1c
	DWORD nImportDllCount; //+20
	DWORD nSectionCount; //+24
};

struct SMemBlock_t {
	DWORD _1[6];
	DWORD cbSize; //+18
	DWORD _2[31];
	BYTE data[1]; //+98
};

struct WardenClient_t {
	WardenClientRegion_t* pWardenRegion; //+00
	DWORD cbSize; //+04
	DWORD nModuleCount; //+08
	DWORD param; //+0c
	DWORD fnSetupWarden; //+10
};

struct WardenIATInfo_t {
	DWORD offsetModuleName;
	DWORD offsetImportTable;
};

struct AttackStruct {
	DWORD dwAttackType;			//0x00
	UnitAny* lpPlayerUnit;		//0x04
	UnitAny* lpTargetUnit;		//0x08
	DWORD dwTargetX;			//0x0C
	DWORD dwTargetY;			//0x10
	DWORD _1;					//0x14
	DWORD _2;					//0x18
};

#pragma pack(push)
#pragma pack(1)

struct NPCMenu {
	DWORD dwNPCClassId;
	DWORD dwEntryAmount;
	WORD wEntryId1;
	WORD wEntryId2;
	WORD wEntryId3;
	WORD wEntryId4;	
	WORD _1;
	DWORD dwEntryFunc1;
	DWORD dwEntryFunc2; 
	DWORD dwEntryFunc3; 
	DWORD dwEntryFunc4;
	BYTE _2[5];
};

struct OverheadMsg {
	DWORD _1;
	DWORD dwTrigger;
	DWORD _2[2];
	char Msg[232];
};

#pragma pack(pop)

struct D2MSG {
	HWND myHWND;
	char lpBuf[256];
};


struct InventoryLayout {
	BYTE SlotWidth;
	BYTE SlotHeight;
	BYTE unk1;
	BYTE unk2;
	DWORD Left;
	DWORD Right;
	DWORD Top;
	DWORD Bottom;
	BYTE SlotPixelWidth;
	BYTE SlotPixelHeight;
};

struct LvlMazeTxt
{
	DWORD dwLevelId;                //0x00
	DWORD dwRooms[3];               //0x04
	DWORD dwSizeX;                  //0x10
	DWORD dwSizeY;                  //0x14
	DWORD dwMerge;                  //0x18
};

struct LvlWarpTxt
{
	DWORD dwLevelId;
	DWORD dwSelectX;
	DWORD dwSelectY;
	DWORD dwSelectDX;
	DWORD dwSelectDY;
	DWORD dwExitWalkX;
	DWORD dwExitWalkY;
	DWORD dwOffsetX;
	DWORD dwOffsetY;
	DWORD dwLitVersion;
	DWORD dwTiles;
	DWORD dwDirection;
};


struct PropertiesTxt
{
	WORD wProp;                   //0x00
	BYTE nSet[8];                 //0x02
	WORD wVal[7];                 //0x0A
	BYTE nFunc[8];                //0x18
	WORD wStat[7];                //0x20
};

#pragma pack(push)
#pragma pack(1)
//these might be duplicated with other names???
struct ItemsTxtStat
{
	DWORD dwProp;                 //0x00
	DWORD dwPar;                  //0x04
	int dwMin;					  //0x08
	int dwMax;			          //0x0C
};

struct AutoMagicTxt
{
	char szName[31];                //0x00
	BYTE _1;						//0x1F
	WORD wIndex;	                //0x20
	WORD wVersion;                  //0x22
	ItemsTxtStat hMods[3];          //0x24
	WORD wSpawnable;                //0x54
	WORD wTransformColor;           //0x56
	DWORD dwLevel;                  //0x58
	DWORD dwGroup;                  //0x5C
	DWORD dwMaxLevel;               //0x60
	BYTE nRare;                     //0x64
	BYTE nLevelReq;                 //0x65
	BYTE nClassSpecific;            //0x66
	BYTE nClass;                    //0x67
	WORD wClassLevelReq;            //0x68
	WORD wIType[7];                 //0x6A
	WORD wEType[5];                 //0x78
	BYTE bFrequency;                //0x82
	BYTE _2;						//0x83
	DWORD dwDivide;                 //0x84
	DWORD dwMultiply;               //0x88
	DWORD dwAdd;                    //0x8C
};


struct SetItemsTxt
{
	WORD wSetItemId;               //0x00
	char szName[32];               //0x02
	WORD _1;	                   //0x22
	DWORD dwTblIndex;              //0x24
	union
	{
		DWORD dwCode;
		char szCode[4];
	};							   //0x28
	DWORD _2;	                   //0x2C
	WORD wLvl;                     //0x30
	WORD wLvlReq;                  //0x32
	DWORD dwRarity;                //0x34
	DWORD dwCostMult;              //0x38
	DWORD dwCostAdd;               //0x3C
	BYTE nChrTransform;            //0x40
	BYTE nInvTransform;            //0x41
	char szFlippyFile[32];         //0x42
	char szInvFile[32];            //0x62
	WORD wDropSound;               //0x82
	WORD wUseSound;                //0x84
	BYTE nDropSfxFrame;            //0x86
	BYTE nAddFunc;                 //0x87
	ItemsTxtStat hStats[9];        //0x88
	ItemsTxtStat hGreenStats[10];   //0x118
};

struct RunesTxt
{
	char szName[64];					 //0x00
	char szRuneName[64];                 //0x40
	BYTE bComplete;                      //0x80
	BYTE bServer;                        //0x81
	DWORD dwRwId;						 //0x82
	WORD dwIType[6];                     //0x86
	WORD dwEType[3];                     //0x92
	DWORD dwRune[6];                     //0x98
	ItemsTxtStat hStats[7];              //0xB0
};

struct UniqueItemsTxt
{
	WORD _1;	                  //0x00
	char szName[34];              //0x02
	DWORD dwVersion;              //0x24
	union
	{
		DWORD dwCode;
		char szCode[4];
	};							  //0x28
	DWORD dwUniqueItemFlags;      //0x2C
	DWORD dwRarity;               //0x30
	WORD wLvl;                    //0x34
	WORD wLvlReq;                 //0x36
	BYTE nChrTransform;           //0x38
	BYTE nInvTransform;           //0x39
	char szFlippyFile[32];        //0x3A
	char szInvFile[34];           //0x5A
	DWORD dwCostMult;             //0x7C
	DWORD dwCostAdd;              //0x80
	WORD wDropSound;              //0x84
	WORD wUseSound;               //0x86
	DWORD dwDropSfxFrame;         //0x88   
	ItemsTxtStat hStats[12];      //0x90
};
#pragma pack(pop)


struct D2ItemsTxt
{
	char	szFlippyFile[32];			//0x00
	char	szInvFile[32];				//0x20
	char	szUniqueInvFile[32];		//0x40
	char	szSetInvFile[32];			//0x60
	union
	{
		DWORD	dwCode;					//0x80
		char	szCode[4];				//0x80
	};
	DWORD	dwNormCode;					//0x84
	DWORD	dwUberCode;					//0x88
	DWORD	dwUltraCode;				//0x8C
	DWORD	dwAlternateGfx;				//0x90
	DWORD	dwPSpell;					//0x94
	WORD	wState;						//0x98
	WORD	wCState1;					//0x9A
	WORD	wCState2;					//0x9C
	WORD	wStat1;						//0x9E
	WORD	wStat2;						//0xA0
	WORD	wStat3;						//0xA2
	DWORD	dwCalc1;					//0xA4
	DWORD	dwCalc2;					//0xA8
	DWORD	dwCalc3;					//0xAC
	DWORD	dwLen;						//0xB0
	WORD	wSpellDesc;					//0xB4
	WORD	wSpellDescStr;				//0xB6
	DWORD	dwSpellDescCalc;			//0xB8
	DWORD	dwBetterGem;				//0xBC
	DWORD	dwWClass;					//0xC0
	DWORD	dw2HandedWClass;			//0xC4
	DWORD	dwTMogType;					//0xC8
	DWORD	dwMinAc;					//0xCC
	DWORD	dwMaxAc;					//0xD0
	DWORD	dwGambleCost;				//0xD4
	DWORD	dwSpeed;					//0xD8
	DWORD	dwBitfield1;				//0xDC
	DWORD	dwCost;						//0xE0
	DWORD	dwMinStack;					//0xE4
	DWORD	dwMaxStack;					//0xE8
	DWORD	dwSpawnStack;				//0xEC
	DWORD	dwGemOffset;				//0xF0
	WORD	wNameStr;					//0xF4
	WORD	wVersion;					//0xF6
	WORD	wAutoPrefix;				//0xF8
	WORD	wMissileType;				//0xFA
	BYTE	bRarity;					//0xFC
	BYTE	bLevel;						//0xFD
	BYTE	bMinDam;					//0xFE
	BYTE	bMaxDam;					//0xFF
	BYTE	bMinMisDam;					//0x100
	BYTE	bMaxMisDam;					//0x101
	BYTE	b2HandMinDam;				//0x102
	BYTE	b2HandMaxDam;				//0x103
	WORD	bRangeAdder;				//0x104
	WORD	wStrBonus;					//0x106
	WORD	wDexBonus;					//0x108
	WORD	wReqStr;					//0x10A
	WORD	wReqDex;					//0x10C
	BYTE	bAbsorbs;					//0x10E
	BYTE	bInvWidth;					//0x10F
	BYTE	bInvHeight;					//0x110
	BYTE	bBlock;						//0x111
	BYTE	bDurability;				//0x112
	BYTE	bNoDurability;				//0x113
	BYTE	bMissile;					//0x114
	BYTE	bComponent;					//0x115
	BYTE	bRArm;						//0x116
	BYTE	bLArm;						//0x117
	BYTE	bTorso;						//0x118
	BYTE	bLegs;						//0x119
	BYTE	bRSPad;						//0x11A
	BYTE	bLSPad;						//0x11B
	BYTE	b2Handed;					//0x11C
	BYTE	bUseable;					//0x11D
	WORD	wType;						//0x11E
	WORD	wType2;						//0x120
	WORD	bSubType;					//0x122
	WORD	wDropSound;					//0x124
	WORD	wUseSound;					//0x126
	BYTE	bDropSfxFrame;				//0x128
	BYTE	bUnique;					//0x129
	BYTE	bQuest;						//0x12A
	BYTE	bQuestDiffCheck;			//0x12B
	BYTE	bTransparent;				//0x12C
	BYTE	bTransTbl;					//0x12D
	BYTE 	pad0x12E;					//0x12E
	BYTE	bLightRadius;				//0x12F
	BYTE	bBelt;						//0x130
	BYTE	bAutoBelt;					//0x131
	BYTE	bStackable;					//0x132
	BYTE	bSpawnable;					//0x133
	BYTE	bSpellIcon;					//0x134
	BYTE	bDurWarning;				//0x135
	BYTE	bQntWarning;				//0x136
	BYTE	bHasInv;					//0x137
	BYTE	bGemSockets;				//0x138
	BYTE	bTransmogrify;				//0x139
	BYTE	bTMogMin;					//0x13A
	BYTE	bTMogMax;					//0x13B
	BYTE	bHitClass;					//0x13C
	BYTE	b1or2Handed;				//0x13D
	BYTE	bGemApplyType;				//0x13E
	BYTE	bLevelReq;					//0x13F
	BYTE	bMagicLvl;					//0x140
	BYTE	bTransform;					//0x141
	BYTE	bInvTrans;					//0x142
	BYTE	bCompactSave;				//0x143
	BYTE	bSkipName;					//0x144
	BYTE	bNameable;					//0x145
	BYTE	bAkaraMin;					//0x146
	BYTE	bGheedMin;					//0x147
	BYTE	bCharsiMin;					//0x148
	BYTE	bFaraMin;					//0x149
	BYTE	bLysanderMin;				//0x14A
	BYTE	bDrognanMin;				//0x14B
	BYTE	bHraltiMin;					//0x14C
	BYTE	bAlkorMin;					//0x14D
	BYTE	bOrmusMin;					//0x14E
	BYTE	bElzixMin;					//0x14F
	BYTE	bAshearaMin;				//0x150
	BYTE	bCainMin;					//0x151
	BYTE	bHalbuMin;					//0x152
	BYTE	bJamellaMin;				//0x153
	BYTE	bMalahMin;					//0x154
	BYTE	bLarzukMin;					//0x155
	BYTE	bDrehyaMin;					//0x156
	BYTE	bAkaraMax;					//0x157
	BYTE	bGheedMax;					//0x158
	BYTE	bCharsiMax;					//0x159
	BYTE	bFaraMax;					//0x15A
	BYTE	bLysanderMax;				//0x15B
	BYTE	bDrognanMax;				//0x15C
	BYTE	bHraltiMax;					//0x15D
	BYTE	bAlkorMax;					//0x15E
	BYTE	bOrmusMax;					//0x15F
	BYTE	bElzixMax;					//0x160
	BYTE	bAshearaMax;				//0x161
	BYTE	bCainMax;					//0x162
	BYTE	bHalbuMax;					//0x163
	BYTE	bJamellaMax;				//0x164
	BYTE	bMalahMax;					//0x165
	BYTE	bLarzukMax;					//0x166
	BYTE	bDrehyaMax;					//0x167
	BYTE	bAkaraMagicMin;				//0x168
	BYTE	bGheedMagicMin;				//0x169
	BYTE	bCharsiMagicMin;			//0x16A
	BYTE	bFaraMagicMin;				//0x16B
	BYTE	bLysanderMagicMin;			//0x16C
	BYTE	bDrognanMagicMin;			//0x16D
	BYTE	bHraltiMagicMin;			//0x16E
	BYTE	bAlkorMagicMin;				//0x16F
	BYTE	bOrmusMagicMin;				//0x170
	BYTE	bElzixMagicMin;				//0x171
	BYTE	bAshearaMagicMin;			//0x172
	BYTE	bCainMagicMin;				//0x173
	BYTE	bHalbuMagicMin;				//0x174
	BYTE	bJamellaMagicMin;			//0x175
	BYTE	bMalahMagicMin;				//0x176
	BYTE	bLarzukMagicMin;			//0x177
	BYTE	bDrehyaMagicMin;			//0x178
	BYTE	bAkaraMagicMax;				//0x179
	BYTE	bGheedMagicMax;				//0x17A
	BYTE	bCharsiMagicMax;			//0x17B
	BYTE	bFaraMagicMax;				//0x17C
	BYTE	bLysanderMagicMax;			//0x17D
	BYTE	bDrognanMagicMax;			//0x17E
	BYTE	bHraltiMagicMax;			//0x17F
	BYTE	bAlkorMagicMax;				//0x180
	BYTE	bOrmusMagicMax;				//0x181
	BYTE	bElzixMagicMax;				//0x182
	BYTE	bAshearaMagicMax;			//0x183
	BYTE	bCainMagicMax;				//0x184
	BYTE	bHalbuMagicMax;				//0x185
	BYTE	bJamellaMagicMax;			//0x186
	BYTE	bMalahMagicMax;				//0x187
	BYTE	bLarzukMagicMax;			//0x188
	BYTE	bDrehyaMagicMax;			//0x189
	BYTE	bAkaraMagicLvl;				//0x18A
	BYTE	bGheedMagicLvl;				//0x18B
	BYTE	bCharsiMagicLvl;			//0x18C
	BYTE	bFaraMagicLvl;				//0x18D
	BYTE	bLysanderMagicLvl;			//0x18E
	BYTE	bDrognanMagicLvl;			//0x18F
	BYTE	bHraltiMagicLvl;			//0x190
	BYTE	bAlkorMagicLvl;				//0x191
	BYTE	bOrmusMagicLvl;				//0x192
	BYTE	bElzixMagicLvl;				//0x193
	BYTE	bAshearaMagicLvl;			//0x194
	BYTE	bCainMagicLvl;				//0x195
	BYTE	bHalbuMagicLvl;				//0x196
	BYTE	bJamellaMagicLvl;			//0x197
	BYTE	bMalahMagicLvl;				//0x198
	BYTE	bLarzukMagicLvl;			//0x199
	BYTE	bDrehyaMagicLvl;			//0x19A
	BYTE	pad0x19B;					//0x19B
	DWORD	dwNightmareUpgrade;			//0x19C
	DWORD	dwHellUpgrade;				//0x1A0
	BYTE	bPermStoreItem;				//0x1A4
	BYTE	bMultibuy;					//0x1A5
	WORD	pad0x1A6;					//0x1A6
};

struct D2TXTLinkageStrc
{
	void* pLink;
	DWORD Unk[3];   //don't care to check
};

struct BlizzardTXT	//[D2Common.0x96A20] = D2Common.0xA9608
{
	void* pPlayerClass;                                 //+00000000   01415B48      playerclass.txt
	D2TXTLinkageStrc* iPlayerClass;                     //+00000004   01410524      playerclass info
	void* pBodyLocs;                                    //+00000008   01415578      bodylocs.txt
	D2TXTLinkageStrc* iBodyLocs;                        //+0000000C   01410504      bodylocs info
	void* pStorepage;                                   //+00000010   01414CC8      storepage.txt
	D2TXTLinkageStrc* iStorePage;                       //+00000014   01415B24      storepage info
	void* pElemtypes;                                   //+00000018   01414958      elemtypes.txt
	D2TXTLinkageStrc* iElemtypes;                       //+0000001C   01415B04      elemtypes info
	void* pHitClass;                                    //+00000020   01414148      hitclass.txt
	D2TXTLinkageStrc* iHitClass;                        //+00000024   01415AE4      hitclass info
	void* pMonModeStub;                                 //+00000028   01416878      monmode.txt
	D2TXTLinkageStrc* iMonMode;                         //+0000002C   01415514      monmode info
	void* pPlayerModeStub;                              //+00000030   014162E8      plrmode.txt
	D2TXTLinkageStrc* iPlayerMode;                      //+00000034   01414934      plrmode info
	void* pSkillCalc;                                   //+00000038   05279860      skillcalc.txt
	D2TXTLinkageStrc* iSkillCalc;                       //+0000003C   01410014      skillcalc info
	BYTE* pSkillsCode;                                  //+00000040   0537A514      skillscode formulae
	DWORD dwSkillsCodeSize;                             //+00000044   00001768      size of skillscode block
	DWORD dwSkillsCodeSizeEx;                           //+00000048   00001768      size of skillscode block
	BYTE* pSkillDescCode;                               //+0000004C   0535C994      skilldesccode formulae
	DWORD dwSkillDescCodeSize;                          //+00000050   0000107F      size of skilldesccode block
	DWORD dwSkillDescCodeSizeEx;                        //+00000054   0000107F      size of skilldesccode block
	const char* pMissileCalc;                           //+00000058   01419C28      misscalc.txt
	D2TXTLinkageStrc* iMissileCalc;                     //+0000005C   01417024      misscalc info
	BYTE* pMissCode;                                    //+00000060   014A4944      misscode formulae
	DWORD dwMissCodeSize;                               //+00000064   000000D4      size of misscode block
	DWORD dwMissCodeSizeEx;                             //+00000068   000000D4      size of misscode block
	const char* pSkillCode;                             //+0000006C   052C445C      skillcode.txt (Id from skills.txt)
	D2TXTLinkageStrc* iSkillCode;                       //+00000070   0141F084      skillcode info
	void* pEvents;                                      //+00000074   0141ACA8      events.txt
	D2TXTLinkageStrc* iEvents;                          //+00000078   0141F064      events info
	DWORD* pCompCodes;                                  //+0000007C   06C4FAFC      compcode.txt
	D2TXTLinkageStrc* iCompCodes;                       //+00000080   01410544      compcode info
	int nCompCodes;                                     //+00000084   00000073      # of compcode records
	void* pMonAI;                                       //+00000088   0564351C      monai.txt
	D2TXTLinkageStrc* iMonAI;                           //+0000008C   01414914      monai info
	int nMonAI;                                         //+00000090   00000098      # of monai records
	D2TXTLinkageStrc* iItems;                           //+00000094   014BA014      items info
	BYTE* pItemsCode;                                   //+00000098   013FDED8      itemscode formulae
	DWORD dwItemsCodeSize;                              //+0000009C   000010E0      size of itemscode block
	DWORD dwItemsCodeSizeEx;                            //+000000A0   000010E0      size of itemscode block
	PropertiesTxt* pProperties;							//+000000A4   0579E218      properties.txt
	D2TXTLinkageStrc* iProperties;                      //+000000A8   01489464      properties info
	int nProperties;                                    //+000000AC   00000110      # of properties records
	D2TXTLinkageStrc* iRunes;                           //+000000B0   014C4774      runes info
	void* pMercDesc;									//+000000B4   01417208      hiredesc.txt
	D2TXTLinkageStrc* iMercDesc;                        //+000000B8   01415534      hiredesc info
	void* pStates;										//+000000BC   05767EA0      states.txt (limit = 255)
	D2TXTLinkageStrc* iStates;                          //+000000C0   014A16C4      states info
	int nStates;                                        //+000000C4   000000BD      # of states records
	void* pStateMasks;                                  //+000000C8   014A2574      statemasks.txt
	DWORD* fStateMasks[40];                             //+000000CC   014A2574      statemasks[40] (statemasks.txt segment array)
	short* pProgressiveStates;                          //+0000016C   014A23E4      progressive-state list
	int nProgressiveStates;                             //+00000170   00000006      # of progressive states
	short* pCurseStates;                                //+00000174   014A2254      curse-state list
	int nCurseStates;                                   //+00000178   0000001A      # of curse states
	short* pTransformStates;                            //+0000017C   014A20C4      transform-state list
	int nTransformStates;                               //+00000180   00000007      # of transform states
	short* pActionStates;                               //+00000184   014A3E74      action-state list
	int nActionStates;                                  //+00000188   00000007      # of action states
	short* pColourStates;                               //+0000018C   014A3CE4      color-state list
	int nColourStates;                                  //+00000190   00000002      # of color states
	void* pSoundCodes;                                  //+00000194   057656BC      soundcode.txt (sound column from sounds.txt)
	D2TXTLinkageStrc* iSoundCodes;                      //+00000198   0141F0E4      soundcode info
	int nSoundCodes;                                    //+0000019C   00000000      # of soundcode records (blanked out later)
	void* pHirelings;									//+000001A0   055D8CD8      hirelings.txt (limit = 256)
	int nHirelings;                                     //+000001A4   00000078      # of hirelings records
	int pMercFirst[256];                                //+000001A8   00000000      array of 256 integers (namefirst column from hirelings.txt)
	int pMercLast[256];		                            //+000005A8   0000000C      array of 256 integers (namelast column from hirelings.txt)   
	void* pNPCs;                                        //+000009A8   05724F74      npcs.txt
	int nNPCs;                                          //+000009AC   00000011      # of npcs records
	void* pColours;                                     //+000009B0   01417568      colors.txt
	D2TXTLinkageStrc* iColours;                         //+000009B4   01415554      colors info
	D2TXTLinkageStrc* iTreasureClassEx;                 //+000009B8   014C4714      treasureclassex info
	void* pTreasureClassEx;								//+000009BC   05718D98      treasureclassex.txt (limit = 65534 - autotcs#)
	int nTreasureClassEx;                               //+000009C0   0000043C      # of treasureclassex records
	DWORD* aTreasureClass[45];                          //+000009C4   0571D074      chest treasureclassex list (an array of 45 pointers)
	void* pMonstats;									//+00000A78   04FE0014      monstats.txt (limit = 32766)
	D2TXTLinkageStrc* iMonstats;                        //+00000A7C   0143C024      monstats info
	int nMonstats;                                      //+00000A80   000002E1      # of monstats records
	void* pMonSounds;                                   //+00000A84   013EBC9C      monsounds.txt
	D2TXTLinkageStrc* iMonSounds;                       //+00000A88   01438024      monsounds info
	int nMonSounds;                                     //+00000A8C   0000008D      # of monsounds records
	void* pMonstats2;									//+00000A90   05287408      monstats2.txt (no sign of that 1023 record limit)
	D2TXTLinkageStrc* iMonstats2;                       //+00000A94   01502014      monstats2 info
	int nMonstats2;                                     //+00000A98   00000245      # of monstats2 records
	void* pMonPlace;                                    //+00000A9C   01412648      monplace.txt
	D2TXTLinkageStrc* iMonPlace;                        //+00000AA0   01417BA4      monplace info
	int nMonPlace;                                      //+00000AA4   00000025      # of monplace records
	void* pMonPreset;                                   //+00000AA8   057248B0      monpreset.txt
	void* aMonPresetI[5];                               //+00000AAC   057248B0      array of 5 pointers to the monpreset sections for each of the 5 acts
	void* aMonPresetII[5];                              //+00000AC0   0000002F      array of 5 integers (# of records for monpreset in each of the 5 acts)
	void* pSuperUniques;								//+00000AD4   05364928      superuniques.txt (limit = 512)
	D2TXTLinkageStrc* iSuperUniques;                    //+00000AD8   0145A1F4      superuniques info
	int nSuperUniques;                                  //+00000ADC   00000042      # of superunique records
	WORD aSuperUniques[66];                             //+00000AE0   00010000      array of 66 words (the IdNos of the default superuniques, new ones are not added here [thankfully])
	void* pMissiles;									//+00000B64   05590014      missiles.txt (does some fixing for collidetype > 8)
	D2TXTLinkageStrc* iMissiles;                        //+00000B68   01492014      missiles info
	int nMissiles;                                      //+00000B6C   000002C4      # of missiles records
	void* pMonLvl;										//+00000B70   013B0064      monlvl.txt
	int nMonLvl;                                        //+00000B74   0000006F      # of monlvl records
	void* pMonSeq;                                      //+00000B78   05375900      monseq.txt
	D2TXTLinkageStrc* iMonSeq;                          //+00000B7C   0143A024      monseq info
	int nMonSeq;                                        //+00000B80   000003F2      # of monseq records
	void* pMonSeqTable;									//+00000B84   0143E7E4      sequences table (created from monseq.txt)
	int nMonSeqTable;                                   //+00000B88   0000003C      # of sequences
	void* pSkillDesc;									//+00000B8C   05741104      skilldesc.txt (limit = 32766) [JL and not JLE]
	D2TXTLinkageStrc* iSkillDesc;                       //+00000B90   014B8024      skilldesc info
	int nSkillDesc;                                     //+00000B94   000000DD      # of skilldesc records
	void* pSkills;										//+00000B98   056E4D78      skills.txt (limit = 32766) [JL and not JLE]
	D2TXTLinkageStrc* iSkills;                          //+00000B9C   014B50E4      skills info
	int nSkills;                                        //+00000BA0   00000173      # of skills records
	int* nClassSkillCount;                              //+00000BA4   014B9014      class skill count list
	int nHighestClassSkillCount;                        //+00000BA8   0000001E      # highest class skill count
	short* nClassSkillList;                             //+00000BAC   014BCB54      class skill list
	int nPassiveSkills;                                 //+00000BB0   0000001C      # of passive skills
	WORD* pPassiveSkills;								//+00000BB4   014BCB04      passiveskill list
	D2TXTLinkageStrc* iOverlay;                         //+00000BB8   01484024      overlay info
	void* pOverlay;										//+00000BBC   05352F54      overlay.txt
	int nOverlay;                                       //+00000BC0   00000125      # of overlay records
	void* pCharStats;									//+00000BC4   057AD178      charstats.txt
	int nCharStats;                                     //+00000BC8   00000007      # of charstats records
	void* pItemStatCost;								//+00000BCC   05219760      itemstatcost.txt (limit = 510) [511 used as END_OF_STATS in 'GF/JM' files]
	D2TXTLinkageStrc* iItemStatCost;                    //+00000BD0   0148C024      itemstatcost info
	int nItemStatCost;                                  //+00000BD4   0000016E      # of itemstatcost records
	void* pOPStats;										//+00000BD8   014882A4      opstats nesting table
	int nOPStats;										//+00000BDC   000000D3      # of nested opstats
	void* pMonEquip;									//+00000BE0   013B3798      monequip.txt (limit = 32766)
	int nMonEquip;                                      //+00000BE4   0000002D      # of monequip records
	void* pPetType;										//+00000BE8   05774138      pettype.txt (limit = 511)
	D2TXTLinkageStrc* iPetType;                         //+00000BEC   01486024      pettype info
	int nPetType;                                       //+00000BF0   00000014      # of pettype records
	D2TXTLinkageStrc* iItemTypes;                       //+00000BF4   0141E024      itemtypes info
	void* pItemTypes;									//+00000BF8   050D14AC      itemtypes.txt
	int nItemTypes;                                     //+00000BFC   00000069      # of itemtypes records
	int nItemTypesIndex;                                //+00000C00   00000004      (itemtypes#+31)/32
	DWORD* pItemTypesNest;                              //+00000C04   0537C41C      itemtypes nesting table
	D2TXTLinkageStrc* iSets;                            //+00000C08   014B3CE4      sets info
	void* pSets;                                        //+00000C0C   057A162C      sets.txt (limit = 32766)
	int nSets;                                          //+00000C10   00000020      # of sets records
	D2TXTLinkageStrc* iSetItems;                        //+00000C14   014B1024      setitems info
	SetItemsTxt* pSetItems;								//+00000C18   056BBAC0      setitems.txt (limit = 32766)
	int nSetItems;                                      //+00000C1C   0000007F      # of setitems records
	D2TXTLinkageStrc* iUniqueItems;                     //+00000C20   014AA044      uniqueitems info
	UniqueItemsTxt* pUniqueItems;						//+00000C24   0510E8B4      uniqueitems.txt (limit = 32766)
	int nUniqueItems;                                   //+00000C28   00000191      # of uniqueitems records
	//ect...
};

#pragma warning ( pop )
#pragma optimize ( "", on )

#endif
