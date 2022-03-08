// HW3 for EE441 Course
// Berkay IPEK 2304814
// In header file, methods and functions comments are there.
// main.cpp is consisting only for algortihms
#include <iostream>
#include <fstream>
#include "header.h"
/* reading processes from file */

using namespace std;
ifstream processesFile; /* input file stream */
int main()
{
    // This part is taken from homework manual
    processesFile.open("processes.txt");
    int numProcesses; /* number of processes */
    processesFile >> numProcesses; /* read from file */
    NodeLinkedList processLinked[numProcesses]; /* create NodeLinkedList array */
    NodeBST processBST[numProcesses]; /* create NodeBST array */
    BST Tree;/*Creating Binary Search Tree*/
    LinkedList RQ;/*Creating LinkedList */
    int processID, arrivalTime, runTime, priority;
    for(int i=0; i<numProcesses; ++i){
        /* read 4 integers from file */
        processesFile >> processID >> arrivalTime >> runTime >> priority;
        /* construct i'th element of the array */
        processLinked[i] = NodeLinkedList(processID, arrivalTime, runTime, priority);//Adding Nodes for LinkedList
        processBST[i]=NodeBST(processID, arrivalTime, runTime, priority);//Adding Nodes for Binary Search Tree

    }

    processesFile.close();
    /* end of reading from file */
    int time = 0; // CPU time
    bool CPUBusy = false; // is the CPU currently running a process
    NodeLinkedList* currentProcessLinkedList = NULL; // pointer to the process CPU is currently running (for LinkedList)
    int processIndex = 0; // index of the process awaiting insertion in RQ
    cout<<"Linked List Implementation RQ"<<endl<<endl;
    while ((processIndex < numProcesses) || (!RQ.isEmpty()) || (CPUBusy==true)){
        if(processLinked[processIndex].getArrivalTime()==time){
                RQ.addNodeLinkedList(processLinked[processIndex]);//Adding nodes to linkedlist
                processIndex++;
        }
        if (CPUBusy == true){currentProcessLinkedList->decreaseRunTime();} // CPU is running a process
        if(currentProcessLinkedList!=NULL){
            if (currentProcessLinkedList->getRunTime() == 0){
                // if it was last cycle of the process
                cout<<currentProcessLinkedList->getProcessID()<<endl;
                CPUBusy = false; // CPU is no longer running a process
            }
        }
        if (CPUBusy==false &&(!RQ.isEmpty())){
            currentProcessLinkedList=RQ.findNodeLinkedListMaxPriority();//Finding max priority
            RQ.deleteNodeLinkedList();//Deleting it
            CPUBusy=true;

        }
        time++;
    }
    RQ.printNumbers();//Printing Numbers
    time = 0; // CPU time
    CPUBusy = false; // is the CPU currently running a process
    NodeBST* currentProcessBST = NULL; // pointer to the process CPU is currently running (for Binary Search Tree)
    processIndex = 0; // index of the process awaiting insertion in RQ
    cout<<"Binary Search Tree implementation"<<endl<<endl;
    while ((processIndex < numProcesses) || (!Tree.isEmpty()) || (CPUBusy==true)){
        if(processBST[processIndex].getArrivalTime()==time){
                Tree.addNodeBST(processBST[processIndex]);//Adding nodes to Tree
                processIndex++;
        }
        if (CPUBusy == true){currentProcessBST->decreaseRunTime();} // CPU is running a process
        if(currentProcessBST!=NULL){
            if (currentProcessBST->getRunTime() == 0){
                // if it was last cycle of the process
                cout<<currentProcessBST->getProcessID()<<endl;
                CPUBusy = false; // CPU is no longer running a process
            }
        }
        if (CPUBusy==false &&(!Tree.isEmpty())){
            currentProcessBST=Tree.deleteNodeBST();
            CPUBusy=true;

        }
        time++;
    }
    cout<<endl;
    Tree.printNodeBSTNumbers();
    return 0;
}
/// NODE FOR LINKEDLIST METHDOS
NodeLinkedList::NodeLinkedList(){}//Empty Constructor

NodeLinkedList::NodeLinkedList(int item1,int item2,int item3,int item4, NodeLinkedList * ptrNext){//Constructor for node
processID=item1;
arrivalTime=item2;
runTime=item3;
priority=item4;
next=ptrNext;
}

