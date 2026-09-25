#pragma once

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

const string ClientsFile = "Clients.txt";

struct stData
{
	string AccountID = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0.0;
	bool MarkForDelete = false;
};

//                                               ---------- File I/O ----------

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

//                                                             ---------- Splitting ----------

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
	if (word != "")
	{
		Words.push_back(word);
	}
	return Words;
}

//                                               ---------- Conversion Functions ----------

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
		Clients.push_back(turnLineToRecord(Lines[i], Delim));
	}
	return Clients;
}

string ConvertRecordToLine(stData& Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountID + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

//                                        ---------- Helper string functions ----------

string LowerAllString(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		S1[i] = tolower(S1[i]);
	}
	return S1;
}

string RemovePunctuation(string str)
{
	string word = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (ispunct(str[i]))
		{
			continue;
		}
		word += str[i];
	}
	return word;
}

//                                              ---------- Read input ----------

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Please enter AccountID: ";
	cin >> AccountNumber;
	return AccountNumber;
}

void ReadNewClient(stData& userData)
{
	cout << "Enter Account Number? ";
	getline(cin >> ws, userData.AccountID);
	cout << "Enter PinCode? ";
	getline(cin, userData.PinCode);
	cout << "Enter Name? ";
	getline(cin, userData.Name);
	cout << "Enter Phone? ";
	getline(cin, userData.Phone);
	cout << "Enter AccountBalance? ";
	cin >> userData.AccountBalance;
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

//                                               ---------- Printing ----------

void PrintClientData(stData& Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountID;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

void PrintClientRecordLine(stData Client)
{
	cout << "|" << setw(15) << left << Client.AccountID;
	cout << "|" << setw(10) << left << Client.PinCode;
	cout << "|" << setw(40) << left << Client.Name;
	cout << "|" << setw(12) << left << Client.Phone;
	cout << "|" << setw(12) << left << Client.AccountBalance;
}

void PrintAllRecords(vector<stData>& vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
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

//                                               ---------- Find ----------

bool findClient(vector<stData>& Clients, stData& client, string AccountID)
{
	for (stData C : Clients)
	{
		if (C.AccountID == AccountID)
		{
			client = C;
			return true;
		}
	}
	return false;
}

//                                                ---------- Add ----------

void AddNewClient()
{
	stData newClient;
	ReadNewClient(newClient);
	AddDataToFile(ClientsFile, ConvertRecordToLine(newClient));
}

void AddClients()
{
	char AddMore = 'N';
	do
	{
		cout << "Adding New Client \n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients (Y/N):  ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

//                                       ---------- Update ----------

void ClientAccount(vector<stData>& Clients, string AccountID)
{
	stData Client;
	char Answer = 'N';

	if (findClient(Clients, Client, AccountID))
	{
		PrintClientData(Client);
		cout << "\n\nAre You Sure You want to update this Data(y/n): ";

		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
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

//                                               ---------- Delete ----------

bool DeleteClientByAccountNumber(string AccountID, vector<stData>& vClients)
{
	stData Client;
	char Answer = 'n';
	if (findClient(vClients, Client, AccountID))
	{
		PrintClientData(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
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
			return true;
		}
		else
		{
			cout << "Okay Nothing changed.";
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountID << ") is Not Found!";
		return false;
	}
}