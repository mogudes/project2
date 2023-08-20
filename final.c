#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#pragma warning(disable:4996)
#define MAXFILE 60
#define MAXSALES 300
#define MAX_NUMBER 100


void invalid();
void invalid() {
	printf("\t\t\t||=========================================================================================================||\n");
	printf("\t\t\t||=======||   ||     ||   ||   |||||||   |||   ||   ||     ||    ||||    |||       |||||||   |||||||=======||\n");
	printf("\t\t\t||======||     ||   ||     ||    |||     ||||  ||   ||     ||   ||  ||   |||         |||     ||    ||======||\n");
	printf("\t\t\t||======||       |||       ||    |||     || || ||    ||   ||    ||==||   |||         |||     ||    ||======||\n");
	printf("\t\t\t||======||     ||   ||     ||    |||     ||  ||||     || ||     ||  ||   |||         |||     ||    ||======||\n");
	printf("\t\t\t||=======||   ||     ||   ||   |||||||   ||   |||      |||      ||  ||   |||||||   |||||||   |||||||=======||\n");
	printf("\t\t\t||=========================================================================================================||\n");
}
void welcome();
void welcome() {
	printf("\t\t\t||==========================================================================================================||\n");
	printf("\t\t\t||=====\\\\                //    |||||||    |||       |||||||    |||||||     ||\\\\         //||    |||||||=====||\n");
	printf("\t\t\t||======\\\\              //     ||         |||       ||        ||     ||    ||  \\\\      // ||    ||     =====||\n");
	printf("\t\t\t||=======\\\\    //\\\\    //      |||||||    |||       ||        ||     ||    ||   \\\\    //  ||    |||||||=====||\n");
	printf("\t\t\t||========\\\\  //  \\\\  //       ||         |||       ||        ||     ||    ||    \\\\  //   ||    ||     =====||\n");
	printf("\t\t\t||=========\\\\//    \\\\//        |||||||    |||||||   |||||||    |||||||     ||     \\\\//    ||    |||||||=====||\n");
	printf("\t\t\t||==========================================================================================================||\n");
}

typedef struct {
	char id[10];
	char name[50];
	char gender;
	char password[20];
	int contact;
	char ic[13];
}member;

typedef struct {
	char name[30];
	char staffid[10];
	char gender;
	char contactno[30];
	char position;
	char password[10];
} Staff;

struct stock
{
	char code[10];
	char description[50];
	double price, costprice;
	int quantity, minimumlevel;
	int restock, outstock;

};

typedef struct {
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
} Time;

typedef struct {
	char salesID[5];
	char itemCode[10];
	int quantityOrder;
	double price;
	char memberID[6];
	char staffID[6];
	Time timeAdd;
} SalesInformation;

SYSTEMTIME time;

//Call By main()
void readFile(member*, Staff*, struct stock*, SalesInformation*, int*, int*, int*, int*);
void StaffInformationModule(Staff*, int*);
void MemberInformationModule(member*, int*);
void SalesInformationModule(SalesInformation*, int*, struct stock[], member[], Staff[], int num_member, int item_number, int staffID);
void StockInformationModule(struct stock*, int*);
void writeFile(member[], Staff[], struct stock[], SalesInformation[], int, int, int, int);


//Call By StaffInformationModule()
int login(int, Staff[]); //Call By Start Of The Program
void newstaff(Staff*, int*);
void edit(int, Staff*);
void listall(int, Staff[]);
void search(int, Staff[]);
void deletestaff(int*, Staff*);


//Call By MemberInformationModule()
int loginMember(member[], int); //Call By editMember() function 
void addMember(member*, int*);
void listMember(member[], int);
void editMember(member*, int);
void findMember(member[], int);
void deleteMember(member*, int*);



//Call By SalesInformationModule()
void DisplayRecord(SalesInformation[], int currentSales);
void AddRecord(int* currentSales, int stafID, SalesInformation*, struct stock[], member[], int num_member, Staff[]);
void SearchRecord(int currentSales, SalesInformation[]);
void DeleteRecord(SalesInformation*, int* currentSales, struct stock[]);
void CalculateRevenue(SalesInformation[], struct stock[], int currentSales, int item_number);
void ModifyRecord(int currentSales, SalesInformation*, struct stock[], member[], Staff[], int item_number, int num_member);


//Call By StockInformationModule()
void add_item(struct stock*, int*);
void delete_item(struct stock*, int*);
void display_item(struct stock[], int);
void modify_item(int, struct stock*);
void search_item(struct stock[], int);
void report(struct stock[], int);





void main() {
	//Prepare All Structure Variable And Array
	member members[MAX_NUMBER];
	Staff staff[MAX_NUMBER];
	struct stock item[MAX_NUMBER];
	SalesInformation salesInfo[MAXSALES];

	//Variable To Record Current Quantity Of Data
	int num_member = 0, item_number = 0, numstaff = 0, currentSales = 0;

	//Variable For Staff Login
	int staffID = -1;

	//Read All Data From File
	readFile(members, staff, item, salesInfo, &num_member, &item_number, &currentSales, &numstaff);

	//Login To Staff Account Before Run Any Function
	while (staffID == -1) {
		staffID = login(numstaff, staff);//Login Function In Staff Information Module
	}

	//Choose Module To Run After Login With Staff Account

	int choice;
	do {
		printf("\t\t\t\t\b\b\b\b\b\b||================================================================================================================||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||====|||||||||||||=======|||||||||||||=======|||=======|||||||||||||=======|||||||||||||=======|||||||||||||=====||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||====|||=================|||========|||======|||=======|||========|||======|||=================|||========|||====||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||====|||=================|||========|||======|||=======|||=========|||=====|||=================|||========|||====||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||====|||=================|||========|||======|||=======|||=========|||=====|||=================|||========|||====||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||====|||||||||||||=======|||||||||||||=======|||=======|||=========|||=====|||||||||||||=======|||||||||||||=====||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||==============|||=======|||=================|||=======|||=========|||=====|||=================|||||||===========||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||==============|||=======|||=================|||=======|||=========|||=====|||=================|||===|||=========||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||==============|||=======|||=================|||=======|||========|||======|||=================|||=====|||=======||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||====|||||||||||||=======|||=================|||=======|||||||||||||=======|||||||||||||=======|||=======|||=====||\n");
		printf("\t\t\t\t\b\b\b\b\b\b||================================================================================================================||\n\n\n");
		printf("\t||   ||||||||||||||||||||||||   ||\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t||   |||||  ||||||||||  |||||   ||\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\b\b\b|| ||==||||==================||||==|| ||\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\b\b\b||     |||| StaffInformation ||||\t\t\b\b\b\b\b||\t\t\t\t\t\b\b\b||     |||| MemberInformation||||\t\t\b\b\b\b\b ||\n");
		printf("\t\b\b\b||=====||||==================||||=====||\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t     ||||||||||||||||||||||||\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t||===||||||||||||||||||||||||===||\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t||          ||< 1 >||           ||\t\t\t\t\t||          ||< 2 >||           ||\n");
		printf("\t||\t\t\t\t||\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t||   ||||||||||||||||||||||||   ||\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\b\b\b||     |||| SalesInformation ||||\t\t\b\b\b\b\b||\t\t\t\t\t\b\b\b||     |||| StockInformation ||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\b\b\b||=====||||==================||||=====||\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t     ||||||||||||||||||||||||\t\t\t\t\t\t\t\b\b||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t||===||||||||||||||||||||||||===||\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t||          ||< 3 >||           ||\t\t\t\t\t||          ||< 4 >||           ||\n");
		printf("\t\t\t\t\t||\t\t\t\t||\t\t\t\t\t||                              ||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||       Exit       ||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||< 5 >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%d", &choice);
		while (choice < 1 && choice > 6) {					//Input Validation
			invalid();
			printf("\t||   ||||||||||||||||||||||||   ||\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t||   |||||  ||||||||||  |||||   ||\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\b\b\b|| ||==||||==================||||==|| ||\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\b\b\b||     |||| StaffInformation ||||\t\t\b\b\b\b\b||\t\t\t\t\t\b\b\b||     |||| MemberInformation||||\t\t\b\b\b\b\b ||\n");
			printf("\t\b\b\b||=====||||==================||||=====||\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t     ||||||||||||||||||||||||\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
			printf("\t||===||||||||||||||||||||||||===||\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t||          ||< 1 >||           ||\t\t\t\t\t||          ||< 2 >||           ||\n");
			printf("\t||\t\t\t\t||\t\t\t\t\t||\t\t\t\t||\n\n\n");
			printf("\t\t\t\t\t||   ||||||||||||||||||||||||   ||\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\t\t\t\t\b\b\b||     |||| SalesInformation ||||\t\t\b\b\b\b\b||\t\t\t\t\t\b\b\b||     |||| StockInformation ||||\t\t\b\b\b\b\b||\n");
			printf("\t\t\t\t\t\b\b\b||=====||||==================||||=====||\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t\t\t\t\t     ||||||||||||||||||||||||\t\t\t\t\t\t\t\b\b||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t||===||||||||||||||||||||||||===||\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t||          ||< 3 >||           ||\t\t\t\t\t||          ||< 4 >||           ||\n");
			printf("\t\t\t\t\t||\t\t\t\t||\t\t\t\t\t||                              ||\n\n\n");
			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||       Exit       ||||\t\t\b\b\b\b\b||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t||          ||< 5 >||           ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%d", &choice);
		}
		switch (choice) {										//Run Module
		case 1:
			StaffInformationModule(staff, &numstaff);
			break;
		case 2:
			MemberInformationModule(members, &num_member);
			break;
		case 3:
			SalesInformationModule(salesInfo, &currentSales, item, members, staff, num_member, item_number, staffID);
			break;
		case 4:
			StockInformationModule(item, &item_number);
			break;
		case 5:
			//Write All Data Into File Before Exiting The Program
			writeFile(members, staff, item, salesInfo, num_member, item_number, currentSales, numstaff);
			exit(1);
			break;
		}

	} while (choice != 5);
}


//Function To Read All Data Into Structure Variable
void readFile(member* members, Staff* staff, struct stock* item, SalesInformation* salesInfo, int* num_member, int* item_number, int* currentSales, int* numstaff) {
	FILE* stockData = fopen("item.bin", "rb");
	FILE* salesData = fopen("sales.bin", "rb");
	FILE* staffData = fopen("staff.txt", "r");
	FILE* memberData = fopen("member.txt", "r");
	if (!stockData) {
		printf("Error On Stock Information\n");
		exit(2);
	}
	if (!salesData) {
		printf("Error On Sales Information\n");
		exit(2);
	}
	if (!staffData) {
		printf("Error On Staff Information\n");
		exit(2);
	}
	if (!memberData) {
		printf("Error On Member Information\n");
		exit(2);
	}

	while (*item_number < MAX_NUMBER && fread(&item[*item_number], sizeof(struct stock), 1, stockData)) {
		item[*item_number].outstock = 0;
		item[*item_number].restock = 0;
		(*item_number)++;
	}
	while (*currentSales < MAXSALES && fread(&salesInfo[*currentSales], sizeof(SalesInformation), 1, salesData)) {
		(*currentSales)++;
	}
	while (!feof(staffData)) {
		fscanf(staffData, "%[^|]|%[^|]|%c|%[^|]|%c|%[^|]|\n", staff[*numstaff].name, staff[*numstaff].staffid, &staff[*numstaff].gender, staff[*numstaff].contactno, &staff[*numstaff].position, staff[*numstaff].password);
		(*numstaff)++;
	}
	while (!feof(memberData)) {
		fscanf(memberData, "%[^|]|%[^|]|%c|%[^|]|%d|%[^|]|\n", members[*num_member].id, members[*num_member].name, &members[*num_member].gender, &members[*num_member].password, &members[*num_member].contact, members[*num_member].ic);
		(*num_member)++;
	}
	fclose(salesData);
	fclose(stockData);
	fclose(staffData);
	fclose(memberData);
}

//Function To Write All Data Into Structure Variable
void writeFile(member members[], Staff staff[], struct stock item[], SalesInformation salesInfo[], int num_member, int item_number, int currentSales, int numstaff) {
	FILE* stockData = fopen("item.bin", "wb");
	FILE* salesData = fopen("sales.bin", "wb");
	FILE* staffData = fopen("staff.txt", "w");
	FILE* memberData = fopen("member.txt", "w");
	if (!stockData) {
		printf("Error On Stock Information\n");
		exit(2);
	}
	if (!salesData) {
		printf("Error On Sales Information\n");
		exit(2);
	}
	if (!staffData) {
		printf("Error On Staff Information\n");
		exit(2);
	}
	if (!memberData) {
		printf("Error On Member Information\n");
		exit(2);
	}
	for (int i = 0; i < currentSales; i++) {
		fwrite(&salesInfo[i], sizeof(SalesInformation), 1, salesData);
	}
	for (int i = 0; i < item_number; i++) {
		fwrite(&item[i], sizeof(struct stock), 1, stockData);
	}
	for (int i = 0; i < numstaff; i++) {
		fprintf(staffData, "%s|%s|%c|%s|%c|%s|\n", staff[i].name, staff[i].staffid, staff[i].gender, staff[i].contactno, staff[i].position, staff[i].password);
	}

	for (int j = 0; j < num_member; j++) {
		fprintf(memberData, "%s|%s|%c|%s|%d|%s|\n", members[j].id, members[j].name, members[j].gender, members[j].password, members[j].contact, members[j].ic);
	}

	fclose(salesData);
	fclose(stockData);
	fclose(staffData);
	fclose(memberData);
}




//-----------------------------------------------------------------Start Of Staff Information Module-----------------------------------------------------------------------
int login(int numstaff, Staff staff[]) {

	char password[20], id[20];
	int index = -1;

	printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||\n");
	printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||||||||||||||||||||||||=====||||||==================\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||==||||||||||||||==||||\t\t||<Login Function>||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||||||==================\n");
	printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
	printf("\t\t\t\t\t\t\t\t||          ||     ||           ||\n");
	printf("\t\t\t\t\t\t\t\t||                              ||\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||         <<Staff ID>>         ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%[^\n]", id);
	for (int i = 0; i < numstaff; i++) {
		if (strcmp(id, staff[i].staffid) == 0) {
			index = i;
		}
	}
	if (index == -1) {
		invalid();
	}
	else {
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||         <<PASSWORD>>         ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);

		scanf("%[^\n]", password);
		if (strcmp(password, staff[index].password) == 0) {
			welcome();
			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||||||||||||||||||||||||=====||||||==================\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||==||||||||||||||==||||\t\t||< %s >||\n", staff[index].name);
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||||||==================\n");
			printf("\t\t\t\t\t\t\t\t\t\b\b\b\b|||||||||||||||||||||||||||||||||\t\t\t\t\t\t\n");
			printf("\t\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t\t||          ||     ||           ||\n");
			printf("\t\t\t\t\t\t\t\t\t||                              ||\n");

		}
		else {
			invalid();
			index = -1;
		}
	}
	return index;
}

