
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}

// add an ID function
string IDName(string str1, string str2) {
    // str1 is last name, str2 is first name
    // id is finished id after removing whitespace, etc
    string id;

    // concatenate strings
    string combined_strings = str1 + str2;

    // go through concatenated string
    for (int i = 0; i < combined_strings.size(); i++) {
        // if it's not a whitespace, make it lowercase and append to id
        if (combined_strings[i] != ' ') {
            char c = tolower(combined_strings[i]);
            id.push_back(c);
        }
    }

    return id;
}

