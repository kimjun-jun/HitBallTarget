/**
* @file ball.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAME_BALLTYPE0						_T("data/TEXTURE/item/ball2.png")							//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_GAME_BALLTYPE1						_T("data/TEXTURE/effect/ballbom.png")						//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_BALL_SIZE_X							(20/2)														//!< �e�N�X�`���T�C�YX
#define TEXTURE_BALL_SIZE_Y							(20/2)														//!< �e�N�X�`���T�C�YY 
#define TEXTURE_BALL_COLLISION_BB_SIZE_X			(20/2)														//!< �����蔻�� BB �T�C�YX
#define TEXTURE_BALL_COLLISION_BB_SIZE_Y			(20/2)														//!< �����蔻�� BB �T�C�YY
#define TEXTURE_BALL_COLLISION_BC_SIZE				((TEXTURE_BALL_SIZE_X+TEXTURE_BALL_SIZE_Y)/2)				//!< �����蔻�� BC �T�C�Y 
#define TEXTURE_BALLCURSOR_SIZE_X					(15/2)														//!< �e�N�X�`���T�C�YX
#define TEXTURE_BALLCURSOR_SIZE_Y					(15/2)														//!< �e�N�X�`���T�C�YY
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_X		(5/2)														//!< �����蔻�� BB �T�C�YX
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_Y		(5/2)														//!< �����蔻�� BB �T�C�YY
#define TEXTURE_BALLCURSOR_COLLISION_BC_SIZE		((TEXTURE_BALLCURSOR_SIZE_X+TEXTURE_BALLCURSOR_SIZE_Y)/2)	//!< �����蔻�� BC �T�C�Y 
#define TEXTURE_BALLSHADOW_SIZE_X					(15/2)														//!< �e�N�X�`���T�C�YX
#define TEXTURE_BALLSHADOW_SIZE_Y					(15/2)														//!< �e�N�X�`���T�C�YY
#define TEXTURE_BALLSHADOW_COLLISION_BC_SIZE		((TEXTURE_BALLSHADOW_SIZE_X+TEXTURE_BALLSHADOW_SIZE_Y)/2)	//!< �����蔻�� BC �T�C�Y
#define BALL_MOTION_SPEED_MID						(2.0f)														//!< �{�[�����x ����
#define BALL_MOTION_SPEED_FAST						(7.0f)														//!< �{�[�����x ����
#define BALLCURSOR_MOTION_SPEED						(1.0f)														//!< �{�[�����n�_���x
#define BALL_ROOT_MOTION_SPEED						(0.41f)														//!< �{�[�����[�g���x
#define TIME_BALLCURSOL_MOVECOUNT_MID				(50)														//!< �{�[���J�[�\���̈ړ��J�E���g
#define BALL_MAX									(3)															//!< �{�[�����v
#define BALL_COUNT_MAX								(5)															//!< �ђʒe�̊ђʏ��
#define BALL_ROT									(0.5f)														//!< �{�[���̉�]��

//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
/**
*�@@struct BALL
*�@@brief 2D�|���S�����`����\����(�{�[��)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;					//!< �e�N�X�`���ւ̃|�C���^ 
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;			//!< �e�N�X�`���ւ̃|�C���^ 
	VERTEX_2D				vertexWk[NUM_VERTEX];				//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;								//!< ���W
	D3DXVECTOR3				oldpos;								//!< �Â����W
	D3DXVECTOR3				effectoldpos[4];					//!< �G�t�F�N�g�̌Â����W
	D3DXVECTOR3				rot;								//!< ��]�p
	D3DXVECTOR3				oldrot;								//!< �Â���]�p
	D3DXVECTOR3				move;								//!< �ړ���
	D3DXVECTOR3				oldmove;							//!< �Â��ړ���
	int						direction;							//!< �ړ�����
	int						penetcount;							//!< �ђʒe�̃J�E���g
	int						diffcount;							//!< �g�U�e�̃J�E���g
	int						effectcount;						//!< �G�t�F�N�g�̃J�E���g
	float					changeVal;							//!< �e�N�X�`���T�C�Y�̕ω��ʒ���
	float					changeValTypeA;						//!< �e�N�X�`���T�C�Y�̕ω��ʒ���
	float					rad;								//!< �e�N�X�`���T�C�YXY��苁�߂�郉�W�A��
	float					BaseAngle;							//!< �e�N�X�`���T�C�YXY��苁�߂��p�x
	bool					OorD;								//!< �ŋ���������
	bool					use;								//!< �g�p���Ă��邩�ǂ���
	bool					tuto;								//!< �`���[�g���A�������ǂ���
	bool					effect;								//!< �G�t�F�N�g����
	bool					diffflag;							//!< �g�U�̃t���O
	bool					diffsignal;							//!< �g�U�̐M���i�t���O������xINITLOOP�����s����Ă���ON�ɂȂ�j
} BALL;

/**
*�@@struct BALLCURSOR
*�@@brief 2D�|���S�����`����\����(�{�[��)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;					//!< �e�N�X�`���ւ̃|�C���^ 
	VERTEX_2D				vertexWk[NUM_VERTEX];				//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;								//!< ���W
	D3DXVECTOR3				rot;								//!< ��]�p
	D3DXVECTOR3				move;								//!< �ړ���
	D3DXVECTOR3				oldmove;							//!< �Â��ړ���
	int						movecount;							//!< �J�[�\���̈ړ��J�E���g
	int						direction;							//!< �ړ�����
	float					changeVal;							//!< �ω��ʂ̒���
	bool					use;								//!< �g�p���Ă��邩�ǂ���
} BALLCURSOR;

/**
*�@@struct BALLSHADOW
*�@@brief 2D�|���S�����`����\����(�{�[��)
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;					//!< �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;			//!< �e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];				//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;								//!< ���W
	D3DXVECTOR3				rot;								//!< ��]�p
	D3DXVECTOR3				move;								//!< �ړ���
	D3DXVECTOR3				oldmove;							//!< �Â��ړ���
	float					changeVal;							//!< �e�N�X�`���T�C�Y�̕ω��ʒ���
	bool					use;								//!< �g�p���Ă��邩�ǂ���
} BALLSHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Ball�������֐� InitBall
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitBall(int type);

/**
* @brief Ball�ď������֐� ReInitBall
*/
void ReInitBall(void);

/**
* @brief Ball�J���֐� UninitBall
*/
void UninitBall(void);

/**
* @brief Ball�X�V�֐� UpdateBall
*/
void UpdateBall(void);

/**
* @brief Ball�`��֐� DrawBall
*/
void DrawBall(void);

/**
* @brief Ball�擾�֐� GetBall
* @return BALLCURSOR
*/
BALL *GetBall(void);

/**
* @brief Ball�擾�֐� GetBallcursor
* @return BALLCURSOR
*/
BALLCURSOR *GetBallcursor(void);

/**
* @brief Ball�擾�֐� GetBallshadow
* @return BALLSHADOW
*/
BALLSHADOW *GetBallshadow(void);

/**
* @brief �{�[���ݒ�֐� SetBall
* @param[in] D3DXVECTOR3 pos �Z�b�g������W
*/
void SetBall(D3DXVECTOR3 pos);

/**
* @brief �|���S�����_�ݒ�֐� SetVertexBall
*/
void SetVertexBall(void);
