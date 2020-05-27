/**
* @file controltype.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_DIGITAL							_T("data/TEXTURE/sozai/select/digital.png")		//!< 読み込むテクスチャファイル名
#define	TEXTURE_ANALOG							_T("data/TEXTURE/sozai/select/analog.png")		//!< 読み込むテクスチャファイル名
#define	TEXTURE_CONTYPECURSOR					_T("data/TEXTURE/sozai/select/nowselect.png")	//!< 読み込むテクスチャファイル名	
#define TEXTURE_CONTYPEBROAD_SIZE_X				(200)											//!< ポリゴンの幅
#define TEXTURE_CONTYPEBROAD_SIZE_Y				(100)											//!< ポリゴンの高さ
#define	CONTYPEMAX								(3)												//!< 画面の選択肢数

/**
*　@struct CONTYPE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;													//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];												//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																//!< ポリゴンの座標
}CONTYPE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief コントロールタイプ画僧初期化関数 InitContype
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitContype(int type);

/**
* @brief コントロールタイプ画僧再初期化関数 ReInitContype
*/
void ReInitContype(void);

/**
* @brief コントロールタイプ画僧開放関数 UninitContype
*/
void UninitContype(void);

/**
* @brief コントロールタイプ画僧更新関数 UpdateContype
*/
void UpdateContype(void);

/**
* @brief コントロールタイプ画僧更新関数 UpdateTUTOContype
*/
void UpdateTUTOContype(void);

/**
* @brief コントロールタイプ画僧描画関数 DrawContype
*/
void DrawContype(void);

/**
* @brief コントロールタイプ画僧カーソルが止まっている場所取得関数 GetSCONkeypos
* @return int
*/
int GetSCONkeypos(void);
