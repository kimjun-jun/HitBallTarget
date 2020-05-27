/**
* @file sensitivity.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_L1R1								_T("data/TEXTURE/sozai/select/digital.png")	//!< 読み込むテクスチャファイル名
#define	TEXTURE_SENSITIVITYNUM						_T("data/TEXTURE/BG/0-9.png")				//!< 読み込むテクスチャファイル名
#define TEXTURE_SENSITIVITYBROAD_SIZE_X				(200)										//!< ポリゴンの幅
#define TEXTURE_SENSITIVITYBROAD_SIZE_Y				(100)										//!< ポリゴンの高さ
#define	SENSITIVITYMAX								(2)											//!< 画面の選択肢数

/**
*　@struct SENSITIVITY
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;													//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];												//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																//!< ポリゴンの座標
}SENSITIVITY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Sensitivity初期化関数 InitSensitivity
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitSensitivity(int type);

/**
* @brief Sensitivity再初期化関数 ReInitSensitivity
*/
void ReInitSensitivity(void);

/**
* @brief Sensitivity開放関数 UninitSensitivity
*/
void UninitSensitivity(void);

/**
* @brief Sensitivity更新関数 UpdateSensitivity
*/
void UpdateSensitivity(void);

/**
* @brief SensitivityTUTO更新関数 UpdateTUTOSensitivity
*/
void UpdateTUTOSensitivity(void);

/**
* @brief Sensitivity描画関数 DrawSensitivity
*/
void DrawSensitivity(void);

/**
* @brief 感度画僧カーソルが止まっている場所取得関数 GetSSENSIkey
* @return int
*/
int GetSSENSIkey(void);
