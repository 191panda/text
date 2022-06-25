#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <windows.h>//Sleep

#define MAX 100
#define NAME 20
#define NUB 13
#define PHONE 13
#define SEX 10
#define IP 20
#define AGE 10

void caidan();
void addren(int* conut);
void seeren(int* conut);
void deleteren(int* conut);
void findren(int* conut);
void modifyren(int* conut);
void sortren(int* conut);
void TongJi(int* conut);//统计文件人数
void find_nub(int* conut);
void find_name(int* conut);
int cpy_str(const void* e1, const void* e2);


struct s
{
	char nub[NUB];//学号
	char name[NAME];//名字
	char sex[SEX];//性别
	char age[AGE];//年龄
	char phone[PHONE];//电话
	char ip[IP];//地址


}ren[MAX];


enum
{
	EXIT,
	ADD,
	SHOW,
	DEL,
	FIND,
	MODIFY,
	SORT
};

int main()
{   
	
	int conut = 0;//统计人的人数
	int  input = 0;//请选择功能

	do
	{   
		caidan();//菜单
		printf("\n 请选择(0-6):\n");
		printf("请选择功能:");
		scanf("%d", &input);

		switch (input)
		{
		case ADD://增加
			addren(&conut);
			break;
		case SHOW://查看
			seeren(&conut);
			break;
		case DEL:
			deleteren(&conut);
			break;
		case FIND:
			findren(&conut);
			break;
		case MODIFY:
			modifyren(&conut);
			break;
		case SORT:
			sortren(&conut);
			break;
		case EXIT:
			printf("退出\n");
			break;
		default:
			printf("输入错误\n");
			break;
		}

	} while (input);

	return 0;
}

#include"TongXunLu.h"



void caidan()
{
	printf("\n***************************************************************\n");
	printf("               0-------------------------------退出 \n");
	printf("               1-------------------------------添加联系人\n");
	printf("               2-------------------------------查看通讯录中联系人\n");
	printf("               3-------------------------------删除指定的人\n");
	printf("               4-------------------------------查找指定的人\n");
	printf("               5-------------------------------修改指定人的信息  \n");
	printf("               6-------------------------------通讯录排序\n");
	printf("\n================================================================\n");
}


