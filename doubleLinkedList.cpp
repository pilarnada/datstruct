#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// PENERAPAN DLL (PUSH MID) YANG SAYA TERAPKAN PADA SOAL QUIZ SEBELUM UTS

struct Node{
	char genre[20];
	char code[20];
	char name[50];
	struct Node *next;
	struct Node *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node *createNode(char genre[], char code[], char name[]){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(newNode->genre, genre);
	strcpy(newNode->code, code);
	strcpy(newNode->name, name);
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void pushHead(struct Node *newNode){
	if(head == NULL){
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail(struct Node *newNode){
	if(head == NULL){
		head = tail = newNode;
	}
	else{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

void pushMid(struct Node *newNode){
	if(head == NULL){
		head = tail = newNode;
	}
	else if(strcmp(newNode->name, head->name)<0){
		pushHead(newNode);
	}
	else if(strcmp(newNode->name, tail->name)>0){
		pushTail(newNode);
	}
	else{
		struct Node *flag = head;
		while(flag != NULL && strcmp(flag->name, newNode->name)<0){
			flag = flag->next;
		}
		
		flag->prev->next = newNode;
		newNode->next = flag;
		newNode->prev = flag->prev;
		flag->prev = newNode;
	}
}

void popHead(){
	if(head == NULL){
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		struct Node *temp = head;
		head = head->next;
		head->prev = NULL;
		free(temp);
	}
}

void popTail(){
	if(head == NULL){
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		struct Node *temp = tail;
		tail = tail->prev;
		tail->next = NULL;
		free(temp);
	}
}

void popMid(char name[]){
	if(head == NULL){
		return;
	}
	
	else{
		struct Node *flag = head;
		
		while(flag != NULL){
			if(strcmp(flag->name, name)==0){
				if(flag == head){
					popHead();
					flag = head;
				}
				else if(flag == tail){
					popTail();
					flag = NULL;
				}
				else{
					struct Node *temp = flag;
					flag->prev->next = flag->next;
					flag->next->prev = flag->prev;
					flag = flag->next;
					free(temp);
				}
			}
			else{
				flag = flag->next;
			}
		}
		
	}
}

void popGenre(char genre[]){
	if(head == NULL){
		return;
	}
	
	else{
		struct Node *flag = head;
		
		while(flag != NULL){
			if(strcmp(flag->genre, genre)==0){
				if(flag == head){
					popHead();
					flag = head;
				}
				else if(flag == tail){
					popTail();
					flag = NULL;
				}
				else{
					struct Node *temp = flag;
					flag->prev->next = flag->next;
					flag->next->prev = flag->prev;
					flag = flag->next;
					free(temp);
				}
			}
			else{
				flag = flag->next;
			}
		}
		
	}
}

void view(){
	if(head == NULL){
		printf("NO DATA\n");
	}
	else{
		struct Node *flag = head;
		while(flag != NULL){
			printf("%s %s %s\n", flag->genre, flag->code, flag->name);\
			flag = flag->next;
		}
	}
}



int main(){
		// CASE 1
	puts("CASE 1");
	pushMid(createNode("Fiction", "B001", "The Lord of the Ringss"));
	pushMid(createNode("Fiction","B002","Harry Potter and the Philosopher's Stone"));
	pushMid(createNode("NonFiction","B003","Sapiens: A Brief History of Humankind"));
	popMid("Sapiens: A Brief History of Humankind");
	view();
	printf("\n\n");
	
	puts("CASE 2");
	head = tail = NULL;
	pushMid(createNode("NonFiction","B001","A Brief History of Time"));
	pushMid(createNode("Fiction","B002","The Catcher in the Rye"));
	pushMid(createNode("Fiction","B003","The Great Gatsby"));
	pushMid(createNode("NonFiction","B004","Sapiens: A Brief History of Humankind"));
	pushMid(createNode("Fiction","B005","The Hobbit"));
	popGenre("Fiction");
	view();
	
	return 0;
}
