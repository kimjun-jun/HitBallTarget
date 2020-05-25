/**
* @file pause.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_HAJIMEKARA					_T("data/TEXTURE/sozai/select/hajimekara.png")		//!< 読み込むテクスチャファイル名
#define	TEXTURE_OPTIONMARK					_T("data/TEXTURE/sozai/select/option.png")			//!< 読み込むテクスチャファイル名
#define	TEXTURE_END							_T("data/TEXTURE/sozai/select/akirameru.png")		//!< 読み込むテクスチャファイル名
#define TEXTURE_RESTART_SIZE_X				(200)												//!< ポリゴンの幅
#define TEXTURE_RESTART_SIZE_Y				(100)												//!< ポリゴンの高さ
#define	PAUSEMAX							(3)													//!< 画面の選択肢数

/**
*　@struct PAUSE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;													//!< テクスチャへのポリゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];												//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																//!< ポリゴンの移動量
	bool					use;
}PAUSE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Pause初期化関数 InitPause
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitPause(int type);

/**
* @brief Pause再初期化関数 ReInitPause
*/
void ReInitPause(void);

/**
* @brief Pause開放関数 UninitPause
*/
void UninitPause(void);

/**
* @brief Pauseポーズシーン更新関数 UpdatePause
*/
void UpdatePause(void);


/**
* @brief Pauseゲームシーン更新関数 UpdateInPause
*/
void UpdateInPause(void);

/**
* @brief Pause描画関数 DrawPause
*/
void DrawPause(void);

/**
* @brief Pause取得関数 GetPause
* @return PAUSE
*/
PAUSE *GetPause(void);
