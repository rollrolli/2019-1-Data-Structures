#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>

#define MAX_SIZE 50
#define COMPARE(x, y) ( ((x)<(y)) ? -1 : (((x)==(y)) ? 0 : 1))

typedef enum { head_, entry_ } tagfield;
typedef struct matrixNode *matrixPointer;
typedef struct entryNode {
	int row;
	int col;
	int value;
} entryNode;

typedef struct matrixNode {
	matrixPointer down;
	matrixPointer right;
	tagfield tag;
	union {
		matrixPointer next;
		entryNode entry;
	} u;
} matrixNode;

matrixPointer hdnode[4][MAX_SIZE];

matrixPointer mread(int hdnode_idx);
void mwrite(matrixPointer node);
void merase(matrixPointer *node, int hdnode_idx);
matrixPointer madd(matrixPointer a, matrixPointer b, int hdnode_idx_a, int hdnode_idx_b);
matrixPointer mmult(matrixPointer a, matrixPointer b, int hdnode_idx_a, int hdnode_idx_b);
matrixPointer mtranspose(matrixPointer a, matrixPointer c, int hdnode_idx_before, int hdnode_idx_after);

// hdnode 배열을 이차원 배열로 만들어 행렬 각각에 다른 인덱스를 사용하였습니다.


int main() {


	printf("***************************************************************************************\n");
	printf("                               희소행렬의 각종 연산\n");
	printf("                                                                자료구조 2차 Assignment\n");
	printf("                                                                    컴퓨터학과 이소라\n\n");
	printf("***************************************************************************************\n");

	printf("메뉴선택-------------------------------------------------------------------------------\n");
	printf("              [1] 희소 행렬 입력하기         [2] 끝내기\n");
	printf("---------------------------------------------------------------------------------------\n\n");
	printf("------(원하는 메뉴를 선택해 주세요)------>> ");


	int input = 0;
	scanf("%d", &input);

	while (1) {

		if (input == 1) break;
		else if (input == 2) {
			printf("\n프로그램이 종료되었습니다.\n\n");
			system("pause");

			return 0;
		}
		else {
			printf("\n올바른 값을 다시 입력해주세요.\n\n");
			scanf("%d", &input);
		}
	} // 올바른 값이 들어올 때까지 반복

	matrixPointer a;
	a = (matrixPointer)malloc(sizeof(matrixNode));

	a = mread(0);
	// 첫번째 입력받은 행렬은 a, hdnode index는 항상 0을 사용

	mwrite(a);


	printf("두번째 메뉴선택-----------------------------------------------------------------------\n");
	printf("  [1] 두번째 희소 행렬 입력(덧셈, 곱셈)  [2] 첫번째 입력 행렬 Transpose  [3] 끝내기\n");
	printf("--------------------------------------------------------------------------------------\n\n");
	printf("------(원하는 메뉴를 선택해 주세요)------>> ");

	scanf("%d", &input);
	int flag = 0;

	matrixPointer b, c, d;
	b = (matrixPointer)malloc(sizeof(matrixNode));
	c = (matrixPointer)malloc(sizeof(matrixNode));
	d = (matrixPointer)malloc(sizeof(matrixNode));


	while (1) {

		if (input == 1 || input == 2) break;
		else if (input == 3) {
			printf("\n프로그램이 종료되었습니다.\n\n");
			system("pause");

			return 0;
		}
		else {
			printf("\n올바른 값을 다시 입력해주세요.\n\n");
			scanf("%d", &input);
		}
	} // 올바른 값이 들어올 때까지 반복

	if (input == 1) {
		b = mread(1);
		// 두번째 입력받은 행렬은 b, hdnode index는 항상 1을 사용

		mwrite(b);




		printf("세번째 메뉴선택--------------------------------------------------------------------\n");
		printf("        [1] 두 행렬 간의 덧셈 연산   [2] 두 행렬 간의 곱셈 연산 [3] 끝내기\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("------(원하는 메뉴를 선택해 주세요)------>> ");

		scanf("%d", &input);

		if (input == 1) {
			
			if ((a->u.entry.row != b->u.entry.row || a->u.entry.col != b->u.entry.col)) {
				printf("***Warnig!!! 행렬 덧셈 연산 시 각각의 행의 수 또는 열의 수가 일치하지 않으면 연산이 불가능합니다!\n");
				printf("----<종료 후 다시 시작해주세요: 0입력>------>>");
				scanf("%d", &input);
				if (input == 0) return 0;
			} // 덧셈 연산 시 행과 열의 개수가 다른 경우 메시지 출력 
			else {
				d = madd(a, b, 0, 1);
			} // a의 hdnode index는 0, b의 hdnode index는 1
 		}

		else if (input == 2) {
			if (a->u.entry.col != b->u.entry.row) {
				printf("***Warnig!!! 행렬 곱셈 연산 시 열과 행의 수가 일치하지 않으면 연산이 불가능합니다!\n");
				printf("----<종료 후 다시 시작해주세요: 0 입력>------>>");
				scanf("%d", &input);
				if (input == 0) return 0;
			} // 곱셈 연산 시 a의 열의 수와 b의 행의 수가 다르면 메시지 출력
			else {
				d = mmult(a, b, 0, 1);
			} // a의 hdnode index는 0, b의 hdnode index는 1
		}

	}
	
	else if (input == 2) {
		d = mtranspose(a, c, 0, 3);
	} // transpose된 새로운 행렬은 hdnode index 3에 저장

	mwrite(d);

	if (!a) merase(a, 0);
	if (!b) merase(b, 1);
	if (!d) merase(d, 2);
	// 사용했던 행렬 merase

	printf("\n(희소 행렬 연산이 종료되었습니다. 0을 입력하면 종료됩니다.)------>>");
	scanf("%d", &input);
	if (input == 0) return 0;


	system("pause");

}


void attach(matrixPointer* node, int row, int col, int value, int head) {
	*node = (matrixPointer)malloc(sizeof(matrixNode));
	if (head) (*node)->tag = head_;
	else if (!head) (*node)->tag = entry_;
	(*node)->u.entry.row = row;
	(*node)->u.entry.col = col;
	(*node)->u.entry.value = value;
}
// entry node 저장 함수
// head == 1일 때는 header of header 노드
// head == 0일 때는 element 노드

matrixPointer mread(int hdnode_idx) {
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	char c;
	matrixPointer temp, last, node;

	printf("**행,열 그리고 0이 아닌 값의 개수 입력(예시:3/2/6, 반드시 형식에 맞춰주세요.)**\n");
	printf("--------------->>");
	scanf("%d%c%d%c%d", &numRows, &c, &numCols, &c, &numTerms);
	numHeads = (numCols > numRows) ? numCols : numRows;

	attach(&node, numRows, numCols, numTerms, 1);
	// header of header node를 entry형 노드로 만들어 값 넣기

	if (!numHeads) node->right = node;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = (matrixPointer)malloc(sizeof(matrixNode));
			hdnode[hdnode_idx][i] = temp;
			hdnode[hdnode_idx][i]->tag = head_;
			hdnode[hdnode_idx][i]->right = temp;
			hdnode[hdnode_idx][i]->u.next = temp;
		} // header node setting

		currentRow = 0;
		last = hdnode[hdnode_idx][0]; // last node : currentRow의 마지막 node
		printf("**순서대로 행,열,값을 입력(예시:0/0/6, 반드시 형식과 순서를 지켜주세요.)**\n\n");
		
		for (i = 0; i < numTerms; i++) {
			printf("%d번째 원소---------->> ", i+1);
			scanf("%d%c%d%c%d", &row, &c, &col, &c, &value);
			if (row > currentRow) {
				last->right = hdnode[hdnode_idx][currentRow];
				currentRow = row;
				last = hdnode[hdnode_idx][row];
			} // 입력된 원소의 row가 currentRow보다 큰 경우 건너뜀
			attach(&temp, row, col, value, 0);
			last->right = temp;
			last = temp;
			// 새로 만든 노드를 currentRow 끝에 붙여줌
			hdnode[hdnode_idx][col]->u.next->down = temp;
			hdnode[hdnode_idx][col]->u.next = temp;
			// 새로 만든 노드를 column 방향으로도 연결
		}
		last->right = hdnode[hdnode_idx][currentRow];
		// 맨 마지막 원소의 right에 그 row의 header node 넣음

		for (i = 0; i < numCols; i++) {
			hdnode[hdnode_idx][i]->u.next->down = hdnode[hdnode_idx][i];
		} // hdnode끼리 column 방향으로 연결
		for (i = 0; i < numHeads - 1; i++) {
			hdnode[hdnode_idx][i]->u.next = hdnode[hdnode_idx][i+1];
		} // hdnode끼리 row 방향으로 연결
		hdnode[hdnode_idx][numHeads - 1]->u.next = node;
		node->right = hdnode[hdnode_idx][0];
	}
	return node;


}


