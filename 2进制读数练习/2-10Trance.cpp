#define _CRT_SECURE_NO_WARNINGS
#include"iomanip"
#include"iostream"
using namespace std;


int rand4Digit()
{
	return rand() % 16;
}

int rand8Digit()
{
	return rand() % 128;
}

int main()
{
	cout << "\n\nWelcome to 2-10 conversion exercise!\n\n" << endl;
loop0:	cout << "cin your choice:\n(1) 4 digits conversion;\n(2) 8 digits conversion" << endl;
	int choice;
	cin >> choice;
	if (choice == 1 || choice == 2)
		;
	else
	{
		cout << "invalid choice!" << endl;
		goto loop0;
	}
	system("cls");

	srand(time(0));
	int answer;
	int recordAn;
	int wrongState = 0;
	while (1)
	{
		int question;
		if (choice == 1)
		{
			cout << "4 digits conversion:" << endl;
			if (wrongState == 1)
			{
				cout << "Your last wrong answer should be..." << endl;
				question = recordAn;
				wrongState = 0;
			}
			else
				question = rand4Digit();
			char cQuestion[5] = { 0,0,0,0,0 };
			cout << setw(4) << setfill('0') << _itoa(question, cQuestion, 2) << endl;
		}
		else if(choice==2)
		{
			cout << "8 digits conversion:" << endl;
			int a1 = rand4Digit();
			int a2 = rand4Digit();
			if (wrongState == 1)
			{
				cout << "Your last wrong answer should be..." << endl;
				wrongState = 0;
				a1 = question/16;
				a2 = question % 16;
			}
			else
				question = a1 * 16 + a2;
			char cQuestion1[5] = { 0,0,0,0,0 };
			char cQuestion2[5] = { 0,0,0,0,0 };
			cout << setw(4) << setfill('0') << _itoa(a1, cQuestion1, 2) << " " << setw(4) << setfill('0') << _itoa(a2, cQuestion2, 2) << endl;
		}

		
		
loop:		cout << "Your answer: ";
		cin >> answer;
		if (answer == question)
		{
		/*	cout << "\nCorrect! Tap c to continue...";
			char a;
loop2:			cin >> a;
			if (a == 'c')
				system("cls");
			else
				goto loop2;*/
			system("cls");
			cout << "Correct! Next one..." << endl;
		}
		else if (answer == -1)
		{
			cout << "\nSee u next time!" << endl;
			break;
		}
		else if(answer<question||answer>question)
		{
			recordAn = answer;
			wrongState = 1;
			cout << "\nPlease try again!...\n";
			goto loop;
		}
	}
	return 0;
}