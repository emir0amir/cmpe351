 
#include<iostream>
#include <iomanip>
#include<string.h>
#include <string>
#include <fstream>
#include <cctype> 
#include <cstdlib>  
#include <sstream>  

using namespace std;

int globalstop = 1;
int fcfs = 0;
int sjf = 0;
int priority = 0;
int scheduling = 0;

struct node{
	int burst;
	int arrival; 
	int prority; 
	int queueId;   
	int numbering; 
	int waitingTime; 
	struct node *next;
};


struct node *createnode(int, int , int, int, int);
struct node *createmininode(int );
struct node *createmidnode(int , int );
int is_empty(struct node *);
struct node *insertFront(struct node *, int,int,int,int, int);
struct node *insertminiFront(struct node *, int);
struct node *insertBack(struct node *, int, int,int,int, int);
struct node *insertminiBack(struct node *, int);
struct node *insertmidBack(struct node *, int , int);
struct node *deleteFront(struct node *);
void deleteAfter(struct node *afternode);
struct node* deepcopyList(struct node* original);
struct node *moveBeginning(struct node *header, struct node *nodetobegin);
void display(struct node* r,struct node* ,struct node* ,struct node* );
void writetofile(const std::string& ,struct node* r,struct node* ,struct node* ,struct node* );
struct node *swapnodes(struct node *,struct node *);
struct node *removeNode(struct node *header, int numbering);
int count(struct node *);
struct node* filterByQueue(struct node* , int );
void computeWaitingTimes(struct node* );
void sortarrival(struct node **, int);
void sortburst(struct node **, int);
void sortpriority(struct node **, int);
void sortnumbering(struct node **, int);
void printlist(struct node *header);

struct node *FSFC(struct node *);
struct node *SJF(struct node * );
struct node *PRIORITY(struct node *);



int main(int argc, char* argv[]) {

     if (argc != 3) {
    cout << "Usage: " << argv[0] << " <inputFile> <outputFile>" << endl;
    return 1;
}

string inputFile = argv[1];
string outputFile = argv[2];


  
    // Display the results
  //  cout << "Input file: " << (inputFile.empty() ? "Invalid command-line arguments." : inputFile) << endl;
  //  cout << "Output file: " << (outputFile.empty() ? "Invalid command-line arguments." : outputFile) << endl;

	
	struct node *header = NULL;
	struct node *header2 ;
	struct node *newheader;
	struct node *newheader2;
	struct node *newheader3;
	struct node *newheader4;
	struct node *newheader5;
	struct node *newheader6;
	int item_1, item_2, item_3, item_4;
	item_4 = 1;
	 int a = 0;
	 int cnt;
     string scheduler;
     int queueId;


	 
	  ifstream input(inputFile.c_str());

    if (input.is_open()) 
	  {char colon;
       while (input >> item_1 >> colon
             >> item_2 >> colon
             >> item_3 >> colon
             >> queueId) 
       {
    if (header == NULL) {
        header = createnode(item_1, item_2, item_3, queueId, item_4);
    } else {
        header = insertBack(header, item_1, item_2, item_3, queueId, item_4);
    }
    item_4++;
       }
       input.close();

    } else {
        std::cout << "Error opening input file: " << inputFile << endl;
        return 1;
    } 
    
     
    
      int size = 0;
	  size = count(header);
    
	if(header == NULL)
	{
      std::cout<<"LIST IS EMPTY";
	}
	else
	{
       sortarrival(&header, size);
	}
	 
	double averaget;
	int waittime;
	   
        //  FCFS (Non-preemptive) 
        newheader = NULL;
        struct node*headercopyforFCFS = deepcopyList(header);
        newheader = FSFC(headercopyforFCFS);

        //SJF (Non-preemptive)
        newheader2 = NULL;
        struct node* headerCopyForSJF = deepcopyList(header);
        newheader2 = SJF(headerCopyForSJF);

        //Priority (Non-preemptive)
        newheader3 = NULL;
        struct node* headerCopyForPriority = deepcopyList(header);
        newheader3 = PRIORITY(headerCopyForPriority);

        //  Output 
        display(newheader, newheader2, newheader3, header);
        writetofile(outputFile, newheader, newheader2, newheader3, header);
        

        return 0;
        }

struct node *createnode(int item1, int item2, int item3, int queueId, int item4)
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(node));
	temp->burst = item1;
	temp->arrival = item2;
	temp->prority = item3;
    temp->queueId = queueId;
	temp->numbering = item4;
	temp->waitingTime = 0;
	temp->next = NULL;
	
	return temp;
}

