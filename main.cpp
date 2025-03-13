
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <limits>

using namespace std;

const int MAX_MENU_SIZE = 4;// max main menu size
const int MIN_MENU_SIZE = 1;// bottom number of the max size used for input validation

class InputValidation// holds all the input validation functions used in other classes and functions
{
    private:
        InputValidation(){} // used to prevent overwiritng of the constructor

    public:
        InputValidation(const InputValidation&) = delete; // delete copy constructor

        static InputValidation& get()  // used to make this a singlton and output data
        {
            static InputValidation instance;
            return instance;
        }

        int YesNoInputValidation ()//handles yes and no input validation
        {
            string full_string;
           // cin.ignore();

            do
            {
            getline(cin,full_string);

            if (full_string == "y" || full_string =="Y"|| full_string =="Yes"|| full_string =="yes")
                return -2;

            else if (full_string == "n" || full_string =="N"|| full_string =="No"|| full_string =="no")
                return -1;

            else 
                cout<<"     Invalide input. Please type y for yes and n for no: ";

            } while (true);
            
            

        }

        string FullStringInputValidation ()// handles full string input
        {
            string full_string;
            getline(cin,full_string);

            return full_string;
        }

        int menuInputValidation (int min, int max)// input validation for menu selection
        {
            bool good_data = false;
            int check;
           // cin.ignore();
                
            do
            {
                cin >> check;
                
                good_data = cin.good();

                good_data = good_data && (check >= min) && (check <= max);

                if ( !cin.good() )
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

                if ( !good_data)
                {
                    cout<< "        Invalid Input: Enter an integer between ";
                    cout <<min <<"-"<< max<<". Please try again: ";
                }

            } while ( !good_data );

            cin.ignore();
            
            return check; 
        }

        string StringInputValidation ()// handles input validation for string inputs
        {
            bool good_data = false, good_string= true;
            string stringTemp, stringTempRebuild;
            //cin.ignore();
            do
            {
                // prompt user for value.
                getline(cin,stringTemp);
                good_data = cin.good();
                
                for (char character : stringTemp) 
                {
                    if (isalpha(character) ) //|| character == " "
                    {
                        good_string = true;
                        character = tolower(character);
                    }
                    else if ( character == ' ')
                    {
                        good_string = true;
                        //character = tolower(character);
                    }
                    else 
                    {
                        good_string = false;
                        stringTempRebuild = "";
                        break; // No need to check further if one non-alpha character is found
                    }
                    stringTempRebuild= stringTempRebuild+character;// makes lowercase string
                }
                
                good_data = good_data*good_string;

                if ( !cin.good() )
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

                if ( !good_data)
                {
                    cout<< "        ERROR: Invalid Input, please only enter characters (no special characters or numbers).";
                    cout <<". Please try again: ";

                }
                

            } while ( !good_data );

            return stringTempRebuild; //returns lowercase string

        }

        string ISBMInputValidation ()// handles input validation for ISBM making sure 13 numberic digit is enterd
        {
            bool good_data = false;
            int  size, max =13;
            long long int check;
                
            do
            {
                // prompt user for value.
                cin >> check;
                good_data = cin.good();

                size = to_string(check).size();

                good_data = good_data && (size == max);

                if ( !cin.good() )
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

                if ( !good_data)
                {
                    cout<< "        Invalid Input: Enter a 13 digit ISBM number. Please try again: ";
                }

            } while ( !good_data );

            cin.ignore();
            
            return to_string(check); 
        }

        int IntInputValidation (int min, int max)// input validation for integers that have to fit between a min and max value
        {
            bool good_data = false;
            int  size;
            long long int check;
     
            do
            {
                cin >> check;
                good_data = cin.good();

                size = to_string(check).size();

                good_data = good_data && (check <= max)&& (check >= min);

                if ( !cin.good() )
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

                if ( !good_data)
                {

                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

            } while ( !good_data );

            cin.ignore();
            
            return check; 
        }

        int IntInputValidation (int min)// overloaded function that provided input validation for integets that have a min value
        {
            bool good_data = false;
            int  size;
            long long int check;
                
            do
            {

                //cin.ignore();
                cin >> check;
                good_data = cin.good();

                size = to_string(check).size();

                good_data = good_data && (check >= min);

                if ( !cin.good() )
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

                if ( !good_data)
                {
                    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // make sure to have #include <limits>
                }

            } while ( !good_data );

            cin.ignore();
            
            return check; 
        }

};

class BookData // Class that manages all book items. Menu titles, functions and data management
{
    private: 
        struct Booklist // list to hold all book data
        { 
            string title;
            string author;
            string isbn;
        
