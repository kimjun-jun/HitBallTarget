/**
* @file score.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_GAME_DOT					_T("data/TEXTURE/BG/dot.png")										//!< 読み込むテクスチャファイル名
#define TEXTURE_SCORE_SIZE_X				(50)																//!< テクスチャサイズY
#define TEXTURE_SCORE_SIZE_Y				(50)																//!< テクスチャサイズX  
#define SCORE_TEXTURE_PATTERN_DIVIDE_X		(10)																//!< アニメパターンのテクスチャ内分割数（X)  
#define SCORE_TEXTURE_PATTERN_DIVIDE_Y		(1)																	//!< アニメパターンのテクスチャ内分割数（Y)  
#define SCORE_ANIM_PATTERN_NUM				(SCORE_TEXTURE_PATTERN_DIVIDE_X*SCORE_TEXTURE_PATTERN_DIVIDE_Y)		//!< アニメーションパターン数  
#define SCORE_TIME_ANIMATION				(4)																	//!< アニメーションの切り替わるカウント  
#define TEXTURE_DOT_SIZE_X					(7)																	//!< テクスチャサイズX
#define TEXTURE_DOT_SIZE_Y					(7)																	//!< テクスチャサイズY  
#define TIME_DIGIT							(3)																	//!< タイムの桁数
#define SCORE_DIGIT							(4)																	//!< スコアの桁数
#define SCORE_GOUKEI						(60)																//!< スコアの合計
#define FPS_TIME_COUNT						(4200)																//!< タイムの合計
#define TEXTURE_GAME_SCORELOGO				_T("data/TEXTURE/sozai/SCORE.png") 									//!< 読み込むテクスチャファイル名
#define TEXTURE_GAME_TIMELOGO				_T("data/TEXTURE/sozai/TIME.png") 									//!< 読み込むテクスチャファイル名
#define TEXTURE_SCORELOGO_SIZE_X			(100)																//!< テクスチャサイズX
#define TEXTURE_SCORELOGO_SIZE_Y			(75)																//!< テクスチャサイズY
#define TEXTURE_TIMELOGO_SIZE_X				(100)																//!< テクスチャサイズX
#define TEXTURE_TIMELOGO_SIZE_Y				(75)																//!< テクスチャサイズY
#define TEXTURE_SCORE_POS_X					(SCREEN_CENTER_X-430.0f)											//!< テクスチャ座標X
#define TEXTURE_SCORE_POS_Y					(SCREEN_CENTER_Y+400.0f)											//!< テクスチャ座標Y
#define TEXTURE_TIME_POS_X					(SCREEN_CENTER_X+570.0f)											//!< テクスチャ座標X
#define TEXTURE_TIME_POS_Y					(TEXTURE_SCORE_POS_Y)												//!< テクスチャ座標Y
#define TEXTURE_SCORELOGO_POS_X				(SCREEN_CENTER_X-520.0f)											//!< テクスチャ座標X
#define TEXTURE_SCORELOGO_POS_Y				(TEXTURE_SCORE_POS_Y-120.0f)										//!< テクスチャ座標Y
#define TEXTURE_TIMELOGO_POS_X				(SCREEN_CENTER_X+520.0f)											//!< テクスチャ座標X
#define TEXTURE_TIMELOGO_POS_Y				(TEXTURE_TIME_POS_Y-100.0f)											//!< テクスチャ座標Y
#define NUM_INTERVAL_X						(60.0f)																//!< 数値間の間隔

//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct TIME
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< テクスチャへのポリゴン 
	VERTEX_2D				texture[NUM_VERTEX];																//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																				//!< ポリゴンの移動量
	D3DXVECTOR3				rot;																				//!< 回転角
	int						nCountAnim;																			//!< アニメカウント
	int						nPatternAnim;																		//!< アニメパターン
	bool					use;																				//!< 使用しているかどうか
} TIME;

/**
*　@struct SCORE
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< テクスチャへのポリゴン 
	VERTEX_2D				texture[NUM_VERTEX];																//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																				//!< ポリゴンの座標
	D3DXVECTOR3				rot;																				//!< ポリゴンの回転角
	int						nCountAnim;																			//!< アニメカウント
	int						nPatternAnim;																		//!< アニメパターン
	int						level;																				//!< 生きてるエネミーの数
} SCORE;

/**
*　@struct DOT
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< テクスチャへのポリゴン 
	VERTEX_2D				texture[NUM_VERTEX];																//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																				//!< ポリゴンの座標
} DOT;

/**
*　@struct TIMELOGO
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< テクスチャへのポリゴン 
	VERTEX_2D				texture[NUM_VERTEX];																//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																				//!< ポリゴンの座標
} TIMELOGO;

/**
*　@struct SCORELOGO
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< テクスチャへのポリゴン 
	VERTEX_2D				texture[NUM_VERTEX];																//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																				//!< ポリゴンの座標
} SCORELOGO;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Score初期化関数 InitScore
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitScore(int type);

/**
* @brief Score再初期化関数 ReInitScore
*/
void ReInitScore(void);

/**
* @brief Score開放関数 UninitScore
*/
void UninitScore(void);

/**
* @brief Score更新関数 UpdateScore
*/
void UpdateScore(void);

/**
* @brief Score描画関数 DrawScore
*/
void DrawScore(void);

/**
* @brief Score取得関数 GetScore
*/
SCORE *GetScore(void);

/**
* @brief Timemaneger取得関数 GetTimemaneger
* @return int
*/
int *GetTimemaneger(void);

/**
* @brief Scoremaneger取得関数 GetScoremaneger
* @return int
*/
int *GetScoremaneger(void);

/**
* @brief スコア、タイムを加減算する関数 AddScore
* @param[in] type 加算するタイプ,val 数値
*/
void AddScore(int val,int type);

