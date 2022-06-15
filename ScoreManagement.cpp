#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Student {
	char first_name[10];
	char last_name[10];
	char id[13];
	int year;
	int otherinID;
	int score;
	int GPA;  //0->A+  1->A  2->B+  3->B  4->C+  5->C  6->D  7>F
	int rank;	
	int isremake;
};

struct Student students[100];
int student_num;
int numin2019,numin2020,numin2021;

void init();
int show_main_menu();
void Add(char *name, char *id, int score);
int Delete(char *id);
int Search(char *id);

void Sort_by_id();
void Sort_by_score();
void Max();
void Min();
void Ave();
void prime();
void coprime();
char *encrypt(int key);
char *decrypt(int key, char *str);
void output_sit();

int GetGPA(int score);
void getRank(int score);
void reRank();
void reIDrank();
int turnToInt(char *chars);
void show_stu_detail(int point);
int isprime(int num);
int isconprime(int num1,int num2);


void add_one();
void add_more();
void search_one();
void delete_one();

int turnToInt(char *chars)
{
	int res=0;
	for(int i=0;i<strlen(chars);i++)
	{
		res+=chars[i]-'0';
		res*=10;
	}
	return res/10;
}

int isprime(int Num)
{
	if(Num <= 1){
		return 0;
	}
	if(Num == 2){
		return 1;
	}
	for(int i=2;i <=sqrt(Num);i++){
		if(Num%i==0) return 0;
	}
	return 1;
}

int isconprime(int num1,int num2)
{
	int temp;
	while(num1%num2!=0)
	{
		temp=num1%num2;
		num1=num2;
		num2=temp;
	}
	
	if(temp==1) return 1;
	else return 0;
}

int GetGPA(int score)
{
	if(score>=93){
		return 0;
	} 
	if(score>=85&&score<=92){
		return 1;
	} 
	if(score>=80&&score<=84){
		return 2;
	} 
	if(score>=75&&score<=79){
		return 3;
	} 
	if(score>=70&&score<=74){
		return 4;
	} 
	if(score>=65&&score<=69){
		return 5;
	} 
	if(score>=60&&score<=64){
		return 6;
	} 
	if(score<60){
		return 7;
	}
}

void getrank(int score)
{
	int rank=1;
	for(int i=0;i<student_num;i++)
	{
		if(score>students[i].score)
		{
			students[i].rank++;
		}
		else if(score<students[i].score)
		{
			rank++;
		}
	}
	students[student_num].rank=rank;
}

void reIDrank()  //以ID号进行排序
{
	struct Student temp;
	for(int i=0;i<student_num;i++)  //先将不同年份的学生分开
	{
		for(int j=0;j<student_num-i-1;j++)
		{
			if(students[j].year>students[j+1].year)
			{
				temp=students[j];
				students[j]=students[j+1];
				students[j+1]=temp;
			}
		}
	}
	
	for(int i=0;i<numin2019;i++)
	{
		for(int j=0;j<numin2019-i-1;j++)
		{
			if(students[j].otherinID>students[j+1].otherinID)
			{
				temp=students[j];
				students[j]=students[j+1];
				students[j+1]=temp;
			}
		}
	}
	
	for(int i=0;i<numin2020;i++)
	{
		for(int j=i;j<numin2020-i-1;j++)
		{
			if(students[numin2019+j].otherinID>students[numin2019+j+1].otherinID)
			{
				temp=students[numin2019+j];
				students[numin2019+j]=students[numin2019+j+1];
				students[numin2019+j+1]=temp;
			}
		}
	}
	
	for(int i=0;i<numin2021;i++)
	{
		for(int j=i;j<numin2021-i-1;j++)
		{
			if(students[numin2019+numin2020+j].otherinID>students[numin2019+numin2020+j+1].otherinID)
			{
				temp=students[numin2019+numin2020+j];
				students[numin2019+numin2020+j]=students[numin2019+numin2020+j+1];
				students[numin2019+numin2020+j+1]=temp;
			}
		}
	}
}

