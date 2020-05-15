///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	controltype.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_DIGITAL			_T("data/TEXTURE/sozai/select/digital.png")		
#define	TEXTURE_ANALOG			_T("data/TEXTURE/sozai/select/analog.png")
#define	TEXTURE_CONTYPECURSOR	_T("data/TEXTURE/sozai/select/nowselect.png")		

#define TEXTURE_CONTYPEBROAD_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_CONTYPEBROAD_SIZE_Y		(100)										// タイトルロゴの高さ





#define	CONTYPEMAX		(3)						//ポーズ画面の選択肢数

typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
}CONTYPE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitContype(int type);
void ReInitContype(void);
void UninitContype(void);
void UpdateContype(void);
void UpdateTUTOContype(void);
void DrawContype(void);
void SetVertexContype(void);
int GetSCONkeypos(void);
