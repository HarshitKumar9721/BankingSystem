#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<fstream.h>
#include<process.h>

class Account
{
	char Account_power;
	protected:

	char name[40];
	char address[70];
	char email[30];

	char phone[11];
	char acc_type;
	char aadhar[15];

	char* fname;

	int bool;
	long account_no;
	long pin;
	double balance;

	public :
	Account();

};

Account :: Account()
{
	name[0] ='\0';
	phone[0]='\0';
	address[0]='\0';
	email[0]='\0';
	pin = 0;
	balance = 0.0;
	bool = 0;
	account_no = 0;


}
class New_Account : public Account
{
	fstream file;
	public:

	New_Account();

	char* getaadhar(){return aadhar;}
	//char* getaccount_no();


	int check_details();

	void accept_details();
	void generate();
	void sort();
	void store_details();
	void show_details();
};
New_Account :: New_Account()
{
	file.open("Bank/aadhar.dat",ios :: binary | ios :: out |ios :: ate);
	if(!file)
	{
		cout << "Unable to open file " ;
		exit(0);
	}
	file.close();
}

void New_Account :: accept_details()
{
	acc_creation:

	Account();
	clrscr();

	cout << "Enter your name : ";
	gets(name);
	cout << "Enter your phone number : ";
	gets(phone);
	cout << "Enter aadhar : ";
	gets(aadhar);
	cout << "Email : ";
	gets(email);
	cout << "Address : ";
	gets(address);
	type:
	cout <<"Account type [Savings(S) / Current(C)]: ";
	cin >> acc_type;
	acc_type = tolower(acc_type);
	if(acc_type != 's' && acc_type != 'c')
	{
		cout<<"Invalid input. Please re-enter the account type."<<endl;
		goto type;
	}
	bal:
	cout << "Enter initial balance (minimum 2000) : ";
	cin >> balance;
	if(balance < 2000)
	{
		cout<<"Initial amount entered too low. Please re-enter the balance."<<endl;
		goto bal;
	}
	bool = 0;
	bool = check_details();
	if(!bool)
	{
		generate();
		store_details();
		file.open("Bank/aadhar.dat",ios::out | ios::app |ios::binary);
		file.write((char*)aadhar,sizeof(aadhar));
		file.close();
	}
	else
	{
		cout<<"Aadhar card already exists in an account."<<endl;
		cout<<"Please remake the account with valid details."<<endl;
		cout<<endl<<"Press any key to continue...."<<endl;
		getch();
		goto acc_creation;
	}
}

int New_Account :: check_details()
{
	file.open("Bank/aadhar.dat",ios::in | ios::binary);
	file.seekg(0L,ios::beg);
	char ad[15];
	while(file.read((char*)ad,sizeof(ad)))
	{
		if(!strcmp(aadhar,ad))
		{
			return 1;
		}
	}
	file.clear();
	file.close();
	return 0;
}
void New_Account :: generate()
{
	srand(time(0));
	account_no = rand() % 888888 + 100000;
	pin = rand() % 8888 + 1000;
	ltoa(account_no,fname,10);
	fname = strcat("Bank/", fname);
	fname = strcat(fname,".dat");

}
void New_Account :: store_details()
{
	fstream fout(fname, ios::out | ios::app | ios::binary);
	fout.write((char*)this,sizeof(*this));
	fout.close();

}
void New_Account :: show_details()
{
	New_Account ac;
	file.open(fname,ios::in | ios::binary);
	file.read((char*)&ac,sizeof(ac));
	cout << endl;
	cout << "Name : "<< ac.name <<endl;
	cout << "Account number : "<< ac.account_no <<endl;
	cout << "Pin : "<< ac.pin <<endl;
	cout << "Phone Number : " << ac.phone<<endl;
	cout << "Aadhar : " << ac.aadhar<<endl;
	cout << "Email : "<< ac.email<<endl;
	cout << "Address : " << ac.address<<endl;
	cout << "Account type : ";
	if(ac.acc_type == 's')
		cout<<"Savings"<<endl;
	if(ac.acc_type == 'c')
	cout<<"Current"<<endl;
	cout << "Balance : Rs." << ac.balance <<endl<<endl;
}

class Existing_Account : public Account
{
	fstream file;

	public:
	Existing_Account(){}

	void accept();
	void withdraw();
	void deposit();
	void Close_Acc();
	void Modify_details();
	void Transfer();
};

void Existing_Account :: accept()
{
	cout <<"Enter your Account number : ";
	gets(fname);

	fname = strcat(fname,".dat");
	file.open(fname, ios::in | ios::ate | ios::out | ios::binary);
}

void Existing_Account :: withdraw()
{
	double amt_withdraw = 0.0;

	Existing_Account e;
	cout<<"Enter the amount you want to withdraw: ";
	cin>>amt_withdraw;

	file.seekg(0L,ios::beg);

	file.read((char*)&e,sizeof(e));
	if(amt_withdraw < e.balance - 500)
	{
		e.balance -= amt_withdraw;
		cout<<"Amount withdrawn. New balance -> Rs."<<e.balance<<endl;
		file.seekp(ios::beg);
		file.write((char*)&e,sizeof(e));
	}
	else
		cout << " You can\'t just empty yaw count bitch";

	file.close();
}

