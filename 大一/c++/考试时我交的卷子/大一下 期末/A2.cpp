#include<iostream>
#include<fstream>
using namespace std;

class CipherMachine;

//类Prime的定义 
class Prime
{
	int number;
	Prime* next;
public:
	//缺省构造函数
	Prime(int num, Prime* next = nullptr)
	{
		this->number = num;
		this->next = next;
	}

	//输出运算符的全局重载  
	friend class CipherMachine;
};


//类CipherMachine的定义 
class CipherMachine
{
	Prime* primes;

public:
	//构造函数，动态分配空间 
	CipherMachine(const int* numArray, int numArraySize)
	{
		// 从numArray数组中读取数据，数组长度为numArraySize
		// 构建长度为 numArraySize 的链表，数据排列方向不作要求
		// 链表首节点的地址存放在primes中，链表中不设置只用于连接，不实际存放数据的节点
		// 请填写代码------------10分-------------------
		primes = new Prime(numArray[0]);
		Prime* head = primes, * pre = primes;
		for (int i = 1; i < numArraySize; i++)
		{
			primes = new Prime(numArray[i]);
			pre->next = primes;
			pre = primes;
		}
		primes = head;
	}

	int Decrypt(long long bigNumber) const
	{
		//请填写代码------------10分-------------------
		//Decrypt函数中，对链表进行遍历，找到能够对 bigNumber 进行质因子分解的数字，
		//若找到了，返回该质数，若找不到，返回 - 1；
		Prime* ptr = primes;
		while (ptr && ptr->next)
		{
			if (bigNumber % ptr->number == 0)
				return ptr->number;
			ptr = ptr->next;
		}
		return -1;
	}


	//析构函数，释放动态分配空间
	~CipherMachine()
	{
		while (primes)
		{
			Prime* temp = primes;
			primes = primes->next;
			delete temp;
		}
	}

};


int main()
{
	//10个大质数
	int primes[] = {
		1000000007, 1000000009, 1000000021, 1000000033,	1000000087,
		1000000093, 1000000097, 1000000103, 1000000123, 1000000181 };
	//构造CipherMachine，
	CipherMachine cm(primes, 10);

	//定义待破解的数字
	long long bigNumber = 1234568064851853299; //待分解的大整数


	//调用Decrypt函数，且在屏幕上以“A = P1 * P2”
	//的形式输出（A、P1、P2替换为具体的数字），
	//请将“A = P1 * P2”的形式（A、P1、P2替换为具体的数字）
	//写入文件“Decrypt_学号.txt”并上传到考试系统。
	//请填写代码------------10分-------------------
	int a=cm.Decrypt(bigNumber);
	cout << bigNumber << " = " << a << " * " << bigNumber / a << endl;


	return 0;
}

//在注解中回答问题（5分）：
// 如果要对10000位的大整数进行质因子分解，每个质因子可能高达5000位，
// 从整数表达上，你有什么好的设想或建议？
//可以