// Exp_Send.cpp : Defines the entry point for the application.
//��ϢͨѶ��������γ̣������ŵ���������·��Э�飬���Ͷ˳���, 2020.3

#include "stdafx.h"
//VC 6.0   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


//--------------------------------------------------------------
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
//--------------------------------------------------------------

SOCKET Cs1, Cs2;
struct sockaddr_in Cs1A, Cs2A;
WSADATA wsData;
char DataAA[200];
char DataB[200];
int d, i;

#define Cs1Port 6100		//���ض˿�(��Ӧ��ģ��ͨ�������е�Aվ�˿�)
#define Cs2Port 7100		//Զ�̶˿�(��Ӧ��ģ��ͨ�������еı��ض˿�)
#define Cs1IP   "127.0.0.1"	//����IP��ַ(127.0.0.1Ϊ���ػ�·)
#define Cs2IP   "127.0.0.1"	//Զ��IP��ַ(127.0.0.1Ϊ���ػ�·)

#define ID_TIMER  201
int time_Num = 0;
HWND hWnd;

char DisplayStringBuffer[5000];//��ʾ������

HINSTANCE hInst;						// current instance
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);//�ص�����
//--------------------------------------------------------------
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
	itoa(Cs1Port, TempChar, 10);
	TempString = "���Ͷ�[�˿�:";
	TempString += TempChar;
	TempString += "]�������ŵ�";

	hInst = hInstance; // Store instance handle in our global variable
	WNDCLASS wc;

	memset(&wc, 0, sizeof(WNDCLASS));

	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "W1";
	RegisterClass(&wc);

	TempString.copy(TempChar1, TempString.length());
	TempChar1[TempString.length()] = 0x00;
	hWnd = CreateWindow("W1", TempChar1,
		WS_DLGFRAME | WS_SYSMENU,
		50, 10, 320, 300,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)   return FALSE;
	SetTimer(hWnd, ID_TIMER, 500, NULL);//������ʱ������ʱʱ��500����

	ShowWindow(hWnd, nCmdShow);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

//--------------------------------------------------------------
//��̬�ı�
HWND CreateStatic(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW, "STATIC", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}

//--------------------------------------------------------------
//��ť
HWND CreateButton(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//���б༭��
HWND CreateEdit(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD | ES_LEFT /*| ES_MULTILINE | WS_HSCROLL */,
		x0, y0, w, h, hW,
		(HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//�����ı���
HWND CreateMemo(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | ES_READONLY |
		WS_HSCROLL | WS_VSCROLL,
		x0, y0, w, h,
		hW, (HMENU)ID, hInst, NULL);
}
//---------------------------------------------------------------------------
//��ӿؼ��ı�
void Puts(HWND hW, int ID_EDIT, char* str)
{
	GetDlgItemText(hW, ID_EDIT, DisplayStringBuffer, sizeof(DisplayStringBuffer));
	if (strlen(DisplayStringBuffer) > 4900)
	{
		//MessageBox(0,"��ʾ�����������","��ʾ������",0);
		strcpy(DisplayStringBuffer, "  \r\n");
	}
	strcat(DisplayStringBuffer, "\r\n");
	strcat(DisplayStringBuffer, str);
	SetDlgItemText(hW, ID_EDIT, (LPSTR)DisplayStringBuffer);
	SendMessage(GetDlgItem(hW, ID_EDIT), WM_VSCROLL, SB_THUMBPOSITION + 1000 * 0x10000, 0);
}
//---------------------------------------------------------------------------
//���ϴ��벻��Ķ�!
//********************************************************************************
//--------------------------------------------------------------------------------
//����������ﶨ�����
int SendBufLeng;										//���ĳ���
int Sendi;												//����֡���ͼ���
//void PhysicalLayerSend(BYTE c);						//����㣺����һ���ֽ�
//BYTE PhysicalLayerReceive();							//����㣺����һ���ֽ�
void PhysicalLayerSend(char* FrameData, int Length);	//����㣺����һ֡����
int PhysicalLayerReceive(char* FrameData);				//����㣺����һ֡���ģ��������ݳ���
int s;                                             //�����ǩ
int send(char* FrameData, HWND hW, int i);         //�������ݷ��ͺ���

//--------------------------------------------------------------
//��Ϣ����
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP)
{
	switch (msg)
	{
	case WM_DESTROY://���ڹر�ʱ����Ϣ����
		WSAAsyncSelect(Cs1, hW, 0, 0);
		closesocket(Cs1);
		WSACleanup();
		KillTimer(hWnd, ID_TIMER);
		PostQuitMessage(0);
		break;
	case WM_CREATE://���ڴ���ʱ����Ϣ����
		WSAStartup(0x0101, &wsData);//�����ʼ��
		Cs1 = socket(AF_INET, SOCK_DGRAM, 0);
		Cs1A.sin_family = AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
		//		Cs1A.sin_addr.s_addr =INADDR_ANY;//�ڱ������õ���ַ(���ܶ��)�У�����Ч��
		Cs1A.sin_addr.s_addr = inet_addr(Cs1IP);
		d = bind(Cs1, (struct sockaddr*)&Cs1A, sizeof(Cs1A));
		if (d == -1)//bind��������ʧ��
		{
			MessageBox(0, "�˿ڷ�����ͻ", "�ŵ�ģ��", 0);
			PostQuitMessage(0);
		};
		Cs2A.sin_family = AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr = inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1, hW, WM_USER + 211, FD_READ);
		Beep(2000, 100);//������ʾ����

		CreateEdit("1234567890", 2, 2, 130, 25, EDIT_Sender, hW, hInst);
		CreateButton("����", 140, 2, 50, 24, BTN_Sender, hW, hInst);
		CreateButton("��λ", 200, 2, 50, 24, BTN_Reset, hW, hInst);
		CreateStatic("������յ�����Ϣ:", 0, 35, 150, 24, STATIC_W1, hW, hInst);
		CreateStatic("���͵���Ϣ:", 160, 35, 150, 24, STATIC_W2, hW, hInst);
		CreateMemo(" ", 0, 55, 150, 220, INFOWin1, hW, hInst);
		CreateMemo(" ", 160, 55, 150, 220, INFOWin2, hW, hInst);

		//SetTimer(hWnd,ID_TIMER,1000,NULL);

		break;
		//============================================================================
		//�����¼�������
		//�������������Ӻͱ�д���룺
	case WM_USER + 211:
		switch (LOWORD(lP))
		{
		case FD_READ://�������ݽ�����Ϣ����
			break;
		}
		break;
	case WM_TIMER://��ʱ����Ϣ����
		switch (wP)
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
		switch (wP)
		{
		case BTN_Sender:											// "����" ��ť�¼�����	
			GetDlgItemText(hW, EDIT_Sender, DataAA, sizeof(DataAA));	//�ӵ��б༭��õ�����
			SendBufLeng = strlen(DataAA);								//������ĳ���
			char P[20];
			int sign[5];
			int i;
			for (Sendi = 0; Sendi < SendBufLeng; Sendi++)		     //���ͱ���
			{
				s = 1;
				Sleep(200);
				P[0] = 0x7e;                                //���ݴ��
				P[1] = Sendi;
				P[2] = DataAA[Sendi];
				P[3] = (DataAA[Sendi] * 0x80 * 2) % 0x87;
				P[4] = 0x7e;

				while (s) {
					for (i = 0; i < 5; i++) {
						sign[i] = send(&(P[i]), hW, i);			//����㷢��һ���ֽڣ�ѭ������ֱ��֡���,�˴������˷��ͺ���
					}

					if (sign[3] == 1)                                 //����жϱ�ǩ�������·����ֽ�
						s = 1;
					else s = 0;                                   //����жϱ�ǩ��ȷ�����������ֽ�
				}
			};
			break;
		case BTN_Reset:												//�����Ϣ������
			SetDlgItemText(hW, INFOWin1, (LPSTR)" ");
			SetDlgItemText(hW, INFOWin2, (LPSTR)" ");
			break;
		}
	}
	return DefWindowProc(hW, msg, wP, lP);
}

