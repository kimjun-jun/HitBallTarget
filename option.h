/**
* @file option.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_MODESELECT			_T("data/TEXTURE/sozai/select/ModeSet.png")		
#define	TEXTURE_R18					_T("data/TEXTURE/sozai/select/r18.png")


#define TEXTURE_SENSITIV_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_SENSITIV_SIZE_Y		(100)										// タイトルロゴの高さ

#define OPTION_PY1_POS_Y						(SCREEN_CENTER_Y-150)		// ポリゴンの初期位置X
#define OPTION_PY2_POS_Y						(SCREEN_CENTER_Y+100)		// ポリゴンの初期位置X

#define OPTION_PX1_POS_X						(SCREEN_CENTER_X-250)		// 同上
#define OPTION_PX2_POS_X						(SCREEN_CENTER_X+250)		// 同上


#define	OPTIONMAX		(4)						//ポーズ画面の選択肢数

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
}OPTION;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitOption(int type);
void ReInitOption(void);
void UninitOption(void);
void UpdateOption(void);
void DrawOption(void);
void SetVertexOption(void);
OPTION *GetOption(void);
