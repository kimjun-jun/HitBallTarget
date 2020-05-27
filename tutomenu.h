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
#define TEXTURE_TUTOMENU_SIZE_X		(200)										//!< ポリゴンの幅
#define TEXTURE_TUTOMENU_SIZE_Y		(100)										//!< ポリゴンの高さ
#define	TUTOMENUMAX					(2)											//!< チュートリアルメニュー構造体画面の選択肢数

/**
*　@struct TUTOMENU
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< テクスチャへのポリゴン
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;												//!< ポリゴンの座標
	bool					use;												//!< 使用しているかどうか
}TUTOMENU;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Tutomenu初期化関数 InitTutomenu
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitTutomenu(int type);
/**
* @brief Tutomenu再初期化関数 ReInitTutomenu
*/
void ReInitTutomenu(void);
/**
* @brief Tutomenu開放関数 UninitTutomenu
*/
void UninitTutomenu(void);
/**
* @brief Tutomenu更新関数 UpdateTutomenu
*/
void UpdateTutomenu(void);
/**
* @brief Tutomenu更新関数 UpdateInTutomenu
*/
void UpdateInTutomenu(void);
/**
* @brief Tutomenu描画関数 DrawTutomenu
*/
void DrawTutomenu(void);
/**
* @brief Tutomenu取得関数 GetTutomenu
* @return TUTOMENU
*/
TUTOMENU *GetTutomenu(void);
