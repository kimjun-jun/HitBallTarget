/**
* @file pause.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_HAJIMEKARA		_T("data/TEXTURE/sozai/select/hajimekara.png")		
#define	TEXTURE_OPTIONMARK		_T("data/TEXTURE/sozai/select/option.png")
#define	TEXTURE_END				_T("data/TEXTURE/sozai/select/akirameru.png")		

#define TEXTURE_RESTART_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_RESTART_SIZE_Y		(100)										// タイトルロゴの高さ






#define	PAUSEMAX		(3)						//ポーズ画面の選択肢数

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
	bool					use;
}PAUSE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPause(int type);
void ReInitPause(void);
void UninitPause(void);
void UpdatePause(void);
void UpdateInPause(void);
void DrawPause(void);
void SetVertexPause(void);
PAUSE *GetPause(void);
