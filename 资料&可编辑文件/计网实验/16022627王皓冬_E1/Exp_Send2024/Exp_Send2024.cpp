// Exp_Send.cpp : Defines the entry point for the application.
//信息通讯网络基础课程，理想信道的数据链路层协议实现，发送端程序, 2024.3

#include "stdafx.h"
//VC 2010   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------

SOCKET Cs1,Cs2;
struct sockaddr_in Cs1A,Cs2A;
WSADATA wsData;
char DataAA[200];
char DataB[200];
int d,i;

#define Cs1Port 6100		//本地端口(对应于模拟通道程序中的A站端口)
#define Cs2Port 7100		//远程端口(对应于模拟通道程序中的本地端口)
#define Cs1IP   "127.0.0.1"	//本地IP网址(127.0.0.1为本地环路)
#define Cs2IP   "127.0.0.1"	//远程IP网址(127.0.0.1为本地环路)

#define ID_TIMER  201
int time_Num=0;
HWND hWnd;

char DisplayStringBuffer[5000];//显示缓冲区

HINSTANCE hInst;						// current instance
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);//回调函数
//----------------------------------------------------------------------------------------
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
	itoa(Cs1Port,TempChar,10);
	TempString = "发送端[端口:";
	TempString += TempChar;
	TempString += "]－理想信道";
	
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
	SetTimer(hWnd,ID_TIMER,500,NULL);//创建定时器，定时时间500毫秒

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
//创建静态文本框
HWND CreateStatic(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW,"STATIC",Titel,
		WS_VISIBLE | WS_CHILD ,
		x0,y0,w,h, hW,(HMENU)ID,hInst,NULL);
}

