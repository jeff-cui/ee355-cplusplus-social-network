#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
// included libraries
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
    
    //initialize head tail and count
    head = NULL;
    tail = NULL;
    count = 0;

    //call loadDB to directly load a database when using this constructor
    loadDB(fileName.c_str());
}

Network::~Network(){
    // TODO: Complete this method
    // Destructure delete all the Person

    //create a pointer that keeps track of the nodes (people)
    Person* destructor_ptr = head;

    //run through every element in the LL 
    //set the pointer equal to the next of the head
    //delete the head
    //make the pointer the new head
    //continue until there are no more people aka head is NULL
    //added cout statements that are commented out that we used to check out destructor

 //   cout << count << endl;
 //   cout << head << endl;
    while(head != NULL){
        destructor_ptr = head->next;
        delete head;
        head = destructor_ptr;
        count--;
    }
//    cout << count << endl;
//    cout << head << endl;
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

    // this checks if it's the first node added into the LL
    if (tail != NULL) {
        // make tail point to the newEntry if it's not the first node added
        // tail is what will be the 2nd to last node
        tail->next = newEntry;
    }
    // else statement only occurs once when tail = NULL
    // this means the node we're adding is the first node in the LL
    // therefore head = newEntry
    else {
        head = newEntry;
    }

    // update tail so it now points to newEntry
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
    ofstream outfile;
    outfile.open(filename.c_str(), ofstream::trunc);

    // create a ptr that goes through our whole LL
    Person* ptr = head;

    // go through LL
    while(ptr != NULL){
        // get birthdate
        string birthdate = ptr->birthdate->get_date();

        // get email and phone info
        string email_info = ptr->email->get_contact();
        string phone_info = ptr->phone->get_contact();

        // write out to file in the format of studentDB.db
        outfile << ptr->l_name << ", " << ptr->f_name << endl;
        outfile << birthdate << endl;
        outfile << email_info << endl;
        outfile << phone_info << endl;
        outfile << "------------------------------" << endl;

        // go to next person in LL/database
        ptr = ptr->next;
    }

    outfile.close();
}

bool allCharactersSame(string s) {
	int n = s.length();
	for (int i = 1; i < n; i++) {
		if (s[i] != s[0]) {
			return false;
		}
	}

	return true;
}

void Network::loadDB(string filename){
    // TODO: Complete this method!
    // Loads the network from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // You need to use the following constructor of the Person class, Person::Person(fname, lname, bdate, email, phone)
    
	int found_dash_line_flag = 0;

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
    // TODO: Decalre other variable if needed

    // read database the 1st time, ignore IDs
    while(getline(infile, buff)) {
    	// read 1st four lines for name, bdate, email, phone
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        // read in email and phone info using getline
        // they are not parsed as they will be parsed in our Person constructor
        getline(infile, email);
        getline(infile, phone);
/*
        // keep reading until we reach the dotted line, ignore the ID
        while (found_dash_line_flag == 0) {
        	getline(infile, buff);
        	cout << buff << endl;

        	
        	// check if it is the dash line, if it is set flag to true and leave while loop
        	if (allCharactersSame(buff)) {
        		cout << buff << endl;
				cout << "found dash line" << endl;
				found_dash_line_flag = 1;
        	}
        	else {
        		cout << buff << endl;
				cout << "no" << endl;
        	}
        }

        // reaching here means we reached dash line, set flag back
        found_dash_line_flag = 0;*/

        // read the dash line
        getline(infile, buff);

        // TODO: use the constructor Person::Person(fname, lname, bdate, email, phone) to modify the following line
        // create a new Person dynamically using constructor
        Person* newEntry = new Person(fname, lname, bdate, email, phone);

        this->push_back(newEntry);
    }

/*
    infile.close();
    // reopen file so we're back at the top of the file
    infile.open(filename.c_str());

    // read database the 2nd time, only look for IDs
    // run through LL
    ptr = head;
    while(ptr != NULL) {
    	// skip the 1st four lines of Person info cause we don't want it this time
    	getline(infile, buff);
        getline(infile, bdate);
        getline(infile, email);
        getline(infile, phone);

        // keep reading until we reach the dotted line, add IDs
        while (found_dash_line_flag == 0) {
        	// read in the next line
        	getline(infile, buff);
        	// check if it is the dash line, if it is set flag to true and leave while loop
        	if (buff[0] == '-') {
        		found_dash_line_flag = 1;
        	}
        	// else we wanna add this ID
        	else {
        		// find pointer of Person who owns the ID
        		Person* friend_ptr = search(buff);
        		// add that friend_ptr to our current node/Person's friend list
        		ptr->addFriend(friend_ptr);
        	}
        }

        // reaching here means we reached dash line, set flag back and go to next Person in the LL
        ptr = ptr->next;
        found_dash_line_flag = 0;
    }

    */
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

        // if not go to next node
        ptr = ptr->next;
    }

    // if we don't find a match, delete our allocated memory and return NULL
    delete searchEntry;
    return NULL;
}

// phase 2 search function
Person* Network::search(string queryid){
    // Search the Network for the given ID
    // if found, returns a pointer to it, else returns NULL
    // Don't forget to delete allocated memory.

	// these strings will be passed into IDName to create ID of a Person
    string lname;
    string fname;
    string id;

    // pointer that starts at head of LL
    Person* ptr = head;

    // run through LL
    while(ptr != NULL) {
    	// get last and first name of the node/Person
    	lname = ptr->l_name;
    	fname = ptr->f_name;

    	// make their ID
    	id = IDName(lname, fname);

    	// if this id equals our queryid, then Person exists and return ptr
    	if (id == queryid) {
    		return ptr;
    	}
    	// if it doesn't match, go to next node
    	else {
        	ptr = ptr->next;
    	}
    }

    // if we don't find a match, return NULL
    return NULL;
}

