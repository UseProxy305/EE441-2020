#include <iostream>
/// HOMEWORK 1 2021 DONE BY BERKAY IPEK 2304814
/// In this homework, names of variables are chosen according to camelCase.
using namespace std;
class Course; ///It is just for initiliaztion


/// Describing class Student
class Student{
    /// private members
    private:
        int mID;
        string mName;
        string mSurname;
        int * mQuiz_scores;
        int * mHw_scores;
        int mFinal_score;
    /// public methods
    public:
        Student(); /// Constructor without any parameters since Course class is calling for Students[10] without any giving parameters
        Student(int ID,string name, string surname, int (*quiz_scores), int  (*hw_scores),int &final_score); /// Constructor
        ///Set methods
        void setID(int ID);
        void setName(string name);
        void setSurname(string surname);
        void setQuizScores(int * quiz_scores);
        void setHwScores(int * hw_scores);
        void setFinalScore(int final_score);
        ///Get methods
        int getID() const;
        string getName() const;
        string getSurname() const;
        int * getQuizScores() const;
        int * getHWScores() const;
        int getFinalScore() const;
        ///Calculator for overall course score (Also default parameters are given)
        float overallCourseScore(float weight_q=30.0,float weight_hw=30.0,float weight_f=40.0) const;
};


/// Describing class Course (inherited)
class Course:public Student{
    private:
        Student mStudents[10]; ///Initializing a list of student class
        int mNum; /// This will hold the number of students in current
        int mWeightQ;
        int mWeightHW;
        int mWeightF;

    public:
        Course(); /// Constructor without any parameters just to initialize when it is necessary
        Course(int weightQ=30.0, int weightHW=30.0,int weightF=40.0); /// In constructor for course, mNum and mStudents parameters are not given since we will add it with additional methods (addNewStudents)
        ///Get Methods
        int getNum() const;
        int getWeightQ() const;
        int getWeightHW() const;
        int getWeightF() const;
        /// Method for adding new student with only 3 parameters in this method all scores is initiliazed with zeros
        void addNewStudent( int ID, string name,string surname);
        /// Updating weights
        void updateWeights(int newWeightQ,int newWeightHW,int newWeightF);
        /// Getting student info from given integer ID
        void getStudentInfo(int ID) const;
        /// Calculating average for quizzes homeworks final and overallcourse. Also it is should be noted that it will return a pointer. This pointer will point the value for quizzes curve. (p+1) will show HW and so on.
        float * calculateAverage() const;
        /// Updating student score. It will be called when a new student is trying to be added.
        void updateStudentScores(int ID, int *newQuiz,int * newHW,int FinalScore);
        /// These two methods will print who is above / below given parameter, threshold.
        void whoIsAbove(float threshold) const;
        void whoIsBelow(float threshold) const;
};


/// Creating main course class that I will operate on ( I gave default parameters as 30 30 40)
Course mainCourse(30,30,40);

/////////////////////////////////////
// Definition of User interface functions (Those will call methods on global course object
/////////////////////////////////////


/// adding new student for created course
void addNewStudent(int ID,string name,string surname){
    if (ID >0) mainCourse.addNewStudent(ID,name,surname); ///Checking if ID is smaller than zero or not. The message will be printed in change student score so that same error meessage does not occur two times.
}


/// show student info whose ID is given.
void showStudent(int searchingID){
    mainCourse.getStudentInfo(searchingID); /// There is no need for a checker
}


