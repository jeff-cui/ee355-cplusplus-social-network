#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <vector>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
}

Network::~Network(){
    // TODO: Complete this method
    // Destructure delete all the Person
}


void Network::push_front(Person* newEntry){
    // Adds a new Person (newEntry) to the front of LL
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // TODO: Complete this method!
    // Adds a new Person (newEntry) to the back of LL

    // set the next and prev of newEntry
    newEntry->next = NULL;
    newEntry->prev = tail;

    // this checks if it's the first node in the LL
    if (tail != NULL) {
        // make tail point to the newEntry
        tail->next = newEntry;
    }
    // else statement only occurs once when tail = NULL
    // this means the node we're adding is the first node in the LL
    // therefore head = newEntry
    else {
        head = newEntry;
    }

    // tail is now newEntry
    tail = newEntry;
    count++;
}


void Network::printDB(){
    // Don't change this method
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of persons: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // TODO: Complete this method!
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.db as a template
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, 
    // now the one who is responsible for implementing Network should be aware of implementation of Person, not good! You will fix this in PA2. 

    /*
    Aguilar, Abel
    7/27/91
    (USC-email) aaaguila@usc.edu
    (Cell) 8872871418
    */

    // open fstream/file
    fstream outfile;
    outfile.open(filename.c_str());

    // create a ptr that goes through our whole LL
    Person* ptr = head;
    while(ptr != NULL){
        // get birthdate
        string birthdate = ptr->birthdate->get_date();

        // get email and phone info
        string email_info = ptr->email->get_contact("not full style");
        string phone_info = ptr->phone->get_contact("not full style");

        // write out to file in the format of studentDB.db
        outfile << ptr->l_name << ", " << ptr->f_name << endl;
        outfile << birthdate << endl;
        outfile << email_info << endl;
        outfile << phone_info << endl;
        outfile << "------------------------------" << endl;

        // go to next person in LL/database
        ptr = ptr->next;
    }
}


void Network::loadDB(string filename){
    // TODO: Complete this method!
    // Loads the network from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // You need to use the following constructor of the Person class, Person::Person(fname, lname, bdate, email, phone)
    
    Person* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate, email, phone;
    // TODO: Decalre other vairiable if needed

    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        // TODO: read email and phone
        
        getline(infile, email);
        getline(infile, phone);

        // this line is to read the dash line
        getline(infile, buff);
        // TODO: use the constructor Person::Person(fname, lname, bdate, email, phone) to modify the following line
        Person* newEntry = new Person(fname, lname, bdate, email, phone);

        this->push_back(newEntry);
    }
}

Person* Network::search(string fname, string lname, string bdate){
    // TODO: Complete this method!
    // Search the Network for the given fname, lname, bdate
    // You may create a new person, say searchEntry, with fname, lname and bdate. Think about what Person constructor will be helpful with these arguments.
    // And use == overloaded operator between two persons
    // if found, returns a pointer to it, else returns NULL
    // Don't forget to delete allocated memory.

    // make a searchEntry with the info we want to search for
    Person* searchEntry = new Person(fname, lname, bdate, "() test@usc.edu", "() 1234567890");

    // pointer that starts at head of LL
    Person* ptr = head;

    // run through LL
    while(ptr != NULL) {
        // if our ptr equals searchEntry, return the ptr
        if (*ptr == *searchEntry) {
            delete searchEntry;
            return ptr;
        }

        ptr = ptr->next;
    }

    // if we don't find a match, return NULL
    delete searchEntry;
    return NULL;
}

bool Network::remove(string fname, string lname, string bdate){
    // TODO: Complete this method! Follow these steps:
    // Create a new person with the the give arguments as you do in search
    // Search if this person exists using search method. If it does not exist just return false! Else, remove the person from LL, make the other connections connected
    // Don't forget to delete allocated memory, change count and returning values!

}

