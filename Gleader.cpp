/* PROGRESS
Linklist - add record function
Priority Queue implementation - added similar max heap funtionality.

TO DO
Link ARRAY and LINK LIST (goods na ata?)
DISPLAY DESIGN
FILE HANDLING
ERROR HANDLING for inputs

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

void push(string name, int score);
void displayScore();//temporary

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
	i = 1;
		for (int j = 0; j < MAX; j++){
			if (p){
				cout << "Rank "<< rank << " " << p->name << " (" << LEAD[j] << ")" << endl;
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
}

int main(){
	//tests
	push("Jule", 5); // prio = 1
	push("Fac", 3);
	push("You", 1);
	push("C", 5);
	push("Ferd", 6);
    push("Ferd", 21);
    push("Ferd", 18);
    push("Ferd", 2);
    push("Ferd", 7);
	push("Test", 12);
	push("Hadj", 16);
	push("Des", 31);
	push("Charl", 101);
	push("Carl", 101);
	push("Adrian",32);
	push("Sup", 4);
	push("Hello", 101);
	push("Its", 101);
	push("Me", 16);

	displayScore();

	push("Charl", 102);
	displayScore();
	return 0;
}

