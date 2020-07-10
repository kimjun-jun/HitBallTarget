/**
* @file ball.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_GAME_BALLTYPE0						_T("data/TEXTURE/item/ball2.png")							//!< 読み込むテクスチャファイル名
#define TEXTURE_GAME_BALLTYPE1						_T("data/TEXTURE/effect/ballbom.png")						//!< 読み込むテクスチャファイル名
#define TEXTURE_BALL_SIZE_X							(20/2)														//!< テクスチャサイズX
#define TEXTURE_BALL_SIZE_Y							(20/2)														//!< テクスチャサイズY 
#define TEXTURE_BALL_COLLISION_BB_SIZE_X			(20/2)														//!< 当たり判定 BB サイズX
#define TEXTURE_BALL_COLLISION_BB_SIZE_Y			(20/2)														//!< 当たり判定 BB サイズY
#define TEXTURE_BALL_COLLISION_BC_SIZE				((TEXTURE_BALL_SIZE_X+TEXTURE_BALL_SIZE_Y)/2)				//!< 当たり判定 BC サイズ 
#define TEXTURE_BALLCURSOR_SIZE_X					(15/2)														//!< テクスチャサイズX
#define TEXTURE_BALLCURSOR_SIZE_Y					(15/2)														//!< テクスチャサイズY
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_X		(5/2)														//!< 当たり判定 BB サイズX
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_Y		(5/2)														//!< 当たり判定 BB サイズY
#define TEXTURE_BALLCURSOR_COLLISION_BC_SIZE		((TEXTURE_BALLCURSOR_SIZE_X+TEXTURE_BALLCURSOR_SIZE_Y)/2)	//!< 当たり判定 BC サイズ 
#define TEXTURE_BALLSHADOW_SIZE_X					(15/2)														//!< テクスチャサイズX
#define TEXTURE_BALLSHADOW_SIZE_Y					(15/2)														//!< テクスチャサイズY
#define TEXTURE_BALLSHADOW_COLLISION_BC_SIZE		((TEXTURE_BALLSHADOW_SIZE_X+TEXTURE_BALLSHADOW_SIZE_Y)/2)	//!< 当たり判定 BC サイズ
#define BALL_MOTION_SPEED_MID						(2.0f)														//!< ボール速度 普通
#define BALL_MOTION_SPEED_FAST						(7.0f)														//!< ボール速度 早い
#define BALLCURSOR_MOTION_SPEED						(1.0f)														//!< ボール着地点速度
#define BALL_ROOT_MOTION_SPEED						(0.41f)														//!< ボールルート速度
#define TIME_BALLCURSOL_MOVECOUNT_MID				(50)														//!< ボールカーソルの移動カウント
#define BALL_MAX									(3)															//!< ボール合計
#define BALL_COUNT_MAX								(5)															//!< 貫通弾の貫通上限
#define BALL_ROT									(0.5f)														//!< ボールの回転数

//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
/**
*　@struct BALL
*　@brief 2Dポリゴンを定義する構造体(ボール)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;					//!< テクスチャへのポインタ 
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;			//!< テクスチャへのポインタ 
	VERTEX_2D				vertexWk[NUM_VERTEX];				//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;								//!< 座標
	D3DXVECTOR3				oldpos;								//!< 古い座標
	D3DXVECTOR3				effectoldpos[4];					//!< エフェクトの古い座標
	D3DXVECTOR3				rot;								//!< 回転角
	D3DXVECTOR3				oldrot;								//!< 古い回転角
	D3DXVECTOR3				move;								//!< 移動量
	D3DXVECTOR3				oldmove;							//!< 古い移動量
	int						direction;							//!< 移動方向
	int						penetcount;							//!< 貫通弾のカウント
	int						diffcount;							//!< 拡散弾のカウント
	int						effectcount;						//!< エフェクトのカウント
	float					changeVal;							//!< テクスチャサイズの変化量調整
	float					changeValTypeA;						//!< テクスチャサイズの変化量調整
	float					rad;								//!< テクスチャサイズXYより求めれるラジアン
	float					BaseAngle;							//!< テクスチャサイズXYより求めれる角度
	bool					OorD;								//!< 打球投球判定
	bool					use;								//!< 使用しているかどうか
	bool					tuto;								//!< チュートリアル中かどうか
	bool					effect;								//!< エフェクト判定
	bool					diffflag;							//!< 拡散のフラグ
	bool					diffsignal;							//!< 拡散の信号（フラグ回収後一度INITLOOPが実行されてからONになる）
} BALL;

/**
*　@struct BALLCURSOR
*　@brief 2Dポリゴンを定義する構造体(ボール)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;					//!< テクスチャへのポインタ 
	VERTEX_2D				vertexWk[NUM_VERTEX];				//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;								//!< 座標
	D3DXVECTOR3				rot;								//!< 回転角
	D3DXVECTOR3				move;								//!< 移動量
	D3DXVECTOR3				oldmove;							//!< 古い移動量
	int						movecount;							//!< カーソルの移動カウント
	int						direction;							//!< 移動方向
	float					changeVal;							//!< 変化量の調整
	bool					use;								//!< 使用しているかどうか
} BALLCURSOR;

/**
*　@struct BALLSHADOW
*　@brief 2Dポリゴンを定義する構造体(ボール)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;					//!< テクスチャへのポインタ
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;			//!< テクスチャへのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];				//!< 頂点情報格納ワーク
	D3DXVECTOR3				pos;								//!< 座標
	D3DXVECTOR3				rot;								//!< 回転角
	D3DXVECTOR3				move;								//!< 移動量
	D3DXVECTOR3				oldmove;							//!< 古い移動量
	float					changeVal;							//!< テクスチャサイズの変化量調整
	bool					use;								//!< 使用しているかどうか
} BALLSHADOW;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Ball初期化関数 InitBall
* @param[in] type 初期化タイプ　INIT_TIME利用。0:初回　0以外: 2回目以降
* @return HRESULT
*/
HRESULT InitBall(int type);

/**
* @brief Ball再初期化関数 ReInitBall
* @details ゲームループ後の初期化などで使用。多重でテクスチャ等の読み込みを防ぐためこの関数で初期化している
*/
void ReInitBall(void);

/**
* @brief Ball開放関数 UninitBall
*/
void UninitBall(void);

/**
* @brief Ball更新関数 UpdateBall
*/
void UpdateBall(void);

/**
* @brief Ball描画関数 DrawBall
*/
void DrawBall(void);

/**
* @brief Ball取得関数 GetBall
* @return BALLCURSOR
*/
BALL *GetBall(void);

/**
* @brief Ball取得関数 GetBallcursor
* @return BALLCURSOR
*/
BALLCURSOR *GetBallcursor(void);

/**
* @brief Ball取得関数 GetBallshadow
* @return BALLSHADOW
*/
BALLSHADOW *GetBallshadow(void);

/**
* @brief ボール設定関数 SetBall
* @param[in] D3DXVECTOR3 pos セットする座標
*/
void SetBall(D3DXVECTOR3 pos);

/**
* @brief ポリゴン頂点設定関数 SetVertexBall
*/
void SetVertexBall(void);
