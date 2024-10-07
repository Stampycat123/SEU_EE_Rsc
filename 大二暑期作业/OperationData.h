#include"BusData.h"
struct OperationInfoDataCstr
{
	InfoData data;
	CString time, Operation, Operator;

	//¹¹Ôìº¯Êý
	OperationInfoDataCstr()
	{
		data = InfoData();
		time = "NULLTime";
		Operation = "NULLOperation";
		Operator = "NULLOperator";
	}
	OperationInfoDataCstr(InfoData temp, int year, int month, int day, int hour, int minute, int second, CString OTN, CString OTR)
	{
		data = temp;
		time.Format(L"%d-%d-%d %d:%d:%d", year, month, day, hour, minute, second);
		Operation = OTN;
		Operator = OTR;
	}
	OperationInfoDataCstr(int year, int month, int day, int hour, int minute, int second, CString OTN, CString OTR)
	{
		data = InfoData();
		strcpy_s(data.no, "  /  ");
		strcpy_s(data.Starting_station, "  /  ");
		strcpy_s(data.Last_station, "  /  ");
		time.Format(L"%d-%d-%d %d:%d:%d", year, month, day, hour, minute, second);
		Operation = OTN;
		Operator = OTR;
	}
};

typedef CList<OperationInfoDataCstr, OperationInfoDataCstr&> ODATALIST_TYPE;
class OperationData
{
protected:
	ODATALIST_TYPE OperationList;
	int countOP;
	
public:
	OperationData()
	{
		countOP = 0;
	}
	OperationData(int c)
	{
		countOP = c;
	}
	void AddOperation(OperationInfoDataCstr oidc)
	{
		OperationList.AddTail(oidc);
	}
	ODATALIST_TYPE* GetDatalist() { return &OperationList; }
};

extern OperationData op_dataFile;