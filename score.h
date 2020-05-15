///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	score.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once


// �}�N����`
#define TEXTURE_GAME_DOT	_T("data/TEXTURE/BG/dot.png")	
#define TEXTURE_SCORE_SIZE_X	(50) // �e�N�X�`���T�C�Y 
#define TEXTURE_SCORE_SIZE_Y	(50) // ����  
#define SCORE_TEXTURE_PATTERN_DIVIDE_X	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define SCORE_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define SCORE_ANIM_PATTERN_NUM			(SCORE_TEXTURE_PATTERN_DIVIDE_X*SCORE_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����  
#define SCORE_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g  
#define TEXTURE_DOT_SIZE_X	(7) // �e�N�X�`���T�C�Y 
#define TEXTURE_DOT_SIZE_Y	(7) // ����  


#define DOT_GOUKEI					(2)
#define TIME_DIGIT					(3)
#define SCORE_DIGIT					(4)
#define SCORE_GOUKEI				(60) //�X�R�A�̍��v
#define FPS_TIME_COUNT				(4200) //���t���[���J�E���g���ă^�C���v��


#define TEXTURE_GAME_SCORELOGO	_T("data/TEXTURE/sozai/SCORE.png") 
#define TEXTURE_GAME_TIMELOGO	_T("data/TEXTURE/sozai/TIME.png") 
#define TEXTURE_SCORELOGO_SIZE_X	(100) // �e�N�X�`���T�C�Y
#define TEXTURE_SCORELOGO_SIZE_Y	(75) // ����  
#define TEXTURE_TIMELOGO_SIZE_X	(100) // �e�N�X�`���T�C�Y 
#define TEXTURE_TIMELOGO_SIZE_Y	(75) // ����  

#define TEXTURE_SCORE_POS_X	(SCREEN_CENTER_X-430.0f) // �e�N�X�`���T�C�Y
#define TEXTURE_SCORE_POS_Y	(SCREEN_CENTER_Y+400.0f) // ����  
#define TEXTURE_TIME_POS_X	(SCREEN_CENTER_X+570.0f) // �e�N�X�`���T�C�Y 
#define TEXTURE_TIME_POS_Y	(TEXTURE_SCORE_POS_Y) // ����  


#define TEXTURE_SCORELOGO_POS_X	(SCREEN_CENTER_X-520.0f) // �e�N�X�`���T�C�Y
#define TEXTURE_SCORELOGO_POS_Y	(TEXTURE_SCORE_POS_Y-120.0f) // ����  
#define TEXTURE_TIMELOGO_POS_X	(SCREEN_CENTER_X+520.0f) // �e�N�X�`���T�C�Y 
#define TEXTURE_TIMELOGO_POS_Y	(TEXTURE_TIME_POS_Y-100.0f) // ����  

#define NUM_INTERVAL_X	(60.0f) // ����  

//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
typedef struct // �G�l�~�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		

	VERTEX_2D				texture[NUM_VERTEX];

	D3DXVECTOR3				pos;					
	D3DXVECTOR3				rot;					
	int						nCountAnim;				
	int						nPatternAnim;
	bool					use;
} TIME;

typedef struct // �G�l�~�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		

	VERTEX_2D				texture[NUM_VERTEX];

	D3DXVECTOR3				pos;					
	D3DXVECTOR3				rot;					
	int						nCountAnim;				
	int						nPatternAnim;
	int						level;
} SCORE;

typedef struct // �G�l�~�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		

	VERTEX_2D				texture[NUM_VERTEX];

	D3DXVECTOR3				pos;					
	int						nCountAnim;				
	int						nPatternAnim;			
} DOT;

typedef struct // �G�l�~�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	VERTEX_2D				texture[NUM_VERTEX];
	D3DXVECTOR3				pos;
} TIMELOGO;

typedef struct // �G�l�~�[�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;
	VERTEX_2D				texture[NUM_VERTEX];
	D3DXVECTOR3				pos;
} SCORELOGO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void ReInitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
SCORE *GetScore(void);
int *GetTimemaneger(void);
int *GetScoremaneger(void);
void AddScore(int val,int type);

