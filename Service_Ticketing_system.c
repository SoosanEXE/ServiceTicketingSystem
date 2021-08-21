#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define hrdware_pswd "hardware101"
#define sftware_pswd "software202"
#define admin_pswd "admin303"
//The above lines store the passwords for different login methods

struct queue_node// Struct for a queue node
{
    int sid, status;//status = 1 ->completed, status = 0 -> not completed
    char *cname, *problem;
    struct queue_node * next;
};
typedef struct queue_node * node;

struct queue_header// Struct to store the front and rear pointers of a queue
{
    node f, r;
};
typedef struct queue_header* queue;


int isempty(queue q)//checks if a queue is empty
{
    return (q->f == NULL && q->r == NULL);
}

queue hq, sq, sl;// Hardware and software queue headers and service log header

//functions
void create_queue()//creates the hardware, software and service log queue
{
    hq = (queue)malloc(sizeof(struct queue_header));
    sq = (queue)malloc(sizeof(struct queue_header));
    sl = (queue)malloc(sizeof(struct queue_header));

    if((hq != NULL && sq != NULL) && sl != NULL)
        hq->f= hq->r= sq->f= sq->r= sl->f= sl->r=NULL;
    else
        printf("Error: Memory is full\n");
}

void dispose_queue(queue q)
{
    if(!isempty(q))
    {
        node t;
        while(q->f != NULL)
        {
            t = q->f;
            q->f = (q->f)->next;
            free(t);
        }
        q->r = NULL;
        free(q);
        printf("Queue disposed\n");
    }
    else if(q != NULL)
    {
        free(q);
        printf("Queue disposed\n");
    }
    else
        printf("Queue not available\n");
}

void enqueue(queue q, node n)
{
    if(n != NULL && isempty(q))
	{
		n->next = NULL;
		q->f = n;
		q->r = n;
    }
    else if(q->f != NULL)
    {
    	n->next = NULL;
		q->r->next = n;
		q->r = n;
	}
    else
    	printf("Queue is Full\n");
}

void dequeue(queue q)
{
    node t1 = q->f;
    strcpy(t2->cname, t1->cname);
    strcpy(t2->problem, t1->problem);
	if(isempty(q))
	{
		printf("Queue is Empty\n");
	}
	else
	{
		q->f=q->f->next;
        enqueue(sl,t1);
	}
}

void disp_node(node n)//displays a node
{
    printf("Service request details:\n");
    char *stat;
    if(n->status == 1)
        stat = "Completed";
    else if(n->status == 0)
        stat = "Not Completed";
    printf("ServiceID: %d\nCustomer Name: %s\nIssue: %s\nService Status: %s\n", n->sid, &n->cname, &n->problem, &stat);
}

void disp_queue(queue q)//displays a queue
{
    if(!isempty(q)) 
    {
        node temp=q->f;
        while(temp!=NULL)
        {
            disp_node(temp);
            temp=temp->next;
        }
    }
    else
    {
        printf("Empty Queue\n");
    }
}

void complete(node n)//changes status of a node to 1
{
    if (n->status == 0)
        n->status = 1;
    return;
}

int queue_pos(queue q,int custid)//returns the queue postion details of a customer
{
    int pos=0;
    node temp = q->f;
    while (temp != NULL && temp->cid != custid)
    {
        pos++;
        temp = temp->next;
    }
    return (temp != NULL) ? pos : -1;
}

void modify(queue q, int custid)//used to change the details of a customers request
{
    char n[100];char p[100];
    node temp = q->f;
    int pos = queue_pos(q,custid);
    if(pos!=-1)                                        //node exists
    {
        while (temp != NULL && temp->cid != custid)
        {
            temp = temp->next;
        }
                
        printf("\nEnter new name: \n"); scanf("%s", n);
        strcpy(temp->cname, n);                            //change name
        printf("\nEnter new problem: \n"); scanf("%s", p);
        strcpy(temp->problem, p);                       //change problem
    }
    else                                       //node doesnt exist
        printf("\nNode not found \n\n");
    return;
}

