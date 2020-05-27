/**
* @file ranking.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NUM							_T("data/TEXTURE/BG/0-9.png")				//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ALPHA						_T("data/TEXTURE/sozai/keyborad.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKINGLOGO					_T("data/TEXTURE/sozai/ranklogo.png")		//!< �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_RANKING_LOGO_SIZE_X			(200)										//!< �|���S���̕�
#define TEXTURE_RANKING_LOGO_SIZE_Y			(100)										//!< �|���S���̍���
#define	TEXTURE_RANKING_RANK_SIZE_X			(200)										//!< �|���S���̕�
#define	TEXTURE_RANKING_RANK_SIZE_Y			(100)										//!< �|���S���̍���
#define	TEXTURE_RANKING_SCORE_SIZE_X		(20)										//!< �|���S���̕�
#define	TEXTURE_RANKING_SCORE_SIZE_Y		(20)										//!< �|���S���̍���
#define	TEXTURE_RANKING_NAME_SIZE_X			(200)										//!< �|���S���̕�
#define	TEXTURE_RANKING_NAME_SIZE_Y			(100)										//!< �|���S���̍���
#define TEXTURE_RANKING_LOGO_POS_X			(SCREEN_CENTER_X)							//!< �|���S���̍��WX
#define TEXTURE_RANKING_LOGO_POS_Y			(SCREEN_CENTER_Y-300.0f)					//!< �|���S���̍��WY
#define	RANKINGSOCRED						(4)											//!< �o�^�����X�R�A�̌���
#define	RANKINGMAX							(9)											//!< �o�^�ł��鍇�v��
#define	RANKINGLOGO_MAX						(1)											//!< ���S�̍��v
#define	TEXTURE_RANKING_SCORE_OFFSET_POS_X	(10.0f)										//!< ���ʂ̕\���Ԋu�I�t�Z�b�g�l

/**
*�@@struct RANKING
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		namepD3DTexture = NULL;										//!< �e�N�X�`���ւ̃|���S�� 
	LPDIRECT3DTEXTURE9		numpD3DTexture = NULL;										//!< �e�N�X�`���ւ̃|���S�� 
	LPDIRECT3DTEXTURE9		scorepD3DTexture = NULL;									//!< �e�N�X�`���ւ̃|���S�� 
	VERTEX_2D				namevertexWk[NUM_VERTEX];									//!< ���_���i�[���[�N
	VERTEX_2D				numvertexWk[NUM_VERTEX];									//!< ���_���i�[���[�N
	VERTEX_2D				scorevertexWk[RANKINGSOCRED][NUM_VERTEX];					//!< ���_���i�[���[�N[��][���_]
	D3DXVECTOR3				namepos;													//!< �|���S���̍��W
	D3DXVECTOR3				numpos;														//!< �|���S���̍��W
	D3DXVECTOR3				scorepos[RANKINGSOCRED];									//!< �|���S���̍��W[����]
	bool					use;														//!< �g�p���Ă��邩�ǂ���
}RANKING;


/**
*�@@struct RANKINGLOGO
*�@@brief 2D�|���S�����`����\����
*/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;											//!< �e�N�X�`���ւ̃|���S��
	VERTEX_2D				vertexWk[NUM_VERTEX];										//!< ���_���i�[���[�N
	D3DXVECTOR3				pos;														//!< �|���S���̍��W
	bool					use;														//!< �g�p���Ă��邩�ǂ���
}RANKINGLOGO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief Ranking�������֐� InitRanking
* @param[in] type �������^�C�v
* @return HRESULT
*/
HRESULT InitRanking(int type);

/**
* @brief Ranking�ď������֐� ReInitRanking
*/
void ReInitRanking(int type);

/**
* @brief Ranking�J���֐� UninitRanking
*/
void UninitRanking(void);

/**
* @brief Ranking�X�V�֐� UpdateRanking
*/
void UpdateRanking(void);

/**
* @brief Ranking�`��֐� DrawRanking
*/
void DrawRanking(void);

/**
* @brief Ranking�擾�֐� GetRanking
* @return RANKING
*/
RANKING *GetRanking(void);