void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Load network database \n";
        cout << "2. Save network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Search \n";
        cout << "5. Remove a person \n";
        cout << "6. Print database \n";
        
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate, email, phone;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Loading network database \n";

            // create a vector that stores file names
            vector < string > fileList;
            int db_match_flag = 0;

            // TODO: print all the files in this same directory that have ".db" format
            // code taken from sample_file.cpp and adjusted to find ".db" format
            DIR *dir;
            struct dirent *ent;
            char targetFolderAddr[] = "./";

            // open current directory
            if ((dir = opendir ("./")) != NULL) {

                cout << "All files that have .db format in this directory: " << endl;

                // while we can read from directory
                while ((ent = readdir (dir)) != NULL) {
                    string file_name = ent->d_name;

                    // check file_name and find the .db format
                    for (int i = 0; i < file_name.size(); i++) {
                        if (file_name[i] == '.') {
                            // if we find .db then print out the file name
                            if (file_name[i+1] == 'd' && file_name[i+2] == 'b') {
                                cout << file_name << endl;
                                fileList.push_back(file_name);
                            }
                        }
                    }     
                }
                
                closedir (dir);
            } 

            // can't open directory
            else {
                /* could not open directory */
                perror ("No directory!");
            }

            cout << endl;

            // read in fileName from user input
            cout << "Enter the name of the load file: "; 
            getline(cin,fileName);

            // iterate through our list of possible .db files
            for (int i = 0; i < fileList.size(); i++) {
                // if we have a match with user input and possible .db files
                // change flag to 1
                if (fileName == fileList[i]) {
                    db_match_flag = 1;
                }
            }
            // have a matching .db file
            if (db_match_flag == 1) {
                loadDB(fileName.c_str());
                // If file is loaded successfully, also print the count of persons in it: 
                cout << "Network loaded from " << fileName << " with " << count << " persons \n";
            }
            // no match
            else {
                // If file with name FILENAME does not exist: 
                cout << "File FILENAME does not exist!" << endl;
            }
            
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Saving network database \n";

            cout << "Enter the name of the save file: ";
            getline(cin,fileName);
            cout << "Network saved in " << fileName << endl;

            // if there is nothing in our database aka head points to NULL
            if (head == NULL) {
                Person* newEntry = new Person("", "", "", "(Nothing) nothing@usc.edu", "(Nothing) 123-456-7890");
                push_front(newEntry);
                saveDB(fileName.c_str());
            }
            else {
                saveDB(fileName.c_str());
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new person ONLY if it does not exists!
            cout << "Adding a new person \n";

            string email_type;
            string phone_type;


            // ask for person's info
            cout << "First Name: ";
            getline(cin,fname);
            cout << "Last Name: ";
            getline(cin,lname);
            cout << "Birthdate (M/D/YYYY): ";
            getline(cin,bdate);
            cout << "Email Type: ";
            getline(cin,email_type);
            cout << "Email: ";
            getline(cin,email);
            cout << "Phone Type: ";
            getline(cin,phone_type);
            cout << "Phone: ";
            getline(cin,phone);

            email = "(" + email_type + ") " + email;
            phone = "(" + phone_type + ") " + phone;

            // search if they exist already or not
            Person* ptr = search(fname, lname, bdate);

            // if found: don't create entry
            if (ptr != NULL) {
                cout << "Person already exists! \n";
            }
            // if not found, create the entry with push_front
            else {
                Person* newEntry = new Person(fname, lname, bdate, email, phone);
                push_front(newEntry);
                cout << "Person added to database \n";
            }
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            getline(cin,fname);
            cout << "Last Name: ";
            getline(cin,lname);
            cout << "Birthdate (M/D/YYYY): ";
            getline(cin,bdate);

            Person* ptr = search(fname, lname, bdate);

            // if found: print person's firstname, lastname, bdate, email, phone using print_person()
            if (ptr != NULL) {
                ptr->print_person();
            }
            // if not, cout << "Not found! \n";
            else {
                cout << "Not found! \n";
            }
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Removing a person \n";
            cout << "First name: ";
            cout << "Last name: ";
            cout << "Birthdate (M/D/YYYY): ";
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
        }
        else if (opt==6){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}


