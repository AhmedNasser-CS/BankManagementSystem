#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<limits>
using namespace std;

const string ClientsFile = "Clients.txt";

enum enMainMenue { ShowClients = 1, AddClient = 2, DeleteClient, UpDataClient, FindClient,Exit };

struct stData
{
	string AccountID = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0.0;
	bool MarkForDelete = false;
};

string ReadString(string str)
{
	string S1;
	cout << str;
	getline(cin>>ws, S1);
	return S1;
}

vector<string> ExtractDataFromFile(string FileName)
{
	fstream Myfile;
	vector<string> Lines;
	string line;
	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		while (getline(Myfile, line))
		{
			Lines.push_back(line);
		}
		Myfile.close();
	}
	return Lines;
}

void AddDataToFile(string FileName, string Data)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << Data << endl;
		Myfile.close();
	}
}

string ConvertRecordToLine(stData& Client, string Separator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountID + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}


void SaveData(string FileName, vector<stData>& Clients)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out);
	string DataLine;
	if (Myfile.is_open())
	{
		for (stData& C : Clients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				Myfile << DataLine << endl;
			}
		}
		Myfile.close();
	}
}


vector<int> SplitterPosition(string line, string splitter = "#//#")
{
	vector<int> Positions;

	for (int i = 0; i < line.length(); i++)
	{
		if (line.substr(i, splitter.length()) == splitter)
		{
			Positions.push_back(i);
		}
	}

	return Positions;
}

vector<string> Splitter(string line, string splitter = "#//#")
{
	vector<int> Positions = SplitterPosition(line, splitter);

	string word = "";
	int positionIndex = 0;
	vector<string> Words;

	for (int i = 0; i < line.length(); i++)
	{
		if (positionIndex < Positions.size() && i == Positions[positionIndex])
		{
			Words.push_back(word);
			word = "";

			i += splitter.length() - 1;
			positionIndex++;
		}
		else
		{
			word += line[i];
		}
	}

	Words.push_back(word);

	return Words;
}

stData TurnLineToRecord(string line, string Delim = "#//#")
{
	stData Client;
	vector<string> Split = Splitter(line, Delim);

	Client.AccountID = Split[0];
	Client.PinCode = Split[1];
	Client.Name = Split[2];
	Client.Phone = Split[3];
	Client.AccountBalance = stod(Split[4]);

	return Client;
}


vector<stData> TransformToStruct(vector<string>& Lines, string Delim = "#//#")
{
	vector<stData> Clients;
	for (int i = 0; i < Lines.size(); i++)
	{
		Clients.push_back(TurnLineToRecord(Lines[i], Delim));
	}
	return Clients;
}

void PrintClientData(stData& Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccount Number: " << Client.AccountID;
	cout << "\nPin Code: " << Client.PinCode;
	cout << "\nName: " << Client.Name;
	cout << "\nPhone: " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}



void PrintClientRecordLine(stData Client)
{
	cout << "|" << setw(16) << left << Client.AccountID;
	cout << "|" << setw(11) << left << Client.PinCode;
	cout << "|" << setw(41) << left << Client.Name;
	cout << "|" << setw(13) << left << Client.Phone;
	cout << "|" << setw(13) << left << Client.AccountBalance;
}


