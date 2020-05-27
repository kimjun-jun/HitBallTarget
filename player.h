/**
* @file player.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct PLAYER_PIT
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	CHARACTER pp;			//!< プレイヤーピッチャー
} PLAYER_PIT;

/**
*　@struct PLAYER_BAT
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	CHARACTER pb;			//!< プレイヤーバッター
} PLAYER_BAT;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Player初期化関数 InitPlayer
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitPlayer(int type);

/**
* @brief Player再初期化関数 ReInitPlayer
*/
void ReInitPlayer(void);

/**
* @brief Player開放関数 UninitPlayer
*/
void UninitPlayer(void);

/**
* @brief Player更新関数 UpdatePlayer
*/
void UpdatePlayer(void);

/**
* @brief Player描画関数 DrawPlayer
*/
void DrawPlayer(void);

/**
* @brief PlayerPit取得関数 GetPlayerPit
* @return PLAYER_PIT
*/
PLAYER_PIT *GetPlayerPit(void);

/**
* @brief PlayerBat取得関数 GetPlayerBat
* @return PLAYER_BAT
*/
PLAYER_BAT *GetPlayerBat(void);

/**
* @brief テクスチャ設定関数 SetTexturePlayer
* @param[in] int cntPattern アニメパターン, int PLYAER_TYPE プレイヤータイプ
*/
void SetTexturePlayer(int cntPattern, int PLYAER_TYPE);

/**
* @brief ポリゴン頂点設定関数 SetVertexPlayer
* @param[in] int PLYAER_TYPE プレイヤータイプ
*/
void SetVertexPlayer(int PLYAER_TYPE);