///LINKED LIST METHODS
void LinkedList::addNodeLinkedList(NodeLinkedList addedNodeLinkedList){
    //Creating Node in a dynamic way
    NodeLinkedList * newNodeLinkedList= new NodeLinkedList(addedNodeLinkedList.getProcessID(),addedNodeLinkedList.getArrivalTime(),addedNodeLinkedList.getRunTime(),addedNodeLinkedList.getPriority());
    //Checks if head is NULL (LinkedList is empty)
    if(head==NULL){
        numberOfInsertion++;//Increment Inserting Node Counter
        head=newNodeLinkedList;//Head and tail initializing
        tail=newNodeLinkedList;
        return;
    }
    //If LinkedList is not empty
    else{
        NodeLinkedList * temp = head;//Create temp node pointer to be iterated
        NodeLinkedList * previous=NULL;//Hold data for previous of temp node since we are going to insert it into list
        numberOfInsertion++;//Since we have looked head pointer we should increment inserting visited node counter
        while(temp!=NULL){//Do it until temp points to NULL (If it points to NULL, then it finished linkedlist)
            if(temp->getPriority()>addedNodeLinkedList.getPriority()){//Checks priority if it is bigger than it should be inserted right there.
                break;
            }
            //Update temp and previous (Go to next one)
            previous=temp;
            temp=temp->next;
            numberOfInsertion++;//We moved our temp node to next one. Therefore, increment inserting visited node counter
        }
        if(temp==head){//If temp ==head, it should be inserted into head of linkedlist. Therefore update head also
            newNodeLinkedList->next=temp;
            head=newNodeLinkedList;
            return;
        }
        else if(temp==NULL){//If temp==NULL, that means it should be inserted into end of linkedlist. Therefore update tail also
            tail->next=newNodeLinkedList;
            tail=tail->next;
            return;
        }
        else{//This block is to insert node into list at the middle of list.
            previous->next=newNodeLinkedList;
            newNodeLinkedList->next=temp;
            return;
        }
    }
}
NodeLinkedList* LinkedList::findNodeLinkedListMaxPriority(void){
    return head;//Since linkedlist is in descending order of priority. It is enough to return head.
}
void LinkedList::deleteNodeLinkedList(){
numberOfSearching++;//Deleting each node will take just one visited because it is already in head
if(head==tail){head=NULL;tail=NULL;return;}//If list consists just one element then empty
head=head->next;//Update head
return ;
}
void LinkedList::printNumbers(){
    cout<<endl;
    cout<<"Total number of "<<this->numberOfSearching<<" Node has been visited to search"<<endl;//Printing result
    cout<<"Total number of "<<this->numberOfInsertion<<" Node has been visited to insert"<<endl;
    cout<<endl;
    return;
}

///NODE FOR TREE METHODS
NodeBST::NodeBST(){}    //Empty Constructor

NodeBST::NodeBST(int item1,int item2,int item3,int item4, NodeBST * ptrRight,NodeBST * ptrLeft){//Constructor
processID=item1;
arrivalTime=item2;
runTime=item3;
priority=item4;
right=ptrRight;
left=ptrLeft;
}
NodeBST* NodeBST::rightNodeBST(void) const{//To access right node
return right;
}
NodeBST* NodeBST::leftNodeBST(void) const{//To access left node
return left;
}
void BST::addNodeBST(NodeBST addedNodeBST){//Adding Node to BST according to priority level
    //Create new node dynamically
    NodeBST * newNodeBST= new NodeBST(addedNodeBST.getProcessID(),addedNodeBST.getArrivalTime(),addedNodeBST.getRunTime(),addedNodeBST.getPriority());
    if(root==NULL){//If root is NULL, that means tree is empty
        numberOfInsertion++;//Since we looked root, increment # of visited nodes for insertion.
        root=newNodeBST;//Therefore, root is started with addednode
        return;
    }
    else{                       //If root is not NULL, tree is not empty
        NodeBST * temp=root;        //Temp pointer so that we can visit nodes
        numberOfInsertion++;        //Since we looked root already , increment # of visited nodes for insertion.
        while(true){                // Infinity loop statement
            if(newNodeBST->getPriority() < temp->getPriority()){//If priority is lower than go left
                if(temp->leftNodeBST() == NULL){//If its left node is empty, put this node into that point
                    temp->left=newNodeBST;// Putting it
                    numberOfInsertion++;// Since we looked left node of it, increment # of visited nodes for insertion
                    break;//Break the loop
                }
                temp=temp->leftNodeBST(); // Go Left
                numberOfInsertion++;//Since we went to left, increment # of visited nodes for insertion
            }
            else{//If priority is higher than go right
                if(temp->rightNodeBST() == NULL){//If its right node is empty, put it into that point
                    temp->right=newNodeBST;//Putting it
                    numberOfInsertion++;// Since we looked right node of it, increment # of visited nodes for insertion
                    break;//Break the loop
                }
                temp=temp->rightNodeBST(); //Go right
                numberOfInsertion++;       //Since we went to right, increment # of visited nodes for insertion
            }// end of else block
        }//end of while loop
    }// end of else block
    return;
}
NodeBST* BST::deleteNodeBST(void){//This will delete node from tree by considering highest priority
    numberOfSearching++;//We will look root of it therefore increment # of visited node for searching
    NodeBST * temp=root;//Temp pointer to point root of it
    NodeBST * prev=NULL;//Take previous node for deleting operation
    while(temp->leftNodeBST()!=NULL){//If its left node is NULL, there is no other node with highest priority
        prev=temp;//Update previous one
        temp=temp->leftNodeBST();//Go left
        numberOfSearching++;// Increment # of visited node for searching since we went to left
    }
    if(prev==NULL){//If previous node is NULL, root should be updated
        root=temp->rightNodeBST();//Update root
        return temp;
    }
    else{
        if(temp->rightNodeBST()==NULL){//If right side of it is NULL, there is nothing surprising
            prev->left=NULL;// Previous node's left pointer is going to point NULL
            return temp;
        }
        else{//Else = right side of temp is full
            prev->left=temp->rightNodeBST();// Update Tree by connecting right node of temp and previous' left
            return temp;
        }//end of else block
    }//end of else block
}//End of function
