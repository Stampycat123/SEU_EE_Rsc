// Exp_Receiver.cpp : Defines the entry point for the application.
//信息通讯网络基础课程，理想信道的数据链路层协议实现，接收端程序 2024.3
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
//按钮
#define BTN_Quit 501
#define BTN_Reset 502
//单行编辑框
#define EDIT_Receiver 601
//多行文本框
#define INFOWin1 801
#define INFOWin2 802
//静态文本
#define STATIC_W1 701
#define STATIC_W2 702
//----------------------------------------------------------------------------------------
WSADATA wsData;
SOCKET Cs1,Cs2;
struct sockaddr_in Cs1A,Cs2A;
char DataB[200];
int d,i;
#define Cs2Port 7100		//远程端口(对应于模拟通道程序中的本地端口)
#define Cs1Port 8100		//本地端口(对应于模拟通道程序中的B站端口)
#define Cs1IP   "127.0.0.1"	//本地IP网址(127.0.0.1为本地环路)
#define Cs2IP   "127.0.0.1"	//远程IP网址(127.0.0.1为本地环路)

char DisplayStringBuffer[5000];//显示缓冲区
//----------------------------------------------------------------------------------------
// Global Variables:
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
	TempString = "接收端[端口:";
	TempString += TempChar;
	TempString += "]－理想信道\0";
	
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
	return CreateWindowEx(WS_EX_PALETTEWINDOW,"BUTTON",Titel,
		WS_VISIBLE | WS_CHILD ,
		x0,y0,w,h, hW,(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//创建单行编辑框
HWND CreateEdit(char *Titel,int x0,int y0,int w,int h,int ID,HWND hW,HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",Titel,
		WS_VISIBLE | WS_CHILD |
		    ES_LEFT | ES_MULTILINE | WS_HSCROLL ,
		x0,y0,w,h, hW,
		(HMENU)ID,hInst,NULL);
}
//----------------------------------------------------------------------------------------
//创建多行文本框
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
//添加控件文本
void Puts(HWND hW,int ID_EDIT,char *str)
{	
	GetDlgItemText(hW,ID_EDIT,DisplayStringBuffer,sizeof(DisplayStringBuffer));
	if (strlen(DisplayStringBuffer) > 4900)
	{
		//MessageBox(0,"显示缓冲区溢出！","显示缓冲区",0);
		strcpy(DisplayStringBuffer,"  \r\n");
	};
	strcat(DisplayStringBuffer,"\r\n");
	strcat(DisplayStringBuffer,str);
	SetDlgItemText(hW,ID_EDIT,(LPSTR) DisplayStringBuffer);
	SendMessage(GetDlgItem(hW,ID_EDIT),WM_VSCROLL,SB_THUMBPOSITION+1000*0x10000,0);
}
//----------------------------------------------------------------------------------------
//以上不需改动!
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//你可以在这里定义新变量
void PhysicalLayerSend(char* FrameData, int Length);	//物理层：发送一帧报文
int PhysicalLayerReceive(char* FrameData, int Length);	//物理层：接收报文数据，返回数据长度
int PhysicalLayerReceive(char* FrameData);

#define ACK 0X88
#define NAK 0X55
#define HEAD 0XFE  
#define TAIL 0XFD

uint8_t GenerateCRC(const uint8_t* Data, size_t FrameLength); //CRC函数，这里用size_t而不用int是因为Length不确定

struct FrameData
{
	bool FrameCheckStatus;//判断是否成功接收数据，初始（等待时）为0
	char FrameDataBuffer[256];//缓冲区
	int FrameBufferLength;//缓冲区长度
};

FrameData MyFrameData;//帧内容
extern int State = 0;//目前接收状态，0代表闲置，1代表接收到帧头，2代表接收到帧尾
extern int FrameLength = 0;//实际接收到可能错误的帧的长度，无误时应在接收到TAIL的同时自增到5
extern int Tail = 4;//帧尾的数组下标，用相对位置访问帧的字节
extern int WrongRec = 0;
extern int WrongRecLen = 0;
extern char* WrongRecCnt = new char[256];
extern char* BufOfSame = new char[1024];
extern int LengthOfSame = 0;

//----------------------------------------------------------------------------------------
//函数声明：
int ProtocolOfFrame(unsigned char* ReceData, int nLength, HWND hW);//帧数据处理
int FrameDataInit();//帧数据的初始化

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
		PostQuitMessage(0);
		break;
	case WM_CREATE://窗口创建时的消息处理
		WSAStartup(0x0101,&wsData);//网络初始化
		Cs1=socket(AF_INET, SOCK_DGRAM,0);
		Cs1A.sin_family=AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
//		Cs1A.sin_addr.s_addr =INADDR_ANY;//在本机设置的网址(可能多个)中，都有效。
		Cs1A.sin_addr.s_addr =inet_addr(Cs1IP);
		d=bind(Cs1,(struct sockaddr *) &Cs1A,sizeof(Cs1A));
		if(d==-1)//bind函数调用失败
		{
			MessageBox(0,"端口发生冲突","信道模拟",0);
			PostQuitMessage(0);
		};
		Cs2A.sin_family=AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr =inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1,hW,WM_USER+212,FD_READ);
		Beep(2000,100);//响铃提示处理

		CreateEdit("接收端",2,2,130,20,EDIT_Receiver,hW,hInst);
		CreateButton("退出", 140,2,50,24,BTN_Quit,hW,hInst);
		CreateButton("复位",200,2,50,24,BTN_Reset,hW,hInst);
		CreateStatic("物理层收到的信息:",0,35,150,24,STATIC_W1,hW,hInst);
		CreateStatic("上交网络层的信息:",160,35,150,24,STATIC_W2,hW,hInst);
		CreateMemo(" ",0,55,150,220,INFOWin1,hW,hInst);
		CreateMemo(" ",160,55,150,220,INFOWin2,hW,hInst);

		break;