struct node *createmininode(int item1)
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(node));
	temp->burst = item1;
	temp->next = NULL;
	
	return temp;
}

struct node *createmidnode(int waiting, int numbering)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->burst = 0;
    temp->arrival = 0;
    temp->prority = 0;
    temp->queueId = 0;

    temp->waitingTime = waiting;
    temp->numbering = numbering;
    temp->next = NULL;

    return temp;
}

int is_empty(struct node *header)
{
	if(header == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct node *insertFront(struct node *header, int item1, int item2, int item3, int queueId, int item4)
{
	struct node *temp;
	temp = createnode(item1,item2,item3,queueId,item4);
	temp->next = header;
	header =  temp;
	
	return header;
}

struct node *insertminiFront(struct node *header, int item)
{
	struct node *temp;
	temp = createmininode(item);
	temp->next = header;
	header =  temp;
	
	return header;
}

struct node *insertBack(struct node *header, int item1, int item2, int item3, int queueId, int item4)
{
    if (header == NULL)
        return createnode(item1, item2, item3, queueId, item4);

    struct node *temp;
    struct node *ht;

    temp = createnode(item1, item2, item3, queueId, item4);
    ht = header;

    while (ht->next != NULL) {
        ht = ht->next;
    }

    ht->next = temp;
    return header;
}

struct node *insertBackWithWT(struct node *header, int item1, int item2, int item3, int queueId, int item4, int waitingTime)
{
    struct node *temp;
    struct node *ht;

    temp = createnode(item1, item2, item3, queueId, item4);
    temp->waitingTime = waitingTime;

    if(header == NULL)
        return temp;

    ht = header;
    while(ht->next != NULL)
        ht = ht->next;

    ht->next = temp;
    return header;
}


struct node *insertminiBack(struct node *header, int item)
{
	struct node *temp;
	struct node *ht;
	temp = createmininode(item);
	ht = header;
	while(ht->next != NULL)
	{
		ht = ht->next;
	}
	ht->next = temp;
	
	return header;
}

struct node *insertmidBack(struct node *header, int item, int item2)
{
	struct node *temp;
	struct node *ht;
	temp = createmidnode(item,item2);
	ht = header;
	while(ht->next != NULL)
	{
		ht = ht->next;
	}
	ht->next = temp;
	
	return header;
}

struct node *deleteFront(struct node *header)
{
	if(header == NULL)
	{
		std::cout<<"The list is empty";
		exit(1);
	}
	else
	{
	struct node *temp;
	temp = header;
	header = temp->next;
	free(temp);
    temp = NULL;
}
	
	return header;
}

void deleteAfter(struct node *afternode)
{
	if(afternode->next == NULL)
	{
		std::cout<<"The list cannot be delete it";
		exit(1);
	}
	else
	{
		struct node *temp;
		temp = afternode->next;
		afternode->next = temp->next;
		free(temp);
        temp = NULL;
	}
	
}

struct node* deepcopyList(struct node* original) {
    if (!original) return NULL;

    struct node* copy = createnode(original->burst, original->arrival, original->prority, original->queueId, original->numbering);
    struct node* temp = original->next;
    struct node* copyTemp = copy;

    while (temp) {
        copyTemp->next = createnode(temp->burst, temp->arrival, temp->prority, temp->queueId, temp->numbering);
        temp = temp->next;
        copyTemp = copyTemp->next;
    }

    return copy;
}


struct node *moveBeginning(struct node *header, struct node *nodetobegin)
{
    struct node *temp;
    int w, x, y, q, z;

    w = nodetobegin->next->burst;
    x = nodetobegin->next->arrival;
    y = nodetobegin->next->prority;
    q = nodetobegin->next->queueId;
    z = nodetobegin->next->numbering;

    deleteAfter(nodetobegin);

    temp = createnode(w, x, y, q, z);
    temp->next = header;
    header = temp;

    return header;
}


struct node *swapnodes(struct node *temp, struct node *tp)
{
	int temp1, temp2, temp3, temp4;
	struct node *t = tp->next;
	tp->next = temp;
	temp->next = t;
			 return tp;
}

void freeList(struct node *header) 
{
    while (header != NULL) {
        struct node *temp = header;
        header = header->next;
        free(temp);
        temp = NULL;
    }
}


struct node *removeNode(struct node *header, int numbering) 
{
    struct node *temp = header;
    struct node *prev = NULL;

    while (temp != NULL && temp->numbering != numbering) 
	{
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) 
	{
        
        return header;
    }

    if (prev == NULL) 
	{
        
        header = temp->next;
    } 
	else 
	{
        prev->next = temp->next;
    }

    free(temp);
    temp = NULL;
    return header;
}

void sortburst(struct node **header, int size)
{
	struct node **ht;
	int swap;
	for(int i=0; i<=size-1; i++)
	{
		ht = header;
		swap =0;
		for(int j=0; j< size-i-1; j++)
		{
			struct node *h1 = *ht;
			struct node *h2 = h1->next;
			
			if(h1->burst > h2->burst)
			{
				*ht = swapnodes(h1,h2);
				swap =1;
			}
			ht = &(*ht)->next;
		}
		
		if(swap ==0)
		{
			break;
			
		}
	}
}


void sortarrival(struct node **header, int size)
{
	struct node **ht;
	int swap;
	for(int i=0; i<=size-1; i++)
	{
		ht = header;
		swap =0;
		for(int j=0; j< size-i-1; j++)
		{
			struct node *h1 = *ht;
			struct node *h2 = h1->next;
			
			if(h1->arrival > h2->arrival)
			{
				*ht = swapnodes(h1,h2);
				swap =1;
			}
			ht = &(*ht)->next;
		}
		
		if(swap ==0)
		{
			break;
			
		}
	}
}

void sortpriority(struct node **header, int size)
{
	struct node **ht;
	int swap;
	for(int i=0; i<=size-1; i++)
	{
		ht = header;
		swap =0;
		for(int j=0; j< size-i-1; j++)
		{
			struct node *h1 = *ht;
			struct node *h2 = h1->next;
			
			if(h1->prority > h2->prority)
			{
				*ht = swapnodes(h1,h2);
				swap =1;
			}
			ht = &(*ht)->next;
		}
		
		if(swap ==0)
		{
			break;
			
		}
	}
}

void sortnumbering(struct node **header, int size)
{
	struct node **ht;
	int swap;
	for(int i=0; i<=size-1; i++)
	{
		ht = header;
		swap =0;
		for(int j=0; j< size-i-1; j++)
		{
			struct node *h1 = *ht;
			struct node *h2 = h1->next;
			
			if(h1->numbering > h2->numbering)
			{
				*ht = swapnodes(h1,h2);
				swap =1;
			}
			ht = &(*ht)->next;
		}
		
		if(swap ==0)
		{
			break;
			
		}
	}
}

int count(struct node *header)
{
	struct node *temp;
	temp = header;
	int cnt;
	 cnt = 0;
	while(temp != NULL)
	{
		cnt = cnt + 1;
		temp = temp->next;		
    }
 return cnt;

}

void computeWaitingTimes(struct node* header) {
    int currentTime = 0;

    while (header != NULL) {
        if (currentTime < header->arrival) {
            currentTime = header->arrival;
        }

        header->waitingTime = currentTime - header->arrival;
        currentTime += header->burst;

        header = header->next;
    }
}

struct node* filterByQueueWithWT(struct node* head, int qid) {
    struct node* result = NULL;

    while (head != NULL) {
        if (head->queueId == qid) {
            if (result == NULL)
                result = createnode(head->burst, head->arrival, head->prority, head->queueId, head->numbering);
            else
                result = insertBackWithWT(result, head->burst, head->arrival, head->prority, head->queueId, head->numbering, head->waitingTime);
        }
        head = head->next;
    }
    return result;
}

void printlist(struct node *header)
{
	if(header == NULL)
	{
		cout<<"The list is empty";
		exit(1);
	}
	else
	{
		struct node *temp;
		int x;
		temp = header;
		while(temp != NULL)
		{
		x = temp->burst;
		cout<<x<<", ";
		temp = temp->next;	
		}
		cout<<endl;
	}
}

struct node* FSFC(struct node* header) {
    cout << "FCFS Scheduling Algorithm Selected" << endl;
    int maxQueueId = 0;
    struct node* temp = header;

    while(temp) {
        if(temp->queueId > maxQueueId) maxQueueId = temp->queueId;
        temp = temp->next;
    }

    struct node* newHeader = NULL;

    for(int qid=1; qid<=maxQueueId; qid++) {
        struct node* queueList = filterByQueue(header, qid);
        int n = count(queueList);

        if(n == 0) {
            newHeader = insertBack(newHeader, 0,0,0,qid,0); // placeholder for empty
            continue;
        }

        sortarrival(&queueList, n);
        computeWaitingTimes(queueList);

        struct node* t = queueList;
        while(t) {
            newHeader = insertBackWithWT(newHeader, t->burst, t->arrival, t->prority, t->queueId, t->numbering, t->waitingTime);
            t = t->next;
        }

        freeList(queueList);
    }

    return newHeader;
}



// --------------------- SJF ---------------------
struct node* SJF(struct node* header) {
    cout << "SJF Scheduling Algorithm Selected" << endl;
    int maxQueueId = 0;
    struct node* temp = header;

    while(temp) {
        if(temp->queueId > maxQueueId) maxQueueId = temp->queueId;
        temp = temp->next;
    }

    struct node* newHeader = NULL;

    for(int qid = 1; qid <= maxQueueId; qid++) {
        struct node* queueList = filterByQueue(header, qid);
        int n = count(queueList);

        if(n == 0) {
            newHeader = insertBack(newHeader, 0,0,0,qid,0); // placeholder
            continue;
        }

        sortarrival(&queueList, n);
        // Non-preemptive SJF: sort by burst for processes that have arrived
        struct node* sjfList = NULL;
        int currentTime = 0;

        while(queueList) {
            // Find all arrived nodes
            struct node* ptr = queueList;
            struct node* minBurstNode = queueList;
            while(ptr) {
                if(ptr->arrival <= currentTime && ptr->burst < minBurstNode->burst)
                    minBurstNode = ptr;
                ptr = ptr->next;
            }

            // If no process has arrived yet, pick first one
            if(currentTime < minBurstNode->arrival)
                currentTime = minBurstNode->arrival;

            minBurstNode->waitingTime = currentTime - minBurstNode->arrival;
            currentTime += minBurstNode->burst;

            sjfList = insertBackWithWT(sjfList, minBurstNode->burst, minBurstNode->arrival, minBurstNode->prority, minBurstNode->queueId, minBurstNode->numbering, minBurstNode->waitingTime);

            // Remove node from queueList
            queueList = removeNode(queueList, minBurstNode->numbering);
        }

        // Append sjfList to newHeader
        temp = sjfList;
        while(temp) {
            newHeader = insertBackWithWT(newHeader, temp->burst, temp->arrival, temp->prority, temp->queueId, temp->numbering, temp->waitingTime);
            temp = temp->next;
        }

        freeList(sjfList);
    }

    return newHeader;
}


// --------------------- PRIORITY ---------------------
struct node* PRIORITY(struct node* header) {
    cout << "Priority Scheduling Algorithm Selected" << endl;
    int maxQueueId = 0;
    struct node* temp = header;

    while(temp) {
        if(temp->queueId > maxQueueId) maxQueueId = temp->queueId;
        temp = temp->next;
    }

    struct node* newHeader = NULL;

    for(int qid = 1; qid <= maxQueueId; qid++) {
        struct node* queueList = filterByQueue(header, qid);
        int n = count(queueList);

        if(n == 0) {
            newHeader = insertBack(newHeader, 0,0,0,qid,0); // placeholder
            continue;
        }

        sortarrival(&queueList, n);
        struct node* priorityList = NULL;
        int currentTime = 0;

        while(queueList) {
            // Find highest priority arrived node (lowest number = highest priority)
            struct node* ptr = queueList;
            struct node* minPriorityNode = queueList;
            while(ptr) {
                if(ptr->arrival <= currentTime && ptr->prority < minPriorityNode->prority)
                    minPriorityNode = ptr;
                ptr = ptr->next;
            }

            if(currentTime < minPriorityNode->arrival)
                currentTime = minPriorityNode->arrival;

            minPriorityNode->waitingTime = currentTime - minPriorityNode->arrival;
            currentTime += minPriorityNode->burst;

            priorityList = insertBackWithWT(priorityList, minPriorityNode->burst, minPriorityNode->arrival, minPriorityNode->prority, minPriorityNode->queueId, minPriorityNode->numbering, minPriorityNode->waitingTime);

            // Remove node from queueList
            queueList = removeNode(queueList, minPriorityNode->numbering);
        }

        // Append priorityList to newHeader
        temp = priorityList;
        while(temp) {
            newHeader = insertBackWithWT(newHeader, temp->burst, temp->arrival, temp->prority, temp->queueId, temp->numbering, temp->waitingTime);
            temp = temp->next;
        }

        freeList(priorityList);
    }

    return newHeader;
}

