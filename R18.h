/**
* @file R18.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_R18SELECT01		_T("data/TEXTURE/sozai/select/heart01.png")			
#define	TEXTURE_R18SELECT02		_T("data/TEXTURE/sozai/select/heart02.png")			
#define	TEXTURE_R18SELECT03		_T("data/TEXTURE/sozai/select/NotR18.png")			


#define TEXTURE_R18SELECT_SIZE_X		(200)								// タイトルロゴの幅
#define TEXTURE_R18SELECT_SIZE_Y		(100)								// タイトルロゴの高さ



#define R18SELECT_PY1_POS_Y						(SCREEN_CENTER_Y-150)		// ポリゴンの初期位置X
#define R18SELECT_PY2_POS_Y						(SCREEN_CENTER_Y+100)		// ポリゴンの初期位置X

#define R18SELECT_PX1_POS_X						(SCREEN_CENTER_X-250)		// 同上
#define R18SELECT_PX2_POS_X						(SCREEN_CENTER_X+250)		// 同上

#define	R18SELECTMAX		(3)						//ポーズ画面の選択肢数

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
}R18SELECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitR18select(int type);
void ReInitR18select(void);
void UninitR18select(void);
void UpdateR18select(void);
void DrawR18select(void);
void SetVertexR18select(void);
R18SELECT *GetR18select(void);