/// Updater for student scores
void changeStudentScores(int newID, int * newQuizzes,int * newHWs, int newFinalScores){

    /// CHECKER BLOCK

    bool checker=true; /// This boolean variable will hold if given parameters are proper or not. At the end, according to this variable, operation will be done.
    if (newID <=0) {cerr << "ID Can not be negative."<<endl;checker=false;} /// Checking if given ID <0 or not. Then it will print an error message.
    for(int i=0;i<4;i++){
        if(*(newQuizzes+i) < 0){
            cerr << (i+1)<<"th Quiz Score can not be negative." << endl;/// Checking if given Quiz score <0 or not. Then it will print an error message.
            checker=false;
        }
        else if(*(newQuizzes+i) > 100){
            cerr << (i+1)<<"th Quiz Score can't exceed 100." << endl;/// Checking if given Quiz score >100 or not. Then it will print an error message.
            checker=false;
        }
    }
    for(int i=0;i<3;i++){
        if(*(newHWs+i) < 0){
            cerr << (i+1)<<"th Homework Score can not be negative." << endl;/// Checking if given HW score <0 or not. Then it will print an error message.
            checker=false;
        }
        else if(*(newHWs+i) > 100){
            cerr << (i+1)<<"th Homework Score can't exceed 100." << endl;/// Checking if given HW score >100 or not. Then it will print an error message.
            checker=false;
        }
    }
    if (newFinalScores <0) {cerr << "Final score can not be negative."<<endl;checker=false;}/// Checking if given Final score <0 or not. Then it will print an error message.
    if (newFinalScores >100) {cerr << "Final score can't exceed 100."<<endl;checker=false;}/// Checking if given Final score >100 or not. Then it will print an error message.

    /// END FOR CHECKER BLOCK

    /// After checking conditions, if checker is not false, operation can be done.
    if(checker) mainCourse.updateStudentScores(newID,newQuizzes,newHWs,newFinalScores);
}

/// Updating weight of assignments in the course
void changeWeights(int newWeightQ,int newWeightHW,int newWeightF){

    /// CHECKER BLOCK
    bool checker=true;
    if (newWeightQ <=0) {cerr << "New weight of quiz can not be negative."<<endl;checker=false;}/// Checking if given quiz weight <0 or not. Then it will print an error message.
    if (newWeightHW <=0) {cerr << "New weight of HW can not be negative."<<endl;checker=false;}/// Checking if given HW weight <0 or not. Then it will print an error message.
    if (newWeightF <=0) {cerr << "New weight of final can not be negative."<<endl;checker=false;}/// Checking if given Final weight <0 or not. Then it will print an error message.
    else if (newWeightQ+newWeightHW+newWeightF != 100){cerr << "Total of weights must equal 100."<<endl;checker=false;}/// Checking if given the total for all weights are equal to 100 or not. Then it will print an error message.

    /// END FOR CHECKER BLOCK

    /// After checking conditions, if checker is not false, operation can be done.
    if(checker)mainCourse.updateWeights(newWeightQ,newWeightHW,newWeightF);
}

/// Calculating average for Class
void showAverage(){
    /// This pointer will be like an array that contains curve for quizzes homeworks final and overall course
    float  *p;
    p=mainCourse.calculateAverage();
    cout <<"Quizzes-Avg: "<<*p<<endl;
    cout <<"Homeworks-Avg: "<<*(p+1)<<endl;
    cout <<"Final-Avg: "<<*(p+2)<<endl;
    //    cout <<"General Avg: "<<*(p+3)<<endl; // If we want to print general average it can be uncommented
}
///Lists all students’ information above a certain overall score threshold
void showAbove(float threshold){

    /// CHECKER BLOCK
    bool checker=true;
    if (threshold <=0) {cerr << "Threshold can not be negative."<<endl;checker=false;}
    /// END FOR CHECKER BLOCK

    /// After checking conditions, if checker is not false, operation can be done.
    if(checker){
    /// pointer will hold the same array that is in showAverage function
    float  *p,generalCurve;
    p=mainCourse.calculateAverage();
    generalCurve=*(p+3);
    mainCourse.whoIsAbove(generalCurve);
    }
}

