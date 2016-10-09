#define PRIME 211
#define SUBPROC_NUM 100
#define EOS '\0'

typedef struct idnode{          /*��ϣ��Ľڵ�*/
    char name[64];
    int type;   /*���ͣ���int��int*��*/
    int offset;
    int *arrayex;               //��չ����ָ��
    struct idnode *next_hash;       /*ָ����һ�ڵ��ָ��*/
}Identifier;

typedef struct{                 /*�ӹ�����Ŀ*/
    char name[64];
    struct symtable* s;
}Subproc;

typedef struct symtable{                //���ű�
    struct symtable* before;
    int width;
    Identifier *SymbolTable[PRIME];    //��ϣ����ű���
    Subproc *SubprocArray[SUBPROC_NUM];
    int subprocptr;
}symtbl;

int hashpjw(char *s)
{
    char *p;
    unsigned h = 0,g;
    for(p = s;*p!=EOS;p=p+1)
    {
        h = (h<<4) + (*p);
        if((g = (h & 0xF0000000)))
        {
            h = h^(g>>24);
            h = h^g;
        }
    }
    return h % PRIME;
}

symtbl *mktable(symtbl *bt)
{
    int i;
    symtbl* st = (symtbl*)malloc(sizeof(symtbl));
    st->before = bt;
    st->subprocptr = 0;
    for(i = 0;i < PRIME;i++)
    {
        st->SymbolTable[i] = NULL;
    }
    for(i=0;i<SUBPROC_NUM;i++)
    {
        st->SubprocArray[i] = NULL;
    }
    return st;
}

void addwidth(symtbl *st,int offset)
{
    st->width = offset;
}

int enter(symtbl *st,char *name,int type,int offset,pintqueue piq)
{
    int index = hashpjw(name);
    int queuenum;
    int j;
    int val;        //�������ֵ
    int sum;
    Identifier *entry = (Identifier*)malloc(sizeof(Identifier));
    Identifier *p,*pb;

    strcpy(entry->name,name);
    entry->type = type;
    entry->offset = offset;
    if(entry->type == 0||entry->type == 1)
    {
        entry->arrayex = NULL;
    }
    else        //entry->type == 3/4
    {
        //PrintIntQueue(piq);
        if(piq->rear >= piq->front)
        {
            queuenum = piq->rear - piq->front;
        }
        else
        {
            queuenum = QUESIZE + (piq->rear - piq->front);  //������Ԫ�ظ���
        }
        entry->arrayex = (int*)malloc(sizeof(int)*(queuenum+2));
        *(entry->arrayex+1) = queuenum/2;   //��¼ά��=������Ԫ�ظ���/2
        j = 2;
        sum =  0;
        while(IntDequeue(piq,&val) != 0)        //�Ӳ���
        {
            *(entry->arrayex+j) = val;
            IntDequeue(piq,&val);               //�϶��ɹ�����
            *(entry->arrayex+(j+1)) = val - *(entry->arrayex+j) + 1;
            sum = sum * (*(entry->arrayex+(j+1))) + (*(entry->arrayex+j));
            j += 2;
        }
        *(entry->arrayex) = entry->offset - sum * (entry->type-1) * 4;      //cֵ=base-sum*w
    }

    p = st->SymbolTable[index];

    if(p == NULL||strcmp(p->name,name)>0)
    {
        entry->next_hash = p;
        st->SymbolTable[index] = entry;
        return 0;
    }

    while(p != NULL)
    {
        if(strcmp(p->name,name) < 0)
        {
            pb = p;
            p = p->next_hash;
        }
        else
        {
            break;
        }
    }

    if(p == NULL)
    {
        entry->next_hash = NULL;
        pb->next_hash = entry;
        return 0;
    }
    else if(strcmp(p->name,name)>0)
    {
        entry->next_hash = p;
        pb->next_hash = entry;
        return 0;
    }
    else
    {
        /*������������*/
        /*return p->firline;*/
        return 1;
    }
}

void enterproc(symtbl *st,char *name,symtbl *t)     //��st������ӳ�����Ŀ
{
    Subproc* sproc = (Subproc*)malloc(sizeof(Subproc));
    strcpy(sproc->name,name);
    sproc->s = t;
    st->SubprocArray[st->subprocptr] = sproc;
    st->subprocptr++;
}

Identifier* lookup(char *name,symtbl* nowsym)       /*����name�ڵ��ڷ��ű��е�ָ�룬�粻���ڷ���null*/
{
    symtbl* beforesym = nowsym;
    int ret = hashpjw(name);
    Identifier *nextid;

    while(beforesym !=  NULL)
    {
        nextid = beforesym->SymbolTable[ret];
        while(nextid != NULL)
        {
            if(strcmp(nextid->name,name) == 0)
            {
                return nextid;
            }
            nextid = nextid->next_hash;
        }
        beforesym = beforesym->before;
    }
    return NULL;

}