bool Network::remove(string fname, string lname, string bdate){
    // TODO: Complete this method! Follow these steps:
    // Create a new person with the the give arguments as you do in search
    // Search if this person exists using search method. If it does not exist just return false! Else, remove the person from LL, make the other connections connected
    // Don't forget to delete allocated memory, change count and returning values!

    //create a pointer to locate where the person is in the LL
    Person* remove_ptr = search(fname, lname, bdate);

    //if the person is the only one on the list, then set the head and the tail to NULL
    //the list is now empty
    if(count == 1){
        head = NULL;
        tail = NULL;
    }

    //if the person is located at the tail of the LL
    //set the new tail equal to the term prev the pointer
    //set the term after the tail equal to NULL
    else if(remove_ptr->next == NULL){
        tail = remove_ptr->prev;     
        tail->next = NULL;
    }

    //if the person is locted at the head of the LL
    //set the new head equal to the term next in the LL
    //set the term before the newly set header equal to NULL
    else if(remove_ptr->prev == NULL){
        head = remove_ptr->next;
        head -> prev = NULL;
    }
    //if the person is located in the middle of the list, aka not head nor tail
    //set the "prev" of the next node after the node we're deleting to = remove_ptr's prev 
    //set the "next" of the node before the node we're deleting to = remove_ptr's next
    // this makes it so we don't break our LL
    else{
        remove_ptr->next->prev = remove_ptr->prev;
        remove_ptr->prev->next = remove_ptr->next;
    }

    //decrement count because there is now one less person in the LL
    count--;
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

        // phase 2 
        cout << "7. Add friends \n";
        
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

            // create a vector that stores .db file names
            vector < string > fileList;
            // this is a flag that we'll use later to see if user input of a .db file matches an existing one
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
                	// read in file name into file_name
                    string file_name = ent->d_name;

                    // check file_name and find the .db format
                    for (int i = 0; i < file_name.size(); i++) {
                    	// if we find a ".", we expect a "db" to follow it
                        if (file_name[i] == '.') {
                            // if we find .db then print out the file name and add it to our vector of .db file names
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
            // if we have a matching .db file
            if (db_match_flag == 1) {
            	// load it
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
                cout << "No database found so we will add a new person \n";
                // create a person with random info just so we have something to write to our output file
                Person* newEntry = new Person("bob", "the builder", "1/1/1970", "(Nothing) nothing@usc.edu", "(Nothing) 123-456-7890");
                // add it to empty database and save the database
                push_front(newEntry);
                saveDB(fileName.c_str());
            }
            // else we will save our database/write to output file
            else {
                saveDB(fileName.c_str());
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new person ONLY if it does not exists!
            cout << "Adding a new person \n";

            // new variables to store info
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

            // format email and phone info to format needed
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
            // ask for first name, last name and birthdate
            cout << "First Name: ";
            getline(cin,fname);
            cout << "Last Name: ";
            getline(cin,lname);
            cout << "Birthdate (M/D/YYYY): ";
            getline(cin,bdate);

            // call search function and it will return a pointer
            Person* ptr = search(fname, lname, bdate);

            // if found aka ptr != NULL, then print person's firstname, lastname, bdate, email, phone using print_person()
            if (ptr != NULL) {
                ptr->print_person();
            }
            // if not found, cout << "Not found! \n";
            else {
                cout << "Not found! \n";
            }
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            cout << "Birthdate (M/D/YYYY): ";
            getline(cin, bdate);

            // search to see if that person exists in database
            Person* ptr = search(fname, lname, bdate);

            // if found, cout << "Remove Successful! \n";
            //remove the name from the database
            if (ptr != NULL) {
                cout << "Remove Successful! \n";
                remove(fname, lname, bdate);
            }
            // if not found: cout << "Person not found! \n";
            else {
                cout << "Person not found! \n";
            }


        }
        else if (opt==6){
            // TODO: Complete me!
            cout << "Network Database: \n";

            // added in call to printDB()
            printDB();
        }

        // phase 2, option 7 add friend
        else if (opt==7){
            cout << "Add Friends: \n";
            string id1;
            string id2;

            // pointers that point to Persons if we want to add friends
            Person* ptr2;
            Person* ptr1;

            // these are flag variables to check if we found a Person based on ID
            int person1_found = 0;
            int person2_found = 0;

            // ask for Person 1's ID
            cout << "Person 1 ID: ";
            getline(cin, id1);

            // search for their ID
            ptr1 = search(id1);

            // if ptr1 is NULL aka ID was not found, print and go back to main menu
            if (ptr1 == NULL) {
            	cout << "Person is not found! \n";
            }
            // set flag to say we found Person 1
            else {
            	person1_found = 1;
            }

            // if we found Person 1, proceed with Person 2
            if (person1_found == 1) {
            	// else ask for Person 2's ID
	            cout << "Person 2 ID: ";
	            getline(cin, id2);

	            // search for Person 2
	            ptr2 = search(id2);

	            // if ptr2 is NULL aka ID was not found, print and go back to main menu
	            if (ptr2 == NULL) {
	            	cout << "Person is not found! \n";
	            }
	            // set flag to say we found Person 2
	            else {
	            	person2_found = 1;
	            }
            }

            // if we have Person 1 and Person 2 found
            if (person1_found == 1 && person2_found == 1) {
            	// if both IDs are found, addFriend for both Person 1 and 2
            	cout << "ADDING FRIENDS" << endl;
	            ptr1->addFriend(ptr2);
	            ptr2->addFriend(ptr1);
            } 
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


