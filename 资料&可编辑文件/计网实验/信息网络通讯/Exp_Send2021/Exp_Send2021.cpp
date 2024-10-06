// Exp_Send.cpp : Defines the entry point for the application.
//信息通讯网络基础课程，理想信道的数据链路层协议，发送端程序, 2020.3

#include "stdafx.h"
//VC 6.0   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


//--------------------------------------------------------------
// Global Variables:
//按钮
#define BTN_Sender 501
#define BTN_Reset  502
//单行编辑框
#define EDIT_Sender 1601
//多行文本框
#define INFOWin1 801
#define INFOWin2 802
//静态文本
#define STATIC_W1 701
#define STATIC_W2 702
//--------------------------------------------------------------

SOCKET Cs1, Cs2;
struct sockaddr_in Cs1A, Cs2A;
WSADATA wsData;
char DataAA[200];
char DataB[200];
int d, i;

#define Cs1Port 6100		//本地端口(对应于模拟通道程序中的A站端口)
#define Cs2Port 7100		//远程端口(对应于模拟通道程序中的本地端口)
#define Cs1IP   "127.0.0.1"	//本地IP网址(127.0.0.1为本地环路)
#define Cs2IP   "127.0.0.1"	//远程IP网址(127.0.0.1为本地环路)

#define ID_TIMER  201
int time_Num = 0;
HWND hWnd;

char DisplayStringBuffer[5000];//显示缓冲区

HINSTANCE hInst;						// current instance
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);//回调函数
//--------------------------------------------------------------
//主函数
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
	TempString = "发送端[端口:";
	TempString += TempChar;
	TempString += "]－理想信道";

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
	SetTimer(hWnd, ID_TIMER, 500, NULL);//创建定时器，定时时间500毫秒

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
//静态文本
HWND CreateStatic(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW, "STATIC", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}

