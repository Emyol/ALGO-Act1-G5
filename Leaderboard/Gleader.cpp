#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

const int MAX = 10;
int LEADScore[MAX]; //array for top 10 leaderboard
string LEADName[MAX];
int playerCount = 0;
int trackUP = 0;

//linked list
struct Node {
	string name;
	int score;
    int prio;
	Node *next;

	Node(string name, int score) : name(name), score(score), prio(1), next(NULL) {}
};
Node* head = NULL;

class InvalidInputException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid input.";
    }
};

//prototypes
void push(string name, int score);
void displayScore();//temporary
bool checkIfPlayerExists(string name);
void saveFile();
void loadFile();
void GUI();
//design functions;
void dSpace();
void CLS();

//prio queue implementation, prio of highest number is always 1, incrementing.
void push(string name, int score, int flag){ 
Node* tmp = new Node(name, score);

bool updatePlayer = false;
bool verify = false;

if (flag == 1) {
	updatePlayer = true;
}

if(!head){
	head = tmp;
} else {
	Node* cur = head;
	Node* prev = NULL;

	//check if existing, removes node.
	while(cur){
		if(tmp->name == cur->name){
			if (updatePlayer == true) {
				verify = true;
		} else {
			char choice;
			cout << "Player " << name << " already has an existing record.\n";
			cout << "Do you wish to update (Y/N)?: ";

			while (true) {
			try {
				cin >> choice;

				if (cin.fail() || cin.peek() != '\n' || !isalpha(choice)) {
					throw InvalidInputException();
				}
				break;
			} catch (const InvalidInputException &e) {
				cout << e.what() << endl;
				cin.ignore(10000, '\n');
			}
    	}
				if(choice == 'Y' || choice == 'y') {
					verify = true;
					trackUP = 1;
				} else if (choice == 'N' || choice == 'n') {
					verify = false;
					trackUP = 2;
					cout << "Returning to main menu...\n";
					return;
				} else {
					cout << "Invalid choice, returning to menu...\n";
					verify = false;
					trackUP = 2;
					return;
				}
		}

		if(prev){
			prev->next = cur->next;
		} else {
			head = cur->next;
				}
		break;
		}
		prev = cur;
		cur = cur->next;
	}

	cur = head;
	prev = NULL;

        while(cur && cur->score >= tmp->score){
            prev = cur;
            cur = cur->next;
        }

        if(prev){
            prev->next = tmp;
            tmp->next = cur;
        } else {
            tmp->next = cur;
            head = tmp;
        }

        Node* temp = head; //readjust priorities
        int tempPrio = 1;
        while (temp) {
            if (temp->next && temp->score == temp->next->score) {
                temp->prio = tempPrio;
            } else {
                temp->prio = tempPrio;
                tempPrio++;
            }
            temp = temp->next;
        }
	}

	// add to leaderboard array
    Node* p = head;
    int i = 0;
    while (p != NULL && i < MAX) {
        LEADScore[i] = p->score;
        LEADName[i] = p->name;
        ++i;
        p = p->next;
		playerCount++;
    }
}

//for displaying leaderboards
void displayScore(){
	bool recordExists = false;
	int i = 0, rank = 1;
	Node *p;
		p = head;
		
		//check if there are records
		if(p!=NULL){
			recordExists = true;
		} else {
			cout << "No records currently exists...\n";
			cout << "Leaderboards unavailable...\n";
			cout << "Returning to main menu...\n";
			return;
		}

    dSpace();
    cout << setw(18) << "PLAYER NAME" << setw(10) << " || " << setw(15) << "SCORE" << endl;
    dSpace();
	p = head;
	i = 1;
	
	     
    for (int j = 0; j < MAX; j++) {  
        if (LEADName[j] != "") { 
            cout << "Rank " << setw(2) << rank << ": "
                 << setw(30) << left << LEADName[j]
                 << "  " << setw(1) << right << LEADScore[j] << endl;

            if (j < playerCount - 1 && LEADScore[j] == LEADScore[j + 1]) {  
                //skip iteration
            } else {
                rank += i;
				i = 0;  
            }
        }
		i++;
    }


	cout <<"Press Enter to continue...";
	cin.ignore();
	cin.get();
	CLS();
}

void saveFile(){
	ofstream file("leaderboard.txt");
	for(int i = 0; i<MAX; i++){
		file << LEADName[i] << " " << LEADScore[i] << endl;
	}
	file.close();

	ofstream rec("record.txt");
	Node* tmp = head;
	while(tmp != NULL){
		rec << tmp->name << " " << tmp->score << endl;
		tmp = tmp->next;
	}
	rec.close();
}

