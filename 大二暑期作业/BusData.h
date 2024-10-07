
#pragma once

#include "fstream"
#include"FileMissing.h"
//#include"stdlib.h"

using namespace std;
//bus1 0 0 nanjing nanjing 100 100 100 0 bus2 1 10 jiangsu jiangsu 200 200 200 1 bus3 chengdu chengdu 300 300 300 2

struct InfoData
{
	char no[32];
	int hour;
	int minute;
	char Starting_station[32];
	char Last_station[32];
	int time;
	int fare;
	int maxPas;
	int sold;

	//构造函数
	InfoData(int H = 0, int M = 0, int T = 0, int F = 0, int MP = 0, int S = 0, char NO[] = 0, char SS[] = 0, char LS[] = 0)
	{
		if (NO && NO[0])strcpy_s(no, NO);
		else no[0] = 0;
		if (SS && SS[0])strcpy_s(Starting_station, SS);
		else Starting_station[0] = 0;
		if (LS && LS[0])strcpy_s(Last_station, LS);
		else Last_station[0] = 0;
       

		hour = H;
		minute = M;
		time = T;
		fare = F;
		maxPas = MP;
		sold = S;
	}
	
	InfoData(CString NO, CString H, CString M, CString SS, CString LS, CString T, CString F, CString MP, CString S)
	{
		/*strcpy_s(no, (LPSTR)(LPCTSTR)NO);
		strcpy_s(Starting_station, (LPSTR)(LPCTSTR)SS);
		strcpy_s(Last_station, (LPSTR)(LPCTSTR)LS);*/
		/*CStringToInteger(H, hour);
		CStringToInteger(M, minute);
		CStringToInteger(T, time);
		CStringToInteger(F, fare);
		CStringToInteger(MP, maxPas);
		CStringToInteger(S, sold);*/
		hour = CStringToInteger(H);
		minute = CStringToInteger(M);
		time = CStringToInteger(T);
		fare = CStringToInteger(F);
		maxPas = CStringToInteger(MP);
		sold = CStringToInteger(S);

		CStringToChar(NO, no);
		CStringToChar(SS, Starting_station);
		CStringToChar(LS, Last_station);
	}

	void CStringToInteger(CString cstr, int I)
	{
		/*char temp[32];
		strcpy_s(temp, (LPSTR)(LPCTSTR)cstr);
		I = atoi(temp);*/
		I = _ttoi(cstr);//ttoi:TCHAR To Integer,TCHAR类型在有Unicode宏定义时被编译为WCHAR，其他时候为char类型
	}//为何此函数不行？

	int CStringToInteger(CString cstr)
	{
		return(_ttoi(cstr));
	}

	void CStringToChar(CString cstr, char c[])
	{
		//string str = CStringA(cstr);//通过string类型作为媒介
		//char ctemp[32];
		//strncpy_s(c, _countof(ctemp), str.c_str(), cstr.GetLength());//查的，并没有看懂
		
		//memcpy(c, LPCTSTR(cstr), cstr.GetLength() * sizeof(TCHAR));

		string str;
		str = _bstr_t(cstr).operator const char* ();
		sprintf_s(c,sizeof(c), "%s", str.c_str());
	}

	int timeToMinute(int hour, int minute)
	{
		return (hour * 60 + minute);
	}

	//CString no, hourMinnute, Starting_station, Last_station, time, fare, maxPas, sold;
	//InfoData(char HM[] = 0, char T[] = 0, char F[] = 0, char MP[] = 0, char S[] = 0, char NO[] = 0, char SS[] = 0, char LS[] = 0)
	//{
	//	no = NO;
	//	hourMinnute = HM;
	//	Starting_station = SS;
	//	Last_station = LS;
	//	time = T;
	//	fare = F;
	//	maxPas = MP;
	//	sold = S;
	//}

	//bool operator==(const InfoData& other)const
	//{
	//	//if (strcmp(no, other.no) == 0)
	//	if (no == other.no)
	//		return true;
	//	return false;
	//}

	/*InfoData& operator=(const InfoData& other)
	{
		if (this == &other)return*this;

		this->hour = other.hour;
		this->minute = other.minute;
		this->time = other.time;
		this->fare = other.fare;
		this->maxPas = other.maxPas;
		this->sold = other.sold;
		if (other.no && other.no[0])strcpy_s(this->no, other.no);
		else this->no[0] = 0;
		if (other.Starting_station && other.Starting_station[0])strcpy_s(this->Starting_station, other.Starting_station);
		else this->Starting_station[0] = 0;
		if (other.Last_station && other.Last_station[0])strcpy_s(this->Last_station, other.Last_station);
		else this->Last_station[0] = 0;
		return *this;
	}*/
};

struct InfoDataCStr
{
	CString no, hourMinnute, Starting_station, Last_station, time, fare, maxPas, sold;

