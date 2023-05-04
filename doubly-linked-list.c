/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>

// doubly linked list의 노드에 대한 구조체
typedef struct Node {
	int key;            // 데이터
	struct Node* llink; // 왼쪽 노드의 주소
	struct Node* rlink; // 오른쪽 노드의 주소
} listNode;

// doubly linked list의 head node에 대한 구조체
typedef struct Head {
	struct Node* first; // 첫 번째 노드의 주소
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h); // 연결 리스트 초기화하는 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해할 것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);             // 연결 리스트에 대한 메모리 해제하는 함수

int insertNode(headNode* h, int key);  // key값 보다 한 단계 큰 값의 노드 앞에 삽입하는 함수
int insertLast(headNode* h, int key);  // 연결 리스트의 마지막에 노드 삽입하는 함수
int insertFirst(headNode* h, int key); // 연결 리스트의 처음에 노드 삽입하는 함수
int deleteNode(headNode* h, int key);  // 인자로 받은 key값과 같은 값을 갖는 노드 삭제하는 함수
int deleteLast(headNode* h);           // 연결 리스트의 마지막 노드 삭제하는 함수
int deleteFirst(headNode* h);          // 연결 리스트의 첫 노드 삭제하는 함수
int invertList(headNode* h);           // 연결 리스트를 역순으로 만드는 함수

void printList(headNode* h);           // 연결 리스트 출력하는 함수