void loadFile(){
	bool check = false;

	ifstream file("leaderboard.txt");
	for(int i = 0; i<MAX; i++){
		if(file >> LEADName[i] >> LEADScore[i]){
			check = true;
		} else {	
			break;
		}
	}
	file.close();

	ifstream rec("record.txt");
	string name;
	int score;
	
 	while (getline(rec, name)) { 
        size_t pos = name.find_last_of(" "); 
        if (pos != string::npos) {
            string tempName = name.substr(0, pos); 
            int tempScore = stoi(name.substr(pos + 1)); 

            push(tempName, tempScore, 1);
        }
    }
	rec.close();

	if (check){
		cout << "Leaderboards loaded successfully\n";
	}
}

void GUI(){
	loadFile(); //initialize saved data

	while (1){
		char choice;
		string validInput;

		dSpace();
		cout << setw(40) << "HADJI GAMES LEADERBOARDS\n";
		dSpace();
		cout <<"A. ADD NEW SCORE\n";
		cout <<"B. UPDATE EXISTING SCORE\n";
		cout <<"C. LEADERBOARDS\n";
		cout <<"D. SAVE LEADERBOARDS\n";
		cout <<"E. EXIT\n";
		dSpace();
		cout <<"Your Choice: ";

		while (true) {
			try {
				cin >> choice;

				if (cin.fail() || cin.peek() != '\n' || !isalpha(choice)) {
					throw InvalidInputException();
				}
				break;
			} catch (const InvalidInputException &e) {
				cout << e.what() << endl;
				cin.ignore(10000, '\n');
				cout << "Try again: ";
			}
    	}

		choice = toupper(choice);
		switch (choice){
			case 'A': {
				trackUP = false;
				string pName;
				int pScore;

				cout << "Enter Player Name: ";
				cin.ignore();
				getline(cin,pName);

				cout << "Enter Score: ";
					while (true) {
						string input;
						cin >> input;

						bool checkValid = true;
						for (char c : input){
							if (!isdigit(c)){
								checkValid = false;
								break;
							}
						}
						if (checkValid){
						try{
							pScore = stoi(input);
							break;		
						} catch (const InvalidInputException &e){
						cout << e.what() << endl;
						cin.clear();
						cin.ignore(10000, '\n');
					}
				} else {
					cout << "Invalid input. Try again: ";
					cin.clear();
					cin.ignore(10000, '\n');
				}
			}

				push(pName, pScore, 0);
				if (trackUP == 1) {
				cout << "Record for " << pName << " Successfully updated!...\n";
				} else if (trackUP == 2) {
				cout << "Cancelled record update for " << pName << "...\n";
				} else {
				cout << "Record for " << pName << " Successfully added!...\n";
				}
			break;
			}
			case 'B':
			{
				string pName;
				int pScore;

				cout << "Enter Player Name: ";
				cin.ignore();
				getline(cin,pName);

				if(checkIfPlayerExists(pName)){
					//proceed
				} else {
					cout << "No record with player " << pName <<" found...\n";
					cout << "Returning to main menu\n";
					break;
				}

				cout << "Enter New Score: ";
					while (true) {
						string input;
						cin >> input;

						bool checkValid = true;
						for (char c : input){
							if (!isdigit(c)){
								checkValid = false;
								break;
							}
						}
						if (checkValid){
						try{
							pScore = stoi(input);
							break;		
						} catch (const InvalidInputException &e){
						cout << e.what() << endl;
						cin.clear();
						cin.ignore(10000, '\n');
					}
				} else {
					cout << "Invalid input. Try again: ";
					cin.clear();
					cin.ignore(10000, '\n');
				}
			}
				push(pName, pScore, 1);
				cout << "Record for " << pName << " Successfully updated!...\n";
			break;
			}
			case 'C':
				displayScore();
			break;
			case 'D':
				cout <<"Saving leaderboards...\n";
				saveFile();
				cout <<"Sucessfully saved!...\n";
				cout <<"Press Enter to continue...";
				cin.ignore();
				cin.get();
				CLS();
			break;
			case 'E':
				cout <<"Thank you! Exiting...\n";
				return;
			break;
			default:
				cout << "Please Enter letters A-E\n";
		}
	}
}

bool checkIfPlayerExists(string name){
	Node *tmp = head;

	while(tmp){
		if(tmp->name == name){
			return true;
		}
	tmp = tmp->next;
	}
	return false;
}



int main(){
	//tests
	GUI();
	return 0;
}

void CLS(){
	for (int i = 0; i < 50; i++){
		cout << endl;
	}
}

void dSpace(){
	for (int i = 0; i < 57; i++){
		cout << "=";
	}
	cout << endl;
}