            // initialize the struct
            Booklist(const string& t, const string& a, const string& i)
                : title(t), author(a), isbn(i) {}
        };

        
        vector<Booklist> library_book;// makes libary a vector with the booklist struct

        BookData(){}; // used to prevents constructro overide

        static Booklist instance; // used to make this a singlton

    public:
        BookData(const BookData&) = delete; // delete copy constructor

        static BookData& get() // 
        {
            static BookData instance;
            return instance;
        }

        string getTitle() {return "Books";} // provided the main menu title
        vector<string> getSubTitle() {return {"Add a Book", "Edit a Book", "Remove a Book"};}// provides classes functions for user to select



        int showBook () // show list of inputed books
        {
            for (int i=0; i <library_book.size(); i++ )
                {
                    cout<<i+1<<") Book Count"<<endl;
                    cout<<     "             Book Title  :"<<library_book[i].title<<endl;
                    cout<<     "             Book Author :"<<library_book[i].author<<endl;
                    cout<<     "             ISMN        :"<<library_book[i].isbn<<endl;
                }
            return library_book.size();
        }

        int findBook (string title, string isbn)// finds book entered in
        {
            string title_test,isbn_test;

            if (library_book.size()==0)
                return -2; // there is no list of books

            for (int i=0; i <library_book.size(); i++ )
            {
                title_test = library_book[i].title;
                isbn_test = library_book[i].isbn;

                if (title_test == title && isbn_test == isbn)
                {
                    return i;
                }
            }
            return -1 ;//did not find the book
        }

        int findBook (string isbn)// overloaded function that can find the book with only the ISBN 
        {
            string isbn_test;

            if (library_book.size()==0)
            return -2; // there is no list of books

            for (int i=0; i <library_book.size(); i++ )
            {

                isbn_test = library_book[i].isbn;

                if (isbn_test == isbn)
                {
                    return i;
                }
            }
            return -1;
        }

        string findBookTitle (string isbn)// finds a book title given isbn
        {
            string isbn_test,title;



            for (int i=0; i <library_book.size(); i++ )
            {

                isbn_test = library_book[i].isbn;
                title = library_book[i].title;

                if (isbn_test == isbn)
                {
                    return title;
                }
            }

            return "Title Not Found";
        }

        void setBook () // adds book title, author and isbm to list
        {
            string title_input,author_input,isbm_input;

            cout<<endl<<"Libary Interface: Add a Book"<<endl;

            cout<<"     Enter a Title: ";
            title_input = InputValidation::get().FullStringInputValidation ();

            cout<<"     Enter a Author: ";
            author_input = InputValidation::get().StringInputValidation();

            cout<<"     Enter the ISBM: ";
            isbm_input=InputValidation::get().ISBMInputValidation();

            library_book.push_back(Booklist(title_input, author_input, isbm_input));
            cout<<"Book Added Succesfully"<<endl<<endl;
        }

        void editBook () // Edits books that are alredy entered in by the user
        {
            string title_search, author_temp, isbn_search;
            int index_found;
            do 
            {
                cout<<endl<<"Libary Interface: Edit Book"<<endl;
                cout<<"     Enter Book Title: ";
                title_search = InputValidation::get().FullStringInputValidation ();
                cout<<"     Enter Book ISBN: ";
                isbn_search = InputValidation::get().ISBMInputValidation();
                
                index_found= findBook (title_search, isbn_search);

                if (index_found == -2)
                {
                    cout<<"     No books have been entered into the system. Please add books first."<<endl;
                    return;
                }
                else if (index_found == -1)
                {
                    cout<<"     Book not found. Try again(y/n)?: ";
                    index_found = InputValidation::get().YesNoInputValidation ();

                    if (index_found==-1)
                        return;
                }
            }while (index_found<0);

            cout<<"Book Found!"<<endl;

            cout<<endl<<"Libary Interface: Edit Book"<<endl;

            cout<<"     Please Enter New Title Name: ";
            title_search= InputValidation::get().FullStringInputValidation ();

            cout<<"     Please Enter New Author: ";
            author_temp= InputValidation::get().StringInputValidation();

            cout<<"     Please Enter New ISBN: ";
            isbn_search=InputValidation::get().ISBMInputValidation();

            library_book[index_found].title = title_search;
            library_book[index_found].author = author_temp;
            library_book[index_found].isbn = isbn_search;
            
            cout<<"Book updated succesfuly!"<< endl;
        }

