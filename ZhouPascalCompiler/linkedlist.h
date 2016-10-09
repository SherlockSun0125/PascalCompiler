typedef struct intnode{
    int label;
    struct intnode *next;
}LabelNode;

LabelNode* makelist(int para)
{
    LabelNode* head = (LabelNode*)malloc(sizeof(LabelNode));
    head->next = NULL;
    head->label = para;
    return head;
}

void mergelist(LabelNode* list1,LabelNode* list2)     //list1/2����Ϊ��,list2����list1��ȥ
{
    LabelNode* nextnode = list1;
    if(nextnode == NULL)
    {
        return ;
    }
    while(nextnode->next != NULL)
    {
        nextnode = nextnode->next;
    }
    (*nextnode).next = list2;
}

void clear_label_list(LabelNode* lalist)
{
    LabelNode* t;
    if(lalist == NULL)
    {
        return ;
    }
    while(lalist->next != NULL)
    {
        t = lalist->next;//������һ����ָ��
        free(lalist);
        lalist = t;      //��ͷ����
    }
    free(lalist);
    lalist = NULL;
}

/* ��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
void initList(Identifier **pNode)
{
    *pNode = NULL;
}

/*������ı�ͷ����һ��Ԫ�� */
Identifier * insertHeadList(Identifier **pNode,int *tempcount)
{
    Identifier *pInsert;
    pInsert = (Identifier *)malloc(sizeof(Identifier));
    memset(pInsert,0,sizeof(Identifier));

    pInsert->arrayex = NULL;
    pInsert->offset = -1;
    pInsert ->type = -1;
    pInsert ->type = -1;

    sprintf(pInsert->name,"t%d",*tempcount);
    (*tempcount)++;
    pInsert->next_hash = *pNode;

    *pNode = pInsert;
    return pInsert;
}

/*������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
void clearList(Identifier *pHead)
{
    Identifier *pNext;            //����һ����pHead���ڽڵ�

    if(pHead == NULL)
    {
        return;
    }
    while(pHead->next_hash != NULL)
    {
        pNext = pHead->next_hash;//������һ����ָ��
        free(pHead);
        pHead = pNext;      //��ͷ����
    }
    free(pHead);
    pHead = NULL;
    return ;
}