void mwrite(matrixPointer node) {
	int i;
	matrixPointer temp, head = node->right;
	printf("\n입력하신 행렬 <행의수 = %d, 열의수 = %d, 인자수 = %d> **\n\n",
		node->u.entry.row, node->u.entry.col, node->u.entry.value);
	printf("입력하신(또는 연산) 행렬의 행과 열 그리고 그 값----------->>\n\n");
	for (i = 0; i < node->u.entry.row; i++) {
		for (temp = head->right; temp != head; temp = temp->right) {
			printf("%5d%5d%5d\n", 
				temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		} // 다시 head로 돌아올 때까지 계속 출력
		head = head->u.next;
		// 다시 head로 돌아오면 다음 head로 이동
	}
	printf("\n");
}

void merase(matrixPointer *node, int hdnode_idx)
{
	matrixPointer x, y;
	int i, numHeads;
	if (!(*node)) {
		for (i = 0; i < (*node)->u.entry.row; i++) {
			y = hdnode[hdnode_idx][i]->right;
			while (y != hdnode[hdnode_idx][i]) {
				x = y;
				y = y->right;
				free(x);
			}
		}

		numHeads = ((*node)->u.entry.row > (*node)->u.entry.col) ?
			(*node)->u.entry.row : (*node)->u.entry.col;
		for (i = 0; i < numHeads; i++)
			free(hdnode[hdnode_idx][i]);
		*node = NULL;
	}
}

matrixPointer mtranspose(matrixPointer a, matrixPointer c, 
	int hdnode_idx_before, int hdnode_idx_after) {
	
	
	matrixPointer newNode, temp, last, nodeToCopy, head;


	int i, j, currentRow;
	int numCols = a->u.entry.row;
	int numRows = a->u.entry.col;
	int numTerms = a->u.entry.value;
	int numHeads = (numCols > numRows) ? numCols : numRows;

	attach(&c, numRows, numCols, numTerms, 1);
	int row, col, value;


	if (!numHeads) c->right = c;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = (matrixPointer)malloc(sizeof(matrixNode));
			hdnode[hdnode_idx_after][i] = temp;
			hdnode[hdnode_idx_after][i]->tag = head_;
			hdnode[hdnode_idx_after][i]->right = temp;
			hdnode[hdnode_idx_after][i]->u.next = temp;
		} // hdnode 세팅

		currentRow = 0;
		last = hdnode[hdnode_idx_after][0];		// last : currentRow의 마지막 node
		head = hdnode[hdnode_idx_before][0];	// head : currentRow의 header node
		nodeToCopy = head->down;				// 원래 행렬에서 copy할 노드

		for (j = 0; j < a->u.entry.col; j++) {
			nodeToCopy = head->down;
			if (nodeToCopy == head) {			// 다시 head로 돌아왔을 때
				head = head->u.next;			// 다음 head로 이동
				nodeToCopy = head->down;		// copy할 노드로 다음 head의 자식 설정 
				continue;
			}
			if (head == a) break;
			for (i = 0; i < numTerms; i++) {

				row = nodeToCopy->u.entry.col;
				col = nodeToCopy->u.entry.row;
				value = nodeToCopy->u.entry.value;
				// 값은 그대로, 좌표만 뒤바뀌도록


				if (row > currentRow) {
					last->right = hdnode[hdnode_idx_after][currentRow];
					currentRow = row;
					last = hdnode[hdnode_idx_after][row];
				}
				// nodeToCopy의 row값이 currentRow보다 크면
				// currentRow 마무리하고 다음 currentRow로 row 채택 

				attach(&temp, row, col, value, 0);
				last->right = temp;
				last = temp;
				hdnode[hdnode_idx_after][col]->u.next->down = temp;
				hdnode[hdnode_idx_after][col]->u.next = temp;
				// currentRow에 새로 입력 들어온 node 만들어서 붙임

				
				if (nodeToCopy->down == head) {
					break;
				} // nodeToCopy가 currentRow의 마지막 노드면 break
				nodeToCopy = nodeToCopy->down;
				// currentRow의 마지막 노드가 아니면 다음 노드로 진행
			}
			head = head->u.next;
		}

		
		last->right = hdnode[hdnode_idx_after][currentRow];
		// 맨 마지막 원소의 right에 그 row의 header node 넣음

		for (i = 0; i < numCols; i++) {
			hdnode[hdnode_idx_after][i]->u.next->down = hdnode[hdnode_idx_after][i];
		}
		for (i = 0; i < numHeads - 1; i++) {
			hdnode[hdnode_idx_after][i]->u.next = hdnode[hdnode_idx_after][i + 1];
		}
		hdnode[hdnode_idx_after][numHeads - 1]->u.next = c;
		c->right = hdnode[hdnode_idx_after][0];
	}

	return c;

}

