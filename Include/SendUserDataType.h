/*************************************************************************
/*
/* ħ������  ����Ƶ����ͷ�ļ�
/*
/************************************************************************/
#pragma once

enum  SendUserDataType
{
	SendUserDataType_MAGIC=1,
	SendUserDataType_AUDIO=2,
	SendUserDataType_VIDEO=3,
	SendUserDataType_BEAN=4,
	SendUserDataType_DING=5,

	SendUserDataType_B2S_STU_Show=10,
	SendUserDataType_B2S_STU_Close=11,
	SendUserDataType_B2S_STU_Show_Other=12,

	SendUserDataType_AddClass=20,
	SendUserDataType_AddClass_Accept=21,

	SendUserDataType_ClassFix_Info = 33,
	SendUserDataType_ClassFix_Remote = 34,

	SendUserDataType_SWITCHAUDIO = 40,

	SendUserDataType_ChangePDF = 51,
	SendUserDataType_SyncCanvas = 52,
	SendUserDataType_ChangeInteract = 53,
	SendUserDataType_RemoteUserSDKSwitched = 54,

	//���̲�֪ͨ
	SendStuChangeBookComplete=80,
	SendTeaChangeBookComplete=81,

	//��ǽ֪ͨ
	SendVideoOnWall=90,
	//��ǽ֪ͨ
	SendVideoOffWall=91,
	//�Լ�¼��ʧ�ܣ�֪ͨ�Է�¼��
	SendSnapShot=100,

	//1v1��Ƶ�Ŵ�ԭ
	SendUserDataType_1V1ideoZoomIn = 110,
	SendUserDataType_1V1VideoZoomOut = 111,

	//1v1�װ�ħ������
	SendUserDataType_1V1WBMagic_Play = 120,
	SendUserDataType_1V1WBMagic_Stop = 121,
	SendUserDataType_1V1WBMagic_Close = 122,
	SendUserDataType_1V1WBMagic_DownloadComplete = 123,

	//Demo ��Ƶ����

	SendUserDataType_Demo_Audio_mute = 130,
	SenduserDataType_Demo_Audio_unmute = 131
};