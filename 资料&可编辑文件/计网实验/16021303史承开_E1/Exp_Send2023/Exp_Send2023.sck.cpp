// Exp_Send.cpp : Defines the entry point for the application.
// 信息通讯网络基础课程，理想信道的数据链路层协议，发送端程序, 2023.4

#include "stdafx.h"
// VC 2005   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>

using namespace std;

//--------------------------------------------------------------
// Global Variables:
// 按钮
#define BTN_Sender 501
#define BTN_Reset 502
// 单行编辑框
#define EDIT_Sender 1601
// 多行文本框
#define INFOWin1 801
#define INFOWin2 802
// 静态文本
#define STATIC_W1 701
#define STATIC_W2 702
//--------------------------------------------------------------

SOCKET             Cs1, Cs2;
struct sockaddr_in Cs1A, Cs2A;
WSADATA            wsData;
char               DataAA[200];
char               DataB[200];
int                d, i;

#define Cs1Port 6100       // 本地端口(对应于模拟通道程序中的A站端口)
#define Cs2Port 7100       // 远程端口(对应于模拟通道程序中的本地端口)
#define Cs1IP "127.0.0.1"  // 本地IP网址(127.0.0.1为本地环路)
#define Cs2IP "127.0.0.1"  // 远程IP网址(127.0.0.1为本地环路)

#define ID_TIMER 201
int  time_Num = 0;
HWND hWnd;

char DisplayStringBuffer[5000];  // 显示缓冲区

