///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	ranking.cpp
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "register.h"
#include "ranking.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRanking(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
RANKING g_ranking[RANKINGMAX];//�����L���O
RANKINGLOGO g_rankinglogo[RANKINGLOGO_MAX];//�����L���O���S

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRanking(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		for (int i = 0; i < RANKINGMAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,
				TEXTURE_ALPHA,
				&g_ranking[i].namepD3DTexture);

			D3DXCreateTextureFromFile(pDevice,
				TEXTURE_NUM,
				&g_ranking[i].numpD3DTexture);

			D3DXCreateTextureFromFile(pDevice,
				TEXTURE_NUM,
				&g_ranking[i].scorepD3DTexture);
		}
	}

	g_ranking[0].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME147_POS_X, TEXTURE_RANKING_NAME123_POS_Y, 0.0f);
	g_ranking[1].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME258_POS_X, TEXTURE_RANKING_NAME123_POS_Y, 0.0f);
	g_ranking[2].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME369_POS_X, TEXTURE_RANKING_NAME123_POS_Y, 0.0f);
	g_ranking[3].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME147_POS_X, TEXTURE_RANKING_NAME456_POS_Y, 0.0f);
	g_ranking[4].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME258_POS_X, TEXTURE_RANKING_NAME456_POS_Y, 0.0f);
	g_ranking[5].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME369_POS_X, TEXTURE_RANKING_NAME456_POS_Y, 0.0f);
	g_ranking[6].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME147_POS_X, TEXTURE_RANKING_NAME789_POS_Y, 0.0f);
	g_ranking[7].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME258_POS_X, TEXTURE_RANKING_NAME789_POS_Y, 0.0f);
	g_ranking[8].namepos = D3DXVECTOR3(TEXTURE_RANKING_NAME369_POS_X, TEXTURE_RANKING_NAME789_POS_Y, 0.0f);

	g_ranking[0].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK147_POS_X, TEXTURE_RANKING_RANK123_POS_Y, 0.0f);
	g_ranking[1].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK258_POS_X, TEXTURE_RANKING_RANK123_POS_Y, 0.0f);
	g_ranking[2].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK369_POS_X, TEXTURE_RANKING_RANK123_POS_Y, 0.0f);
	g_ranking[3].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK147_POS_X, TEXTURE_RANKING_RANK456_POS_Y, 0.0f);
	g_ranking[4].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK258_POS_X, TEXTURE_RANKING_RANK456_POS_Y, 0.0f);
	g_ranking[5].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK369_POS_X, TEXTURE_RANKING_RANK456_POS_Y, 0.0f);
	g_ranking[6].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK147_POS_X, TEXTURE_RANKING_RANK789_POS_Y, 0.0f);
	g_ranking[7].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK258_POS_X, TEXTURE_RANKING_RANK789_POS_Y, 0.0f);
	g_ranking[8].numpos = D3DXVECTOR3(TEXTURE_RANKING_RANK369_POS_X, TEXTURE_RANKING_RANK789_POS_Y, 0.0f);

	for (int i = 0; i < RANKINGSOCRED; i++)
	{
		g_ranking[0].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE147_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE123_POS_Y, 0.0f);
		g_ranking[1].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE258_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE123_POS_Y, 0.0f);
		g_ranking[2].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE369_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE123_POS_Y, 0.0f);
		g_ranking[3].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE147_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE456_POS_Y, 0.0f);
		g_ranking[4].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE258_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE456_POS_Y, 0.0f);
		g_ranking[5].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE369_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE456_POS_Y, 0.0f);
		g_ranking[6].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE147_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE789_POS_Y, 0.0f);
		g_ranking[7].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE258_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE789_POS_Y, 0.0f);
		g_ranking[8].scorepos[i] = D3DXVECTOR3(TEXTURE_RANKING_SCORE369_POS_X + (i* TEXTURE_RANKING_SCORE_OFFSET_POS_X), TEXTURE_RANKING_SCORE789_POS_Y, 0.0f);
	}

	//logo���܂�







	// ���_���̍쐬
	MakeVertexRanking();

	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
