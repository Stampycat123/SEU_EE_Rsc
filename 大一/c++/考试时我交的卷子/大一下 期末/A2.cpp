#include<iostream>
#include<fstream>
using namespace std;

class CipherMachine;

//��Prime�Ķ��� 
class Prime
{
	int number;
	Prime* next;
public:
	//ȱʡ���캯��
	Prime(int num, Prime* next = nullptr)
	{
		this->number = num;
		this->next = next;
	}

	//����������ȫ������  
	friend class CipherMachine;
};


//��CipherMachine�Ķ��� 
class CipherMachine
{
	Prime* primes;

public:
	//���캯������̬����ռ� 
	CipherMachine(const int* numArray, int numArraySize)
	{
		// ��numArray�����ж�ȡ���ݣ����鳤��ΪnumArraySize
		// ��������Ϊ numArraySize �������������з�����Ҫ��
		// �����׽ڵ�ĵ�ַ�����primes�У������в�����ֻ�������ӣ���ʵ�ʴ�����ݵĽڵ�
		// ����д����------------10��-------------------
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
		//����д����------------10��-------------------
		//Decrypt�����У���������б������ҵ��ܹ��� bigNumber ���������ӷֽ�����֣�
		//���ҵ��ˣ����ظ����������Ҳ��������� - 1��
		Prime* ptr = primes;
		while (ptr && ptr->next)
		{
			if (bigNumber % ptr->number == 0)
				return ptr->number;
			ptr = ptr->next;
		}
		return -1;
	}


	//�����������ͷŶ�̬����ռ�
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
	//10��������
	int primes[] = {
		1000000007, 1000000009, 1000000021, 1000000033,	1000000087,
		1000000093, 1000000097, 1000000103, 1000000123, 1000000181 };
	//����CipherMachine��
	CipherMachine cm(primes, 10);

	//������ƽ������
	long long bigNumber = 1234568064851853299; //���ֽ�Ĵ�����


	//����Decrypt������������Ļ���ԡ�A = P1 * P2��
	//����ʽ�����A��P1��P2�滻Ϊ��������֣���
	//�뽫��A = P1 * P2������ʽ��A��P1��P2�滻Ϊ��������֣�
	//д���ļ���Decrypt_ѧ��.txt�����ϴ�������ϵͳ��
	//����д����------------10��-------------------
	int a=cm.Decrypt(bigNumber);
	cout << bigNumber << " = " << a << " * " << bigNumber / a << endl;


	return 0;
}

//��ע���лش����⣨5�֣���
// ���Ҫ��10000λ�Ĵ��������������ӷֽ⣬ÿ�������ӿ��ܸߴ�5000λ��
// ����������ϣ�����ʲô�õ�������飿
//����