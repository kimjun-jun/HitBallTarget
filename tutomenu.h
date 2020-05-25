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
#define TEXTURE_TUTOMENU_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_TUTOMENU_SIZE_Y		(100)										// タイトルロゴの高さ


#define	TUTOMENUMAX		(2)						//ポーズ画面の選択肢数

/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< テクスチャへのポリゴン
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;												
	bool					use;
}TUTOMENU;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief R18初期化関数 InitR18select
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitTutomenu(int type);
/**
* @brief R18再初期化関数 ReInitR18select
*/
void ReInitTutomenu(void);
/**
* @brief R18開放関数 UninitR18select
*/
void UninitTutomenu(void);
/**
* @brief R18更新関数 UpdateR18select
*/
void UpdateTutomenu(void);
/**
* @brief R18更新関数 UpdateR18select
*/
void UpdateInTutomenu(void);
/**
* @brief R18描画関数 DrawR18select
*/
void DrawTutomenu(void);
void SetVertexTutomenu(void);
/**
* @brief R18取得関数 GetR18select
*/
TUTOMENU *GetTutomenu(void);
