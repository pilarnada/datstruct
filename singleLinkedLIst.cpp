#include<stdio.h>
#include<stdlib.h>

struct Node{
	int value;
	struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node *createNode(int value){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

void pushHead(int value){
	struct Node *newNode = createNode(value);
	
	if(head == NULL){
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head = newNode;
	}
}

void pushTail(int value){
	struct Node *newNode = createNode(value);
	
	if(head == NULL){
		head = tail = newNode;
	}
	else{
		tail->next = newNode;
		tail = newNode;
	}
}

void pushMid(int value, int insertAfter){
	struct Node *newNode = createNode(value);
	if(head == NULL){
		printf("Linked List is Empty.\n");
	}
	else if(tail->value == insertAfter){
		pushTail(value);
	}
	else{
		struct Node *flag = head;
		while(flag != NULL){
			if(flag->value == insertAfter) break;
			flag = flag->next;
		}
		
		if(flag == NULL){
			printf("Value %d is Not Found.\n", insertAfter);
		}
		else{
			struct Node *temp = flag->next;
			flag->next = newNode;
			newNode->next = temp;
		}
	}
}

void popHead(){
	if(head == NULL){
		printf("Linked List is Empty. \n");
	}
	else if(head == tail){
		head = tail = NULL;
	}
	else{
		struct Node *temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp);
	}
}

void popTail(){
	if(head == NULL){
		printf("Linked List is Empty. \n");
	}
	else if(head == tail){
		head = tail = NULL;
	}
	else{
		struct Node *flag = head;
		while(flag != NULL && flag->next != tail){
			flag = flag->next;
		}
		struct Node *temp = tail;
		flag->next = NULL;
		tail = flag;
		temp->next = NULL;
		free(temp);
	}
}

void popMid(int target){
	if(head == NULL){
		printf("Linked List is Empty. \n");
	}
	else if(head->value == target){
		popHead();
	}
	else if(tail->value == target){
		popTail();
	}
	else{
		struct Node *flag = head;
		while(flag != NULL && flag->next->value != target){
			flag = flag->next;
		}
		
		if(flag->next == NULL){
			printf("Value %d Not Found. \n", target);
		}
		else{
			struct Node *temp = flag->next;
			flag->next = temp->next;
			temp->next = NULL;
			free(temp);
		}
	}
}

void view(){
	struct Node *flag = head;
	while(flag != NULL){
		printf("%d -> ", flag->value);
		flag = flag->next;
	}
	puts("NULL");
}
int main(){
	pushHead(30);
	pushHead(20);
	pushTail(40);
	pushMid(25, 20);
	popHead();
	
	view();
	return 0;
}
