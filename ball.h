///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	ball.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once


// マクロ定義
#define TEXTURE_GAME_BALLTYPE0	_T("data/TEXTURE/item/ball2.png")	// サンプル用画像  
#define TEXTURE_GAME_BALLTYPE1	_T("data/TEXTURE/effect/ballbom.png")	// サンプル用画像  


#define TEXTURE_BALL_SIZE_X	(20/2) // テクスチャサイズ 
#define TEXTURE_BALL_SIZE_Y	(20/2) // 同上 
#define TEXTURE_BALL_COLLISION_BB_SIZE_X	(20/2) // テクスチャサイズ 
#define TEXTURE_BALL_COLLISION_BB_SIZE_Y	(20/2) // 同上  
#define TEXTURE_BALL_COLLISION_BC_SIZE		((TEXTURE_BALL_SIZE_X+TEXTURE_BALL_SIZE_Y)/2) // バレット当たり判定BCテクスチャサイズ 



#define TEXTURE_BALLCURSOR_SIZE_X	(15/2) // テクスチャサイズ 
#define TEXTURE_BALLCURSOR_SIZE_Y	(15/2) // 同上  
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_X	(5/2) // テクスチャサイズ 
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_Y	(5/2) // 同上  
#define TEXTURE_BALLCURSOR_COLLISION_BC_SIZE		((TEXTURE_BALLCURSOR_SIZE_X+TEXTURE_BALLCURSOR_SIZE_Y)/2) // バレット当たり判定BCテクスチャサイズ 


#define TEXTURE_BALLSHADOW_SIZE_X	(15/2) // テクスチャサイズ 
#define TEXTURE_BALLSHADOW_SIZE_Y	(15/2) // 同上  
#define TEXTURE_BALLSHADOW_COLLISION_BC_SIZE		((TEXTURE_BALLSHADOW_SIZE_X+TEXTURE_BALLSHADOW_SIZE_Y)/2) // バレット当たり判定BCテクスチャサイズ 


#define BALL_MOTION_SPEED_MID			(2.0f) //ムーブ速度普通
#define BALL_MOTION_SPEED_FAST			(7.0f) //ムーブ速度早い
#define BALLCURSOR_MOTION_SPEED			(1.0f) //ムーブ速度早い
#define BALL_ROOT_MOTION_SPEED			(0.41f) //ルートムーブ速度
#define BALL_GOUKEI						(1) //ボールの合計
#define BALL_NO_0						(0)
#define TIME_BALLCURSOL_MOVECOUNT_MID			(50)

#define BALL_MAX							(3)//ボール合計
#define BALL_COUNT_MAX						(5)//貫通弾の貫通上限
#define BALL_ROT							(0.5f)//ボールの回転数

//*****************************************************************************
//* 構造体定義
//******************************************************************************* /
typedef struct // バレット構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン 
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;		// テクスチャへのポリゴン 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				oldpos;						// ポリゴンの移動量
	D3DXVECTOR3				effectoldpos[4];			// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量
	D3DXVECTOR3				oldrot;						// ポリゴンの回転量
	D3DXVECTOR3				move;						//移動量
	D3DXVECTOR3				oldmove;					//移動量

	int						direction;					// ポリゴンの移動方向
	int						penetcount;						//貫通弾のカウント
	int						diffcount;					//拡散弾のカウント
	int						effectcount;					//拡散弾のカウント
	float					changeVal;					//テクスチャサイズの変化量調整
	float					changeValTypeA;					//テクスチャサイズの変化量調整
	float					rad;
	float					BaseAngle;
	bool					OorD;						
	bool					use;
	bool					tuto;
	bool					effect;						//エフェクトの信号
	bool					diffflag;					//拡散のフラグ
	bool					diffsignal;					//拡散の信号（フラグ回収後一度INITLOOPが実行されてからONになる）
} BALL;

typedef struct // バレット構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量
	D3DXVECTOR3				move;						//移動量
	D3DXVECTOR3				oldmove;						//移動量
	int						movecount;					//カーソルの移動カウント
	int						direction;
	float					changeVal;					//変化量の調整
	bool					use;
} BALLCURSOR;

typedef struct // バレット構造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// テクスチャへのポリゴン 
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;		// テクスチャへのポリゴン 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	D3DXVECTOR3				pos;						// ポリゴンの移動量
	D3DXVECTOR3				rot;						// ポリゴンの回転量
	D3DXVECTOR3				move;						//移動量
	D3DXVECTOR3				oldmove;						//移動量
	float					changeVal;					//テクスチャサイズの変化量調整
	bool					use;
} BALLSHADOW;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBall(int type);
void ReInitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

HRESULT MakeVertexBall(void);
void SetVertexBall(void);					// 

BALL *GetBall(void);
BALLCURSOR *GetBallcursor(void);
BALLSHADOW *GetBallshadow(void);
void SetBall(D3DXVECTOR3 pos);