void reRank()
{
	struct Student temp;
	for(int i=0;i<student_num;i++)
	{
		for(int j=0;j<student_num-i-1;j++)
		{
			if(students[j].rank>students[j+1].rank)
			{
				temp=students[j];
				students[j]=students[j+1];
				students[j+1]=temp;
			}
		}
	}
}

void Add(char *name, char *id, int score)
{
	char first_name[10], last_name[10];
	char year[5],otherinID[9];
	int GPA=GetGPA(score);
	sscanf(name,"%s %s",first_name,last_name);
	sscanf(id,"%4s %s",year,otherinID);
	
	int intyear, intotherinID;
	intyear=turnToInt(year);
	intotherinID=turnToInt(otherinID);
	
	strcpy(students[student_num].first_name, first_name);
	strcpy(students[student_num].last_name, last_name);
	strcpy(students[student_num].id,id);
	students[student_num].year=intyear;
	students[student_num].otherinID=intotherinID;
	students[student_num].score=score;
	students[student_num].GPA=GPA;
	
	getrank(score);
	
	if(strcmp(year,"2019")==0){
		numin2019++;
		students[student_num].isremake=1;
	}
	else if(strcmp(year,"2020")==0){
		numin2020++;
		students[student_num].isremake=1;
	}
	else if(strcmp(year,"2021")==0){
		numin2021++;
		students[student_num].isremake=0;
	}
	
	student_num++;
}

int Search(char *id)
{
	for(int i=0;i<student_num;i++)
	{
		if(strcmp(students[i].id,id)==0) return i;
	}
	return -1;
}

int Delete(char *id)
{
	int point=Search(id);
	if(point==-1) return 0;
	else
	{
		int del_stu_rank=students[point].rank;
		int del_stu_year=students[point].year;
		for(int i=point;i<student_num-1;i++)
		{
			students[i]=students[i+1]; //线性表删除元素
		}
		student_num--;
		for(int i=0;i<student_num;i++)
		{
			if(students[i].rank>del_stu_rank) students[i].rank--;
		}
		if(del_stu_year==2019) numin2019--;
		else if(del_stu_year==2020) numin2020--;
		else if(del_stu_year==2021) numin2021--;
	}
	return 1;
}

void show_stu_detail(int point)  //debug
{
	char name[13];
	strcpy(name,students[point].first_name);
	strcat(name,students[point].last_name);
	printf("%16s   ",name);
	printf("%12s    ",students[point].id);
	printf("%2d   ",students[point].score);
	
	switch (students[point].GPA) {
	case 0:
		printf(" A+   ");
		break;
	case 1:
		printf("  A   ");
		break;
	case 2:
		printf(" B+   ");
		break;
	case 3:
		printf("  B   ");
		break;
	case 4:
		printf(" C+   ");
		break;
	case 5:
		printf("  C   ");
		break;
	case 6:
		printf("  D   ");
		break;
	case 7:
		printf("  F   ");
		break;
	}
	
	printf("   %3d     ",students[point].rank);
	if(students[point].isremake)
	{
		printf("remake");
	}
}

void show_all_stu() //debug
{
	printf("        name             id     score    GPA     rank   isremake\n");
	printf("================================================================\n");
	for(int i=0;i<student_num;i++)
	{
		show_stu_detail(i);
		printf("\n");
	}
}

void add_one()
{
	char input_name[20];
	char input_id[20];
	char year[5];
	int input_score;
	printf("Please input the name:");
	gets(input_name);
	while(1)
	{
		printf("Please input the id:");
		gets(input_id);
		sscanf(input_id,"%4s",year);
		if(strcmp(year,"2019")==0&&strlen(input_id)==12) break;
		if(strcmp(year,"2020")==0&&strlen(input_id)==12) break;
		if(strcmp(year,"2021")==0&&strlen(input_id)==12) break;
		printf("id is ERROR!\n");
	}
	sscanf(input_id,"%4s",year);
	
	printf("Please input the score:");
	scanf("%d",&input_score);
	getchar();
	
	Add(input_name,input_id,input_score);
}

