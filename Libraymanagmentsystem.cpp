#include<iostream> 
#include<iomanip>   
#include<conio.h>   /////////////////////////////////////
#include<cstring>   //////////   HEADER FILES  //////////
#include<string>    /////////////////////////////////////
#include<fstream>   
#include<sstream>
#include<cstdlib> 


using namespace std;

// Initializing all arrays of Books and Members
void initializeBooks(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS);
void initializeMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS);


//function for data persisitent
bool saveBooks(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS);
bool loadBooks(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS);
bool saveMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS);
bool loadMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS);


////////  BOOK MANAGMENT   ////////
bool addbook(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS, string bookname, string bookid, string authorname, string category, string year);
int searchbyID(string idlist[], int MAX_BOOKS, string bookid);
bool updatebook(string namelist[], string idlist[], string authorlist[], string categorylist[] , string pubYlist[] ,int MAX_BOOKS, string oldbookid, string bookname, string bookid,string category, string authorname, string year);
bool deletebook(string namelist[], string idlist[], string authorlist[],string categorylist[], string pubYlist[], int MAX_BOOKS, string bookid);
void displaybooks(string namelist[],string idlist[], string authorlist[],string categorylist[], string pubYlist[], int MAX_BOOKS);


////////  MEMBER MANAGMENT ////////
bool addmember(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS, string memberName,string memberCode, string memberAge,string phoneNo,string CNIC);
bool removeMember(string memberNamelist[], string memberCodelist[], string agelist[], string phoneNoList[], string Cniclist[], int MAX_MEMBERS, string memberCode);
int searchMember(string memberCodelist[], int MAX_MEMBERS, string memberCode);
bool updateMember(string memberNamelist[], string memberCodelist[], string agelist[], string phoneNoList[] , string Cniclist[] ,int MAX_MEMBERS, string oldmembercode, string memberName, string memberCode,string memberAge, string phoneNo, string CNIC);
void viewMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS);


/////  ISSUEING BOOKS /////
bool issuebook(string namelist[],string memberNamelist[],string IssuedBooksList[],string IssuedBooksMembersList[], int MAX_BOOKS, int MAX_MEMBERS, string bookname, string memberName);
bool returnbook(string namelist[],string memberNamelist[], int MAX_BOOKS,string IssuedBooksList[],string IssuedBooksMembersList[], string memberName, string bookname);
bool viewissuedbooks(string IssuedBooksList[],string IssuedBooksMembersList[], int MAX_BOOKS);

/////  VALIDATION FUNCTIONS FOR BOOK  /////
bool isValidBookName(string bookname);
bool isValidAuthorname(string authorname);
bool isValidcategory(string category);
bool isValidISBN(string bookid);
bool isValidyear(string year);
bool validateAllDataofBooks(string bookname, string authorname, string category, string bookid, string year);


/////  VALIDATION FOR MEMBERS /////
bool isValidCNIC(string CNIC);
bool isValidnumber(string phoneNo);
bool isValidMembername(string memberName);
bool isValidcode(string memberCode);
bool isValidage(string memberAge);
bool validateAllDataofmember(string CNIC, string phoneNo, string memberName, string memberCode, string memberAge);


//////////////////////
//     FUNCTIONS   ///
//////////////////////

// BOOKS MANAGMENT FUNCTIONS

//to initialize all arrays of books
void initializeBooks(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS)
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        namelist[i]=" ";
        idlist[i]=" ";
        authorlist[i]=" "; 
        categorylist[i]=" ";
        pubYlist[i]=" ";
    }
}

//to inilize all arrays of members
void initializeMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS)
{
    for (int i = 0; i < MAX_MEMBERS; i++)
    {
      memberNamelist[i]=" ";
      memberCodelist[i]=" ";
      agelist[i]=" ";
      phoneNoList[i]=" ";
      Cniclist[i]=" ";
    }
}

// To save books for file handling
bool saveBooks(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS)
{
    // This variable for read data from file
    ofstream myfile;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and 
	not remove previous content of file */
    myfile.open("Books.txt");
    //This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        for (int i = 0; i < MAX_BOOKS; i++)
        {
            if (namelist[i] != "" && idlist[i] != "" && authorlist[i] != "" && categorylist[i] != "" && pubYlist[i] != "")
            {
                //These lines will write all array data to the file and make a comma separated file
                myfile << namelist[i] << ",";
                myfile << idlist[i] << ",";
                myfile << authorlist[i] << ",";
                myfile << categorylist[i] << ",";
                myfile << pubYlist[i] << endl;
            }
        }

        myfile.close();
        return true;
    }
    else
    {
        //If there is error while opening file this function will return false
        return false;
    }
}


