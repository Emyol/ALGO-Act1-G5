/* PROGRESS
Linklist - add record function
Priority Queue implementation - added similar max heap funtionality.

TO DO
Link ARRAY and LINK LIST (goods na ata?)
DISPLAY DESIGN
FILE HANDLING

*/


#include <iostream>
using namespace std;

const int MAX = 10;
int LEAD[MAX]; //array for top 10 leaderboard

//linked list
struct Node {
	string name;
	int score;
    int prio;
	Node *next;

	Node(string name, int score) : name(name), score(score), prio(1), next(NULL) {}
};
Node* head = NULL;

void addRecord(string name, int score);
void displayScore();//temporary

//prio queue implementation, prio of highest number is always 1, incrementing.
void addRecord(string name, int score){ 
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
			LEAD[i] = p->score;
				if (count == 10){
					break;
				}
			++i;
			++count;
			p = p->next;
		}

	cout << "ARRAY Content: \n";
		p = head;
		count = 0;
		for (int j = 0; j < MAX; j++){
			if (p){
				cout << "Rank "<< rank << " " << p->name << " (" << LEAD[j] << ")" <<endl;
					if (p && p->next->score == p->score){
						rank--;
					}
				p = p->next;
				rank++;
			} else{
				break;
			}
		}
}

int main(){
	//tests
	addRecord("Jule", 5); // prio = 1
	addRecord("Fac", 3);
	addRecord("You", 1);
	addRecord("C", 5);
	addRecord("Ferd", 6);
    addRecord("Ferd", 21);
    addRecord("Ferd", 18);
    addRecord("Ferd", 2);
    addRecord("Ferd", 7);
	addRecord("Test", 12);
	addRecord("Hadj", 16);
	addRecord("Des", 31);
	addRecord("Charl", 81);
	addRecord("Carl", 57);
	addRecord("Adrian",32);
	addRecord("Sup", 4);
	addRecord("Hello", 101);
	addRecord("Its", 8);
	addRecord("Me", 10);

	displayScore();

	return 0;
}