void add_more()
{
	char input_name[20];
	char input_id[20];
	char year[5];                                                                                                                                    //id:3053 
	int input_score;
	char iscontinue;
	
	while(1)
	{
		printf("Please input the name of student%d:",student_num+1);
		gets(input_name);
		
		while(1)
		{
			printf("Please input the id of student%d:",student_num+1);
			gets(input_id);
			sscanf(input_id,"%4s",year);
			if(strcmp(year,"2019")==0&&strlen(input_id)==12) break;
			if(strcmp(year,"2020")==0&&strlen(input_id)==12) break;
			if(strcmp(year,"2021")==0&&strlen(input_id)==12) break;
			printf("id is ERROR!\n");
		}
		
		printf("Please input the score of student%d:",student_num+1);
		scanf("%d",&input_score);
		getchar();
		
		Add(input_name,input_id,input_score);
		
		printf("upload successfully! do you want to exit uploading?(Y/others)");
		scanf("%c",&iscontinue);
		getchar();
		if(iscontinue=='Y') {break;}
	}
}

void delete_one()
{
	char id[13];
	char year[5];
	while(1)
	{
		printf("Please input the id:");
		gets(id);
		sscanf(id,"%4s",year);
		if(strcmp(year,"2019")==0&&strlen(id)==12) break;
		if(strcmp(year,"2020")==0&&strlen(id)==12) break;
		if(strcmp(year,"2021")==0&&strlen(id)==12) break;
		printf("id is ERROR!\n");
	}
	if(Delete(id)){
		printf("Deleted!\n\n");
	}
	else printf("Can`t find this student!\n\n");
	system("pause");
}

void search_one()
{
	char id[13];
	char year[5];
	while(1)
	{
		printf("Please input the id:");
		gets(id);
		sscanf(id,"%4s",year);
		if(strcmp(year,"2019")==0&&strlen(id)==12) break;
		if(strcmp(year,"2020")==0&&strlen(id)==12) break;
		if(strcmp(year,"2021")==0&&strlen(id)==12) break;
		printf("id is ERROR!\n");
	}
	int point = Search(id);
	if(point==-1) printf("Can`t find this student!\n\n");
	else{
		printf("        name             id     score    GPA     rank   isremake\n");
		printf("================================================================\n");
		show_stu_detail(point);
		printf("\n\n");
	}
	system("pause");
}

void Sort_by_id()
{
	reIDrank();
	show_all_stu();
	system("pause");
}

void Sort_by_score()
{
	reRank();
	show_all_stu();
	system("pause");
}

void Max()
{
	reRank();
	printf("        name             id     score    GPA     rank   isremake\n");
	printf("================================================================\n");
	show_stu_detail(0);
	system("pause");
}

void Min()
{
	reRank();
	printf("        name             id     score    GPA     rank   isremake\n");
	printf("================================================================\n");
	show_stu_detail(student_num-1);
	system("pause");
}

void Ave()
{
	double sum=0;
	for(int i=0;i<student_num;i++)
	{
		sum+=students[i].score;
	}
	printf("The Average is %f\n\n",sum/student_num);
	system("pause");
}

void prime()
{
	char id[13];
	char year[5];
	while(1)
	{
		printf("Please input the id:");
		gets(id);
		sscanf(id,"%4s",year);
		if(strcmp(year,"2019")==0&&strlen(id)==12) break;
		if(strcmp(year,"2020")==0&&strlen(id)==12) break;
		if(strcmp(year,"2021")==0&&strlen(id)==12) break;
		printf("id is ERROR!\n");
	}
	int point=Search(id);
	if(point==-1)
	{
		printf("Can`t find this student!\n\n");
	}
	else
	{
		if(isprime(students[point].score)==1) printf("The score is a prime number.\n\n");
		else printf("The score is NOT a prime number.\n\n");
	}
	system("pause");
}
	
