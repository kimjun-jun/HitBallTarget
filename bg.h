/**
* @file bg.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLEBG		_T("data/TEXTURE/bg000.jpg")					//!< 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIALBG	_T("data/TEXTURE/tutorial/tutobg.png")			//!< 読み込むテクスチャファイル名
#define TEXTURE_GAMEBG		_T("data/TEXTURE/BG/bg.png")					//!< 読み込むテクスチャファイル名
#define TEXTURE_GAMEBGR1801	_T("data/TEXTURE/sozai/R1801.png")				//!< 読み込むテクスチャファイル名
#define TEXTURE_GAMEBGR1802	_T("data/TEXTURE/sozai/R1802.png")				//!< 読み込むテクスチャファイル名
#define	TEXTURE_PAUSETBG	_T("data/TEXTURE/sozai/textbg.png")				//!< 読み込むテクスチャファイル名
#define BG_SIZE_W			(SCREEN_W)										//!< テクスチャサイズX
#define BG_SIZE_H			(SCREEN_H)										//!< テクスチャサイズY
#define BG_POS_X			(0)												//!< ポリゴンの初期座標X(左上)
#define BG_POS_Y			(0)												//!< ポリゴンの初期座標Y(左上)
#define BG_MAX				(15)											//!< 背景種類の合計
#define GAMER18BG_MAX		(3)												//!< 

/**
*　@struct BG
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;								//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];							//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;											//!< 背景の座標
} BG;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief R18初期化関数 InitBG
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitBG(int type);

/**
* @brief BG再初期化関数 ReInitBG
*/
void ReInitBG(void);

/**
* @brief BG開放関数 UninitBG
*/
void UninitBG(void);

/**
* @brief BG更新関数 UpdateBG
*/
void UpdateBG(void);

/**
* @brief BG描画関数 DrawBG
*/
void DrawBG(void);

/**
* @brief BG設定関数 SetGameBGtype
* @param[in] num -1標準,0魔女っ子,1スイーツ
*/
void SetGameBGtype(int num);