void StaffInformationModule(Staff* staff, int* numstaff) {

	int choose;
	do {
		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     |||| StaffInformation ||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||< 1 >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.New Staff           ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Edit Staff          ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.List Staff          ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Find Staff          ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Delete Staff        ||\n");
		printf("\t\t\t\t\t\t\t\t||        6.Exit                ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%d", &choose);
		while (choose < 1 && choose >6) {
			invalid();
			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     |||| StaffInformation ||||\t\t\b\b\b\b\b||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t||          ||< 1 >||           ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
			printf("\t\t\t\t\t\t\t\t||                              ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||        1.New Staff           ||\n");
			printf("\t\t\t\t\t\t\t\t||        2.Edit Staff          ||\n");
			printf("\t\t\t\t\t\t\t\t||        3.List Staff          ||\n");
			printf("\t\t\t\t\t\t\t\t||        4.Find Staff          ||\n");
			printf("\t\t\t\t\t\t\t\t||        5.Delete Staff        ||\n");
			printf("\t\t\t\t\t\t\t\t||        6.Exit                ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%d", &choose);
		}
		switch (choose) {
		case 1:
			newstaff(staff, &(*numstaff));
			break;
		case 2:
			edit(*numstaff, staff);
			break;
		case 3:
			listall(*numstaff, staff);
			break;
		case 4:
			search(*numstaff, staff);
			break;
		case 5:
			deletestaff(&(*numstaff), staff);
			break;
		case 6:
			return;
			break;
		}
	} while (choose != 6);

}

void newstaff(Staff* staff, int* numstaff) {
	Staff newstaff;
	int num, found = -1;
	printf("\t\t\t\t\t\tEnter how many new staff u need to add ? Lower Than 0 To Back:");
	scanf("%d", &num);
	if (num > 0) {
		for (int i = 1; i <= num; i++)
		{
			printf("\t\t\t\t\t\t||====================================================================================||\n");
			printf("\t||   ||||||||||||||||||||||||   ||\t||\tEnter your name : ");
			rewind(stdin);
			scanf("%[^\n]", &newstaff.name);
			printf("\t||   |||||  ||||||||||  |||||   ||\t||\tEnter your Staff ID : ");
			rewind(stdin);
			do {
				scanf("%[^\n]", &newstaff.staffid);
				rewind(stdin);
				for (int j = 0; j < *numstaff; j++) {
					if (strcmp(newstaff.staffid, staff[j].staffid) == 0) {
						found = 0;
					}
				}
			} while (found == 0);

			printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tEnter your gender : ");
			scanf("%c", &newstaff.gender);
			printf("\t\b\b\b||     ||||     NewStaff     ||||\t\t\b\b\b\b\b||\t||\tEnter your Contact Number  : ");
			rewind(stdin);
			scanf("%[^\n]", &newstaff.contactno);
			printf("\t\b\b\b||=====||||==================||||=====||\t||\t(F = Financial Department , I = IT Department , M = Marketing Department)\n");
			printf("\t||===||||||||||||||||||||||||===||\t||\t(R = Research and Development Department, P = Production Department)\n");
			printf("\t||          ||< %d >||           ||\t||\tEnter your Position :", i);
			rewind(stdin);
			scanf("%c", &newstaff.position);
			printf("\t\t\t\t\t\t||\n");
			printf("\t\t\t\t\t\t||====================================================================================||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||         <<PASSWORD>>         ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%s", &newstaff.password);

			staff[*numstaff] = newstaff;
			(*numstaff)++;
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||       <<SUCCESFULLY>>        ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
	}
	else
	{
		return;
	}

}

void search(int numstaff, Staff staff[]) {
	char searchString[30], searchChar;
	int index = -1, ans;
	printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
	printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||      Search      ||||\t\t\b\b\b\b\b||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
	printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
	printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
	printf("\t\t\t\t\t\t\t\t||          ||< 1 >||           ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
	printf("\t\t\t\t\t\t\t\t||                              ||\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t||            <<By>>            ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||        1.Staff ID            ||\n");
	printf("\t\t\t\t\t\t\t\t||        2.Name                ||\n");
	printf("\t\t\t\t\t\t\t\t||        3.Position            ||\n");
	printf("\t\t\t\t\t\t\t\t||        4.Gender              ||\n");
	printf("\t\t\t\t\t\t\t\t||        5.Exit                ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	scanf("%d", &ans);
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	while (ans < 1 && ans > 5) {
		invalid();
		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||      Search      ||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||< 4 >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||            <<By>>            ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Staff ID            ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Name                ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Position            ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Gender              ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Exit                ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%d", &ans);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	}
	switch (ans) {
	case 1:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||      < Enter StaffID >       ||\n");
		printf("\t\t\t\t\t\t\t\t||        =============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%s", searchString);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");

		for (int i = 0; i < numstaff; i++)
		{
			if (strcmp(staff[i].staffid, searchString) == 0) {
				printf("\t\t\t\t\t\t||===================================================================||\n");
				printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].staffid);
				printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].name);
				printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].gender);
				printf("\t\b\b\b||     ||||     TheStaff     ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %-15s\t\t\t\t\b\b\b||\n", staff[i].contactno);
				printf("\t\b\b\b||=====||||==================||||=====||\t||\tPosition : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].position);
				printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||===================================================================||\n");
				index = i;
			}
		}
		if (index == -1) {
			invalid();
		}
		break;
	case 2:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||        <<Enter Name>>        ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%[^\n]", searchString);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		for (int i = 0; i < numstaff; i++)
		{
			if (strcmp(staff[i].name, searchString) == 0) {
				printf("\t\t\t\t\t\t||===================================================================||\n");
				printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].staffid);
				printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].name);
				printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].gender);
				printf("\t\b\b\b||     ||||     TheStaff     ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %-15s\t\t\t\t\b\b\b||\n", staff[i].contactno);
				printf("\t\b\b\b||=====||||==================||||=====||\t||\tPosition : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].position);
				printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||===================================================================||\n");
				index = i;
			}
		}
		if (index == -1) {
			printf("No Record Found\n");
		}
		break;
	case 3:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||      <<Enter POSITION>>      ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%c", &searchChar);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		for (int i = 0; i < numstaff; i++)
		{
			if (staff[i].position == searchChar) {
				printf("\t\t\t\t\t\t||===================================================================||\n");
				printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].staffid);
				printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].name);
				printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].gender);
				printf("\t\b\b\b||     ||||     TheStaff     ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %-15s\t\t\t\t\b\b\b||\n", staff[i].contactno);
				printf("\t\b\b\b||=====||||==================||||=====||\t||\tPosition : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].position);
				printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||===================================================================||\n");
				index = i;
			}
		}
		if (index == -1) {
			invalid();
		}
		break;
	case 4:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||       <<Enter GENDER>>       ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%c", &searchChar);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		for (int i = 0; i < numstaff; i++)
		{
			if (staff[i].gender == searchChar) {
				printf("\t\t\t\t\t\t||===================================================================||\n");
				printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].staffid);
				printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].name);
				printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].gender);
				printf("\t\b\b\b||     ||||     TheStaff     ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %-15s\t\t\t\t\b\b\b||\n", staff[i].contactno);
				printf("\t\b\b\b||=====||||==================||||=====||\t||\tPosition : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].position);
				printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
				printf("\t\t\t\t\t\t||===================================================================||\n");
				index = i;
			}
		}
		if (index == -1) {
			invalid();
		}
		break;
	case 5:
		return;
		break;
	}
}

