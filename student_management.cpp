#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

void Enroll(void);
void show_all(void); 
void search(void);
void delete_data(void);

class student
{
    int roll,age;
    char name[20];
    public:
        void set(string n,int r,int a)
            { strcpy(name,n.c_str()); roll=r; age=a; }
        void show()
            { cout<<roll<<"\t"<<name<<"\t"<<age<<endl; }
		int roll_no()
			{ return roll; }
};

void Enroll()
{
    ofstream fout("student_management",ios::app | ios::binary);
    int n,r,a;
    string na;
    cout<<"Enter no of student:";
    cin>>n;
    student s[n];
    for(int i=0;i<n;i++){
        cout<<"\nName:";    cin>>na;
        cout<<"roll no.:";  cin>>r;
        cout<<"age:";       cin>>a;
        s[i].set(na,r,a);
        fout.write((char *)&s[i], sizeof(s[i]));
    }
    cout<<"\nStudents are successfully enrolled\n";
    fout.close();
}

void show_all()
{
    ifstream fin("student_management",ios::in | ios::binary);
    student s;
    cout<<"ROLL\tNAME\tAGE\n";
    if(!fin)
        cout<<"cannot open file\n";
    else{
    fin.read((char *)&s, sizeof(s));
    while(!fin.eof()){
        s.show();
        fin.read((char *)&s, sizeof(s));
    }
    fin.close();
    }
}

void search()
{
	ifstream fin("student_management",ios::in | ios::binary);
	student s;
	int roll,c=0;
	cout<<"Enter roll no. of student you want to search: ";
	cin>>roll;
    cout<<"\n";
    fin.read((char *)&s, sizeof(s));
	while(!fin.eof()){
		if(s.roll_no() == roll){
			s.show();
			c++;
		}
		fin.read((char *)&s, sizeof(s));
	}
	if(c==0)
		cout<<"student not found";
}

void update()
{
    int r;
    bool c=true;
    student s;
    fstream file;
    file.open("student_management",ios::binary | ios::in | ios::out | ios::ate);
    file.seekg(0);
    cout<<"Enter roll of student you want to update: ";
    cin>>r;
    file.read((char *)&s, sizeof(s));
    while(!file.eof()){
        if(s.roll_no()==r){
            c=false;
            cout<<"data of student before updation:\n";
            s.show();
            cout<<"Enter new name, rollno. and age:\n";
            string n;
            int *pr=new int;
            int *pa=new int;
            cin>>n;
            cin>>*pr>>*pa;
            s.set(n,*pr,*pa);
            file.seekp(file.tellp()-sizeof(student));
            file.write((char *)&s, sizeof(s));
            break;
        }
        else   { file.read((char *)&s, sizeof(s)); }
    }
    if(c) 
        cout<<"Student not found!!";
    file.close();
}

void delete_data()
{
    int r,c=0;
    student s;
    ifstream fin; 
    ofstream fout;
    fin.open("student_management",ios::in | ios::binary);
    fout.open("temp",ios::out | ios::binary);
    cout<<"Enter roll no you want to delete:";
    cin>>r;
    fin.read((char *)&s, sizeof(s));
    while(!fin.eof()){
        if(s.roll_no()==r){
            s.show();
            cout<<"Do you really want to delete data?\n   Press '1' to delete\n   Press '0' to exit\n";
            cin>>c;
            if(!c){
                remove("temp");   
                fin.close();    fout.close();
                cout<<"Data will not delete.";
                exit(0);
            }
        }
        else
            fout.write((char *)&s,sizeof(s));
        fin.read((char *)&s, sizeof(s));
    }
    if(c)
        cout<<"Data is successfully deleted\n";
    fin.close();    fout.close();
    remove("student_management");
    rename("temp","student_management");

}

int main()
{
    system("cls");
    cout<<"! Welcome to student management system !\n\n";
    string pass;
    cout<<"Enter password for login: ";
    cin>>pass;
    if(pass=="stud@123")
    {
    system("cls");
    int c;
    cout<<"you logged in successfully......\n\n";
    cout<<"1. Enroll new stu.\n2. Read all data\n3. Search\n4. Update\n5. Delete\n6. exit\n";
    cout<<"Enter choice:";
    cin>>c;
    switch(c)
    {
        case 1:
            Enroll();
            break;
        case 2:
            show_all();
            break;
		case 3:
			search();
			break;
        case 4:
            update();
            break;
        case 5:
            delete_data();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"Invalid";
    }
    }
    else
        cout<<"!! Incorrect password !!";
    cout<<"\npress any key to end program!";
    getch();
    return 0;
}