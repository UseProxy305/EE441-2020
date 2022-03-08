#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
// CONSTANT PART
const long int MaxStackSize = 30000;// Assume a section has capacity maximum of 30000
const long int maxQSize=100000; // Assume waiting room has capacity maximum of 100000
// END OF CONSTANT PART

//CLASS DECLARATIONS

//STACK DECLARATION (Although it is a template class, stacks will always be the list of Student Class)
template <class T>
class Stack{
    private:
        T stacklist[MaxStackSize];//Stack List
        int top;// Top value that will determine which index is going to be popped
        int mlimit; // mlimit variable will hold the number of capacity for a section

    public:
        Stack();// Empty Constructor so that stacks for capacities can be declared at the beginning
        Stack(int limit); // Constructor with limit parameter
        void Push(const T & item);// Pushing function for a stack
        T Pop(void);// Popping function for a stack
        int StackEmpty(void) const;//Checks whether stack is empty or not
        int StackFull(void) const;//Checks whether stack is full or not
};



//STACK DECLARATION (Although it is a template class, queue will always be the list of Student Class)
template <class dataType>
class Queue{
    private:
        int mFront;//Front value for queue
        int mRear;//Rear value for queue
        int mCount;//Count value for queue
        dataType qlist[maxQSize];//Queue List
    public:
        Queue(void);//Queue Empty Constructor
        void Qinsert(const dataType & item);// To insert an item to queue
        dataType Qdelete(void);// To delete an item from a queue
        int QLenght(void) const;// To get the length of queue (How many items are there)
        int QEmpty(void) const; // Checks whether queue is empty or not
};

// Student Class Declaration
class Student
{
private:
    int mID;//Student ID
    char mPreferences[4]={NULL,NULL,NULL,NULL};// Preference lists that is initialize with full of NULL chars

public:
    Student();// Empty Constructor
    Student(int ID); // Constructor with ID as a parameter
    void addPreferences(char pref);// Adding a reference day into the reference list (It is adding one by one)
    int availableDays(Stack<Student> &wedStack,
                      Stack<Student> &thuStack,
                      Stack<Student> &friStack) const;// Eligible Sections Finder For Student
    int getID() const { return mID; }// Returning ID of current student (NOTE: It is DEFINED HERE)
    char * getPreferences() { return this->mPreferences; }// Returning Eligible Sections for current student as a char list (NOTE: It is DEFINED HERE)
    char getPriorPreference(Stack<Student> &wedStack,
                            Stack<Student> &thuStack,
                            Stack<Student> &friStack) const;// Getting most preferred eligible section, it returns a char.
};

int slotsMaker(char output [100]);// Slots setter for sections

int assignStudent(Student &currentStudent,
                  Stack<Student> &wedStack,
                  Stack<Student> &thuStack,
                  Stack<Student> &friStack);// Taking Student and placing them if there is only one eligible section

int findID(char data[100]);// Taking ID number while reading a file

void checkerForWaitingRoom(Queue<Student> &WaitingRoom,
                           Stack<Student> &wedStack,
                           Stack<Student> &thuStack,
                           Stack<Student> &friStack);// Checks all students in waiting queue, if there is a student with just one eligible section then place it via assigningStudent Function.

void assignAllQueue(Queue<Student> &WaitingRoom,
                    Stack<Student> &wedStack,
                    Stack<Student> &thuStack,
                    Stack<Student> &friStack);// After reading all input file, students will be placed based on the priority of their references.
#endif // HEADER_H_INCLUDED