void ReInitRanking(int type)
{

}

//=============================================================================
// �I������
//=============================================================================
void UninitRanking(void)
{
	for (int i = 0; i < RANKINGMAX; i++)
	{
		if (g_ranking[i].namepD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_ranking[i].namepD3DTexture->Release();
			g_ranking[i].namepD3DTexture = NULL;
		}
		if (g_ranking[i].numpD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_ranking[i].numpD3DTexture->Release();
			g_ranking[i].numpD3DTexture = NULL;
		}
		if (g_ranking[i].scorepD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_ranking[i].scorepD3DTexture->Release();
			g_ranking[i].scorepD3DTexture = NULL;
		}
	}

	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		if (g_rankinglogo[i].pD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_rankinglogo[i].pD3DTexture->Release();
			g_rankinglogo[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V�����@
//=============================================================================
void UpdateRanking(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RANKINGMAX; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_ranking[i].namepD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ranking[i].namevertexWk, sizeof(VERTEX_2D));



		pDevice->SetTexture(0, g_ranking[i].numpD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ranking[i].numvertexWk, sizeof(VERTEX_2D));
		


		pDevice->SetTexture(0, g_ranking[i].scorepD3DTexture);
		for (int j = 0; j < RANKINGSOCRED; j++)
		{
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_ranking[i].scorevertexWk[j], sizeof(VERTEX_2D));
		}
	}

	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		pDevice->SetFVF(FVF_VERTEX_2D);
		pDevice->SetTexture(0, g_rankinglogo[i].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_rankinglogo[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRanking(void)
{
	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	for (int i = 0; i < RANKINGMAX; i++)
	{
		g_ranking[i].namevertexWk[0].rhw =
			g_ranking[i].namevertexWk[1].rhw =
			g_ranking[i].namevertexWk[2].rhw =
			g_ranking[i].namevertexWk[3].rhw = 1.0f;
		g_ranking[i].namevertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].namevertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].namevertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].namevertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].namevertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_ranking[i].numvertexWk[0].rhw =
		g_ranking[i].numvertexWk[1].rhw =
		g_ranking[i].numvertexWk[2].rhw =
		g_ranking[i].numvertexWk[3].rhw = 1.0f;
		g_ranking[i].numvertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ranking[i].numvertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].numvertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].numvertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].numvertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		for (int j = 0; j < RANKINGSOCRED;j++)
		{
			g_ranking[i].scorevertexWk[0][j].rhw =
			g_ranking[i].scorevertexWk[1][j].rhw =
			g_ranking[i].scorevertexWk[2][j].rhw =
			g_ranking[i].scorevertexWk[3][j].rhw = 1.0f;
			g_ranking[i].scorevertexWk[0][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[1][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[2][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[3][j].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_ranking[i].scorevertexWk[0][j].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_ranking[i].scorevertexWk[1][j].tex = D3DXVECTOR2(1.0f, 0.0f);
			g_ranking[i].scorevertexWk[2][j].tex = D3DXVECTOR2(0.0f, 1.0f);
			g_ranking[i].scorevertexWk[3][j].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		g_rankinglogo[i].vertexWk[0].rhw =
		g_rankinglogo[i].vertexWk[1].rhw =
		g_rankinglogo[i].vertexWk[2].rhw =
		g_rankinglogo[i].vertexWk[3].rhw = 1.0f;
		g_rankinglogo[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rankinglogo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rankinglogo[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rankinglogo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rankinglogo[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRanking(void)
{
	for (int i = 0; i < RANKINGMAX; i++)
	{
		g_ranking[i].namevertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].namevertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].namevertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].namevertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_ranking[i].numvertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ranking[i].numvertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_ranking[i].numvertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_ranking[i].numvertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		for (int j = 0; j < RANKINGSOCRED; j++)
		{
			g_ranking[i].scorevertexWk[0][j].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_ranking[i].scorevertexWk[1][j].tex = D3DXVECTOR2(1.0f, 0.0f);
			g_ranking[i].scorevertexWk[2][j].tex = D3DXVECTOR2(0.0f, 1.0f);
			g_ranking[i].scorevertexWk[3][j].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		g_rankinglogo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rankinglogo[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rankinglogo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rankinglogo[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexRanking(void)
{
	// ���_���W�̐ݒ� 
	for (int i = 0; i < RANKINGMAX; i++)
	{
		g_ranking[i].namevertexWk[0].vtx.x = g_ranking[i].namepos.x - TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[0].vtx.y = g_ranking[i].namepos.y - TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[0].vtx.z = 0.0f;		  			  
		g_ranking[i].namevertexWk[1].vtx.x = g_ranking[i].namepos.x + TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[1].vtx.y = g_ranking[i].namepos.y - TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[1].vtx.z = 0.0f;		  			  
		g_ranking[i].namevertexWk[2].vtx.x = g_ranking[i].namepos.x - TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[2].vtx.y = g_ranking[i].namepos.y + TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[2].vtx.z = 0.0f;		  			  
		g_ranking[i].namevertexWk[3].vtx.x = g_ranking[i].namepos.x + TEXTURE_RANKING_NAME_SIZE_X;
		g_ranking[i].namevertexWk[3].vtx.y = g_ranking[i].namepos.y + TEXTURE_RANKING_NAME_SIZE_Y;
		g_ranking[i].namevertexWk[3].vtx.z = 0.0f;

		g_ranking[i].numvertexWk[0].vtx.x = g_ranking[i].numpos.x - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[0].vtx.y = g_ranking[i].numpos.y - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[0].vtx.z = 0.0f;					
		g_ranking[i].numvertexWk[1].vtx.x = g_ranking[i].numpos.x + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[1].vtx.y = g_ranking[i].numpos.y - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[1].vtx.z = 0.0f;					
		g_ranking[i].numvertexWk[2].vtx.x = g_ranking[i].numpos.x - TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[2].vtx.y = g_ranking[i].numpos.y + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[2].vtx.z = 0.0f;					
		g_ranking[i].numvertexWk[3].vtx.x = g_ranking[i].numpos.x + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[3].vtx.y = g_ranking[i].numpos.y + TEXTURE_RANKING_RANK_SIZE_X;
		g_ranking[i].numvertexWk[3].vtx.z = 0.0f;

		for (int j = 0; j < RANKINGSOCRED; j++)
		{
			g_ranking[i].scorevertexWk[j][0].vtx.x = g_ranking[i].scorepos[j].x - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][0].vtx.y = g_ranking[i].scorepos[j].y - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][0].vtx.z = 0.0f;			  
			g_ranking[i].scorevertexWk[j][1].vtx.x = g_ranking[i].scorepos[j].x + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][1].vtx.y = g_ranking[i].scorepos[j].y - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][1].vtx.z = 0.0f;			   
			g_ranking[i].scorevertexWk[j][2].vtx.x = g_ranking[i].scorepos[j].x - TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][2].vtx.y = g_ranking[i].scorepos[j].y + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][2].vtx.z = 0.0f;			   
			g_ranking[i].scorevertexWk[j][3].vtx.x = g_ranking[i].scorepos[j].x + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][3].vtx.y = g_ranking[i].scorepos[j].y + TEXTURE_RANKING_SCORE_SIZE_X;
			g_ranking[i].scorevertexWk[j][3].vtx.z = 0.0f;
		}
	}
	for (int i = 0; i < RANKINGLOGO_MAX; i++)
	{
		g_rankinglogo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rankinglogo[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rankinglogo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rankinglogo[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

}


RANKING *GetRanking(void)
{
	return &g_ranking[0];
}