	InfoDataCStr(InfoData data)
	{
		if (data.no && data.no[0])
			no = data.no;
		else
			no = "NULLno";
		if (data.Starting_station && data.Starting_station[0])
			Starting_station = data.Starting_station;
		else
			Starting_station = "NULLSS";
		if (data.Last_station && data.Last_station[0])
			Last_station = data.Last_station;
		else
			Last_station = "NULLLS";

		hourMinnute.Format(L"%d:%d", /*hFormat(data.hour), mFormat(data.minute)*/data.hour, data.minute);
		time.Format(L"%d分钟", data.time);
		fare.Format(L"%d", data.fare);
		maxPas.Format(L"%d", data.maxPas);
		sold.Format(L"%d", data.sold);
	}

	InfoDataCStr(char HM[] = 0, char T[] = 0, char F[] = 0, char MP[] = 0, char S[] = 0, char NO[] = 0, char SS[] = 0, char LS[] = 0)
	{
		no = NO;
		hourMinnute = HM;
		Starting_station = SS;
		Last_station = LS;
		time = T;
		fare = F;
		maxPas = MP;
		sold = S;
	}

	bool operator==(const InfoData& other)const
	{
		//if (strcmp(no, other.no) == 0)
		if (no == other.no)
			return true;
		return false;
	}

	/*CString hFormat(int h)
	{
		CString hCstr;
		if (h >= 0 && h < 24)
		{
			hCstr.Format(L"%d", h);
		}
		else
			hCstr.Format(L"时间信息错误！(小时)");

		return hCstr;
	}*/

	/*tring mFormat(int m)
	{
		string mCstr;
		if (m >= 0 && m < 60)
		{
			if (m < 10)
				mCstr.Format(L"0%d", m);
			else
				mCstr.Format(L"%d", m);
		}
		else
			mCstr.Format(L"时间信息错误！(分钟)");

		return mCstr;
	}*/
};

//typedef CList<InfoData, InfoData&> DATALIST_TYPE;
//class BusData
//{
//protected:
//
//	DATALIST_TYPE DataList;
//	CFile File;
//	CString Filename;
//
//public:
//	BusData(void)
//	{
//	};
//	BusData(CString fileName)
//	{
//		Filename = fileName;
//	}
//	~BusData(void)
//	{
//		DataList.RemoveAll();
//	};
//public:
//	void Read()
//	{
//		if (File.Open(Filename, CFile::modeRead | CFile::typeBinary))
//		{
//			//POSITION posi = DataList.GetHeadPosition();
//			int nReadBytes = 0;//从文件中读到的总字节数
//			File.SeekToBegin();
//
//			while (1)
//			{
//				InfoData data;
//				InfoData* pdata = &data;
//				int nRet = File.Read((InfoData*)pdata, 32);
//				nReadBytes += nRet;
//
//				AddInfo(data);
//				//DataList.GetNext(posi);
//				delete pdata;
//				if (nRet < sizeof(pdata))
//					break;
//			}
//			File.Close();
//		}
//		else
//		{
//			FileMissing FMDlg;
//			FMDlg.DoModal();
//		}
//			
//	}
//
//public:
//	void AddInfo(InfoData& data)
//	{
//		DataList.AddTail(data);
//	};
//	void DelInfo(InfoData& data)
//	{
//		POSITION posi = DataList.GetHeadPosition();
//		for (; posi != NULL; DataList.GetNext(posi))
//			if (DataList.GetAt(posi) == data)
//				DataList.RemoveAt(posi);
//	};
//	DATALIST_TYPE* GetDatalist() { return &DataList; }
//};

typedef CList<InfoData, InfoData&> DATALIST_TYPE;
class BusData
{
protected:

	DATALIST_TYPE DataList;
	//fstream File;
	CString Filename;
	int n = 5;//手动录入车次总数

public:
	BusData(void)
	{
		Filename = "";
	};
	BusData(CString fileName)
	{
		Filename = fileName;
	}
	~BusData(void)
	{
		DataList.RemoveAll();
	};
public:
	void Read()
	{
		fstream File;
		File.open(Filename, ios::in);
		//找不到文件时：
		if (File.fail())
		{
			FileMissing FMDlg;
			FMDlg.DoModal();
			exit(1);
		}
		//找到文件：
		int i = 0;
		while (!File.eof())
		//for(int i=1;i<=n;i++)
		{
			InfoData data;
			File >> data.no;
			////防止第一行是空的被读取进去：
			/*if (File.eof())
			{
				File.close();
				break;
			}*/
			File >> data.hour;
			File >> data.minute;
			File >> data.Starting_station;
			File >> data.Last_station;
			File >> data.time;
			File >> data.fare;
			File >> data.maxPas;
			File >> data.sold;
			i++;

			if (data.no == NULL)
				break;
			DataList.AddTail(data);
		}
		n = i;
		File.close();
	}

