// Exp_Receiver.cpp : Defines the entry point for the application.
//��ϢͨѶ��������γ̣������ŵ���������·��Э��ʵ�֣����ն˳��� 2024.3
#pragma warning(disable:4996)

#include "stdafx.h"
//VC 2010   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <bitset>

using namespace std;

//----------------------------------------------------------------------------------------
//��ť
#define BTN_Quit 501
#define BTN_Reset 502
//���б༭��
#define EDIT_Receiver 601
//�����ı���
#define INFOWin1 801
#define INFOWin2 802
//��̬�ı�
#define STATIC_W1 701
#define STATIC_W2 702
//----------------------------------------------------------------------------------------
WSADATA wsData;
SOCKET Cs1,Cs2;
struct sockaddr_in Cs1A,Cs2A;
char DataB[200];
int d,i;
#define Cs2Port 7100		//Զ�̶˿�(��Ӧ��ģ��ͨ�������еı��ض˿�)
#define Cs1Port 8100		//���ض˿�(��Ӧ��ģ��ͨ�������е�Bվ�˿�)
#define Cs1IP   "127.0.0.1"	//����IP��ַ(127.0.0.1Ϊ���ػ�·)
#define Cs2IP   "127.0.0.1"	//Զ��IP��ַ(127.0.0.1Ϊ���ػ�·)

char DisplayStringBuffer[5000];//��ʾ������
//----------------------------------------------------------------------------------------
// Global Variables:
HINSTANCE hInst;						// current instance
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);//�ص�����
//----------------------------------------------------------------------------------------
//������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	string TempString;
	char TempChar[80];
	char TempChar1[80];
	itoa(Cs1Port,TempChar,10);
	TempString = "���ն�[�˿�:";
	TempString += TempChar;
	TempString += "]�������ŵ�\0";
	
	HWND hWnd;
	hInst = hInstance; // Store instance handle in our global variable
	WNDCLASS wc;

	memset(&wc,0,sizeof(WNDCLASS));

	wc.lpfnWndProc	= (WNDPROC)WndProc;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground	= (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName	= "W1";
	RegisterClass(&wc);

	TempString.copy(TempChar1,TempString.length());
	TempChar1[TempString.length()] = 0x00;
	hWnd=CreateWindow("W1",TempChar1,
		WS_DLGFRAME|WS_SYSMENU,
		400,10,320,300,
		NULL,NULL,hInstance,NULL);

   	if (!hWnd)   return FALSE;

   	ShowWindow(hWnd, nCmdShow);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

//----------------------------------------------------------------------------------------
//������̬�ı���
HWND CreateStatic(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW,"STATIC",Titel,
		WS_VISIBLE | WS_CHILD ,
		x0,y0,w,h, hW,(HMENU)ID,hInst,NULL);
}