void Existing_Account :: deposit()
{
	Existing_Account e;

	double amt_deposit = 0;

	cout << "Enter the amount you want to deposit: ";
	cin >> amt_deposit;

	file.seekg(0L,ios::beg);
	file.read((char*)&e, sizeof(e));

	e.balance += amt_deposit;
	cout << "Amount deposited! New balance: Rs."<<e.balance<<endl;

	file.seekp(0L,ios::beg);
	file.write((char*)&e, sizeof(e));

	file.close();
}
void Existing_Account :: Modify_details()
{
	Existing_Account e;
	int choice;
	char phone[11];
	char email[30];
	char address[70];
	char reply = 'Y';
	file.seekg(0L,ios::beg);
	file.read((char*)&e, sizeof(e));
	cout<<"Welcome to modification menu,"<<endl;
	while(reply == 'Y' || reply == 'y')
	{
		clrscr();
		cout<<"Please choose an option below to modify."<<endl;
		cout<<"1. Phone Number"<<endl;
		cout<<"2. Email Address"<<endl;
		cout<<"3. Address"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1: clrscr();
				cout << "Modifying Phone number. Please enter the new number: ";
				gets(phone);
				strcpy(e.phone, phone);
				cout<<"Phone number modified. Do you want to modify anything else? [Y/N]"<<endl;
				file.seekp(0L,ios::beg);
				file.write((char*)&e, sizeof(e));
				cin>>reply;
				break;
			case 2: clrscr();
				cout<<"Modifying email address. Please enter the new email address: ";
				gets(email);
				strcpy(e.email, email);
				cout<<"Email address modified. Do you want to modify anything else? [Y/N]"<<endl;
				file.seekp(0L,ios::beg);
				file.write((char*)&e, sizeof(e));
				cin>>reply;
				break;
			case 3: clrscr();
				cout<<"Modifying address. Please enter the new address: ";
				gets(address);
				strcpy(e.address, address);
				cout<<"Address modified. Do you want to modify anything else? [Y/N]"<<endl;
				file.seekp(0L,ios::beg);
				file.write((char*)&e, sizeof(e));
				cin>>reply;
				break;
			default: clrscr();
				cout<<"Invalid choice. Do you wish to try again? [Y/N]";
				cin>>reply;
		}
	}
	clrscr();
}
/*void Existing_Account :: Close_Acc()
{
	char opt = 'n';
	cout << "U sure nigga u wanna close your account : ";
	cin >> opt;
	opt = tolower(opt);
	if(opt == 'y')
	{
		fstream tfile;
		tfile.open("Bank/aadhar.dat",ios::in | ios::out | ios::ate | ios::binary);
		while(tfile.read((char*)ad,sizeof(ad)))
		{
			if(!strcmp(aadhar,ad))
		}
		remove(fname);
		cout << "good bye fagot ";
	}
} */

void main()
{
	clrscr();
	New_Account na;
	Existing_Account e;
	na.accept_details();
	//e.accept();
	na.show_details();
	//e.Close_Acc();
	//e.Modify_details();
	getch();
}
/*void New_Account::sort()
{
	New_Account o1,o2;
	fstream f;
	f.open("Bank.dat",ios::in | ios::out | ios::ate |ios::binary);
	long size = f.tellg()/sizeof(o1);
	long sizeo =sizeof(o1);
	f.seekg(0,ios::beg);
	for(int i=0;i<=size;i++)
	{
		for(int j=i+1;j<=size-1;j++)
		{
			f.read((char*)&o1,sizeof(o1));
			f.read((char*)&o2,sizeof(o2));
			if(o1.balance > o2.balance)
			{
				f.seekp(-2 * sizeo,ios::cur);
				f.write((char*)&o2,sizeof(o2));
				f.write((char*)&o1,sizeof(o1));
				//f.seekp(-sizeo,ios::cur);
			}
			f.seekg(-sizeo,ios::cur);
		}
	}
	f.close();

}

void New_Account :: show_details()
{
	fstream fin;
	fin.open("Bank.dat",ios::in | ios::binary);
	New_Account ac;
	fin.seekg(0L,ios::beg);
	while(!fin.eof())
	{
		clrscr();
		for(int i=0;i<2;i++)
		{
			fin.read((char*)&ac,sizeof(ac));
			if(fin.eof())
				break;
			cout<<endl;
			cout << "Name : "<< ac.name <<endl;
			cout << "Account number : "<< ac.account_no <<endl;
			cout << "Pin : "<< ac.pin <<endl;
			cout << "Phone Number : " << ac.phone<<endl;
			cout << "Enter aadhar : " << ac.aadhar<<endl;
			cout << "Email : "<< ac.email<<endl;
			cout << "Address : " << ac.address<<endl;
			cout << "Account type : ";
			if(ac.acc_type == 's')
				cout<<"Savings"<<endl;
			if(ac.acc_type == 'c')
				cout<<"Current"<<endl;
			cout << "Balance : Rs." << ac.balance <<endl<<endl;
		}
		if(fin.eof())
			break;
		cout << "Press any key to continue ";
		getch();
	}
	fin.clear();
	fin.close();
}*/
