/*
	# 블랙 잭

	1) 먼저 카드를 한 장 가져온다.

	2) 원하는 숫자만큼 추가로 카드를 가져올 수 있다.

	3) 가져온 카드의 합을 계산해서 21에 가까운 쪽이 승리,
	   21을 블랙 잭이라고 한다.

	4) 카드의 합이 22이상이면 패배한다.

	5) J(잭), Q(퀸), K(킹)은 10으로 계산한다.

	6) A(에이스)는 1과 11 중에서 선택할 수 있으며,
	   자동으로 유리한 숫자로 계산된다.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 블랙 잭 카드의 장수
#define CMAX 52
// 키보드로 입력할 수 있는 버퍼의 크기
#define BUFF_SIZE 256

// 가져온 카드를 저장할 구조체
struct input
{
	// 가져온 가드
	int card[CMAX];
	// 카드의 수
	int num;
};

// 컴퓨터가 카드를 가져간다
int comp(void);
// 사람이 카드를 가져간다
int getcard(struct input* inp_card);
// 가져간 카드를 계산
void print_card(const struct input* inp_card, const char* card[]);
// 득점 계산
int calc(const struct input* inp_card);

// 난수의 초기화
#define randmize() srand(time(NULL))

int main()
{
	// 카드 종류
	const static char* card[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	// 가져간 카드
	int x;
	// 컴퓨터의 점수
	int c_score;
	// 사람의 점수
	int h_score;
	// 입력한 문자열
	char in[BUFF_SIZE];
	// 사람이 가져간 카드
	struct input h_card = { {0},0 };

	printf("블랙 잭 게임 \n");
	randmize();
	c_score = comp();

	x = getcard(&h_card);
	printf("'%s'을(를) 가져갔습니다. \n", card[x]);
	printf("한 장 더 가져가겠습니까? (y/n): ");

	while (h_card.num < CMAX && fgets(in, BUFF_SIZE, stdin) != NULL)
	{
		if (strcmp(in, "y", 1) == 0)
		{
			x = getcard(&h_card);
			printf("'%s'을(를) 가져갔습니다.", card[x]);
			print_card(&h_card, card);
			printf("한 장 더 가져가겠습니까? (y/n): ");
		}
		else if (strncmp(in, "n", 1) == 0)
			break;
		else
			printf("y 또는 n을 입력하세요. \n");
	}

	h_score = calc(&h_card);
	printf("당신은 %d점입니다. 컴퓨터는 %d점입니다. \n", h_score, c_score);

	if (c_score <= 21 && (h_score > 21 || c_score > h_score))
		printf("컴퓨터가 이겼습니다! \n");
	else if (h_score <= 21 && (c_score > 21 || h_score > c_score))
		printf("당신이 이겼습니다! \n");
	else
		printf("무승부 \n");

	return 0;
}

int comp(void)
{
	return rand() % 8 + 16;
}

int getcard(struct input* h_card)
{
	// 가져간 카드
	int x;

	x = rand() % 13 + 1;
	h_card->card[h_card->num] = x;
	++(h_card->num);

	return x;
}

void print_card(const struct input* inp_card, const char* card[])
{
	// 반복문의 변수
	int i;

	printf("지금까지 가져간 카드는");
	for (i = 0; i < inp_card->num; ++i)
		printf("%s ", card[inp_card->card[i]]);
	printf("입니다. \n");
}

int calc(const struct input* inp_card)
{
	// 카드의 점수:			     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,  J,  Q,  K
	const static int ncard[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
	// 반복문의 변수
	int i;
	// A 카드의 장수
	int n1 = 0;
	// 합계 점수
	int score = 0;

	for (i = 0; i < inp_card->num; i++)
	{
		score += ncard[inp_card->card[i]];
		// 카드가 A인 경우
		if (inp_card->card[i] == 1)
			++n1;
	}
	// 카드가 A인 경우의 득점 처리
	while (n1-- > 0)
		if (score <= (21 - 10))
			score += 10;

	return score;
}