matrixPointer madd(matrixPointer a, matrixPointer b, int hdnode_idx_a, int hdnode_idx_b) {
	int i, j;
	matrixPointer temp1, temp2, head_a, head_b, head_d, last;
	matrixPointer d, temp;
	int sum, value = 0;
	int currentRow;

	int numCols = a->u.entry.row;
	int numRows = a->u.entry.col;
	int numHeads = (numCols > numRows) ? numCols : numRows;

	attach(&d, a->u.entry.row, a->u.entry.col, 0, 1);

	if (!numHeads) d->right = d;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = (matrixPointer)malloc(sizeof(matrixNode));
			hdnode[2][i] = temp;
			hdnode[2][i]->tag = head_;
			hdnode[2][i]->right = temp;
			hdnode[2][i]->u.next = temp;
		} // header node 세팅

		head_a = hdnode[hdnode_idx_a][0];	temp1 = head_a->right;
		head_b = hdnode[hdnode_idx_b][0];	temp2 = head_b->right;
		head_d = hdnode[2][0];				temp = head_d;
		// 행렬 a와 b 그리고 답을 적을 d의 head 노드를 각각
		// head_a, head_b, head_d에 저장하고
		// 현재 보고 있는 노드를 temp1, temp2, temp로 나타냄

		last = hdnode[2][0];
		// last에 row 0의 헤더를 넣어 hdnode[2]에 새 노드 붙일 준비
		d->right = hdnode[2][0];
		// d와 hdnode[2] 연결


		currentRow = 0;

		for (i = 0; i < a->u.entry.value;) {
			for (j = 0; j < b->u.entry.value;) {
				if (temp1 == head_a) {		// 행렬 a row에서 한바퀴 돌아 header가 되었을 떄
					for (; temp2 != head_b; temp2 = temp2->right) {
						attach(&temp, temp2->u.entry.row, temp2->u.entry.col,
							temp2->u.entry.value, 0);	// 남은 b의 요소들을 추가
						last->right = temp;
						last = temp;
						value++;	// 전체 element의 수을 알 수 없으므로 하나하나 세어줌
						hdnode[2][temp2->u.entry.col]->u.next->down = temp;
						hdnode[2][temp2->u.entry.col]->u.next = temp;
						// 새로 추가해준 b의 요소들을 끝에 붙임
					}
					last->right = hdnode[2][currentRow];
					// last의 오른쪽에 다시 헤더노드 붙여줌

					head_a = head_a->u.next;
					head_b = head_b->u.next;
					currentRow++;
					
					temp1 = head_a->right;
					temp2 = head_b->right;
					last = hdnode[2][currentRow];
					head_d = hdnode[2][currentRow];
					temp = head_d;
					// 다음 row로 이동


					if (head_a == a || head_b == b) break;
					// header가 한바퀴 돌아 header of header가 되는 경우 break

				}
				if (temp2 == head_b) {	// 행렬 b row에서 한바퀴 돌아 header 되었을 때
					for (; temp1 != head_a; temp1 = temp1->right) {
						attach(&temp, temp1->u.entry.row, temp1->u.entry.col,
							temp1->u.entry.value, 0);
						// 남은 a element들 추가해줌
						value++;
						last->right = temp;
						last = temp;
						hdnode[2][temp1->u.entry.col]->u.next->down = temp;
						hdnode[2][temp1->u.entry.col]->u.next = temp;
						// 이 부분 제외하면 위의 내용과 동일
					}
					last->right = hdnode[2][currentRow];

					head_a = head_a->u.next;
					head_b = head_b->u.next;
					currentRow++;

					temp1 = head_a->right;
					temp2 = head_b->right;

					last = hdnode[2][currentRow];
					head_d = hdnode[2][currentRow];
					temp = head_d;

					if (head_a == a || head_b == b) break;

				}

				else {
					int t = 0;
					t = COMPARE(temp1->u.entry.col, temp2->u.entry.col);
					
					if (t == 1) { // 왼쪽이 더 큼
						attach(&temp->right, temp2->u.entry.row, temp2->u.entry.col,
							temp2->u.entry.value, 0);
						// col이 작은 쪽은 바로 붙여줌
						value++;
						temp = temp->right;
						last->right = temp;
						last = temp;
						temp2 = temp2->right;
						// col 작았던 쪽을 다음 칸으로 이동시킴
						temp->right = hdnode[2][currentRow];
					}
					else if (t == 0) {	// 두 값이 같음
						attach(&temp->right, temp1->u.entry.row, temp1->u.entry.col,
							temp1->u.entry.value + temp2->u.entry.value, 0);
						// col이 같으면 value의 합을 붙여줌
						value++;
						temp = temp->right;
						last->right = temp;
						last = temp;
						temp1 = temp1->right; temp2 = temp2->right;
						temp->right = hdnode[2][currentRow];
					}
					else if (t == -1) {		// 오른쪽이 더 큼
						attach(&temp->right, temp1->u.entry.row, temp1->u.entry.col,
							temp1->u.entry.value, 0);
						// col이 작은 쪽은 바로 붙여줌
						value++;
						temp = temp->right;
						last->right = temp;
						last = temp;
						temp1 = temp1->right;
						// col 작았던 쪽을 다음 칸으로 이동시킴
						temp->right = hdnode[2][currentRow];

					}
				}
				last->right = hdnode[2][currentRow];
			}
			for (i = 0; i < numCols; i++) {
				hdnode[2][i]->u.next->down = hdnode[2][i];
			}
			for (i = 0; i < numHeads - 1; i++) {
				hdnode[2][i]->u.next = hdnode[2][i + 1];
			}
			hdnode[2][numHeads - 1]->u.next = d;
			d->right = hdnode[2][0];

			d->u.entry.value = value;
			return d;
		}
	}

};
matrixPointer mmult(matrixPointer a, matrixPointer b, int hdnode_idx_a, int hdnode_idx_b) {
	matrixPointer newB, d;
	newB = (matrixPointer)malloc(sizeof(matrixNode));
	
	
	newB = mtranspose(b, newB, 1, 3);
	//newB의 헤더노드 인덱스는 3

	int i, j;
	matrixPointer temp1, temp2, head_a, head_b, head_d, last, temp;
	
	int sum = 0, value = 0;
	int currentRow, currentCol;

	int numRows = a->u.entry.row;
	int numCols = b->u.entry.col;
	int numHeads = (numCols > numRows) ? numCols : numRows;

	attach(&d, a->u.entry.row, b->u.entry.col, 0, 1);

	if (!numHeads) d->right = d;
	else {
		for (i = 0; i < numHeads; i++) {
			temp = (matrixPointer)malloc(sizeof(matrixNode));
			hdnode[2][i] = temp;
			hdnode[2][i]->tag = head_;
			hdnode[2][i]->right = temp;
			hdnode[2][i]->u.next = temp;
		} // header node setting

		head_a = hdnode[hdnode_idx_a][0]; 	head_b = hdnode[3][0];  head_d = hdnode[2][0];
		last = hdnode[2][0];
		d->right = hdnode[2][0];
		temp1 = head_a->right; temp2 = head_b->right; temp = head_d;
		
		currentRow = 0;
		currentCol = 0;

		for (i = 0; i < a->u.entry.value;) {			
			for (j = 0; j < b->u.entry.value;) {
				if (temp1 == head_a || temp2 == head_b) {
					if (sum) {
						attach(&temp, currentRow, currentCol, sum, 0); value++;
						last->right = temp;
						last = temp;
						last->right = hdnode[2][currentRow];
					} // sum이 0이 아니면 currentRow, currentCol에 붙여줌
					sum = 0;	// sum 초기화
					
					hdnode[2][currentCol]->u.next->down = temp;
					hdnode[2][currentCol]->u.next = temp;
					currentCol++;

					if (currentCol == numCols) { // currentRow에 대해 column 계산 끝
						currentRow++; currentCol = 0;
						head_b = hdnode[3][0];
						if (currentRow == numRows) break;
						// currentRow도 끝났으면 모든 계산 끝
						else {
							head_a = hdnode[hdnode_idx_a][currentRow];
							head_d = hdnode[2][currentRow];
							last = hdnode[2][currentRow];
						} // currentCol만 끝났으면 새로운 row 계산할 준비
					}
					head_b = hdnode[3][currentCol];
					temp1 = head_a->right; temp2 = head_b->right;
				}
				
				else {
					int t = COMPARE(temp1->u.entry.col, temp2->u.entry.col);
					// a의 row와 b의 col 비교
					if (t == 1) { // a의 col > b의 row
						temp2 = temp2->right;
					}
					else if (t == 0) {	// a의 col == b의 row
						sum += temp1->u.entry.value * temp2->u.entry.value;
						temp1 = temp1->right;
						temp2 = temp2->right;
					}
					else if (t == -1) {	// a의 col < b의 row
						temp1 = temp1->right;
					}
				}
			}

			for (i = 0; i < numCols; i++) {
				hdnode[2][i]->u.next->down = hdnode[2][i];
			}
			for (i = 0; i < numHeads - 1; i++) {
				hdnode[2][i]->u.next = hdnode[2][i + 1];
			}
			hdnode[2][numHeads - 1]->u.next = d;
			d->right = hdnode[2][0];

			d->u.entry.value = value;
			merase(newB, 3);
			return d;
		}
	}

	return d;
};