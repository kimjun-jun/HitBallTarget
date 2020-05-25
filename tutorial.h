/**
* @file tutorial.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TUTORIALF1		_T("data/TEXTURE/tutorial/tutorialF1.png")			//!< 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIALF2		_T("data/TEXTURE/tutorial/tutorialF2.png")			//!< 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIALF3		_T("data/TEXTURE/tutorial/tutorialF3.png")			//!< 読み込むテクスチャファイル名
#define	TUTORIAL_POS_X			(0)													//!< タイトルの表示位置X
#define	TUTORIAL_POS_Y			(0)													//!< タイトルの表示位置Y
#define	TUTORIAL_SIZE_X			(SCREEN_W)											//!< タイトルの幅X
#define	TUTORIAL_SIZE_Y			(SCREEN_H)											//!< タイトルの高さY
#define TUTORIAL_GOUKEI			(3)													//!< タイトルの合計

/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;										//!< テクスチャへのポリゴン
	VERTEX_2D				vertexWk[NUM_VERTEX];									//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;													//!< テクスチャへのポリゴン
}TUTO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief R18初期化関数 InitR18select
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitTutorial(int type);
/**
* @brief R18開放関数 UninitR18select
*/
void UninitTutorial(void);
/**
* @brief R18更新関数 UpdateR18select
*/
void UpdateTutorial(void);
/**
* @brief R18描画関数 DrawR18select
*/
void DrawTutorial(void);

