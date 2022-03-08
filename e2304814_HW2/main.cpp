#include <iostream>
#include <fstream>
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
// This header file is full of declaration
// Also , it consists explanation (what they do) for functions, constant variables, classes and methods.

using namespace std;

//MAIN FUNCTION
int main(){
    // These stacks and queues just for declaration. It is not in header file since I don't want to use it as global variable.
    Stack<Student> wedStack,thuStack,friStack;
    Queue<Student> WaitingRoom;

    int previousStudentID=0; // This parameter is checking whether there is a duplicated students in file.

    //Taking input from a file (Taken from EE441_Homework_2.pdf)
    ifstream inputtxt;
    inputtxt.open("preferences.txt");
    char output[100];
    if (inputtxt.is_open()) {
        while (!inputtxt.eof()) {
            inputtxt >> output;

            // This if-else block is checking line info for class(1) or student (2)

            // If block is for class and capacities
            if(output[0]=='W' ||output[0]=='T'||output[0]=='F'){ //Assuming days are only Wednesday, Thursday, and Friday

                int capacity = slotsMaker(output);// Capacity finder

                // Wednesday
                if(output[0]=='W'){
                    Stack<Student> wedStacks(capacity); // initialization for Wednesday Stack
                    wedStack=wedStacks; //  Assigning it into "wedStack"
                }

                // Thursday
                else if(output[0]=='T'){
                    Stack<Student> thuStacks(capacity);// initialization for Thursday Stack
                    thuStack=thuStacks; //  Assigning it into "thuStack"
                }
                // Friday
                else if(output[0]=='F'){
                    Stack<Student> friStacks(capacity);// initialization for Friday Stack
                    friStack=friStacks; //  Assigning it into "friStack"
                }
                else{
                    cerr<<"Days should be correct!!"<<endl; // Not expected block since if block is checking W,T,F therefore probably it is not possible to go into this line
                }
            }

            //Else block is for students and preferences
            else{
                int currentStudentID=findID(output); // ID finder

                // Since ID can be in any range, iteration can not be given directly.
                // That's why the variable "iteration" is set to the location in right the first comma via While Loop
                int iteration=0;
                while(output[iteration]!=','){
                    iteration++;
                }
                Student currentStudent(currentStudentID); // initialization for current iterated student that is read from input file
                iteration++;// After the while loop iteration is pointing ",", therefore it must be added by one

                // This if block is checking whether there is a duplicated consecutively students in file. If there is then break the while loop.
                if (previousStudentID==currentStudentID){break;}

                // Getting preferences for a specific student.
                while(output[iteration]!=NULL){
                    if(output[iteration]=='F' ||output[iteration]=='T' || output[iteration]=='W')// Assume there is only F,W,T
                        {   currentStudent.addPreferences(output[iteration]);// Adding preference initial character into the currentStudent object
                            }
                    iteration++;
                }
                // checkerForAssigning variable is holding the necessary info for checking the queue again or not.
                // It is returning 1 when currentStudent is assigned to a section
                // It is returning 0 when currentStudent is not assigned to a section
                int checkerForAssigning=assignStudent(currentStudent,wedStack,thuStack,friStack);
                if (checkerForAssigning== 1){
                    // If currentStudent is assigned to a section (Updated in stacks), then go to check queue
                    checkerForWaitingRoom(WaitingRoom,wedStack,thuStack,friStack);
                }
                else{
                    // If it is not assigned to a section (No updated in stacks), then currentStudent should be inserted into waiting line.
                    WaitingRoom.Qinsert(currentStudent);
                }
                previousStudentID=currentStudentID;// To keep the information about student that is recently read

            }
        }
    }
    inputtxt.close();

    // When the while loop is finished on the above, queue should be assigned according to most preffered sections
    assignAllQueue(WaitingRoom,wedStack,thuStack,friStack);

    int studentID;// Student ID that will be written
    //WRITING ON THE FILE (Taken from EE441_Homework_2.pdf)
    ofstream outputtxt;
    outputtxt.open("results.txt");//File name

    //Writing on a file part is going to be form of: (For days and unassigned part)

    //if stack(queue) is empty , put "-"
    //else
        //while Stack is not empty;
            // Day Stack is popped. And ID that corresponds to popped student is pulled
            // write ID and new line char character
        // When day is finished, put new line character

    outputtxt << "Wednesday:\n";
    if(wedStack.StackEmpty()){outputtxt<<"-\n\n";}
    else{
        while(!wedStack.StackEmpty()){
            studentID=wedStack.Pop().getID();
            outputtxt<<studentID;
            outputtxt<<"\n";
        }
        outputtxt<<"\n";
    }
    outputtxt << "Thursday:\n";
    if(thuStack.StackEmpty()){outputtxt<<"-\n\n";}
    else{
        while(!thuStack.StackEmpty()){
            studentID=thuStack.Pop().getID();
            outputtxt<<studentID;
            outputtxt<<"\n";
        }
        outputtxt<<"\n";
    }
    outputtxt << "Friday:\n";
    if(friStack.StackEmpty()){outputtxt<<"-\n\n";}
    else{
        while(!friStack.StackEmpty()){
            studentID=friStack.Pop().getID();
            outputtxt<<studentID;
            outputtxt<<"\n";
        }
        outputtxt<<"\n";
    }
    outputtxt << "Unassigned:\n";
    if(WaitingRoom.QEmpty()){outputtxt<<"-\n\n";}
    else{
        while(!WaitingRoom.QEmpty()){
            studentID=WaitingRoom.Qdelete().getID();
            outputtxt<<studentID;
            outputtxt<<"\n";
            }
    }
    outputtxt.close();

    //END OF WRITING PART
    return 0;
   }