//----------------------------------------------------------------------------------------
//������ť
HWND CreateButton(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW,"BUTTON",Titel,
		WS_VISIBLE | WS_CHILD ,
		x0,y0,w,h, hW,(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//�������б༭��
HWND CreateEdit(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Titel,
		WS_VISIBLE | WS_CHILD |
		    ES_LEFT | ES_MULTILINE | WS_HSCROLL ,
		x0,y0,w,h, hW,
		(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//���������ı���
HWND CreateMemo(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Titel,
		WS_VISIBLE | WS_CHILD |
		    ES_LEFT | ES_MULTILINE |ES_READONLY|
		    WS_HSCROLL | WS_VSCROLL,
		x0,y0,w,h,
		hW,(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//��ӿؼ��ı�
void Puts(HWND hW,int ID_EDIT,char *str)
{	
	GetDlgItemText(hW,ID_EDIT,DisplayStringBuffer,sizeof(DisplayStringBuffer));
	if (strlen(DisplayStringBuffer) > 4900)
	{
		//MessageBox(0,"��ʾ�����������","��ʾ������",0);
		strcpy(DisplayStringBuffer,"  \r\n");
	};
	strcat(DisplayStringBuffer,"\r\n");
	strcat(DisplayStringBuffer,str);
	SetDlgItemText(hW,ID_EDIT,(LPSTR) DisplayStringBuffer);
	SendMessage(GetDlgItem(hW,ID_EDIT),WM_VSCROLL,SB_THUMBPOSITION+1000*0x10000,0);
}
//----------------------------------------------------------------------------------------
//���ϲ���Ķ�!
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//����������ﶨ���±���
void PhysicalLayerSend(char* FrameData, int Length);	//����㣺����һ֡����
int PhysicalLayerReceive(char* FrameData, int Length);	//����㣺���ձ������ݣ��������ݳ���
int PhysicalLayerReceive(char* FrameData);

#define ACK 0X88
#define NAK 0X55
#define HEAD 0XFE  
#define TAIL 0XFD

uint8_t GenerateCRC(const uint8_t* Data, size_t FrameLength); //CRC������������size_t������int����ΪLength��ȷ��

struct FrameData
{
	bool FrameCheckStatus;//�ж��Ƿ�ɹ��������ݣ���ʼ���ȴ�ʱ��Ϊ0
	char FrameDataBuffer[256];//������
	int FrameBufferLength;//����������
};

FrameData MyFrameData;//֡����
extern int State = 0;//Ŀǰ����״̬��0�������ã�1������յ�֡ͷ��2������յ�֡β
extern int FrameLength = 0;//ʵ�ʽ��յ����ܴ����֡�ĳ��ȣ�����ʱӦ�ڽ��յ�TAIL��ͬʱ������5
extern int Tail = 4;//֡β�������±꣬�����λ�÷���֡���ֽ�
extern int WrongRec = 0;
extern int WrongRecLen = 0;
extern char* WrongRecCnt = new char[256];
extern char* BufOfSame = new char[1024];
extern int LengthOfSame = 0;

//----------------------------------------------------------------------------------------
//����������
int ProtocolOfFrame(unsigned char* ReceData, int nLength, HWND hW);//֡���ݴ���
int FrameDataInit();//֡���ݵĳ�ʼ��

//----------------------------------------------------------------------------------------
//��Ϣ����
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP)
{
	switch (msg)
	{
	case WM_DESTROY://���ڹر�ʱ����Ϣ����
		WSAAsyncSelect(Cs1, hW, 0, 0);
		closesocket(Cs1);
		WSACleanup( );
		PostQuitMessage(0);
		break;
	case WM_CREATE://���ڴ���ʱ����Ϣ����
		WSAStartup(0x0101,&wsData);//�����ʼ��
		Cs1=socket(AF_INET, SOCK_DGRAM,0);
		Cs1A.sin_family=AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
//		Cs1A.sin_addr.s_addr =INADDR_ANY;//�ڱ������õ���ַ(���ܶ��)�У�����Ч��
		Cs1A.sin_addr.s_addr =inet_addr(Cs1IP);
		d=bind(Cs1,(struct sockaddr *) &Cs1A,sizeof(Cs1A));
		if(d==-1)//bind��������ʧ��
		{
			MessageBox(0,"�˿ڷ�����ͻ","�ŵ�ģ��",0);
			PostQuitMessage(0);
		};
		Cs2A.sin_family=AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr =inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1,hW,WM_USER+212,FD_READ);
		Beep(2000,100);//������ʾ����

		CreateEdit("���ն�",2,2,130,20,EDIT_Receiver,hW,hInst);
		CreateButton("�˳�", 140,2,50,24,BTN_Quit,hW,hInst);
		CreateButton("��λ",200,2,50,24,BTN_Reset,hW,hInst);
		CreateStatic("������յ�����Ϣ:",0,35,150,24,STATIC_W1,hW,hInst);
		CreateStatic("�Ͻ���������Ϣ:",160,35,150,24,STATIC_W2,hW,hInst);
		CreateMemo(" ",0,55,150,220,INFOWin1,hW,hInst);
		CreateMemo(" ",160,55,150,220,INFOWin2,hW,hInst);

		break;
//============================================================================
//������Ϣ�¼���
//�������������Ӻͱ�д���룺
	case WM_USER+212:
		switch(LOWORD(lP))
		{
		case FD_READ://�������ݽ�����Ϣ����
			//*****************************************************************************
			//��������֡���մ������ڴ˸���Э���޸Ļ���Ӵ���
			//����13�д���ֻ�����ڲ��ԣ�����Ҫ����Э������޸�
			//*****************************************************************************

			//���ǵ�һ�����
			/*//char ReceData[100];
			//int Length;
			//Length=PhysicalLayerReceive(ReceData);					//����㣺����һ���ֽ�
			//DataB[0] = ReceData[0];
			//DataB[1]=0;
			//char DisplayBufffer[250];
			//wsprintf(DisplayBufffer,"%02XH",(unsigned char)DataB[0]);
			//Puts(hW,INFOWin1,DisplayBufffer);						//��ʾ��������յ�����Ϣ
			//DataB[0]=(DataB[0]&0x0F)+0x30;							//ȥ����4λ����,��4λתΪASCII��
			//Puts(hW,INFOWin2,DataB);								//��ʾ���Ͻ���������Ϣ
			//char SendData[100];
			//SendData[0] = 0x88;
			//PhysicalLayerSend(&(SendData[0]),1);					//����㣺����һ���ֽ�,��ʾ������ȷ
			//break;
			*/
			char ReceData[100];
			int Length;
			char DisplayBufffer[250];
			Length = PhysicalLayerReceive(ReceData, 100); // ����㣺����һ���ֽ�

			ProtocolOfFrame((unsigned char*)ReceData, Length, hW);
			Sleep(50);//sleep��Ϊ�˰������
			//*****************************************************************************
			/*
			char ReceData[100];
			memset(ReceData, 0, 100);
			int Length;
			char DisplayBufffer[250];								//������
			Length = PhysicalLayerReceive(ReceData,100);					//����㣺����һ֡����
			*/
			/*
			ԭ���룺
			DataB[0] = ReceData[0];
			DataB[1]=0;
			wsprintf(DisplayBufffer,"%02XH",(unsigned char)DataB[0]);
			Puts(hW,INFOWin1,DisplayBufffer);						//��ʾ��������յ�����Ϣ
			DataB[0]=(DataB[0]&0x0F)+0x30;							//ȥ����4λ����,��4λתΪASCII��
			Puts(hW,INFOWin2,DataB);								//��ʾ���Ͻ���������Ϣ
			char SendData[100];
			SendData[0] = 0x88;
			PhysicalLayerSend(&(SendData[0]),1);	
			*/
			//*****************************************************************************
			break;
		}
		break;
//============================================================================
	case WM_COMMAND://��ť������Ϣ����
		switch(wP)
		{
		case BTN_Quit:												//�˳�����
			PostQuitMessage(0);
			break;
		case BTN_Reset:												//�����Ϣ������
			SetDlgItemText(hW,INFOWin1,(LPSTR) " ");
			SetDlgItemText(hW,INFOWin2,(LPSTR) " ");
			break;
		}
	}
	return DefWindowProc(hW, msg, wP, lP);
}

//----------------------------------------------------------------------------------------
//����㱨��֡���ͺ���������һ֡��������
//���������char* FrameData�����ͱ���֡����ָ��
//          int Length������֡���ݳ���
//�����������
void PhysicalLayerSend(char* FrameData, int Length)					
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, CS2A_Length);
}

//----------------------------------------------------------------------------------------
//�����������ݺ���������һ֡���ģ��������ݳ��ȡ�
//һ֡���Ŀ����ɶ���ֽڹ��ɣ��ú���ִ��һ�ο���֪ʶ�����˱���֡��һ���ֽڻ�һ���֣�
//ͨ����Ҫ���ִ�иú������Ա������������֡��
//���������char* FrameData�����ձ�������ָ��
//���������int ��������ֵ��Ϊ�������ݵĳ���


int PhysicalLayerReceive(char* FrameData,int Length)//Length�����ջ���������
{
	/*int Length;
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	Length = recvfrom(Cs1,FrameData,sizeof(FrameData),0,(struct sockaddr *) &Cs2A,&CS2A_Length);
	return Length;*/
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	return recvfrom(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, &CS2A_Length);
}

int PhysicalLayerReceive(char* FrameData)
{
	int Length;
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	Length = recvfrom(Cs1,FrameData,sizeof(FrameData),0,(struct sockaddr *) &Cs2A,&CS2A_Length);
	return Length;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

//֡���ݴ���
int ProtocolOfFrame(unsigned char* ReceData, int nLength, HWND hW)//nLength��֡����
{		
	char SendData[100];
	
		/*
		switch ((unsigned char)ReceData[0])
		{
		case 0xfe:
			ProtocolFrameDataInit();
			TestFrameData.FrameDataBuffer[TestFrameData.CurrentFrameReceivedPos] = ReceData[0];
			TestFrameData.CurrentFrameReceivedPos++;
			SendData[0] = 0x88;
			PhysicalLayerSend(&(SendData[0]), 2);
		case 0xfd:
			DataB[0] = TestFrameData.FrameDataBuffer[2];
			DataB[1] = 0;

			for (int i = 0; i < nLength; i++)//�����������ȡ�����������Ϣ
			{
				char testBuf[64];
				wsprintf(testBuf, "%02XH", (unsigned char)TestFrameData.FrameDataBuffer[i]);
				Puts(hW, INFOWin1, testBuf);						//��ʾ��������յ�����Ϣ
			}
			Puts(hW, INFOWin1, "*******************");

			int i;
			for (i = 0; i < 5; i++)
			{
				//switch ((unsigned char)TestFrameData.FrameDataBuffer[i])
								//		case 0xfd://֡�������ٷ���ACK�����֡���������д����֡���������ݲ���ȷ���д�
								//			if (TestFrameData.CurrentFrameReceivedPos != 4)//���յ�0xfd��״̬������4˵��֡������ʧ
				if (i == 4)//���յ�0xfd��״̬������4˵��֡������ʧ
				{
					switch ((unsigned char)TestFrameData.FrameDataBuffer[i])
					{
					case 0xfd:
						TestFrameData.FrameCheckStatus = 1;
					default:
						TestFrameData.FrameCheckStatus = 0;
						char buf[22];
						wsprintf(buf, "Message missing");
						Puts(hW, INFOWin1, buf);
						break;
					};
					char DisplayBufffer[250];
					DataB[0] = (DataB[0] & 0x0F) + 0x30;							//ȥ����4λ����,��4λתΪASCII��
					wsprintf(DisplayBufffer, "%02XH, %c", (unsigned char)DataB[0], DataB[0]);
					Puts(hW, INFOWin2, DisplayBufffer);

					//����У�飨ʹ�ü�У��ͣ�����ʹ��CRC���飩
					int Temp = 0x0;
					Temp += TestFrameData.FrameDataBuffer[0];
					Temp += TestFrameData.FrameDataBuffer[1];
					Temp += TestFrameData.FrameDataBuffer[2];
					if (Temp == TestFrameData.FrameDataBuffer[3])//�Ƚ�У��״̬
					{
						TestFrameData.FrameCheckStatus = 1;
					}
					else
					{
						TestFrameData.FrameCheckStatus = 0;
					}

					//�д�����0x55��������0x88
					if (TestFrameData.FrameCheckStatus)
					{
						//SendData[0] = 0x88;
						//PhysicalLayerSend(&(SendData[0]), 1);
						//char buf[22];
						//wsprintf(buf, "0x%02xh, %c", (unsigned char)TestFrameData.FrameDataBuffer);
						//Puts(hW, INFOWin2, buf);
						//DataB[2] = (DataB[2] & 0x0F) + 0x30;							//ȥ����4λ����,��4λתΪASCII��
						//Puts(hW,INFOWin2,DataB);								//��ʾ���Ͻ���������Ϣ
						SendData[0] = 0x88;
						PhysicalLayerSend(&(SendData[0]), 2);					//����㣺����һ���ֽ�,��ʾ������ȷ
					}
					else
					{
						SendData[0] = 0x55;
						PhysicalLayerSend(&(SendData[0]), 2);
					};
				}
				break;
			}
		default:
			TestFrameData.FrameDataBuffer[TestFrameData.CurrentFrameReceivedPos] = ReceData[0];
			TestFrameData.CurrentFrameReceivedPos++;
			SendData[0] = 0x88;
			PhysicalLayerSend(&(SendData[0]), 2);
		}*/
for (int i = 0; i < nLength; i++)//��ȡ��Ϣ��������ѭ����nLength����Ϊ������һ���Խ��յ����ٸ��ֽڣ������������д��
{
	MyFrameData.FrameDataBuffer[FrameLength] = ReceData[i];
	FrameLength++;
}

//�������if����Է�ʽ���Ľ��
//˼·�ǣ�����������ط�4���ˣ����ն˲²�������������ʹ�������ŵ��������ˡ���ˣ����Ĳ���ȡ��ÿһ�δ�����������е��ظ����֣�
//����֡ͷ֡β���ж��Ƿ��������ظ�������AB������B��A��У��ͣ���A�Ͻ�������㣬�����������������
if (WrongRec == 4)//�ط�4������Ϊ�������ط���Σ������Ȼ�д��������һ����������һ�����ݵ�ǰ�����ط�һ�𱻼�¼�����
{
	for (int m = 0; m < WrongRecLen; m++)
	{
		if ((unsigned char)WrongRecCnt[m] != HEAD && (unsigned char)WrongRecCnt[m] != TAIL && (unsigned char)WrongRecCnt[m] > 0x11)
		//�������֡ͷҲ����֡βҲ�������
		{
			for (int n = m + 1; n < WrongRecLen; n++)//���ж��Ƿ����ظ������¼��һ��
			{
				if (WrongRecCnt[m] == WrongRecCnt[n])
				{
					BufOfSame[LengthOfSame++] = WrongRecCnt[m];
					BufOfSame[LengthOfSame++] = WrongRecCnt[m];
				}
			}
		}
	}
	//�������ע�͵��Ĵ������ڲ���
	//��ע�͵��ˣ�ע�͵���������û�������
	for (int j = 0; j < LengthOfSame; j++)//�����������ȡ�����������Ϣ
	{
		char testBuf2[128];
		wsprintf(testBuf2, "%02xh", (unsigned char)BufOfSame[j]);
		Puts(hW, INFOWin1, testBuf2);						//��ʾ��������յ�����Ϣ
	}
	for (int m = 0; m < LengthOfSame; m++)
	{
		for (int n = m + 1; n < LengthOfSame; n++)
		{
			if ((unsigned char)BufOfSame[m] == ((unsigned char)BufOfSame[n] * 0x80 * 2) % 0x87)
			{
				for (int k = n + 1; k < LengthOfSame; k++)
				{
					if ((unsigned char)BufOfSame[n] == (unsigned char)BufOfSame[k])
					{
						DataB[0] = BufOfSame[n];
						DataB[1] = 0;
						MyFrameData.FrameCheckStatus = 1;
						goto FB;
					}
				}
			}
		}
	}
	//�ط��Ĵξ����û���
	memset(WrongRecCnt, 0, 256);
	WrongRec = 0;
	WrongRecLen = 0;
	memset(BufOfSame, 0, 1024);
	LengthOfSame = 0;
}
//�������ע�͵��Ĵ����ǳ���˼·��ܣ�
/*
		int judge = 0;
		for (int i = 0; i < FrameLength; i++)
		{
			switch ((unsigned char)MyFrameData.FrameDataBuffer[i])//���һ�ν���һ���ֽڣ�������switch���Ժϲ�
//			switch ((unsigned char)ReceData[i])
			{
			case HEAD:
				if (State == 1)//������յ���֡ͷ����״̬��Ϊ0����û�н��յ�֡β�������������ϵ�֡ͷ��
				{
					judge++;
					break;
				}
				State = 1;
				break;
			}
		}
*/
		bool HeadRec = 0;
		for (int i = 0; i < nLength; i++)
		{
			if((unsigned char)MyFrameData.FrameDataBuffer[i] == HEAD)
				HeadRec = true;
			if ((unsigned char)MyFrameData.FrameDataBuffer[i] == HEAD && State == 0)//������յ�֡ͷ������State=1��״̬���˳�ѭ��
			{
				State = 1;
				Puts(hW, INFOWin1, "*******************");//�ָ�����˻�����
				break;
			}
			else if ((unsigned char)MyFrameData.FrameDataBuffer[i] == HEAD && State == 2)//������յ�֡ͷ����State��2��˵��û���յ�֡β���ط���
			{
				Puts(hW, INFOWin1, "Loses of FRAME_TAIL!");//��ʾ֡β��ʧ
				MyFrameData.FrameCheckStatus = 0;
				goto FB;
			}
		}
		
		/*if (judge)
		{
			Puts(hW, INFOWin1, "Loses of FRAME_TAIL!");
			Tail = FrameLength - 1;
			judge = 0;
		}*/

    	switch ((unsigned char)MyFrameData.FrameDataBuffer[FrameLength-1])//�����������һ���ֽ���TAIL��˵�����յ���֡β
		{
		case TAIL:
			if (HeadRec == false)//���û֡ͷ����֡β��
			{
				Puts(hW, INFOWin1, "Invalid Data.");//��ʾ����Ϣ��Ч
				State = 2;
				MyFrameData.FrameCheckStatus = 0;//�ط�
				goto FB;
			}
			if (FrameLength < 5)//���ճ���С��5��˵����Ϣû�н���ȫ���ط�
			{
				Puts(hW, INFOWin1, "Frame incomplete.");//��ʾ��Ϣ��ȫ
				State = 2;
				//�������ע�͵��Ĵ��볢�Ե�˼·�ǣ��������û�н���ȫ�����ٽ���һ�����ݣ�û�н��յ����ط�
				//ʵ������ʱ�������������ȱʧ�����ն�ֱ������
				/*char tempBuf[100];
				int tempL;
				tempL = PhysicalLayerReceive(tempBuf, 100);
				strcat(MyFrameData.FrameDataBuffer, tempBuf);
				FrameLength += tempL;
				if (tempL==0)
				{
					MyFrameData.FrameCheckStatus = 0;
					goto FB;
					break;
				}*/
				MyFrameData.FrameCheckStatus = 0;
				goto FB;
				break;
			}
			for (int j = 0; j < FrameLength; j++)//�����������ȡ�����������Ϣ
			//������������Ϊ���յ�֡β�����ܹ���ȷ������ٰ��������յ��������
			{
				char testBuf[64];
				wsprintf(testBuf, "%02xh", (unsigned char)MyFrameData.FrameDataBuffer[j]);
				Puts(hW, INFOWin1, testBuf);						//��ʾ��������յ�����Ϣ
			}
			//if (State == 0)//������յ���֡β����״̬��Ϊ1����û�н��յ�֡ͷ��
			//{
			//	Puts(hW, INFOWin1, "Loses of FRAME_HEAD!");
			//	Tail = FrameLength - 1;//��ʱ�������������ݣ��ܳ��ȼ�Ϊ֡���ܳ���
			//}
			Puts(hW, INFOWin1, "*******************");
			State = 2;
			break;
		}

		Tail = FrameLength - 1;//����һ��Tail����ֵ�������ŵ���FrameLength=5��Tail���ֲ���Ϊ4

		char buf[22];
		if (State == 2)
		{
			DataB[0] = MyFrameData.FrameDataBuffer[Tail - 2];
			DataB[1] = 0;
			int Temp = ((unsigned char)MyFrameData.FrameDataBuffer[Tail - 2] * 0x80 * 2) % 0x87;//�������ɵ�У�飬�����ü�У��������

			//����������ʼ�����жϽ����Ƿ�������˼·���������޸����ж�֡β�Ĵ��룬������ι����ظ���
			//��ɾ����Ҳûʲô���⣬ɾ����һ������ô�죬��ɾ�˰�>_<
			switch ((unsigned char)MyFrameData.FrameDataBuffer[Tail])//Ҳ���Բ���switch��ֱ���ж�FrameLength�Ƿ�Ϊ5
			{
			case TAIL:
				MyFrameData.FrameCheckStatus = 1;
				//wsprintf(buf, "Message Length completed");
				//Puts(hW, INFOWin1, buf);

				//����У��
				/*
				int Temp = 0x0;
				Temp += (unsigned char)TestFrameData.FrameDataBuffer[0];
				Temp += (unsigned char)TestFrameData.FrameDataBuffer[1];
				Temp += (unsigned char)TestFrameData.FrameDataBuffer[2];
				*/
				/*
				char TempFrameData[6];
				strcpy_s(TempFrameData, 6, TestFrameData.FrameDataBuffer);
				unsigned char CRC_Code = GenerateCRC((const uint8_t*)TestFrameData.FrameDataBuffer + 1, 2);//����У��
				TempFrameData[3] = CRC_Code;
				*/
				if ((unsigned char)Temp == (unsigned char)MyFrameData.FrameDataBuffer[Tail - 1])//�Ƚ�У��״̬
					MyFrameData.FrameCheckStatus = 1;
				else
					MyFrameData.FrameCheckStatus = 0;
				break;
			default:
				MyFrameData.FrameCheckStatus = 0;
				wsprintf(buf, "Message missing");
				//				wsprintf(buf, "%d", FrameLength);//���ڵ���
				Puts(hW, INFOWin1, buf);
				break;
			};

			//��������������Ĵ�����ACK��NAK��������ͳһ���С�FB��feedback����д
			//�д�����0x55��������0x88
			//���ø��������Ĳ���������Ӧ�÷Ž�FrameDataInit�����������Ҫ�ĵ�̫���ˣ����Խ���һ�£�bushi������Ҳû������
		FB:			if (MyFrameData.FrameCheckStatus)
		{
			char DisplayBufffer[250];//������߾���ȷ���Ͻ��������
			DataB[0] = (DataB[0] & 0x0F) + 0x30;							//ȥ����4λ����,��4λתΪASCII��
			wsprintf(DisplayBufffer, "%c", DataB[0]);
			Puts(hW, INFOWin2, DisplayBufffer);

			WrongRec = 0;
			memset(WrongRecCnt, 0, 256);
			WrongRecLen = 0;
			memset(BufOfSame, 0, 1024);
			LengthOfSame = 0;

			SendData[0] = 0x88;//������ȷ����Ϣ
			PhysicalLayerSend(&(SendData[0]), 1);					//����㣺����һ���ֽ�,��ʾ������ȷ
			State = 0;
			FrameLength = 0;
			memset(MyFrameData.FrameDataBuffer, 0, 256);
			Tail = 4;
		}
		else
		{
			SendData[0] = 0x55;//����д��Ͳ��Ͻ���������NCK
			PhysicalLayerSend(&(SendData[0]), 1);

			strcpy_s(WrongRecCnt + WrongRecLen, FrameLength + 1, MyFrameData.FrameDataBuffer);//��¼����
			WrongRecLen += FrameLength;
			WrongRecCnt[WrongRecLen] = '0';
			WrongRec++;
			LengthOfSame = 0;
			//����������������Ե�

			//for (int j = 0; j < WrongRecLen; j++)//�����������ȡ�����������Ϣ
			//{
			//	char testBuf[128];
			//	wsprintf(testBuf, "%02xh", (unsigned char)WrongRecCnt[j]);
			//	Puts(hW, INFOWin1, testBuf);						//��ʾ��������յ�����Ϣ
			//}

			State = 0;
			FrameLength = 0;
			memset(MyFrameData.FrameDataBuffer, 0, 256);
			Tail = 4;
		}
		}
		FrameDataInit();
		return 0;
}

//֡���ݵĳ�ʼ��
int FrameDataInit()
{
	MyFrameData.FrameBufferLength = 0;
	MyFrameData.FrameCheckStatus = 1;
	return 0;
}

uint8_t GenerateCRC(const uint8_t* Data, size_t FrameLength) //CRC������������size_t������int����ΪLength��ȷ��
{
	uint8_t CRC_Code = 0;
	for (size_t i = 0, CRC_Code = 0; i < FrameLength; i++)
	{
		CRC_Code ^= Data[i];                 //���ֵ
		for (int j = 0; j < 8; j++)
		{
			if (CRC_Code & 0X80)				  //80��1000 0000
				CRC_Code = (CRC_Code << 1) ^ 0X07;//07��0000 0111
			else
				CRC_Code <<= 1;
		}
	}
	return CRC_Code;
}