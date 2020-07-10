/**
* @file balleffect.h
* @brief HitBallTarget(2D)�I���ăQ�[��(������)
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


// �}�N����`
#define BALLEFFECT_TEXTURETYPE0			_T("data/TEXTURE/item/ball2.png")	// �摜
#define BALLEFFECT_TEXTURETYPE1			_T("data/TEXTURE/effect/ballbom.png")	// �摜
#define BALLEFFECT_TEXTURE_SIZE_X	(20/2)		// �e�N�X�`���T�C�Y
#define BALLEFFECT_TEXTURE_SIZE_Y	(20/2)		// ����

#define BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define BALLEFFECT_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define BALLEFFECT_ANIM_PATTERN_NUM			(BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X*BALLEFFECT_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define BALLEFFECT_TIME_ANIMATION			(1)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define BALLEFFECT_NUM_PARTS 1
#define BALLEFFECT_NUM_BALLEFFECTS 5


//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�t�F�N�g�\����
{
	D3DXVECTOR3				pos;						// �|���S���̈ړ���
	D3DXVECTOR3				move;						// �ړ���
	int						PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int						CountAnim;					// �A�j���[�V�����J�E���g
	int						liveTime;
	LPDIRECT3DTEXTURE9		Texture;					// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	bool					isFinish;
}PARTICLE;

typedef struct	// �G�t�F�N�g�\����
{
	int				use;
	int				isEnding;
	bool			isRemoveOnFinish;
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	int				duration;
	int				elapsed;
	int				numFinish;
	int				balleffectCount;
	int				emitCounter;
	PARTICLE		pParticle[BALLEFFECT_NUM_PARTS];

}BALLEFFECT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Balleffect�������֐� InitBalleffect
* @param[in] type �������^�C�v�@INIT_TIME���p�B0:����@0�ȊO: 2��ڈȍ~
* @return HRESULT
*/
HRESULT InitBalleffect(int type);

/**
* @brief Balleffect�J���֐� UninitBalleffect
*/
void UninitBalleffect(void);

/**
* @brief Balleffect�X�V�֐� UpdateBalleffect
*/
void UpdateBalleffect(void);

/**
* @brief Balleffect�`��֐� DrawBalleffect
*/
void DrawBalleffect(void);

/**
* @brief Balleffect�ݒ�֐� SetBalleffect
* @param[in] D3DXVECTOR3 pos, int duration
*/
void SetBalleffect(D3DXVECTOR3 pos, int duration);
