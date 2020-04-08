
#include "person.h"

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    // TODO: complete the method!
}


Person::Person(string fname, string lname, string bdate, string email, string phone) {
    // TODO: Complete this method!
    // phone and email strings are in full version

    string email_type;
    string addr;

    string phone_type;
    string num;

    int i = 0;
    int j = 0;

    // reads in and ignores until we find '('
    while (email[j] != '(') {
        j++;
    }

    // increment once to skip the '('
    j++;

    // reads into email_type until we find ')'
    while (email[j] != ')') {
        email_type.append(email[j]);
        j++;
    }
    // reads in the email
    for (int k = j+2; k < email.size(); k++) {
        addr.append(email[k]);
    }

    // create email class
    email = new Email(email_type, addr);


    // reads in and ignores until we find '('
    while (phone[i] != '(') {
        i++;
    }

    // increment once to skip the '('
    i++;

    // reads into phone_type until we find ')'
    while (phone[i] != ')') {
        phone_type.append(phone[i]);
        i++;
    }

    // reads in the phone
    for (int k = i+2; k < phone.size(); k++) {
        num.append(phone[k]);
    }

    // create phone class
    phone = new Phone(phone_type, num);


    // set f_name, l_name and birthdate
    this->f_name = fname;
    this->l_name = lname;
    birthdate = new Date(bdate);

}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    getline(cin,f_name);

	cout << "Last Name: ";
    getline(cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    getline(cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    getline(cin,type);
    cout << "Email address: ";
    // code here
    getline(cin,temp);

    // set new email
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    // code here
    getline(cin, type);

    cout << "Phone number: ";
    // code here
    getline(cin, temp);

    // set new phone number
    phone = new Phone(type, temp);
    // code here
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!

    /*
    Julia Scarlett Elizabeth
    Louis-Dreyfus
    1/13/1961
    (Home) 310-192-2011
    (Work) julia@wh.com
    */

    fstream file;
    file.open(filename);
    string input;

    // for 5 lines in our file
    for (int i = 0; i < 5; i++) {
        getline(file, input);

        // 1st line is first name
        if (i == 0) {
            f_name = input;
        }  
        // 2nd line is last name 
        if (i == 1) {
            l_name = input;
        }
        // 3rd line is birthdate
        if (i == 2) {
            birthdate = new Date(input); 
        }
        // 4th line is phone
        if (i == 3) {
            string phone_type;
            string number;
            int j = 1;

            // reads in the type without parenthesis
            while (input[j] != ')') {
                phone_type.append(input[j]);
                j++;
            }

            // reads in the number
            for (int k = j+2; k < input.size(); k++) {
                number.append(input[k]);
            }

            // create phone number class
            phone = new Phone(phone_type, number);
        }
        // 5th line is email
        if (i == 4) {
            string email_type;
            string addr;
            int j = 1;

            // reads in the type without parenthesis
            while (input[j] != ')') {
                email_type.append(input[j]);
                j++;
            }

            // reads in the email
            for (int k = j+2; k < input.size(); k++) {
                addr.append(input[k]);
            }

            // create email class
            email = new Email(email_type, addr);
        }
    }

    file.close();

}


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)

    // get birthdates
    string bday = get_date();
    string rhs_bday = rhs.get_date();

    // check first name, last name and birthdates
    if ( (f_name == rhs.f_name) && (l_name == rhs.l_name) && (bday == rhs_bday) ) {
        return true;
    }
    else {
        return false;
    }
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
}

