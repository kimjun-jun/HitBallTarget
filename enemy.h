/**
* @file ememy.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
//* ?造体定?
//******************************************************************************* /
typedef struct // プレイヤ??造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// テクス?ャへの?リゴン 
	VERTEX_2D				vertexWk[NUM_ENEMY];		// 頂?情報格?ワ?ク
	D3DXVECTOR3				pos;						// ?リゴンの移動量
	D3DXVECTOR3				rot;						// ?リゴンの回?量
	D3DXVECTOR3				move;						//移動量
	D3DXVECTOR3				oldmove;					//移動量
	D3DXVECTOR3				oldpos;
	D3DXVECTOR3				ppos[4];
	int						colori;
	int						nCountAnim;					// アニメ?ションカウント 
	int						nPatternAnim;				// アニメ?ションパ??ンナンバ? 
	int						direction;					// ?リゴンの移動方向
	int						movecount;
	int						point;
	float					chengeval;
	float					oldchengeval;
	bool					motion;						// ?投球している 偽投球していない
	bool					use;						// 使用しているかどうか
	bool					color;
	bool					effect;
} CAT;

typedef struct // プレイヤ??造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;	
	VERTEX_2D				vertexWk[NUM_ENEMY];
	D3DXVECTOR3				pos;				
	D3DXVECTOR3				rot;				
	D3DXVECTOR3				move;				
	D3DXVECTOR3				oldmove;			
	D3DXVECTOR3				oldpos;
	D3DXVECTOR3				ppos[4];
	int						colori;
	int						nCountAnim;			
	int						nPatternAnim;		
	int						direction;	
	int						movecount;
	int						point;
	float					chengeval;
	float					oldchengeval;
	bool					motion;
	bool					use;
	bool					color;
	bool					effect;
} SURAIMU;

typedef struct // プレイヤ??造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	VERTEX_2D				vertexWk[NUM_ENEMY];
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	D3DXVECTOR3				move;
	D3DXVECTOR3				oldmove;
	D3DXVECTOR3				oldpos;
	D3DXVECTOR3				ppos[4];
	int						colori;
	int						nCountAnim;
	int						nPatternAnim;
	int						direction;
	int						movecount;
	int						point;
	float					chengeval;
	float					oldchengeval;
	bool					motion;
	bool					use;
	bool					color;
	bool					effect;
} HINOTAMA;

typedef struct // プレイヤ??造体
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			
	VERTEX_2D				vertexWk[NUM_ENEMY];		
	D3DXVECTOR3				pos;						
	D3DXVECTOR3				rot;						
	D3DXVECTOR3				move;						
	D3DXVECTOR3				oldmove;			
	D3DXVECTOR3				ppos[4];
	D3DXVECTOR3				oldpos;
	int						nCountAnim;					
	int						nPatternAnim;				
	int						direction;	
	int						colori;
	int						point;
	float					movecount;
	float					rad;
	float					angle;
	bool					motion;
	bool					use;
	bool					color;
	bool					effect;
} UFO;

//*****************************************************************************
// プロト?イプ宣言
//*****************************************************************************
HRESULT InitEnemy(int type);
void ReInitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
HRESULT MakeVertexEnemy(int i,int type);
void SetTextureEnemy(int cntPattern, int i,int type);	
void SetVertexEnemy(int i,int type);					
CAT *GetCat(int i);
SURAIMU *GetSuraimu(int i);
HINOTAMA *GetHinotama(int i);
UFO *GetUfo(int i);