//Function to load Books in arrays
bool loadBooks(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS)
{
    int i = 0;
    ifstream getBooks("Books.txt");
    if (!getBooks.is_open())
    {
        //cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string bookname, bookid, authorname;
        string category, year;
        string line;
        while (!getBooks.eof() && i < MAX_BOOKS)
        {
            getline(getBooks, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, bookname, ',');
            namelist[i] = bookname;
            getline(ss, bookid, ',');
            idlist[i] = bookid;
            getline(ss, authorname, ',');
            authorlist[i] = authorname;
            getline(ss, category, ',');
            categorylist[i] = category;
            getline(ss, year, ',');
            pubYlist[i] = year;
            i++;
        }

        getBooks.close();
        return true;
    }
}

//search a book by its ID(ISBN)
int searchbyID(string idlist[], int MAX_BOOKS, string bookid)
{
    int index = -1;
    for (int i = 0; i < MAX_BOOKS; i++)
    {
      
        if (idlist[i] == bookid)
        {
            index = i;
            break;
        }
    }
    return index;
}

//// add books ////
bool addbook(string namelist[],string idlist[],string authorlist[], string categorylist[],string pubYlist[], int MAX_BOOKS, string bookname, string bookid, string authorname, string category, string year)
{
    bool flag = false;
    int i = searchbyID(idlist,MAX_BOOKS," ");
    if (i != -1)
    {
        namelist[i]=bookname;
        idlist[i]=bookid;
        authorlist[i]=authorname;
        categorylist[i]=category;
        pubYlist[i]=year;
        flag = true;
    }
    return flag;
}

////update a book/////
bool updatebook(string namelist[], string idlist[], string authorlist[], string categorylist[] , string pubYlist[] ,int MAX_BOOKS, string oldbookid, string bookname, string bookid,string category, string authorname, string year)
{

    bool flag = false;
    int updateIndex = searchbyID(idlist,MAX_BOOKS,oldbookid);
    cout<<"Upate Book Information "<<updateIndex<<endl;
    if (updateIndex != -1)
    {
        namelist[updateIndex]=bookname;
        idlist[updateIndex]=bookid;
        authorlist[updateIndex]=authorname;
        categorylist[updateIndex]=category;
        pubYlist[updateIndex]=year;
        flag = true;
    }
    return flag;
}

/////delete a book/////
bool deletebook(string namelist[], string idlist[], string authorlist[],string categorylist[], string pubYlist[], int MAX_BOOKS, string bookid)
{
    bool flag = false;
    int i = searchbyID(idlist, MAX_BOOKS, bookid);
    if (i != -1)
    {
        namelist[i]=" ";
        idlist[i]=" ";
        authorlist[i]=" ";
        categorylist[i]=" ";
        pubYlist[i]=" ";
        flag = true;
    }
    return flag;
}

/////display all books//////
void displaybooks(string namelist[],string idlist[], string authorlist[],string categorylist[], string pubYlist[], int MAX_BOOKS)
{
    cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
	cout<<setw(10)<<"\"Book ID\""
        <<setw(30)<<"\"Book Name\""
        <<setw(30)<<"\"Author Name\""
        <<setw(30)<<"\"Category\""
        <<setw(30)<<"\"Year of Publication\""<<endl;
	cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
    for(int i=0;i<MAX_BOOKS;i++)
		{
	      cout<<setw(10)<<idlist[i]
              <<setw(40)<<namelist[i]
              <<setw(25)<<authorlist[i]
              <<setw(25)<<categorylist[i]
              <<setw(20)<<pubYlist[i]<<endl;
         cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
		}
}

// MEMBER MANAGMENT FUNCTIONS

//// This function will save all members in file ////
bool saveMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS)
{
    // This variable for read data from file
    ofstream save;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and 
	not remove previous content of file */
    save.open("Members.txt");
    //This function will check if the file open then write data from file
    if (save.is_open())
    {
        for (int i = 0; i < MAX_MEMBERS; i++)
        {
            if (memberNamelist[i] != "" && memberCodelist[i] != "" && agelist[i] != "" && phoneNoList[i] != "" && Cniclist[i] != "")
            {
                //These lines will write all array data to the file and make a comma separated file
                save << memberNamelist[i] << ",";
                save << memberCodelist[i] << ",";
                save << agelist[i] << ",";
                save << phoneNoList[i] << ",";
                save << Cniclist[i] << endl;
            }
        }

        save.close();
        return true;
    }
    else
    {
        //If there is error while opening file this function will return false
        return false;
    }
}

