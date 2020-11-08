#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>
//#include<bios.h>

#define RETURNTIME 15

char catagories[][15] = { "Computer","Electronics","Electrical","Civil","Mechnnical","Architecture" };
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
int  getdata();
int  checkid(int);
int t(void);
//void show_mouse(void);
void Password();
void issuerecord();
//void loaderanim();

//list of global files that can be acceed form anywhere in program
FILE *fp, *ft, *fs, *check, *del;

COORD coord = { 0, 0 };
//list of global variable
int s;
char findbook;
char password[10] = { "hi" };

void gotoxy(int x, int y)
{
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct meroDate
{
	int mm, dd, yy;
};
struct books
{
	int id;
	char stname[20];
	char name[20];
	char Author[20];
	int quantity;
	float Price;
	int count;
	char *cat;
	struct meroDate issued;
	struct meroDate duedate;
};
struct books a;
int main()
{
	Password();
	getch();
	return 0;

}
void mainmenu()
{
	//loaderanim();
	system("cls");
	//    textbackground(13);
	int i;
	gotoxy(20, 3);
	printf("*********************************** MAIN MENU ******************************************");
	//    show_mouse();
	gotoxy(20, 5);
	printf("1. Add Books   ");
	gotoxy(20, 7);
	printf("2. Delete books");
	gotoxy(20, 9);
	printf("3. Search Books");
	gotoxy(20, 11);
	printf("4. Borrow Books");
	gotoxy(20, 13);
	printf("5. View Book list");
	gotoxy(20, 15);
	printf("6. Edit Book's Record");
	gotoxy(20, 17);
	printf("7. Close Application");
	gotoxy(20, 19);
	printf("*******************************************************************************************");
	gotoxy(20, 20);
	t();
	gotoxy(20, 21);
	printf("Enter your choice:");
	switch (getch())
	{
	case '1':
		addbooks();
		break;
	case '2':
		deletebooks();
		break;
	case '3':
		searchbooks();
		break;
	case '4':
		issuebooks();
		break;
	case '5':
		viewbooks();
		break;
	case '6':
		editbooks();
		break;
	case '7':
	{
		system("cls");
		gotoxy(16, 3);
		printf("\tThank you\n\n");
		printf("\tExiting in 3 second...........>");
		//flushall();
		Sleep(3000);
		exit(0);
	}
	default:
	{
		gotoxy(10, 23);
		printf("\aWrong Entry!!Please re-entered correct option");
		if (getch())
			mainmenu();
	}

	}
}
void addbooks(void)    //funtion that add books
{
	system("cls");
	int i;
	gotoxy(20, 5);
	printf("**************************************SELECT CATEGORIES**************************************");
	gotoxy(20, 7);
	printf(" 1. Computer");
	gotoxy(20, 9);
	printf(" 2. Electronics");
	gotoxy(20, 11);
	printf(" 3. Electrical");
	gotoxy(20, 13);
	printf(" 4. Civil");
	gotoxy(20, 15);
	printf(" 5. Mechanical");
	gotoxy(20, 17);
	printf(" 6. Architecture");
	gotoxy(20, 19);
	printf(" 7. Back to main menu");
	gotoxy(20, 21);
	printf("********************************************************************************************");
	gotoxy(20, 22);
	printf("Enter your choice:");
	bool checkChoice = scanf("%d", &s);
	if ((s < 1 || s > 7) || !checkChoice)
	{
		while (getchar() != '\n');
		gotoxy(20, 23);
		printf("Wrong input");
		mainmenu();
	}
	while (getchar() != '\n');
	if (s == 7)
		mainmenu();
	system("cls");
	fp = fopen("Bibek.bin", "ab+");
	if (getdata() == 1)
	{
		a.cat = catagories[s - 1];
		fseek(fp, 0, SEEK_END);
		fwrite(&a, sizeof(a), 1, fp);
		fclose(fp);
		gotoxy(21, 14);
		printf("The record is sucessfully saved");
		gotoxy(21, 15);
		printf("Save any more?(Y / N):");
		if (getch() == 'n')
			mainmenu();
		else
			system("cls");
		addbooks();
	}
}
void deletebooks()    //function that delete items from file fp
{
	system("cls");
	int d;
	char another = 'y';
	findbook = '\0';
	while (another == 'y')  //infinite loop
	{
		system("cls");
		gotoxy(10, 5);
		printf("Enter the Book ID to  delete:");
		scanf("%d", &d);
		while (getchar() != '\n');
		del = fopen("Bibek.bin", "rb+");
		if (del == NULL)
		{
			//fclose(del);
			gotoxy(10, 10);
			printf("No record is found modify the search");
			if (getch())
				mainmenu();

		}
		while (fread(&a, sizeof(a), 1, del) == 1)
		{
			if (a.id == d)
			{
				gotoxy(10, 7);
				printf("The book record is available");
				gotoxy(10, 8);
				printf("Book name is %s", a.name);
				findbook = 't';
				break;
			}
		}
		fclose(del);
		if (findbook != 't')
		{
			gotoxy(10, 10);
			printf("No record is found modify the search");
			if (getch())
				mainmenu();
		}
		else
		{
			gotoxy(10, 9);
			printf("Do you want to delete it?(Y/N):");
			if (getch() == 'y')
			{
				ft = fopen("test.bin", "wb+");  //temporary file for delete
				fp = fopen("Bibek.bin", "rb+");
				while (fread(&a, sizeof(a), 1, fp) == 1)
				{
					if (a.id != d)
					{
						fseek(ft, 0, SEEK_CUR);
						fwrite(&a, sizeof(a), 1, ft); //write all in tempory file except that
					}                              //we want to delete
				}
				fclose(ft);
				fclose(fp);
				remove("Bibek.bin");
				rename("test.bin", "Bibek.bin"); //copy all item from temporary file to fp except that
				//fp = fopen("Bibek.bin", "rb+");    //we want to delete
				gotoxy(10, 10);
				printf("The record is sucessfully deleted");
				gotoxy(10, 11);
				printf("Delete another record?(Y/N)");

			}
			else
				mainmenu();
			fflush(stdin);
			another = getch();
		}

	}
	gotoxy(10, 15);
	mainmenu();
}
void searchbooks()
{
	system("cls");
	int d;
	gotoxy(20, 5);
	printf("*****************************Search Books*********************************");
	gotoxy(20, 10);
	printf(" 1. Search By ID");
	gotoxy(20, 14);
	printf(" 2. Search By Name");
	gotoxy(15, 20);
	printf("Enter Your Choice");
	fp = fopen("Bibek.bin", "rb+"); //open file for reading propose
	switch (getch())
	{
	case '1':
	{
		system("cls");
		gotoxy(25, 4);
		printf("****Search Books By Id****");
		gotoxy(20, 5);
		printf("Enter the book id:");
		scanf("%d", &d);
		while (getchar() != '\n');
		gotoxy(20, 7);
		printf("Searching........");
		findbook = '\0';
		if (fp == NULL)
		{
			gotoxy(20, 8);
			printf("********************************************************************************************");
			gotoxy(20, 9); printf("*");  gotoxy(38, 9); printf("*");
			gotoxy(20, 10);
			printf("********************************************************************************************");
			gotoxy(22, 9); printf("\aNo Record Found");

			gotoxy(20, 17);
			printf("Try another search?(Y/N)");
			if (getch() == 'y')
				searchbooks();
			else
				mainmenu();
		}
		while (fread(&a, sizeof(a), 1, fp) == 1)
		{
			if (a.id == d)
			{
				Sleep(2);
				gotoxy(20, 7);
				printf("The Book is available");
				gotoxy(20, 8);
				printf("********************************************************************************************");
				gotoxy(20, 9);
				printf("* ID:%d", a.id); gotoxy(47, 9); printf("*");
				gotoxy(20, 10);
				printf("* Name:%s", a.name); gotoxy(47, 10); printf("*");
				gotoxy(20, 11);
				printf("* Author:%s ", a.Author); gotoxy(47, 11); printf("*");
				gotoxy(20, 12);
				printf("* Qantity:%d ", a.quantity); gotoxy(47, 12); printf("*"); gotoxy(47, 11); printf("*");
				gotoxy(20, 13);
				printf("* Price:Rs.%.2f", a.Price); gotoxy(47, 13); printf("*");
				gotoxy(20, 14);
				printf("********************************************************************************************");
				findbook = 't';
				break;
			}

		}
		fclose(fp);
		if (findbook != 't')  //checks whether conditiion enters inside loop or not
		{
			gotoxy(20, 8);
			printf("********************************************************************************************");
			gotoxy(20, 9); printf("*");  gotoxy(38, 9); printf("*");
			gotoxy(20, 10);
			printf("********************************************************************************************");
			gotoxy(22, 9); printf("\aNo Record Found");
		}
		gotoxy(20, 17);
		printf("Try another search?(Y/N)");
		if (getch() == 'y')
			searchbooks();
		else
			mainmenu();
		break;
	}
	case '2':
	{
		char s[15];
		system("cls");
		gotoxy(25, 4);
		printf("****Search Books By Name****");
		gotoxy(20, 5);
		printf("Enter Book Name:");
		scanf("%s", s);
		while (getchar() != '\n');
		int d = 0;
		while (fread(&a, sizeof(a), 1, fp) == 1)
		{
			if (strcmp(a.name, (s)) == 0) //checks whether a.name is equal to s or not
			{
				gotoxy(20, 7);
				printf("The Book is available");
				gotoxy(20, 8);
				printf("********************************************************************************************");
				gotoxy(20, 9);
				printf("* ID:%d", a.id); gotoxy(47, 9); printf("*");
				gotoxy(20, 10);
				printf("* Name:%s", a.name); gotoxy(47, 10); printf("*");
				gotoxy(20, 11);
				printf("* Author:%s", a.Author); gotoxy(47, 11); printf("*");
				gotoxy(20, 12);
				printf("* Qantity:%d", a.quantity); gotoxy(47, 12); printf("*");
				gotoxy(20, 13);
				printf("* Price:Rs.%.2f", a.Price); gotoxy(47, 13); printf("*");
				gotoxy(20, 14);
				printf("********************************************************************************************");
				d++;
			}

		}
		if (d == 0)
		{
			gotoxy(20, 8);
			printf("********************************************************************************************");
			gotoxy(20, 9); printf("*");  gotoxy(38, 9); printf("*");
			gotoxy(20, 10);
			printf("********************************************************************************************");
			gotoxy(22, 9); printf("\aNo Record Found");
		}
		gotoxy(20, 17);
		printf("Try another search?(Y/N)");
		if (getch() == 'y')
			searchbooks();
		else
			mainmenu();
		break;
	}
	default:
		getch();
		searchbooks();
	}
	fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
	int t;

	system("cls");
	gotoxy(10, 3);
	printf("*****************************BORROW BOOKS*********************************");
	gotoxy(10, 5);
	printf(" 1. Borrow a Book");
	gotoxy(10, 7);
	printf(" 2. View borrowed Book");
	gotoxy(10, 9);
	printf(" 3. Return borrowed Book");
	gotoxy(10, 14);
	printf("Enter a Choice:");
	switch (getch())
	{
	case '1':  //issue book
	{
		system("cls");
		int c = 0;
		char another = 'y';
		while (another == 'y')
		{
			system("cls");
			gotoxy(15, 4);
			printf("***Borrow Book section***");
			gotoxy(10, 6);
			printf("Enter the Book Id:");
			scanf("%d", &t);
			while (getchar() != '\n');
			fs = fopen("Issue.bin", "ab+");
			if (checkid(t) == 0) //issues those which are present in library
			{
				gotoxy(10, 8);
				printf("The book record is available");
				gotoxy(10, 9);
				printf("There are %d unborrowed books in library ", a.quantity);
				gotoxy(10, 10);
				printf("The name of book is %s", a.name);
				gotoxy(10, 11);
				printf("Enter student name:");
				scanf("%s", a.stname);
				while (getchar() != '\n');
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);

				a.issued.dd = tm.tm_mday;
				a.issued.mm = tm.tm_mon + 1;
				a.issued.yy = tm.tm_year + 1900;
				gotoxy(10, 13);
				printf("********************************************************************************************");
				gotoxy(10, 14);
				printf("Issued date=%d-%d-%d", a.issued.dd, a.issued.mm, a.issued.yy);
				gotoxy(10, 15);
				printf("The BOOK of ID %d is issued", a.id);
				gotoxy(10, 16);
				printf("********************************************************************************************");
				a.duedate.dd = a.issued.dd + RETURNTIME;   //for return date
				a.duedate.mm = a.issued.mm;
				a.duedate.yy = a.issued.yy;
				if (a.duedate.dd > 30)
				{
					a.duedate.mm += a.duedate.dd / 30;
					a.duedate.dd -= 30;

				}
				if (a.duedate.mm > 12)
				{
					a.duedate.yy += a.duedate.mm / 12;
					a.duedate.mm -= 12;

				}
				gotoxy(10, 18);
				printf("To be return:%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);
				fseek(fs, sizeof(a), SEEK_END);
				fwrite(&a, sizeof(a), 1, fs);
				fclose(fs);
				c = 1;
			}
			else
			{
				gotoxy(10, 11);
				printf("No record found");
			}
			gotoxy(10, 20);
			printf("Issue any more(Y/N):");
			fflush(stdin);
			another = getche();
		}

		break;
	}
	case '2':  //show issued book list
	{
		system("cls");
		int j = 4;
		printf("*******************************borrowed book list*******************************\n");
		gotoxy(2, 2);
		printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
		fs = fopen("Issue.bin", "rb");
		if (fs == NULL)
		{
			gotoxy(1, 24);
			printf("There's no borrowed books");
			gotoxy(1, 25);
			returnfunc();
		}
		while (fread(&a, sizeof(a), 1, fs) == 1)
		{

			gotoxy(2, j);
			printf("%s", a.stname);
			gotoxy(18, j);
			printf("%s", a.cat);
			gotoxy(30, j);
			printf("%d", a.id);
			gotoxy(36, j);
			printf("%s", a.name);
			gotoxy(51, j);
			printf("%d-%d-%d", a.issued.dd, a.issued.mm, a.issued.yy);
			gotoxy(65, j);
			printf("%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);
			//struct dosdate_t d;
			//_dos_getdate(&d);
			gotoxy(50, 25);
			//            printf("Current date=%d-%d-%d",d.day,d.month,d.year);
			j++;

		}
		fclose(fs);
		gotoxy(1, 25);
		returnfunc();
	}
	break;
	case '3':  //remove issued books from list
	{
		system("cls");
		int b;
		FILE *fg;  //declaration of temporary file for delete
		char another = 'y';
		while (another == 'y')
		{
			system("cls");
			gotoxy(10, 5);
			printf("Enter book id to return:");
			scanf("%d", &b);
			while (getchar() != '\n');
			fs = fopen("Issue.bin", "rb+");
			findbook = '\0';
			if (fs == NULL)
			{
				gotoxy(10, 15);
				printf("No Record Found");

				gotoxy(10, 16);
				printf("Return any more?(Y/N)");
				another = getch();
				continue;
			}
			while (fread(&a, sizeof(a), 1, fs) == 1)
			{
				if (a.id == b)
				{
					issuerecord();
					findbook = 't';
				}
				if (findbook == 't')
				{
					gotoxy(10, 12);
					printf("Do You Want to Return it?(Y/N)");
					if (getch() == 'y')
					{
						fg = fopen("record.bin", "wb+");
						while (fread(&a, sizeof(a), 1, fs) == 1)
						{
							if (a.id != b)
							{
								fseek(fs, 0, SEEK_CUR);
								fwrite(&a, sizeof(a), 1, fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.bin");
						rename("record.bin", "Issue.bin");
						gotoxy(10, 14);
						printf("The borrowed book is returned from list");

					}

				}
				else
				{
					gotoxy(10, 15);
					printf("No Record Found");
				}
			}
			gotoxy(10, 16);
			printf("Return any more?(Y/N)");
			another = getch();
		}
	}
	break;
	default:
		gotoxy(10, 18);
		printf("\aWrong Entry!!");
		getch();
		issuebooks();
		break;
	}
	gotoxy(1, 30);
	returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
	int i = 0, j;
	system("cls");
	gotoxy(1, 1);
	printf("*********************************Book List*****************************");
	gotoxy(2, 2);
	printf(" CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE ");
	j = 4;
	fp = fopen("Bibek.bin", "rb");
	if (fp == NULL)
	{
		gotoxy(3, j);
		printf(" There's no book to View");
		//fclose(fp);
		gotoxy(3, j + 1);
		returnfunc();
	}
	while (fread(&a, sizeof(a), 1, fp) == 1)
	{
		gotoxy(3, j);
		printf("%s", a.cat);
		gotoxy(16, j);
		printf("%d", a.id);
		gotoxy(22, j);
		printf("%s", a.name);
		gotoxy(36, j);
		printf("%s", a.Author);
		gotoxy(50, j);
		printf("%d", a.quantity);
		gotoxy(57, j);
		printf("%.2f", a.Price);
		gotoxy(69, j);
		printf("\n\n");
		j++;
		i = i + a.quantity;
	}
	gotoxy(3, 25);
	printf("Total Books =%d", i);
	fclose(fp);
	gotoxy(35, 25);
	returnfunc();
}
void editbooks(void)  //edit information about book
{
	system("cls");
	int c = 0;
	int d, e;
	gotoxy(20, 4);
	printf("****Edit Books Section****");
	char another = 'y';
	while (another == 'y')
	{
		system("cls");
		gotoxy(15, 6);
		printf("Enter Book Id to be edited:");
		if (!scanf("%d", &d))
		{
			while (getchar() != '\n');
			gotoxy(15, 7);
			printf("Wrong input");

			gotoxy(15, 16);
			printf("Modify another Record?(Y/N)");
			fflush(stdin);
			another = getch();

			returnfunc();
		}
		while (getchar() != '\n');
		fp = fopen("Bibek.bin", "rb+");
		while (fread(&a, sizeof(a), 1, fp) == 1)
		{
			if (checkid(d) == 0)
			{
				gotoxy(15, 7);
				printf("The book is availble");
				gotoxy(15, 8);
				printf("The Book ID:%d", a.id);
				gotoxy(15, 9);
				printf("Enter new name:"); scanf("%s", a.name);
				while (getchar() != '\n');
				gotoxy(15, 10);
				printf("Enter new Author:"); scanf("%s", a.Author);
				while (getchar() != '\n');
				gotoxy(15, 11);

				printf("Enter new quantity:");
				if (!scanf("%d", &a.quantity))
				{
					while (getchar() != '\n');
					gotoxy(15, 12);
					printf("Wrong input");
					break;
				}
				while (getchar() != '\n');
				gotoxy(15, 12);
				printf("Enter new price:");
				if (!scanf("%f", &a.Price))
				{
					while (getchar() != '\n');
					gotoxy(15, 13);
					printf("Wrong input");
					break;
				}
				while (getchar() != '\n');
				gotoxy(15, 13);
				printf("The record is modified");
				fseek(fp, ftell(fp) - sizeof(a), 0);
				fwrite(&a, sizeof(a), 1, fp);
				fclose(fp);
				c = 1;
			}
			if (c == 0)
			{
				gotoxy(15, 9);
				printf("No record found");
			}
		}
		gotoxy(15, 16);
		printf("Modify another Record?(Y/N)");
		fflush(stdin);
		another = getch();
	}
	returnfunc();
}
void returnfunc(void)
{
	{
		printf(" Press ENTER to return to main menu");
	}
a:
	if (getch() == 13) //allow only use of enter
		mainmenu();
	else
		goto a;
}
int getdata()
{
	int t;
	gotoxy(20, 3); printf("Enter the Information Below");
	gotoxy(20, 4); printf("********************************************************************************************");
	gotoxy(20, 5);
	printf("*"); gotoxy(46, 5); printf("*");
	gotoxy(20, 6);
	printf("*"); gotoxy(46, 6); printf("*");
	gotoxy(20, 7);
	printf("*"); gotoxy(46, 7); printf("*");
	gotoxy(20, 8);
	printf("*"); gotoxy(46, 8); printf("*");
	gotoxy(20, 9);
	printf("*"); gotoxy(46, 9); printf("*");
	gotoxy(20, 10);
	printf("*"); gotoxy(46, 10); printf("*");
	gotoxy(20, 11);
	printf("*"); gotoxy(46, 11); printf("*");
	gotoxy(20, 12);
	printf("********************************************************************************************");
	gotoxy(21, 5);
	printf("Category:");
	gotoxy(31, 5);
	printf("%s", catagories[s - 1]);
	gotoxy(21, 6);
	printf("Book ID:\t");
	gotoxy(30, 6);
	if (!scanf("%d", &t))
	{
		while (getchar() != '\n');
		gotoxy(30, 7);
		printf("wrong input");
		getch();
		mainmenu();
		return 0;
	}
	while (getchar() != '\n');

	if (checkid(t) == 0)
	{
		gotoxy(21, 13);
		printf("\aThe book id already exists\a");
		gotoxy(21, 14);
		printf("\aPress any key to coninue\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id = t;
	gotoxy(21, 7);
	printf("Book Name:"); gotoxy(33, 7);
	scanf("%s", a.name);
	while (getchar() != '\n');
	gotoxy(21, 8);
	printf("Author:"); gotoxy(30, 8);
	scanf("%s", a.Author);
	while (getchar() != '\n');
	gotoxy(21, 9);
	printf("Quantity:"); gotoxy(31, 9);
	if (!scanf("%d", &a.quantity))
	{
		while (getchar() != '\n');
		gotoxy(31, 10);
		printf("Wrong input");
		getch();
		mainmenu();
		return 0;
	}
	while (getchar() != '\n');
	gotoxy(21, 10);
	printf("Price:"); gotoxy(28, 10);
	if (!scanf("%f", &a.Price))
	{
		while (getchar() != '\n');
		gotoxy(28, 11);
		printf("Wrong input");
		getch();
		mainmenu();
		return 0;
	}
	while (getchar() != '\n');
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	check = fopen("Bibek.bin", "rb+");
	if (check == NULL)
		return 1;		//there's no book, so not exist

	while (fread(&a, sizeof(a), 1, check) == 1)
	{
		if (a.id == t)
		{
			fclose(check);
			return 0;	//returns 0 if book exits
		}
	}
	fclose(check);
	return 1; //return 1 if it not
}
int t(void) //for time
{
	time_t t;
	time(&t);
	printf("Date and time:%s\n", ctime(&t));

	return 0;
}
/*void show_mouse(void) //show inactive mouse pointer in programme
{
union REGS in,out;
	   in.x.ax = 0x1;
	   int86(0x33,&in,&out);
}*/
void Password(void) //for password option
{

	system("cls");
	char d[25] = "Password Protected";
	char ch = '\0';
	char pass[10];
	int i = 0, j;
	//textbackground(WHITE);
	//textcolor(RED);
	gotoxy(10, 4);
	/*for (j = 0; j < 20; j++)
	{
		Sleep(50);
		printf("*");
	}
	for (j = 0; j < 20; j++)
	{
		Sleep(50);
		printf("%c", d[j]);
	}
	for (j = 0; j < 20; j++)
	{
		Sleep(50);
		printf("*");
	}*/
	printf("******************************Welcome to******************************");
	gotoxy(10, 5);
	printf("*************************Kwang Woon Library***************************");
	gotoxy(10, 10);
	gotoxy(15, 7);
	printf("Enter Password:");

	while (ch != 13)
	{
		ch = getch();
		if (ch != 13 && ch != 8) {
			putch('*');
			pass[i] = ch;
			i++;
		}
	}
	pass[i] = '\0';
	if (strcmp(pass, password) == 0)
	{
		gotoxy(15, 9);
		//textcolor(BLINK);
		printf("Password match");
		gotoxy(17, 10);
		printf("Press any key to countinue.....");
		getch();
		mainmenu();
	}
	else
	{
		gotoxy(15, 16);
		printf("\aWarning!! Incorrect Password");
		getch();
		Password();
	}
}
void issuerecord()  //display issued book's information
{
	system("cls");
	gotoxy(10, 8);
	printf("The Book has taken by %s", a.stname);
	gotoxy(10, 9);
	printf("Issued Date:%d-%d-%d", a.issued.dd, a.issued.mm, a.issued.yy);
	gotoxy(10, 10);
	printf("Returning Date:%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);
}
/*void loaderanim()
{
int loader;
system("cls");
gotoxy(20,10);
printf("LOADING........");
printf("\n\n");
gotoxy(22,11);
for(loader=1;loader<20;loader++)
{
Sleep(100);printf("%c",219);}
}*/
//End of program
