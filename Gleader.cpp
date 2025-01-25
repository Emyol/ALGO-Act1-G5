/* PROGRESS
Linklist - add record function
Priority Queue implementation - added similar max heap funtionality.

TO DO
Link ARRAY and LINK LIST (goods na ata?)
DISPLAY DESIGN
FILE HANDLING (Oks naren ata? I mean pwede lagyan ng design ung pag save sa file pero nag fufunction na)
ERROR HANDLING for inputs

*/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 10;
int LEADScore[MAX]; //array for top 10 leaderboard
string LEADName[MAX];

//linked list
struct Node {
	string name;
	int score;
    int prio;
	Node *next;

	Node(string name, int score) : name(name), score(score), prio(1), next(NULL) {}
};
Node* head = NULL;

//prototypes
void push(string name, int score);
void displayScore();//temporary
void saveFile();
void loadFile();

//prio queue implementation, prio of highest number is always 1, incrementing.
void push(string name, int score){ 
Node* tmp = new Node(name, score);

if(!head){
	head = tmp;
} else {
	Node* cur = head;
	Node* prev = NULL;

	//check if existing, removes node.
	while(cur){
		if(tmp->name == cur->name){
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
}

//for testing
void displayScore(){
	int count = 1, i = 0, rank = 1;
	Node *p;
		p = head;
		while (p!=NULL){
			//saving top 10 scores to array (di pako certain kung ano restrictions sa top 10)
			LEADScore[i] = p->score;
			LEADName[i] = p->name;
				if (count == 10){
					break;
				}
			++i;
			++count;
			p = p->next;
		}

	cout << "ARRAY Content: \n";
	p = head;
	i = 1;
		for (int j = 0; j < MAX; j++){
			if (p){
				cout << "Rank "<< rank << " " << LEADName[j] << " (" << LEADScore[j] << ")" << endl;
					if (p && p->next->score == p->score){
					 //skip rank increment
					} else{
						rank += i;
						i = 0;
					}
				p = p->next;
				i++;
			} else{
				break;
			}
		}
		saveFile();
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
	ifstream file("leaderboard.txt");
	for(int i = 0; i<MAX; i++){
		file >> LEADName[i] >> LEADScore[i];
	}
	file.close();

	ifstream rec("record.txt");
	string name;
	int score;

	while (rec >> name >> score) {
		push(name, score);
	}

	rec.close();

}

int main(){
	//tests
	loadFile();
	displayScore();

	return 0;
}