// This will load all members in arrays
bool loadMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS)
{
    int i = 0;
    ifstream getMembers("Members.txt");
    if (!getMembers.is_open())
    {
        //cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string memberName,memberCode, memberAge;
        string phoneNo, CNIC;
        string line;
        while (!getMembers.eof() && i < MAX_MEMBERS)
        {
            getline(getMembers, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, memberName, ',');
            memberNamelist[i] = memberName;
            getline(ss, memberCode, ',');
            memberCodelist[i] = memberCode;
            getline(ss, memberAge, ',');
            agelist[i] = memberAge;
            getline(ss, phoneNo, ',');
            phoneNoList[i] = phoneNo;
            getline(ss, CNIC, ',');
            Cniclist[i] = CNIC;
            i++;
        }

        getMembers.close();
        return true;
    }
}


//// search a member by member code  ////
int searchMember(string memberCodelist[], int MAX_MEMBERS, string memberCode)
{
    int index = -1;
    for (int i = 0; i < MAX_MEMBERS; i++)
    {
      
        if (memberCodelist[i] == memberCode)
        {
            index = i;
            break;
        }
    }
    return index;
}

///// add a member ////
bool addmember(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS, string memberName,string memberCode, string memberAge,string phoneNo,string CNIC)
{
    bool flag = false;
    int i = searchMember(memberCodelist,MAX_MEMBERS," ");
    if (i != -1)
    {
        memberNamelist[i]=memberName;
        memberCodelist[i]=memberCode;
        agelist[i]=memberAge;
        phoneNoList[i]=phoneNo;
        Cniclist[i]=CNIC;
        flag = true;
    }
    return flag;
}

///// remove member /////
bool removeMember(string memberNamelist[], string memberCodelist[], string agelist[], string phoneNoList[], string Cniclist[], int MAX_MEMBERS, string memberCode)
{
    bool flag = false;
    int i = searchMember(memberCodelist,MAX_MEMBERS,memberCode);
    if (i != -1)
    {
        memberNamelist[i]=" ";
        memberCodelist[i]=" ";
        agelist[i]=" ";
        phoneNoList[i]=" ";
        Cniclist[i]=" ";
        flag = true;
    }
    return flag;
}

//// update a member ////
bool updateMember(string memberNamelist[], string memberCodelist[], string agelist[], string phoneNoList[] , string Cniclist[] ,int MAX_MEMBERS, string oldmembercode, string memberName, string memberCode,string memberAge, string phoneNo, string CNIC)
{

    bool flag = false;
    int updateIndex =searchMember(memberCodelist,MAX_MEMBERS,memberCode);
    cout<<"Update member information"<<updateIndex<<endl;
    if (updateIndex != -1)
    {
        memberNamelist[updateIndex]= memberName;
        memberCodelist[updateIndex]= memberCode;
        agelist[updateIndex]=memberAge;
        phoneNoList[updateIndex]= phoneNo;
        Cniclist[updateIndex]=CNIC;
        flag = true;
    }
    return flag;
}

//// view list of members ////
void viewMembers(string memberNamelist[], string memberCodelist[], string agelist[],string phoneNoList[], string Cniclist[], int MAX_MEMBERS)
{
    cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
	cout<<setw(10)<<"\"Member Name\""
        <<setw(30)<<"\"Member Code\""
        <<setw(30)<<"\"Member Age\""
        <<setw(30)<<"\"Member Phone no.\""
        <<setw(30)<<"\"Member CNIC\""<<endl;
	cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
    for(int i=0;i<MAX_MEMBERS;i++)
		{
	      cout<<setw(10)<<memberNamelist[i]
              <<setw(25)<<memberCodelist[i]
              <<setw(30)<<agelist[i]
              <<setw(35)<<phoneNoList[i]
              <<setw(35)<<Cniclist[i]<<endl;
         cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
		}
}

// ISSUE BOOK FUNCTIONS

/// to issue book to member ///
bool issuebook(string namelist[],string memberNamelist[],string IssuedBooksList[],string IssuedBooksMembersList[], int MAX_BOOKS, int MAX_MEMBERS, string bookname, string memberName)
{
    bool flag=false;
    for(int i=0;i<MAX_BOOKS; i++)
    {
        if(namelist[i] == bookname)
        {
            for(int j=0; j< MAX_MEMBERS; j++)
            {
                if(memberNamelist[j] == memberName)
                {
                    IssuedBooksList[j] = bookname;
                    IssuedBooksMembersList[j] = memberName;
                    flag=true;
                    break;
                }
            }
        }
    }
    return flag;
}


