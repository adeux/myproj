#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct LinearList
{
	int *list;
	int size;
	int MaxSize;
};

typedef struct LinearList LIST;

int InitList(LIST *L,int ms)
{
	if((L->list=(int*)malloc(sizeof(int)*ms))==NULL)
	{
		printf("内存申请错误!\n");
		exit(1);
	}
	L->size=0;
	L->MaxSize=ms;

	return 0;

}

int InsertList(LIST *L,int item,int rc)
{
	int i;
	if(L->size > L->MaxSize)
		return -1;
	if(rc<0)
		rc=0;
	if(rc > L->MaxSize-1)
		rc=L->size;
	for(i=L->size-1;i>=rc;i--)
	{
		L->list[i+1]=L->list[i];
	}
	L->list[rc]=item;
	return 0;
}


int OutputList(LIST *L)
{
	int i;
	for(i=0;i<L->size;i++)
	{
		printf("%d",L->list[i]);
		printf("\n");
	}
	return 0;
}

int FindList(LIST* L,int item)
{
	int i;
	for(i=0;i<L->size;i++)
	{
		if(L->list[i]==item)
		return i;
	}
	return -1;
}

int DeleteLisst1(LIST *L,int item)
{
	int i,n;
	for(i=0;i<L->size;i++)
	{
		if(L->list[i]==item)
		break;
	}
	if(i<L->size)
	{
		for(n=i;n<L->size-1;n++)
			L->list[n]=L->list[i+1];
		L->size--;
		return i;
	}
	return -1;

}
int main(int argc,char *argv[])
{
	LIST LL;
	int i,r;
	printf("list addr=%p\tsize=%d\tMaxSize=%d\n",LL.list,LL.size,LL.MaxSize);
	InitList(&LL,100);
	printf("list addr=%p\tsize=%d\tMaxSize=%d\n",LL.list,LL.size,LL.MaxSize);
	while(1)
	{
		printf("请输入元素值，输入零结束插入操作：\n");
		fflush(stdin);
		scanf("%d",&i);
		if(i==0)
			break;
		printf("输入插入位置：\n");
		scanf("%d",&r);
		InsertList(&LL,i,r);
		printf("线性表为：\n");
		OutputList(&LL);
	}
	return 0;
}