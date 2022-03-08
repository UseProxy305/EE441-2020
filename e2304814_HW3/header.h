#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
//Node
class NodeLinkedList{
    private:
        int processID, arrivalTime, runTime, priority;//Process has four different data
    public:
        NodeLinkedList * next; // Pointer which points next in the list
        NodeLinkedList();  //Empty Constructor so that it can be initialized without any argument
        NodeLinkedList(int item1,int item2,int item3,int item4,NodeLinkedList * ptrNext=NULL);//Constructor
        //Get Methods
        int getProcessID(void) const{return processID;}
        int getArrivalTime(void) const{return arrivalTime;}
        int getRunTime(void) const{return runTime;}
        int getPriority(void) const{return priority;}
        //To decrease data (Since it is a private member, it can not be directly decreased)
        void decreaseRunTime(void){this->runTime--;}
};

//LinkedList Class
class LinkedList{
    private:
        NodeLinkedList *head,*tail;// Pointing the start point and end point in the list
        int numberOfInsertion=0;    //While inserting how many node has been visited
        int numberOfSearching=0;    //While searching how many node has been visited
    public:
        LinkedList(NodeLinkedList * mhead=NULL,NodeLinkedList* mtail=NULL){head=mhead;tail=mtail;}//LinkedList Constructor
        void addNodeLinkedList(NodeLinkedList addedNodeLinkedList);//Adding Node to list with respect to priority
        bool isEmpty(void)const{return ((head==NULL)&&(tail==NULL));}//Returning true if linkedlist is empty, ow returns false
        NodeLinkedList* findNodeLinkedListMaxPriority(void);//Find the maximum priority (Returning head)
        void deleteNodeLinkedList();//Deleting node from list
        void printNumbers();//Printing numbers
};

class NodeBST{
    private:
        int processID, arrivalTime, runTime, priority;//Process has four different data
    public:
        NodeBST * right, *left;// Pointer which points next nodes in tree
        NodeBST();//Empty Constructor so that it can be initialized without any argument
        NodeBST(int item1,int item2,int item3,int item4,NodeBST * ptrRight=NULL,NodeBST * ptrLeft=NULL);//Constructor
        NodeBST * rightNodeBST(void) const;//To access right node pointer
        NodeBST * leftNodeBST(void) const;//To access left node pointer
        //GETTER METHODS
        int getProcessID(void) const{return processID;}
        int getArrivalTime(void) const{return arrivalTime;}
        int getRunTime(void) const{return runTime;}
        int getPriority(void) const{return priority;}
        //To decrease data (Since it is a private member, it can not be directly decreased
        void decreaseRunTime(void){this->runTime--;}
};
class BST{
    private:
        NodeBST *root;//Root pointer for tree
        int numberOfInsertion=0;//While inserting how many node has been visited
        int numberOfSearching=0;//While searching how many node has been visited
    public:
        BST(NodeBST * _root = NULL){root=_root;}//Constructor for Tree Class
        void addNodeBST(NodeBST addedNodeBST);//Adding node in terms of priority level
        NodeBST* deleteNodeBST(void);// Deleting node who has maximum priority, and redesigning tree structure
        bool isEmpty(void) const{return root==NULL;}//If tree is empty, return true
        void printNodeBSTNumbers(void) const{//Printing # of visited nodes.
            std::cout<<std::endl;
            std::cout<<"Total number of "<<this->numberOfSearching<<" Node has been visited to search"<<std::endl;//Printing result
            std::cout<<"Total number of "<<this->numberOfInsertion<<" Node has been visited to insert"<<std::endl;
            std::cout<<std::endl;
            return;
        }
};

#endif // HEADER_H_INCLUDED
