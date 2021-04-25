/*
	# �� ��

	1) ���� ī�带 �� �� �����´�.

	2) ���ϴ� ���ڸ�ŭ �߰��� ī�带 ������ �� �ִ�.

	3) ������ ī���� ���� ����ؼ� 21�� ����� ���� �¸�,
	   21�� �� ���̶�� �Ѵ�.

	4) ī���� ���� 22�̻��̸� �й��Ѵ�.

	5) J(��), Q(��), K(ŷ)�� 10���� ����Ѵ�.

	6) A(���̽�)�� 1�� 11 �߿��� ������ �� ������,
	   �ڵ����� ������ ���ڷ� ���ȴ�.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// �� �� ī���� ���
#define CMAX 52
// Ű����� �Է��� �� �ִ� ������ ũ��
#define BUFF_SIZE 256

// ������ ī�带 ������ ����ü
struct input
{
	// ������ ����
	int card[CMAX];
	// ī���� ��
	int num;
};

// ��ǻ�Ͱ� ī�带 ��������
int comp(void);
// ����� ī�带 ��������
int getcard(struct input* inp_card);
// ������ ī�带 ���
void print_card(const struct input* inp_card, const char* card[]);
// ���� ���
int calc(const struct input* inp_card);

// ������ �ʱ�ȭ
#define randmize() srand(time(NULL))

int main()
{
	// ī�� ����
	const static char* card[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	// ������ ī��
	int x;
	// ��ǻ���� ����
	int c_score;
	// ����� ����
	int h_score;
	// �Է��� ���ڿ�
	char in[BUFF_SIZE];
	// ����� ������ ī��
	struct input h_card = { {0},0 };

	printf("�� �� ���� \n");
	randmize();
	c_score = comp();

	x = getcard(&h_card);
	printf("'%s'��(��) ���������ϴ�. \n", card[x]);
	printf("�� �� �� �������ڽ��ϱ�? (y/n): ");

	while (h_card.num < CMAX && fgets(in, BUFF_SIZE, stdin) != NULL)
	{
		if (strcmp(in, "y", 1) == 0)
		{
			x = getcard(&h_card);
			printf("'%s'��(��) ���������ϴ�.", card[x]);
			print_card(&h_card, card);
			printf("�� �� �� �������ڽ��ϱ�? (y/n): ");
		}
		else if (strncmp(in, "n", 1) == 0)
			break;
		else
			printf("y �Ǵ� n�� �Է��ϼ���. \n");
	}

	h_score = calc(&h_card);
	printf("����� %d���Դϴ�. ��ǻ�ʹ� %d���Դϴ�. \n", h_score, c_score);

	if (c_score <= 21 && (h_score > 21 || c_score > h_score))
		printf("��ǻ�Ͱ� �̰���ϴ�! \n");
	else if (h_score <= 21 && (c_score > 21 || h_score > c_score))
		printf("����� �̰���ϴ�! \n");
	else
		printf("���º� \n");

	return 0;
}

int comp(void)
{
	return rand() % 8 + 16;
}

int getcard(struct input* h_card)
{
	// ������ ī��
	int x;

	x = rand() % 13 + 1;
	h_card->card[h_card->num] = x;
	++(h_card->num);

	return x;
}

void print_card(const struct input* inp_card, const char* card[])
{
	// �ݺ����� ����
	int i;

	printf("���ݱ��� ������ ī���");
	for (i = 0; i < inp_card->num; ++i)
		printf("%s ", card[inp_card->card[i]]);
	printf("�Դϴ�. \n");
}

int calc(const struct input* inp_card)
{
	// ī���� ����:			     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,  J,  Q,  K
	const static int ncard[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
	// �ݺ����� ����
	int i;
	// A ī���� ���
	int n1 = 0;
	// �հ� ����
	int score = 0;

	for (i = 0; i < inp_card->num; i++)
	{
		score += ncard[inp_card->card[i]];
		// ī�尡 A�� ���
		if (inp_card->card[i] == 1)
			++n1;
	}
	// ī�尡 A�� ����� ���� ó��
	while (n1-- > 0)
		if (score <= (21 - 10))
			score += 10;

	return score;
}