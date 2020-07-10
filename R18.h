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
#define	TEXTURE_R18SELECT01						_T("data/TEXTURE/sozai/select/heart01.png")	//!< 読み込むテクスチャファイル名		
#define	TEXTURE_R18SELECT02						_T("data/TEXTURE/sozai/select/heart02.png")	//!< 読み込むテクスチャファイル名		
#define	TEXTURE_R18SELECT03						_T("data/TEXTURE/sozai/select/NotR18.png")	//!< 読み込むテクスチャファイル名		
#define TEXTURE_R18SELECT_SIZE_X				(200)										//!< ポリゴンの幅
#define TEXTURE_R18SELECT_SIZE_Y				(100)										//!< ポリゴンの高さ
#define R18SELECT_PY1_POS_Y						(SCREEN_CENTER_Y-150)						//!< ポリゴンの初期位置Y1
#define R18SELECT_PY2_POS_Y						(SCREEN_CENTER_Y+100)						//!< ポリゴンの初期位置Y2
#define R18SELECT_PX1_POS_X						(SCREEN_CENTER_X-250)						//!< ポリゴンの初期位置X1
#define R18SELECT_PX2_POS_X						(SCREEN_CENTER_X+250)						//!< ポリゴンの初期位置X2
#define	R18SELECTMAX							(3)											//!< 画面の選択肢数

/**
*　@struct R18SELECT
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;												//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];											//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;															//!< ポリゴンの座標
}R18SELECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief R18初期化関数 InitR18select
* @param[in] type 初期化タイプ　INIT_TIME利用。0:初回　0以外: 2回目以降
* @return HRESULT
*/
HRESULT InitR18select(int type);

/**
* @brief R18再初期化関数 ReInitR18select
*/
void ReInitR18select(void);

/**
* @brief R18開放関数 UninitR18select
*/
void UninitR18select(void);

/**
* @brief R18更新関数 UpdateR18select
*/
void UpdateR18select(void);

/**
* @brief R18描画関数 DrawR18select
*/
void DrawR18select(void);

/**
* @brief R18取得関数 GetR18select
* @return R18SELECT
*/
R18SELECT *GetR18select(void);
