// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// weijian.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
#include <InitGuid.h>
// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������


#include "..\..\include\ACCef\ACCef.c"
//#include "..\baseclass\sha1.c"


string MakeBucketUrl()
{
// 	string strUrl = COS_BucketUrlProd;
// 	wstring wstrHost = TestModeHelper()->GetString(L"TestMode", L"BucketUrl", L"");
// 
// 	if (!wstrHost.empty())
// 	{
// 		CUTFString utf(wstrHost.c_str());
// 		strUrl = utf.ANSI();
// 	}

//	return strUrl;
	return "";
}


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <stdlib.h>


using namespace std;


//���ļ����뵽string��
string readFileIntoString(const char * filename)
{
	ifstream ifile(filename);
	//���ļ����뵽ostringstream����buf��
	ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
		buf.put(ch);
	//������������buf�������ַ���
	return buf.str();
}
