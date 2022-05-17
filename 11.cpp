#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;

const int MAX=20;

class Student
{
    int rollno;
    char name[20],address[20];
    char div;
    
public:
    Student()
    {
        strcpy(name,"");
        strcpy(address,"");
        rollno=div=0;
    }
    Student(int rollno,char name[MAX],char div,char address[MAX])
    {
        strcpy(this->name,name);
        strcpy(this->address,address);
        this->rollno=rollno;
        
        this->div=div;
    }
    int getRollNo()
    {
        return rollno;
    }
    void displayRecord()
    {   
        
        cout<<endl<<setw(5)<<rollno<<setw(15)<<name<<setw(5)<<div<<setw(15)<<address;
    }
};

//==========File Operations ===========
class FileOperations
{
    fstream file;
public:
    FileOperations(char* filename)
    {
        file.open(filename,ios::in|ios::out|ios::ate);
    }

    void insertRecord(int rollno, char name[MAX], char div,char address[MAX])
    {
        Student s1(rollno,name,div,address);
        file.seekp(0,ios::end);
        file.write((char *)&s1,sizeof(Student));
        file.clear();
    }

    void displayAll()
    {
        Student s1;
        file.seekg(0,ios::beg);
        while(file.read((char *)&s1, sizeof(Student)))
        {
            s1.displayRecord();
        }
    file.clear();
    }

    void displayRecord(int rollNo)
    {
        Student s1;
        file.seekg(0,ios::beg);
        bool flag=false;
        while(file.read((char*)&s1,sizeof(Student)))
        {
            if(s1.getRollNo()==rollNo)
            {
                s1.displayRecord();
                flag=true;
                break;
            }
        }
        if(flag==false)
        {
            cout<<"\nRecord of "<<rollNo<<" is not present.\n";
        }
        file.clear();
    }

    void deleteRecord(int rollno)
    {
        ofstream outFile("new.txt");
        file.seekg(0,ios::beg);
        bool flag=false;
        Student s1;

        while(file.read((char *)&s1, sizeof(Student)))
        {
            if(s1.getRollNo()==rollno)
            {
                flag=true;
                continue;
            }
            outFile.write((char *)&s1, sizeof(Student));
        }
        if(!flag)
        {
            cout<<"\nRecord of "<<rollno<<" is not present.\n";
        }
        file.close();
        outFile.close();
        remove("student.txt");
        rename("new.txt","student.txt");
        file.open("student.txt",ios::in|ios::out|ios::ate);
    }

    ~FileOperations()
    {
        file.close();
        cout<<"\nFile Closed.";
    }
};

int main() {

    ofstream newFile("student.txt",ios::app);
    newFile.close();
    FileOperations file((char*)"student.txt");
    int rollNo,year,choice=0;
    char div;
    char name[MAX],address[MAX];

    while(choice!=5)
    {
        
        cout<<"\n*****Student Database*****\n";
        cout<<"1) Add New Record\n";
        cout<<"2) Display All Records\n";
        cout<<"3) Search by Roll Number\n";
        cout<<"4) Delete Record\n";
        cout<<"5) Exit\n";
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1: //New Record
                cout<<endl<<"Enter Roll Number: ";
                cin>>rollNo;
                cout<<"Enter name: ";
                cin>>name;
                cout<<"Enter Division: ";
                cin>>div;
                cout<<"Enter Address: ";
                cin>>address;
                file.insertRecord(rollNo,name,div,address);
                cout<<"\nRecord Inserted.\n";
                break;

            case 2:
                cout<<endl<<setw(5)<<"ROLL"<<setw(15)<<"NAME"<<setw(5)<<"DIV"<<setw(15)<<"ADDRESS";
                file.displayAll();
                cout<<endl;
                break;
            case 3:
                cout<<endl<<"Enter Roll Number";
                cin>>rollNo;
                file.displayRecord(rollNo);
                cout<<endl;
                break;
             
            case 4:
                cout<<endl<<"Enter Roll Number";
                cin>>rollNo;
                file.deleteRecord(rollNo);
                break;
            case 5:
                cout<<endl<<"***** You have exited *****\n";
                break;
            
            default:
                cout<<"Enter valid choice!\n";
                break;
        }

    }

    return 0;
}