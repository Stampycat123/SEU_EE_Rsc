// Exp_Receiver.cpp : Defines the entry point for the application.
//��ϢͨѶ��������γ̣������ŵ���������·��Э�飬���ն˳��� 2020.3

#include "stdafx.h"
//VC 6.0   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void wlc(BYTE Fram);
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
//--------------------------------------------------------------
WSADATA wsData;
SOCKET Cs1, Cs2;
struct sockaddr_in Cs1A, Cs2A;
char DataB[200];
int d, i;
#define Cs2Port 7100		//Զ�̶˿�(��Ӧ��ģ��ͨ�������еı��ض˿�)
#define Cs1Port 8100		//���ض˿�(��Ӧ��ģ��ͨ�������е�Bվ�˿�)
#define Cs1IP   "127.0.0.1"	//����IP��ַ(127.0.0.1Ϊ���ػ�·)
#define Cs2IP   "127.0.0.1"	//Զ��IP��ַ(127.0.0.1Ϊ���ػ�·)


char DisplayStringBuffer[5000];//��ʾ������
//--------------------------------------------------------------
// Global Variables:
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
	TempString = "���ն�[�˿�:";
	TempString += TempChar;
	TempString += "]�������ŵ�\0";

	HWND hWnd;
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
		400, 10, 320, 300,
		NULL, NULL, hInstance, NULL);

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
	return CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//���б༭��
HWND CreateEdit(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | WS_HSCROLL,
		x0, y0, w, h, hW,
		(HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//�����ı���
HWND CreateMemo(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
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

//���ϲ���Ķ�!
//--------------------------------------------------------------
//����������ﶨ�����
//void PhysicalLayerSend(BYTE c);	//����㣺����һ���ֽ�
//BYTE PhysicalLayerReceive();	//����㣺����һ���ֽ�
void PhysicalLayerSend(char* FrameData, int Length);	//����㣺����һ֡����
int PhysicalLayerReceive(char* FrameData);	//����㣺����һ֡���ģ��������ݳ���
int Count = 0;            //���ü���
char S[250];
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
		WSAAsyncSelect(Cs1, hW, WM_USER + 212, FD_READ);
		Beep(2000, 100);//������ʾ����

		CreateEdit("���ն�", 2, 2, 130, 20, EDIT_Receiver, hW, hInst);
		CreateButton("�˳�", 140, 2, 50, 24, BTN_Quit, hW, hInst);
		CreateButton("��λ", 200, 2, 50, 24, BTN_Reset, hW, hInst);
		CreateStatic("������յ�����Ϣ:", 0, 35, 150, 24, STATIC_W1, hW, hInst);
		CreateStatic("�Ͻ���������Ϣ:", 160, 35, 150, 24, STATIC_W2, hW, hInst);
		CreateMemo(" ", 0, 55, 150, 220, INFOWin1, hW, hInst);
		CreateMemo(" ", 160, 55, 150, 220, INFOWin2, hW, hInst);

		break;
		//============================================================================
		//������Ϣ�¼���
		//�������������Ӻͱ�д���룺
	case WM_USER + 212:
		switch (LOWORD(lP))
		{
		case FD_READ://�������ݽ�����Ϣ����
			int Length;
			char R[250];
			Length = PhysicalLayerReceive(R);					//����㣺����һ���ֽ�
			DataB[1] = 0x0f;
			Count++;
			int flag;

			if (Count == 3) {
				S[0] = R[0];
				S[1] = 0x55;
				S[2] = 0x88;
			}
			if (Count == 4) {
				flag = (S[0] * 0x80 * 2 - R[0]) % 0x87;                         //����У��λ
				if (flag == 0) {                                               //��ȷ������㷢��һ��0x88
					PhysicalLayerSend(&S[2], 1);
					char DisplayBufffer[250];
					wsprintf(DisplayBufffer, "%02XH", (unsigned char)S[0]);
					Puts(hW, INFOWin1, DisplayBufffer);				           //��ʾ������յ�����Ϣ			        
					S[0] = (S[0] & 0x0F) + 0x30;						       //ȥ����4λ����,��4λתΪASCII��
					Sleep(100);
					wsprintf(DisplayBufffer, "%02XH, %c", (unsigned char)S[0], S[0]);
					Puts(hW, INFOWin2, DisplayBufffer);				          //��ʾ�Ͻ������õ�����Ϣ
				}
				else if (flag != 0) {                                         //��������㷢��һ��0x55
					PhysicalLayerSend(&S[1], 1);
					char DisplayBufffer[250];
					DisplayBufffer[0] = 0x00;
					Puts(hW, INFOWin1, DisplayBufffer);				          //��ʾ������յ�����Ϣ			        
					S[0] = 0xff;
					Sleep(100);
					wsprintf(DisplayBufffer, "%02XH", (unsigned char)S[0]);
					Puts(hW, INFOWin2, DisplayBufffer);				         //��ʾ�Ͻ������õ�����Ϣ
				}
			}
			if (Count == 5) Count = 0;                                       //����������
			if (Count != 4) PhysicalLayerSend(&DataB[1], 1);	             //��У��λʱ����0x0f����ʾ�ѽ��յ�������

		//*****************************************************************************
			break;
		}
		break;
		//============================================================================
	case WM_COMMAND://��ť������Ϣ����
		switch (wP)
		{
		case BTN_Quit:												         //�˳�����
			PostQuitMessage(0);
			break;
		case BTN_Reset:												        //�����Ϣ������
			SetDlgItemText(hW, INFOWin1, (LPSTR)" ");
			SetDlgItemText(hW, INFOWin2, (LPSTR)" ");
			break;
		}
	}
	return DefWindowProc(hW, msg, wP, lP);
}

//--------------------------------------------------------------
void PhysicalLayerSend(char* FrameData, int Length)					        //����㣺����һ֡����
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, CS2A_Length);
}

//--------------------------------------------------------------
int PhysicalLayerReceive(char* FrameData)							        //����㣺����һ֡���ģ��������ݳ���
{
	int Length;
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	Length = recvfrom(Cs1, FrameData, sizeof(FrameData), 0, (struct sockaddr*)&Cs2A, &CS2A_Length);
	return Length;
}

