// Exp_Send.cpp : Defines the entry point for the application.
//��ϢͨѶ��������γ̣������ŵ���������·��Э��ʵ�֣����Ͷ˳���, 2024.3

#include "stdafx.h"
//VC 2010   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------
// Global Variables:
//��ť
#define BTN_Sender 501
#define BTN_Reset  502
//���б༭��
#define EDIT_Sender 1601
//�����ı���
#define INFOWin1 801
#define INFOWin2 802
//��̬�ı�
#define STATIC_W1 701
#define STATIC_W2 702
//----------------------------------------------------------------------------------------

SOCKET Cs1,Cs2;
struct sockaddr_in Cs1A,Cs2A;
WSADATA wsData;
char DataAA[200];
char DataB[200];
int d,i;

#define Cs1Port 6100		//���ض˿�(��Ӧ��ģ��ͨ�������е�Aվ�˿�)
#define Cs2Port 7100		//Զ�̶˿�(��Ӧ��ģ��ͨ�������еı��ض˿�)
#define Cs1IP   "127.0.0.1"	//����IP��ַ(127.0.0.1Ϊ���ػ�·)
#define Cs2IP   "127.0.0.1"	//Զ��IP��ַ(127.0.0.1Ϊ���ػ�·)

#define ID_TIMER  201
int time_Num=0;
HWND hWnd;

