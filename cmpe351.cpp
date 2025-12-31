//SIMULATING THE SERVICE OF JOBS IN CPU SCHEDULING  
#include<iostream>
#include<string.h>
#include <string>
#include <fstream>
#include <cctype> 
#include <cstdlib>  
#include <sstream>  

using namespace std;

int globalstop = 1;
int prem= 0;
int fcfs = 0;
int sjf = 0;
int priority = 0;
int scheduling = 0;

struct node{
	int burst; //burst time
	int arrival; //arrival time
	int prority; //priority level
	int queueId;   //grouping queue id
	int numbering; //process number
	int waitingTime; //waiting time
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
void insertAfter(struct node *, int, int, int,int);
struct node *deleteFront(struct node *);
void deleteAfter(struct node *afternode);
struct node* deepcopyList(struct node* original);
struct node *moveBeginning(struct node *header, struct node *nodetobegin);
void display(struct node *,struct node *,struct node *,struct node *,struct node *,struct node *, struct node*);
void writetofile(const std::string& , struct node* , struct node* , struct node* , struct node* , struct node* , struct node* , struct node *);
struct node *swapnodes(struct node *,struct node *);
struct node *removeNode(struct node *header, int numbering);
int count(struct node *);
void printlist2(struct node *header2);
void sortarrival(struct node **, int);
void sortburst(struct node **, int);
void sortpriority(struct node **, int);
void sortnumbering(struct node **, int);
void sortList(struct node **head);
void printlist(struct node *header);

struct node *FSFC(struct node *, struct node **);
struct node *SJF(struct node * , struct node **);
struct node *PRIORITY(struct node * , struct node **);



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
	 string premmode;
     string scheduler;
     int queueId;


	 
	  ifstream input(inputFile.c_str());

    if (input.is_open()) 
	  {
       while (input >> item_1 >> item_2 >> item_3 >> queueId) 
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
	//cout<<"\n";
	 
	

	double averaget;
	int waittime;
	   
	

        //  FCFS (Non-preemptive) 
        newheader = NULL;
        newheader = FSFC(header, &newheader);

        // SJF (Non-preemptive)
        newheader2 = NULL;
        struct node* headerCopyForSJF = deepcopyList(header);
        newheader2 = SJF(headerCopyForSJF, &newheader2);

        //Priority (Non-preemptive)
        newheader3 = NULL;
        struct node* headerCopyForPriority = deepcopyList(header);
        newheader3 = PRIORITY(headerCopyForPriority, &newheader3);

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
