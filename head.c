#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
typedef struct Node1 {
	int povorot;
	int line;//������
	int str;//����� ������
	int stl;//����� �������
	struct Node1 *next;
} Node1;
Node1 *First,*Last;
void push(int str,int stl)
{
	Node1 *tmp;
	tmp = (Node1*)malloc(sizeof(Node1));
	if (tmp == NULL)
	{
		printf("�� ������� �������� ������ ��� ������� ������.\n");
		system("pause");
		return;
	}
	tmp->str = str;
	tmp->stl = stl;
	tmp->next = NULL;

	if (First == NULL)
		First = Last = tmp;
	else
	{
		Last->next = tmp;
		Last = Last->next;
	}
}
void fon()
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 15;									// ��������� ���������� X
	position.Y = 10;									// ��������� ���������� Y
	SetConsoleCursorPosition(hConsole, position);		// ����������� ������� �� �������� �����������
	printf("SNAKE\n");
	position.X = 3;
	position.Y = 11;
	SetConsoleCursorPosition(hConsole, position);
	printf("'A' ������ ������������ ������\n");
	position.X = 3;
	position.Y = 12;
	SetConsoleCursorPosition(hConsole, position);
	printf("'D' ������ ������������ �������\n");
	for (int i = 0; i < 15; i++)//���
	{
		for (int j = 0; j < 35; j++)
		{
			position.X = 40+j;									// ��������� ���������� X
			position.Y = 5+i;									// ��������� ���������� Y
			SetConsoleCursorPosition(hConsole, position);		// ����������� ������� �� �������� �����������
			SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 0));
			printf(" ");
		}
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("\n");
	}
}
void main()
{
	char sr;
	int pushstr, pushstl,speed=0,pakfs=5;
	int line = 2,times=500, foodstr,linef=0,foodstl,str = 2,fpak=0, headstr=0,headstl=0,stl = 40,fkol=0, pointstr, pointstl, end = 0, fpr = 1, povorot = 0, fline = 0;
	int fpovorot1=0,fpovorot2=0;
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_ALL, "RUS");
	system("color F0");//�������� ���� ����� ����
	fon();
	Node1 *tmp;
    //������� ��������� 2 ������� ������
	push(5,41);
	push(5,40);
	//��������� ������������ ����
	tmp = First;
	tmp->line = 2;
	tmp -> povorot = 0;
	position.X = tmp->stl;
	position.Y = tmp->str;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 0));
	printf(" ");
	tmp = tmp->next;
	tmp->povorot = 0;
	tmp->line = 2;
	position.X = tmp->stl;
	position.Y = tmp->str;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
	printf(" ");
	//����������� ��� ��� ������
	srand(time(NULL));
	foodstr = 5 + rand() % 20;
	foodstl = 40 + rand() % 75;
	while (foodstl >= 75)
	{
		foodstl = 40 + rand() % 75;
	}
	while (foodstr >= 20)
	{
		foodstr = 5 + rand() % 20;
	}
	position.X = foodstl;
	position.Y = foodstr;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
	printf(" ");
	//
	Sleep(500);
	int linez;
	while (1)
	{
		while (!_kbhit())//���� ������ ������ �� ���������� �� ���������� �����
		{
			//���� �� ������ ������ �� ���������� ��������� �� ������
			tmp = First;
			tmp->line = line;
			tmp->povorot = povorot;
			//������
			fkol = 0;
			if (line == 1) tmp->str = tmp->str -1;
			else
			{
				if (line == 2) tmp->stl = tmp->stl + 1;
				else
				{
					if (line == 3) tmp->str = tmp->str + 1;
					else
					{
						if (line == 4) tmp->stl = tmp->stl - 1;
					}
				}
			}
			position.X = tmp->stl;
			position.Y = tmp->str;
			SetConsoleCursorPosition(hConsole, position);
			SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 0));//��������� � �������
			printf(" ");
			//�������� �� ������
			//1 �������� �� ������
			if ((tmp->stl > 74) || (tmp->stl < 40)) { end = 1; break; }
			if ((tmp->str > 19) || (tmp->str < 5)) { end = 1; break; }
			//2 �������� �� ��������
			headstr = tmp->str;
			headstl = tmp->stl;
			for (tmp=First->next;tmp!=NULL;tmp=tmp->next)
			{
				if ((tmp->str == headstr) && (tmp->stl == headstl))
					end = 1;
			}
			tmp = First;
			//�������� �� �������� ��� 
			if ((tmp->str == foodstr) && (tmp->stl == foodstl))
			{//�������� 1 ������� � ��������
				for (tmp = First; tmp->next != NULL; tmp = tmp->next);
				if (tmp->line == 1) { pushstr = tmp->str + 1; pushstl = tmp->stl; }
				else
				{
					if (tmp->line == 2) { pushstl = tmp->stl- 1; pushstr = tmp->str; }
					else
					{
						if (tmp->line == 3) { pushstr = tmp->str - 1; pushstl = tmp->stl;}
						else
						{
							if (tmp->line == 4) { pushstl = tmp->stl + 1; pushstr = tmp->str; }
						}
					}
				}
				linef = tmp->line;
				push(pushstr,pushstl);
				for (tmp = First; tmp->next != NULL; tmp = tmp->next);
				tmp ->line = linef;
				//������ ��� 
				speed++;
				if ((speed == pakfs)&&(fpak<40))
				{
					times = times - 50;
					pakfs = pakfs + 5;
				}
				foodstr = 5 + rand() % 20;
				foodstl = 40 + rand() % 75;
				int fffp1 = 0,fffp2=0;
				tmp = First;
				while (fffp1 == 0)
				{
					if ((foodstl == tmp->stl) && (foodstr == tmp->str))
					{
						fffp2 = 1; foodstl = 40 + rand() % 75;
						while (foodstl >= 75)
						{
							foodstl = 40 + rand() % 75;
						}
						foodstr = 5 + rand() % 20;
						while (foodstr >= 20)
						{
							foodstr = 5 + rand() % 20;
						}
					}
					if (tmp->next == NULL)
					{
						tmp = First;
						if (fffp2 == 0)fffp1 = 1;
						fffp2 = 0;
					}
					else
					tmp=tmp->next;
				}
				fffp1 = 0;
				while (foodstl >= 75)
				{
					foodstl = 40 + rand() % 75;
				}
				while (foodstr >= 20)
				{
					foodstr = 5 + rand() % 20;
				}
				position.X = foodstl;
				position.Y = foodstr;
				SetConsoleCursorPosition(hConsole, position);
				SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
				printf(" ");
			}
			for (tmp=First->next;tmp!=NULL;tmp=tmp->next)
			{
				if ((tmp->str==headstr)&&(tmp->stl==headstl))
				{
					end = 1;
					break;
				}
			}
			//��������
			for (tmp = First->next; tmp!= NULL; tmp = tmp->next)
			{
				if (tmp->povorot == 1)
				{
					if (tmp->line == 1) tmp->line = 4;
					else tmp->line--;
				}
				if (tmp->povorot == 2)
				{
					if (tmp->line == 4) tmp->line = 1;
					else tmp->line++;
				}
				if (tmp->line== 1) tmp->str = tmp->str - 1;
				else
				{
					if (tmp->line == 2) tmp->stl = tmp->stl + 1;
					else
					{
						if (tmp->line == 3) tmp->str = tmp->str + 1;
						else
						{
							if (tmp->line == 4) tmp->stl = tmp->stl - 1;
						}
					}
				}
				position.X = tmp->stl;
				position.Y = tmp->str;
				SetConsoleCursorPosition(hConsole, position);
				SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));//��������� � �����
				printf(" ");
				//����������� �� �������
				if (tmp->next == NULL)
				{
					if (tmp->line == 1) tmp->str = tmp->str + 1;
					else
					{
						if (tmp->line == 2) tmp->stl = tmp->stl - 1;
						else
						{
							if (tmp->line == 3) tmp->str = tmp->str - 1;
							else
							{
								if (tmp->line == 4) tmp->stl = tmp->stl + 1;
							}
						}
					}
					position.X = tmp->stl;
					position.Y = tmp->str;
					SetConsoleCursorPosition(hConsole, position);
					SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 0));//��������� � �����
					printf(" ");
					if (tmp->line == 1) tmp->str = tmp->str - 1;
					else
					{
						if (tmp->line == 2) tmp->stl = tmp->stl + 1;
						else
						{
							if (tmp->line == 3) tmp->str = tmp->str + 1;
							else
							{
								if (tmp->line == 4) tmp->stl = tmp->stl - 1;
							}
						}
					}
				}
			}
			//���������� �������
			tmp = First;
			fpovorot1 = tmp->povorot;
			tmp->povorot = 0;
			for (tmp = First->next; tmp != NULL; tmp = tmp->next)
			{
				fpovorot2 = tmp->povorot;
				tmp->povorot = fpovorot1;
				fpovorot1 = fpovorot2;
			}
			for (tmp = First->next; tmp != NULL; tmp = tmp->next)
			{
				if ((tmp->str == headstr) && (tmp->stl == headstl))
					end = 1;
			}
			tmp = First;
			Sleep(times);
			povorot = 0;
		}
		if (end == 1)//����� ����
		{
			position.X = 12;
			position.Y = 16;
			SetConsoleCursorPosition(hConsole, position);
			printf("�� ���������!\n");
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
			break;
		}
		sr = _getch();//���� ��� ������ ������� �� �����
		if ((sr == 'a')|| (sr == 'A'))//������
		{
			fkol++;
			if (fkol == 1)
			{
				tmp = First;
				tmp->line = line;
				if (line == 1) line = 4;
				else line = line - 1;
				fpr = 0;
				povorot = 1;
			}
		}
		if ((sr == 'd') || (sr == 'D'))//�������
		{
			fkol++;
			if (fkol == 1)
			{
				tmp = First;
				tmp->  line = line;
				if (line == 4) line = 1;
				else line = line + 1;
				fpr = 0;
				povorot = 2;
			}
		}
	}
	system("pause");
}