//----------------------------------------------------------------------------------------
//创建按钮
HWND CreateButton(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_PALETTEWINDOW,"BUTTON",Titel,
		WS_VISIBLE | WS_CHILD ,
		x0,y0,w,h, hW,(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//创建单行编辑框
HWND CreateEdit(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return ::CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Titel,
		WS_VISIBLE | WS_CHILD | ES_LEFT /*| ES_MULTILINE | WS_HSCROLL */,
		x0,y0,w,h, hW,
		(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//创建多行文本框
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
//添加控件文本
void Puts(HWND hW,int ID_EDIT,char *str)
{
	GetDlgItemText(hW,ID_EDIT,DisplayStringBuffer,sizeof(DisplayStringBuffer));
	if (strlen(DisplayStringBuffer) > 4900)
	{
		//MessageBox(0,"显示缓冲区溢出！","显示缓冲区",0);
		strcpy(DisplayStringBuffer,"  \r\n");
	}
	strcat(DisplayStringBuffer,"\r\n");
	strcat(DisplayStringBuffer,str);
	SetDlgItemText(hW,ID_EDIT,(LPSTR) DisplayStringBuffer);
	SendMessage(GetDlgItem(hW,ID_EDIT),WM_VSCROLL,SB_THUMBPOSITION+1000*0x10000,0);
}
//----------------------------------------------------------------------------------------
//以上代码不需改动!
//****************************************************************************************
//----------------------------------------------------------------------------------------
//你可以在这里定义变量
int SendBufLeng;										//报文长度
int Sendi;												//数据帧发送计数
//void PhysicalLayerSend(BYTE c);						//物理层：发送一个字节
//BYTE PhysicalLayerReceive();							//物理层：接收一个字节
void PhysicalLayerSend(char* FrameData, int Length);	//物理层发送数据函数：发送一帧报文
int PhysicalLayerReceive(char* FrameData);
int PhysicalLayerReceive(char* FrameData,int Length);				//物理层接收数据函数：接收报文数据，返回数据长度

#define ACK 0X88
#define NCK 0X55
#define HEAD 0XFE  
#define TAIL 0XFD
									
int nSending;											//重复发送的次数，重复发送8次则判断接收方无法接收

uint8_t GenerateCRC(const uint8_t* Data, size_t Length);//CRC校验函数
/*
* struct MyFrameData											//完整的帧数据，包括帧头：0XFE；帧序号；数据；校验和；帧尾：0XFD
{
	char FrameData[16];
	int FrameLength = 5;									//帧长度，便于完整发送

	MyFrameData()											//构造函数									
	{
		FrameData[0] = HEAD;
		for (int i = 1; i < 4; i++)
			FrameData[i] = -1;
		FrameData[4] = TAIL;
		FrameData[5] = '\0';
	}

	void setContent(char content)
	{
		FrameData[1] = (FrameData[1] + 1) % 8;//发送序号
		FrameData[2] = content;
		unsigned char CRC_Code = GenerateCRC((const uint8_t*)FrameData + 1, 2);//数据校验
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


void FrameDataInit(char* FrameData,unsigned char Data,int Sendi)//赋值函数，返回帧长度
{
	FrameData[0] = HEAD;
	FrameData[1] = unsigned char(Sendi + 1);
	FrameData[2] = Data;
//	unsigned char CRC_Code = GenerateCRC((const uint8_t*)FrameData + 1, 2);//数据校验
//	FrameData[3] = CRC_Code;
//	FrameData[3] = (HEAD + Sendi + Data)&0XFF;
	FrameData[3] = (Data * 0x80 * 2) % 0x87;//测试时采用简单校验
	FrameData[4] = TAIL;
}

char FrameData[16] = { 0xfe,-1,-1,-1,0xfd,0 };//定义时直接赋一次值，确保安全性
int FrameLength = 5;//发送的每一帧长度为5

//----------------------------------------------------------------------------------------
//消息处理
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP)
{
	switch (msg)
	{
	case WM_DESTROY://窗口关闭时的消息处理
		WSAAsyncSelect(Cs1, hW, 0, 0);
		closesocket(Cs1);
		WSACleanup( );
		KillTimer(hWnd,ID_TIMER);
		PostQuitMessage(0);
		break;
	case WM_CREATE://窗口创建时的消息处理
		WSAStartup(0x0101,&wsData);//网络初始化
		Cs1=socket(AF_INET, SOCK_DGRAM,0);
		Cs1A.sin_family=AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
//		Cs1A.sin_addr.s_addr =INADDR_ANY;//在本机设置的网址(可能多个)中，都有效。
		Cs1A.sin_addr.s_addr =inet_addr(Cs1IP);
		d = bind(Cs1,(struct sockaddr *) &Cs1A,sizeof(Cs1A));
		if(d == -1)//bind函数调用失败
		{
			MessageBox(0,"端口发生冲突","信道模拟",0);
			PostQuitMessage(0);
		};
		Cs2A.sin_family=AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr =inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1,hW,WM_USER+211,FD_READ);
		Beep(2000,100);//响铃提示处理

		CreateEdit("1234567890",2,2,130,25,EDIT_Sender,hW,hInst);
		CreateButton("发送",140,2,50,24,BTN_Sender,hW,hInst);
		CreateButton("复位",200,2,50,24,BTN_Reset,hW,hInst);
		CreateStatic("物理层收到的信息:",0,35,150,24,STATIC_W1,hW,hInst);
		CreateStatic("发送的信息:",160,35,150,24,STATIC_W2,hW,hInst);
		CreateMemo(" ",0,55,150,220,INFOWin1,hW,hInst);
		CreateMemo(" ",160,55,150,220,INFOWin2,hW,hInst);

		break;
//============================================================================
//接收事件触发：
//你可以在这里添加和编写代码：
	case WM_USER+211:
		switch(LOWORD(lP))
		{
		case FD_READ://网络数据接收消息处理
			//*******************************************************************************
			//进行数据帧接收处理，请在此根据协议修改或添加代码
			//以下拾行代码只是用于测试，你需要根据协议进行修改
			//*******************************************************************************
			//原代码：
			//char ReceData[100];
			//int Length;
			//Length=PhysicalLayerReceive(ReceData);					//物理层：接收一个字节
			//DataB[0] = ReceData[0];
			//DataB[1]=0;
			//char DisplayBufffer[250];
			//wsprintf(DisplayBufffer,"%02XH,  %c",(unsigned char)DataB[0],DataB[0]);
			//Puts(hW,INFOWin1,DisplayBufffer);						//显示，物理层收到的信息
//          Sleep(100);
//			MessageBox(0,DataB,"(FD_READ)",0);
			//*******************************************************************************
			
			char ReceData[100];
			memset(ReceData, 0, 100);
			int Length;
			Length = PhysicalLayerReceive(ReceData);				//物理层：接收一个字节
			DataB[0] = ReceData[0];
			DataB[1]=0;												//截断
			
			//*******************************************************************************
			break;
		}
		break;
	case WM_TIMER://定时器消息处理
		switch(wP)
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
		switch(wP)
		{
		case BTN_Sender:											// "发送" 按钮事件触发	
			GetDlgItemText(hW,EDIT_Sender,DataAA,sizeof(DataAA));	//从单行编辑框得到报文
			SendBufLeng = strlen(DataAA);								//求出报文长度
			//*******************************************************************************
			//进行数据帧组装，请在以下添加代码
			//以下两行代码只是用于测试，你需要根据协议进行修改
			//*******************************************************************************
			//原代码如下
			//PhysicalLayerSend(DataAA,SendBufLeng);					//物理层：发送一个字节
			//for(Sendi=0;Sendi<SendBufLeng;Sendi++)					//发送报文
			//{
			//	//PhysicalLayerSend(&(DataAA[Sendi]),1);			//物理层：发送一个字节
			//	char buf[22];
			//	wsprintf(buf,"%02XH,  %c",(unsigned char)DataAA[Sendi],DataAA[Sendi]);
			//	Puts(hW,INFOWin2,buf);								//显示，物理层发送的信息
			//};
			//*******************************************************************************

			//此段是尝试用timer完成功能，未果
			/*
			FrameData.setContent(DataAA[Sendi++]);
			PhysicalLayerSend(FrameData.FrameData, FrameData.FrameLength);  // 物理层：发送
			SetTimer(hW, 1, 5000, TimerProc);
			for (int i = 0; i < SendBufLeng; i++)
			{
				char buf[22];
				wsprintf(buf, "%02XH,  %c", (unsigned char)DataAA[i], DataAA[i]);
				Puts(hW, INFOWin2, buf);  // 显示，物理层发送的信息
			};
			*/
			for (Sendi = 0 ; Sendi < SendBufLeng; Sendi++)					//发送报文
			{
				nSending = 0;//nSending是重发次数，约定不超过8次；每新发送一个字节时清零
				FrameDataInit(FrameData, DataAA[Sendi], Sendi);
				FrameLength = strlen(FrameData);

			loop:PhysicalLayerSend(FrameData, 5);			//物理层：发送一帧

				char buf[32];//不同信息类型采用不同缓冲区，防止因为数据长度不同而出现信息部分覆盖的情况。
							 //或许可以用一个缓冲区、每次写入前清零来优化。
				char bufL[64];
				char bufO[128];
				char bufE[32];
				char bufR[64];

				wsprintf(buf, "%02XH,  %c", (unsigned char)DataAA[Sendi], DataAA[Sendi]);
				Puts(hW, INFOWin2, buf);								//显示，物理层发送的信息

				double time = 0;
				int errChecking = 0;//用来防止下面这个循环 在没有接收到ACK、NAK时 每循环一次都会报一次错，让结果好看一点
				while (time < 4)
				{
					Sleep(1000);//延时1s
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
		case BTN_Reset:												//清除信息框内容
			SetDlgItemText(hW,INFOWin1,(LPSTR) " ");
			SetDlgItemText(hW,INFOWin2,(LPSTR) " ");
			break;
		}
	}
finish:
	return DefWindowProc(hW, msg, wP, lP);
}

//---------------------------------------------------------------------------------------------
//物理层报文帧发送函数：发送一帧完整报文
//输入参数：char* FrameData，发送报文帧数据指针
//          int Length，报文帧数据长度
//输出参数：无
void PhysicalLayerSend(char* FrameData, int Length)					
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1,FrameData,Length,0,(struct sockaddr *) &Cs2A,CS2A_Length);
}

//---------------------------------------------------------------------------------------------
//物理层接收数据函数：接收一帧报文，返回数据长度。
//一帧报文可能由多个字节构成，该函数执行一次可能只是接收了报文帧的一个字节或一部分，
//通常需要多次执行该函数，以便接收完整数据帧。
//输入参数：char* FrameData，接收报文数据指针
//输出参数：int 函数返回值，为接收数据的长度
int PhysicalLayerReceive(char* FrameData)							
{
	int Length;
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	Length = recvfrom(Cs1,FrameData,sizeof(FrameData),0,(struct sockaddr *) &Cs2A,&CS2A_Length);
	return Length;
}

int PhysicalLayerReceive(char* FrameData, int Length)//Length：接收缓冲区长度
//这是个重载
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	return recvfrom(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, &CS2A_Length);
}
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
uint8_t GenerateCRC(const uint8_t* Data, size_t FrameLength) //CRC函数，这里用size_t而不用int是因为Length不确定
{
	uint8_t CRC_Code = 0;
	for (size_t i = 0, CRC_Code = 0; i < FrameLength; i++)
	{
		CRC_Code ^= Data[i];                 //异或赋值
		for (int j = 0; j < 8; j++)
		{
			if (CRC_Code & 0X80)				  //80：1000 0000
				CRC_Code = (CRC_Code << 1) ^ 0X07;//07：0000 0111
			else
				CRC_Code <<= 1;
		}
	}
	return CRC_Code;
}