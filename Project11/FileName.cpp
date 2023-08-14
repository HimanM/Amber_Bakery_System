#include<iostream>
#include<string>		//To include string datatype
#include<fstream>		//To handle text files
#include<utility>		//To make data pairs
#include <iomanip>		//To ser field length
#include <windows.h>	//Change text Color in windows consoles
#include <cctype>		//To Capitalize

using namespace std;

//Functions declaretion
void welcome();
int menu();
void viewBakeryItem();
void manageItemAndPackage();
bool verification();
void readSalesDetails();
void addSalesDetails();
void adminCommands();
void companyDetails();
bool itemAdder();
void readtext();
int getIntInput();



//Login Details
const string USER = "Himan";	//Admin Username
const string PASS = "Himan";	//Admin password
const string USERC = "Amber";	//Cashier Username
const string PASSC = "Amber";	//Cashier Passwd


//Struct and Global var declaration
const int MAX_LIMIT = 100;
struct BakeryProducts {
	string id;
	string name;
	int amount;
}bakeryItems[MAX_LIMIT], beverages[MAX_LIMIT], otherItems[MAX_LIMIT];

struct ReturnValue {
	string name;
	int amount;
};


//Add sales details to sales.txt file
void addToSales(double amount, string details) {
	string line;
	ifstream salesin("sales.txt");
	ofstream sales("sales.txt", ios::app);
	line = "+" + to_string(amount) + " by selling " + details + "\n";
	sales << line;
	cout << "Sales Details Added Successfully\n\n";
}

//Read sales details from sales.txt file
void readSalesDetails() {
	int sort = 1;
	string line, addMore;
	ifstream salesin("sales.txt");

	if (!salesin) {
		cout << "The file does not exist. Add sales details first...\n\nYour Choice: " << endl;
		cout << "Press Enter to continue...\n";
		cin.ignore(10, '\n');
		if (cin.get() == '\n'){
			return;
		}
	}
	else {
		while (true) {
			getline(salesin, line);
			if (line.empty()) {
				break;
			}
			cout <<sort<<". "<< line << endl;
			sort++;
		}
		salesin.close();
		cout << "Press Enter to go back...\n";
		cin.ignore(10, '\n');
		if (cin.get() == '\n'){
			return;
		}
	}
	
}

//User Interface for welcoming
void welcome() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << R"(                                     
   _____         ___.                  __________         __                        
  /  _  \   _____\_ |__   ___________  \______   \_____  |  | __ ___________ ___.__.
 /  /_\  \ /     \| __ \_/ __ \_  __ \  |    |  _/\__  \ |  |/ // __ \_  __ <   |  |
/    |    \  Y Y  \ \_\ \  ___/|  | \/  |    |   \ / __ \|    <\  ___/|  | \/\___  |
\____|__  /__|_|  /___  /\___  >__|     |______  /(____  /__|_ \\___  >__|   / ____|
        \/      \/    \/     \/                \/      \/     \/    \/       \/     )";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	cout << "\n\t\t\tWelcome To Amber Bakery\t\t\t\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//Fucntion to show company details
void companyDetails() {
	welcome();
	cout << "Amber bakery\n\nContact :\n\tEmail: amberbakery@gmail.com\n\tPhone: +4409453453454\n\n";
	cout << "Press Enter to continue...\n";
	cin.ignore(10, '\n'); 
	if (cin.get() == '\n'){
		return;
	}

}

//Function to check Adminlogin credentials
bool verification() {
	string user, pass;
	cout << "Enter User Name:";
	cin >> user;
	cout << "Enter User Password:";
	cin >> pass;
	cout << "\n\n";
	if (user == USER && pass == PASS) {
		return true;
	}
	else {
		return false;
	}
}

//Function to check Cashierslogin credentials
bool cashierVerification() {
	string user, pass;
	cout << "Enter User Name:";
	cin >> user;
	cout << "Enter User Password:";
	cin >> pass;
	cout << "\n\n";
	if (user == USERC && pass == PASSC) {
		return true;
	}
	else {
		return false;
	}
}

//Main menu function
int menu(int selection) {
	welcome();
	cout << "1. View Bakery Items\n2. View Company Details\n3. Admin Login\n4. Cashier Login\n5. Exit\n\n" << endl;
	while (true) {
		cout << "Please enter your selection:";
		if (cin >> selection) {
			cout << "\n\n";
			break; // Valid input, exit the loop
		}
		else {
			cout << "Invalid input. Please enter a valid integer.\n";
			cin.clear();  // Clear the error state
			return -1;
		}
	}

	return selection;
}