HINSTANCE        hInst;                                // current instance
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  // 回调函数
//--------------------------------------------------------------
// 主函数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // TODO: Place code here.
    MSG    msg;
    string TempString;
    char   TempChar[80];
    char   TempChar1[80];
    itoa(Cs1Port, TempChar, 10);
    TempString = "发送端[端口:";
    TempString += TempChar;
    TempString += "]－理想信道";

    hInst = hInstance;  // Store instance handle in our global variable
    WNDCLASS wc;

    memset(&wc, 0, sizeof(WNDCLASS));

    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "W1";
    RegisterClass(&wc);

    TempString.copy(TempChar1, TempString.length());
    TempChar1[TempString.length()] = 0x00;
    hWnd = CreateWindow("W1", TempChar1, WS_DLGFRAME | WS_SYSMENU, 50, 10, 320, 300, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return FALSE;
    SetTimer(hWnd, ID_TIMER, 500, NULL);  // 创建定时器，定时时间500毫秒

    ShowWindow(hWnd, nCmdShow);
    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

//--------------------------------------------------------------
// 静态文本
HWND CreateStatic(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst) {
    return CreateWindowEx(WS_EX_PALETTEWINDOW, "STATIC", Titel, WS_VISIBLE | WS_CHILD, x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}

//--------------------------------------------------------------
// 按钮
HWND CreateButton(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst) {
    return ::CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", Titel, WS_VISIBLE | WS_CHILD, x0, y0, w, h, hW, (HMENU)ID, hInst,
                            NULL);
}
//--------------------------------------------------------------
// 单行编辑框
HWND CreateEdit(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst) {
    return ::CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel, WS_VISIBLE | WS_CHILD | ES_LEFT /*| ES_MULTILINE | WS_HSCROLL */, x0,
                            y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
// 多行文本框
HWND CreateMemo(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst) {
    return ::CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
                            WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | ES_READONLY | WS_HSCROLL | WS_VSCROLL, x0, y0, w, h,
                            hW, (HMENU)ID, hInst, NULL);
}
//---------------------------------------------------------------------------
// 添加控件文本
void Puts(HWND hW, int ID_EDIT, char* str) {
    GetDlgItemText(hW, ID_EDIT, DisplayStringBuffer, sizeof(DisplayStringBuffer));
    if (strlen(DisplayStringBuffer) > 4900) {
        // MessageBox(0,"显示缓冲区溢出！","显示缓冲区",0);
        strcpy(DisplayStringBuffer, "  \r\n");
    }
    strcat(DisplayStringBuffer, "\r\n");
    strcat(DisplayStringBuffer, str);
    SetDlgItemText(hW, ID_EDIT, (LPSTR)DisplayStringBuffer);
    SendMessage(GetDlgItem(hW, ID_EDIT), WM_VSCROLL, SB_THUMBPOSITION + 1000 * 0x10000, 0);
}
//---------------------------------------------------------------------------
// 以上代码不需改动!
//********************************************************************************
//--------------------------------------------------------------------------------
// 你可以在这里定义变量
#define ACK 0x88
#define NCK 0x55
#define FRAME_HEADER 0x7E  // 定义帧头、帧尾
#define FRAME_TAIL 0x7E    
int     SendBufLeng;  // 定义报文长度
int     Sendi;        // 定义数据帧发送计数
int     frameLen = 0;
uint8_t crc8(const uint8_t* data, size_t length);//CRC校验函数
struct Frame //定义帧
{
    Frame() 
	{
        frame[0] = FRAME_HEADER;//帧头
        frame[1] = -1;
        frame[4] = FRAME_TAIL;//帧尾
        frame[5] = 0;
     }
    void setContent(char content) 
	{
        frame[1] = (frame[1] + 1) % 8;//发送序号
        frame[2] = content;
        unsigned char crc = crc8((const uint8_t*)frame + 1, 2);//数据校验
        frame[3] = crc;
     }
	int  length = 5;
    char frame[6];
} frame;
// void PhysicalLayerSend(BYTE c);						//物理层：发送一个字节
// BYTE PhysicalLayerReceive();							//物理层：接收一个字节
void PhysicalLayerSend(char* FrameData, int Length);    // 物理层发送数据函数：发送一帧报文
int  PhysicalLayerReceive(char* FrameData);             // 物理层接收数据函数：接收报文数据，返回数据长度

uint8_t crc8(const uint8_t* data, size_t length) //CRC函数
{
    uint8_t crc = 0;
    for (size_t i = 0; i < length; i++) 
	{
        crc ^= data[i];
        for (int j = 0; j < 8; j++) 
		{
            if (crc & 0x80) 
			{crc = (crc << 1) ^ 0x07;}
            else 
			{crc <<= 1;}
        }
    }
    return crc;
}

void CALLBACK TimerProc(HWND aHwnd, UINT aMessage, UINT_PTR aTimerId, DWORD aTime)
{ PhysicalLayerSend(frame.frame, frame.length);}
//--------------------------------------------------------------
// 消息处理
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP) 
{
    switch (msg) 
	{
    case WM_DESTROY:                  // 窗口关闭时的消息处理
        WSAAsyncSelect(Cs1, hW, 0, 0);
        closesocket(Cs1);
        WSACleanup( );
        KillTimer(hWnd, ID_TIMER);
        PostQuitMessage(0);
        break;
    case WM_CREATE:                   // 窗口创建时的消息处理
        WSAStartup(0x0101, &wsData);  // 网络初始化
        Cs1             = socket(AF_INET, SOCK_DGRAM, 0);
        Cs1A.sin_family = AF_INET;
        Cs1A.sin_port   = htons(Cs1Port);
                                      // Cs1A.sin_addr.s_addr =INADDR_ANY;//在本机设置的网址(可能多个)中，都有效。
        Cs1A.sin_addr.s_addr = inet_addr(Cs1IP);
        d                    = bind(Cs1, (struct sockaddr*)&Cs1A, sizeof(Cs1A));
        if (d == -1)                  // bind函数调用失败
        {
            MessageBox(0, "端口发生冲突", "信道模拟", 0);
            PostQuitMessage(0);
        };
        Cs2A.sin_family = AF_INET;
        Cs2A.sin_port = htons(Cs2Port);
        Cs2A.sin_addr.s_addr = inet_addr(Cs2IP);
        WSAAsyncSelect(Cs1, hW, WM_USER + 211, FD_READ);
        Beep(2000, 100);             // 响铃提示处理
        CreateEdit("1234567890", 2, 2, 130, 25, EDIT_Sender, hW, hInst);
        CreateButton("发送", 140, 2, 50, 24, BTN_Sender, hW, hInst);
        CreateButton("复位", 200, 2, 50, 24, BTN_Reset, hW, hInst);
        CreateStatic("物理层收到的信息:", 0, 35, 150, 24, STATIC_W1, hW, hInst);
        CreateStatic("发送的信息:", 160, 35, 150, 24, STATIC_W2, hW, hInst);
        CreateMemo(" ", 0, 55, 150, 220, INFOWin1, hW, hInst);
        CreateMemo(" ", 160, 55, 150, 220, INFOWin2, hW, hInst);

                                    // SetTimer(hWnd,ID_TIMER,1000,NULL);
        break;
        //============================================================================
        // 接收事件触发：
        // 你可以在这里添加和编写代码：
    case WM_USER + 211:
        switch (LOWORD(lP)) {
        case FD_READ:  // 网络数据接收消息处理
            //*******************************************************************************
            // 进行数据帧接收处理，请在此根据协议修改或添加代码
            // 以下拾行代码只是用于测试，你需要根据协议进行修改
            //*******************************************************************************
            char ReceData[100];
            memset(ReceData, 0, 100);
            int Length;
            Length = PhysicalLayerReceive(ReceData);  // 物理层：接收一个字节
            if (Length == 1) 
			{
                KillTimer(hW, 1);//开始计时
                if ((ReceData[0] & 0xff) == ACK) 
				{
                    if (Sendi == SendBufLeng) 
					{
                        Sendi = 0;
                        goto finish;//出现差错重新发送
                    }
                    frame.setContent(DataAA[Sendi++]);//接收后确认正确才继续
                }
                PhysicalLayerSend(frame.frame, frame.length);
                SetTimer(hW, 1, 5000, TimerProc);//超过5000ms则重发
                char DisplayBufffer[250];
                wsprintf(DisplayBufffer, "%02XH,  %c", (unsigned char)ReceData[0], ReceData[0]);
                Puts(hW, INFOWin1, DisplayBufffer);  // 显示，物理层收到的信息
            }
            //			MessageBox(0,DataB,"(FD_READ)",0);
            //*******************************************************************************
            break;
        }
        break;
    case WM_TIMER:  // 定时器消息处理
        switch (wP) 
		{
        case ID_TIMER:
             time_Num++;
            // char buf[22];
            // wsprintf(buf,"TIMER:%d",time_Num);
            // Puts(hW,INFOWin1,buf);								//显示，物理层收到的信息
            break;
        };
        break;
    case WM_COMMAND:  // 按钮命令消息处理
        switch (wP) 
		{
        case BTN_Sender: 
			{                                            // "发送" 按钮事件触发
            GetDlgItemText(hW, EDIT_Sender, DataAA, sizeof(DataAA));  // 从单行编辑框得到报文
            SendBufLeng = strlen(DataAA);                             // 求出报文长度
            //*******************************************************************************
            // 进行数据帧组装，请在以下添加代码
            // 以下两行代码只是用于测试，你需要根据协议进行修改
            //*******************************************************************************
            frame.setContent(DataAA[Sendi++]);
            PhysicalLayerSend(frame.frame, frame.length);  // 物理层：发送
            SetTimer(hW, 1, 5000, TimerProc);
            for (int i = 0; i < SendBufLeng; i++) 
			{
                char buf[22];
                wsprintf(buf, "%02XH,  %c", (unsigned char)DataAA[i], DataAA[i]);
                Puts(hW, INFOWin2, buf);  // 显示，物理层发送的信息
            };
        }
        //*******************************************************************************
        break;
        case BTN_Reset:  // 清除信息框内容
            SetDlgItemText(hW, INFOWin1, (LPSTR) " ");
            SetDlgItemText(hW, INFOWin2, (LPSTR) " ");
            break;
        }
    }
finish:
    return DefWindowProc(hW, msg, wP, lP);
}

//---------------------------------------------------------------------------------------------
// 物理层报文帧发送函数：发送一帧完整报文
// 输入参数：char* FrameData，发送报文帧数据指针
//          int Length，报文帧数据长度
// 输出参数：无
void PhysicalLayerSend(char* FrameData, int Length) 
{
    int CS2A_Length;
    CS2A_Length = sizeof(Cs2A);
    sendto(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, CS2A_Length);
}

//---------------------------------------------------------------------------------------------
// 物理层接收数据函数：接收一帧报文，返回数据长度。
// 一帧报文可能由多个字节构成，该函数执行一次可能知识接收了报文帧的一个字节或一部分，
// 通常需要多次执行该函数，以便接收完整数据帧。
// 输入参数：char* FrameData，接收报文数据指针
// 输出参数：int 函数返回值，为接收数据的长度
int PhysicalLayerReceive(char* FrameData) 
{
    int Length;
    int CS2A_Length;
    CS2A_Length = sizeof(Cs2A);
    Length = recvfrom(Cs1, FrameData, sizeof(FrameData), 0, (struct sockaddr*)&Cs2A, &CS2A_Length);
    return Length;
}
//---------------------------------------------------------------------------------------------
