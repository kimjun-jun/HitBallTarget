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
#define	TUTORIAL_POS_X			(0)													//!< ポリゴンの表示位置X
#define	TUTORIAL_POS_Y			(0)													//!< ポリゴンの表示位置Y
#define	TUTORIAL_SIZE_X			(SCREEN_W)											//!< ポリゴンの幅X
#define	TUTORIAL_SIZE_Y			(SCREEN_H)											//!< ポリゴンの高さY
#define TUTORIAL_GOUKEI			(3)													//!< チュートリアル構造体の合計

/**
*　@struct TUTO
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;										//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];									//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;													//!< ポリゴンの座標
}TUTO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Tutorial初期化関数 InitTutorial
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitTutorial(int type);

/**
* @brief Tutorial開放関数 UninitTutorial
*/
void UninitTutorial(void);

/**
* @brief Tutorial更新関数 UpdateTutorial
*/
void UpdateTutorial(void);

/**
* @brief Tutorial描画関数 DrawTutorial
*/
void DrawTutorial(void);