//END OF MAIN FUNCTION


void assignAllQueue(Queue<Student> &WaitingRoom,
                    Stack<Student> &wedStack,
                    Stack<Student> &thuStack,
                    Stack<Student> &friStack){
    int iterationNumber=WaitingRoom.QLenght();// To keep the information length of queue
    for(int i=0;i<iterationNumber;i++){
        Student iteratedStudent;
        iteratedStudent=WaitingRoom.Qdelete();// Delete the first item of waiting queue then assigning into a student object
        int availableDayNumber=iteratedStudent.availableDays(wedStack,thuStack,friStack);// Pulling how many day is eligible for current student
        if(availableDayNumber >= 1){// If it is bigger than 1, that means we should assign the student based on priority.
            char i=iteratedStudent.getPriorPreference(wedStack,thuStack,friStack);// Taking most priority section
            if (i == 'W'){
                wedStack.Push(iteratedStudent);//Pushing
            }
            else if (i == 'T'){
                thuStack.Push(iteratedStudent);//Pushing
            }
            else if (i == 'F'){
                friStack.Push(iteratedStudent);//Pushing
            }

        }
        else{
            //If available day number is not bigger than 1, that means it is zero
            //and it can not be assigned therefore we should insert it again waiting room
            //(After these assignments, waitingRoom will be our unassigned part)
            WaitingRoom.Qinsert(iteratedStudent);
        }
    }//END OF FOR LOOP
}// END OF FUNCTION


int findID(char output[100]){
    int iteration=0;
    char ID[100];
    while(output[iteration]!=','){//Since there is no restriction for ID's digit, I assumed there is comma right after last digit of ID
        ID[iteration]=output[iteration];
        iteration++;
    }
    ID[iteration]=NULL;
    return stoi(ID);// stoi function takes the string as a input returns it in integer form.
}
int assignStudent(Student &currentStudent,
                  Stack <Student> & wedStack,
                  Stack <Student> & thuStack,
                  Stack <Student> & friStack){// Student is assigned (1) //Student is not assigned (0)
    int availableDayNumber=currentStudent.availableDays(wedStack,thuStack,friStack);//Calculating eligible sections for given student
    if(availableDayNumber == 1)// If there is a just one eligible section, then push it.
    {
        char i=currentStudent.getPriorPreference(wedStack,thuStack,friStack);//Which section that will be pushed into
        if (i == 'W'){
            wedStack.Push(currentStudent);//Pushing
            return 1;// It is pushed therefore it return 1
        }
        else if (i == 'T')
        {
           thuStack.Push(currentStudent);//Pushing
            return 1;// It is pushed therefore it return 1
        }
        else if (i == 'F')
        {
           friStack.Push(currentStudent);//Pushing
            return 1;// It is pushed therefore it return 1
        }
    }
    else{
        return 0;// It is not pushed therefore it return 0
    }

}

int slotsMaker(char data[100]){
    char currentChar= data[0];// W, T, F is expected
    int iteration=2;// Since there is a comma right after W T F
    char capacity[10];// Capacity is assumed that it can have maximum of capacity with 10 digits
    while(true){
        if(data[iteration]==NULL){
            break;// If it is finished, then break the loop
        }
        capacity[iteration-2]=data[iteration];// Capacity variable is assigned
        iteration++;
    }
    capacity[iteration-1]='\0';// Putting end character for the capacity char list
    int cap = stoi(capacity);// stoi function takes the string as a input returns it in integer form.
    return cap;
}

void checkerForWaitingRoom(Queue<Student> &WaitingRoom,
                           Stack<Student> &wedStack,
                           Stack<Student> &thuStack,
                           Stack<Student> &friStack){
    int iterationNumber=WaitingRoom.QLenght();// To keep the information length of queue
    for(int i=0;i<iterationNumber;i++){
        Student iteratedStudent;
        iteratedStudent=WaitingRoom.Qdelete();// Delete the first item of waiting queue then assigning into a student object
        int availableDayNumber=iteratedStudent.availableDays(wedStack,thuStack,friStack);// Pulling how many day is eligible for current student
        if(availableDayNumber != 1){
            WaitingRoom.Qinsert(iteratedStudent);// If there is not one eligible section, then insert it into waitingRoom again
        }
        else{
            assignStudent(iteratedStudent,wedStack,thuStack,friStack);// If there is one eligible section, then assign it corresponding to the section via calling assignStudent function
        }
    }

}

// Definition for STUDENT METHODS

Student::Student(){}// Empty Constructor