void TongJi(int* conut)
{
	*conut = 0;
	struct s temp = { 0 };
	FILE* pfread = fopen("通讯录.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	while (fread(&temp, sizeof(struct s), 1, pfread))
	{
		(*conut)++;
	}
	//关闭文件
	fclose(pfread);
	pfread = NULL;

}

//添加联系人到文件
void addren(int* conut)
{
	TongJi(conut);
	if (*conut == MAX)
	{
		printf("通讯录已满");

	}
	else
	{
		printf("输入学号：");
		scanf("%s", ren[*conut].nub);
		printf("输入姓名：");
		scanf("%s", (ren[*conut].name));
		printf("输入性别：");
		scanf("%s", (ren[*conut].sex));
		printf("输入年龄：");
		scanf("%s", (ren[*conut].age));
		printf("输入联系方式：");
		scanf("%s", ren[*conut].phone);
		printf("输入家庭地址：");
		scanf("%s", ren[*conut].ip);


		(*conut)++;
		//写入文件
		FILE* pfwrite = fopen("通讯录.txt", "wb");
		if (pfwrite == NULL)
		{
			printf("%s", strerror(errno));
		}
		//写入
		else
		{
			for (int i = 0; i < *conut; i++)
			{
				fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
			}
			fclose(pfwrite); pfwrite = NULL;
			printf("\n添加成功\n");


		}

	}


}


//显示联系人
void seeren(int* conut)
{
	printf("\n--------------------------------------------------------------------------\n");
	printf("学号\t\t姓名\t性别\t年龄\t电话\t\t家庭地址\n");
	FILE* pfshow = fopen("通讯录.txt", "rb");
	if (pfshow == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	else
	{
		TongJi(conut);
		for (int i = 0; i < *conut; i++)
			fread(&ren[i], sizeof(struct s), 1, pfshow);

		for (int i = 0; i < *conut; i++)
		{
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
		}
		fclose(pfshow);
		pfshow = NULL;
		printf("读取完成\n");
	}
}


//采用学号删除
void deleteren(int* conut)
{
	printf("输入你要删除人的学号：");
	char nubarr[NUB] = { 0 };
	int i = 0, j = 0;
	scanf("%s", nubarr);
	TongJi(conut);

	if (*conut == 0)
	{
		printf("通讯录为空！\n");
	}
	else
	{
		for (i = 0; i < *conut; i++)
		{
			if (0 == strcmp(nubarr, ren[i].nub))
			{
				for (j = i; j < *conut; j++)
				{
					ren[j] = ren[j + 1];

				}
			}
			if (j == *conut)
			{
				printf("删除成功\n");
				(*conut)--;
			}
			else if (i == *conut - 1)
				printf("找不到！");

		}

		//打开文件
		FILE* pfwrite = fopen("通讯录.txt", "wb");
		if (pfwrite == NULL)
		{
			printf("%s", strerror(errno));
			return;
		}

		for (i = 0; i < *conut; i++)
		{
			fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
		}

		fclose(pfwrite);
		pfwrite = NULL;
	}

}

//查找
void findren(int* conut)
{
	int b = 0;
	do
	{

		printf("\n***********************MENU********************\n");
		printf("    1---------------用学号查找.\n");
		printf("    2---------------用姓名查找.\n");
		printf("    0---------------安全退出.\n");
		printf("\n***********************************************\n");
		printf("\n 请选择(0-2):\n");
		scanf("%d", &b);
		switch (b)
		{
		case 1:find_nub(conut); break;
		case 2:find_name(conut); break;
		case 0:printf("退出！"); break;
		default:
			printf("输入错误！");
			break;
		}


	} while (b);

}

//用学号查找 
void find_nub(int* conut)
{
	printf("请输入学号：");
	char temp[20] = { 0 };
	scanf("%s", temp);
	printf("正在查找~\n");
	Sleep(2000);

	//打开文件
	FILE* pfread = fopen("通讯录.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	TongJi(conut);
	int i = 0;
	for (i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
		if (strcmp(ren[i].nub, temp) == 0)
		{
			printf("查找成功\n您要找到人的信息：\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("学号\t\t姓名\t性别\t年龄\t电话\t\t家庭地址\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
			break;

		}
	}
	if (i == *conut)
	{
		printf("查找失败\n你所查找的人不在通讯录！\n");
	}
	//关闭文件
	fclose(pfread);
	pfread = NULL;
}


void find_name(int* conut)
{

	printf("请输入名字：");
	char temp[20] = { 0 };
	scanf("%s", temp);
	printf("正在查找~\n");
	Sleep(2000);
	//打开文件
	FILE* pfread = fopen("通讯录.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	TongJi(conut);
	int i = 0;
	for (i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
		if (strcmp(ren[i].name, temp) == 0)
		{
			printf("查找成功\n您要找到人的信息：\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("学号\t\t姓名\t性别\t年龄\t电话\t\t家庭地址\n");
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
			printf("\n--------------------------------------------------------------------------\n");
			break;

		}
	}
	if (i == *conut)
	{
		printf("查找失败\n你所查找的人不在通讯录！\n");
	}
	//关闭文件
	fclose(pfread);
	pfread = NULL;
}

//按学号排序
void sortren(int* conut)
{
	TongJi(conut);
	FILE* pfread = fopen("通讯录.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	for (int i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
	}

	fclose(pfread);
	pfread = NULL;

	//排序
	qsort(ren, *conut, sizeof(struct s), cpy_str);


	FILE* pfwrite = fopen("通讯录.txt", "wb");
	if (pfwrite == NULL)
	{
		printf("sortren_pfread:%s", strerror(errno));
		return;
	}

	for (int i = 0; i < *conut; i++)
	{
		fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
	}

	fclose(pfwrite);
	pfwrite = NULL;

	printf("排序成功\n");

}

int cpy_str(const void* e1, const void* e2)
{
	return  strcmp((*(struct s*)e1).nub, (*(struct s*)e2).nub);

}

//修改信息

void modifyren(int* conut)
{
	printf("输入修改人的学号：");
	char temp[20] = { 0 };
	scanf("%s", temp);

	FILE* pfread = fopen("通讯录.txt", "rb");
	if (pfread == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}
	TongJi(conut);
	int i = 0;
	for (i = 0; i < *conut; i++)
	{
		fread(&ren[i], sizeof(struct s), 1, pfread);
		if (strcmp(ren[i].nub, temp) == 0)
		{
			printf("查找成功\n您要找到人的信息：\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("学号\t\t姓名\t性别\t年龄\t电话\t\t家庭地址\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("%-16s%-8s%-8s%-8s%-16s%-16s\n", ren[i].nub, ren[i].name, ren[i].sex, ren[i].age, ren[i].phone, ren[i].ip);
			printf("=============================开始修改=======================================\n");
			printf("输入学号：");
			scanf("%s", ren[i].nub);
			printf("输入姓名：");
			scanf("%s", (ren[i].name));
			printf("输入性别：");
			scanf("%s", (ren[i].sex));
			printf("输入年龄：");
			scanf("%s", (ren[i].age));
			printf("输入联系方式：");
			scanf("%s", ren[i].phone);
			printf("输入家庭地址：");
			scanf("%s", ren[i].ip);
			printf("修改成功\n");
			break;

		}
	}
	if (i == *conut)
	{
		printf("查找失败\n你所查找的人不在通讯录！\n");
	}
	//关闭文件
	fclose(pfread);
	pfread = NULL;


	FILE* pfwrite = fopen("通讯录.txt", "wb");
	if (pfwrite == NULL)
	{
		printf("%s", strerror(errno));
		return;
	}

	for (int i = 0; i < *conut; i++)
	{
		fwrite(&ren[i], sizeof(struct s), 1, pfwrite);
	}
	fclose(pfwrite);
	pfwrite = NULL;
}