char DisplayStringBuffer[5000];//��ʾ������

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
	TempString = "���Ͷ�[�˿�:";
	TempString += TempChar;
	TempString += "]�������ŵ�";
	
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
		50,10,320,300,
		NULL,NULL,hInstance,NULL);

   	if (!hWnd)   return FALSE;
	SetTimer(hWnd,ID_TIMER,500,NULL);//������ʱ������ʱʱ��500����

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
	return ::CreateWindowEx(WS_EX_PALETTEWINDOW,"BUTTON",Titel,
		WS_VISIBLE | WS_CHILD ,
		x0,y0,w,h, hW,(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//�������б༭��
HWND CreateEdit(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Titel,
		WS_VISIBLE | WS_CHILD | ES_LEFT /*| ES_MULTILINE | WS_HSCROLL */,
		x0,y0,w,h, hW,
		(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//���������ı���
HWND CreateMemo(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Titel,
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
	}
	strcat(DisplayStringBuffer,"\r\n");
	strcat(DisplayStringBuffer,str);
	SetDlgItemText(hW,ID_EDIT,(LPSTR) DisplayStringBuffer);
	SendMessage(GetDlgItem(hW,ID_EDIT),WM_VSCROLL,SB_THUMBPOSITION+1000*0x10000,0);
}
//----------------------------------------------------------------------------------------
//���ϴ��벻��Ķ�!
//****************************************************************************************
//----------------------------------------------------------------------------------------
//����������ﶨ�����
int SendBufLeng;										//���ĳ���
int Sendi;												//����֡���ͼ���
//void PhysicalLayerSend(BYTE c);						//����㣺����һ���ֽ�
//BYTE PhysicalLayerReceive();							//����㣺����һ���ֽ�
void PhysicalLayerSend(char* FrameData, int Length);	//����㷢�����ݺ���������һ֡����
int PhysicalLayerReceive(char* FrameData);
int PhysicalLayerReceive(char* FrameData,int Length);				//�����������ݺ��������ձ������ݣ��������ݳ���

#define ACK 0X88
#define NCK 0X55
#define HEAD 0XFE  
#define TAIL 0XFD
									
int nSending;											//�ظ����͵Ĵ������ظ�����8�����жϽ��շ��޷�����

uint8_t GenerateCRC(const uint8_t* Data, size_t Length);//CRCУ�麯��
/*
* struct MyFrameData											//������֡���ݣ�����֡ͷ��0XFE��֡��ţ����ݣ�У��ͣ�֡β��0XFD
{
	char FrameData[16];
	int FrameLength = 5;									//֡���ȣ�������������

	MyFrameData()											//���캯��									
	{
		FrameData[0] = HEAD;
		for (int i = 1; i < 4; i++)
			FrameData[i] = -1;
		FrameData[4] = TAIL;
		FrameData[5] = '\0';
	}

	void setContent(char content)
	{
		FrameData[1] = (FrameData[1] + 1) % 8;//�������
		FrameData[2] = content;
		unsigned char CRC_Code = GenerateCRC((const uint8_t*)FrameData + 1, 2);//����У��
		FrameData[3] = CRC_Code;
	}
};
*/

/*
void CALLBACK TimerProc(HWND aHwnd, UINT aMessage, UINT_PTR aTimerId, DWORD aTime)
{
	PhysicalLayerSend(FrameData.FrameData, FrameData.FrameLength);
}
*/


void FrameDataInit(char* FrameData,unsigned char Data,int Sendi)//��ֵ����������֡����
{
	FrameData[0] = HEAD;
	FrameData[1] = unsigned char(Sendi + 1);
	FrameData[2] = Data;
//	unsigned char CRC_Code = GenerateCRC((const uint8_t*)FrameData + 1, 2);//����У��
//	FrameData[3] = CRC_Code;
//	FrameData[3] = (HEAD + Sendi + Data)&0XFF;
	FrameData[3] = (Data * 0x80 * 2) % 0x87;//����ʱ���ü�У��
	FrameData[4] = TAIL;
}

char FrameData[16] = { 0xfe,-1,-1,-1,0xfd,0 };//����ʱֱ�Ӹ�һ��ֵ��ȷ����ȫ��
int FrameLength = 5;//���͵�ÿһ֡����Ϊ5

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
		KillTimer(hWnd,ID_TIMER);
		PostQuitMessage(0);
		break;
	case WM_CREATE://���ڴ���ʱ����Ϣ����
		WSAStartup(0x0101,&wsData);//�����ʼ��
		Cs1=socket(AF_INET, SOCK_DGRAM,0);
		Cs1A.sin_family=AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
//		Cs1A.sin_addr.s_addr =INADDR_ANY;//�ڱ������õ���ַ(���ܶ��)�У�����Ч��
		Cs1A.sin_addr.s_addr =inet_addr(Cs1IP);
		d = bind(Cs1,(struct sockaddr *) &Cs1A,sizeof(Cs1A));
		if(d == -1)//bind��������ʧ��
		{
			MessageBox(0,"�˿ڷ�����ͻ","�ŵ�ģ��",0);
			PostQuitMessage(0);
		};
		Cs2A.sin_family=AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr =inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1,hW,WM_USER+211,FD_READ);
		Beep(2000,100);//������ʾ����

		CreateEdit("1234567890",2,2,130,25,EDIT_Sender,hW,hInst);
		CreateButton("����",140,2,50,24,BTN_Sender,hW,hInst);
		CreateButton("��λ",200,2,50,24,BTN_Reset,hW,hInst);
		CreateStatic("������յ�����Ϣ:",0,35,150,24,STATIC_W1,hW,hInst);
		CreateStatic("���͵���Ϣ:",160,35,150,24,STATIC_W2,hW,hInst);
		CreateMemo(" ",0,55,150,220,INFOWin1,hW,hInst);
		CreateMemo(" ",160,55,150,220,INFOWin2,hW,hInst);

		break;
//============================================================================
//�����¼�������
//�������������Ӻͱ�д���룺
	case WM_USER+211:
		switch(LOWORD(lP))
		{
		case FD_READ://�������ݽ�����Ϣ����
			//*******************************************************************************
			//��������֡���մ������ڴ˸���Э���޸Ļ���Ӵ���
			//����ʰ�д���ֻ�����ڲ��ԣ�����Ҫ����Э������޸�
			//*******************************************************************************
			//ԭ���룺
			//char ReceData[100];
			//int Length;
			//Length=PhysicalLayerReceive(ReceData);					//����㣺����һ���ֽ�
			//DataB[0] = ReceData[0];
			//DataB[1]=0;
			//char DisplayBufffer[250];
			//wsprintf(DisplayBufffer,"%02XH,  %c",(unsigned char)DataB[0],DataB[0]);
			//Puts(hW,INFOWin1,DisplayBufffer);						//��ʾ��������յ�����Ϣ
//          Sleep(100);
//			MessageBox(0,DataB,"(FD_READ)",0);
			//*******************************************************************************
			
			char ReceData[100];
			memset(ReceData, 0, 100);
			int Length;
			Length = PhysicalLayerReceive(ReceData);				//����㣺����һ���ֽ�
			DataB[0] = ReceData[0];
			DataB[1]=0;												//�ض�
			
			//*******************************************************************************
			break;
		}
		break;
	case WM_TIMER://��ʱ����Ϣ����
		switch(wP)
		{
		case ID_TIMER:
			time_Num++;
			//char buf[22];
			//wsprintf(buf,"TIMER:%d",time_Num);
			//Puts(hW,INFOWin1,buf);								//��ʾ��������յ�����Ϣ
			break;
		};
		break;
	case WM_COMMAND://��ť������Ϣ����
		switch(wP)
		{
		case BTN_Sender:											// "����" ��ť�¼�����	
			GetDlgItemText(hW,EDIT_Sender,DataAA,sizeof(DataAA));	//�ӵ��б༭��õ�����
			SendBufLeng = strlen(DataAA);								//������ĳ���
			//*******************************************************************************
			//��������֡��װ������������Ӵ���
			//�������д���ֻ�����ڲ��ԣ�����Ҫ����Э������޸�
			//*******************************************************************************
			//ԭ��������
			//PhysicalLayerSend(DataAA,SendBufLeng);					//����㣺����һ���ֽ�
			//for(Sendi=0;Sendi<SendBufLeng;Sendi++)					//���ͱ���
			//{
			//	//PhysicalLayerSend(&(DataAA[Sendi]),1);			//����㣺����һ���ֽ�
			//	char buf[22];
			//	wsprintf(buf,"%02XH,  %c",(unsigned char)DataAA[Sendi],DataAA[Sendi]);
			//	Puts(hW,INFOWin2,buf);								//��ʾ������㷢�͵���Ϣ
			//};
			//*******************************************************************************

			//�˶��ǳ�����timer��ɹ��ܣ�δ��
			/*
			FrameData.setContent(DataAA[Sendi++]);
			PhysicalLayerSend(FrameData.FrameData, FrameData.FrameLength);  // ����㣺����
			SetTimer(hW, 1, 5000, TimerProc);
			for (int i = 0; i < SendBufLeng; i++)
			{
				char buf[22];
				wsprintf(buf, "%02XH,  %c", (unsigned char)DataAA[i], DataAA[i]);
				Puts(hW, INFOWin2, buf);  // ��ʾ������㷢�͵���Ϣ
			};
			*/
			for (Sendi = 0 ; Sendi < SendBufLeng; Sendi++)					//���ͱ���
			{
				nSending = 0;//nSending���ط�������Լ��������8�Σ�ÿ�·���һ���ֽ�ʱ����
				FrameDataInit(FrameData, DataAA[Sendi], Sendi);
				FrameLength = strlen(FrameData);

			loop:PhysicalLayerSend(FrameData, 5);			//����㣺����һ֡

				char buf[32];//��ͬ��Ϣ���Ͳ��ò�ͬ����������ֹ��Ϊ���ݳ��Ȳ�ͬ��������Ϣ���ָ��ǵ������
							 //���������һ����������ÿ��д��ǰ�������Ż���
				char bufL[64];
				char bufO[128];
				char bufE[32];
				char bufR[64];

				wsprintf(buf, "%02XH,  %c", (unsigned char)DataAA[Sendi], DataAA[Sendi]);
				Puts(hW, INFOWin2, buf);								//��ʾ������㷢�͵���Ϣ

				double time = 0;
				int errChecking = 0;//������ֹ�������ѭ�� ��û�н��յ�ACK��NAKʱ ÿѭ��һ�ζ��ᱨһ�δ��ý���ÿ�һ��
				while (time < 4)
				{
					Sleep(1000);//��ʱ1s
					time += 1;

					DataB[0] = '0';
					PhysicalLayerReceive(DataB, 1);

					if ((unsigned char)DataB[0] == ACK)
					{
						wsprintf(bufR, "%02XH,  %c", (unsigned char)DataB[0], DataB[0]);
						Puts(hW, INFOWin1, bufR);
						break;
					}
					else if ((unsigned char)DataB[0] == NCK)
					{
						wsprintf(bufR, "%02XH,  %c", (unsigned char)DataB[0], DataB[0]);
						Puts(hW, INFOWin1, bufR);
						if (nSending < 8)
						{
							wsprintf(bufE, "Message error. Retrying...");
							Puts(hW, INFOWin2, bufE);
							nSending++;
							goto loop;
						}
						else
						{
							wsprintf(bufO, "The Receiver might be offline. Try again later!");
							Puts(hW, INFOWin2, bufO);
							break;
						}
					}
					else if(errChecking == 0)
					{
						wsprintf(bufE, "Waiting for feedback...");
						Puts(hW, INFOWin2, bufE);
						errChecking++;
					}
				}
				if (time >= 4)
				{
					errChecking = 0;
					wsprintf(bufL, "Losing feedback. Retrying...");
					Puts(hW, INFOWin2, bufL);
					nSending++;
					if (nSending < 8)
					{
						goto loop;
					}
					else
					{
						Puts(hW, INFOWin2, "****************\n");
						wsprintf(bufO, "The Receiver might be offline. Try agaian later!\n");
						Puts(hW, INFOWin2, bufO);
						Puts(hW, INFOWin2, "****************");
						continue;
					}
				}
			end:errChecking = 0;
			};
			
			//*******************************************************************************
			break;
		case BTN_Reset:												//�����Ϣ������
			SetDlgItemText(hW,INFOWin1,(LPSTR) " ");
			SetDlgItemText(hW,INFOWin2,(LPSTR) " ");
			break;
		}
	}
finish:
	return DefWindowProc(hW, msg, wP, lP);
}

