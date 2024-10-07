#pragma once

#include"BusData.h"

class PassengerData
{
protected:

	DATALIST_TYPE DataList;
	//fstream File;
	CString Filename;
	int n = 2;//已购数

public:
	PassengerData(void)
	{
		Filename = "";
	};
	PassengerData(CString fileName)
	{
		Filename = fileName;
	}
	~PassengerData(void)
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
		while (!File.eof())
		//for (int i = 1; i <= n; i++)
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

			if (data.no == NULL)
				break;
			DataList.AddTail(data);
		}
		File.close();
	}

	void WriteExample()
	{
		fstream File;
		File.open(Filename, ios::out);
		File << "bus1 0 50 Nanjing Chengdu 600 570 1000 100 bus3 7 10 Xi'an Bangbu 270 300 850 70";
		File.close();
	}

	void Write(InfoData data)
	{
		fstream File;
		File.open(Filename, ios::out);
		//写入：
		File << data.no;
		File << data.hour;
		File << data.minute;
		File << data.Starting_station;
		File << data.Last_station;
		File << data.time;
		File << data.fare;
		File << data.maxPas;
		File << data.sold;
		File.close();
	}
public:
	POSITION Find(CString no)
	{
		if (!DataList.IsEmpty())
		{
			POSITION posi = DataList.GetHeadPosition();
			InfoData temp = DataList.GetAt(posi);
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

	void AddInfo(InfoData& data)
	{
		DataList.AddTail(data);
		n++;
		//Write(data);
	};
	void AddInfo(CString NO)
	{
		POSITION tempposi = Find(NO);
		InfoData tempdata = DataList.GetAt(tempposi);
		DataList.AddTail(tempdata);
		n++;
		//Write(data);
	};
	void DelInfo(CString no)
	{
		if (Find(no))
		{
			DataList.RemoveAt(Find(no));
			n--;
		}
	};
	DATALIST_TYPE* GetDatalist() { return &DataList; }
};

extern PassengerData p_dataFile;