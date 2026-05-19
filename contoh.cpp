#include <iostream>
using namespace std;

/*
const int s_max = 50;

int top = 0;
int stack[s_max];

void buatStack(){
	stack[top] = 0;
}

bool stackkosong(){
	if (top == 0)
		return(true);
	else
		return(false);
}

bool stackPenuh(){
	if(top == s_max)
		return true;
	else
		return false;
}	

void push(int IB){
	if(stackPenuh()){
		cout << "stack overflow/penuh\n";
	} else {
		top++;
		stack[top] = IB;
		stack[0] = top;
		}
	
}

void pop(){
	int dataTampung;
	if (stackkosong()){
		cout << "stack kosong";
		} else{
			dataTampung = stack[top];
			cout << "data " << dataTampung << " berhasil dihapus\n";
			top--;
			stack[0]=top;
			}
}

void cetakstack(){
	int i = 1;
	if (stackkosong()){
		cout << "stack kosong" << endl;
		}
		else {
			while (i <= top){
				cout << "data ke-" << i << ": " << stack[i] << endl;
				i++;
				}
			}
	}
	
int main()
{
buatStack();
	
push(10);	
push(20);
push(30);

cetakstack();

pop();

cetakstack();
	
	return 0;
}
*/

struct Node {
  int data;
  Node *next;
};

struct {
  Node *front = NULL;
  Node *rear = NULL;
} Queue;

void enqueue(int value) {

  Node *baru = new Node;

  baru->data = value;
  baru->next = NULL;

  if (Queue.front == NULL) {
    Queue.front = baru;
    Queue.rear = baru;
  } else {

    Queue.rear->next = baru;

    Queue.rear = baru;
  }

  cout << value << " berhasil ditambahkan\n";
}
void dequeue() {

  if (Queue.front == NULL) {
    cout << "Queue kosong!\n";
    return;
  }

  Node *hapus = Queue.front;

  cout << Queue.front->data << " dihapus\n";

  Queue.front = Queue.front->next;

  if (Queue.front == NULL) {
    Queue.rear = NULL;
  }

  delete hapus;
}
void display() {

  if (Queue.front == NULL) {
    cout << "Queue kosong!\n";
    return;
  }

  Node *bantu = Queue.front;

  cout << "Isi queue: ";

  while (bantu != NULL) {
    cout << bantu->data << " ";
    bantu = bantu->next;
  }

  cout << endl;
}
int main() {

  enqueue(10);
  enqueue(20);
  enqueue(30);

  display();

  cout << endl;

  dequeue();

  display();

  cout << endl;

  enqueue(40);

  display();

  return 0;
}