        void removeBook () // Removes books entered in by the user
        {
            string title_search, isbn_search;
            int index_found;

            do
            {
                cout<<endl<<"Libary Interface: Remove a Book"<<endl;
                cout<<"     Enter Book Title: ";
                title_search = InputValidation::get().FullStringInputValidation ();
                cout<<"     Enter Book ISBN: ";
                isbn_search = InputValidation::get().ISBMInputValidation();

                index_found= findBook (title_search, isbn_search);

                index_found= findBook (title_search, isbn_search);
                if (index_found == -2)
                {
                    cout<<"     No books have been entered into the system. Please add books first."<<endl;
                    return;
                }
                else if (index_found == -1)
                {
                    cout<<"     Book not found. Try again(y/n)?: ";
                    index_found = InputValidation::get().YesNoInputValidation ();

                    if (index_found==-1)
                        return;
                }
            }while (index_found<0);

            library_book.erase(library_book.begin() + index_found);

            cout<<"Book Removed Succesfully"<< endl;
        }
};

class UserData // Class that manages all user items. Menu titles, functions and data management
{
    private: 
    
        struct Userlist // book struct to store book data
        { 
            string name;
            int id;
            // initialize the struct
            Userlist(const string& n, const int& i)
                : name(n), id(i){}
        };

        
        vector<Userlist>libary_user;// makes libary a vector with the booklist struct

        UserData(){}; // prevent overwritting the constructor

        static Userlist instance; // makes this a singlton

    public:
    UserData(const UserData&) = delete; // delete copy constructor

    string getTitle() {return "User";}// provided the main menu title name for this class
    vector<string> getSubTitle() {return {"Add a User", "Edit a User", "Remove a User"};}// provides the functions that this class can do to the user

        static UserData& get() //used to make this a singlton 
        {
            static UserData instance;
            return instance;
        }

        int  user_id_generator ()// generates a unique user ID
        {
            static int s_id{ 0 }; // static local variable
            return ++s_id;
        }

        int showUser () // shows list of users already entered
        {
            for (int i=0; i <libary_user.size(); i++ )
            {
                cout<<i+1<<") User Count"<<endl;
                cout<<     "                  User Name :"<<libary_user[i].name<<endl;
                cout<<     "                  User ID   :"<<libary_user[i].id<<endl;
            }
            return libary_user.size();
        }

        int findUser (string name, int id)// finds users already entered in
        {
            string name_test;
            int id_test;

            if (libary_user.size()==0)
                return -2; // there is no list of books

            for (int i=0; i <libary_user.size(); i++ )
            {
                name_test = libary_user[i].name;
                id_test = libary_user[i].id;

                if (name_test == name && id_test == id)
                {
                    return i;
                }
            }
            return -1;
        }

        string findUser (int id)// overloaded functions that can find user only using id number and returns a string
        {
            int id_test;

            if (libary_user.size()==0)
                return "-2"; // there is no list of books
                
            for (int i=0; i <libary_user.size(); i++ )
            {
                id_test = libary_user[i].id;

                if (id_test == id)
                {
                    return libary_user[i].name;
                }
            }
            return "-1";
        }

        void setUser () // sets user name and id
        {
            string user_name;
            int user_id;
            cout<<endl<<"Libary Interface: Add User"<<endl;
            cout<<"     Enter Full Name: ";
            user_name= InputValidation::get().StringInputValidation();
            user_id = user_id_generator ();
            libary_user.push_back(Userlist(user_name, user_id));
            cout<<"Added Succesfully"<<endl;
            cout<<"                 User Name: "<<user_name<<endl;
            cout<<"                 User Id  : "<<user_id<<endl;
        }

        void editUser () // edits user name
        {
            string name_search;
            int id_search, index_found;
            do
            {
                cout<<endl<<"Libary Interface: Edit User"<<endl;
                cout<<"     Enter User Name: ";
                name_search= InputValidation::get().StringInputValidation();
                cout<<"     Enter User ID: ";
                id_search= InputValidation::get().IntInputValidation (1);

                index_found= findUser (name_search, id_search);

                if (index_found == -2)
                {
                    cout<<"        No Users have been entered into the system. Please add a user first."<<endl;
                    return;
                }
                else if (index_found == -1)
                {
                    cout<<"        User not found. Try again(y/n)?: ";
                    index_found = InputValidation::get().YesNoInputValidation ();

                    if (index_found==-1)
                        return;
                }
            } while (index_found < 0);

            cout<<"Account Found!"<<endl;

            cout<<endl<<"Libary Interface: Edit User"<<endl;
            cout<<"     Please Enter New Name: ";
            name_search= InputValidation::get().StringInputValidation();
            libary_user[index_found].name = name_search;
            
            cout<<"User account updated succesfuly!"<< endl;
        }

