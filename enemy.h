///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	enemy.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once

//*****************************************************************************
//* ?���̒�?
//******************************************************************************* /
typedef struct // �v���C��??����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_ENEMY];		// ��?���i?��?�N
	D3DXVECTOR3				pos;						// ?���S���̈ړ���
	D3DXVECTOR3				rot;						// ?���S���̉�?��
	D3DXVECTOR3				move;						//�ړ���
	D3DXVECTOR3				oldmove;					//�ړ���
	D3DXVECTOR3				oldpos;
	D3DXVECTOR3				ppos[4];
	int						colori;
	int						nCountAnim;					// �A�j��?�V�����J�E���g 
	int						nPatternAnim;				// �A�j��?�V�����p??���i���o? 
	int						direction;					// ?���S���̈ړ�����
	int						movecount;
	int						point;
	float					chengeval;
	float					oldchengeval;
	bool					motion;						// ?�������Ă��� �U�������Ă��Ȃ�
	bool					use;						// �g�p���Ă��邩�ǂ���
	bool					color;
	bool					effect;
} CAT;

typedef struct // �v���C��??����
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

typedef struct // �v���C��??����
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

typedef struct // �v���C��??����
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
// �v���g?�C�v�錾
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
