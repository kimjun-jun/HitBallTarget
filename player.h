/**
* @file player.h
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#pragma once


//*****************************************************************************
//* ?���̒�?
//******************************************************************************* /
typedef struct // �v���C��??����
{
	CHARACTER pp;
} PLAYER_PIT;

typedef struct // �v���C��??����
{
	CHARACTER pb;
} PLAYER_BAT;


//*****************************************************************************
// �v���g?�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void ReInitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

HRESULT MakeVertexPlayer(int i);
void SetTexturePlayer(int cntPattern, int i);	// 
void SetVertexPlayer(int i);					// 

PLAYER_PIT *GetPlayerPit(void);
PLAYER_BAT *GetPlayerBat(void);