        void removeUser () // removes user name and id
        {
            string name_search;
            int id_search, index_found;
            do
            {
                cout<<endl<<"Libary Interface: Removed User"<<endl;
                cout<<"     Enter User Name: ";
                name_search= InputValidation::get().StringInputValidation();
                cout<<"     Enter User ID: ";
                id_search= InputValidation::get().IntInputValidation (1);

                index_found= findUser (name_search, id_search);

                if (index_found == -2)
                {
                    cout<<"        No Users have been entered into the system. Please add a user first."<<endl;
                    return;
                }
                else if (index_found == -1)
                {
                    cout<<"         User not found. Try again(y/n)?: ";
                    index_found = InputValidation::get().YesNoInputValidation ();

                    if (index_found==-1)
                        return;
                }
            }while(index_found<0);

            
            libary_user.erase(libary_user.begin() + index_found);

            cout<<"User Removed Succesfully"<< endl;
        }
};

class LibaryData // Class that manages all libary items. Menu titles, functions and data management
{
    private: 
       
            struct Libarylist  // book struct to store book data
            { 
                string isbm;
                int user_id;
                // initialize the struct
                Libarylist(const string& n, const int& i)
                    : isbm(n), user_id(i){}
            };

            
            vector<Libarylist>libary_libary;// makes libary a vector with the booklist struct

            LibaryData(){}; // prevent overwriting constructor

            static Libarylist instance;// use to make this a singlton

    public:
        LibaryData(const LibaryData&) = delete; // delete copy constructor

        string getTitle() {return "Libary Transaction";} // provides main menu title for this class for the user to select
        vector<string> getSubTitle() {return {"Check out a Book", "Return a Book", "List all Books", "List all Users","List all Checked Out Books"};}// provides the titles of each of the functions that this class can do

            static LibaryData& get() // use to make this a singlton
            {
                static LibaryData instance;
                return instance;
            }

            int findCheckedOut (string isbm, int user_id)// used to find checked out book and user that check out the book
            {
                string isbn_test;
                int id_test;

                if (libary_libary.size()==0)
                return -2; // there is no list of books

                for (int i=0; i <libary_libary.size(); i++ )
                {
                    isbn_test = libary_libary[i].isbm;
                    id_test = libary_libary[i].user_id;

                    if (isbn_test == isbm && id_test == user_id)
                    {
                        return i;
                    }
                }
                return -1;
            }

            int findCheckedOut (string isbm)// overloaded function that can find checked out book and user with only the isbm
            {
                string isbn_test;

                if (libary_libary.size()==0)
                return -2; // there is no list of books

                for (int i=0; i <libary_libary.size(); i++ )
                {
                    isbn_test = libary_libary[i].isbm;

                    if (isbn_test == isbm )
                    {
                        return i;
                    }
                }
                return -1;
            }

