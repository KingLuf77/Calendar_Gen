#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>

#define MAX_STRING 1000

int main() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	system("dir");
	printf("\nSUPER CALENDAR\n");
	printf("Current Date:  %02d / %02d / %d\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);
	int year;
	while (1) {
		printf("\nYear:        ");
		scanf_s("%d", &year);
		if (year < 1900 || year > 2099) {
			printf("Bad input. Try again.\n");
		}
		else {
			break;
		}
	}
	int start;
	while (1) {
		printf("Start Month: ");
		scanf_s("%d", &start);
		if (start < 1 || start > 12) {
			printf("Bad input. Try again.\n");
		}
		else {
			break;
		}
	}
	int startDay;
	char weekStrings[7][MAX_STRING] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
	while (1) {
		for (int i = 0; i < 7; i++) {
			printf("%d = %s", i + 1, weekStrings[i]);
			if (i < 6) {
				printf(", ");
			}
		}
		printf("\nFirst WkDay: ");
		scanf_s("%d", &startDay);
		if (startDay < 1 || startDay > 7) {
			printf("Bad input. Try again.\n");
		}
		else {
			break;
		}
	}
	int end;
	while (1) {
		printf("End Month:   ");
		scanf_s("%d", &end);
		if (end < 1 || end > 12) {
			printf("Bad input. Try again.\n");
		}
		else {
			break;
		}
	}
	char monthStrings[12][MAX_STRING] = { "JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER" };
	char monthShort[12][MAX_STRING] = { "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };
	int monthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		printf("\n       Year: %d (leap year)", year);
	}
	else {
		printf("\n       Year: %d", year);
	}
	printf("\nStart Month: %s\n  End Month: %s\n  Start Day: %s\n", monthStrings[start - 1], monthStrings[end - 1], weekStrings[startDay - 1]);
	bool wrapAround = true;
	if (end > start) {
		wrapAround = false;
	}
	printf("\nFrom %s %d to %s ", monthStrings[start - 1], year, monthStrings[end - 1]);
	int length = end - start;
	if (wrapAround == false) {
		printf("%d\n", year);
		monthDays[1] = 29;
	}
	else {
		printf("%d\n", year + 1);
		length += 12;
		if (start > 1) {
			monthDays[1] = 28;
		}
	}
	printf("\nExport Title: ");
	char title[MAX_STRING] = "untitled_calendar";
	scanf_s("%s", &title, MAX_STRING);
	strcat_s(title, MAX_STRING, ".txt");
	printf("\nExporting...");
	FILE* exportFile = fopen(title, "w");
	int realYear = year;
	if (wrapAround == true) {
		realYear++;
	}
	int clicks = startDay - 1;
	fprintf(exportFile, "%s\nfrom %s %d to %s %d\n\n", title, monthStrings[start - 1], year, monthStrings[end - 1], realYear);
	for (int i = 0; i < length + 1; i++) {
		int month = i + start - 1;
		int realYear = year;
		if (month > 11) {
			month -= 12;
			realYear = year + 1;
		}
		//fprintf(exportFile, "\n>=>=> %s %d\n\n", monthStrings[month], realYear);
		for (int d = 0; d < monthDays[month]; d++) {
			fprintf(exportFile, ">> ");
			fprintf(exportFile, "%s ", weekStrings[clicks % 7]);
			fprintf(exportFile, "%s ", monthShort[month]);
			if (d < 9) {
				fprintf(exportFile, " ");
			}
			fprintf(exportFile, "%d\n\n\n", d + 1);
			clicks++;
		}
	}
	fclose(exportFile);
	printf("Done!\n\n");
	FILE* printFile = fopen(title, "r");
	while (1) {
		printf("%c", fgetc(printFile));
		if (feof(printFile)) {
			break;
		}
	}
	system("dir");
	printf("\n");
}