void remove(queue q, int id)
{
    if(!isempty(q))
    {
        node t, p;
        t = q->f;
        while(t != NULL && t->sid != id)
        {
            p = t;
            t = t->next;
        }
        if(t == NULL)
        {
            printf("Complaint Not found\n");
            return;
        }
        else
        {
            p->next = t->next;
            free(t);
            printf("Complaint removed\n");
        }
        
    }
}

node new(queue q)
{
    node n = (node)malloc(sizeof(struct queue_node));
    if(n != NULL)
    {
        if(isempty(q))
            n->sid = 1;
        else
            n->sid = q->r->sid + 1;
        n->status = 0;
        n->cname = (char*)malloc(100*sizeof(char));
        n->problem = (char*)malloc(100*sizeof(char));
        printf("Enter Name: "); scanf("%[^\n]", n->cname);
        printf("Enter Problem: "); scanf("%[^\n]", n->problem);
        return n;
    }
    else
    {
        printf("Fatal error!\n");
        return NULL;
    }
    
}

void customer()
{
    int s;
    char c;
    do
    {
        switch (cmenu())
        {
            case 1:
                printf("Hardware(h) or software problem(s)? "); scanf("%c", &c);
                if(c == 'h')
                {
                    node n = new(hq);
                    enqueue(hq, n);
                }
                else
                {
                    node n = new(sq);
                    enqueue(sq, n);
                }
                break;

            case 2:
                printf("Hardware(h) or software problem(s)? "); scanf("%c", &c);
                printf("Enter service id: "); scanf("%d", &s);
                if(c == 'h')
                {
                    remove(hq, s);   
                }
                else
                {
                    remove(sq, s);
                }
                break;
            case 3:
                printf("Hardware(h) or software problem(s)? "); scanf("%c", &c);
                printf("Enter service id: "); scanf("%d", &s);
                if(c == 'h')
                {
                    if(queue_pos(hq, s) != -1)
                        printf("Your Queue postion is: %d\n", queue_pos(hq, s));
                    else
                        printf("Your queue position not found\n");
                       
                }
                else
                {
                    if(queue_pos(sq, s) != -1)
                        printf("Your Queue postion is: %d\n", queue_pos(sq, s));
                    else
                        printf("Your queue position not found\n");
                }
                break;
            case 4:
                printf("Hardware(h) or software problem(s)? "); scanf("%c", &c);
                printf("Enter service id: "); scanf("%d", &s);
                if(c == 'h')
                {
                    modify(hq, s);   
                }
                else
                {
                    modify(sq, s);
                }
                break;
            case 5:
                return;
        }

    } while (1);
    
}


void engineer()
{
    int s;
    char c;
    do
    {
        
    } while (1);
    
}

//menus
int menu()
{
    int c;
    printf("\tMenu\n1. Customer\n2. Engineer\n3. Admin\n4. Exit\nEnter a choice: ");
    scanf("%d", &c);
    return c;
}

int cmenu()//menu for the cutomers
{
    int c;
    printf("\t\tCustomer Menu\n\t1. Raise complaint\n\t2. Remove complaint\n\t3. Check queue position\n\t4. Modify complaint");
    printf("\n\t5. Back\n\tEnter choice: ");
    scanf("%d", &c);
    return c;
}

int emenu()//menu for the engineers
{
    int c;
    printf("\t\tEngineer Menu\n\t1. View all pending services\n\t2. View next in queue\n\t3. View details of a complaint\n\t");
    printf("4. Change status of current service\n\t5. Back\n\tEnter choice: ");
    scanf("%d", &c);
    return c;
}

int amenu()//menu for the admin
{
    int c;
    printf("\t\tAdmin Menu\n\t1. View all pending services\n\t2. View next in queue\n\t3. View details of a complaint\n");
    printf("\t4. View service log\n\t5. Back\n\tEnter choice: ");
    scanf("%d", &c);
    return c;
}

int main()
{
    do
    {
        switch (menu())
        {
            case 1:
                customer();
                break;
            case 2:
                engineer();
                break;
            case 3:
                admin();
                break;
            case 4:
                return 1;
        }
    } while (1);
}