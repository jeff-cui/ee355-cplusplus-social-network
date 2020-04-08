#include "contact.h" 
// TODO: Add needed libraries! 


Email::Email(string type, string email_addr){
    // TODO: Complete me!
    //set type equal to type
    this->type = type;
    //set the email address equal to the variable email_addr
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    cin >> type;
    // some code here
    cout << "Enter email address: ";
    cin >> email_addr;
    // some code here
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    // emaple: Email (USC): tommytrojan@usc.edu
    if (style=="full")
	    return "Email (" + type + "): " + email_addr;
    else 
        return "(" + type + ") " + email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it! 222-444-7898
    // TODO: Complete this method!

    //set type to type
    this->type = type;
    //set num equal to the phone number of type string
    this->phone_num = num;
    //if there are dashes in the phone number make it so that there are no dashes and it is just numbers
    if(num.length() == 12){
        string x_1 = num.substr(0,3);
        string x_2 = num.substr(4,3);
        string x_3 = num.substr(8,4);
        this->phone_num = x_1 + x_2 + x_3;
    }

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand why?
    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    */
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    cin >> type;

    // this is a flag to see if we have a valid input
    // 1 means valid, 0 is not
    int valid_input_flag = 0;
    // a counter that checks if every digit we have in our input phone number is actually a number
    int every_char_is_number_counter = 0;

    // while not valid input
    while (valid_input_flag == 0) {
        // prompt user for phone number
        cout << "Enter the phone number: ";
        cin >> phone_num;

        // if we have our 10 digit number, continue
        if (phone_num.size() == 10) {
            // run through each digit of number and see if it's 0-9
            for (int i = 0; i < phone_num.size(); i++) {
                char c = phone_num[i];

                // if c is 0-9 based on ASCII value, increment counter
                if (c > 47 && c < 58) {
                    every_char_is_number_counter++;
                }
            }

            // valid phone number should have all 10 digits increment the counter
            // if so we have valid input
            if (every_char_is_number_counter == 10) {
                valid_input_flag = 1;
            }

            // if not, try again
            else {
                every_char_is_number_counter = 0;
                cout << "Not every digit was a number" << endl;
            }

        }
    }
}

string Phone::get_contact(string style){
    // TODO:

    string x1 = phone_num.substr(0,3);
    string x2 = phone_num.substr(3,3);
    string x3 = phone_num.substr(6,4);

    string num = x1 + "-" + x2 + "-" + x3; 

    if (style=="full")
        return "phone (" + type + "): " + num;
    else 
         return "(" + type + ") " + num;

}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