void PrintAllRecords(vector<stData>& vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!\n";
	}
	else
	{
		for (stData& Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}


bool findClient(vector<stData>& Clients, stData& client, string AccountID)
{
	for (stData& C : Clients)
	{
		if (C.AccountID == AccountID)
		{
			client = C;
			return true;
		}
	}
	return false;
}

void ReadNewClient(stData& userData)
{
	cout << "Enter Account Number: ";
	getline(cin >> ws, userData.AccountID);
	cout << "Enter PinCode: ";
	getline(cin, userData.PinCode);
	cout << "Enter Name: ";
	getline(cin, userData.Name);
	cout << "Enter Phone: ";
	getline(cin, userData.Phone);
	cout << "Enter AccountBalance: ";
	cin >> userData.AccountBalance;
}

void AddNewClient(vector<stData>& Clients)
{
	stData NewClient ,Client;
	ReadNewClient(NewClient);

	if (findClient(Clients, Client,NewClient.AccountID ))
	{
		cout << "This Account ID (" << NewClient.AccountID << ") already exist.";
	}
	else
	{
		AddDataToFile(ClientsFile, ConvertRecordToLine(NewClient));
		Clients.push_back(NewClient);
		cout << "\nClient Added Successfully.";
	}
}


void updateData(stData& Client)
{
	cout << "\n\nEnter PinCode: ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name: ";
	getline(cin, Client.Name);
	cout << "Enter Phone: ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance: ";
	cin >> Client.AccountBalance;
}

void UpDateClientAccount(vector<stData>& Clients, string AccountID)
{
	stData Client;
	char Answer = 'N';

	if (findClient(Clients, Client, AccountID))
	{
		PrintClientData(Client);
		cout << "\n\nAre You Sure You want to update this Data(y/n): ";

		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (stData& C : Clients)
			{
				if (C.AccountID == AccountID)
				{
					updateData(C);
					break;
				}
			}
			SaveData(ClientsFile, Clients);
			cout << "\nClient Updated Successfully.\n" << endl;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountID << ") is Not Found!";
	}
}

void DeleteClientByAccountNumber(string AccountID, vector<stData>& vClients)
{
	stData Client;
	char Answer = 'n';
	if (findClient(vClients, Client, AccountID))
	{
		PrintClientData(Client);
		cout << "\n\nAre you sure you want delete this client (y/n)? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stData& C : vClients)
			{
				if (C.AccountID == AccountID)
				{
					C.MarkForDelete = true;
				}
			}
			SaveData(ClientsFile, vClients);
			cout << "\n\nClient Deleted Successfully.";
		}
		else
		{
			cout << "Okay Nothing changed.";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountID << ") is Not Found!";
	}
}

int ReadNumber(int from, int to,string message)
{
	int Number;
	do
	{
		cout << message;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Number, Enter a valid one:" << endl;
			cin >> Number;
		}

	} while (Number > to || Number < from);
	
	return Number;
}

void MainMenuScreen()
{
	cout << "\n\n";
	cout << "============================================================\n";
	cout << "                    BANK MANAGEMENT SYSTEM\n";
	cout << "============================================================\n";
	cout << "\n";
	cout << "                    [1] Show Client List\n";
	cout << "                    [2] Add New Client\n";
	cout << "                    [3] Delete Client\n";
	cout << "                    [4] Update Client\n";
	cout << "                    [5] Find Client\n";
	cout << "                    [6] Exit\n";
	cout << "\n";
	cout << "============================================================\n";
}

void MainMenuSelection(vector<stData> &Clients,stData &Client,int Choose)
{
	enMainMenue MM = (enMainMenue)Choose;
	string AccountID;
	switch (MM)
	{

	case ShowClients:
		PrintAllRecords(Clients);
		break;

	case AddClient:
		AddNewClient(Clients);
		break;

	case DeleteClient:
		AccountID = ReadString("Enter Your Account ID: ");
		DeleteClientByAccountNumber(AccountID, Clients);
		break;

	case UpDataClient:
		AccountID = ReadString("Enter Your Account ID: ");
		UpDateClientAccount(Clients, AccountID);
		break;

	case FindClient:
		AccountID = ReadString("Enter Your Account ID: ");
		if(findClient(Clients, Client, AccountID))
		{
			PrintClientData(Client);
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountID << ") is Not Found!";
		}
		break;

	default:
		return;
	}
}

void ShowEndScreen()
{
	cout << "\n=============================================\n";
	cout << "\tThank You For Using Our System";
	cout << "\n=============================================\n";
}

void BankSystem()
{
	int choice;
	do
	{
		system("cls");
		vector<string> Lines = ExtractDataFromFile(ClientsFile);
		vector<stData> Clients = TransformToStruct(Lines);
		stData Client;
		MainMenuScreen();
		choice = ReadNumber(1, 6, "Choose what do you want to do? [1 to 6]: ");
		MainMenuSelection(Clients, Client, choice);

		if(choice!=Exit)
		{
			cout << "\n\nPress any key to return to Main Menu...";
			system("pause>0");
		}
	} while (choice != Exit);
	ShowEndScreen();
}

int main()
{
	BankSystem();
	return 0;
}