//--------------------------------------------------------------
//按钮
HWND CreateButton(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//单行编辑框
HWND CreateEdit(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD | ES_LEFT /*| ES_MULTILINE | WS_HSCROLL */,
		x0, y0, w, h, hW,
		(HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//多行文本框
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
//添加控件文本
void Puts(HWND hW, int ID_EDIT, char* str)
{
	GetDlgItemText(hW, ID_EDIT, DisplayStringBuffer, sizeof(DisplayStringBuffer));
	if (strlen(DisplayStringBuffer) > 4900)
	{
		//MessageBox(0,"显示缓冲区溢出！","显示缓冲区",0);
		strcpy(DisplayStringBuffer, "  \r\n");
	}
	strcat(DisplayStringBuffer, "\r\n");
	strcat(DisplayStringBuffer, str);
	SetDlgItemText(hW, ID_EDIT, (LPSTR)DisplayStringBuffer);
	SendMessage(GetDlgItem(hW, ID_EDIT), WM_VSCROLL, SB_THUMBPOSITION + 1000 * 0x10000, 0);
}
//---------------------------------------------------------------------------
//以上代码不需改动!
//********************************************************************************
//--------------------------------------------------------------------------------
//你可以在这里定义变量
int SendBufLeng;										//报文长度
int Sendi;												//数据帧发送计数
//void PhysicalLayerSend(BYTE c);						//物理层：发送一个字节
//BYTE PhysicalLayerReceive();							//物理层：接收一个字节
void PhysicalLayerSend(char* FrameData, int Length);	//物理层：发送一帧报文
int PhysicalLayerReceive(char* FrameData);				//物理层：接收一帧报文，返回数据长度
int s;                                             //定义标签
int send(char* FrameData, HWND hW, int i);         //设置数据发送函数

//--------------------------------------------------------------
//消息处理
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP)
{
	switch (msg)
	{
	case WM_DESTROY://窗口关闭时的消息处理
		WSAAsyncSelect(Cs1, hW, 0, 0);
		closesocket(Cs1);
		WSACleanup();
		KillTimer(hWnd, ID_TIMER);
		PostQuitMessage(0);
		break;
	case WM_CREATE://窗口创建时的消息处理
		WSAStartup(0x0101, &wsData);//网络初始化
		Cs1 = socket(AF_INET, SOCK_DGRAM, 0);
		Cs1A.sin_family = AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
		//		Cs1A.sin_addr.s_addr =INADDR_ANY;//在本机设置的网址(可能多个)中，都有效。
		Cs1A.sin_addr.s_addr = inet_addr(Cs1IP);
		d = bind(Cs1, (struct sockaddr*)&Cs1A, sizeof(Cs1A));
		if (d == -1)//bind函数调用失败
		{
			MessageBox(0, "端口发生冲突", "信道模拟", 0);
			PostQuitMessage(0);
		};
		Cs2A.sin_family = AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr = inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1, hW, WM_USER + 211, FD_READ);
		Beep(2000, 100);//响铃提示处理

		CreateEdit("1234567890", 2, 2, 130, 25, EDIT_Sender, hW, hInst);
		CreateButton("发送", 140, 2, 50, 24, BTN_Sender, hW, hInst);
		CreateButton("复位", 200, 2, 50, 24, BTN_Reset, hW, hInst);
		CreateStatic("物理层收到的信息:", 0, 35, 150, 24, STATIC_W1, hW, hInst);
		CreateStatic("发送的信息:", 160, 35, 150, 24, STATIC_W2, hW, hInst);
		CreateMemo(" ", 0, 55, 150, 220, INFOWin1, hW, hInst);
		CreateMemo(" ", 160, 55, 150, 220, INFOWin2, hW, hInst);

		//SetTimer(hWnd,ID_TIMER,1000,NULL);

		break;
		//============================================================================
		//接收事件触发：
		//你可以在这里添加和编写代码：
	case WM_USER + 211:
		switch (LOWORD(lP))
		{
		case FD_READ://网络数据接收消息处理
			break;
		}
		break;
	case WM_TIMER://定时器消息处理
		switch (wP)
		{
		case ID_TIMER:
			time_Num++;
			//char buf[22];
			//wsprintf(buf,"TIMER:%d",time_Num);
			//Puts(hW,INFOWin1,buf);								//显示，物理层收到的信息
			break;
		};
		break;
	case WM_COMMAND://按钮命令消息处理
		switch (wP)
		{
		case BTN_Sender:											// "发送" 按钮事件触发	
			GetDlgItemText(hW, EDIT_Sender, DataAA, sizeof(DataAA));	//从单行编辑框得到报文
			SendBufLeng = strlen(DataAA);								//求出报文长度
			char P[20];
			int sign[5];
			int i;
			for (Sendi = 0; Sendi < SendBufLeng; Sendi++)		     //发送报文
			{
				s = 1;
				Sleep(200);
				P[0] = 0x7e;                                //数据打包
				P[1] = Sendi;
				P[2] = DataAA[Sendi];
				P[3] = (DataAA[Sendi] * 0x80 * 2) % 0x87;
				P[4] = 0x7e;

				while (s) {
					for (i = 0; i < 5; i++) {
						sign[i] = send(&(P[i]), hW, i);			//物理层发送一个字节，循环发送直到帧完毕,此处调用了发送函数
					}

					if (sign[3] == 1)                                 //如果判断标签错误，重新发送字节
						s = 1;
					else s = 0;                                   //如果判断标签正确，结束发送字节
				}
			};
			break;
		case BTN_Reset:												//清除信息框内容
			SetDlgItemText(hW, INFOWin1, (LPSTR)" ");
			SetDlgItemText(hW, INFOWin2, (LPSTR)" ");
			break;
		}
	}
	return DefWindowProc(hW, msg, wP, lP);
}

//---------------------------------------------------------------------------------------------
void PhysicalLayerSend(char* FrameData, int Length)					//物理层：发送一帧报文
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, CS2A_Length);
}

//---------------------------------------------------------------------------------------------
int PhysicalLayerReceive(char* FrameData)							//物理层：接收一帧报文，返回数据长度
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
			Puts(hW, INFOWin2, buf);								//显示发送的信息
		}
		for (T = 100; T <= 1000; T = T + 100)                             //最长延时等待时间设置1000ms
		{
			Sleep(100);                                        //间隔100ms检测是否有接收端传回的确认信息
			PhysicalLayerReceive(S);
			if ((unsigned char)S[0] == 0x88) {              //0x88表示正确
				Ns = 0;                                           //判断标签为0
				char DisplayBufffer[16];
				wsprintf(DisplayBufffer, "%02XH,  %c", (unsigned char)S[0], S[0]);
				Puts(hW, INFOWin1, DisplayBufffer);		    	//显示物理层收到的信息
			}
			if ((unsigned char)S[0] == 0x55) {             //0x55表示差错
				Ns = 1;                                          //判断标签为1                                       
				char DisplayBufffer[16];
				wsprintf(DisplayBufffer, "%02XH,  %c", (unsigned char)S[0], S[0]);
				Puts(hW, INFOWin1, DisplayBufffer);			//显示物理层收到的信息，
			}

			if (S[0] != 0) {                                    //若收到了数据，则结束循环，若没有收到数据，则重新发送原数据重走一遍流程
				i = 0;
				break;
			}
		}
	}
	return Ns;                                                 //返回到判断标签
}
