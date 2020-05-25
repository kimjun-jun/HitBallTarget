/**
* @file option.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_MODESELECT						_T("data/TEXTURE/sozai/select/ModeSet.png")		//!< 読み込むテクスチャファイル名		
#define	TEXTURE_R18								_T("data/TEXTURE/sozai/select/r18.png")			//!< 読み込むテクスチャファイル名		
#define TEXTURE_SENSITIV_SIZE_X					(200)											//!< ポリゴンの幅
#define TEXTURE_SENSITIV_SIZE_Y					(100)											//!< ポリゴンの高さ
#define OPTION_PY1_POS_Y						(SCREEN_CENTER_Y-150)							//!< ポリゴンの初期位置Y1
#define OPTION_PY2_POS_Y						(SCREEN_CENTER_Y+100)							//!< ポリゴンの初期位置Y2
#define OPTION_PX1_POS_X						(SCREEN_CENTER_X-250)							//!< ポリゴンの初期位置X1
#define OPTION_PX2_POS_X						(SCREEN_CENTER_X+250)							//!< ポリゴンの初期位置X2
#define	OPTIONMAX								(4)												//!< 画面の選択肢数		

/**
*　@struct OPTION
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;												//!< テクスチャへのポリゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];											//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;															//!< ポリゴンの移動量
}OPTION;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Option初期化関数 InitOption
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitOption(int type);

/**
* @brief Option再初期化関数 ReInitOption
*/
void ReInitOption(void);

/**
* @brief Option開放関数 UninitOption
*/
void UninitOption(void);

/**
* @brief Option更新関数 UpdateOption
*/
void UpdateOption(void);

/**
* @brief Option描画関数 DrawOption
*/
void DrawOption(void);

/**
* @brief Option取得関数 GetOption
* @return OPTION
*/
OPTION *GetOption(void);
