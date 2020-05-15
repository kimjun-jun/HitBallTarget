///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	player.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once


//*****************************************************************************
//* ?造体定?
//******************************************************************************* /
typedef struct // プレイヤ??造体
{
	CHARACTER pp;
} PLAYER_PIT;

typedef struct // プレイヤ??造体
{
	CHARACTER pb;
} PLAYER_BAT;


//*****************************************************************************
// プロト?イプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void ReInitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

HRESULT MakeVertexPlayer(int i);
void SetTexturePlayer(int cntPattern, int i);	// 
void SetVertexPlayer(int i);					// 

PLAYER_PIT *GetPlayerPit(void);
PLAYER_BAT *GetPlayerBat(void);