            void checkOutBook () // function to check out a book to a user
            {

                auto& bookData = BookData::get(); // used to making calling into the BookData singlton easier to write
                auto& userData = UserData::get(); // used to making calling into the BookData singlton easier to write

                string isbm, book_title_search, name_search;
                int user_id, book_index, user_index;
                int checkOut_index;

                do 
                {
                    do
                    {             
                        cout<<endl<<"Libary Interface: Checkout a Book"<<endl;
                        cout<<"     Enter Book Title: ";
                        book_title_search = InputValidation::get().FullStringInputValidation ();

                        cout<<"     Enter Book ISBN: ";
                        isbm= InputValidation::get().ISBMInputValidation();

                        book_index = bookData.findBook(isbm);

                        if (book_index == -2)
                        {
                            cout<<"         No books have been entered into the system. Please add books first."<<endl;
                            return;
                        }
                        else if (book_index == -1)
                        {
                            cout<<"         Book not found. Try again(y/n)?: ";
                            book_index = InputValidation::get().YesNoInputValidation ();

                            if (book_index==-1)
                                return;
                        }
                    } while (book_index < 0);


                    checkOut_index = findCheckedOut(isbm);

                    if (checkOut_index > -1)
                    {
                    cout<<"         Book is already checked out. Do you want to try a differnt book (y/n)?.";
                    checkOut_index = InputValidation::get().YesNoInputValidation ();

                        if (checkOut_index == -1)// no
                            return;
                        
                        else //yes
                            checkOut_index=0;                   
                    }

                }while (checkOut_index>-1);


                do
                {

                    cout<<"     Enter User Name: ";
                    name_search=InputValidation::get().StringInputValidation();

                    
                    cout<<"     Enter User ID: ";
                    user_id=InputValidation::get().IntInputValidation (1);

                    user_index = userData.findUser(name_search,user_id);

                    if (user_index == -2)
                    {
                        cout<<"No Users have been entered into the system. Please add a user first."<<endl;
                        return;
                    }
                    else if (user_index == -1)
                    {
                        cout<<"         User not found. Try again(y/n)?: ";
                        user_index = InputValidation::get().YesNoInputValidation ();

                        if (user_index==-1)
                            return;
                    }
                } while (user_index<0);



                libary_libary.push_back(Libarylist(isbm, user_id));
                cout<<"Book Check Out Succesfully"<<endl;
            }

            void checkInBook () // function to return a checked out book
            {

                string isbm_search, book_title_search;
                int user_id_search, libary_index,checkOut_index;

                do 
                {
                    cout<<endl<<"Libary Interface: Return Book"<<endl;
                cout<<"     Enter Book ISBN: ";
                isbm_search=InputValidation::get().ISBMInputValidation();

                cout<<"     Enter User ID: ";
                user_id_search=InputValidation::get().IntInputValidation (1);

                checkOut_index = findCheckedOut(isbm_search,user_id_search);

                if (checkOut_index == -2)
                {
                    cout<<"No books have been chekced out."<<endl;
                    return;
                }
                else if (checkOut_index == -1)
                {
                    cout<<"         Book is not check out or input was miss spelled. Try again(y/n)?: ";
                    checkOut_index = InputValidation::get().YesNoInputValidation ();

                    if (checkOut_index==-1)
                        return;
                }

                }while(checkOut_index<0);

                // check to make sure book and user is in system
                libary_index = findCheckedOut(isbm_search,user_id_search);
                libary_libary.erase(libary_libary.begin() + libary_index);
            
                cout<<"Book Returned Succesfully"<<endl;
            }

            void listBooks ()// lists all the book entered into the system
            {
                int size; 
                cout<<endl<<"Libary Interface: Book List"<<endl;

                auto& bookData = BookData::get(); // used to making calling into the BookData singlton easier to write
                size = bookData.showBook();
                if (size ==0)
                cout<<"No Books have been entered into the system."<<endl;

            }


            void listUsers ()// lists all users entered into the system
            {
                int size; 
                cout<<endl<<"Libary Interface: User List"<<endl;

                auto& userData = UserData::get(); // used to making calling into the BookData singlton easier to write
                size = userData.showUser(); 
                if (size ==0)
                cout<<"No Users have been entered into the system."<<endl;
            }

            void listCheckOutBooks ()// list all the checked out book and the users that checked out the books
            {
                auto& bookData = BookData::get(); // used to making calling into the BookData singlton easier to write
                auto& userData = UserData::get(); // used to making calling into the BookData singlton easier to write

                string libary_ismb;
                int libary_userID;
                string book_title, user_name;

                if (libary_libary.size()==0)
                {
                    cout<<"No Books have been checked out."<<endl;
                    return;
                }
                cout<<endl<<"Libary Interface: List of Checked Out Books"<<endl;

                for (int i= 0; i < libary_libary.size(); i++)
                {
                    libary_ismb = libary_libary[i].isbm;
                    libary_userID = libary_libary[i].user_id;

                    book_title = bookData.findBookTitle(libary_ismb);
                    user_name = userData.findUser(libary_userID);

                    cout<<i+1<<") Book Check Out"<<endl;
                    cout<<     "                  User Name     :"<<user_name<<endl;
                    cout<<     "                  ID            :"<<libary_libary[i].user_id<<endl;
                    cout<<     "                  Book Check Out:"<<book_title<<endl;
                    cout<<     "                  ISMN          :"<<libary_libary[i].isbm<<endl;
                }
            }

};

class Menu // creats all the menu options and manages moving through menues
{
    public:
        int showMenu(int userintput)
        {
            int menu_input, menu1, menu2;

            menu1 = mainMenu(userintput);
            menu2 = subMenu(menu1);
       

            if (menu1 ==1)
            {
                switch (menu2)
                {
                    case 1: 
                        BookData::get().setBook ();
                        break;
                    case 2: 
                        BookData::get().editBook();
                        break;
                    case 3: 
                        BookData::get().removeBook();
                        break;
                }
            }
            else if (menu1 ==2)
            {
                switch (menu2)
                {
                    case 1: 
                        UserData::get().setUser();
                        break;
                    case 2: 
                        UserData::get().editUser();
                        break;
                    case 3: 
                        UserData::get().removeUser();
                        break;
                }
            }
            else if (menu1 ==3)
            {
                switch (menu2)
                {
                    case 1: 
                        LibaryData::get().checkOutBook();
                        break;
                    case 2: 
                        LibaryData::get().checkInBook();
                        break;
                    case 3: 
                        LibaryData::get().listBooks();
                        break;
                    case 4: 
                        LibaryData::get().listUsers();
                        break;
                    case 5: 
                        LibaryData::get().listCheckOutBooks();
                        break;
                }  
            }

            if (menu2 == -1)
                menu1 = -1 ;
        
            return menu1;
        }

