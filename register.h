/**
* @file register.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define SAVE_TEXTURE_FILE_00		_T("data/TEXTURE/SAVE/save.png")			//!< 読み込むテクスチャファイル名
#define SAVE_SIZE_W					(880)										//!< テクスチャサイズX
#define SAVE_SIZE_H					(660)										//!< テクスチャサイズY
#define SAVE_POS_X					(0)											//!< ポリゴンの初期位置X
#define SAVE_POS_Y					(0)											//!< ポリゴンの初期位置Y

/*******************************************************************************
* 構造体定義
*******************************************************************************/
/**
*　@struct SAVEDATA
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	int ftime;																	//!< タイムの保存
	int fscore;																	//!< スコアの保存
} SAVEDATA;

/**
*　@struct SAVE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;									//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];								//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;												//!< 背景の位置
}SAVE;

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
/**
* @brief Save初期化関数 InitSave
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitSave(int type);

/**
* @brief Save開放関数 UninitSave
*/
void UninitSave(void);

/**
* @brief Save更新関数 UpdateSave
*/
void UpdateSave(void);

/**
* @brief Save描画関数 DrawSave
*/
void DrawSave(void);

/**
* @brief Save開放関数 SaveData
* @details セーブデータを作成し、ファイルへ出力する
*/
void SaveData(void);

/**
* @brief Save開放関数 LoadData
* @details セーブデータをファイルから読み込む
*/
void LoadData(void);