//---------------------------------------------------------------------------------------------
void PhysicalLayerSend(char* FrameData, int Length)					//����㣺����һ֡����
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, CS2A_Length);
}

//---------------------------------------------------------------------------------------------
int PhysicalLayerReceive(char* FrameData)							//����㣺����һ֡���ģ��������ݳ���
{
	int Length;
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	Length = recvfrom(Cs1, FrameData, sizeof(FrameData), 0, (struct sockaddr*)&Cs2A, &CS2A_Length);
	return Length;
}
//---------------------------------------------------------------------------------------------
int send(char* FrameData, HWND hW, int j)
{
	char S[16];
	S[0] = 0;
	int Ns = 0;
	int T;
	int i = 1;
	while (i) {
		PhysicalLayerSend(FrameData, i);
		if (j == 2) {
			char buf[16];
			wsprintf(buf, "%02XH,  %c", (unsigned char)FrameData[0], FrameData[0]);
			Puts(hW, INFOWin2, buf);								//��ʾ���͵���Ϣ
		}
		for (T = 100; T <= 1000; T = T + 100)                             //���ʱ�ȴ�ʱ������1000ms
		{
			Sleep(100);                                        //���100ms����Ƿ��н��ն˴��ص�ȷ����Ϣ
			PhysicalLayerReceive(S);
			if ((unsigned char)S[0] == 0x88) {              //0x88��ʾ��ȷ
				Ns = 0;                                           //�жϱ�ǩΪ0
				char DisplayBufffer[16];
				wsprintf(DisplayBufffer, "%02XH,  %c", (unsigned char)S[0], S[0]);
				Puts(hW, INFOWin1, DisplayBufffer);		    	//��ʾ������յ�����Ϣ
			}
			if ((unsigned char)S[0] == 0x55) {             //0x55��ʾ���
				Ns = 1;                                          //�жϱ�ǩΪ1                                       
				char DisplayBufffer[16];
				wsprintf(DisplayBufffer, "%02XH,  %c", (unsigned char)S[0], S[0]);
				Puts(hW, INFOWin1, DisplayBufffer);			//��ʾ������յ�����Ϣ��
			}

			if (S[0] != 0) {                                    //���յ������ݣ������ѭ������û���յ����ݣ������·���ԭ��������һ������
				i = 0;
				break;
			}
		}
	}
	return Ns;                                                 //���ص��жϱ�ǩ
}
