#include <iostream> 
#include <iomanip>
#include <fstream>
#include <string> 
#include <cstring>
using namespace std; 
const string file = "C:\\Users\\Εμμανουελα\\source\\repos\\Status\\x64\\Debug\\currencies.dat";
const string download_file = "C:\\Users\\Εμμανουελα\\source\\repos\\Status\\x64\\Debug\\Status_Update.dat";

const int N = 8;
const int M = 4;
ifstream ifs;
ofstream ofs;


struct Money {
	string name;
	double rate_buy;
	double course_sell;
};

struct Bureau {
	string name;
	string address;
	Money currencies[N];
};

 
void input(Bureau& office);
void print_all(Bureau& office);
void write_file(const Bureau& office);
void download( Bureau office[]);

void update(Bureau office[]);
void min_desk(Bureau office[],string key);



void main() {
	int choice;
	Bureau offices[M];
	Bureau min_office;
	string currency_name;
	cout << endl << "-------------------------------------------------------------------------";
	cout << endl << "|                               MENU                                    |";
	cout << endl << "-------------------------------------------------------------------------";
	cout << endl << "| 1. Insert data(manually)                                              |"; 
	cout << endl << "| 2. Update and refresh                                                 |";
	cout << endl << "| 3. Display Informations and Currency Exchange Rates                   |";
	cout << endl << "| 4. Display the exchange office selling the cheapest currency of choice|";
	cout << endl << "| 5. Exit Program                                                       |";
	cout << endl << "| 6. Download Data                                                      |";
	cout << endl << "-------------------------------------------------------------------------";
	cout << endl << "Input your choice(1-6): ";
	cin >> choice;

	while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5)&&(choice!=6)) {
		cout << endl << "Oops, incorrect answer, please try again (1-6): ";
		cin >> choice;
	};

	do {
		switch (choice) {

		case 1:
			cin.ignore();
			for (int i = 0;i < M;i++) {
				cout << endl << " Enter details ";
				cout << endl << " ";
				input(offices[i]);
			}
			cout << endl << "Input successfull";

			for (int i = 0;i < M;i++) {
				write_file(offices[i]);
			}break;
		case 2:
			update(offices);break;
		case 3:
			for(int i=0;i<M;i++)
			print_all(offices[i]);
		break;
		case 4:
			cin.ignore();
			cout << endl << "Enter the currency to find the minimum selling rate Bureau: ";
			getline(cin, currency_name);
			min_desk(offices, currency_name);break;
			
		case 5:
			cout << endl << "Thank you for using 'Status: Update' ";
			cout << endl << " ";
			exit(0);
		case 6:
			cout << endl << "Downloading...";
			for(int i=0;i<M;i++)
			download(offices);
			cout << endl << "Download is complete!";
			break;
			
		}
		cout << endl << " ";
		cout << endl << "Would you like to use another function?(Insert Menu Option): ";
		cin >> choice;
	} while (choice != 5);
}

void input(Bureau& office) {
	cout << endl << "Enter the office's name: ";
	getline(cin, office.name);
	cout << endl << "Enter the office's address: ";
	getline(cin, office.address);
	for (int i = 0;i < N;i++) {
		cout << endl << "Enter the currency name: ";
		getline(cin, office.currencies[i].name);
		cout << endl << "Enter buy rate for " << office.currencies[i].name<<": ";
		cin >> office.currencies[i].rate_buy;
		cout << endl << "Enter sell rate for " << office.currencies[i].name << ": ";
		cin >> office.currencies[i].course_sell;
		cin.ignore();
	}
}
void write_file(const Bureau& office) {
	ofs.open(file, ios::app);
	if (ofs.fail()) {
		cout << endl << "Error";
		exit(1);
	}
	ofs << endl << office.name;
	ofs << endl << office.address;
	for (int i = 0;i < N;i++) {
		ofs << endl  << office.currencies[i].name;
		ofs << endl  << office.currencies[i].rate_buy;
		ofs << endl  << office.currencies[i].course_sell;
	}
	ofs.close();

}

void print_all(Bureau& office) {
	cout << endl << "--------------------------------------------------------------------";
	cout << endl << "|" <<"Office name : "<< office.name << " | ";
	cout << endl <<"|"<<"Office address: "<< office.address << "|";
	
	for (int i = 0;i < N;i++) {
		cout << endl <<"|"<<"Currency name : "<<office.currencies[i].name<<"|";
		cout << endl << fixed << setprecision(4) << "|"<<"Buy Rate      : "    <<setprecision(2)<<office.currencies[i].rate_buy<<"|";
		cout << endl << fixed << setprecision(4) << "|"<<"Sell Rate     : "    <<setprecision(2)<<office.currencies[i].course_sell<<"|";
	}

	
	cout << endl << "--------------------------------------------------------------------";
}


 void min_desk(Bureau office[], string key) {
	 double min_rate(5);
	 Bureau min_office;
	 int counter(0);
	 for (int i = 0;i < M;i++) {
		 for (int j = 0;j < N;j++) {
			 if ((office[i].currencies[j].name == key) && (office[i].currencies[j].course_sell < min_rate)) {
				 min_rate = office[i].currencies[j].course_sell;
				 min_office = office[i];
				 counter += 1;
			 }
		 }
	 }
	 if (counter == 0) {
		 cout << endl << "Currency not found in any office.";
	 }
	 else {
		 cout << endl << "The minimum sell rate for " << key << " is can be found in the  " << min_office.name;
	 }
}

 void update(Bureau office[]) {
	 string update_office;
	 string update_currency;
	 double update_RateBuy;
	 double update_CourseSell;
	 bool flag(false);
	 bool flag2(false);
	 cin.ignore();
	 cout << endl << "Enter the office name for update: ";
	 getline(cin, update_office);

	 
	 for (int i = 0;i < M;i++) {
		 if (office[i].name == update_office) {
			 flag = true;

			 cout << "Enter the currency name for update: ";
			 getline(cin, update_currency);

			 
			 for (int j = 0;j < N;++j) {
				 if (office[i].currencies[j].name == update_currency) {
					 flag2 = true;

					 cout << endl << "Enter the new Buy rate for " << update_currency << ": ";
					 cin >> update_RateBuy;
					 cout << endl << "Enter the new Sell rate for " << update_currency << ": ";
					 cin >> update_CourseSell;

					 office[i].currencies[j].rate_buy = update_RateBuy;
					 office[i].currencies[j].course_sell = update_CourseSell;


					 ofs.open(download_file);
					 if (ofs.fail()) {
						 cout << endl << "Error";exit(1);
					 }
					 else {
						 ofs << office[i].currencies[j].rate_buy;
						 ofs << office[i].currencies[j].course_sell;
					 }
					 ofs.close();

					 cout << endl << "Currency rates updated successfully!";break;
				 }
			 }

			 if (flag2 == false) {
				 cout << endl << "Currency not found in the specified office.";
			 }
			 break;
		 }
	 }
	 
	 if (flag == false) {
		 cout << endl << "Office not found. :(";
	 }


 }

 void download( Bureau office[]) {
	 
	 ifs.open(download_file);
	 if (ifs.fail()) {
		 cout << endl << "Error";
		 exit(1);
	 }
	 
	 for (int i = 0;i < M;++i) {
		 getline(ifs, office[i].name);
		 getline(ifs, office[i].address);

		 for (int j = 0;j < N;++j) {
			 getline(ifs, office[i].currencies[j].name);
			 ifs >> office[i].currencies[j].rate_buy;
			 ifs >> office[i].currencies[j].course_sell;
			 ifs.ignore();
		 }
	 }
	 
	 ifs.close();
	 
	 