//Admins menu function
int adminMenu(int selection) {
	system("cls");
	cout << "Login Success";
	cout << "\n\n";
	cout << "\t\t\tWelcome Admin\t\t\t\n";
	cout << "1. Add Items\n2. View Items\n3. View Sales\n4. Logout\n\n" << endl;
	while(true) {
		cout << "Please enter your selection:";
		if (cin >> selection) {
			cout << "\n\n";
			break; // Valid input, exit the loop
		}
		else {
			cout << "Invalid input. Please enter a valid integer.\n";
			cin.clear();  // Clear the error state
			return -1;
		}
	}

	return selection;
}

//Cashier menu function
int cashierMenu(int selection) {
	system("cls");
	cout << "Login Success";
	cout << "\n\n";
	cout << "\t\t\tWelcome Cashier\t\t\t\n";
	cout << "1. View Items\n2. Make bill\n3. Logout\n\n" << endl;
	while (true) {
		cout << "Please enter your selection:";
		if (cin >> selection) {
			cout << "\n\n";
			break; // Valid input, exit the loop
		}
		else {
			cout << "Invalid input. Please enter a valid integer.\n";
			cin.clear();  // Clear the error state
			return -1;
		}
	}

	return selection;
}

//Search products according to their unique ID
ReturnValue searchProduct(string ItemID, BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[],
	int bakeItemCount, int beverageitemCount, int otherItemCount) {
	ReturnValue parser;
	parser.name = "404";
	parser.amount = 0;
	if (ItemID[0] == 'A') {
		for (int i = 0; i < bakeItemCount; i++) {
			if (bakeryItems[i].id == ItemID) {
				parser.name = bakeryItems[i].name;
				parser.amount = bakeryItems[i].amount;
			}
		}
	}
	else if (ItemID[0] == 'B') {
		for (int i = 0; i < beverageitemCount; i++) {
			if (beverages[i].id == ItemID) {
				parser.name = beverages[i].name;
				parser.amount = beverages[i].amount;
			}
		}
	}
	else {
		for (int i = 0; i < otherItemCount; i++) {
			if (otherItems[i].id == ItemID) {
				parser.name = otherItems[i].name;
				parser.amount = otherItems[i].amount;
			}
		}
	}
	return parser;
}