///Lists all students’ information below a certain overall score threshold
void showBelow(float threshold){
    bool checker=true;
    if (threshold <=0) {cerr << "Threshold can not be negative."<<endl;checker=false;}
    if(checker){
    float  *p,generalCurve;
    p=mainCourse.calculateAverage();
    generalCurve=*(p+3);
    mainCourse.whoIsBelow(generalCurve);
    }

}
///Main Function
int main(){
    /// This part is taken from a website to print just 2 decimals after the decimal point
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2); /// By giving 2 as a parameter, it will print 2 digit only after the decimal point


    /// This part is for home page
    cout<<"EE441 Classroom Interface"<<endl;cout<<"Choose your option:"<<endl;
    cout<<"1)Add a student"<<endl;
    cout<<"2)Search a student by ID"<<endl;
    cout<<"3)Change a student's score"<<endl;
    cout<<"4)Update weights"<<endl;
    cout<<"5)Show class average"<<endl;
    cout<<"6)Show students with overall score above threshold"<<endl;
    cout<<"7)Show students with overall score below threshold"<<endl;
    cout<<"8)Exit"<<endl;

    char option; /// This variable will hold the value which operation will be done. Since I am using a char. If you give more than one character to user interface program will crush.
    do{
        cout<<"Choose your option: ";
        cin>>option;

        /// This switch/case block will determine the option
        switch(option){
            /// Add a new student
            case '1':{
                cout <<"Enter student's ID, name, surname and scores (quizzes, homeworks,final)"<<endl;
                int ID,finalScore;
                string name,surname;
                int quizFirst,quizSecond,quizThird,quizFourth;
                int hwFirst,hwSecond,hwThird;
                cin>>ID>>name>>surname>>quizFirst>>quizSecond>>quizThird>>quizFourth>>hwFirst>>hwSecond>>hwThird>>finalScore;
                /// This part is important. Arrays should be static so that when this line proccesing it will occupy a new space in the static memory.
                int *quiz= new int[4]; /// These arrays will firstly occupy a list of length 4*sizeof(int). If it werent for new command, it wont work properly. Since we are assigning a pointer to quiz and hw students.
                int *hw= new int[3]; /// These arrays will firstly occupy a list of length 3*sizeof(int). If it werent for new command, it wont work properly. Since we are assigning a pointer to quiz and hw students.
                quiz[0]=quizFirst;
                quiz[1]=quizSecond;
                quiz[2]=quizThird;
                quiz[3]=quizFourth;
                hw[0]=hwFirst;
                hw[1]=hwSecond;
                hw[2]=hwThird;

                /// Calling necessary methods
                addNewStudent(ID,name,surname);
                changeStudentScores(ID,quiz,hw,finalScore);
                break; /// IF it weren't for break command, it will go into another case section
            }
            /// Getting student info given ID
            case '2':{
                cout <<"Enter your student ID"<<endl;
                int searchingID;
                cin >> searchingID;
                /// Calling necessary method
                showStudent(searchingID);
                break;
            }
            /// Updating varaibles
            case '3':{
                cout <<"Enter your student ID and new scores (quizzes, homeworks, final):"<<endl;
                int ID,finalScore,quizFirst,quizSecond,quizThird,quizFourth,hwFirst,hwSecond,hwThird;
                cin>>ID>>quizFirst>>quizSecond>>quizThird>>quizFourth>>hwFirst>>hwSecond>>hwThird>>finalScore;
                int *quiz= new int[4]; /// These arrays will firstly occupy a list of length 4*sizeof(int). If it werent for new command, it wont work properly. Since we are assigning a pointer to quiz and hw students.
                int *hw= new int[3]; /// These arrays will firstly occupy a list of length 3*sizeof(int). If it werent for new command, it wont work properly. Since we are assigning a pointer to quiz and hw students.
                quiz[0]=quizFirst;
                quiz[1]=quizSecond;
                quiz[2]=quizThird;
                quiz[3]=quizFourth;
                hw[0]=hwFirst;
                hw[1]=hwSecond;
                hw[2]=hwThird;

                ///Calling necessary methods
                changeStudentScores(ID,quiz,hw,finalScore);
                break;
            }
            /// Updating wieghts
            case '4':{
                cout<<"Enter updated weight values (quizzes, homeworks, final):"<<endl;
                int newWeightQ,newWeightHW,newWeightF;
                cin >> newWeightQ >> newWeightHW >> newWeightF;

                ///Calling necessary methods
                changeWeights(newWeightQ,newWeightHW,newWeightF);
                break;
            }
            /// Printing averages for all assignments
            case '5':{
                /// Calling necessary methods
                showAverage();
                break;
            }
            /// Listing all students that has upper given threshold
            case '6':{
                float threshold;
                cout<<"Enter threshold: ";
                cin>>threshold;

                ///Calling necessary methods
                showAbove(threshold);
                break;
            }
            /// Listing all students that has lower given threshold
            case '7':{
                float threshold;
                cout<<"Enter threshold: ";
                cin>>threshold;
                ///Calling necessary methods
                showBelow(threshold);
                break;
            }
            /// Closing program
            case '8':{
                cout << "Program closed"<<endl;
                return 0;
                break;
            }
            default:
                cout<<"Invalid Option: Please try again."<<endl; /// When an unknown parameter is given

        }

    }while(option!='8');
}

