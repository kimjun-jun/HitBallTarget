/**
* @file enemy.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
/**
*�@@struct CAT
*�@@brief 2D�|���S�����`����\����(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< �e�N�X�`���ւ̃|�C���^ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;						//!< ���W
	D3DXVECTOR3				rot;						//!< ��]�p
	D3DXVECTOR3				move;						//!< �ړ���
	D3DXVECTOR3				oldmove;					//!< �Â��ړ���
	D3DXVECTOR3				oldpos;						//!< �Â����W
	D3DXVECTOR3				ppos[4];					//!< 4�����|���S���̊e�|���S�����S���W
	int						colori;						//!< �ϐF�l(int)
	int						nCountAnim;					//!< �A�j���J�E���g 
	int						nPatternAnim;				//!< �A�j���p�^�[�� 
	int						direction;					//!< �ړ�����
	int						movecount;					//!< �ړ��J�E���g
	int						point;						//!< ���_
	float					chengeval;					//!< �ω���
	float					oldchengeval;				//!< �Â��ω���
	bool					motion;						//!< ���[�V�������Ă��邩�ǂ���
	bool					use;						//!< �g�p���Ă��邩�ǂ���
	bool					color;						//!< �ϐF����
	bool					effect;						//!< �G�t�F�N�g����
} CAT;

/**
*�@@struct SURAIMU
*�@@brief 2D�|���S�����`����\����(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< �e�N�X�`���ւ̃|�C���^ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;						//!< ���W
	D3DXVECTOR3				rot;						//!< ��]�p
	D3DXVECTOR3				move;						//!< �ړ���
	D3DXVECTOR3				oldmove;					//!< �Â��ړ���
	D3DXVECTOR3				oldpos;						//!< �Â����W
	D3DXVECTOR3				ppos[4];					//!< 4�����|���S���̊e�|���S�����S���W
	int						colori;						//!< �ϐF�l(int)
	int						nCountAnim;					//!< �A�j���J�E���g 
	int						nPatternAnim;				//!< �A�j���p�^�[�� 
	int						direction;					//!< �ړ�����
	int						movecount;					//!< �ړ��J�E���g
	int						point;						//!< ���_
	float					chengeval;					//!< �ω���
	float					oldchengeval;				//!< �Â��ω���
	bool					motion;						//!< ���[�V�������Ă��邩�ǂ���
	bool					use;						//!< �g�p���Ă��邩�ǂ���
	bool					color;						//!< �ϐF����
	bool					effect;						//!< �G�t�F�N�g����
} SURAIMU;

/**
*�@@struct HINOTAMA
*�@@brief 2D�|���S�����`����\����(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< �e�N�X�`���ւ̃|�C���^ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;						//!< ���W
	D3DXVECTOR3				rot;						//!< ��]�p
	D3DXVECTOR3				move;						//!< �ړ���
	D3DXVECTOR3				oldmove;					//!< �Â��ړ���
	D3DXVECTOR3				oldpos;						//!< �Â����W
	D3DXVECTOR3				ppos[4];					//!< 4�����|���S���̊e�|���S�����S���W
	int						colori;						//!< �ϐF�l(int)
	int						nCountAnim;					//!< �A�j���J�E���g 
	int						nPatternAnim;				//!< �A�j���p�^�[�� 
	int						direction;					//!< �ړ�����
	int						movecount;					//!< �ړ��J�E���g
	int						point;						//!< ���_
	float					chengeval;					//!< �ω���
	float					oldchengeval;				//!< �Â��ω���
	bool					motion;						//!< ���[�V�������Ă��邩�ǂ���
	bool					use;						//!< �g�p���Ă��邩�ǂ���
	bool					color;						//!< �ϐF����
	bool					effect;						//!< �G�t�F�N�g����
} HINOTAMA;

/**
*�@@struct UFO
*�@@brief 2D�|���S�����`����\����(enemy)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			//!< �e�N�X�`���ւ̃|�C���^ 
	VERTEX_2D				vertexWk[NUM_ENEMY];		//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;						//!< ���W
	D3DXVECTOR3				rot;						//!< ��]�p
	D3DXVECTOR3				move;						//!< �ړ���
	D3DXVECTOR3				oldmove;					//!< �Â��ړ���
	D3DXVECTOR3				ppos[4];					//!< �Â����W
	D3DXVECTOR3				oldpos;						//!< 4�����|���S���̊e�|���S�����S���W
	int						nCountAnim;					//!< �ϐF�l(int)
	int						nPatternAnim;				//!< �A�j���J�E���g 
	int						direction;					//!< �A�j���p�^�[�� 
	int						colori;						//!< �ړ�����
	int						point;						//!< �ړ��J�E���g
	float					movecount;					//!< ���_
	float					rad;						//!< �ω���
	float					angle;						//!< �Â��ω���
	bool					motion;						//!< ���[�V�������Ă��邩�ǂ���
	bool					use;						//!< �g�p���Ă��邩�ǂ���
	bool					color;						//!< �ϐF����
	bool					effect;						//!< �G�t�F�N�g����
} UFO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Enemy�������֐� InitEnemy
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitEnemy(int type);

/**
* @brief Enemy�ď������֐� ReInitEnemy
*/
void ReInitEnemy(void);

/**
* @brief Enemy�J���֐� UninitEnemy
*/
void UninitEnemy(void);

/**
* @brief Enemy�X�V�֐� UpdateEnemy
*/
void UpdateEnemy(void);

/**
* @brief Enemy�`��֐� DrawEnemy
*/
void DrawEnemy(void);

/**
* @brief Enemy�擾�֐� GetCat
* @param[in] int i �A�h���X�Ԓn�w��
* @return CAT
*/
CAT *GetCat(int i);

/**
* @brief Enemy�擾�֐� GetSuraimu
* @param[in] int i �A�h���X�Ԓn�w��
* @return SURAIMU
*/
SURAIMU *GetSuraimu(int i);

/**
* @brief Enemy�擾�֐� GetHinotama
* @param[in] int i �A�h���X�Ԓn�w��
* @return HINOTAMA
*/
HINOTAMA *GetHinotama(int i);

/**
* @brief Enemy�擾�֐� GetUfo
* @param[in] int i �A�h���X�Ԓn�w��
* @return UFO
*/
UFO *GetUfo(int i);