//============================================================================
//接收消息事件：
//你可以在这里添加和编写代码：
	case WM_USER+212:
		switch(LOWORD(lP))
		{
		case FD_READ://网络数据接收消息处理
			//*****************************************************************************
			//进行数据帧接收处理，请在此根据协议修改或添加代码
			//以下13行代码只是用于测试，你需要根据协议进行修改
			//*****************************************************************************

			//这是第一版代码
			/*//char ReceData[100];
			//int Length;
			//Length=PhysicalLayerReceive(ReceData);					//物理层：接收一个字节
			//DataB[0] = ReceData[0];
			//DataB[1]=0;
			//char DisplayBufffer[250];
			//wsprintf(DisplayBufffer,"%02XH",(unsigned char)DataB[0]);
			//Puts(hW,INFOWin1,DisplayBufffer);						//显示，物理层收到的信息
			//DataB[0]=(DataB[0]&0x0F)+0x30;							//去掉高4位内容,低4位转为ASCII码
			//Puts(hW,INFOWin2,DataB);								//显示，上交网络层的信息
			//char SendData[100];
			//SendData[0] = 0x88;
			//PhysicalLayerSend(&(SendData[0]),1);					//物理层：发送一个字节,表示发送正确
			//break;
			*/
			char ReceData[100];
			int Length;
			char DisplayBufffer[250];
			Length = PhysicalLayerReceive(ReceData, 100); // 物理层：接收一个字节

			ProtocolOfFrame((unsigned char*)ReceData, Length, hW);
			Sleep(50);//sleep是为了按序接收
			//*****************************************************************************
			/*
			char ReceData[100];
			memset(ReceData, 0, 100);
			int Length;
			char DisplayBufffer[250];								//缓冲区
			Length = PhysicalLayerReceive(ReceData,100);					//物理层：接收一帧报文
			*/
			/*
			原代码：
			DataB[0] = ReceData[0];
			DataB[1]=0;
			wsprintf(DisplayBufffer,"%02XH",(unsigned char)DataB[0]);
			Puts(hW,INFOWin1,DisplayBufffer);						//显示，物理层收到的信息
			DataB[0]=(DataB[0]&0x0F)+0x30;							//去掉高4位内容,低4位转为ASCII码
			Puts(hW,INFOWin2,DataB);								//显示，上交网络层的信息
			char SendData[100];
			SendData[0] = 0x88;
			PhysicalLayerSend(&(SendData[0]),1);	
			*/
			//*****************************************************************************
			break;
		}
		break;
//============================================================================
	case WM_COMMAND://按钮命令消息处理
		switch(wP)
		{
		case BTN_Quit:												//退出程序
			PostQuitMessage(0);
			break;
		case BTN_Reset:												//清除信息框内容
			SetDlgItemText(hW,INFOWin1,(LPSTR) " ");
			SetDlgItemText(hW,INFOWin2,(LPSTR) " ");
			break;
		}
	}
	return DefWindowProc(hW, msg, wP, lP);
}

