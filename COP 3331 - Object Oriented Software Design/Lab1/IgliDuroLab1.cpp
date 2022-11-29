/* COP3331
 * IGLI DURO
 * U33766202 */

/* This program will open a .html file and save the contents to a string.
 * It will then remove any paragraph and HTML tags from the string.
 * Last, it will print out the results.  */


#include <iostream>
#include <string> //Allows use of strings.
#include <sstream> //Allows use of string streams.
#include <fstream> //Allows use of ifstream.  

using namespace std;

//This function will open the desired file using user input and copy the contents to a string.
string readFile(string fileName) {
    //Input file stream.
    ifstream inFS;
    string fileContents;
    string temp;

    //Open file using string from input.
    inFS.open(fileName);

    //Check if file opened properly.
    if(!inFS.is_open()){
        cout <<"Error opening file." << endl;
    }
    //While loop to read file contents line by line and concactenate to string fileContents using string temp. 
    while (!inFS.eof()){
        getline(inFS, temp);
        fileContents += temp + "\n";
     }


    //Test output of string fileContents.
    //cout << fileContents;
    
    //close file
    inFS.close();
    return fileContents;
}

//This function will find paragraph tags and copy the content between tags to the string paragraphs.
string extractParagraphs(string fileData) {
    
    int index1;
    int index2;
    int i = 0;
    int j = 0;
    string paragraphs;
    string temp;
    

    //While loop that continues until no more paragraph tags can be found.
    while (!(index1 == string::npos)) {    

        //Find beginning of paragraph.
        index1 = fileData.find("<p>", i);

        //Find end of paragraph.
        index2 = fileData.find("</p>", j);

        //Variables to modify the starting search index for next iteration.
        i = index1 + 1;
        j = index2 + 1;
    
    //If statement, may be redundent. Code will break without it. Need help on this one. 
    if (!(index1 == string::npos)) {
    
    //Save content of the substring of string fileData using index found earlier.
     temp = fileData.substr(index1 + 3, (index2 - index1 - 3) );
        //Concactenate temp to string paragraphs along with newlines for formatting.

        paragraphs += temp + "\n\n";
    }
    }
    //Test output of string paragraphs.
    //cout << paragraphs;

    return paragraphs;
}


//This function will find HTML tags in the string and remove them.
string removeTags(string fileParagraphs){

    int index1;
    int index2;

    //While loop that continues until no more tags are found.
    while(!(index1 == string::npos)) {
        
        //Find beginning of tag.
        index1 = fileParagraphs.find("<");

        //Find end of tag.
        index2 = fileParagraphs.find(">");

        //If statement, same issue as in function extractParagraphs.
        if (!(index1 == string::npos)) {
            
            //Replace HTML tags with nothing, essentially deleting them.
            fileParagraphs.replace(index1, (index2 - index1 + 1), "");
        }
    }
    //Test output of fileParagraphs
    //cout << fileParagraphs;

    return fileParagraphs;
}

int main() {
    string fileName;
    string fileData;
    string fileParagraphs;
    string fileTagless;

    //Get user input for filename.
    cout << "Please enter the name of the file in the format filename.html: ";
    cin >> fileName; 
    cout << endl;

    fileData = readFile(fileName);

    fileParagraphs = extractParagraphs(fileData);

    fileTagless = removeTags(fileParagraphs);

    //Display final output.
    cout << fileTagless;
   

    return 0;
}