//// to return/ unissue a book from member ////
bool returnbook(string namelist[],string memberNamelist[], int MAX_BOOKS,string IssuedBooksList[],string IssuedBooksMembersList[], string memberName, string bookname)
{
    bool flag = false;
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if ((namelist[i] == bookname) && (memberNamelist[i] == memberName))
        {
            IssuedBooksList[i]=" ";
            IssuedBooksMembersList[i]=" ";
            flag = true;
            break;
        }
    }
    return flag;
}

// View List of issued books
bool viewissuedbooks(string IssuedBooksList[],string IssuedBooksMembersList[], int MAX_BOOKS)
{
    cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<endl;
    cout<< left;
    cout<< setw(30) << "Issued Books"
        << setw(30) << "Member Name"<<endl;
    cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<endl;
    for(int i=0; i< MAX_BOOKS; i++)
    {
        if((IssuedBooksList[i] != " ") && (IssuedBooksMembersList[i] != " "))
        {
            cout<< setw(30) << IssuedBooksList[i]
                << setw(30) << IssuedBooksMembersList[i]<<endl;
             cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<endl;
        }
    }
}

//////   VALIDATIONS FOR BOOKS  //////

/////  validation for book name   /////
bool isValidBookName(string bookname)
{
    bool valid_bname=true;
    int n=bookname.length();
    if(n<=50)
    {
         for(int i=0;i<n;i++)
         {
             if(!((bookname[i]>='A' && bookname[i]<='Z'|| (bookname[i]>='a' && bookname[i]<='z')||(bookname[i]==' '))))
             {
                valid_bname=false;
                break;
             }
             else
             {
                valid_bname=true;
             }
         }
    }
return valid_bname;
}

/////  validation for author name   /////
bool isValidAuthorname(string authorname)
{
    bool valid_aname=true;
    int s=authorname.length();
    if(s<=50)
    {
         for(int i=0;i<s;i++)
         {
             if(!((authorname[i]>='A' && authorname[i]<='Z'|| (authorname[i]>='a' && authorname[i]<='z')||(authorname[i]==' '))))
             {
                valid_aname=false;
                break;
             }
             else
             {
                valid_aname=true;
             }
         }
    }
return valid_aname;
}

/////   validation for category of book   /////
bool isValidcategory(string category)
{
    bool valid_category=true;
    int t=category.length();
    if(t<=50)
    {
         for(int i=0;i<t;i++)
         {
             if(!((category[i]>='A' && category[i]<='Z'|| (category[i]>='a' && category[i]<='z')||(category[i]==' '))))
             {
                valid_category=false;
                break;
             }
             else
             {
                valid_category=true;
             }
         }
    }
return valid_category;
}

/////  validation for ISBN no. for book ID which should be of 13 digits  /////
bool isValidISBN(string bookid)
{
    bool valid_isbn=true;
    int a=bookid.length();
    if(a!=13)
    {
        valid_isbn=false;
    }
        for(int i=0; i<13; i++)
        {
         if(!(bookid[i]>='0' && bookid[i]<='9'))
    {
        valid_isbn=false;
        break;
    }
    else
    {
        valid_isbn=true;
    }
    }
return valid_isbn;
}

/////  validation for publication year  ////
bool isValidyear(string year)
{
    bool valid_year=true;
    int e=year.length();
    if(e!=4)
    {
        valid_year=false;
    }
        for(int i=0; i<4; i++)
        {
         if(!(year[i]>='0' && year[i]<='9'))
    {
        valid_year=false;
        break;
    }
    else
    {
        valid_year=true;
    }
    }
return valid_year;
}

///////  VALIDATIONS FOR MEMBERS  ////////

/////  validation for CNIC of member  /////
bool isValidCNIC(string CNIC)
{
    bool valid_cnic=true;
    int a=CNIC.length();
    if(a!=13)
    {
        valid_cnic=false;
    }
        for(int i=0; i<13; i++)
        {
         if(!(CNIC[i]>='0' && CNIC[i]<='9'))
    {
        valid_cnic=false;
        break;
    }
    else
    {
        valid_cnic=true;
    }
    }
return valid_cnic;
}

/////  validation for phone number of member  /////
bool isValidnumber(string phoneNo)
{
    bool valid_number=true;
    int x=phoneNo.length();
    if(x!=11)
    {
        valid_number=false;
    }
        for(int i=0; i<11; i++)
        {
         if(!(phoneNo[i]>='0' && phoneNo[i]<='9'))
    {
        valid_number=false;
        break;
    }
    else
    {
        valid_number=true;
    }
    }
return valid_number;
}

/////  validation for member name  /////
bool isValidMembername(string memberName)
{
    bool valid_name=true;
    int b=memberName.length();
    if(b<=40)
    {
         for(int i=0;i<b;i++)
         {
             if(!((memberName[i]>='A' && memberName[i]<='Z'|| (memberName[i]>='a' && memberName[i]<='z')||(memberName[i]==' '))))
             {
                valid_name=false;
                break;
             }
             else
             {
                valid_name=true;
             }
         }
    }
return valid_name;
}