//----------------------------------------------------------------------------------------
//物理层报文帧发送函数：发送一帧完整报文
//输入参数：char* FrameData，发送报文帧数据指针
//          int Length，报文帧数据长度
//输出参数：无
void PhysicalLayerSend(char* FrameData, int Length)					
{
	int CS2A_Length;
	CS2A_Length = sizeof(Cs2A);
	sendto(Cs1, FrameData, Length, 0, (struct sockaddr*)&Cs2A, CS2A_Length);
}

//----------------------------------------------------------------------------------------
//物理层接收数据函数：接收一帧报文，返回数据长度。
//一帧报文可能由多个字节构成，该函数执行一次可能知识接收了报文帧的一个字节或一部分，
//通常需要多次执行该函数，以便接收完整数据帧。
//输入参数：char* FrameData，接收报文数据指针
//输出参数：int 函数返回值，为接收数据的长度


int PhysicalLayerReceive(char* FrameData,int Length)//Length：接收缓冲区长度
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

//帧数据处理
int ProtocolOfFrame(unsigned char* ReceData, int nLength, HWND hW)//nLength：帧长度
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

			for (int i = 0; i < nLength; i++)//遍历，输出提取到的物理层信息
			{
				char testBuf[64];
				wsprintf(testBuf, "%02XH", (unsigned char)TestFrameData.FrameDataBuffer[i]);
				Puts(hW, INFOWin1, testBuf);						//显示，物理层收到的信息
			}
			Puts(hW, INFOWin1, "*******************");

			int i;
			for (i = 0; i < 5; i++)
			{
				//switch ((unsigned char)TestFrameData.FrameDataBuffer[i])
								//		case 0xfd://帧结束后再发送ACK。如果帧不完整，判错；如果帧完整但内容不正确，判错
								//			if (TestFrameData.CurrentFrameReceivedPos != 4)//接收到0xfd但状态不等于4说明帧部分遗失
				if (i == 4)//接收到0xfd但状态不等于4说明帧部分遗失
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
					DataB[0] = (DataB[0] & 0x0F) + 0x30;							//去掉高4位内容,低4位转为ASCII码
					wsprintf(DisplayBufffer, "%02XH, %c", (unsigned char)DataB[0], DataB[0]);
					Puts(hW, INFOWin2, DisplayBufffer);

					//生成校验（使用简单校验和，可以使用CRC检验）
					int Temp = 0x0;
					Temp += TestFrameData.FrameDataBuffer[0];
					Temp += TestFrameData.FrameDataBuffer[1];
					Temp += TestFrameData.FrameDataBuffer[2];
					if (Temp == TestFrameData.FrameDataBuffer[3])//比较校验状态
					{
						TestFrameData.FrameCheckStatus = 1;
					}
					else
					{
						TestFrameData.FrameCheckStatus = 0;
					}

					//判错则发送0x55，否则发送0x88
					if (TestFrameData.FrameCheckStatus)
					{
						//SendData[0] = 0x88;
						//PhysicalLayerSend(&(SendData[0]), 1);
						//char buf[22];
						//wsprintf(buf, "0x%02xh, %c", (unsigned char)TestFrameData.FrameDataBuffer);
						//Puts(hW, INFOWin2, buf);
						//DataB[2] = (DataB[2] & 0x0F) + 0x30;							//去掉高4位内容,低4位转为ASCII码
						//Puts(hW,INFOWin2,DataB);								//显示，上交网络层的信息
						SendData[0] = 0x88;
						PhysicalLayerSend(&(SendData[0]), 2);					//物理层：发送一个字节,表示发送正确
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
for (int i = 0; i < nLength; i++)//提取信息，这里用循环和nLength是因为，无论一次性接收到多少个字节，这样均能完成写入
{
	MyFrameData.FrameDataBuffer[FrameLength] = ReceData[i];
	FrameLength++;
}

//下面这个if是针对方式二的解决
//思路是：如果都连续重发4次了，接收端猜测可能是有数据送达，但由于信道被阻塞了。因此，查阅并提取出每一次错误接收内容中的重复部分，
//跳过帧头帧尾，判断是否有两组重复的数据AB，满足B是A的校验和，则将A上交到网络层，物理层输出缓存的数据
if (WrongRec == 4)//重发4次是因为，假如重发五次，如果仍然判错，会出现上一个数据与下一个数据的前两次重发一起被记录的情况
{
	for (int m = 0; m < WrongRecLen; m++)
	{
		if ((unsigned char)WrongRecCnt[m] != HEAD && (unsigned char)WrongRecCnt[m] != TAIL && (unsigned char)WrongRecCnt[m] > 0x11)
		//如果不是帧头也不是帧尾也不是序号
		{
			for (int n = m + 1; n < WrongRecLen; n++)//就判断是否发现重复项，有则录入一次
			{
				if (WrongRecCnt[m] == WrongRecCnt[n])
				{
					BufOfSame[LengthOfSame++] = WrongRecCnt[m];
					BufOfSame[LengthOfSame++] = WrongRecCnt[m];
				}
			}
		}
	}
	//下面这段注释掉的代码用于测试
	//不注释掉了，注释掉了物理层就没有输出了
	for (int j = 0; j < LengthOfSame; j++)//遍历，输出提取到的物理层信息
	{
		char testBuf2[128];
		wsprintf(testBuf2, "%02xh", (unsigned char)BufOfSame[j]);
		Puts(hW, INFOWin1, testBuf2);						//显示，物理层收到的信息
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
	//重发四次就重置缓存
	memset(WrongRecCnt, 0, 256);
	WrongRec = 0;
	WrongRecLen = 0;
	memset(BufOfSame, 0, 1024);
	LengthOfSame = 0;
}
//下面这段注释掉的代码是初版思路框架：
/*
		int judge = 0;
		for (int i = 0; i < FrameLength; i++)
		{
			switch ((unsigned char)MyFrameData.FrameDataBuffer[i])//如果一次接收一个字节，这两个switch可以合并
//			switch ((unsigned char)ReceData[i])
			{
			case HEAD:
				if (State == 1)//如果接收到了帧头，但状态不为0（即没有接收到帧尾，或有两个以上的帧头）
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
			if ((unsigned char)MyFrameData.FrameDataBuffer[i] == HEAD && State == 0)//如果接收到帧头，进入State=1的状态，退出循环
			{
				State = 1;
				Puts(hW, INFOWin1, "*******************");//分割，便于人机交互
				break;
			}
			else if ((unsigned char)MyFrameData.FrameDataBuffer[i] == HEAD && State == 2)//如果接收到帧头，但State是2，说明没接收到帧尾。重发。
			{
				Puts(hW, INFOWin1, "Loses of FRAME_TAIL!");//提示帧尾丢失
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

    	switch ((unsigned char)MyFrameData.FrameDataBuffer[FrameLength-1])//如果储存的最后一个字节是TAIL，说明接收到了帧尾
		{
		case TAIL:
			if (HeadRec == false)//如果没帧头就有帧尾了
			{
				Puts(hW, INFOWin1, "Invalid Data.");//提示此信息无效
				State = 2;
				MyFrameData.FrameCheckStatus = 0;//重发
				goto FB;
			}
			if (FrameLength < 5)//接收长度小于5，说明信息没有接收全。重发
			{
				Puts(hW, INFOWin1, "Frame incomplete.");//提示信息不全
				State = 2;
				//下面这段注释掉的代码尝试的思路是：如果数据没有接收全，则再接收一次数据，没有接收到再重发
				//实际运行时，如果出现数据缺失，接收端直接闪退
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
			for (int j = 0; j < FrameLength; j++)//遍历，输出提取到的物理层信息
			//放在这里是因为接收到帧尾、且能够正确输出，再把物理层接收的内容输出
			{
				char testBuf[64];
				wsprintf(testBuf, "%02xh", (unsigned char)MyFrameData.FrameDataBuffer[j]);
				Puts(hW, INFOWin1, testBuf);						//显示，物理层收到的信息
			}
			//if (State == 0)//如果接收到了帧尾，但状态不为1（即没有接收到帧头）
			//{
			//	Puts(hW, INFOWin1, "Loses of FRAME_HEAD!");
			//	Tail = FrameLength - 1;//此时读完了所有数据，总长度即为帧的总长度
			//}
			Puts(hW, INFOWin1, "*******************");
			State = 2;
			break;
		}

		Tail = FrameLength - 1;//修正一次Tail的数值。理想信道，FrameLength=5，Tail保持不变为4

		char buf[22];
		if (State == 2)
		{
			DataB[0] = MyFrameData.FrameDataBuffer[Tail - 2];
			DataB[1] = 0;
			int Temp = ((unsigned char)MyFrameData.FrameDataBuffer[Tail - 2] * 0x80 * 2) % 0x87;//本地生成的校验，这里用简单校验来测试

			//下面这段是最开始用来判断接收是否完整的思路，但后来修改了判断帧尾的代码，所以这段功能重复了
			//不删好像也没什么问题，删了万一错了怎么办，不删了吧>_<
			switch ((unsigned char)MyFrameData.FrameDataBuffer[Tail])//也可以不用switch，直接判断FrameLength是否为5
			{
			case TAIL:
				MyFrameData.FrameCheckStatus = 1;
				//wsprintf(buf, "Message Length completed");
				//Puts(hW, INFOWin1, buf);

				//生成校验
				/*
				int Temp = 0x0;
				Temp += (unsigned char)TestFrameData.FrameDataBuffer[0];
				Temp += (unsigned char)TestFrameData.FrameDataBuffer[1];
				Temp += (unsigned char)TestFrameData.FrameDataBuffer[2];
				*/
				/*
				char TempFrameData[6];
				strcpy_s(TempFrameData, 6, TestFrameData.FrameDataBuffer);
				unsigned char CRC_Code = GenerateCRC((const uint8_t*)TestFrameData.FrameDataBuffer + 1, 2);//数据校验
				TempFrameData[3] = CRC_Code;
				*/
				if ((unsigned char)Temp == (unsigned char)MyFrameData.FrameDataBuffer[Tail - 1])//比较校验状态
					MyFrameData.FrameCheckStatus = 1;
				else
					MyFrameData.FrameCheckStatus = 0;
				break;
			default:
				MyFrameData.FrameCheckStatus = 0;
				wsprintf(buf, "Message missing");
				//				wsprintf(buf, "%d", FrameLength);//用于调试
				Puts(hW, INFOWin1, buf);
				break;
			};

			//对正误两种情况的处理（发ACK或NAK）在这里统一进行。FB是feedback的缩写
			//判错则发送0x55，否则发送0x88
			//重置各个参数的操作理论上应该放进FrameDataInit函数里，但这里要改的太多了，所以将就一下（bushi（代码也没长多少
		FB:			if (MyFrameData.FrameCheckStatus)
		{
			char DisplayBufffer[250];//如果二者均正确才上交到网络层
			DataB[0] = (DataB[0] & 0x0F) + 0x30;							//去掉高4位内容,低4位转为ASCII码
			wsprintf(DisplayBufffer, "%c", DataB[0]);
			Puts(hW, INFOWin2, DisplayBufffer);

			WrongRec = 0;
			memset(WrongRecCnt, 0, 256);
			WrongRecLen = 0;
			memset(BufOfSame, 0, 1024);
			LengthOfSame = 0;

			SendData[0] = 0x88;//并发送确认信息
			PhysicalLayerSend(&(SendData[0]), 1);					//物理层：发送一个字节,表示发送正确
			State = 0;
			FrameLength = 0;
			memset(MyFrameData.FrameDataBuffer, 0, 256);
			Tail = 4;
		}
		else
		{
			SendData[0] = 0x55;//如果判错，就不上交，并发送NCK
			PhysicalLayerSend(&(SendData[0]), 1);

			strcpy_s(WrongRecCnt + WrongRecLen, FrameLength + 1, MyFrameData.FrameDataBuffer);//记录错误
			WrongRecLen += FrameLength;
			WrongRecCnt[WrongRecLen] = '0';
			WrongRec++;
			LengthOfSame = 0;
			//下面这段是用来调试的

			//for (int j = 0; j < WrongRecLen; j++)//遍历，输出提取到的物理层信息
			//{
			//	char testBuf[128];
			//	wsprintf(testBuf, "%02xh", (unsigned char)WrongRecCnt[j]);
			//	Puts(hW, INFOWin1, testBuf);						//显示，物理层收到的信息
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

//帧数据的初始化
int FrameDataInit()
{
	MyFrameData.FrameBufferLength = 0;
	MyFrameData.FrameCheckStatus = 1;
	return 0;
}

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