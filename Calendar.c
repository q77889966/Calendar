#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<Windows.h>
#include<Winnt.h>
int main() {
	SetConsoleTitle("月 历 打 印");
	char c;//键盘键入
	int year,month,i=0;
	char a[20]={0};

	printf("Pls input the year;\nPress [Enter] for now;\nPress [Esc] for exit.\n-->");

	while (1) {
		c = getch();
		
		if (c == 27) {                        //ESC
			exit(0);
		}

		else if (c >= '0' && c <= '9') {
			printf("%c", c);
			a[i] = c;
			i++;
			continue;
		}
		else if (c == 13||c==10) {            //ENTER
			if (strlen(a)!=0) {
				year = atoi(a);
				if (year >= 1 ) {

					printf("\nPls input the month:");

					while (1) {
						scanf_s("%d", &month);
						if (month >= 1 && month <= 12) {
							cal(year, month);
						}
						else {
							month = 0;
							printf("Error! Pls input the month again:");
						}
					}

				}
				else {
					printf("Error! Pls input the year again:");
				}
			}
			else {                  //当前时间
				time_t t;
				struct tm* ym;
				t = time(NULL);	
				ym = localtime(&t);	
				year = ym->tm_year + 1900;
				month = ym->tm_mon + 1;
				cal(year, month);
			}

		}
	}
	return 0;
}
int cal(int year, int month) {
	char a;
	if (year == 0)
		exit(0);
	//printf("%d %d",year,month);
	//printf("1");

	int days, week = 0, i, j = 0, m = month, y1 = year;               //days为当月天数,i为计数器，week为当月1号星期，j统计已经打印的数量，每7次换行
	int y = year % 100, c = year / 100;
	printf("\n\nThe calendar of %02d/%04d(month/year).张峻宸\n", m, y1);
	printf("**********************************\nMON  TUE  WEN  THU  FRI  SAT  SUN\n");
	if (y1 >= 1583 || (y1 == 1582 && m > 10)) {

		switch (m) {             //判断当月天数
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
		case 2:
			if (y1 % 4 == 0 && y1 % 100 != 0 || y1 % 400 == 0) {
				days = 29;
				break;
			}
			else {
				days = 28;
				break;
			}
		default: {
			days = 31;
			break; }
		}

		if (m == 1 || m == 2) {                         //1月2月当上一年13，14计算
			m += 12;
			y -= 1;
		}

		week = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10) % 7;  //公式

	}

	else if (year == 1582 && month == 10) {
		week = 1;
		days = 31;
	}
	

	else {
		switch (m) {             //判断当月天数
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
		case 2:
			if (y1 % 4 == 0) {
				days = 29;
				break;
			}
			else {
				days = 28;
				break;
			}
		default: {
			days = 31;
			break;
		}
		}
		if (m == 1 || m == 2) {                         //1月2月当上一年13，14计算
			m += 12;
			y -= 1;
		}
		week = (y + (y / 4) + (c-1) / 4 - 2*(c-1) + (13 * (m + 1) / 5)  +3) % 7;
		
	}

	if (week <= 0)
		week += 7;
	
	for (i = 1; i <= days;i++) {
		if (year == 1582 && month == 10&&(i>4&&i<15))
			continue;
		++j;
		
		if (week-1) {
			printf("     ");
			week--;
			i--;
		}
		else {
			//printf("1");
			printf("%-3d", i);
			printf("  ");
		}
		if (j % 7 == 0) {
			printf("\n");
		}
	}

	if (j % 7 == 0)                          //避免出现最后一天刚好周日，多空一行
		printf("**********************************\n");
	else
		printf("\n**********************************\n");
	printf("Press [N/n] for the next month;\nPress [P/p] for the previous month;\nPress [Esc] or other characters for exit.");
	
	a = getch();
	if (a == 78 || a == 110) {
		if (month != 12) {
			month += 1;
		}
		else {
			month = 1;
			year += 1;
		}
		cal(year, month);

	}
	else if (a == 80 || a == 112) {
		if (month != 1) {
			month -= 1;
		}
		else {
			month = 12;
			year -= 1;
		}
		cal(year, month);
	}
	else {
		system("cls");
		main();
	}
}