/////////////////////////////////////
/// Definition of Constructor and methods for class "Student"
/////////////////////////////////////



/// Constructor for Student class
Student::Student(int ID,string name, string surname, int (* quiz_scores), int  (* hw_scores),int &final_score){
mID=ID;
mName=name;
mSurname=surname;
mQuiz_scores=quiz_scores;
mHw_scores=hw_scores;
mFinal_score=final_score;
}
/// Empty Constructor for student class
Student::Student(){
}
/// NOTE: I DIDN'T CHECK WHETHER PARAMETERS ARE PROPER OR NOT SINCE COURSE METHODS WILL DO IT.
/// IT IS NOT POSSIBLE TO SEND INVALID PARAMETER TO THOSE METHODS

/// setting ID method
void Student::setID(int ID){
mID=ID;

}

/// setting name method
void Student::setName(string name){
mName=name;
}

/// setting surname method
void Student::setSurname(string surname){
mSurname=surname;
}

/// setting quiz scores method (Since it is a pointer I used "this->" keyword)
void Student::setQuizScores(int * quiz_scores){
this->mQuiz_scores=quiz_scores;
}

/// setting homework scores method (Since it is a pointer I used "this->" keyword)
void Student::setHwScores(int * hw_scores){
this->mHw_scores=hw_scores;
}

/// setting final score method
void Student::setFinalScore(int final_score){
mFinal_score=final_score;
}

/// GET METHODS BLOCKS
int Student::getID() const{
    return mID;
}
string Student::getName() const{
    return mName;
}
string Student::getSurname() const{
    return mSurname;
}
int * Student::getQuizScores() const{
    return this->mQuiz_scores;
}
int * Student::getHWScores() const{
    return this->mHw_scores;
}
int Student::getFinalScore() const{
    return mFinal_score;
}
///END OF GET METHODS BLOCK


/// Calculator for overall method
float Student::overallCourseScore(float weight_q,float weight_hw,float weight_f) const{
    float average_hw;
    float average_q;
    /// These variables hold the value for total score that a student got
    float total_hw=0.0;
    float total_q=0.0;
    for (int j=0; j< 3;j++){
        total_hw+=*(mHw_scores+j);
    }
    for (int i=0; i< 4;i++){
        total_q+=*(mQuiz_scores+i);
    }
    /// Calculating averages
    average_hw=total_hw/3;
    average_q=total_q/4;
    return ((average_hw*weight_hw)+(average_q*weight_q)+(mFinal_score*weight_f))/100;
}
/////////////////////////////////////
/// Definition of Constructor and methods for class "Course"
/////////////////////////////////////


/// Empty constructor for Class Course
Course::Course(){
}

/// Constructor for Class Course
Course::Course(int weightQ, int weightHW,int weightF){
this->mNum=0;
this->mWeightQ=weightQ;
this->mWeightHW=weightHW;
this->mWeightF=weightF;
}

/// Getter methods Block
int Course::getNum() const{
    return mNum;
}
int Course::getWeightF() const{
    return mWeightF;
}
int Course::getWeightQ() const{
    return mWeightQ;
}
int Course::getWeightHW() const{
    return mWeightHW;
}
/// End for Getter methods Block

