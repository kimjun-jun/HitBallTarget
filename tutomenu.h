/**
* @file tutomenu.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TUTOMENU_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_TUTOMENU_SIZE_Y		(100)										// タイトルロゴの高さ


#define	TUTOMENUMAX		(2)						//ポーズ画面の選択肢数

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
	bool					use;
}TUTOMENU;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutomenu(int type);
void ReInitTutomenu(void);
void UninitTutomenu(void);
void UpdateTutomenu(void);
void UpdateInTutomenu(void);
void DrawTutomenu(void);
void SetVertexTutomenu(void);
TUTOMENU *GetTutomenu(void);