	void WriteExample()
	{
		fstream File;
		File.open(Filename, ios::out);
		File << "bus1 0 50 Nanjing Chengdu 600 570 1000 100 bus2 1 25 Nanjing Shanghai 240 300 900 90 bus3 7 10 Xi'an Bangbu 270 300 850 70 bus4 13 30 Chongqing Beijing 500 530 1200 400 bus5 17 05 Guangzhou Shenzhen 300 250 900 500";
		File.close();
	}

	void Write(InfoData data)
	{
		fstream File;
		File.open(Filename, ios::out);
		//写入：
		File  << data.no;
		File  << data.hour;
		File  << data.minute;
		File  << data.Starting_station;
		File  << data.Last_station;
		File  << data.time;
		File  << data.fare;
		File  << data.maxPas;
		File  << data.sold;
		File.close();
	}
public:
	POSITION Find(CString no)
	{
		if (!DataList.IsEmpty())
		{
			POSITION posi = DataList.GetHeadPosition();
			InfoData temp;
			/*do
			{
				InfoDataCStr tempcstr(temp);
				if (no == tempcstr.no)
					return posi;
				else
					temp = DataList.GetNext(posi);
			} while (posi != NULL);*/
			for (int i = 0; i < n; i++)
			{
				temp = DataList.GetAt(posi);
				InfoDataCStr tempcstr(temp);
				if (no == tempcstr.no)
					return posi;
				else
					DataList.GetNext(posi);
			}
			return false;
		}
	}

	bool FindTrue(CString cstr)
	{
		if (!DataList.IsEmpty())
		{
			POSITION posi = DataList.GetHeadPosition();
			InfoData temp;

			for (int i = 0; i < n; i++)
			{
				temp = DataList.GetAt(posi);
				InfoDataCStr tempcstr(temp);
				if (cstr == tempcstr.Starting_station || cstr == tempcstr.Last_station || cstr == tempcstr.no)
				{
					return true;
				}
				DataList.GetNext(posi);
			}
		}
		return false;
	}

	int Find(CString cstr,POSITION* storage)
	{
		int count = 0;
		if (!DataList.IsEmpty())
		{
			POSITION posi = DataList.GetHeadPosition();
			/*for (; posi != NULL; temp = DataList.GetNext(posi))
			{
				InfoDataCStr tempcstr(temp);
				if (cstr == tempcstr.Starting_station || cstr == tempcstr.Last_station)
				{
					storage[i] = posi;
					i++;
					count++;
				}
			}*/
			for (int i = 0; i < n; i++)
			{
				InfoData temp = DataList.GetAt(posi);
				InfoDataCStr tempcstr(temp);
				if (cstr == tempcstr.Starting_station || cstr == tempcstr.Last_station || cstr == tempcstr.no)
				{
					storage[count++] = posi;
				}
				DataList.GetNext(posi);
			}
			return count;
		}
		return count;
	}

	//bool timeCheck(int time,CString SS)//时间冲突
	//{
	//	if (!DataList.IsEmpty())
	//	{
	//		if (Find(SS))
	//		{
	//			POSITION posi = Find(SS);
	//			InfoData temp = DataList.GetAt(posi);
	//			if (fabs(temp.hour * 60 + temp.minute - time) <= 15)
	//			{
	//				return true;
	//			}
	//		}
	//	}
	//	return false;
	//}

	void AddInfo(InfoData& data)
	{
		InfoDataCStr cstr(data);
		if (Find(cstr.no))
		{
			AfxMessageBox(TEXT("录入失败！车次已存在！"));
		}
		else if (data.time <= 0)
		{
			AfxMessageBox(TEXT("录入失败！请核验行车时间！"));
		}
		else if (data.maxPas < data.sold)
		{
			AfxMessageBox(TEXT("录入失败！请核验已售票数！"));
		}
		else if (data.hour >= 24 || data.hour < 0)
		{
			AfxMessageBox(TEXT("录入失败！发车时间错误（小时）"));
		}
		else if (data.minute >= 60 || data.minute < 0)
		{
			AfxMessageBox(TEXT("录入失败！发车时间错误（分钟）"));
		}
		/*if (timeCheck(data.hour*60+data.minute,cstr.Starting_station))
		{
			AfxMessageBox(TEXT("录入失败！该始发站存在冲突车次！"));
			return;
		}*/
		else
		{
			DataList.AddTail(data);
			n++;
			AfxMessageBox(TEXT("录入成功！"));
		}
		//Write(data);
	};
	/*void DelInfo(InfoData& data)
	{
		if(!DataList.IsEmpty())
		{
			POSITION posi = DataList.GetHeadPosition();
			for (; posi != NULL; DataList.GetNext(posi))
				if (strcmp(DataList.GetAt(posi).no, data.no) == 0)
					DataList.RemoveAt(posi);
		}
	};*/
	void DelInfo(CString no)
	{
		if (Find(no))
		{
			DataList.RemoveAt(Find(no));
			n--;
		}
		
	};
	DATALIST_TYPE* GetDatalist() { return &DataList; }
	void Addsold(POSITION posi)
	{
		DataList.GetAt(posi).sold++;
	}
};

extern BusData g_dataFile;//general