/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- [김민재] [2021041070] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z     ㅋ      Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; // 원형리스트이므로 리스트가 비어있을때 헤드노드는 자신을 가리킴
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h) // 리스트가 비어있다면
	{
		free(h); //헤드 노드 삭제
		return 1;
	}

	listNode* p = h->rlink; //현재 노드

	listNode* prev = NULL; // 이전노드
	while(p != NULL && p != h) {
		prev = p; //이전노드
		p = p->rlink; //다음노드로 이동
		free(prev); //이전 노드 삭제
	}
	free(h); //헤드노드 삭제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 리스트가 비어있다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //현재노드 

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key); //현재 노드의 값 출력
		p = p->rlink; //다음 노드 이동
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //헤드노드의 이전,이후 링크 출력

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // 노드의 이전,이후 링크 출력
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 삽입할 노드 생성
	node->key = key; //노드의 값을 입력값으로 설정
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node; //헤드노드의 다음링크가 삽입할 노드를 가리킴
		h->llink = node; // 헤드노드의 이전링크도, 원형리스트이므로 삽입할 노드를 가리킴
		node->rlink = h; // 삽입할 노드의 다음링크는 헤드노드를 가리킴
		node->llink = h;// 삽입할 노드의 이전링크는 헤드노드를 가리킴
	} else {
		h->llink->rlink = node; // 마지막 노드의 다음링크는 삽입할 노드를 가리킴
		node->llink = h->llink; // 삽입할 노드의 이전링크는 마지막 노드를 가리킴
		h->llink = node; // 헤드노드의 이전링크는 삽입할 노드를 가리킴
		node->rlink = h; // 삽입할 노드의 다음링크는 헤드노드를 가리킴
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) //연결리스트가 비어있다면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //마지막 노드

	/* link 정리 */
	nodetoremove->llink->rlink = h; // 뒤에서 두번째 노드의 다음링크는 헤드노드를 가리킴
	h->llink = nodetoremove->llink; //헤드노드의 이전링크는 뒤에서 두번째 노드를 가리킴

	free(nodetoremove); //마지막 노드를 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 노드 생성
	node->key = key; //노드의 값을 입력값으로 설정
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink; //삽입할 노드의 다음링크는 헤드노드의 다음노드를 가리킴
	h->rlink->llink = node; // 헤드노드의 다음노드의 이전링크는 삽입할 노드를 가리킴
	node->llink = h; // 삽입할 노드의 이전링크는 헤드노드를 가리킴
	h->rlink = node; //헤드노드의 다음링크는 삽입할 노드를 가리킴


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) //리스트가 비어있다면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; //헤드노드의 다음노드

	/* link 정리 */
	nodetoremove->rlink->llink = h; //첫 노드의 다음노드의 이전링크는 헤드노드를 가리킴
	h->rlink = nodetoremove->rlink; //헤드노드의 다음링크는 첫노드의 다음노드를 가리킴

	free(nodetoremove); //첫노드 제거

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { //리스트가 비어있다면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; 
	listNode *trail = h;
	listNode *middle = h;
	//n이 현재, middle이 그뒤, tail이 그뒤를 가르키면서 값을 가지고 있게된다.

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle; // trail은 middle을 가리킴
		middle = n; // middle은 n을 가리킴
		n = n->rlink; // n은 다음노드로 이동
		middle->rlink = trail; // middle의 이전 노드는 n, 다음노드는 trail를 가리킴 >> 가리키는 방향 역순
		middle->llink = n;
	}
	//끝나면 노드를 가리키는 방향이 역순으로 가리키게 됌
	h->rlink = middle; // 다 바뀌었으면 n은 Null이므로 그 다음 노드인 middle이 헤드노드가 된다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 노드 생성
	node->key = key; // 입력값을 노드의 값으로 설정
	node->llink = node->rlink = NULL;

	if (h->rlink == h) // 리스트가 비어있다면
	{
		insertFirst(h, key); // 첫자리에 넣음
		return 1;
	}

	listNode* n = h->rlink; //현재노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { 
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { 
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //삽입할 노드의 다음링크는 현재 노드를 가리킴
				node->llink = n->llink; //삽입할 노드의 이전링크는 현재노드의 이전노드를 가리킴
				n->llink->rlink = node; //현재노드의 이전노드의 다음링크는 삽입할 노드를 가리킴
				n->llink = node; //현재노드의 이전링크는 삽입할 노드를 가리킴
			}
			return 0;
		}

		n = n->rlink; //다음노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) //리스트가 비어있다면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //현재 노드

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //삭제할 노드의 앞에 있는 노드의 다음 노드 링크는, 삭제할 노드의 뒤에 있는 노드를 가리킴
				n->rlink->llink = n->llink; //삭제할 노드의 뒤에 있는 노드의 이전 노드 링크는, 삭제할 노드의 앞에 있는 노드를 가리킴
				free(n); //현재노드 삭제
			}
			return 0;
		}

		n = n->rlink; // 다음노드로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


