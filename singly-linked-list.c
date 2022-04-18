#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {  //노드 구조체 선언 데이터와 다음 주소를 가리키는 링크가 들어 있음
	int key; //데이터 
	struct Node* link; // link 필드 자신과 동일한 타입을 가르켜야 함
} listNode;

typedef struct Head { // 처음 노드를 가르키는 first Head 구조체
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h); //종료 동적 할당 해제

int insertFirst(headNode* h, int key); // list 처음에 key에 대한 노드하나를 추가
int insertNode(headNode* h, int key); // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertLast(headNode* h, int key); // list에 key에 대한 노드하나를 마지막에 추가

int deleteFirst(headNode* h); // list의 첫번째 노드 삭제
int deleteNode(headNode* h, int key); // list에서 key에 대한 노드 삭제
int deleteLast(headNode* h); // list의 마지막 노드 삭제
int invertList(headNode* h); // 리스트의 링크를 역순으로 재 배치

void printList(headNode* h); // 리스트를 출력

int main()
{
	char command; // 문자형 변수 선언
	int key; // int형 변수 선언
	headNode* headnode=NULL;
    printf("[----- [kim dongmin] [2017038093] -----]\n");
    
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 입력 받음

		switch(command) {
		case 'z': case 'Z': //초기화 
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': //출력 리스트
			printList(headnode);
			break;
		case 'i': case 'I': // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //list에서 key에 대한 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // list에 key에 대한 노드하나를 마지막에 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode); // list의 마지막 노드 삭제
			break;
		case 'f': case 'F': // list 처음에 key에 대한 노드하나를 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // list의 첫번째 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //리스트의 링크를 역순으로 재 배치
			invertList(headnode);
			break;
		case 'q': case 'Q': //종료 및 동적 할당 해제
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) { //초기화

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL) //조건문 h가 NULL이 아니면 할당된 메모리 모두 헤제
		freeList(h);//할당한 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); //동적 할당
	temp->first = NULL; //NULL 대입
	return temp; //temp 반환
}

int freeList(headNode* h){ //
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // listNode형 포인터 p에 첫번쩨 주소 h 대입

	listNode* prev = NULL; /// listNode형 포인터 prev에 NULL 대입
	while(p != NULL) { //p 가 NULL이 아닐 때까지 반복
		prev = p;
		p = p->link;
		free(prev); //동적할당 해제
	}
	free(h); //동적할당 해제
	return 0; //리턴 0
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당
	node->key = key; //노드에 key 데이터를 받음
	node->link = NULL; // 다음 링크 NULL

	if (h->first == NULL) //첫번째 일때 
	{
		h->first = node; // 노드를 첫번째에다 넣음
		return 0;
	}

	listNode* n = h->first; //listNode형 포인터 n 선언 후 first 대입
	listNode* trail = h->first; //listNode형 포인터 trail 선언 후 first 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이 맞을 때까지 반복
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { 
				h->first = node;
				node->link = n;
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n; //trail에 n 대입
		n = n->link; //link 대입
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; //마지막 노드에 삽입
	return 0;
}

/**
 * // list에 key에 대한 노드하나를 마지막에 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당
	node->key = key; //노드에 key 데이터를 받음
	node->link = NULL; // 다음 링크 NULL

	if (h->first == NULL) //처음 노드 가 없으면 첫번째에 넣어줌
	{
		h->first = node; //first에 node대입
		return 0;
	}

	listNode* n = h->first; // listNode형 포인터 n 선언 하고 first을 넣음
	while(n->link != NULL) { //link가 NULL이 맞을 때까지 반복
		n = n->link; 
	}
	n->link = node; //n의 link가 node를 가리침
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { //맨 앞에 노드 추가

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적 할당
	node->key = key; // //노드에 key 데이터를 받음

	node->link = h->first; // 원래 가르키던 노드를 지금 추가한 노드가 가르키게 함
	h->first = node; //처음 주소에 node을삽입

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //노드가 없을때 오류 노드가 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // listNode형 포인터 n 선언 하고 first을 넣음
	listNode* trail = NULL; //trail NULL

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //로드 
		if(n->key == key) { 
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n); //동적 할당 해제
			return 0;
		}

		trail = n; //trail에  n
		n = n->link; //이전 노드의 링크 삽입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) ////노드가 없을때 오류 노드가 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { 
		h->first = NULL;
		free(n); //동적할당 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n; //이동
		n = n->link; 
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; // 이전 노드의 링크 NULL 처리
	free(n); //동적할당 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) ////노드가 없을때 오류 노드가 없음
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // 첫번째 노드

	h->first = n->link; //이전 노드를 첫번째로 가리킴
	free(n); // 동적 할당 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //노드가 없을때 오류 노드가 없음
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; // listNode형 n 선언
	listNode *trail = NULL; // listNode형 trail 선언
	listNode *middle = NULL; // listNode형 middle 선언

	while(n != NULL){ 
		trail = middle; //trail에 middle저장
		middle = n; //middle 에 n
		n = n->link; //다음 n이 가리키고 있는 노드
		middle->link = trail; //  링크 역순
	}

	h->first = middle; // middle가 처음 노드

	return 0;
}


void printList(headNode* h) { //출력 리스트
	int i = 0; //정수형 i 선언
	listNode* p; //listNode형 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //노드가 없을때 오류 노드가 없음
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p에 처음노드

	while(p != NULL) { //p가 NULL이 될 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //i 번째 와 데이터 출력
		p = p->link; //다음 노드
		i++; //i값 증가
	}

	printf("  items = %d\n", i); //노드의 갯수
}