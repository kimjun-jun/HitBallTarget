/**
* @file meetstrike.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MEETSTRIKE_GOUKEI							(2)																	//!< ミートカーソルとストライク
																														
//ストライクゾーン
#define TEXTURE_GAME_STRIKE							_T("data/TEXTURE/item/strike.png")									//!< 読み込むテクスチャファイル名
#define TEXTURE_STRIKE_SIZE_X						(150/2)																//!< ポリゴンの幅 
#define TEXTURE_STRIKE_SIZE_Y						(180/2)																//!< ポリゴンの高さ
#define TEXTURE_STRIKE_COLLISION_BB_SIZE_X			(150/2)																//!< 当たり判定 BB ポリゴンの幅
#define TEXTURE_STRIKE_COLLISION_BB_SIZE_Y			(180/2)																//!< 当たり判定 BB ポリゴンの高さ
#define TEXTURE_STRIKE_COLLISION_BC_SIZE			((TEXTURE_STRIKE_SIZE_X+TEXTURE_STRIKE_SIZE_Y)/2)					//!< 当たり判定 BC テクスチャサイズ 
#define STRIKE_GOUKEI								(1)																	//!< ストライク構造体合計

//ミートカーソル
#define TEXTURE_GAME_CURSOR							_T("data/TEXTURE/item/batcursor.png")								//!< 読み込むテクスチャファイル名
#define TEXTURE_CURSOR_BIG_SIZE_X					(75/2)																//!< ポリゴンの幅 大
#define TEXTURE_CURSOR_BIG_SIZE_Y					(75/2)																//!< ポリゴンの高さ 大 
#define TEXTURE_CURSOR_BIG_COLLISION_BC_SIZE		((TEXTURE_CURSOR_BIG_SIZE_X+TEXTURE_CURSOR_BIG_SIZE_Y)/2)			//!< 当たり判定 BC テクスチャサイズ 大
#define TEXTURE_CURSOR_SMALL_SIZE_X					(30/2)																//!< ポリゴンの幅 小
#define TEXTURE_CURSOR_SMALL_SIZE_Y					(30/2)																//!< ポリゴンの高さ 小
#define TEXTURE_CURSOR_SMALL_COLLISION_BC_SIZE		((TEXTURE_CURSOR_SMALL_SIZE_X+TEXTURE_CURSOR_SMALL_SIZE_Y)/2)		//!< 当たり判定 BC テクスチャサイズ 小 
#define CURSOR_GOUKEI								(1)																	//!< ミートカーソル構造体合計


//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct MeetStrike
*　@brief 2Dポリゴンを定義する構造体
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																			//!< テクスチャへのポリゴン 
	VERTEX_2D				vertexWk[NUM_VERTEX];																		//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;																						//!< ポリゴンの移動量
	D3DXVECTOR3				rot;																						//!< ポリゴンの回転量
	int						direction;																					//!< ポリゴンの移動方向
	int						meet;																						//!< 大か小か
	bool					use;																						//!< 使用しているかどうか
} MeetStrike;

/**
*　@struct STRIKE
*　@brief 2Dポリゴンを定義する構造体 MeetStrike
*/
typedef struct
{
	MeetStrike s;
}STRIKE;

/**
*　@struct CURSOR
*　@brief 2Dポリゴンを定義する構造体 MeetStrike
*/
typedef struct
{
	MeetStrike c;
}CURSOR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief MeetStrike初期化関数 InitMeetStrike
* @param[in] type 初期化タイプ
* @return HRESULT
*/
HRESULT InitMeetStrike(int type);

/**
* @brief MeetStrike再初期化関数 ReInitMeetStrike
*/
void ReInitMeetStrike(void);

/**
* @brief MeetStrike開放関数 UninitMeetStrike
*/
void UninitMeetStrike(void);

/**
* @brief MeetStrike更新関数 UpdateMeetStrike
*/
void UpdateMeetStrike(void);

/**
* @brief MeetStrike描画関数 DrawMeetStrike
*/
void DrawMeetStrike(void);


/**
* @brief MeetStrike取得関数 GetStrike
* @return STRIKE
*/
STRIKE *GetStrike(void);

/**
* @brief MeetStrike取得関数 Get_Cursor
* @return CURSOR
*/
CURSOR *Get_Cursor(void);

/**
* @brief MeetStrike取得関数 SetVertexMeetStrike
* @param[in] CursorType カーソルタイプ
*/
void SetVertexMeetStrike(int CursorType);

