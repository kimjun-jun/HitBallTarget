/**
* @file select.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EASY				_T("data/TEXTURE/sozai/select/easy.png")	//!< 読み込むテクスチャファイル名
#define	TEXTURE_NORMAL				_T("data/TEXTURE/sozai/select/normal.png")	//!< 読み込むテクスチャファイル名
#define	TEXTURE_HARD				_T("data/TEXTURE/sozai/select/hard.png")	//!< 読み込むテクスチャファイル名
#define	TEXTURE_LEVEL				_T("data/TEXTURE/sozai/level.png")			//!< 読み込むテクスチャファイル名
#define	TEXTURE_RANKING 			_T("data/TEXTURE/sozai/select/ranking.png")	//!< 読み込むテクスチャファイル名
#define	TEXTURE_ENTER				_T("data/TEXTURE/sozai/enterstart.png")		//!< 読み込むテクスチャファイル名
#define TEXTURE_EASY_SIZE_X			(200)										//!< ポリゴンの幅	全難易度
#define TEXTURE_EASY_SIZE_Y			(100)										//!< ポリゴンの高さ	全難易度
#define	TEXTURE_ENTER_SIZE_X		(300)										//!< ポリゴンの幅	エンター
#define	TEXTURE_ENTER_SIZE_Y		(200)										//!< ポリゴンの高さ	エンター
#define EASY_POS_Y					(SCREEN_H-650)								//!< ポリゴンの初期位置Y	イージー
#define NORMAL_POS_Y				(SCREEN_H-400)								//!< ポリゴンの初期位置Y	ノーマル
#define HRAD_POS_Y					(SCREEN_H-150)								//!< ポリゴンの初期位置Y	ハード
#define LEVEL_POS_Y					(SCREEN_H-850)								//!< ポリゴンの初期位置Y	レベル
#define EASY_POS_X					(SCREEN_W-900)								//!< ポリゴンの初期位置X	全難易度
#define LEVEL_POS_X					(SCREEN_W-1000)								//!< ポリゴンの初期位置X	レベル
#define ENTERorSTART_POS_Y			(SCREEN_H-400)								//!< ポリゴンの初期位置Y	エンター
#define ENTERorSTART_POS_X			(SCREEN_W-350)								//!< ポリゴンの初期位置X	エンター
#define	SMAX						(5)											//!< 選択肢の構造体数

/**
*　@struct SELECT
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{																				//!< テクスチャへのポインタ 
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< 頂点情報格納ワーク
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< ポリゴンの座標
	D3DXVECTOR3				pos;						
}SELECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Select初期化関数 InitSelect
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitSelect(int type);

/**
* @brief Select開放関数 UninitSelect
*/
void UninitSelect(void);

/**
* @brief Select更新関数 UpdateSelect
*/
void UpdateSelect(void);

/**
* @brief Select描画関数 DrawSelect
*/
void DrawSelect(void);

/**
* @brief セレクトしている難易度(ネコの数)取得関数 GetSpos
* @return int
*/
int GetSpos(void);