void coprime()
{
	char id1[20],id2[20];
	char year1[5],year2[5];
	int point1,point2;
	while(1)
	{
		printf("Please input the id1:");
		gets(id1);
		sscanf(id1,"%4s",year1);
		if(strcmp(year1,"2019")==0&&strlen(id1)==12) break;
		if(strcmp(year1,"2020")==0&&strlen(id1)==12) break;
		if(strcmp(year1,"2021")==0&&strlen(id1)==12) break;
		printf("id1 is ERROR!\n");
	}
	while(1)
	{
		printf("Please input the id1:");
		gets(id2);
		sscanf(id2,"%4s",year2);
		if(strcmp(year2,"2019")==0&&strlen(id2)==12) break;
		if(strcmp(year2,"2020")==0&&strlen(id2)==12) break;
		if(strcmp(year2,"2021")==0&&strlen(id2)==12) break;
		printf("id2 is ERROR!\n");
	}
	point1=Search(id1);
	point2=Search(id2);
	if(point1==-1||point2==-1) printf("Can`t find the Student!\n\n");
	else{
		int score1=students[point1].score;
		int score2=students[point1].score;
		int isconprimeres=isconprime(score1,score2);
		if(isconprimeres==1) printf("The scores is conprime.\n\n");
		else printf("The scores is NOT conprime.\n\n");
	}
	system("pause");
}

void output_sit()
{
	int sit[8]={0};
	for(int i=0;i<student_num;i++)
	{
		sit[students[i].GPA]++;
	}
	printf("A+:%d\n",sit[0]);
	printf("A:%d\n",sit[1]);
	printf("B+:%d\n",sit[2]);
	printf("B:%d\n",sit[3]);
	printf("C+:%d\n",sit[4]);
	printf("C:%d\n",sit[5]);
	printf("D:%d\n",sit[6]);
	printf("F:%d\n",sit[7]);
	system("pause");
}


char *encrypt(int key)
{
	reIDrank();
	char charnum[4];
	char charnums[301];
	for(int i=0;i<student_num;i++)
	{
		sprintf(charnum,"%d",students[i].score);
		strcat(charnums,charnum);
	}
	
	for(int i=0;i<strlen(charnums);i++)
	{
		charnums[i]+=key%10;
		if(charnums[i]>'9') charnums[i]-=10;
	}
	
	char *charnumsadd = charnums;
	printf("Result:");
	puts(charnums);
	system("pause");
	return charnumsadd;
}

int show_main_menu()
{
	int choose;
	
	system("cls");
	printf("What do you what to do next? You can enter a number to tell me.\n");
	printf("1 add\n");
	printf("2 adds\n");
	printf("3 delete\n");
	printf("4 search\n");
	printf("5 sort by id\n");
	printf("6 sort by score\n");
	printf("7 best score\n");
	printf("8 worst score\n");
	printf("9 average score\n");
	printf("10 prime judge\n");
	printf("11 coprime judge\n");
	printf("12 show GPA detail\n");
	printf("13 encrypt\n");
	printf("0 Exit\n");
	printf("Input a number here:");
	scanf("%d",&choose);
	getchar();
	if(!(choose>=0&&choose<=13))
	{
		printf("Error input!Press any key to input again");
		system("pause");
		return show_main_menu();
	}
	return choose;
}

void init() 
{
	student_num=0;
	numin2019=0,numin2020=0,numin2021=0;
	printf("Hello, pls input a series of student information!\n");
	add_more();
	printf("Okey! data upload finished.\n");
}

int main()
{
	init();
	while(1)
	{
		switch(show_main_menu()) 
		{
		case 0:
			printf("BYEBYE!\n");
			system("pause");
			return 0;
		case 1:
			add_one();
			break;
		case 2:
			add_more();
			break;
		case 3:
			delete_one();
			break;
		case 4:
			search_one();
			break;
		case 5:
			Sort_by_id();
			break;
		case 6:
			Sort_by_score();
			break;
		case 7:
			Max();
			break;
		case 8:
			Min();
			break;
		case 9:
			Ave();
			break;
		case 10:
			prime();
			break;
		case 11:
			coprime();
			break;
		case 12:
			output_sit();
			break;
		case 13:
			int key;
			printf("Please input the key:");
			scanf("%d",&key);
			getchar();
			encrypt(key);
			break;
		}
	
	}
	return 0;

}

