//#include<stdio.h>
//#pragma warning(disable:4996)
//typedef struct {
//	int day;
//	int month;
//	int year;
//	int hour;
//	int minute;
//	int second;
//}Time;
//typedef struct {
//	char name[30];
//	char staffid[10];
//	char gender;
//	char contactno[30];
//	char position;
//	char password[10];
//}Staff;
//typedef struct {
//	char salesID[5];
//	char itemCode[10];
//	int quantityOrder;
//	double price;
//	char memberID[6];
//	char staffID[6];
//	Time timeAdd;
//
//}SalesInformation;
//struct stock
//{
//	char code[10];
//	char description[50];
//	double price, costprice;
//	int quantity, minimumlevel;
//	int reorder_qty;
//
//};
//typedef struct {
//	char id[10];
//	char name[50];
//	char gender;
//	char password[20];
//	int contact;
//	char ic[20];
//}member;
//int main() {
//	SalesInformation sales[20] = { {"R001","C063",2,70.00,"M0001","S0137",{18,4,2023,12,30,5}},{"R002","C051",5,50.00,"M0003","S0137",{18,4,2023,12,45,5}},{"R003","C042",3,108.00,"M0003","S0978",{19,4,2023,10,15,5}},{"R004","C032",1,40.00,"M0004","S0352",{20,4,2023,16,30,23}},{"R005","C94",3,30.00,"M0005","S0021",{4,2,2001,3,4,5}} ,{"R006","C48",10,15.00,"M0006","S0542",{14,12,2004,5,6,7}},{"R007","C018",2,40.00,"M0007","S0974",{4,2,2013,2,4,6}},{"R008","C067",4,32.00,"M0009","S0796",{4,2,2003,2,6,4}} ,{"R009","C095",2,200.00,"M0010","a123",{2,4,2010,4,2,6}}, {"R010","C059",4,80.00,"M0004","S0594",{7,7,2077,6,6,6}} };
//	member members[10] = { {"M0001","Chun Wai",'M',"123456",111111111,"11111111111"},{"M0002","Shi Min",'M',"321312",222222222,"22222222222"},{"M0003","Nai Yen",'F',"5555555",333333333,"333333333333"} ,{"M0004","Weiliang",'M',"444444",4444444,"444444444444"} ,{"M0005","hanjie",'M',"66666",6666666,"666666"} ,{"M0006","jiayew",'M',"777777",7777777,"777777777"},{"M0007","jiahui",'M',"88888",8888888,"88888888888"} ,{"M0008","KimWah",'M',"99999",999999,"9999999999"} ,{"M0009","ShiQi",'F',"898989",8989898,"8989898989"},{"M0010","Kaixaing",'M',"123456",123456,"1234567890"} };
//	struct stock item[10] = { {"C063","Coffee Beans",35,22,190,100,0},{"C051","Beef",10,7,254,100,0},{"C059","Baguette",20,10,232,100,0},{"C042","Arctic Char",36,18,129,100,0}, {"C095","Wine",200,120,100,50,0},{"C048","Spring Water",1.50,0.80,300,150,0},{"C094","Cookie Dough",10,6,50,70,0}, {"C032","Mon Cheese",40,25,150,100,0},{"C067","Regu Straw",8,5,120,100,0},{"C018","Dry Pasta",20,12,190,100,0}};
//	Staff staff[11] = { {"kaixiang","a123",'M',"176279060",'M',"a123"},{"Mill craft","S0137",'M',"176279060",'R',"oqs874"},{"Moss Shury","S0978",'M',"169751322",'R',"nqq338"},{"Caesar Wrefford","S0352",'F',"196677999",'P',"kat555"}, {"Malina Pitt","S0021",'F',"132463099",'F',"xax155"},{"Kelwin Macro","S0542",'F',"159765124",'P',"utj503"},{"Otho Tague","S0947",'M',"187992136",'R',"rxc632"},{"Stevena Cotman","S0796",'M',"173549524",'P',"rdc776"},{"Igor Bernade","S0138",'F',"100139053",'P',"kfd587"},{"Tana Kitchingham","S0911",'F',"116147198",'M',"jas390"},{"Vera Mitrikhin","S0594",'F',"111352021",'R',"uvb385"} };
//	
//	
//	FILE* sale;
//	sale = fopen("sales.bin", "wb");
//	FILE* items;
//	items = fopen("item.bin", "wb");
//	FILE* memberData;
//	memberData = fopen("member.txt", "w");
//	FILE* staffs;
//	staffs = fopen("staff.txt", "w");
//
//
//	
//	
//
//	fwrite(&item, sizeof(struct stock), 10, items);
//	fwrite(&sales, sizeof(SalesInformation), 10, sale);
//	for (int i = 0; i < 10; i++) {
//		fprintf(staffs, "%s|%s|%c|%s|%c|%s|\n", staff[i].name, staff[i].staffid, staff[i].gender, staff[i].contactno, staff[i].position, staff[i].password);
//	}
//	for (int i = 0; i < 10; i++) {
//		fprintf(memberData, "%s|%s|%c|%s|%d|%s|\n", members[i].id, members[i].name, members[i].gender, members[i].password, members[i].contact, members[i].ic);
//	}
//
//
//
//
//	fclose(sale);
//	fclose(items);
//	fclose(staffs);
//	fclose(memberData);
//
//	
//
//}
