/**
* @file title.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE_LOGO	_T("data/TEXTURE/title/title_logo.png")			//!< 読み込むテクスチャファイル名
#define	TITLELOGO_POS_X		(SCREEN_CENTER_X)								//!< タイトルロゴの表示位置X
#define	TITLELOGO_POS_Y		(SCREEN_CENTER_Y)								//!< タイトルロゴの表示位置Y
#define	TITLELOGO_SIZE_X	(SCREEN_CENTER_X/2)								//!< タイトルロゴの幅X
#define	TITLELOGO_SIZE_Y	(SCREEN_CENTER_Y/2)								//!< タイトルロゴの高さY
#define	TITLE_GOUKEI		(1)												//!< タイトルの合計

/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;								//!< テクスチャへのポリゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];							//!< 頂点情報格納ワーク
}TITLE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

/**
* @brief タイトル初期化関数 InitTitle
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitTitle(int type);

/**
* @brief タイトル開放関数 UninitTitle
*/
void UninitTitle(void);

/**
* @brief タイトル更新関数 UpdateTitle
*/
void UpdateTitle(void);

/**
* @brief タイトル描画関数 DrawTitle
*/
void DrawTitle(void);
