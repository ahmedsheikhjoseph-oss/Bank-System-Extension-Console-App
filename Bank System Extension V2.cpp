#pragma warning(disable : 26812)  // Disable Error of enum Class 
#pragma warning(disable : 4267)  // Disable Error of enum Class 
#pragma warning(disable : 4996)  // Disable Error of enum Class 

/*
Project: Bank Management System Extension (V2) .. Transactions Menu (Deposit, Withdraw, Total Balances)
Course: Algorithms & Problem Solving Level 3
Concept: Advanced File Handling, Data Persistence, and CRUD Operations.
Developed By: [ِAhmed Sheikh Al-deen]
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;
const string ClientsFileName = "Clients.txt";

void ShowMainMenue();
void ShowTransactionsMenue();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0.00;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable  

	// use find() function to get the position of the delimiters  
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word   
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}

	return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double
	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}

		MyFile.close();

	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber); // Usage of std::ws will extract allthe whitespace character

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\033[31m\nClient with [" << Client.AccountNumber << "] already exists,\033[0m";
		cout << " Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

// UI/UX: Displays all clients in a well-formatted table using iomanip
void ShowAllClientsScreen()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\033[33m" << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s)." << "\033[0m";
	cout << "\n___________________________________________";
	cout << "________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________";
	cout << "________________________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\033[33m" << "\t\t\t\tNo Clients Available In the System!" << "\033[0m";
	else

		for (sClient Client : vClients)
		{

			PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintClientRecordBalanceLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalances()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\033[38;5;208m" << "\n\t\t\t\t\t Balances List (" << vClients.size() << ") Client(s)." << "\033[0m";
	cout << "\n___________________________________________";
	cout << "________________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n___________________________________________";
	cout << "________________________________________________________\n" << endl;

	double TotalBalance = 0;

	if (vClients.size() == 0)
		cout << "\033[33m" << "\t\t\t\tNo Clients Available In the System!" << "\033[0m";
	else

		for (sClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalance += Client.AccountBalance;

			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "\033[38;2;152;251;152m" << "\t\t\t\t\tTotal Balance = " << TotalBalance << "\033[0m";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}

	}
	return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

	for (sClient& C : vClients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}

	}

	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{

			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.  
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}

		}

		MyFile.close();
	}

	return vClients;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		//system("cls");
		cout << "Adding New Client:\n\n";

		AddNewClient();

		cout << "\033[32m" << "\nClient Added Successfully, " << "\033[0m" << "do you want to add more clients ? Y / N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients 
			vClients = LoadCleintsDataFromFile(ClientsFileName);

			cout << "\033[32m" << "\n\nClient Deleted Successfully." << "\033[0m";
			return true;
		}

	}
	else
	{
		cout << "\033[31m" << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n" << "\033[0m";
		return false;
	}

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{

		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\033[32m" << "\n\nClient Updated Successfully." << "\033[0m";
			return true;
		}

	}
	else
	{
		cout << "\033[31m" << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n" << "\033[0m";
		return false;
	}
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{

		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;

				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\033[32m" << "\n\nDone Successfully." << "\033[0m" << "The New Balance Is: " << C.AccountBalance;
				return true;
			}
		}


		return false;
	}
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;

}

void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[33m" << "\tAdd New Clients Screen" << "\033[0m";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}

void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[33m" << "\tDelete Client Screen\n" << "\033[0m";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[33m" << "\tUpdate Client Info Screen\n" << "\033[0m";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[33m" << "\tFind Client Screen" << "\033[0m";
	cout << "\n-----------------------------------\n";

	sClient Client;
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number\033[33m [" << AccountNumber << "] \033[0m" << "\033[31m" << "Not Found!\n" << "\033[0m";

}

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[33m" << "\tProgram Ends :-)" << "\033[0m";
	cout << "\n-----------------------------------\n";
}

void ShowDepositScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[38;5;208m" << "\tDeposit Screen" << "\033[0m";
	cout << "\n-----------------------------------\n";

	sClient Client;
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with\033[33m [" << AccountNumber << "] \033[0m" << "\033[31m" << "does not exist.\n" << "\033[0m";

		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);


}

void ShowWithDrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\033[38;5;208m" << "\tWithdraw Screen" << "\033[0m";
	cout << "\n-----------------------------------\n";

	sClient Client;
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with\033[33m [" << AccountNumber << "] \033[0m" << "\033[31m" << "does not exist.\n" << "\033[0m";

		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	//Validate that the amount does not exceeds the balance
	while (Amount > Client.AccountBalance)
	{
		cout << "\n\033[31mAmount Exceeds The Balance.\033[0m " << "you can withdraw up to : " << Client.AccountBalance;
		cout << "\nPlease enter another amount? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{
	ShowTotalBalances();
}

enum enTransactionsMenueOptions
{
	eDeposit = 1, eWithdraw = 2,
	eShowTotalBalances = 3, eShowMainMenue = 4
};
enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionsMenue = 6, eExit = 7
};

void GoBackToMainMenue()
{
	cout << "\033[38;5;226m" << "\n\nPress any key to go back to Main Menue..." << "\033[0m";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactionsMenue()
{
	cout << "\033[38;5;226m" << "\n\nPress any key to go back to Transactions Menue..." << "\033[0m";
	system("pause>0");
	ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
{
	short Choice = 0;
	do
	{
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 4);

	return Choice;
}
void PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionOption)
{
	switch (TransactionOption)
	{
	case enTransactionsMenueOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;
	}

	case enTransactionsMenueOptions::eWithdraw:
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::eShowTotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::eShowMainMenue:
		ShowMainMenue();
		break;
	}
}
string GetCurrentTimestamp() {
	time_t now = time(0);
	char buf[80];
	struct tm tstruct;
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);
	return buf;
}

// UI/UX: Displays all clients in a well-formatted table using iomanip
void ShowTransactionsMenue()
{
	system("cls");
	cout << "\033[1;38;5;51;48;5m" << GetCurrentTimestamp() << " \033[0m\n\n";
	cout << "\033[1;38;5;51;48;5;244m" << "=============================================" << "\033[0m" << endl;
	cout << "\033[1;38;5;51;48;5;244m" << "              Transactions Menu Screen       " << "\033[0m" << endl;
	cout << "\033[1;38;5;51;48;5;244m" << "=============================================" << "\033[0m" << endl;
	cout << "\033[1;38;5;51;48;5;244m" << "       [1] Deposit.                          \n";
	cout << "\033[1;38;5;51;48;5;244m" << "       [2] Withdraw.                         \n";
	cout << "\033[1;38;5;51;48;5;244m" << "       [3] Total Balances.                   \n";
	cout << "\033[1;38;5;51;48;5;244m" << "       [4] Main Menue.                       \n";
	cout << "\033[1;38;5;51;48;5;244m" << "=============================================" << "\033[0m\n\n" << endl;

	PerfromTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{

	short Choice = 0;

	do
	{
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 7);

	return Choice;
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
	{
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eShowTransactionsMenue:
		system("cls");
		ShowTransactionsMenue();
		break;

	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

// UI/UX: Displays all clients in a well-formatted table using iomanip
void ShowMainMenue()
{
	system("cls");
	cout << "\033[1;38;5;226;48;5m" << GetCurrentTimestamp() << " \033[0m\n\n";
	cout << "\033[1;38;5;226;48;5;244m" << "===========================================" << "\033[0m" << endl;
	cout << "\033[1;38;5;226;48;5;244m" << "              Main Menu Screen             " << "\033[0m" << endl;
	cout << "\033[1;38;5;226;48;5;244m" << "===========================================" << "\033[0m" << endl;
	cout << "\033[1;38;5;226;48;5;244m" << "       [1] Show Client List.               \n";
	cout << "\033[1;38;5;226;48;5;244m" << "       [2] Add New Client.                 \n";
	cout << "\033[1;38;5;226;48;5;244m" << "       [3] Delete Client.                  \n";
	cout << "\033[1;38;5;226;48;5;244m" << "       [4] Update Client Info.             \n";
	cout << "\033[1;38;5;226;48;5;244m" << "       [5] Find Client.                    \n";
	cout << "\033[1;38;5;226;48;5;244m" << "       [6] Transactions.                   \n";
	cout << "\033[1;38;5;226;48;5;244m" << "       [7] Exit.                           \n";
	cout << "\033[1;38;5;226;48;5;244m" << "===========================================" << "\033[0m\n\n" << endl;

	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}



int main()
{
	ShowMainMenue();

	system("pause>0");
	return 0;
}