int main(){
	char command;            // 명령어
	int key;                 // 입력받을 값
	headNode* headnode=NULL; // head에 들어있는 주소값을 NULL로 초기화

	printf("[----- [Choi Yoolim] [2020022001] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령어 입력

		switch(command) {              // 입력받은 명령어에 대한 switch문
		case 'z': case 'Z':
			initialize(&headnode);     // 연결리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode);       // 연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);         // 삽입할 key값 입력
			insertNode(headnode, key); // 입력된 key값보다 한 단계 큰 노드 앞에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);         // 삽입할 key값 입력
			deleteNode(headnode, key); // 입력된 key값과 동일한 값을 가진 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);         // 삽입할 key값 입력
			insertLast(headnode, key); // 입력된 key값을 노드 마지막에 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);      // 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);          // 삽입할 key값 입력
			insertFirst(headnode, key); // 입력된 key값을 맨 앞에 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);      // 첫 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);       // 연결 리스트 역순
			break;
		case 'q': case 'Q':
			freeList(headnode);         // 동적 메모리 할당 해제
			break;
		default:                        // 그 이외의 명령어는 다루지 않음
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 'q' 또는 'Q'가 입력되면 프로그램종료

	return 1;
}

int initialize(headNode** h) { // 링크드 리스트 초기화 함수

	if(*h != NULL)                            // 메모리가 할당된 경우
		freeList(*h);                         // 메모리 해제

	*h = (headNode*)malloc(sizeof(headNode)); // headNode의 사이즈 만큼 메모리 할당
	(*h)->first = NULL;                       // headNode에 들어가는 주소값을 NULL로 초기화
	return 1;
}

int freeList(headNode* h){  // 링크드 리스트에 대한 동적 메모리 해제
	
	listNode* p = h->first; // p이 첫 노드를 가리키도록 설정

	listNode* prev = NULL;  // 이전 노드에 대한 메모리 해제를 위한 포인트 변수
	while(p != NULL) {      // 노드가 다른 노드를 가리키고 있을 경우 반복
		prev = p;           // 현재 노드를 임시로 다른 포인터 변수에 저장
		p = p->rlink;       // 다음 노드를 현재 노드로 설정
		free(prev);         // 임시로 저장한 포인트 변수에 대한 메모리 해제
	}
	free(h);                // 헤드에 대한 메모리 해제
	return 0;
}

void printList(headNode* h) {              // 연결 리스트 출력
	int i = 0;
	listNode* p;                           // 헤드에 대한 포인트 변수

	printf("\n---PRINT\n");

	if(h == NULL) {                        // 연결 리스트에 대한 메모리 할당이 없는 경우
		printf("Nothing to print....\n");
		return;                            // 함수 종료
	}

	p = h->first;                          // p이 첫 노드를 가리키도록 설정

	while(p != NULL) {                     // p가 할당된 메모리가 아닐 경우 반복
		printf("[ [%d]=%d ] ", i, p->key); // [ [i]="노드 p의 key값]의 형태로 출력 
		p = p->rlink;                      // p가 다음 노드를 가리키도록 설정
		i++;
	}

	printf("  items = %d\n", i);           // 링크드 리스트에 대한 노드의 갯수 출력
}

int insertLast(headNode* h, int key) {                    // 링크드 리스트의 마지막에 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode의 사이즈 만큼 동적 메모리 할당하여 변수 node에 대입
	node->key = key;                                      // 입력받은 key값을 노드의 key값에 대입
	node->rlink = NULL;                                   // 노드의 오른쪽 링크를 NULL로 초기화
	node->llink = NULL;                                   // 노드의 왼쪽 링크를 NULL로 초기화

	if (h->first == NULL){                                // 헤드가 가리키는 노드가 없을 경우
		h->first = node;                                  // 노드를 링크드 리스트의 첫 노드로 삽입
		return 0;
	}

	listNode* n = h->first;                               // n이 첫 노드를 가리키도록 설정
	while(n->rlink != NULL) {                             // n의 오른쪽 링크가 가리키는 메모리가 할당된 메모리일 경우
		n = n->rlink;                                     // n에 다음 노드의 주소값을 넘김
	}
	n->rlink = node;                                      // 삽입할 노드를 기존 마지막 노드의 다음 노드로 설정
	node->llink = n;                                      // 삽입할 노드의 이전 노드로 기존의 마지막 노드를 설정
	return 0;
}

int deleteLast(headNode* h) {           // 링크드 리스트의 마지막 노드 삭제

	if (h->first == NULL) {             // 헤드가 가리키는 메모리가 없을 경우
		printf("nothing to delete.\n");
		return 0;                       // 함수 종료
	}

	listNode* n = h->first;             // 첫 노드를 가리키는 포인터 변수
	listNode* trail = NULL;             // n의 앞 노드를 가리키는 포인터 변수

	if(n->rlink == NULL) {              // n의 다음 노드가 없을 경우
		h->first = NULL;                // 헤드를 NULL로 초기화
		free(n);                        // n에 대한 동적 메모리 해제
		return 0;
	}

	while(n->rlink != NULL) {           // n의 다음 노드가 있을 경우 반복
		trail = n;                      // 현재 노드를 trail에 대입
		n = n->rlink;                   // 다음 노드의 주소를 n에 대입
	}

	trail->rlink = NULL;                // 마지막 노드의 앞 노드(trail)의 오른쪽 링크를 NULL로 초기화
	free(n);                            // 마지막 노드에 대한 동적 메모리 해제

	return 0;
}

int insertFirst(headNode* h, int key) {                   // 링크드 리스트의 처음에 노드 삽입

	// 삽입할 노드에 대한 동적 메모리 할당 및 key값 및 양쪽 link값 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL; 

	// 링크드 리스트가 비어 있는 경우 삽입할 노드를 첫 노드로 설정
	if(h->first == NULL){ 
		h->first = node;
		return 1;
	}

	node->rlink = h->first;                               // 헤드가 삽입할 노드를 가리키도록 설정
	node->llink = NULL;                                   // 삽입할 노드의 이전 link값을 NULL로 초기화

	listNode *p = h->first;                               // p이 첫 노드를 가리키도록 설정
	p->llink = node;                                      // 첫 노드의 왼쪽 링크를 삽입할 노드로 설정
	h->first = node;                                      // 헤드가 삽입할 노드를 가리키도록 설정

	return 0;
}

int deleteFirst(headNode* h) {          // 첫 노드 삭제

	// 링크드 리스트가 비어 있는 경우
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;             // 첫 노드를 가리키는 포인터 변수 n
	h->first = n->rlink;                // 헤드가 두 번째 노드(n->rlink가 가리키는 노드)를 가리키도록 설정설정

	free(n);                            // 첫 노드에 대한 동적 메모리 해제

	return 0;
}

int invertList(headNode* h) {             // 링크드 리스트의 처음에 노드 삽입

	// 링크드 리스트가 비어 있는 경우
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;               // n(현재 노드)이 첫 노드를 가리키도록 설정
	listNode *trail = NULL;               // 이전 노드를 가리키는 포인터 변수
	listNode *middle = NULL;              // 현재 노드를 가리키는 포인터 변수
 
	while(n != NULL){                     // n이 비어 있지 않을 경우 반복
		trail = middle;                   // middle을 trail에 저장
		middle = n;                       // 현재 노드를 middle에 저장
		n = n->rlink;                     // 다음노드를 n에 저장
		middle->rlink = trail;            // trail을 middle(현재 노드)의 오른쪽 노드로 저장
		middle->llink = n;                // n을 middle(현재 노드)의 왼쪽 노드로 저장
	}

	h->first = middle;                    // 헤드가 마지막 노드를 가리키도록 설정

	return 0;
}

int insertNode(headNode* h, int key) {                    // key값의 크기 순서에 따른 노드 삽입

	// 삽입할 노드에 대한 동적 메모리 할당 및 key값 및 양쪽 link값 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL){                                // 링크드 리스트가 비어 있는 경우
		h->first = node;                                  // 헤드가 삽입할 노드를 가리키도록 함
		return 0;
	}

	listNode* n = h->first;                               // n이 첫 노드를 가리키도록 설정

	while(n != NULL) {                                    // 노드가 비어 있지 않을 경우 반복

		if(n->key >= key) {                               // 입력한 key값보다 큰 key값을 가진 노드가 있을 경우

			if(n == h->first) {                           // 첫 노드가 큰 경우
				insertFirst(h, key);                      // 삽입할 노드를 첫 노드로 설정
			}
			else {                                        // 첫 노드가 아닌 노드가 큰 경우
				node->rlink = n;                          // 큰 노드를 삽입할 노드의 다음 노드로 설정
				node->llink = n->llink;                   // 삽입할 노드의 왼쪽 링크를 큰 노드의 왼쪽 링크로 설정
				n->llink->rlink = node;                   // 삽입할 노드의 왼쪽 링크의 오른쪽 링크를 삽입할 노드로 설정
			}

			return 0;
		}

		n = n->rlink;                                     // n의 다음 노드를 n으로 설정
	}

	// 삽입할 노드의 key값보다 큰 key을 찾지 못한 경우
	insertLast(h, key);                                   // 링크드 리스트의 마지막 노드로 삽입
	return 0;
}

int deleteNode(headNode* h, int key) {                  // 인자로 받은 key값과 동일한 key값을 가진 노드 삭제

	// 링크드 리스트가 비어 있는 경우
	if (h->first == NULL){
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;                             // n이 첫 노드를 가리키도록 설정

	while(n != NULL) {                                  // n이 비어 있지 않을 경우

		if(n->key == key) {                             // 입력한 key값과 동일한 key이 있을 경우

			if(n == h->first) {                         // 동일한 key가 첫 노드에 해당하는 경우
				deleteFirst(h);                         // 첫 노드 삭제 함수 실행
			} 
			else if (n->rlink == NULL){                 // 동일한 key가 마지막 노드에 해당하는 경우
				deleteLast(h);                          // 마지막 노드 삭제 함수 실행
			} 
			else {                                      // 동일한 key가 중간 노드에 해당하는 경우
				n->llink->rlink = n->rlink;             // 앞 노드의 오른쪽 링크를 현재 노드의 오른쪽 링크로 변경
				n->rlink->llink = n->llink;             // 뒷 노드의 왼쪽 링크를현재 노드의 왼쪽 링크로 변경
				free(n);                                // 현재 노드 메모리 해제
			}

			return 1;
		}

		n = n->rlink;                                   // 다음 노드를 현재 노드로 설정
	}

	printf("cannot find the node for key = %d\n", key); // 입력한 key값과 일치하는 노드가 없음
	return 1;
}