Student::Student(int ID){
mID=ID;
}// CONSTRUCTOR WITH ID

void Student::addPreferences(char pref){// Adding preference letter into the preference list. IT IS ADDING ONE CHAR BY ONE CHAR.
    for(int i=0;i<3;i++){
        if(mPreferences[i]==NULL){
            mPreferences[i]=pref;
            break;//WHEN A CHAR ADDITION IS FINISHED , break the loop
        }
    }
}

int Student::availableDays(Stack<Student> &wedStack,
                           Stack<Student> &thuStack,
                           Stack<Student> &friStack) const{
    int days=0;// this variable holds how many eligible section there are
    for(int i=0;i<3;i++){//for loop that iterates on the preference list
        if(mPreferences[i]==NULL){
            continue;// if there is empty element go to next element
        }

        else if(mPreferences[i]=='W'){
            if(! wedStack.StackFull()){days++;}// if Wednesday stack is not full, then # of eligible section is going to be added by one
            else{}
        }

        else if(mPreferences[i]=='T'){
            if(! thuStack.StackFull()){days++;}// if Thursday stack is not full, then # of eligible section is going to be added by one
            else{}
        }

        else if(mPreferences[i]=='F'){
            if(! friStack.StackFull()){days++;}// if Friday stack is not full, then # of eligible section is going to be added by one
            else{}
        }

        else{continue;}// not expected input is going to be skipeed
    }// end of for loop

    return days; // return the value that holds # of eligible section
}

char Student::getPriorPreference(Stack<Student> &wedStack,
                                 Stack<Student> &thuStack,
                                Stack<Student> &friStack) const{// Method that returns the most preferred and eligible section for the current student
    for(int i=0;i<3;i++){
        switch(mPreferences[i]){
            case 'W':
                if (!wedStack.StackFull()){return mPreferences[i];}// If stack is not empty, return initial character
                break;
            case 'T':
                if (!thuStack.StackFull()){return mPreferences[i];}// If stack is not empty, return initial character
                break;
            case 'F':
                if (!friStack.StackFull()){return mPreferences[i];}// If stack is not empty, return initial character
                break;
            case NULL:// If it is NULL then jump to next iteration
                break;
            default:
                cerr <<"Day is not correct!"<<endl;
                exit(1);
        }// end of switch-case block
    }// end of for loop
    return mPreferences[0];
}// end of method


// STACK PART

template <class T>
Stack <T>::Stack(){
    top=-1;// Empty constructor with initializing top value as -1 so that it can be empty stack
}

template <class T>
Stack <T>::Stack(int limit){//Constructor with limit value (Capacity for a section)
    top=-1;// top as -1 since it is just initialized, it is empty
    mlimit=limit;//Setting limit (capacity) value
}


template <class T>
int Stack<T>::StackEmpty(void) const{
    return top==-1;// Stack is empty (1,true) or not (0,false)
}

template <class T>
int Stack<T>::StackFull(void) const{
    return top==(mlimit-1);// Stack is full (1,true) or not (0,false)
}

template <class T>
void Stack<T>::Push(const T & item){
    if (StackFull()){
        cerr<<"Stack overflow"<<endl;// If stack is full and we are trying to push an item, then it will exit the program by giving a message.
        exit(1);
    }
    top++;// Increment top
    stacklist[top]=item;// Inserting the item into the list
}

template <class T>
T Stack<T>::Pop(void){
    if (StackEmpty()){
        cerr<< "Stack empty"<<endl;// If stack is empty and we are trying to pop an item, then it will exit the program by giving a message.
        exit(1);
    }
    T temp=stacklist[top];// temp item= last item in the list, since it will return popped item
    top--;// decreasing top
    return temp;//returning popped item
}
// END OF STACK PART

// START OF QUEUE PART



template <class dataType>
Queue<dataType>::Queue(void):mFront(0),mRear(0),mCount(0){}//Constructor(Empty queue)


template <class dataType>
int Queue<dataType>::QLenght(void) const{
    return mCount;//Returning length of queue, i.e. the number of items in the queue
}

template <class dataType>
int Queue<dataType>::QEmpty(void) const{
    return mCount==0;// Queue is empty (1,true) or not (0,false)
}


template <class dataType>
void Queue<dataType>::Qinsert(const dataType & item){
    mCount++;//Increment the variable that holds # of items in the queue
    qlist[mRear]=item;// Adding item into the list
    mRear=(mRear+1)%maxQSize;// Since there is an addition on the list, mRear value should be increased.(To be circular array, it should be updated)
}

template <class dataType>
dataType Queue<dataType>::Qdelete(void){
    dataType temp;
    if (QEmpty()){
        cerr << "Deleting from an empty queue!"<<endl;// If queue is empty and we try to delete an item it will return an error message and exit the program
        exit(1);
    }
    temp = qlist[mFront];// temp item= last item in the list, since it will return popped item
    mCount--;// Decrement of the variable that holds # of items in the list
    mFront=(mFront+1)%maxQSize;//Since there is an subtraction on the list, mFront value should be decreased.(To be circular array, it should be updated)
    return temp;// returning newly deleted item
}
// END OF QUEUE PART