//////  validation for member code(4 digits)  /////
bool isValidcode(string memberCode)
{
    bool valid_code=true;
    int y=memberCode.length();
    if(y!=4)
    {
        valid_code=false;
    }
        for(int i=0; i<4; i++)
        {
         if(!(memberCode[i]>='0' && memberCode[i]<='9'))
    {
        valid_code=false;
        break;
    }
    else
    {
        valid_code=true;
    }
    }
return valid_code;
}

/////  validation for member age  /////
bool isValidage(string memberAge)
{
    bool valid_age=true;
    int z=memberAge.length();
    if(z!=2)
    {
        valid_age=false;
    }
        for(int i=0; i<2; i++)
        {
         if(!(memberAge[i]>='0' && memberAge[i]<='9'))
    {
        valid_age=false;
        break;
    }
    else
    {
        valid_age=true;
    }
    }
return valid_age;
}

// Validate all data of Members
bool validateAllDataofmember(string CNIC, string phoneNo, string memberName, string memberCode, string memberAge)
{
    if (!( isValidCNIC(CNIC) && isValidnumber(phoneNo) && isValidMembername(memberName) && isValidcode(memberCode) && isValidage(memberAge)))
    {
        return false;
    }
    return true;
}

//Validate all Data of Books
bool validateAllDataofBooks(string bookname, string authorname, string category, string bookid, string year)
{
     if (!(isValidBookName(bookname) && isValidAuthorname(authorname) && isValidcategory(category) && isValidISBN(bookid) && isValidyear(year)))
    {
        return false;
    }
    return true;
} 

//////////////////////////
////   MAIN FUNCTION  ////
//////////////////////////