void edit(int numstaff, Staff* staff) {
	char name[30];
	char staffid[10];
	char gender;
	char contactno[30];
	char position;
	int find = -1, choice;
	char newgender;

	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||      < Enter StaffID >       ||\n");
	printf("\t\t\t\t\t\t\t\t||        <  to Edit  >         ||\n");
	printf("\t\t\t\t\t\t\t\t||        =============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%s", staffid);
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	for (int i = 0; i < numstaff; i++)
	{
		if (strcmp(staff[i].staffid, staffid) == 0)
		{
			find = i;
		}
	}

	if (find == -1) {
		invalid();
		return;
	}
	do {
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[find].staffid);
		printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[find].name);
		printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[find].gender);
		printf("\t\b\b\b||     ||||     TheStaff     ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %-15s\t\t\t\t\b\b\b||\n", staff[find].contactno);
		printf("\t\b\b\b||=====||||==================||||=====||\t||\tPosition : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[find].position);
		printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t\t\t\t\t\t\t\t||    <<Which Field To Edit>>   ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Staff Name          ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Gender              ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Contact No          ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Department          ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Cancel Action       ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%d", &choice);
		while (choice < 1 && choice > 5) {
			printf("\t\t\t\t\t\t||===================================================================||\n");
			printf("\t\t\t\t\t\t\t\t||    <<Which Field To Edit>>   ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||        1.Staff Name          ||\n");
			printf("\t\t\t\t\t\t\t\t||        2.Gender              ||\n");
			printf("\t\t\t\t\t\t\t\t||        3.Contact No          ||\n");
			printf("\t\t\t\t\t\t\t\t||        4.Department          ||\n");
			printf("\t\t\t\t\t\t\t\t||        5.Cancel Action       ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%d", &choice);

		}
		switch (choice) {
		case 1:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      <<Enter New Name>>      ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%[^\n]", name);
			if (strlen(name) > 0) {
				strcpy(staff[find].name, name);
			}
			break;
		case 2:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||    <<Enter New Gender>>      ||\n");
			printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%c", &newgender);
			toupper(newgender);
			while (newgender != 'M' && newgender != 'F') {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t|| <Please Enter  Valid Gender> ||\n");
				printf("\t\t\t\t\t\t\t\t||    <<Enter New Gender>>      ||\n");
				printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
				printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
				rewind(stdin);
				scanf("%c", &newgender);
				toupper(newgender);
			}
			staff[find].gender = newgender;
			break;
		case 3:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||    <<Enter New ContactNo>>     ||\n");
			printf("\t\t\t\t\t\t\t\t||      ===================       ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%s", contactno);
			if (strlen(contactno) > 0) {
				strcpy(staff[find].contactno, contactno);
			}
			break;
		case 4:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||        <<Department>>        ||\n");
			printf("\t\t\t\t\t\t\t\t||   F: Financial I:IT          ||\n");
			printf("\t\t\t\t\t\t\t\t||   M: Marketing R:Research    ||\n");
			printf("\t\t\t\t\t\t\t\t||   P: Production              ||\n");
			printf("\t\t\t\t\t\t\t\t||    <<Enter New Position>>    ||\n");
			printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%c", &position);
			position = toupper(position);
			while (position != 'F' && position != 'I' && position != 'M' && position != 'R' && position != 'P') {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||  Invalid Position Try Again  ||\n");
				printf("\t\t\t\t\t\t\t\t||        <<Department>>        ||\n");
				printf("\t\t\t\t\t\t\t\t||   F: Financial I:IT          ||\n");
				printf("\t\t\t\t\t\t\t\t||   M: Marketing R:Research    ||\n");
				printf("\t\t\t\t\t\t\t\t||   P: Production              ||\n");
				printf("\t\t\t\t\t\t\t\t||    <<Enter New Position>>    ||\n");
				printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
				printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
				rewind(stdin);
				scanf("%c", &position);
				position = toupper(position);
			}
			staff[find].position = position;
			break;
		case 5:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      ! Edit succesfully !    ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			return;
			break;
		}
	} while (choice != 5);

}

void listall(int numstaff, Staff staff[]) {
	for (int i = 0; i < numstaff; i++)
	{
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].staffid);
		printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", staff[i].name);
		printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].gender);
		printf("\t\b\b\b||     ||||     TheStaff     ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %-15s\t\t\t\t\b\b\b||\n", staff[i].contactno);
		printf("\t\b\b\b||=====||||==================||||=====||\t||\tPosition : %c\t\t\t\t\t\t\t\b\b\b||\n", staff[i].position);
		printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||===================================================================||\n");

	}

}

void deletestaff(int* numstaff, Staff* staff) {
	char id[10];
	int index = -1;
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||         Enter StaffID        ||\n");
	printf("\t\t\t\t\t\t\t\t||      you want to delete      ||\n");
	printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%[^\n]", id);
	rewind(stdin);
	for (int i = 0; i < *numstaff; i++) {
		if (strcmp(staff[i].staffid, id) == 0) {
			index = i;
		}
	}

	if (index == -1) {
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||        ! %s unfounded !        ||\n", id);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		return;
	}
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||   ! %s delete succesfully !   ||\n", staff[index].staffid);
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	for (int i = index; i < *numstaff; i++) {
		staff[i] = staff[i + 1];
	}
	(*numstaff)--;

}
//-----------------------------------------------------------------End Of Staff Information Module-----------------------------------------------------------------------


