#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 单向链表作为内存池，原理上不随时释放内存(free),链表记录每个被删除的内存块；存的链表够多了(MAX),就删除整个链表中的内存块
// 通讯录例子中，也是用一个单向链表；删除时，删除内容不进行free 操作，通讯录链表中删除内容，转移到内存池链表中，内存池满了再统一清理内存池内的所有链表内存空间占用
// 好处是避免频繁的内存申请和清理，造成连续的内存上千疮百孔(删除后空间)，适合大小的少，寻找可用内存空间时容易出现，内存总余量很多，但是没有合适，内存申请失败

#define MAX 1024    // 链表存储的最大(指针)数量MAX

struct Person
{
        char name[40];
        char phone[20];
        struct Person *next;
};

struct Person *pool = NULL; // 全局 结构体 指针
int count;

void getInput(struct Person *person);
void printPerson(struct Person *person);
void addPerson(struct Person **contacts);
void changePerson(struct Person *contacts);
void delPerson(struct Person **contacts);
struct Person *findPerson(struct Person *contacts);
void displayContacts(struct Person *contacts);
void releaseContacts(struct Person **contacts);
void releasePool(void);

void getInput(struct Person *person)
{
        printf("请输入姓名：");
        scanf("%s", person->name);
        printf("请输入电话：");
        scanf("%s", person->phone);
}

void addPerson(struct Person **contacts)
{
        struct Person *person; // 局部 结构体 指针
        struct Person *temp;

	// 如果内存池非空，则直接从里面获取空间
	if (pool != NULL)
	{
		person = pool;
		pool = pool->next;
		count--;
	}
	// 如果内存池为空，则调用malloc函数申请新的(动态)内存空间
	else
	{
		person = (struct Person *)malloc(sizeof(struct Person));
		if (person == NULL)
		{
			printf("内存分配失败！\n");
			exit(1);
		} 
	}

        getInput(person);

        // 将person用头插法添加到通讯录中
        if (*contacts != NULL)
        {
                temp = *contacts;
                *contacts = person;
                person->next = temp;
        }
        else
        {
                *contacts = person;
                person->next = NULL;
        }
}

void printPerson(struct Person *person)
{
        printf("联系人：%s\n", person->name);
        printf("电话：%s\n", person->phone);
}

struct Person *findPerson(struct Person *contacts)
{
        struct Person *current;
        char input[40];

        printf("请输入联系人：");
        scanf("%s", input);

        current = contacts;
        while (current != NULL && strcmp(current->name, input))
        {
                current = current->next;
        }

        return current;
}

void changePerson(struct Person *contacts)
{
        struct Person *person;

        person = findPerson(contacts);
        if (person == NULL)
        {
                printf("找不到该联系人！\n");
        }
        else
        {
                printf("请输入新的联系电话：");
                scanf("%s", person->phone);
        }
}

void delPerson(struct Person **contacts)
{
        struct Person *temp;
        struct Person *person; // 局部变量
        struct Person *current;
        struct Person *previous;

        // 先找到待删除的节点指针
        person = findPerson(*contacts);
        if (person == NULL)
        {
                printf("找不到该联系人！\n");
        }
        else
        {
                current = *contacts;
                previous = NULL;

                // current定位到待删除的节点
                while (current != NULL && current != person)
                {
                        previous = current;
                        current = current->next;
                }
                // 当前要删除的 person， 状态 current == person
                if (previous == NULL)
                {
                        // 待删除的节点是第一个节点
                        *contacts = current->next;
                }
                else
                {
                        // 待删除的节点不是第一个节点
                        previous->next = current->next;
                }

		// 判断内存池是不是有空位
		if (count < MAX)
		{
			if (pool != NULL)
			{
				temp = pool;
				pool = person;
				person->next = temp; // 头插法， 将pool[data:pointer->NULL] 作为当前 person 的指针尾部指向
			}
			else // person 当前为NULL
			{
				pool = person;  // 指针pool 被 结构体(链表)指针 person  赋值
				person->next = NULL; 
			}
			count++;
		}
		else   // 达到设置的最大数据量，free 整个链表
		{
                	free(person);
		}
        }
}

void displayContacts(struct Person *contacts)
{
        struct Person *current;

        current = contacts;
        while (current != NULL)
        {
                printPerson(current);
                current = current->next;
        }
}

void releaseContacts(struct Person **contacts)
{
        struct Person *temp;

        while (*contacts != NULL)
        {
                temp = *contacts;
                *contacts = (*contacts)->next;
                free(temp);
        }
}

void releasePool(void)
{
	struct Person *temp;

	while (pool != NULL)
	{
		temp = pool;
		pool = pool->next;
		free(temp);
	}
}

int main(void)
{
        int code;
        struct Person *contacts = NULL;
        struct Person *person;

        printf("| 欢迎使用通讯录管理程序 |\n");
        printf("|--- 1:插入新的联系人 ---|\n");
        printf("|--- 2:查找已有联系人 ---|\n");
        printf("|--- 3:更改已有联系人 ---|\n");
        printf("|--- 4:删除已有联系人 ---|\n");
        printf("|--- 5:显示当前通讯录 ---|\n");
        printf("|--- 6:退出通讯录程序 ---|\n");
        printf("|- Powered by FishC.com -|\n");

        while (1)
        {
                printf("\n请输入指令代码：");
                scanf("%d", &code);
                switch (code)
                {
                        case 1: addPerson(&contacts); break;

                        case 2: person = findPerson(contacts);
                                if (person == NULL)
                                {
                                        printf("找不到该联系人！\n");
                                }
                                else
                                {
                                        printPerson(person);
                                }
                                break;
                                
                        case 3: changePerson(contacts); break;

                        case 4: delPerson(&contacts); break;

                        case 5: displayContacts(contacts); break;

                        case 6: goto END;
                }
        }

END:
        releaseContacts(&contacts);
	releasePool();

        return 0;
}