//Function to make bills
pair<int, pair<string, string>> makeBills(BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[],
	int bakeItemCount, int beverageitemCount, int otherItemCount) {
	ReturnValue itemDetails;
	int quantity;
	int amount, netAmount = 0;
	string itemID, currentBill, finalBill = "", addMore, salesDetails, finalSalesDetails;
	while (true) {
		cout << "Enter the ID of the item (press Enter to go back): ";
		cin.ignore();
		getline(cin, itemID);
		if (itemID.empty()) {
			cout << "Going back to the main menu...\n";
			break;
		}
		itemID[0] = toupper(itemID[0]);
		itemDetails = searchProduct(itemID, bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
		if (itemDetails.name != "404") {
			cout << "Enter the quantity of the item" << itemDetails.name << " :";
			cin >> quantity;
			amount = itemDetails.amount * quantity;
			currentBill = itemDetails.name + "\t\t\t" + to_string(itemDetails.amount) + "\t\t" + to_string(quantity) + "\t" + to_string(amount) + '\n';
			salesDetails = to_string(quantity) + " of " + itemDetails.name + ',';
			finalSalesDetails += salesDetails;
			netAmount += amount;
			finalBill += currentBill;
			cout << "Added! Do you want to add more?(Y/N): ";
			cin >> addMore;
			cout << "\n\n";
			if (addMore == "n" or addMore == "N") {
				break;
			}
		}
		else {
			cout << "Wrong ID!";
			cout << "Press Enter to continue...\n";
			cin.ignore(10, '\n');
			if (cin.get() == '\n') {
				continue;
			}
		}
	}
	return make_pair(netAmount, make_pair(finalBill, finalSalesDetails + "."));
}


//Add items to BakeryItems Arrays
bool itemAdder(BakeryProducts list[], int& itemCount,string item) {
	string value,addMore;
	int price = 0;
	bool found = false;
	cout << "Enter the name of the "<<item<<" :";
	cin.ignore();
	getline(cin, value);
	
	for (int i = 0; i < itemCount; i++) {
		if (list[i].name == value) {
			found = true;
			break;
		}
	}
	if (found) {
		cout << "Value already exist..\n";
		cout << "Press Enter to continue...\n";
		cin.ignore(10, '\n');
		if (cin.get() == '\n') {
			return false;
		}
		
	}
	else {
		list[itemCount].name = value;
		cout << "Enter the price of the " << item << " :";
		if (item == "Bakery Item") {
			item = "A";
		}
		else if (item == "Beverage item") {
			item = "B";
		}
		else {
			item = "C";
		}
		cin >> price;
		list[itemCount].amount = price;
		list[itemCount].id = item + to_string(itemCount);
		ofstream outFile("data.txt", ios::app);
		if (outFile.is_open()) {
			outFile << item << ","
				<< list[itemCount].name << ","
				<< list[itemCount].amount << ","
				<< list[itemCount].id << "\n";
			outFile.close(); // Close the file after writing
			itemCount++;
		}
		else {
			cout << "Unable to open the file.\n";
			//return 0;
		}
		cout << "Success! Add more?(Y/N): ";
		cin >> addMore;
		cout << "\n\n";
		if (addMore == "y" or addMore == "Y") {
			return true;
		}
		else {
			return false;
		}
	}
}

//Function to call itemmAdder and viewBakeryitem
void manageItemAndPackage(BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[], 
	int& bakeItemCount, int& beverageitemCount,int& otherItemCount) {
	welcome();
	int itemChoice;
	bool addMore;					//Using as a variable to store Yes No Responses
	while (true) {
		cout << "1. Add items\n2.Return to menu\n\n";
		cout << "Please enter your selection:";
		cin >> itemChoice;
		cout << "\n\n";
		switch (itemChoice) {
		case 1:
			while (true) {
				cout << "1. Add Bakery Item\n2. Add Beverages\n3. Add other\n4. Return to menu\n\n";
				cout << "Please enter your selection:";
				cin >> itemChoice;
				cout << endl;
				switch (itemChoice) {
				case 1:
					do {
						addMore = itemAdder(bakeryItems, bakeItemCount, "Bakery Item");
					} while (addMore == true);
					break;
				case 2:
					do {
						addMore = itemAdder(beverages, beverageitemCount, "Beverage item");
					} while (addMore == true);
					break;
				case 3:
					do {
						addMore = itemAdder(otherItems, otherItemCount, "Other item");
					} while (addMore == true);
					break;
				case 4:
					break;
				default:
					cout << "Error ! Wrong Selection\n\n";
					cout << "\n\nPress Enter to go back.\n\n";
					cin.ignore(10, '\n');
					if (cin.get() == '\n') {
						continue;
					}
				}
				break;
			}
		case 2:
			return;
		default:
			cout << "Invalid Selection\n";
		}
	}
}

//View values in BackeryProduct arrays
void viewBakeryItem(BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[], 
	int bakeItemCount, int beverageitemCount, int otherItemCount) {
	welcome();
	if (bakeItemCount == 0 && beverageitemCount == 0 && otherItemCount == 0) {
		cout << "Empty! Please Add Some Products!\n\n";
	}
	if (bakeItemCount != 0) {
		cout << "\n\nBakery Products\n\n\tID\t\tName\t\t\t\tAmount\n\n";
		for (int i = 1; i <= bakeItemCount; ++i) {
			cout << i << ". \t"<< bakeryItems[i - 1].id<<"\t\t" << bakeryItems[i - 1].name << setw(15) << "\t\t" << bakeryItems[i - 1].amount << endl;
		}
		cout << endl;
	}
	if (beverageitemCount != 0) {
		cout << "\n\nBeverages\n\n\tID\t\tName\t\t\t\tAmount\n\n";
		for (int i = 1; i <= beverageitemCount; ++i) {
			cout << i << ". \t" << beverages[i - 1].id << "\t\t" << beverages[i - 1].name << setw(15) << "\t\t" << beverages[i - 1].amount << endl;
		}
		cout << endl;
	}
	if (otherItemCount != 0) {
		cout << "\n\nOther Items\n\n\tID\t\tName\t\t\t\tAmount\n\n";
		for (int i = 1; i <= otherItemCount; ++i) {
			cout << i << ". \t" << otherItems[i - 1].id << "\t\t" << otherItems[i - 1].name << setw(15) << "\t\t" << otherItems[i - 1].amount << endl;
		}
		cout << endl;
	}
	cout << "\n\nPress Enter to go back.\n\n";
	cin.ignore(10, '\n');
	if (cin.get() == '\n') {
		return;
	}
}

//Admins command handler
void adminCommands(int slectionAdmin, BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[], 
	int bakeItemCount, int beverageitemCount, int otherItemCount) {
	if (verification() == true) {
		while (true) {
			slectionAdmin = adminMenu(slectionAdmin);
			switch (slectionAdmin) {
			case 1:
				manageItemAndPackage(bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
				break;
			case 2:
				viewBakeryItem(bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
				break;
			case 3:
				readSalesDetails();
				break;
			case 4:
				return;
			default:
				cout << "Wrong Choice!\n\n";
				cout << "\n\nPress Enter to go back.\n\n";
				cin.ignore(10, '\n');
				if (cin.get() == '\n') {
					return;
				}
			}
		}
	}
	else {
		cout << "Wrong Credentaials !\n\n";
		cout << "\n\nPress Enter to go back.\n\n";
		cin.ignore(10, '\n');
		if (cin.get() == '\n') {
			return;
		}
	}
}

//Cashierts command handler
void cashierCommands(int slection, BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[], 
	int bakeItemCount, int beverageitemCount, int otherItemCount) {
	pair<int, pair<string, string>> getter; 
	if (cashierVerification() == true) {
		while (true) {
			slection = cashierMenu(slection);
			switch (slection) {
			case 1:
				viewBakeryItem(bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
				break;
			case 2:
				getter = makeBills(bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
				if (getter.first == 0) {
					break;
				}
				cout << setw(8) << "Name" << "\t\t" << "Unit Price" << "\t" << "Quantity" << "\t" << "Amount" << endl;
				cout << getter.second.first << endl << "Total is : " << getter.first << endl;
				addToSales(getter.first, getter.second.second);
				cout << "Press Enter to continue...\n";
				cin.ignore(10, '\n');
				if (cin.get() == '\n') {
					break;
				}
			case 3:
				return;
			default:
				cout << "Wrong Choice!\n\n";
				cout << "\n\nPress Enter to go back.\n\n";
				cin.ignore(10, '\n');
				if (cin.get() == '\n') {
					return;
				}
			}
		}
	}
	else {
		cout << "Wrong Credentaials !\n\n";
		cout << "\n\nPress Enter to go back.\n\n";
		cin.ignore(10, '\n');
		if (cin.get() == '\n') {
			return;
		}
	}
}

//Fucntion to read txt file and assign values to struct array
void readtext(BakeryProducts bakeryItems[], BakeryProducts beverages[], BakeryProducts otherItems[], 
	int& bakeItemCount, int& beverageitemCount, int& otherItemCount) {
	ifstream inFile("data.txt"); // Open the file for reading

	if (inFile.is_open()) {
		while (true) {
			string line,datatype;
			getline(inFile, line);
			if (line.empty()) {
				// Break the loop if an empty line is encountered
				//cout << "ADD ITEMS FIRST!\n\n";
				break;
			}
			size_t pos1 = line.find(",");
			size_t pos2 = line.find(",", pos1 + 1);
			size_t pos3 = line.find(",", pos2 + 1);

			datatype = (line.substr(0, pos1));
			if (datatype == "A") {
				bakeryItems[bakeItemCount].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
				bakeryItems[bakeItemCount].amount = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
				bakeryItems[bakeItemCount].id = line.substr(pos3 + 1);
				bakeItemCount++;
			}
			else if (datatype == "B") {
				beverages[beverageitemCount].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
				beverages[beverageitemCount].amount = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
				beverages[beverageitemCount].id = line.substr(pos3 + 1);
				beverageitemCount++;
			}
			else if(datatype == "C") {
				otherItems[otherItemCount].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
				otherItems[otherItemCount].amount = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
				otherItems[otherItemCount].id = line.substr(pos3 + 1);
				otherItemCount++;
			}

		}
		inFile.close(); // Close the file after reading
	}
	else {
		cout << "Unable to open the file.\n";
	}
}


int main() {
	int selection = 0,slectionAdmin = 0, slectionCashier = 0;
	int beverageitemCount = 0, bakeItemCount = 0,otherItemCount = 0;
	welcome();
	readtext(bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
	while (true) {
		selection = menu(selection);
		switch (selection) {
		case 1:
			viewBakeryItem(bakeryItems,beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
			break;
		case 2:
			companyDetails();
			break;
		case 3:
			adminCommands(slectionAdmin, bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
			break;
		case 4:
			cashierCommands(slectionCashier, bakeryItems, beverages, otherItems, bakeItemCount, beverageitemCount, otherItemCount);
			break;
		case 5:
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			cout << R"( 
 / _____)                                   | |         _                              
( (____  _____ _____    _   _  ___  _   _   | | _____ _| |_ _____  ____                
 \____ \| ___ | ___ |  | | | |/ _ \| | | |  | |(____ (_   _) ___ |/ ___)               
 _____) ) ____| ____|  | |_| | |_| | |_| |  | |/ ___ | | |_| ____| |       _    _    _ 
(______/|_____)_____)   \__  |\___/|____/    \_)_____|  \__)_____)_|      (_)  (_)  (_)
                       (____/                                                          )";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			return 0;
		default:
			cout << "Invalid Input\n";
			cout << "\n\nPress Enter to go back.\n\n";
			cin.ignore(10, '\n');
			if (cin.get() == '\n') {
				continue;
			}
		}
	}
}