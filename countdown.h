/**
* @file countdown.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


// マクロ定義
#define TEXTURE_GAME_COUNTDOWNGO					_T("data/TEXTURE/sozai/go.png")											//!< 読み込むテクスチャファイル名
#define TEXTURE_COUNTDOWN_SIZE_X					(50)																	//!< テクスチャサイズX
#define TEXTURE_COUNTDOWN_SIZE_Y					(50)																	//!< テクスチャサイズY
#define TEXTURE_COUNTDOWNGO_SIZE_X					(200)																	//!< テクスチャサイズX
#define TEXTURE_COUNTDOWNGO_SIZE_Y					(200)																	//!< テクスチャサイズY
#define COUNTDOWN_TEXTURE_PATTERN_DIVIDE_X			(10)																	//!< アニメパターンのテクスチャ内分割数（X)  
#define COUNTDOWN_TEXTURE_PATTERN_DIVIDE_Y			(1)																		//!< アニメパターンのテクスチャ内分割数（Y)  
#define COUNTDOWN_ANIM_PATTERN_NUM					(COUNTDOWN_TEXTURE_PATTERN_DIVIDE_X*COUNTDOWN_TEXTURE_PATTERN_DIVIDE_Y)	//!< アニメーションパターン数  
#define COUNTDOWN_TIME_ANIMATION					(4)																		//!< アニメーションの切り替わるカウント  
#define TEXTURE_COUNTDOWN_POS_X						(SCREEN_CENTER_X)														//!< ポリゴンの初期座標X
#define TEXTURE_COUNTDOWN_POS_Y						(SCREEN_CENTER_Y)														//!< ポリゴンの初期座標Y  
#define COUNTDOWN_GOUKEI							(2)																		//!< カウントダウン構造体の合計
#define COUNTDOWN_NUM								(3)																		//!< カウントダウン数値
#define FPS_TIME_COUNTDOWN							(240)																	//!< カウントダウン合計値
#define COUNTDOWN_ALPHA_SUB							(10)																	//!< スタートLOGOが透明になるスピード
#define COUNTDOWN_CHANGESIZE						(5)																		//!< カウントダウン中の数値が大きくなるスピード

//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct COUNTDOWN
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																				//!< テクスチャへのポインタ
	VERTEX_2D				texture[NUM_VERTEX];																		  	//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																						  	//!< ポリゴンの座標
	int						nCountAnim;																					  	//!< アニメカウント
	int						nPatternAnim;																				  	//!< アニメパターン
	int						changeval;																					  	//!< 変化量
	int						alpha;																						  	//!< アルファ値
	bool					use;																							//!< 使用しているかどうか
	bool					signal;																							//!< 使用するか判定用フラグ
} COUNTDOWN;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Countdown初期化関数 InitCountdown
* @param[in] type 初期化タイプ　INIT_TIME利用。0:初回　0以外: 2回目以降
* @return HRESULT
*/
HRESULT InitCountdown(int type);

/**
* @brief Countdown再初期化関数 ReInitCountdown
* @details ゲームループ後の初期化などで使用。多重でテクスチャ等の読み込みを防ぐためこの関数で初期化している
*/
void ReInitCountdown(void);

/**
* @brief Countdown開放関数 UninitCountdown
*/
void UninitCountdown(void);

/**
* @brief Countdown更新関数 UpdateCountdown
*/
void UpdateCountdown(void);

/**
* @brief Countdown描画関数 DrawCountdown
*/
void DrawCountdown(void);

/**
* @brief Countdown取得関数 GetCountdown
* @return COUNTDOWN
*/
COUNTDOWN *GetCountdown(void);

/**
* @brief Countdown取得関数 AddCountdown
* @param[in] val 減算値
*/
void AddCountdown(int val);

