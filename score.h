/**
* @file score.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_GAME_DOT					_T("data/TEXTURE/BG/dot.png")										//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SCORE_SIZE_X				(50)																//!< �e�N�X�`���T�C�YY
#define TEXTURE_SCORE_SIZE_Y				(50)																//!< �e�N�X�`���T�C�YX  
#define SCORE_TEXTURE_PATTERN_DIVIDE_X		(10)																//!< �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define SCORE_TEXTURE_PATTERN_DIVIDE_Y		(1)																	//!< �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define SCORE_ANIM_PATTERN_NUM				(SCORE_TEXTURE_PATTERN_DIVIDE_X*SCORE_TEXTURE_PATTERN_DIVIDE_Y)		//!< �A�j���[�V�����p�^�[����  
#define SCORE_TIME_ANIMATION				(4)																	//!< �A�j���[�V�����̐؂�ւ��J�E���g  
#define TEXTURE_DOT_SIZE_X					(7)																	//!< �e�N�X�`���T�C�YX
#define TEXTURE_DOT_SIZE_Y					(7)																	//!< �e�N�X�`���T�C�YY  
#define TIME_DIGIT							(3)																	//!< �^�C���̌���
#define SCORE_DIGIT							(4)																	//!< �X�R�A�̌���
#define SCORE_GOUKEI						(60)																//!< �X�R�A�̍��v
#define FPS_TIME_COUNT						(4200)																//!< �^�C���̍��v
#define TEXTURE_GAME_SCORELOGO				_T("data/TEXTURE/sozai/SCORE.png") 									//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAME_TIMELOGO				_T("data/TEXTURE/sozai/TIME.png") 									//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SCORELOGO_SIZE_X			(100)																//!< �e�N�X�`���T�C�YX
#define TEXTURE_SCORELOGO_SIZE_Y			(75)																//!< �e�N�X�`���T�C�YY
#define TEXTURE_TIMELOGO_SIZE_X				(100)																//!< �e�N�X�`���T�C�YX
#define TEXTURE_TIMELOGO_SIZE_Y				(75)																//!< �e�N�X�`���T�C�YY
#define TEXTURE_SCORE_POS_X					(SCREEN_CENTER_X-430.0f)											//!< �e�N�X�`�����WX
#define TEXTURE_SCORE_POS_Y					(SCREEN_CENTER_Y+400.0f)											//!< �e�N�X�`�����WY
#define TEXTURE_TIME_POS_X					(SCREEN_CENTER_X+570.0f)											//!< �e�N�X�`�����WX
#define TEXTURE_TIME_POS_Y					(TEXTURE_SCORE_POS_Y)												//!< �e�N�X�`�����WY
#define TEXTURE_SCORELOGO_POS_X				(SCREEN_CENTER_X-520.0f)											//!< �e�N�X�`�����WX
#define TEXTURE_SCORELOGO_POS_Y				(TEXTURE_SCORE_POS_Y-120.0f)										//!< �e�N�X�`�����WY
#define TEXTURE_TIMELOGO_POS_X				(SCREEN_CENTER_X+520.0f)											//!< �e�N�X�`�����WX
#define TEXTURE_TIMELOGO_POS_Y				(TEXTURE_TIME_POS_Y-100.0f)											//!< �e�N�X�`�����WY
#define NUM_INTERVAL_X						(60.0f)																//!< ���l�Ԃ̊Ԋu

//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
/**
*�@@struct TIME
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				texture[NUM_VERTEX];																//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																				//!< �|���S���̈ړ���
	D3DXVECTOR3				rot;																				//!< ��]�p
	int						nCountAnim;																			//!< �A�j���J�E���g
	int						nPatternAnim;																		//!< �A�j���p�^�[��
	bool					use;																				//!< �g�p���Ă��邩�ǂ���
} TIME;

/**
*�@@struct SCORE
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				texture[NUM_VERTEX];																//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																				//!< �|���S���̈ړ���
	D3DXVECTOR3				rot;																				//!< �|���S���̉�]�p
	int						nCountAnim;																			//!< �A�j���J�E���g
	int						nPatternAnim;																		//!< �A�j���p�^�[��
	int						level;																				//!< �����Ă�G�l�~�[�̐�
} SCORE;

/**
*�@@struct DOT
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				texture[NUM_VERTEX];																//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																				//!< �|���S���̈ړ���
} DOT;

/**
*�@@struct TIMELOGO
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				texture[NUM_VERTEX];																//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																				//!< �|���S���̈ړ���
} TIMELOGO;

/**
*�@@struct SCORELOGO
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;																	//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				texture[NUM_VERTEX];																//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;																				//!< �|���S���̈ړ���
} SCORELOGO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Score�������֐� InitScore
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitScore(int type);

/**
* @brief Score�ď������֐� ReInitScore
*/
void ReInitScore(void);

/**
* @brief Score�J���֐� UninitScore
*/
void UninitScore(void);

/**
* @brief Score�X�V�֐� UpdateScore
*/
void UpdateScore(void);

/**
* @brief Score�`��֐� DrawScore
*/
void DrawScore(void);

/**
* @brief Score�擾�֐� GetScore
*/
SCORE *GetScore(void);

/**
* @brief Timemaneger�擾�֐� GetTimemaneger
* @return int
*/
int *GetTimemaneger(void);

/**
* @brief Scoremaneger�擾�֐� GetScoremaneger
* @return int
*/
int *GetScoremaneger(void);

/**
* @brief �X�R�A�A�^�C���������Z����֐� AddScore
* @param[in] type ���Z����^�C�v
*/
void AddScore(int val,int type);