//---------------------------------------------------------------------------------------------
//����㱨��֡���ͺ���������һ֡��������
//���������char* FrameData�����ͱ���֡����ָ��
//          int Length������֡���ݳ���
//�����������
void PhysicalLayerSend(char* FrameData, int Length)					
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1,FrameData,Length,0,(struct sockaddr *) &Cs2A,CS2A_Length);
}

//---------------------------------------------------------------------------------------------
//�����������ݺ���������һ֡���ģ��������ݳ��ȡ�
//һ֡���Ŀ����ɶ���ֽڹ��ɣ��ú���ִ��һ�ο���ֻ�ǽ����˱���֡��һ���ֽڻ�һ���֣�
//ͨ����Ҫ���ִ�иú������Ա������������֡��
//���������char* FrameData�����ձ�������ָ��
//���������int ��������ֵ��Ϊ�������ݵĳ���
int PhysicalLayerReceive(char* FrameData)							
{
	int Length;
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	Length = recvfrom(Cs1,FrameData,sizeof(FrameData),0,(struct sockaddr *) &Cs2A,&CS2A_Length);
	return Length;
}

int PhysicalLayerReceive(char* FrameData, int Length)//Length�����ջ���������
//���Ǹ�����
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	return recvfrom(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, &CS2A_Length);
}
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
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