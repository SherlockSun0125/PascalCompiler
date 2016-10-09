#define QUESIZE 1000        //ѭ�����е����洢�ռ�

typedef struct queue
{
    char pBase[QUESIZE][64];             //�ַ�����
    int front;                          //ָ����е�һ��Ԫ�أ�����һ��
    int rear;                           //ָ��������һ��Ԫ�ص���һ��Ԫ�أ����һ��
}queue,*pqueue;

void MakeNULLQueue(pqueue Q)
{
    Q->front=0;                         //��ʼ������
    Q->rear=0;
}

int FullQueue(pqueue Q)
{
    if(Q->front==(Q->rear+1)%QUESIZE)    //�ж�ѭ�������Ƿ�������һ��Ԥ���ռ䲻��
        return 1;
    else
        return 0;
}

int EmptyQueue(pqueue Q)
{
    if(Q->front==Q->rear)    //�ж��Ƿ�Ϊ��
        return 1;
    else
        return 0;
}

int Enqueue(pqueue Q, char *val)
{
    if(FullQueue(Q))
        return 0;
    else
    {
        strcpy(Q->pBase[Q->rear],val);
        Q->rear=(Q->rear+1)%QUESIZE;
        return 1;
    }
}

int Dequeue(pqueue Q, char *val)
{
    if(EmptyQueue(Q))
    {
        return 0;
    }
    else
    {
        strcpy(val,Q->pBase[Q->front]);
        Q->front=(Q->front+1)%QUESIZE;
        return 1;
    }
}

typedef struct intqueue
{
    int pBase[QUESIZE];             //����
    int front;                          //ָ����е�һ��Ԫ�أ�����һ��
    int rear;                           //ָ��������һ��Ԫ�ص���һ��Ԫ�أ����һ��
}intqueue,*pintqueue;

void PrintIntQueue(pintqueue Q)
{
    int i;
    if(Q->front==Q->rear)
    {
        printf("empty queue!");
    }
    for(i=Q->front;i<Q->rear;i=(i+1)%QUESIZE)
    {
        printf("%d",Q->pBase[i]);
    }
}

void IntMakeNULLQueue(pintqueue Q)
{
    Q->front=0;                         //��ʼ������
    Q->rear=0;
}

int IntFullQueue(pintqueue Q)
{
    if(Q->front==(Q->rear+1)%QUESIZE)    //�ж�ѭ�������Ƿ�������һ��Ԥ���ռ䲻��
        return 1;
    else
        return 0;
}

int IntEmptyQueue(pintqueue Q)
{
    if(Q->front==Q->rear)    //�ж��Ƿ�Ϊ��
        return 1;
    else
        return 0;
}

int IntEnqueue(pintqueue Q, int val)
{
    if(IntFullQueue(Q))
        return 0;
    else
    {
        Q->pBase[Q->rear] = val;
        Q->rear=(Q->rear+1)%QUESIZE;
        return 1;
    }
}

int IntDequeue(pintqueue Q, int *val)
{
    if(IntEmptyQueue(Q))
    {
        return 0;
    }
    else
    {
        *val = Q->pBase[Q->front];
        Q->front=(Q->front+1)%QUESIZE;
        return 1;
    }
}