//-----------------------------------------------------------------Start Of Member Information Module-----------------------------------------------------------------------
void MemberInformationModule(member* members, int* num_member) {
	int option;
	do {
		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||Member Information||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||< 2 >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Add Member          ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.List Member         ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Edit Member         ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Find Member         ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Delete Member       ||\n");
		printf("\t\t\t\t\t\t\t\t||        6.Exit                ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%d", &option);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		while (option < 1 && option > 6) {
			invalid();
			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||Member Information||||\t\t\b\b\b\b\b||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t||          ||< 2 >||           ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
			printf("\t\t\t\t\t\t\t\t||                              ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||        1.Add Member          ||\n");
			printf("\t\t\t\t\t\t\t\t||        2.List Member         ||\n");
			printf("\t\t\t\t\t\t\t\t||        3.Edit Member         ||\n");
			printf("\t\t\t\t\t\t\t\t||        4.Find Member         ||\n");
			printf("\t\t\t\t\t\t\t\t||        5.Delete Member       ||\n");
			printf("\t\t\t\t\t\t\t\t||        6.Exit                ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%d", &option);
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
		switch (option)
		{
		case 1:
			addMember(members, &(*num_member));
			break;
		case 2:
			listMember(members, *num_member);
			break;
		case 3:
			editMember(members, *num_member);
			break;
		case 4:
			findMember(members, *num_member);
			break;
		case 5:
			deleteMember(members, &(*num_member));
			break;
		case 6:
			return;
			break;
		}
	} while (option != 6);


}

void addMember(member* members, int* num_member) {
	int n;
	member temp;
	int repeat = -1;
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t||    << Enter the number >>    ||\n");
	printf("\t\t\t\t\t\t\t\t||<< of new members(< 0 Back) >>||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	scanf("%d", &n);

	if (n > 0) {
		for (int i = 0; i < n; i++) {

			do
			{

				repeat = -1;
				printf("\n\t\t\t\t\t\t||====================================================================================||\n");
				printf("\t||   ||||||||||||||||||||||||   ||\t||\tEnter your ID : ");
				rewind(stdin);
				scanf("%s", &temp.id);
				rewind(stdin);
				for (int a = 0; a < *num_member; a++)
				{
					if (strcmp(temp.id, members[a].id) == 0)
					{
						repeat = 0;
					}
				}
			} while (repeat == 0);
			do {
				repeat = -1;
				printf("\t||   |||||  ||||||||||  |||||   ||\t||\tEnter your name : ");
				scanf("%[^\n]", &temp.name);
				rewind(stdin);
				for (int a = 0; a < *num_member; a++)
				{
					if (strcmp(temp.name, members[a].id) == 0)
					{
						repeat = 0;
					}
				}
			} while (repeat == 0);

			printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tEnter your gender : ");
			scanf("%c", &temp.gender);
			while (temp.gender != 'F' && temp.gender != 'M') {
				invalid();
				printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tEnter your gender : ");
				scanf("%c", &temp.gender);
			}
			rewind(stdin);
			printf("\t\b\b\b||     ||||     NewMember    ||||\t\t\b\b\b\b\b||\t||\tEnter your Contact Number  : ");
			scanf("%d", &temp.contact);
			rewind(stdin);
			printf("\t\b\b\b||=====||||==================||||=====||\t||\n");
			printf("\t||===||||||||||||||||||||||||===||\t||\n");
			printf("\t||          ||< %d >||           ||\t||\tEnter your IC Number :", i + 1);
			scanf("%s", &temp.ic);
			if (temp.gender == 'F') {
				while (temp.ic[11] % 2 == 0) {
					printf("Invalid IC.No For Female!!");
					printf("\t\b\b\b||=====||||==================||||=====||\t||\n");
					printf("\t||===||||||||||||||||||||||||===||\t||\n");
					printf("\t||          ||< %d >||           ||\t||\tEnter your IC Number :", i + 1);
					scanf("%s", &temp.ic);
				}
			}
			else if (temp.gender == 'M') {
				while (temp.ic[11] % 2 == 1) {
					printf("Invalid IC.No For Male!!");
					printf("\t\b\b\b||=====||||==================||||=====||\t||\n");
					printf("\t||===||||||||||||||||||||||||===||\t||\n");
					printf("\t||          ||< %d >||           ||\t||\tEnter your IC Number :", i + 1);
					scanf("%s", &temp.ic);
				}

			}
			printf("\t\t\t\t\t\t||====================================================================================||\n");
			rewind(stdin);
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||         <<Password>>         ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%[^\n]", &temp.password);
			rewind(stdin);

			members[*num_member] = temp;
			(*num_member)++;
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||       <<Succesfully>>        ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
	}
	else {
		return
			;
	}

}

void listMember(member members[], int num_member) {

	for (int i = 0; i < num_member; i++) {
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", members[i].id);
		printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", members[i].name);
		printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", members[i].gender);
		printf("\t\b\b\b||     ||||     TheMember    ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %d\t\t\t\t\t\b\b\b||\n", members[i].contact);
		printf("\t\b\b\b||=====||||==================||||=====||\t||\tMemberIC : %-15s\t\t\t\t\t\b\b\b||\n", members[i].ic);
		printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||===================================================================||\n");
	}

}

void editMember(member* members, int num_member) {
	char name[50], newgender, password[20], ic[30];
	int contact, found = 0, choice;

	found = loginMember(members, num_member);
	do {
		printf("\n\t\t\t\t\t\t\b\b>>Current information for member %s:\n", members[found].id);
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", members[found].id);
		printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", members[found].name);
		printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", members[found].gender);
		printf("\t\b\b\b||     ||||     TheMember    ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %d\t\t\t\t\t\b\b\b||\n", members[found].contact);
		printf("\t\b\b\b||=====||||==================||||=====||\t||\tMemberIC : %-15s\t\t\t\t\t\b\b\b||\n", members[found].ic);
		printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t\t\t\t\t\t\t\t||    <<Which Field To Edit>>   ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Member Name         ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Gender              ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Contact No          ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.IC Number           ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Password            ||\n");
		printf("\t\t\t\t\t\t\t\t||        6.Cancel Action       ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%d", &choice);
		while (choice < 1 && choice > 6) {
			invalid();
			printf("\t\t\t\t\t\t||===================================================================||\n");
			printf("\t\t\t\t\t\t\t\t||    <<Which Field To Edit>>   ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||        1.Member Name         ||\n");
			printf("\t\t\t\t\t\t\t\t||        2.Gender              ||\n");
			printf("\t\t\t\t\t\t\t\t||        3.Contact No          ||\n");
			printf("\t\t\t\t\t\t\t\t||        4.IC Number           ||\n");
			printf("\t\t\t\t\t\t\t\t||        5.Password            ||\n");
			printf("\t\t\t\t\t\t\t\t||        6.Cancel Action       ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%d", &choice);
		}
		switch (choice) {
		case 1:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||     << Enter New Name >>     ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%[^\n]", name);
			strcpy(members[found].name, name);
			break;
		case 2:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||   << Enter New Gender >>     ||\n");
			printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%c", &newgender);
			newgender = toupper(newgender);
			while (newgender != 'M' && newgender != 'F') {
				invalid();
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||   << Enter New Gender >>     ||\n");
				printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
				printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
				rewind(stdin);
				scanf("%c", &newgender);
				newgender = toupper(newgender);
			}
			members[found].gender = newgender;
			break;
		case 3:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||   << Enter New ContactNo >>    ||\n");
			printf("\t\t\t\t\t\t\t\t||      ===================       ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%d", &contact);
			members[found].contact = contact;
			break;
		case 4:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||   << Enter New IC Number >>    ||\n");
			printf("\t\t\t\t\t\t\t\t||         << Without - >>        ||\n");
			printf("\t\t\t\t\t\t\t\t||      ===================       ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%s", &ic);
			if (members[found].gender == 'F') {
				while (ic[11] % 2 == 0) {
					printf("Invalid IC.No For Female!!");
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||   << Enter New IC Number >>    ||\n");
					printf("\t\t\t\t\t\t\t\t||         << Without - >>        ||\n");
					printf("\t\t\t\t\t\t\t\t||      ===================       ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					rewind(stdin);
					scanf("%s", &ic);
				}
			}
			else if (members[found].gender == 'M') {
				while (ic[11] % 2 == 1) {
					printf("Invalid IC.No For Male!!");
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||   << Enter New IC Number >>    ||\n");
					printf("\t\t\t\t\t\t\t\t||         << Without - >>        ||\n");
					printf("\t\t\t\t\t\t\t\t||      ===================       ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					rewind(stdin);
					scanf("%s", &ic);
				}

			}
			strcpy(members[found].ic, ic);
			break;
		case 5:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      << New Password >>      ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%s", password);
			strcpy(members[found].password, password);
			break;
		case 6:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      << Succesfully >>       ||\n");
			printf("\t\t\t\t\t\t\t\t||        << edited >>          ||\n");
			printf("\t\t\t\t\t\t\t\t||        ============          ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			return;
			break;
		}


	} while (choice != 6);
}

void findMember(member members[], int num_member) {
	char id[10];
	int found = 0;
	FILE* fp;
	fp = fopen("member.txt", "r");


	printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||\n");
	printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||||||||||||||||||||||||=====||||||==================\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||==||||||||||||||==||||\t\t||<Search Function>||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||||||==================\n");
	printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
	printf("\t\t\t\t\t\t\t\t||          ||     ||           ||\n");
	printf("\t\t\t\t\t\t\t\t||                              ||\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t|| <<Enter Member ID to Search>>||\n");
	printf("\t\t\t\t\t\t\t\t||   ========================   ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%s", id);
	for (int i = 0; i < num_member; i++) {
		if (strcmp(members[i].id, id) == 0)
		{
			printf("\t\t\t\t\t\t||===================================================================||\n");
			printf("\t||   ||||||||||||||||||||||||   ||\t||\tID : %-15s\t\t\t\t\t\t\b\b\b||\n", members[i].id);
			printf("\t||   |||||  ||||||||||  |||||   ||\t||\tName : %-15s\t\t\t\t\t\t\b\b\b||\n", members[i].name);
			printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tGender : %c\t\t\t\t\t\t\t\b\b\b||\n", members[i].gender);
			printf("\t\b\b\b||     ||||     TheMember    ||||\t\t\b\b\b\b\b||\t||\tContact Number  : %d\t\t\t\t\t\b\b\b||\n", members[i].contact);
			printf("\t\b\b\b||=====||||==================||||=====||\t||\tMemberIC : %-15s\t\t\t\t\t\b\b\b||\n", members[i].ic);
			printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
			printf("\t||          ||     ||           ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
			printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
			printf("\t\t\t\t\t\t||===================================================================||\n");
			found = 1;
		}

	}
	if (found == 0) {
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||      ! Member unfounded !     ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	}
}

void deleteMember(member* members, int* num_member) {
	char id[10];
	int index = -1;
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||        Enter MemberID        ||\n");
	printf("\t\t\t\t\t\t\t\t||      you want to delete      ||\n");
	printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	scanf("%s", id);
	rewind(stdin);
	for (int i = 0; i < *num_member; i++) {
		if (strcmp(members[i].id, id) == 0) {
			index = i;
		}
	}

	if (index == -1) {
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||        ! %s unfounded !        ||\n", id);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		return;
	}
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||   ! %s delete succesfully !   ||\n", members[index].id);
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	for (int i = index; i < *num_member; i++) {
		members[i] = members[i + 1];

		(*num_member)--;
	}

}

int loginMember(member members[], int num_member) {
	char id[10], password[20];
	int index = -1;
	do {
		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||||||||||||||||||||||||=====||||||==================\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||==||||||||||||||==||||\t\t||<Login Function>||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||||||==================\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\t\t\t\t\t\t\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||     ||           ||\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||         <<Member ID>>        ||\n");
		printf("\t\t\t\t\t\t\t\t||         =============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%s", id);
		rewind(stdin);

		for (int i = 0; i < num_member; i++) {
		
			if (strcmp(members[i].id, id) == 0) {
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||         <<Password>>         ||\n");
				printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
				printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
				scanf("%s", password);
				rewind(stdin);
				if (strcmp(members[i].password, password) == 0) {
					welcome();
					index = i;
					return index;
				}
				else {
					invalid();

				}
			}
		}
	} while (index == -1);

}
//-----------------------------------------------------------------End Of Member Information Module-----------------------------------------------------------------------


//-----------------------------------------------------------------Start Of Sales Information Module-----------------------------------------------------------------------
void SalesInformationModule(SalesInformation* salesInfo, int* currentSales, struct stock item[], member members[], Staff staff[], int num_member, int item_number, int staffID) {
	int choice;
	do {
		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||Sales Information||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||< 3 >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Display Record      ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Add Record          ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Search Record       ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Delete Record       ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Modify Record       ||\n");
		printf("\t\t\t\t\t\t\t\t||        6.Revenue             ||\n");
		printf("\t\t\t\t\t\t\t\t||          and Commission      ||\n");
		printf("\t\t\t\t\t\t\t\t||        0.Exit                ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");

		scanf("%d", &choice);
		while (choice < 0 && choice > 6) {
			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||Sales Information||||\t\t\b\b\b\b\b||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t||          ||< 3 >||           ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
			printf("\t\t\t\t\t\t\t\t||                              ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||        1.Display Record      ||\n");
			printf("\t\t\t\t\t\t\t\t||        2.Add Record          ||\n");
			printf("\t\t\t\t\t\t\t\t||        3.Search Record       ||\n");
			printf("\t\t\t\t\t\t\t\t||        4.Delete Record       ||\n");
			printf("\t\t\t\t\t\t\t\t||        5.Modify Record       ||\n");
			printf("\t\t\t\t\t\t\t\t||        6.Revenue             ||\n");
			printf("\t\t\t\t\t\t\t\t||          and Commission      ||\n");
			printf("\t\t\t\t\t\t\t\t||        0.Exit                ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");

		}
		switch (choice) {
		case 1:
			DisplayRecord(salesInfo, *currentSales);
			break;
		case 2:
			AddRecord(&(*currentSales), staffID, salesInfo, item, members, num_member, staff);
			break;
		case 3:
			SearchRecord(*currentSales, salesInfo);
			break;
		case 4:
			DeleteRecord(salesInfo, currentSales, item);
			break;
		case 5:
			ModifyRecord(*currentSales, salesInfo, item, members, staff, item_number, num_member);
			break;
		case 6:
			CalculateRevenue(salesInfo, item, *currentSales, item_number);
			break;
		case 0:
			return;
			break;
		}
	} while (choice != 0);
}

void DisplayRecord(SalesInformation salesInfo[], int currentSales) {
	printf("\t\t\t\t||=============================================================================================||\n");
	printf("\t\t\t\t|| %-10s|%-10s|%-15s|%-12s|%-15s|%-15s|%-8s ||\n", "SalesID", "ItemCode", "QuantityOrder", "Price(RM)", "Purchased By", "Recorded By", "Time");
	printf("\t\t\t\t||=============================================================================================||\n");
	printf("\t\t\t\t||Date : %02d-%02d-%d\t\t\t\t\t\t\t\t\t\t\b||\n", salesInfo[0].timeAdd.day, salesInfo[0].timeAdd.month, salesInfo[0].timeAdd.year);
	printf("\t\t\t\t||=============================================================================================||\n");
	for (int i = 0; i < currentSales; i++) {
		if (i != 0) {
			if (salesInfo[i].timeAdd.day != salesInfo[i - 1].timeAdd.day || salesInfo[i].timeAdd.month != salesInfo[i - 1].timeAdd.month || salesInfo[i].timeAdd.year != salesInfo[i - 1].timeAdd.year) {
				printf("\t\t\t\t||Date : %02d-%02d-%d\t\t\t\t\t\t\t\t\t\t\b||\n", salesInfo[i].timeAdd.day, salesInfo[i].timeAdd.month, salesInfo[i].timeAdd.year);
				printf("\t\t\t\t||=============================================================================================||\n");
			}
		}
		printf("\t\t\t\t||%-10s|%-10s|%-15d|%-12.2f|%-15s|%-15s|%02d:%02d:%02d  ||\n", salesInfo[i].salesID, salesInfo[i].itemCode, salesInfo[i].quantityOrder, salesInfo[i].price, salesInfo[i].memberID, salesInfo[i].staffID, salesInfo[i].timeAdd.hour, salesInfo[i].timeAdd.minute, salesInfo[i].timeAdd.second);
		printf("\t\t\t\t||---------------------------------------------------------------------------------------------||\n");

	}

	printf("\t\t\t\t||=============================================================================================||\n");
}

void AddRecord(int* currentSales, int staffID, SalesInformation* salesInfo, struct stock* item, member members[], int num_member, Staff staff[]) {
	SalesInformation temp;
	char confirm, another;
	int index = -1, num = *currentSales;
	strcpy(temp.staffID, staff[staffID].staffid);
	do {
		GetLocalTime(&time);
		temp.timeAdd.day = time.wDay;
		temp.timeAdd.month = time.wMonth;
		temp.timeAdd.year = time.wYear;
		temp.timeAdd.hour = time.wHour;
		temp.timeAdd.minute = time.wMinute;
		temp.timeAdd.second = time.wSecond;
		if (currentSales == 0) {
			strcpy(temp.salesID, "R001");
		}
		else {
			strcpy(temp.salesID, salesInfo[*currentSales - 1].salesID);
			temp.salesID[3]++;
			while (temp.salesID[3] >= ':') {
				temp.salesID[3] = '0';
				temp.salesID[2]++;
				while (temp.salesID[2] >= ':') {
					temp.salesID[2] = '0';
					temp.salesID[1]++;
				}
			}
		}
		printf("\t\t\t\t\t\t||===================================================================||\n");
		printf("\t||   ||||||||||||||||||||||||   ||\t||\tSales ID : %-15s\t\t\t\t\t\b\b\b||\n", temp.salesID);
		printf("\t||   |||||  ||||||||||  |||||   ||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\b\b\b|| ||==||||==================||||==|| ||\t||\tStaff ID : % -15s\t\t\t\t\t\b\b\b||\n", temp.staffID);
		printf("\t\b\b\b||     ||||     The Sales    ||||\t\t\b\b\b\b\b||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\b\b\b||=====||||==================||||=====||\t||\tDate : %02d-%02d-%d\t\t\t\t\t\t\b\b\b||\n", temp.timeAdd.day, temp.timeAdd.month, temp.timeAdd.year);
		printf("\t||===||||||||||||||||||||||||===||\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t||          ||     ||           ||\t||\tTime : %02d:%02d:%02d\t\t\t\t\t\t\t\b\b\b||\n", temp.timeAdd.hour, temp.timeAdd.minute, temp.timeAdd.second);
		printf("\t\t\t\t\t\t||\t\t\t\t\t\t\t\t\t\b\b\b||\n");
		printf("\t\t\t\t\t\t||===================================================================||\n");
		do {
			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||||||||||||||||||||||||=====||||||==================\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||==||||||||||||||==||||\t\t||  <Add Function>||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||||||==================\n");
			printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\t\t\t\t\t\t\n");
			printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t||          ||     ||           ||\n");
			printf("\t\t\t\t\t\t\t\t||                              ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t|| <<Enter Member ID to Search>>||\n");
			printf("\t\t\t\t\t\t\t\t||   ========================   ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%s", temp.memberID);
			rewind(stdin);
			for (int i = 0; i < num_member; i++) {

				if (strcmp(members[i].id, temp.memberID) == 0) {
					index = i;
				}
			}
			if (index == -1) {
				invalid();
			}
		} while (index == -1);
		index = -1;
		do {

			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||     << Enter ItemCode >>     ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%s", temp.itemCode);
			rewind(stdin);
			for (int i = 0; i < *currentSales; i++) {
				if (strcmp(item[i].code, temp.itemCode) == 0) {
					index = i;
				}
			}
			if (index == -1) {
				invalid();
			}
		} while (index == -1);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     << Enter Quantity >>     ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%d", &temp.quantityOrder);
		while (temp.quantityOrder > item[index].quantity) {
			printf("||===========================================||\n");
			printf("||The Item Stock Is Not Enough For This Order||\n");
			printf("||       Please Enter Again Quantity.        ||\n");
			printf("||0 = Cancel This Action(Back To Menu Page)  ||\n");
			printf("||===========================================||\n");
			printf("||\t\t\b\b\b\b\b>");;
			scanf("%d", &temp.quantityOrder);
			printf("||===========================================||\n");
			if (temp.quantityOrder == 0) {
				return;
			}

		}
		temp.price = (double)temp.quantityOrder * item[index].price;

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||         << Preview >>        ||\n");
		printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
		printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", temp.salesID);
		printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", temp.memberID);
		printf("\t\t\t\t\t\t\t\t||    Staff ID    :%s\t\t||\n", temp.staffID);
		printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", temp.timeAdd.day, temp.timeAdd.month, temp.timeAdd.year);
		printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", temp.timeAdd.hour, temp.timeAdd.minute, temp.timeAdd.second);
		printf("\t\t\t\t\t\t\t\t||    Item        :%s\t||\n", item[index].description);
		printf("\t\t\t\t\t\t\t\t||    Item code   :(%s)\t||\n", temp.itemCode);
		printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", temp.quantityOrder);
		printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", temp.price);
		printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");

		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||Confirm to Add This Order to Sales Record ?||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%c", &confirm);
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
		rewind(stdin);
		confirm = toupper(confirm);
		while (confirm != 'Y' && confirm != 'N') {
			invalid();
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||Confirm to Add This Order to Sales Record ?||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
			scanf("%c", &confirm);
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
			rewind(stdin);
			confirm = toupper(confirm);
		}
		if (confirm == 'Y') {
			item[index].quantity = item[index].quantity - temp.quantityOrder;
			item[index].outstock += temp.quantityOrder;
			salesInfo[*currentSales] = temp;

			printf("\t\t\t\t\t\t\t\t||==============================||\n");
			printf("\t\t\t\t\t\t\t\t||      ====================    ||\n");
			printf("\t\t\t\t\t\t\t\t||     <<Sales Record Added>>   ||\n");
			printf("\t\t\t\t\t\t\t\t||      ====================    ||\n");
			printf("\t\t\t\t\t\t\t\t||==============================||\n");
			(*currentSales)++;
		}
		else if (confirm == 'N') {

			printf("\t\t\t\t\t\t\t\t||==============================||\n");
			printf("\t\t\t\t\t\t\t\t||     =====================    ||\n");
			printf("\t\t\t\t\t\t\t\t||   <<Sales Record Canceled>>  ||\n");
			printf("\t\t\t\t\t\t\t\t||     =====================    ||\n");
			printf("\t\t\t\t\t\t\t\t||==============================||\n");

			return;
		}

		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||            Add Another Record ?           ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");

		scanf("%c", &another);
		rewind(stdin);
		another = toupper(another);
		while (another != 'Y' && another != 'N') {
			invalid();
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||            Add Another Record ?           ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
			scanf("%c", &another);
			rewind(stdin);
			another = toupper(another);

		}
	} while (another == 'Y');


}

void SearchRecord(int currentSales, SalesInformation salesInfo[]) {

	while (currentSales > 0) {
		int choice, index = 0, searchDay, searchMonth, searchYear;
		char searchID[6];

		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||      Search      ||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||<   >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||            <<By>>            ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Sales ID            ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Member ID           ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Date                ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Exit                ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      < Enter SalesID >       ||\n");
			printf("\t\t\t\t\t\t\t\t||        =============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%s", searchID);
			rewind(stdin);

			for (int i = 0; i < currentSales; i++) {
				if (strcmp(searchID, salesInfo[i].salesID) == 0) {

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
					printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
					printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", salesInfo[i].salesID);
					printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", salesInfo[i].memberID);
					printf("\t\t\t\t\t\t\t\t||    Staff ID    :%s\t\t||\n", salesInfo[i].staffID);
					printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", salesInfo[i].timeAdd.day, salesInfo[i].timeAdd.month, salesInfo[i].timeAdd.year);
					printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", salesInfo[i].timeAdd.hour, salesInfo[i].timeAdd.minute, salesInfo[i].timeAdd.second);
					printf("\t\t\t\t\t\t\t\t||    Item        :%s\t||\n", salesInfo[i].itemCode);
					printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", salesInfo[i].quantityOrder);
					printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", salesInfo[i].price);
					printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					index++;
				}

			}
			if (index > 0) {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||      ! %d record founded !\t||\n", index);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
			else {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||      ! %d record unfounded !\t||\n", index);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
			break;
		case 2:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      < Enter MemberID >      ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%s", searchID);
			rewind(stdin);

			for (int i = 0; i < currentSales; i++) {
				if (strcmp(searchID, salesInfo[i].memberID) == 0) {
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
					printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
					printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", salesInfo[i].salesID);
					printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", salesInfo[i].memberID);
					printf("\t\t\t\t\t\t\t\t||    Staff ID    :%s\t\t||\n", salesInfo[i].staffID);
					printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", salesInfo[i].timeAdd.day, salesInfo[i].timeAdd.month, salesInfo[i].timeAdd.year);
					printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", salesInfo[i].timeAdd.hour, salesInfo[i].timeAdd.minute, salesInfo[i].timeAdd.second);
					printf("\t\t\t\t\t\t\t\t||    Item        :%s\t||\n", salesInfo[i].itemCode);
					printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", salesInfo[i].quantityOrder);
					printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", salesInfo[i].price);
					printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					index++;
				}

			}
			if (index > 0) {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||      ! %d record founded !\t||\n", index);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
			else {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||      ! %d record unfounded !\t||\n", index);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
			break;
		case 3:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||         < Enter Day >        ||\n");
			printf("\t\t\t\t\t\t\t\t||           =========          ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%d", &searchDay);
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||        < Enter Month >       ||\n");
			printf("\t\t\t\t\t\t\t\t||          ===========         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%d", &searchMonth);
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||        < Enter Year >        ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%d", &searchYear);

			for (int i = 0; i < currentSales; i++) {
				if (searchDay == salesInfo[i].timeAdd.day && searchMonth == salesInfo[i].timeAdd.month && searchYear == salesInfo[i].timeAdd.year) {
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
					printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
					printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", salesInfo[i].salesID);
					printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", salesInfo[i].memberID);
					printf("\t\t\t\t\t\t\t\t||    Staff ID    :%s\t\t||\n", salesInfo[i].staffID);
					printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", salesInfo[i].timeAdd.day, salesInfo[i].timeAdd.month, salesInfo[i].timeAdd.year);
					printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", salesInfo[i].timeAdd.hour, salesInfo[i].timeAdd.minute, salesInfo[i].timeAdd.second);
					printf("\t\t\t\t\t\t\t\t||    Item        :%s\t||\n", salesInfo[i].itemCode);
					printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", salesInfo[i].quantityOrder);
					printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", salesInfo[i].price);
					printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					index++;
				}

			}
			if (index > 0) {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||      ! %d record founded !\t||\n", index);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
			else {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||      ! %d record unfounded !\t||\n", index);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			}
			break;
		case 4:

			return;
			break;
		default:
			invalid();
			continue;
		}
	}

}

void DeleteRecord(SalesInformation* salesInfo, int* currentSales, struct stock item[]) {
	char deleteID[5], confirm, another;
	do {

		int index = -1;

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||   Enter SalesID to delete    ||\n");
		printf("\t\t\t\t\t\t\t\t||(Type 'Back' To Cancel Action)||\n");
		printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%s", deleteID);
		rewind(stdin);
		if (strcmp("Back", deleteID) == 0) {

			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||      <<Action Canceled>>     ||\n");
			printf("\t\t\t\t\t\t\t\t||    Going Back To Menu Page   ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			return;
		}

		for (int i = 0; i < *currentSales; i++) {
			if (strcmp(deleteID, salesInfo[i].salesID) == 0) {
				index = i;
			}
		}
		if (index >= 0) {

			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
			printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
			printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", salesInfo[index].salesID);
			printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", salesInfo[index].memberID);
			printf("\t\t\t\t\t\t\t\t||    Staff ID    :%s\t\t||\n", salesInfo[index].staffID);
			printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", salesInfo[index].timeAdd.day, salesInfo[index].timeAdd.month, salesInfo[index].timeAdd.year);
			printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", salesInfo[index].timeAdd.hour, salesInfo[index].timeAdd.minute, salesInfo[index].timeAdd.second);
			printf("\t\t\t\t\t\t\t\t||    Item        :%s\t\t||\n", salesInfo[index].itemCode);
			printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", salesInfo[index].quantityOrder);
			printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", salesInfo[index].price);
			printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       Confirm to Delete This Order ?      ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
			scanf("%c", &confirm);
			rewind(stdin);
			if (confirm == 'Y') {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
				printf("\t\t\t\t\t\t\t\t||         <<Sales %s>>       ||\n", salesInfo[index].salesID);
				printf("\t\t\t\t\t\t\t\t||       has been deleted       ||\n");
				printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				item[index].quantity = item[index].quantity + salesInfo[index].quantityOrder;
				item[index].outstock -= salesInfo[index].quantityOrder;
				for (int i = index; i < *currentSales - 1; i++) {
					salesInfo[i] = salesInfo[i + 1];
				}
				(*currentSales)--;
			}
		}
		else {

			printf("================================\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||         <<Sales %s>>       ||\n", deleteID);
			printf("\t\t\t\t\t\t\t\t||          Not Founded         ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}

		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           Delete Another Record?          ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
		scanf("%c", &another);
		rewind(stdin);
		another = toupper(another);
		while (another != 'Y' && another != 'N') {
			invalid();
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           Delete Another Record?          ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
			scanf("%c", &another);
			rewind(stdin);
			another = toupper(another);

		}
	} while (another == 'Y');
}

void ModifyRecord(int currentSales, SalesInformation* salesInfo, struct stock* item, member members[], Staff staff[], int item_number, int num_member) {
	char modify[6], confirm, another;
	int index, field, current, itemCheck = -1, idCheck, tempStock;
	do {
		index = -1;
		itemCheck = -1;
		SYSTEMTIME time;
		GetLocalTime(&time);
		SalesInformation temp;

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     << Enter Sales ID >>     ||\n");
		printf("\t\t\t\t\t\t\t\t||       << to Modify >>        ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%s", modify);
		rewind(stdin);
		for (int i = 0; i < currentSales; i++) {
			if (strcmp(salesInfo[i].salesID, modify) == 0) {
				index = i;
			}
		}
		temp = salesInfo[index];
		do {
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
			printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
			printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", salesInfo[index].salesID);
			printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", salesInfo[index].memberID);
			printf("\t\t\t\t\t\t\t\t||    Staff ID    :%s\t\t||\n", salesInfo[index].staffID);
			printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", salesInfo[index].timeAdd.day, salesInfo[index].timeAdd.month, salesInfo[index].timeAdd.year);
			printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", salesInfo[index].timeAdd.hour, salesInfo[index].timeAdd.minute, salesInfo[index].timeAdd.second);
			printf("\t\t\t\t\t\t\t\t||    Item        :%s\t\t||\n", salesInfo[index].itemCode);
			printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", salesInfo[index].quantityOrder);
			printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", salesInfo[index].price);
			printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");

			printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
			printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||       Edit       ||||\t\t\b\b\b\b\b||\n");
			printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
			printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
			printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
			printf("\t\t\t\t\t\t\t\t||          ||<   >||           ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
			printf("\t\t\t\t\t\t\t\t||                              ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||    <<Which Field To Edit>>   ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||        1.Member ID           ||\n");
			printf("\t\t\t\t\t\t\t\t||        2.Staff ID            ||\n");
			printf("\t\t\t\t\t\t\t\t||        3.Date and Time       ||\n");
			printf("\t\t\t\t\t\t\t\t||        4.Item,Quantity       ||\n");
			printf("\t\t\t\t\t\t\t\t||          and Price           ||\n");
			printf("\t\t\t\t\t\t\t\t||        5.Cancel Action       ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
			printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
			printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%d", &field);
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			switch (field) {
			case 1:
				idCheck = -1;

				do {

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||   << Enter New MemberID >>   ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%s", temp.memberID);
					rewind(stdin);
					for (int i = 0; i < num_member; i++) {

						if (strcmp(members[i].id, temp.memberID) == 0) {
							idCheck = i;
						}
					}
					if (idCheck == -1) {
						invalid();
					}
				} while (idCheck == -1);
				break;
			case 2:
				idCheck = -1;

				do {

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||   << Enter New StaffID >>    ||\n");
					printf("\t\t\t\t\t\t\t\t||      =================       ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%s", temp.staffID);
					rewind(stdin);
					for (int i = 0; i < num_member; i++) {

						if (strcmp(staff[i].staffid, temp.staffID) == 0) {
							idCheck = i;
						}
					}
					if (idCheck == -1) {
						invalid();
					}
				} while (idCheck == -1);
				break;
			case 3:

				printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
				printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       1.Use Current Date and Time         ||\n");
				printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       2.Manually Type New Date and Time   ||\n");
				printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
				printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
				rewind(stdin);
				scanf("%d", &current);
				if (current == 1) {
					GetLocalTime(&time);
					temp.timeAdd.day = time.wDay;
					temp.timeAdd.month = time.wMonth;
					temp.timeAdd.year = time.wYear;
					temp.timeAdd.hour = time.wHour;
					temp.timeAdd.minute = time.wMinute;
					temp.timeAdd.second = time.wSecond;
				}
				else if (current == 2) {

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||     << Enter New Day >>      ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%d", &temp.timeAdd.day);
					while (temp.timeAdd.day > 31 && temp.timeAdd.day < 1) {
						invalid();
						printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
						printf("\t\t\t\t\t\t\t\t||     << Enter New Day >>      ||\n");
						printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
						printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
						scanf("%d", &temp.timeAdd.day);
					}

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||     << Enter New Month >>    ||\n");
					printf("\t\t\t\t\t\t\t\t||        ================      ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%d", &temp.timeAdd.month);
					while (temp.timeAdd.month > 12 && temp.timeAdd.month < 1) {
						invalid();
						printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
						printf("\t\t\t\t\t\t\t\t||     << Enter New Month >>    ||\n");
						printf("\t\t\t\t\t\t\t\t||        ================      ||\n");
						printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
						scanf("%d", &temp.timeAdd.month);
					}

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||     << Enter New Year >>     ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%d", &temp.timeAdd.year);
					while (temp.timeAdd.year > time.wYear) {
						invalid();
						printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
						printf("\t\t\t\t\t\t\t\t||     << Enter New Year >>     ||\n");
						printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
						printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
						scanf("%d", &temp.timeAdd.year);
					}
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||     << Enter New Hour >>     ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%d", &temp.timeAdd.hour);
					while (temp.timeAdd.hour > 24 && temp.timeAdd.hour < 0) {
						invalid();
						printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
						printf("\t\t\t\t\t\t\t\t||     << Enter New Hour >>     ||\n");
						printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
						printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
						scanf("%d", &temp.timeAdd.hour);
					}
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||    << Enter New Minute >>    ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%d", &temp.timeAdd.minute);
					while (temp.timeAdd.minute > 59 && temp.timeAdd.minute < 0) {
						invalid();
						printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
						printf("\t\t\t\t\t\t\t\t||    << Enter New Minute >>    ||\n");
						printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
						printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
						scanf("%d", &temp.timeAdd.minute);
					}
					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||    << Enter New Second >>    ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%d", &temp.timeAdd.second);
					while (temp.timeAdd.second > 59 && temp.timeAdd.second < 0) {
						invalid();
						printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
						printf("\t\t\t\t\t\t\t\t||    << Enter New Second >>    ||\n");
						printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
						printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
						scanf("%d", &temp.timeAdd.second);
					}
				}
				break;
			case 4:


				do {

					printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
					printf("\t\t\t\t\t\t\t\t||  << Enter New Item Code >>   ||\n");
					printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
					printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
					scanf("%s", temp.itemCode);
					rewind(stdin);
					for (int i = 0; i < item_number; i++) {

						if (strcmp(item[i].code, temp.itemCode) == 0) {
							itemCheck = i;
						}
					}

					if (itemCheck == -1) {
						invalid();
					}
				} while (itemCheck == -1);
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||   << Enter New Quantity >>   ||\n");
				printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
				printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
				scanf("%d", &temp.quantityOrder);
				tempStock = item[itemCheck].quantity;
				tempStock += salesInfo[index].quantityOrder;
				item[itemCheck].outstock += salesInfo[index].quantityOrder;
				while (temp.quantityOrder > tempStock) {

					printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
					printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||The Item Stock Is Not Enough For This Order||\n");
					printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||   Please Enter Again Quantity. 0 = Back   ||\n");
					printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
					printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");

					scanf("%d", &temp.quantityOrder);
				}
				if (temp.quantityOrder == 0) {
					continue;
				}
				temp.price = temp.quantityOrder * item[itemCheck].price;
				item[itemCheck].outstock -= temp.quantityOrder;
				break;
			case 5:
				return;
				break;
			default:
				invalid();
				continue;
			}
			printf("\t\t\t\t\t\t\t\t||==============================||\n");
			printf("\t\t\t\t\t\t\t\t|| New Record for %s\n", modify);

			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
			printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
			printf("\t\t\t\t\t\t\t\t||    Sales ID    :%s\t\t||\n", temp.salesID);
			printf("\t\t\t\t\t\t\t\t||    Member ID   :%s\t||\n", temp.memberID);
			printf("\t\t\t\t\t\t\t\t||    Staff ID    :%-13s||\n", temp.staffID);
			printf("\t\t\t\t\t\t\t\t||    Date        :%02d-%02d-%d\t||\n", temp.timeAdd.day, temp.timeAdd.month, temp.timeAdd.year);
			printf("\t\t\t\t\t\t\t\t||    Time        :%02d:%02d:%02d\t||\n", temp.timeAdd.hour, temp.timeAdd.minute, temp.timeAdd.second);
			printf("\t\t\t\t\t\t\t\t||    Item        :%s\t||\n", item[index].description);
			printf("\t\t\t\t\t\t\t\t||    Item        :%s\t||\n", temp.itemCode);
			printf("\t\t\t\t\t\t\t\t||    Quantity    :%d\t\t||\n", temp.quantityOrder);
			printf("\t\t\t\t\t\t\t\t||    Total Price :%.2f\t||\n", temp.price);
			printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");

			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||   << Confirm The Modify? >>  ||\n");
			printf("\t\t\t\t\t\t\t\t||       Y = Yes : N = No       ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%c", &confirm);
			rewind(stdin);
			confirm = toupper(confirm);
			if (confirm == 'Y') {
				salesInfo[index] = temp;
				item[itemCheck].quantity = item[itemCheck].quantity - temp.quantityOrder;
			}
		} while (confirm == 'N');

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t|| << Modify Another Record? >> ||\n");
		printf("\t\t\t\t\t\t\t\t||       Y = Yes : N = No       ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%c", &another);
		rewind(stdin);
		another = toupper(another);
		while (another != 'N' && another != 'Y') {
			invalid();
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t|| << Modify Another Record? >> ||\n");
			printf("\t\t\t\t\t\t\t\t||       Y = Yes : N = No       ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%c", &another);
			rewind(stdin);
			another = toupper(another);
		}
	} while (another == 'Y');
}

void CalculateRevenue(SalesInformation salesInfo[], struct stock item[], int currentSales, int item_number) {
	double revenue[MAX_NUMBER] = { 0 }, commission[MAX_NUMBER] = { 0 }, totalRevenue = 0, totalCommission = 0;

	for (int i = 0; i < currentSales; i++) {
		for (int j = 0; j < item_number; j++) {
			if (strcmp(salesInfo[i].itemCode, item[j].code) == 0) {
				revenue[j] += (item[j].price - item[j].costprice) * (double)salesInfo[i].quantityOrder;
				totalRevenue += (item[j].price - item[j].costprice) * (double)salesInfo[i].quantityOrder;
				commission[j] = revenue[j] / 100 * 5;
			}
		}
	}
	totalCommission = totalRevenue / 100 * 5;
	printf("\t\t\t\t\t||============================================================================||\n");
	printf("\t\t\t\t\t|| %-10s||%-20s||%-15s||%-15s\t\t\b\b||\n", "Code", "Item", "Revenue", "Commission");
	printf("\t\t\t\t\t||============================================================================||\n");
	for (int j = 0; j < item_number; j++) {
		printf("\t\t\t\t\t||%-10s||%-20s||%-15.2f||%-15.2f\t\t\b\b||\n", item[j].code, item[j].description, revenue[j], commission[j]);
	}
	printf("\t\t\t\t\t||============================================================================||\n");
	printf("\t\t\t\t\t|| Current Total Revenue Is : RM%.2f. Total Commission(5%%) Of Staff Is:%.2f||\n", totalRevenue, totalCommission);
	printf("\t\t\t\t\t||============================================================================||\n");

}

//-----------------------------------------------------------------End Of Staff Information Module-----------------------------------------------------------------------


//-----------------------------------------------------------------Start Of Stock Information Module-----------------------------------------------------------------------
void StockInformationModule(struct stock* item, int* item_number) {
	int choice;

	do {

		printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
		printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||Stock  Information||||\t\t\b\b\b\b\b||\n");
		printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
		printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
		printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
		printf("\t\t\t\t\t\t\t\t||          ||< 4 >||           ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
		printf("\t\t\t\t\t\t\t\t||                              ||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<MODULE>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Add Item            ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Delete Item         ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Display All Items   ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Modify Item         ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Search Item         ||\n");
		printf("\t\t\t\t\t\t\t\t||        6.Report              ||\n");
		printf("\t\t\t\t\t\t\t\t||        7.Exit                ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");

		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			add_item(item, &(*item_number));
			break;
		case 2:
			delete_item(item, &(*item_number));
			break;
		case 3:
			display_item(item, *item_number);
			break;
		case 4:
			modify_item(*item_number, item);
			break;
		case 5:
			search_item(item, *item_number);
			break;
		case 6:
			report(item, *item_number);
			break;
		case 7:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||         << Exiting >>        ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			return;
		default:
			invalid();
		}
	} while (choice != 7);



}

void add_item(struct stock* item, int* item_number) {
	int choice, index = -1, addstock;
	char code[10];


	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       1. Add stock to current item        ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       2. Add new item to stock            ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       3. Exit                             ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     << Enter ItemCode >>     ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%s", code);
		for (int i = 0; i < *item_number; i++) {
			if (strcmp(item[i].code, code) == 0) {
				index = i;
			}
		}
		if (index == -1) {

			printf("\t\t\t\t\t\t\t\t||==============================||\n");
			printf("\t\t\t\t\t\t\t\t||     =====================    ||\n");
			printf("\t\t\t\t\t\t\t\t||      << No Item Found >>     ||\n");
			printf("\t\t\t\t\t\t\t\t||     =====================    ||\n");
			printf("\t\t\t\t\t\t\t\t||==============================||\n");
			return;
		}

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||  Enter Quantity Stock To Add ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%d", &addstock);
		item[index].quantity += addstock;
		item[index].restock += addstock;
		break;
	case 2:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     << Enter ItemCode >>     ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%s", item[*item_number].code);
		rewind(stdin);

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t|| << Enter Item discription >> ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%[^\n]", item[*item_number].description);
		rewind(stdin);

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     << Enter Quantity >>     ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%d", &item[*item_number].quantity);

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||       << Enter Price >>      ||\n");
		printf("\t\t\t\t\t\t\t\t||         =============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%lf", &item[*item_number].price);

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     << Enter CostPrice >>    ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%lf", &item[*item_number].costprice);

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||   << Enter Minimumlevel >>   ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%d", &item[*item_number].minimumlevel);
		item[*item_number].restock = item[*item_number].quantity;
		item[*item_number].outstock = 0;
		(*item_number)++;

		break;
	case 3:
		return;
	}

}

void delete_item(struct stock* item, int* item_number) {
	char code[10], ans;
	int found = -1;
	// Ask the user for the code of the item to delete

	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||      Enter product code      ||\n");
	printf("\t\t\t\t\t\t\t\t||   of the product to delete   ||\n");
	printf("\t\t\t\t\t\t\t\t||       ================       ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%s", code);

	// Search for the item with the specified code and delete it if found
	for (int j = 0; j < *item_number; j++) {
		if (strcmp(code, item[j].code) == 0) {
			found = j;
		}
	}

	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||          << Result >>        ||\n");
	printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
	printf("\t\t\t\t\t\t\t\t||    Itemcode    :%s\t\t||\n", item[found].code);
	printf("\t\t\t\t\t\t\t\t||    Description :%s\t||\n", item[found].description);
	printf("\t\t\t\t\t\t\t\t||    Price       :%.2f\t||\n", item[found].price);
	printf("\t\t\t\t\t\t\t\t||    Cost Price  :%.2f\t||\n", item[found].costprice);
	printf("\t\t\t\t\t\t\t\t||    Instock     :%d\t\t||\n", item[found].quantity);
	printf("\t\t\t\t\t\t\t\t||    Minimum level:%d\t\t||\n", item[found].minimumlevel);
	printf("\t\t\t\t\t\t\t\t||  =========================== ||\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       Confirm to Delete This Order ?      ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ( Y = Yes : N = No )            ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
	rewind(stdin);
	scanf("%c", &ans);
	if (toupper(ans) == 'Y') {

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||  ! %s delete succesfully ! ||\n", item[found].code);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		for (int i = found; i < *item_number; i++) {
			item[i] = item[i + 1];
		}

		(*item_number)--;

	}


	if (found == -1) {
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||        ! %s unfounded !        ||\n", code);
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	}
}

void display_item(struct stock item[], int item_number) {
	int choice, count = 0;

	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||===========================================||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       1. All item                         ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       2. Item Need to Restock             ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||       3. Exit                             ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||           ====================            ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b\b\b\b||\t\t\b\b\b\b\b>");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		printf("\t\t\t\t\t\t||=============================================================||\n");
		printf("\t\t\t\t\t\t|| Item code   discription   quantity    price    minimumlevel ||\n");
		printf("\t\t\t\t\t\t|| =========   ===========   ========   =======   ============ ||\n");
		for (int i = 0; i < item_number; i++) {
			printf("\t\t\t\t\t\t|| %-8s ||%-12s ||%-8d ||%-7.2f ||%-12d ||\n", item[i].code, item[i].description, item[i].quantity, item[i].price, item[i].minimumlevel);
			printf("\t\t\t\t\t\t||-------------------------------------------------------------||\n");
			count++;
		}

		printf("\t\t\t\t\t\t||=============================================================||\n");
		printf("\t\t\t\t\t\t||                    < %d product listed >                    ||\n", count);
		printf("\t\t\t\t\t\t||=============================================================||\n");
		break;
	case 2:
		printf("\t\t\t\t\t\t||=============================================================||\n");
		printf("\t\t\t\t\t\t|| Item code   discription   quantity    price    minimumlevel ||\n");
		printf("\t\t\t\t\t\t|| =========   ===========   ========   =======   ============ ||\n");
		for (int i = 0; i < item_number; i++) {
			if (item[i].quantity < item[i].minimumlevel) {
				printf("\t\t\t\t\t\t|| %-8s ||%-12s ||%-8d ||%-7.2f ||%-12d ||\n", item[i].code, item[i].description, item[i].quantity, item[i].price, item[i].minimumlevel);
				printf("\t\t\t\t\t\t||---------------------------------------------------------||\n");
				count++;
			}
		}
		printf("\t\t\t\t\t\t||=============================================================||\n");
		printf("\t\t\t\t\t\t||                    < %d product listed >                    ||\n", count);
		printf("\t\t\t\t\t\t||=============================================================||\n");
		break;
	case 3:
		return;
		break;
	}

}

void modify_item(int item_number, struct stock* item) {
	struct stock temp;
	char code[10], cont, ans;
	double price;
	int quantity, minimumlevel, found, choice;

	do {

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||   << Enter Product Code >>   ||\n");
		printf("\t\t\t\t\t\t\t\t||       << to Modify >>        ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%s", code);
		rewind(stdin);
		found = -1;
		for (int i = 0; i < item_number; i++) {
			if (strcmp(code, item[i].code) == 0) {
				found = i;
			}
		}
		if (found == -1) {

			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||   No product found item = %s ||\n", code);
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			return;
		}
		strcpy(temp.code, item[found].code);

		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||    <<Which Field To Edit>>   ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||        1.Item Description    ||\n");
		printf("\t\t\t\t\t\t\t\t||        2.Item Price          ||\n");
		printf("\t\t\t\t\t\t\t\t||        3.Item Cost           ||\n");
		printf("\t\t\t\t\t\t\t\t||        4.Quantity            ||\n");
		printf("\t\t\t\t\t\t\t\t||        5.Minimum Level       ||\n");
		printf("\t\t\t\t\t\t\t\t||        6.Cancel Action       ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
		printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
		printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||  Enter New item description  ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%[^\n]", &temp.description);
			break;
		case 2:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||      Enter New item price    ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%lf", &temp.price);
			break;
		case 3:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||   Enter New item cost price  ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%lf", &temp.costprice);
			break;
		case 4:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t|| Enter New Quantity in stock  ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%d", &temp.quantity);
			temp.restock = 0;
			temp.outstock = 0;
			if (item[found].quantity > temp.quantity) {
				temp.outstock = item[found].quantity - temp.quantity;
			}
			else if (item[found].quantity < temp.quantity) {
				temp.restock = temp.quantity - item[found].quantity;
			}
			break;
		case 5:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||    Enter New minimumlevel    ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%d", &temp.minimumlevel);
			break;
		case 6:
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||    << Confirm to back >>     ||\n");
			printf("\t\t\t\t\t\t\t\t||      << Y=Yes / N=NO >>      ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			rewind(stdin);
			scanf("%c", &ans);
			if (toupper(ans) == 'Y') {
				item[found] = temp;
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
				printf("\t\t\t\t\t\t\t\t||   Item modified successfully ||\n");
				printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");

				printf("\t\t\t\t\t\t||=============================================================||\n");
				printf("\t\t\t\t\t\t|| Updated Record:                                             ||\n");
				printf("\t\t\t\t\t\t||=============================================================||\n");
				printf("\t\t\t\t\t\t|| Item code   discription   quantity    price    minimumlevel ||\n");
				printf("\t\t\t\t\t\t|| =========   ===========   ========   =======   ============ ||\n");
				printf("\t\t\t\t\t\t|| %-8s ||%-12s ||%-8d ||%-7.2f ||%-12d ||\n", item[found].code, item[found].description, item[found].quantity, item[found].price, item[found].minimumlevel);
				printf("\t\t\t\t\t\t||=============================================================||\n");


			}
			else {

				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
				printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
				printf("\t\t\t\t\t\t\t\t||     Item modify canceled     ||\n");
				printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
				printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");

			}
			return;
			break;
		}


		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t|| << Modify Another Record? >> ||\n");
		printf("\t\t\t\t\t\t\t\t||       Y = Yes : N = No       ||\n");
		printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		rewind(stdin);
		scanf("%c", &cont);
		cont = toupper(cont);
		while (cont != 'N' && cont != 'Y') {
			invalid();
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t|| << Modify Another Record? >> ||\n");
			printf("\t\t\t\t\t\t\t\t||       Y = Yes : N = No       ||\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
			scanf("%c", &cont);
			rewind(stdin);
			cont = toupper(cont);
		}
	} while (toupper(cont) == 'Y');


}

void search_item(struct stock item[], int item_number) {
	char code[10];
	int choice;
	char description[50];

	printf("\t\t\t\t\t\t\t\t||   ||||||||||||||||||||||||   ||\n");
	printf("\t\t\t\t\t\t\t\t||   |||||  ||||||||||  |||||   ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b|| ||==||||==================||||==|| ||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||     ||||      Search      ||||\t\t\b\b\b\b\b||\n");
	printf("\t\t\t\t\t\t\t\t\b\b\b||=====||||==================||||=====||\n");
	printf("\t\t\t\t\t\t\t\t     ||||||||||||||||||||||||\n");
	printf("\t\t\t\t\t\t\t\t||===||||||||||||||||||||||||===||\n");
	printf("\t\t\t\t\t\t\t\t||          ||<   >||           ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n\n\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t||            <<By>>            ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||        1.Item Code           ||\n");
	printf("\t\t\t\t\t\t\t\t||        2.Description         ||\n");
	printf("\t\t\t\t\t\t\t\t||        3.Exit                ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\t\t||\n");
	printf("\t\t\t\t\t\t\t\t||          <<Choice>>          ||\n");
	printf("\t\t\t\t\t\t\t\t||         ============         ||\n");
	printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||       < Enter ItemCode >     ||\n");
		printf("\t\t\t\t\t\t\t\t||         < to search >        ||\n");
		printf("\t\t\t\t\t\t\t\t||         =============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%s", code);

		int found = -1;
		int i = 0;


		for (i = 0; i < item_number; i++) {
			if (strcmp(item[i].code, code) == 0) {
				printf("\t\t\t\t\t\t||=============================================================||\n");
				printf("\t\t\t\t\t\t|| Item found:                                                 ||\n");
				printf("\t\t\t\t\t\t||=============================================================||\n");
				printf("\t\t\t\t\t\t|| Item code   description   quantity    price    minimumlevel ||\n");
				printf("\t\t\t\t\t\t|| =========   ===========   ========   =======   ============ ||\n");
				printf("\t\t\t\t\t\t|| %-8s ||%-12s ||%-8d ||%-7.2f ||%-12d ||\n", item[i].code, item[i].description, item[i].quantity, item[i].price, item[i].minimumlevel);
				printf("\t\t\t\t\t\t||-------------------------------------------------------------||\n");
				printf("\t\t\t\t\t\t||=============================================================||\n");
				found = i;

			}
		}
		if (found == -1) {
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||     unfounded item = %s\t||\n", code);
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
		break;
	case 2:
		printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		printf("\t\t\t\t\t\t\t\t||     < Enter Description >    ||\n");
		printf("\t\t\t\t\t\t\t\t||         < to search >        ||\n");
		printf("\t\t\t\t\t\t\t\t||         =============        ||\n");
		printf("\t\t\t\t\t\t\t\t||\t\t\b\b\b\b\b>");
		scanf("%s", description);




		for (i = 0; i < item_number; i++) {
			if (strcmp(item[i].description, description) == 0) {
				printf("\t\t\t\t\t\t||=============================================================||\n");
				printf("\t\t\t\t\t\t|| Item found:                                                 ||\n");
				printf("\t\t\t\t\t\t||=============================================================||\n");
				printf("\t\t\t\t\t\t|| Item code   description   quantity    price    minimumlevel ||\n");
				printf("\t\t\t\t\t\t|| =========   ===========   ========   =======   ============ ||\n");
				printf("\t\t\t\t\t\t|| %-8s ||%-12s ||%-8d ||%-7.2f ||%-12d ||\n", item[i].code, item[i].description, item[i].quantity, item[i].price, item[i].minimumlevel);
				printf("\t\t\t\t\t\t||-------------------------------------------------------------||\n");
				printf("\t\t\t\t\t\t||=============================================================||\n");
				found = i;
				break;
			}
		}
		if (found == -1) {
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t||     unfounded = %s\t||\n", description);
			printf("\t\t\t\t\t\t\t\t||        ==============        ||\n");
			printf("\t\t\t\t\t\t\t\t/\\/\\/\\/\\/\\/\\/\\/\\/\\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
		}
		break;
	case 3:
		return;
		break;
	}



}

void report(struct stock item[], int item_number) {

	printf("\t\t\t\t\t\t||============================================================||\n");
	printf("\t\t\t\t\t\t|| %-10s | %-20s | %-20s   ||\n", "Item", "Out Stock", "In Stock");
	printf("\t\t\t\t\t\t||============================================================||\n");

	for (int i = 0; i < item_number; i++) {
		printf("\t\t\t\t\t\t|| %-10s | %-20d | %-20d   ||\n", item[i].code, item[i].outstock, item[i].restock);
	}
	printf("\t\t\t\t\t\t||============================================================||\n");

}

//-----------------------------------------------------------------End Of Stock Information Module-----------------------------------------------------------------------