///Adding new student
void Course::addNewStudent( int ID, string name,string surname){
    /// these parameters are default parameters
    int Quizzes[4]={0,0,0,0};
    int HWs[3]={0,0,0};
    int fin=0;
    Student newStudent(ID,name,surname,Quizzes,HWs,fin); /// Instance for student that will be added
    mStudents[mNum] = newStudent; /// Adding a new student to the list
    mNum+=1; /// Incrementing the number of students in class
}
/// Updating weights
void Course::updateWeights(int newWeightQ,int newWeightHW,int newWeightF){
    mWeightQ= newWeightQ;
    mWeightHW= newWeightHW;
    mWeightF= newWeightF;
}
/// Get student info by given ID
void Course::getStudentInfo(int ID) const{
    /// This boolean variable is a checker. True means there is a student with given ID
    bool FindStudent=false;

    /// For loop that will iterate on the student list
    for(int i = 0; i <(mNum);i++){
            /// If statement for ID matching
        if (mStudents[i].getID() == ID){
            /// Printing information
            cout << mStudents[i].getID() <<" "<< mStudents[i].getName()<<" "<<mStudents[i].getSurname()<<" ";
            for(int j=0;j<4;j++){
                    cout <<*(mStudents[i].getQuizScores()+j)<<" ";
            }
            for(int j=0;j<3;j++){
                    cout <<*(mStudents[i].getHWScores()+j)<<" ";
            }
            cout<<mStudents[i].getFinalScore()<<endl;
            FindStudent=true; /// It should turn into true since we found student given ID
            break;
        }
    }
    if(!FindStudent) cout<<"Invalid ID"<<endl; /// If there is no student it will print a message
}

/// Calculating all averages
float * Course::calculateAverage() const{
    float totalHW=0.0,totalQ=0.0,totalF=0.0; /// These variables hold the total scores for the students for all assigments
    static float scoresCurve[4];
    for (int j=0; j<mNum;j++){
        for (int i=0;i<4;i++){
            totalQ+=*(mStudents[j].getQuizScores()+i);
        }
        for (int i=0;i<3;i++){
            totalHW+=*(mStudents[j].getHWScores()+i);
        }
        totalF+=mStudents[j].getFinalScore();
    }
    scoresCurve[0]=(totalQ)/(4*mNum); /// Since there are four Quizzes
    scoresCurve[1]=(totalHW)/(3*mNum); /// Since there are three homeworks
    scoresCurve[2]=(totalF)/(mNum); /// since there is just one final exam
    scoresCurve[3]=((scoresCurve[0]*mWeightQ)+(scoresCurve[1]*mWeightHW)+(scoresCurve[2]*mWeightF))/100; /// Calculating general average (multiplying their weights)
    return scoresCurve;
}
/// Updating student scores
void Course::updateStudentScores(int ID,int * newQuiz_scores, int * newHW_scores, int newFinal_score){
    /// Firstly it is checking there is a given student or not.
    /// we are not able to use getstudent method because it will print info for student
    /// but procedure is the same
    bool FindStudent=false;
    int index;
    for(int i = 0; i <(mNum);i++){
        if (mStudents[i].getID() == ID){
            FindStudent=true;
            index=i;
            break;
        }
    }
    if(!FindStudent) cout<<"Invalid ID"<<endl; /// If there is no student it will print a message
    else{
            /// Updating scores
        mStudents[index].setFinalScore(newFinal_score);
        mStudents[index].setHwScores(newHW_scores);
        mStudents[index].setQuizScores(newQuiz_scores);

        }
}
/// Listing desired students
void Course::whoIsAbove(float threshold) const{
    /// This part is explained in main part
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    float averageOfStudent;
    /// For loop will iterate through all students
    for (int i=0;i<mNum;i++){
        averageOfStudent=mStudents[i].overallCourseScore(mWeightQ,mWeightHW,mWeightF);/// Calculating average for iterated current student
        if(averageOfStudent>threshold){/// Checker if block
            cout << mStudents[i].getID() <<" "<< mStudents[i].getName()<<" "<<mStudents[i].getSurname()<<" Avg:"<<averageOfStudent<<endl; /// Printing his/her info
        }
    }
}
/// Listing desired students
void Course::whoIsBelow(float threshold) const{
    /// This part is explained in main part
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    float averageOfStudent;
    /// For loop will iterate through all students
    for (int i=0;i<mNum;i++){
        averageOfStudent=mStudents[i].overallCourseScore(mWeightQ,mWeightHW,mWeightF);/// Calculating average for iterated current student
        if(averageOfStudent<threshold){/// Checker if block
            cout << mStudents[i].getID() <<" "<< mStudents[i].getName()<<" "<<mStudents[i].getSurname()<<" Avg:"<<averageOfStudent<<endl;/// Printing his/her info
        }
    }
}
