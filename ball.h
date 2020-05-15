///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	ball.h
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#pragma once


// �}�N����`
#define TEXTURE_GAME_BALLTYPE0	_T("data/TEXTURE/item/ball2.png")	// �T���v���p�摜  
#define TEXTURE_GAME_BALLTYPE1	_T("data/TEXTURE/effect/ballbom.png")	// �T���v���p�摜  


#define TEXTURE_BALL_SIZE_X	(20/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_BALL_SIZE_Y	(20/2) // ���� 
#define TEXTURE_BALL_COLLISION_BB_SIZE_X	(20/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_BALL_COLLISION_BB_SIZE_Y	(20/2) // ����  
#define TEXTURE_BALL_COLLISION_BC_SIZE		((TEXTURE_BALL_SIZE_X+TEXTURE_BALL_SIZE_Y)/2) // �o���b�g�����蔻��BC�e�N�X�`���T�C�Y 



#define TEXTURE_BALLCURSOR_SIZE_X	(15/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_BALLCURSOR_SIZE_Y	(15/2) // ����  
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_X	(5/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_Y	(5/2) // ����  
#define TEXTURE_BALLCURSOR_COLLISION_BC_SIZE		((TEXTURE_BALLCURSOR_SIZE_X+TEXTURE_BALLCURSOR_SIZE_Y)/2) // �o���b�g�����蔻��BC�e�N�X�`���T�C�Y 


#define TEXTURE_BALLSHADOW_SIZE_X	(15/2) // �e�N�X�`���T�C�Y 
#define TEXTURE_BALLSHADOW_SIZE_Y	(15/2) // ����  
#define TEXTURE_BALLSHADOW_COLLISION_BC_SIZE		((TEXTURE_BALLSHADOW_SIZE_X+TEXTURE_BALLSHADOW_SIZE_Y)/2) // �o���b�g�����蔻��BC�e�N�X�`���T�C�Y 


#define BALL_MOTION_SPEED_MID			(2.0f) //���[�u���x����
#define BALL_MOTION_SPEED_FAST			(7.0f) //���[�u���x����
#define BALLCURSOR_MOTION_SPEED			(1.0f) //���[�u���x����
#define BALL_ROOT_MOTION_SPEED			(0.41f) //���[�g���[�u���x
#define BALL_GOUKEI						(1) //�{�[���̍��v
#define BALL_NO_0						(0)
#define TIME_BALLCURSOL_MOVECOUNT_MID			(50)

#define BALL_MAX							(3)//�{�[�����v
#define BALL_COUNT_MAX						(5)//�ђʒe�̊ђʏ��
#define BALL_ROT							(0.5f)//�{�[���̉�]��

//*****************************************************************************
//* �\���̒�`
//******************************************************************************* /
typedef struct // �o���b�g�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S�� 
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|���S�� 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				oldpos;						// �|���S���̈ړ���
	D3DXVECTOR3				effectoldpos[4];			// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��
	D3DXVECTOR3				oldrot;						// �|���S���̉�]��
	D3DXVECTOR3				move;						//�ړ���
	D3DXVECTOR3				oldmove;					//�ړ���

	int						direction;					// �|���S���̈ړ�����
	int						penetcount;						//�ђʒe�̃J�E���g
	int						diffcount;					//�g�U�e�̃J�E���g
	int						effectcount;					//�g�U�e�̃J�E���g
	float					changeVal;					//�e�N�X�`���T�C�Y�̕ω��ʒ���
	float					changeValTypeA;					//�e�N�X�`���T�C�Y�̕ω��ʒ���
	float					rad;
	float					BaseAngle;
	bool					OorD;						
	bool					use;
	bool					tuto;
	bool					effect;						//�G�t�F�N�g�̐M��
	bool					diffflag;					//�g�U�̃t���O
	bool					diffsignal;					//�g�U�̐M���i�t���O������xINITLOOP�����s����Ă���ON�ɂȂ�j
} BALL;

typedef struct // �o���b�g�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S�� 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��
	D3DXVECTOR3				move;						//�ړ���
	D3DXVECTOR3				oldmove;						//�ړ���
	int						movecount;					//�J�[�\���̈ړ��J�E���g
	int						direction;
	float					changeVal;					//�ω��ʂ̒���
	bool					use;
} BALLCURSOR;

typedef struct // �o���b�g�\����
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;		// �e�N�X�`���ւ̃|���S�� 
	LPDIRECT3DTEXTURE9		pD3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|���S�� 

	VERTEX_2D				vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				rot;						// �|���S���̉�]��
	D3DXVECTOR3				move;						//�ړ���
	D3DXVECTOR3				oldmove;						//�ړ���
	float					changeVal;					//�e�N�X�`���T�C�Y�̕ω��ʒ���
	bool					use;
} BALLSHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
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
