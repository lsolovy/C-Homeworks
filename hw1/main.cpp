/*Name: Louie Solovy
Date: 2/6/2020
Name of program: URL state machine
Description: This program will prompt the user to enter a URL. It will make sure its a valid URL or else it will prompt
 the user to enter a new URL. It will loop through the URL going throught each character to check if it meets the requiremnets of
 that current state and adding it to the buffer. After it finishes going through the loop without any improper URL requirements
 (or it will quit the state machine) it will print out the scheme, host, and path of the URL.
inputs: URL string
outputs: strings (scheme,path,host), and if there was a validation error with the URL
*/
#include <iostream>

using namespace std;

int main() {
    // intializes strings to be empty
    string input;
    string buffer = "";
    string scheme = "";
    string host = "";
    string path = "";
    // prompts user to enter a URL and save it as a string
    cout << "Please enter a URL" << endl;
    getline(cin, input);
    // outerloop - will stop the program is the user types quit
    while (input != "quit") {


        enum states {
            validation_error, scheme_start, scheme_state, path_host, host_state, path_start, path_state
        };
        states currentstate;
        int index = 0;
        currentstate = scheme_start;
        // inner loop - will run is the index is less than the string size and if the current state is not a validation error
        while (index <= input.size() && currentstate != validation_error) {
            char c = input[index];
            //start of scheme start state
            if (currentstate == scheme_start) {
                // will check to see if the character is a letter (uppercase or lower)
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                    char temp = c;
                    temp = temp - 'A' + 'a';
                    // will make sure that the lowercase version gets added to buffer
                    if ((c >= 'A' && c <= 'Z')) {
                        buffer += temp;
                    }
                    currentstate = scheme_state;
                    if ((c >= 'a' && c <= 'z')) {
                        buffer += c;
                    }

                } else {
                    currentstate = validation_error;
                }
                // start of scheme state
            } else if (currentstate == scheme_state) {
                // will check to see if the character is a letter (uppercase or lower) or a number 0-9
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '+') || (c == '-') || (c == '.') ||
                    (c >= '0' && c <= '9')) {
                    char temp = c;
                    // will change uppercase to lowercase if needed
                    if ((c >= 'A' && c <= 'Z')) {
                        temp = temp - 'A' + 'a';
                        buffer += temp;
                    }else{
                    buffer += c;}
                    currentstate = scheme_state;
                }
                else if (c == ':') {
                    scheme = buffer;
                    buffer.clear();
                    // check to see if remaining string has a '/'
                    if (input[index + 1] == '/') {
                        currentstate = path_host;
                        index++;
                    } else {
                        currentstate = validation_error;
                    }
                } else {
                    currentstate = validation_error;
                }
                // start of path or host state
            } else if (currentstate == path_host) {
                if (input[index] == '/') {
                    currentstate = host_state;
                } else {
                    currentstate = path_state;
                    index--;
                }
                // start of host state
            } else if (currentstate == host_state) {
                if ((c == '\0') || (c == '/')) {
                    index --;
                    //if buffer is empty, validation error
                    if (buffer.length() == 0) {
                        currentstate = validation_error;
                    } else {
                        host = buffer;
                        buffer.clear();
                        currentstate = path_start;
                    }
                }else{
                    buffer += c;
                }
                // start of path start state
            } else if (currentstate == path_start) {
                // if URL is special
                if ((scheme == "ftp") || (scheme == "http") || (scheme == "https")) {
                    currentstate = path_state;
                    if (c != '/') {
                        index--;
                    }
                } else if (c == '?') {
                    currentstate = validation_error;
                } else if (c == '#') {
                    currentstate = validation_error;
                } else if (c != '\0') {
                    currentstate = path_state;
                    if (c != '/') {
                        index--;
                    }
                }
                // start of path state
            } else if (currentstate == path_state) {
                if ((c == '\0') || (c == '?') || (c == '#')) {
                    path += buffer;
                    buffer.clear();
                    if ((c == '#') || (c == '?')) {
                        currentstate = validation_error;
                    }
                } else {
                    buffer += c;
                }
            }
            index++;
        }
        // will print the scheme, host, path
        cout << "Scheme: " << scheme << "\nHost: " << host << "\nPath: " << path << endl;
        //resets all strings for new information
        buffer.clear();
        scheme.clear();
        host.clear();
        path.clear();
        // will prompt user if url is invalid to please enter a new one
        if (currentstate == validation_error){
            cout << "URL is not valid. Please enter a new one" << endl;
        }
        // will still prompt user to enter a new URL until they want to quit
        else {
            cout << "Enter another one if you want to" << endl;
        }
        getline(cin, input);
    }

    return 0;
}