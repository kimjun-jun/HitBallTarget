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
#define	TEXTURE_EASY		_T("data/TEXTURE/sozai/select/easy.png")			// 読み込むテクスチャファイル名
#define TEXTURE_EASY_SIZE_X		(200)										// タイトルロゴの幅
#define TEXTURE_EASY_SIZE_Y		(100)										// タイトルロゴの高さ

#define	TEXTURE_NORMAL		_T("data/TEXTURE/sozai/select/normal.png")		
#define	TEXTURE_HARD		_T("data/TEXTURE/sozai/select/hard.png")			
#define	TEXTURE_LEVEL		_T("data/TEXTURE/sozai/level.png")			
#define	TEXTURE_RANKING 		_T("data/TEXTURE/sozai/select/ranking.png")		


#define EASY_POS_Y					(SCREEN_H-650)		// ポリゴンの初期位置X
#define NORMAL_POS_Y				(SCREEN_H-400)		// ポリゴンの初期位置X
#define HRAD_POS_Y					(SCREEN_H-150)		// ポリゴンの初期位置X
#define LEVEL_POS_Y					(SCREEN_H-850)		// ポリゴンの初期位置X


#define EASY_POS_X					(SCREEN_W-900)		// 同上
#define LEVEL_POS_X					(SCREEN_W-1000)		// ポリゴンの初期位置X


#define	TEXTURE_ENTER		_T("data/TEXTURE/sozai/enterstart.png")			
#define	TEXTURE_ENTER_SIZE_X		(300)					
#define	TEXTURE_ENTER_SIZE_Y		(200)					
#define ENTERorSTART_POS_Y			(SCREEN_H-400)		// ポリゴンの初期位置X
#define ENTERorSTART_POS_X			(SCREEN_W-350)		// 同上


#define	SMAX		(5)													//選択肢の数

/**
*　@struct TITLE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂?情報格?ワ?ク

	D3DXVECTOR3				pos;						// ?リゴンの移動量
}SELECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief R18初期化関数 InitR18select
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitSelect(int type);
/**
* @brief R18開放関数 UninitR18select
*/
void UninitSelect(void);
/**
* @brief R18更新関数 UpdateR18select
*/
void UpdateSelect(void);
/**
* @brief R18描画関数 DrawR18select
*/
void DrawSelect(void);
void SetTextureSelect(void);
void SetVertexSelect(void);
/**
* @brief R18取得関数 GetR18select
*/
int GetSpos(void);
