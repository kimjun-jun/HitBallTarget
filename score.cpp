/**
* @file score.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "score.h"
#include "fade.h"
#include "select.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);	// 
void SetVertexScore(void);					// 

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
SCORE g_score[SCORE_DIGIT];
static TIME  g_time[TIME_DIGIT];
static DOT g_dot;
static TIMELOGO g_timelogo;
static SCORELOGO g_scorelogo;


static int g_score_maneger;//�Q�b�g�����X�R�A
static int g_time_maneger;//�c�莞��
static int g_e_defeat;//�G�l�~�[��|������

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		TIME *time = &g_time[i];
		time->pos = D3DXVECTOR3(TEXTURE_TIME_POS_X - (NUM_INTERVAL_X*i), TEXTURE_TIME_POS_Y, 0.0f);
		time->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		time->nCountAnim = 0;
		time->nPatternAnim = 0;
		time->use = true;
		// �e�N�X�`���̓ǂݍ���  
		if (type == 0)	// ����̂ݓǂݍ���
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_GAME_SCORE,				// �t�@�C���̖��O
				&time->pD3DTexture);			// �ǂݍ��ރ������̃|�C���^
		}
	}

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		SCORE *score = &g_score[i];
		score->pos = D3DXVECTOR3(TEXTURE_SCORE_POS_X - (NUM_INTERVAL_X*i), TEXTURE_SCORE_POS_Y, 0.0f);
		score->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		score->nCountAnim = 0;
		score->nPatternAnim = 0;
		score->level = 0;
		// �e�N�X�`���̓ǂݍ���  
		if (type == 0)	// ����̂ݓǂݍ���
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_GAME_SCORE,				// �t�@�C���̖��O
				&score->pD3DTexture);			// �ǂݍ��ރ������̃|�C���^
		}
	}
	g_dot.pos = D3DXVECTOR3(g_time[0].pos.x-30.0f, TEXTURE_TIMELOGO_POS_Y+130.0f, 0.0f);
	g_dot.nCountAnim = 0;
	g_dot.nPatternAnim = 0;
	g_timelogo.pos = D3DXVECTOR3(TEXTURE_TIMELOGO_POS_X, TEXTURE_TIMELOGO_POS_Y, 0.0f);
	g_scorelogo.pos = D3DXVECTOR3(TEXTURE_SCORELOGO_POS_X, TEXTURE_SCORELOGO_POS_Y, 0.0f);
	// �e�N�X�`���̓ǂݍ���  
	if (type == 0)	// ����̂ݓǂݍ���
	{
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_GAME_DOT,				
			&g_dot.pD3DTexture);			

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_GAME_TIMELOGO,				
			&g_timelogo.pD3DTexture);			

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_GAME_SCORELOGO,				
			&g_scorelogo.pD3DTexture);			

	}
	g_score_maneger = 0;
	g_e_defeat = 0;
	g_time_maneger = FPS_TIME_COUNT;
	MakeVertexScore();
	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
void ReInitScore(void)
{
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		TIME *time = &g_time[i];
		time->nCountAnim = 0;
		time->nPatternAnim = 0;
		time->use = true;
	}

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		SCORE *score = &g_score[i];
		score->nCountAnim = 0;
		score->nPatternAnim = 0;
		score->level = 0;
	}
	g_dot.nCountAnim = 0;
	g_dot.nPatternAnim = 0;
	g_score_maneger = 0;
	g_e_defeat = 0;
	g_time_maneger = FPS_TIME_COUNT;
	MakeVertexScore();
	UpdateScore();
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		SCORE *score = &g_score[i];
		if (score->pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			score->pD3DTexture->Release();
			score->pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		TIME *time = &g_time[i];
		if (time->pD3DTexture != NULL)
		{	// �e�N�X�`���̊J��
			time->pD3DTexture->Release();
			time->pD3DTexture = NULL;
		}
	}
	if (g_dot.pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_dot.pD3DTexture->Release();
		g_dot.pD3DTexture = NULL;
	}
	if (g_timelogo.pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_timelogo.pD3DTexture->Release();
		g_timelogo.pD3DTexture = NULL;
	}
	if (g_scorelogo.pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_scorelogo.pD3DTexture->Release();
		g_scorelogo.pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	SetTextureScore();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		SCORE *score = &g_score[i];
		// �e�N�X�`���̐ݒ�  
		pDevice->SetTexture(0, score->pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, score->texture, sizeof(VERTEX_2D));
	}
	for (int i = 0; i < TIME_DIGIT; i++)
	{
		TIME *time = &g_time[i];
		if (time->use == true)
		{
			pDevice->SetTexture(0, time->pD3DTexture);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, time->texture, sizeof(VERTEX_2D));
		}
	}
	DOT *dot = &g_dot;
	pDevice->SetTexture(0, dot->pD3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, dot->texture, sizeof(VERTEX_2D));
	TIMELOGO *tlogo = &g_timelogo;
	pDevice->SetTexture(0, tlogo->pD3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, tlogo->texture, sizeof(VERTEX_2D));
	SCORELOGO *slogo = &g_scorelogo;
	pDevice->SetTexture(0, slogo->pD3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, slogo->texture, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_���W�̐ݒ�
	SetVertexScore();
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// rhw�̐ݒ�
		g_score[i].texture[0].rhw =
			g_score[i].texture[1].rhw =
			g_score[i].texture[2].rhw =
			g_score[i].texture[3].rhw = 1.0f;
		// ���ːݒ�  [i]
		g_score[i].texture[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_score[i].texture[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_score[i].texture[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_score[i].texture[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		// �e�N�����W[i]�̐ݒ�  
		g_score[i].texture[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_score[i].texture[1].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_score[i].texture[2].tex = D3DXVECTOR2(0.0f, 1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_Y);
		g_score[i].texture[3].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_Y);
	}
	for (int i = 0; i < TIME_DIGIT;i++)
	{
		g_time[i].texture[0].rhw =
			g_time[i].texture[1].rhw =
			g_time[i].texture[2].rhw =
			g_time[i].texture[3].rhw = 1.0f;
		g_time[i].texture[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_time[i].texture[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_time[i].texture[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_time[i].texture[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		g_time[i].texture[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_time[i].texture[1].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_time[i].texture[2].tex = D3DXVECTOR2(0.0f, 1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_Y);
		g_time[i].texture[3].tex = D3DXVECTOR2(1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_X, 1.0f / SCORE_TEXTURE_PATTERN_DIVIDE_Y);
	}

	g_dot.texture[0].rhw =
	g_dot.texture[1].rhw =
	g_dot.texture[2].rhw =
	g_dot.texture[3].rhw = 1.0f;
	g_dot.texture[0].diffuse = D3DCOLOR_RGBA(0,0,0, 255);
	g_dot.texture[1].diffuse = D3DCOLOR_RGBA(0,0,0, 255);
	g_dot.texture[2].diffuse = D3DCOLOR_RGBA(0,0,0, 255);
	g_dot.texture[3].diffuse = D3DCOLOR_RGBA(0,0,0, 255);
	g_dot.texture[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_dot.texture[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_dot.texture[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_dot.texture[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_scorelogo.texture[0].rhw =
	g_scorelogo.texture[1].rhw =
	g_scorelogo.texture[2].rhw =
	g_scorelogo.texture[3].rhw = 1.0f;
	g_scorelogo.texture[0].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_scorelogo.texture[1].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_scorelogo.texture[2].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_scorelogo.texture[3].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_scorelogo.texture[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_scorelogo.texture[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_scorelogo.texture[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_scorelogo.texture[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_timelogo.texture[0].rhw =
	g_timelogo.texture[1].rhw =
	g_timelogo.texture[2].rhw =
	g_timelogo.texture[3].rhw = 1.0f;
	g_timelogo.texture[0].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_timelogo.texture[1].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_timelogo.texture[2].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_timelogo.texture[3].diffuse = D3DCOLOR_RGBA(255,255,255, 255);
	g_timelogo.texture[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_timelogo.texture[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_timelogo.texture[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_timelogo.texture[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScore(void)
{
	int timeval = g_time_maneger;
	timeval /= 7;
	if (timeval > 0)
	{
		if (timeval <= 100)
		{
			g_time[0].texture[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[0].texture[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[0].texture[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[0].texture[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[1].texture[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[1].texture[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[1].texture[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[1].texture[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_time[2].use= false;

			g_dot.texture[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_dot.texture[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_dot.texture[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_dot.texture[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		}
		for (int i = 0; i < TIME_DIGIT; i++)
		{
			TIME *time = &g_time[i];
			float tx = (float)(timeval % 10);
			// �e�N�X�`�����W�̐ݒ�
			time->texture[0].tex = D3DXVECTOR2(tx*0.1f, 0.0f);
			time->texture[1].tex = D3DXVECTOR2((tx + 1)*0.1f, 0.0f);
			time->texture[2].tex = D3DXVECTOR2(tx*0.1f, 1.0f);
			time->texture[3].tex = D3DXVECTOR2((tx + 1)*0.1f, 1.0f);
			timeval /= 10;
		}
	}

	int val = g_score_maneger;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		SCORE *score = &g_score[i];
		float tx = (float)(val % 10);
		// �e�N�X�`�����W�̐ݒ�
		score->texture[0].tex = D3DXVECTOR2(tx*0.1f, 0.0f);
		score->texture[1].tex = D3DXVECTOR2((tx + 1)*0.1f, 0.0f);
		score->texture[2].tex = D3DXVECTOR2(tx*0.1f, 1.0f);
		score->texture[3].tex = D3DXVECTOR2((tx + 1)*0.1f, 1.0f);
		val /= 10;
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexScore(void)
{
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		SCORE *score = &g_score[i];
		// ���_���W�̐ݒ� 
		score->texture[0].vtx.x = score->pos.x - TEXTURE_SCORE_SIZE_X;
		score->texture[0].vtx.y = score->pos.y - TEXTURE_SCORE_SIZE_Y;
		score->texture[0].vtx.z = 0.0f;

		score->texture[1].vtx.x = score->pos.x + TEXTURE_SCORE_SIZE_X;
		score->texture[1].vtx.y = score->pos.y - TEXTURE_SCORE_SIZE_Y;
		score->texture[1].vtx.z = 0.0f;

		score->texture[2].vtx.x = score->pos.x - TEXTURE_SCORE_SIZE_X;
		score->texture[2].vtx.y = score->pos.y + TEXTURE_SCORE_SIZE_Y;
		score->texture[2].vtx.z = 0.0f;

		score->texture[3].vtx.x = score->pos.x + TEXTURE_SCORE_SIZE_X;
		score->texture[3].vtx.y = score->pos.y + TEXTURE_SCORE_SIZE_Y;
		score->texture[3].vtx.z = 0.0f;
	}

	for (int i = 0; i < TIME_DIGIT; i++)
	{
		TIME *time = &g_time[i];
		// ���_���W�̐ݒ� 
		time->texture[0].vtx.x = time->pos.x - TEXTURE_SCORE_SIZE_X;
		time->texture[0].vtx.y = time->pos.y - TEXTURE_SCORE_SIZE_Y;
		time->texture[0].vtx.z = 0.0f;

		time->texture[1].vtx.x = time->pos.x + TEXTURE_SCORE_SIZE_X;
		time->texture[1].vtx.y = time->pos.y - TEXTURE_SCORE_SIZE_Y;
		time->texture[1].vtx.z = 0.0f;

		time->texture[2].vtx.x = time->pos.x - TEXTURE_SCORE_SIZE_X;
		time->texture[2].vtx.y = time->pos.y + TEXTURE_SCORE_SIZE_Y;
		time->texture[2].vtx.z = 0.0f;

		time->texture[3].vtx.x = time->pos.x + TEXTURE_SCORE_SIZE_X;
		time->texture[3].vtx.y = time->pos.y + TEXTURE_SCORE_SIZE_Y;
		time->texture[3].vtx.z = 0.0f;
	}

	DOT *dot = &g_dot;
	// ���_���W�̐ݒ� 
	dot->texture[0].vtx.x = dot->pos.x - TEXTURE_DOT_SIZE_X;
	dot->texture[0].vtx.y = dot->pos.y - TEXTURE_DOT_SIZE_Y;
	dot->texture[0].vtx.z = 0.0f;
	dot->texture[1].vtx.x = dot->pos.x + TEXTURE_DOT_SIZE_X;
	dot->texture[1].vtx.y = dot->pos.y - TEXTURE_DOT_SIZE_Y;
	dot->texture[1].vtx.z = 0.0f;
	dot->texture[2].vtx.x = dot->pos.x - TEXTURE_DOT_SIZE_X;
	dot->texture[2].vtx.y = dot->pos.y + TEXTURE_DOT_SIZE_Y;
	dot->texture[2].vtx.z = 0.0f;
	dot->texture[3].vtx.x = dot->pos.x + TEXTURE_DOT_SIZE_X;
	dot->texture[3].vtx.y = dot->pos.y + TEXTURE_DOT_SIZE_Y;
	dot->texture[3].vtx.z = 0.0f;

	SCORELOGO *slogo = &g_scorelogo;
	slogo->texture[0].vtx.x = slogo->pos.x - TEXTURE_SCORELOGO_SIZE_X;
	slogo->texture[0].vtx.y = slogo->pos.y - TEXTURE_SCORELOGO_SIZE_Y;
	slogo->texture[0].vtx.z = 0.0f;
	slogo->texture[1].vtx.x = slogo->pos.x + TEXTURE_SCORELOGO_SIZE_X;
	slogo->texture[1].vtx.y = slogo->pos.y - TEXTURE_SCORELOGO_SIZE_Y;
	slogo->texture[1].vtx.z = 0.0f;
	slogo->texture[2].vtx.x = slogo->pos.x - TEXTURE_SCORELOGO_SIZE_X;
	slogo->texture[2].vtx.y = slogo->pos.y + TEXTURE_SCORELOGO_SIZE_Y;
	slogo->texture[2].vtx.z = 0.0f;
	slogo->texture[3].vtx.x = slogo->pos.x + TEXTURE_SCORELOGO_SIZE_X;
	slogo->texture[3].vtx.y = slogo->pos.y + TEXTURE_SCORELOGO_SIZE_Y;
	slogo->texture[3].vtx.z = 0.0f;

	TIMELOGO *tlogo = &g_timelogo;
	tlogo->texture[0].vtx.x = tlogo->pos.x - TEXTURE_TIMELOGO_SIZE_X;
	tlogo->texture[0].vtx.y = tlogo->pos.y - TEXTURE_TIMELOGO_SIZE_Y;
	tlogo->texture[0].vtx.z = 0.0f;
	tlogo->texture[1].vtx.x = tlogo->pos.x + TEXTURE_TIMELOGO_SIZE_X;
	tlogo->texture[1].vtx.y = tlogo->pos.y - TEXTURE_TIMELOGO_SIZE_Y;
	tlogo->texture[1].vtx.z = 0.0f;
	tlogo->texture[2].vtx.x = tlogo->pos.x - TEXTURE_TIMELOGO_SIZE_X;
	tlogo->texture[2].vtx.y = tlogo->pos.y + TEXTURE_TIMELOGO_SIZE_Y;
	tlogo->texture[2].vtx.z = 0.0f;
	tlogo->texture[3].vtx.x = tlogo->pos.x + TEXTURE_TIMELOGO_SIZE_X;
	tlogo->texture[3].vtx.y = tlogo->pos.y + TEXTURE_TIMELOGO_SIZE_Y;
	tlogo->texture[3].vtx.z = 0.0f;
}

//=============================================================================
// �X�R�A�̃A�h���X��Ԃ�
//=============================================================================
SCORE *GetScore(void)
{
	return &g_score[0];
}


//=============================================================================
// �^�C���̃A�h���X��Ԃ�
//=============================================================================
int *GetTimemaneger(void)
{
	return &g_time_maneger;
}

//=============================================================================
// �X�R�A�̃A�h���X��Ԃ�
//=============================================================================
int *GetScoremaneger(void)
{
	return &g_score_maneger;
}

//=============================================================================
// �X�R�A���Z����
//=============================================================================
void AddScore(int val,int type)
{
	if (type == TIME_VAL) g_time_maneger += val;
	else if (type == ENEMY_VAL) g_e_defeat++;
	else if(type ==SCORE_VAL) g_score_maneger += val;
	if (g_time_maneger == 0)
	{
		SetFade(FADE_OUT, SCENE_RESULT_FIELD, SOUND_LABEL_BGM_gameover01);
	}
	if (g_e_defeat >= ENEMY_GOUKEI + g_score[0].level) SetFade(FADE_OUT, SCENE_RESULT_CLEAR, SOUND_LABEL_BGM_gameclear01);
}
