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
#define	TEXTURE_NUM					_T("data/TEXTURE/BG/0-9.png")		
#define	TEXTURE_ALPHA				_T("data/TEXTURE/sozai/keyborad.png")		
#define	TEXTURE_RANKINGLOGO			_T("data/TEXTURE/sozai/ranklogo.png")		

#define TEXTURE_RANKING_LOGO_SIZE_X			(200)										// �^�C�g�����S�̕�
#define TEXTURE_RANKING_LOGO_SIZE_Y			(100)										// �^�C�g�����S�̍���
#define	TEXTURE_RANKING_RANK_SIZE_X			(200)					
#define	TEXTURE_RANKING_RANK_SIZE_Y			(100)					
#define	TEXTURE_RANKING_SCORE_SIZE_X		(20)					
#define	TEXTURE_RANKING_SCORE_SIZE_Y		(20)					
#define	TEXTURE_RANKING_NAME_SIZE_X			(200)					
#define	TEXTURE_RANKING_NAME_SIZE_Y			(100)					
					   

#define TEXTURE_RANKING_LOGO_POS_X			(SCREEN_CENTER_X)							// �^�C�g�����S�̕�
#define TEXTURE_RANKING_LOGO_POS_Y			(SCREEN_CENTER_Y-300.0f)					// �^�C�g�����S�̍���

#define	TEXTURE_RANKING_RANK147_POS_X			(SCREEN_CENTER_X-300.0f)
#define	TEXTURE_RANKING_RANK258_POS_X			(SCREEN_CENTER_X)					
#define	TEXTURE_RANKING_RANK369_POS_X			(SCREEN_CENTER_X+300.0f)	
#define	TEXTURE_RANKING_RANK123_POS_Y			(SCREEN_CENTER_Y-300.0f)
#define	TEXTURE_RANKING_RANK456_POS_Y			(SCREEN_CENTER_Y)					
#define	TEXTURE_RANKING_RANK789_POS_Y			(SCREEN_CENTER_Y+300.0f)					

#define	TEXTURE_RANKING_SCORE147_POS_X			(SCREEN_CENTER_X-200.0f)
#define	TEXTURE_RANKING_SCORE258_POS_X			(SCREEN_CENTER_X)
#define	TEXTURE_RANKING_SCORE369_POS_X			(SCREEN_CENTER_X+200.0f)
#define	TEXTURE_RANKING_SCORE123_POS_Y			(SCREEN_CENTER_Y-300.0f)
#define	TEXTURE_RANKING_SCORE456_POS_Y			(SCREEN_CENTER_Y)
#define	TEXTURE_RANKING_SCORE789_POS_Y			(SCREEN_CENTER_Y+300.0f)

#define	TEXTURE_RANKING_NAME147_POS_X			(SCREEN_CENTER_X-100.0f)
#define	TEXTURE_RANKING_NAME258_POS_X			(SCREEN_CENTER_X)					
#define	TEXTURE_RANKING_NAME369_POS_X			(SCREEN_CENTER_X+100.0f)	
#define	TEXTURE_RANKING_NAME123_POS_Y			(SCREEN_CENTER_Y-300.0f)
#define	TEXTURE_RANKING_NAME456_POS_Y			(SCREEN_CENTER_Y)					
#define	TEXTURE_RANKING_NAME789_POS_Y			(SCREEN_CENTER_Y+300.0f)					


#define	RANKINGSOCRED		(4)						//�|�[�Y��ʂ̑I������
#define	RANKINGMAX			(9)						//�|�[�Y��ʂ̑I������
#define	RANKINGLOGO_MAX		(1)						//�|�[�Y��ʂ̑I������

#define	TEXTURE_RANKING_SCORE_OFFSET_POS_X			(10.0f)

typedef struct
{
	LPDIRECT3DTEXTURE9		namepD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	LPDIRECT3DTEXTURE9		numpD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	LPDIRECT3DTEXTURE9		scorepD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 

	VERTEX_2D				namevertexWk[NUM_VERTEX];		// ��?���i?��?�N
	VERTEX_2D				numvertexWk[NUM_VERTEX];		// ��?���i?��?�N
	VERTEX_2D				scorevertexWk[RANKINGSOCRED][NUM_VERTEX];		// [��][���_]

	D3DXVECTOR3				namepos;						// ?���S���̈ړ���
	D3DXVECTOR3				numpos;						// ?���S���̈ړ���
	D3DXVECTOR3				scorepos[RANKINGSOCRED];						// ?���S���̈ړ���

	bool					use;
}RANKING;


typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture = NULL;			// �e�N�X?���ւ�?���S�� 
	VERTEX_2D				vertexWk[NUM_VERTEX];		// ��?���i?��?�N
	D3DXVECTOR3				pos;						// ?���S���̈ړ���
	bool					use;
}RANKINGLOGO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRanking(int type);
void ReInitRanking(int type);
void UninitRanking(void);
void UpdateRanking(void);
void UpdateinRanking(void);
void DrawRanking(void);
void SetTextureRanking(void);
void SetVertexRanking(void);
RANKING *GetRanking(void);
