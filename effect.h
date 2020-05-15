///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	effect.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once

// マクロ定義
#define BE_TEXTURE_FILE_00		_T("data/TEXTURE/effect/bom.png")	// サンプル用画像
#define BE_SIZE_W			(20)	// テクスチャサイズl
#define BE_SIZE_H			(20)	// 同上


#define BE_TEXTURE_PATTERN_DIVIDE_X	(6)	// アニメパターンのテクスチャ内分割数（X)  
#define BE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)  
#define BE_ANIM_PATTERN_NUM			(BE_TEXTURE_PATTERN_DIVIDE_X*BE_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数  
#define BE_TIME_ANIMATION				(6)	// アニメーションの切り替わるカウント  


typedef struct // キャラクター構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;	// テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 背景の位置
	int						nCountAnim;					// アニメ?ションカウント 
	int						nPatternAnim;				// アニメ?ションパ??ンナンバ? 
	bool					motion;						// ?投球している 偽投球していない
	bool					use;						// 使用しているかどうか
} BE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBE(int type);
void ReInitBE(void);
void UninitBE(void);
void UpdateBE(void);
void DrawBE(void);
HRESULT MakeVertexBE(void);
void SetTextureBe(int cntPattern);
void SetVertexBE(void);
void SelectBE(int type);
void DeadEffect(int i, int type);
BE *GetBE(int i);