///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	bg.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once

// マクロ定義
#define	TEXTURE_TITLEBG		_T("data/TEXTURE/bg000.jpg")					// 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIALBG	_T("data/TEXTURE/tutorial/tutobg.png")			// 読み込むテクスチャファイル名
#define TEXTURE_GAMEBG		_T("data/TEXTURE/BG/bg.png")	// サンプル用画像
#define TEXTURE_GAMEBGR1801	_T("data/TEXTURE/sozai/R1801.png")	// サンプル用画像
#define TEXTURE_GAMEBGR1802	_T("data/TEXTURE/sozai/R1802.png")	// サンプル用画像
#define	TEXTURE_PAUSETBG	_T("data/TEXTURE/sozai/textbg.png")		
#define BG_SIZE_W			(SCREEN_W)	// テクスチャサイズl
#define BG_SIZE_H			(SCREEN_H)	// 同上
#define BG_POS_X			(0)		// ポリゴンの初期位置X(左上)
#define BG_POS_Y			(0)		// 同上

#define BG_MAX			(15)
#define GAMEBG_MAX		(3)

typedef struct // キャラクター構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;	// テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 背景の位置
} BG;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void ReInitBG(void);
void UpdateBG(void);
void DrawBG(void);
HRESULT MakeVertexBG(void);
void SetVertexBG(void);
void SetGameBGtype(int num);