int main()               
{
    system("cls");

    ////////// ALL VARIABLES ////////

    // Books variables
    string bookname;
    string bookid;
    string authorname;
    string category;
    string year;
    string oldbookid;

    // Members Variables
    string memberName;
    string memberCode;
    string memberAge;
    string phoneNo;
    string CNIC;
    string oldmembercode;

    /////////// SIZE of arrays /////////
    int MAX_BOOKS;
    cout<<"Enter the number of books:"<<endl;
    cin>>MAX_BOOKS;

    int MAX_MEMBERS;
    cout<<"Enter the number of members:"<<endl;
    cin>>MAX_MEMBERS;
    system("cls");
    
    ///////// ALL ARRAYS /////////

    // Books arrays
    string namelist[MAX_BOOKS];
    string idlist[MAX_BOOKS];
    string authorlist[MAX_BOOKS]; 
    string categorylist[MAX_BOOKS];
    string pubYlist[MAX_BOOKS]; 

    // Member arrays
    string memberNamelist[MAX_MEMBERS];
    string memberCodelist[MAX_MEMBERS];
    string agelist[MAX_MEMBERS];
    string phoneNoList[MAX_MEMBERS];
    string Cniclist[MAX_MEMBERS];
    string IssuedBooksList[MAX_BOOKS];
    string IssuedBooksMembersList[MAX_MEMBERS];

    // input variable
    char input;
    int optionB; 
    int optionM;
    int optionI;

    // Initialize all arrays
    initializeBooks(namelist,idlist,authorlist,categorylist,pubYlist,MAX_BOOKS);
    initializeMembers(memberNamelist,memberCodelist,agelist,phoneNoList,Cniclist,MAX_MEMBERS);

    //This function will load the books
    loadBooks(namelist, idlist, authorlist, categorylist, pubYlist, MAX_BOOKS);

    //This function will load all members
    loadMembers(memberNamelist, memberCodelist, agelist, phoneNoList, Cniclist,MAX_MEMBERS);

    //For Username
    cout<<"****Welcome to LIBRARY MANAGMENT system****"<<endl;
    cout<<"Firstly enter your Username(any) and Password to start the system"<<endl;
    cout<<"  "<<endl;
    string userName;
    cout<<"Enter Username:"<<endl;
    cin.ignore();
    getline(cin, userName);

    // For Password
    cout<<"  "<<endl;
    int password = 54321;
    int pass;
    cout<<"Enter Your 5 digit Password:"<<endl;
    cin>>pass;
    system("cls");

    if(pass == password)
    {

   system("cls");

 cout<<"******************************************************************************"<<endl;
 cout<<"                         LIBRARY MANAGEMENT SYSTEM                            "<<endl;
 cout<<"******************************************************************************"<<endl;
 cout<<"         "<<endl;
 cout<<"Press any key to move to main menu..."<<endl;
 getch();           //it will handle any key after above line
 system("cls");     //clear the screen above

 char input;
 do{
    cout<<setw(30)<<"---------------"<<endl
        <<setw(30)<<" | MAIN MENU | "<<endl
        <<setw(30)<<"---------------"<<endl
        <<setw(30)<<" "<<endl
        <<"Please choose an option from the menu:"<<endl
        <<"            "<<endl
        <<"(B) BOOK MANAGMENT" << endl
        <<"(M) MEMBER MANAGMENT" << endl
        <<"(I) ISSUING BOOKS" << endl
        <<"(S) SEE YOUR PASSWORD" << endl
        <<"(E) EXIT PROGRAM" << endl  
        <<"        "<<endl
        <<"Enter Your desired Option:"<<endl;
    cin>>input;
    cout<<"Press any Key to continue..."<<endl;
	getch();
	system("CLS");

    switch(input)
    {
        // For Book Managment //
        case 'b':
        case 'B':
        int optionB;
        cout<<"     BOOK MANAGMENT IN A LIBRARY    "<<endl
            <<"     "<<endl
            <<"1. Add a Book"<<endl
            <<"2. Search a Book"<<endl
            <<"3. Delete a Book"<<endl
            <<"4. Update a Book"<<endl
            <<"5. Display all Books"<<endl
		    <<"Choose an option number:"<<endl;
        cin>>optionB;
        getch();
        system("CLS");


        // Here you will call add a book function
        if(optionB==1)
        {
         cout << "Enter the Name of book:";
         cin.ignore();
         getline(cin, bookname);
         cout << "Enter the ID of Book (ISBN)"<<endl
              << "13 digits ISBN No.:"<<endl;
         cin>>bookid;
         cout << "Enter the Name of author:";
         cin.ignore();
         getline(cin, authorname);
         cout << "Enter the Category of book:";
         cin.ignore();
         getline(cin, category);
         cout << "Enter the Publication Year of book:";
         cin>>year;

         if(validateAllDataofBooks(bookname,authorname,category,bookid,year))
           {
             //Call addbook function
             if (addbook(namelist,idlist,authorlist,categorylist,pubYlist,MAX_BOOKS,bookname,bookid,authorname,category,year))
             {
                cout << "Book has been added Successfully" << endl;
             }
             else
             {
                cout << "Sorry could not add book" << endl;
             }
           }
            else
            {
                //If any validity is false it will not add the book
                cout << "Invalid details" << endl;
            }
         cout<<"Press any key to select another choice..."<<endl;
         getch();
         system("cls");
        }


        //Here you will call search books 
        else if(optionB==2)
        {
          cout<<"Enter ID of book (ISBN)";
          cin>> bookid;
            if(isValidISBN(bookid))
               {
                 //Call search function
                   if (searchbyID(idlist,MAX_BOOKS,bookid))
                    {
                        cout << "Book has been found Successfully" << endl;
                    }
                  else
                    {
                        cout << "Sorry could not found book" << endl;
                    }
                }
                 else
                {
                   //If any validity is false it will not add the book
                    cout << "Invalid details" << endl;
                }
            cout<<"Press any key to select another choice..."<<endl;
            getch();
            system("cls");
        }


        //Here you will delete a book
        else if(optionB==3)
        {
           cout << "Enter Book ID (ISBN)" << endl;
                cin >> bookid;
                //Validate the course Code
                if (isValidISBN(bookid))
                {
                    //call function to delete the book 
                    if (deletebook(namelist,idlist,authorlist,categorylist,pubYlist,MAX_BOOKS,bookid))
                    {
                        cout << "Book Successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Book found " << endl;
                    }
                }
                else
                {
                    //if book id is invalid then this message will show
                    cout << "Invalid Book ID" << endl;
                }
           cout<<"Press any key to select another choice..."<<endl;
           getch();
           system("cls");
        }


          //Here you will update a book information
        else if(optionB==4)
        {
          cout<< "Enter the old book ID (ISBN)" << endl;
                cin >> oldbookid;

                //check validity of book code(ISBN)
                if (isValidISBN(bookid))
                {
                    //Find the index
                  cout << "Enter the Name of book:";
                  cin.ignore();
                  getline(cin, bookname);
                  cout << "Enter the ID of Book (ISBN):";
                  cin>>bookid;
                  cout << "Enter the Name of author:";
                  cin.ignore();
                  getline(cin, authorname);
                  cout << "Enter the Category of book:";
                  cin.ignore();
                  getline(cin, category);
                  cout << "Enter the Publication Year of book:";
                  cin>>year;

                    //Check validity of all details entered by user
                    if (validateAllDataofBooks(bookname,authorname,category,bookid,year))
                    {

                        if (updatebook(namelist,idlist,authorlist,categorylist ,pubYlist ,MAX_BOOKS, oldbookid,bookname,bookid,category,authorname,year))
                        {
                            cout << "Book successfully updated" << endl;
                        }
                        else
                        {
                            cout << "No book found" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid data" << endl;
                    }
                }
                else
                {
                    //here we will show message of not valid data
                    cout << "Invalid Data" << endl;
                }
          cout<<"Press any key to move to main menu..."<<endl;
          getch();
          system("cls");
        }


          //Display all books
        else if(optionB==5)
        {
           cout<<"Display all books:"<<endl;
           displaybooks(namelist,idlist,authorlist,categorylist,pubYlist,MAX_BOOKS);

          cout<<"Press any key to select another choice..."<<endl;
          getch();
          system("cls");
        }
        break;

        // MEMBER MANAGMENT //

        case 'M':
        case 'm':
        int optionM;
        cout<<" MEMBER MANAGMENT "<<endl
            <<"   "<<endl
            <<"1. Add Member"<<endl
            <<"2. Search Member"<<endl
            <<"3. Delete Member"<<endl
            <<"4. Update Member"<<endl
            <<"5. View Members"<<endl
            <<"Select an option"<<endl;
            cin>>optionM;
            getch();
            system("CLS");


        //Here you will add a new member
         if(optionM==1)
        {
           cout << "Enter the Name of Member:";
           cin.ignore();
           getline(cin, memberName);
           cout << "Enter the 4 digit code of Member:";
           cin>>memberCode;
           cout << "Enter the age of member:";
           cin>>memberAge;
           cout << "Enter the phone no. of member (11 digits):";
           cin >> phoneNo;
           cout << "Enter the CNIC of member (13 digits):";
           cin>>CNIC;
               
                //Check validity of all inputs of member
                if (validateAllDataofmember(CNIC,phoneNo,memberName,memberCode,memberAge))
                {
                    //Call addmember function
                    if (addmember(memberNamelist,memberCodelist,agelist,phoneNoList,Cniclist,MAX_MEMBERS,memberName,memberCode,memberAge,phoneNo,CNIC))
                    {
                        cout << "Member Successfully added" << endl;
                    }
                    else
                    {
                        cout << "Sorry No space to add new member" << endl;
                    }
                }
                else
                {
                    //If any validity is false it will not add the course
                    cout << "Invalid details" << endl;
                }

          cout<<"Press any key to select another choice..."<<endl;
          getch();
          system("cls");
        }


          //Here you will call remove a member
        else if(optionM==2)
        {
         cout << "Enter member code (4 digits):" << endl;
                cin >> memberCode;
                //Validate the course Code
                if (isValidcode(memberCode))
                {
                    //call function to delete the book detail which has same book code as user enter
                    if (removeMember(memberNamelist,memberCodelist,agelist,phoneNoList,Cniclist,MAX_MEMBERS,memberCode))
                    {
                        cout << "Member Successfully removed" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Member found " << endl;
                    }
                }
                else
                {
                    //if course code is invalid then this message will show
                    cout << "Invalid Member Code" << endl;
                }

                
             cout<<"Press any key to select another choice..."<<endl;
             getch();
             system("cls");
        }


        // here you will call search a member function by its code
        else if(optionM==3)
        {
          cout<<"Enter member code (4 digit) to search :"<<endl;
          cin>> memberCode;
             //Validate the member Code
                if (isValidcode(memberCode))
                {
                    //call function to search the member
                    if (searchMember(memberCodelist,MAX_MEMBERS,memberCode))
                    {
                        cout << "Member has been found!!!" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Member found " << endl;
                    }
                }
                else
                {
                    //if course code is invalid then this message will show
                    cout << "Invalid Member Code" << endl;
                }

           cout<<"Press any key to select another choice..."<<endl;
           getch();
           system("cls");
        }


         //Here you will call update a member information
        else if(optionM==4)
        {
          cout<< "Enter the old member code (4 digit)" << endl;
                cin >> oldmembercode;

                //check validity of member code
                if (isValidcode(memberCode))
                {
                    //Find the index
                 cout << "Enter the Name of Member:";
                 cin.ignore();
                 getline(cin, memberName);
                 cout << "Enter the 4 digit code of Member:";
                 cin>>memberCode;
                 cout << "Enter the age of member:";
                 cin>>memberAge;
                 cout << "Enter the phone no. of member (11 digits):";
                 cin >> phoneNo;
                 cout << "Enter the CNIC of member (13 digits):";
                 cin>>CNIC;
                 

                    //Check validity of all details entered by user
                    if (validateAllDataofmember(CNIC,phoneNo,memberName,memberCode,memberAge))
                    {
                        if (updateMember(memberNamelist,memberCodelist,agelist,phoneNoList,Cniclist,MAX_MEMBERS,oldmembercode,memberName,memberCode,memberAge,phoneNo,CNIC))
                        {
                            cout << "Member successfully updated" << endl;
                        }
                        else
                        {
                            cout << "No member found" << endl;
                        }
                    }
                    else
                    {
                       //here we will show message of not valid data
                        cout << "Invalid Data" << endl;
                    }
                }
                  else
                {
                    //here we will show message of not valid data
                    cout << "Invalid Data" << endl;
                }
                
          cout<<"Press any key to select another choice..."<<endl;
          getch();
          system("cls");
        }



          //Here you will show List of All Members
        else if(optionM==5)
        {
            cout<<"View of all members:"<<endl;
            viewMembers(memberNamelist,memberCodelist,agelist,phoneNoList,Cniclist,MAX_MEMBERS);

            cout<<"Press any key to select another choice..."<<endl;
            getch();
            system("cls");
        }
        break;


        // ISSUING A BOOK //
        case 'I':
        case 'i':
        int optionI;
        cout<<" ISSUING BOOKS TO MEMBERS "<<endl
            <<"   "<<endl
            <<"1. Issue a Book"<<endl
            <<"2. Un Issue a Book"<<endl
            <<"3. View List of book issued by members"<<endl
            <<"Select an option"<<endl;
            cin>>optionI;
            getch();
            system("CLS");


        // here you will call issue a book function
        if(optionI==1)
        {
            cout<<"Enter book name"<<endl;
            cin >> bookname;
            cout<<"Enter member name to issue book"<<endl;
            cin.ignore();
            getline(cin,memberName);
            if(isValidBookName(bookname) && isValidMembername(memberName))
            {
                if(issuebook(namelist,memberNamelist,IssuedBooksList,IssuedBooksMembersList,MAX_BOOKS,MAX_MEMBERS,bookname,memberName))
                    {
                        cout<<" Book has been issued to member!!!"<<endl;
                    }
                    else
                    {
                        cout<<"No book found"<<endl;
                    }
            }
            else
            {
                cout<<"Invalid details"<<endl; 
            }
            cout<<"Press any key to move to main menu..."<<endl;
            getch();
            system("cls");
        }


        /// here you will return or un issue a book from member ///
        else if(optionI==2)
        {
           cout<<"Enter book name"<<endl;
           cin >> bookname;
           cout<<"Enter member name to issue book"<<endl;
           cin.ignore();
           getline(cin,memberName);
             if(isValidBookName(bookname) && isValidMembername(memberName))
                {
                    if(returnbook(namelist,memberNamelist,MAX_BOOKS,IssuedBooksList,IssuedBooksMembersList,memberName,bookname))
                        {
                            cout<<"Book has been un issued/ returned from member!!!"<<endl;
                        }
                     else
                        {
                        cout<<"No book found"<<endl;
                        }
                }
                else
                {
                     cout<<"Invalid details"<<endl;
                }
                cout<<"Press any key to move to main menu..."<<endl;
                getch();
                system("cls");
        }

             //To view list of issued books
             else if(optionI == 3)
            {
                cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
                cout<<"                                       |ISSUING DETAILS|                                  "<<endl;
                cout<<"___"<<"________________"<<"__________"<<"__________"<<"__________"<<"__________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<"___________"<<endl;
                viewissuedbooks(IssuedBooksList,IssuedBooksMembersList,MAX_BOOKS);
                cout<<"Press any key to move to main menu..."<<endl;
                getch();
                system("cls");
            }
        break;


        // to see your password
        case 's':
        case 'S':
            cout<<"Your current password is:"<<endl
            <<"54321"<<endl;
        
          cout<<"Press any key to move to main menu..."<<endl;
          getch();
          system("cls");
        break;


      
           // For Closing Program
            case 'E':
            case 'e':
                if ((saveBooks(namelist,idlist,authorlist,categorylist,pubYlist,MAX_BOOKS) && saveMembers(memberNamelist,memberCodelist,agelist,phoneNoList,Cniclist,MAX_MEMBERS)))
                {
                    cout << "All Books Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                cout << "Program closed ";
                cout<<"Press any key to move to main menu..."<<endl;
                getch();
                system("cls");
           break;

    } //end switch
} //end do

 while(input=='b'||'B'||'M'||'m'||'I'||'i'||'e'||'E'||'s'||'S');
}//end if
else
{
   cout<<"Your Password is incorrect"<<endl;
}
return 0;
}