        int mainMenu(int menu_input)
        {
            int exit_adjustment = 0, size, i = 1, user_input;

         

           if (menu_input == -1)
           {
                cout<<endl;
                cout<<"Libary Interface: Main Menu"<<endl;
                cout<<"     1) "<<BookData::get().getTitle()<<endl;
                cout<<"     2) "<<UserData::get().getTitle()<<endl;
                cout<<"     3) "<<LibaryData::get().getTitle()<<endl;
                cout<<"     4)Exit " << endl;
                cout<<"Enter User Input:";
                user_input = InputValidation::get().menuInputValidation(MIN_MENU_SIZE,MAX_MENU_SIZE );

                if (user_input ==MAX_MENU_SIZE)
                {
                    user_input = -2;
                }
            }
            else
            {
                user_input = menu_input;
            }
                return user_input;
        }

        int subMenu(int mainMenu_Input)
        {

            int size, user_input,i;
            bool found_menu = false;
            cout<<endl;

                if (mainMenu_Input == 1)
                {
                    cout<<"Libary Interface: "<<BookData::get().getTitle()<<" Menu"<<endl;
                    size = BookData::get().getSubTitle().size();
                    for ( i=0; i<size; i++)
                        cout<<"     "<<i+1<<") " << BookData::get().getSubTitle()[i] << endl;
                    cout<<"     "<<i+1<<")Go Back" << endl;
                    cout<<"User Input: ";
                    user_input = InputValidation::get().menuInputValidation(MIN_MENU_SIZE,size+1 );
                }
                else if (mainMenu_Input == 2)
                {
                    cout<<"Libary Interface: "<<UserData::get().getTitle()<<" Menu"<<endl;
                    size = UserData::get().getSubTitle().size();
                    for ( i=0; i<size; i++)
                        cout<<"     "<<i+1<<") " << UserData::get().getSubTitle()[i] << endl;
                    cout<<"     "<<i+1<<")Go Back" << endl;
                    cout<<"User Input: ";
                    user_input= InputValidation::get().menuInputValidation(MIN_MENU_SIZE,size+1 );                    
                }
                else if (mainMenu_Input == 3)
                {
                    cout<<"Libary Interface: "<<LibaryData::get().getTitle()<<" Menu"<<endl;
                    size = LibaryData::get().getSubTitle().size();
                    for ( i=0; i<size; i++)
                        cout<<"     "<<i+1<<") " << LibaryData::get().getSubTitle()[i] << endl;
                    cout<<"     "<<i+1<<")Go Back" << endl;
                    cout<<"User Input: ";
                    user_input= InputValidation::get().menuInputValidation(MIN_MENU_SIZE,size+1 ); 
                }
                else 
                {
                    user_input = -2;
                }

                if (user_input == size+1)
                {
                    user_input = -1;//this goes back to main menu
                }
                return user_input;
        }

};


int main()  // main function
{

    Menu menu;// created class object menu 
    int userinput = -1;

    do 
    {
        userinput = menu.showMenu(userinput); // rund menu options and controls all function of program from here
    }
    while (userinput != -2);

    cout<<"Thank you for using the Libary Interface System"<<endl<<endl;

    return 0;
}

