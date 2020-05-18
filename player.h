/**
* @file player.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
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
