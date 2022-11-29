/* COP3331
 * IGLI DURO
 * U33766202 */

/* This program will open a .txt file containing information regarding a piece of music.
 * The first line of the file represents the tempo as an integer and will be saved to a varaible.
 * The remaining lines will be a sequence of words seperated by spaces.
 * Each word is comprised of the following:
 * - 1 or 2 characters representing the pitch of the note.
 * - A digit representing the octave of the note. 
 * - 1 or 2 characters representing the duration of the note.
 * Words relating to musical notes will be converted to struct note_t and compiled in a vector.
 * The vector is then passed to functions in wavemaker.cpp to be altered and formatted.
 * Last, an ouput.wav is created with the final result. */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "wavemaker.h"
#include "wavemaker.cpp"
#include <string>
#include <cctype>


using namespace std;

//Function to get pitch from word. 
pitch_t getPitch(string fileNote) {

    int i = 0;
    string noteType;
    pitch_t pitch;
    //Max note length is 2, if a digit is encountered it will be ignored. 
    for (i = 0; i < 2; i++ ) {

        if (!(isdigit(fileNote[i]))) {
            noteType += fileNote[i];
            }
            
    }

    //Find match for pitch and set enumeration type.
    if (noteType == "R")
        pitch = REST; 
    else if (noteType == "A")
        pitch = A;
    else if (noteType == "B")
        pitch = B;
    else if (noteType == "C")
        pitch = C;
    else if (noteType == "D")
        pitch = D;
    else if (noteType == "E")
        pitch = E;
    else if (noteType == "F")
        pitch = F;
    else if (noteType == "G")
        pitch = G;
    else if (noteType == "Ab" || noteType == "G#")
        pitch = Ab;
    else if (noteType == "Bb" || noteType == "A#")
        pitch = Bb;
    else if (noteType == "Db" || noteType == "C#")
        pitch = Db;
    else if (noteType == "Eb" || noteType == "D#")
        pitch = Eb;
    else if (noteType == "Gb" || noteType == "F#")
        pitch = Gb;
        
        //Test function return data.
       // cout << noteType << " " << pitch << " ";
    
    return pitch;
}

//Get octave from word.
uint16_t getOctave(string fileNote) {
    uint16_t octave; 
    string holdInt;
    //There will only be one digit in the word. Loop through string to find digit index.
    for (int i = 1; i < 3; i++) {
        if (isdigit(fileNote[i])) {
            //Copy value at index containing digit to second string.
            holdInt = fileNote[i];
        }
    }
    //Turn string value into int.
    octave = stoi(holdInt);

    //Test function ouput return data. 
    //cout << octave << ' ';


    return octave;
}

//Get duration from word.
//q = 1, h = 2, w = 4, e = .5, s = 0.25, . = *1.5
double getDuration(string fileNote) {
    double duration;
    int i = 2;
    string holdDuration;

    //Loop till end of string, ignore digit, copy to second string.
    while (!fileNote[i] == '\0') {
        if (!isdigit(fileNote[i])) {
            holdDuration += fileNote[i];
        }
        i++;
    }

    //Find match for duration and set value. 
    if (holdDuration ==  "q")
        duration = 1.0;
    else if (holdDuration ==  "q.")
        duration = 1.0 * 1.5;
    else if (holdDuration ==  "h")
        duration = 2.0;
    else if (holdDuration ==  "h.")
        duration = 2.0 * 1.5;
    else if (holdDuration ==  "w")
        duration = 4.0;
    else if (holdDuration ==  "w.")
        duration = 4.0 * 1.5;
    else if (holdDuration ==  "e")
        duration = 0.5;
    else if (holdDuration ==  "e.")
        duration = 0.5 * 1.5;
    else if (holdDuration ==  "s")
        duration = 0.25;
    else if (holdDuration ==  "s.")
        duration = 0.25 * 1.5;
    
    //Test values.
    //cout << holdDuration << ' ' << duration << ' ';

    return duration;
}
int main () {

    //Vectors to hold struct data.
    vector<note_t> convertedNotes; 
    vector<sample_t> empty;
    vector<sample_t> convertedSample;

    //Input file stream.
    ifstream inFile;

    int tempo;
    string fileNote;
    string temp;
    
    //Variable of type struct to hold data members.
    note_t notes;
    //Input string stream.
    istringstream inSS; 

     //Open file using string from input.
    inFile.open("input.txt");

    //First line contains data for tempo.
    inFile >> tempo;

    //Test output.
    //cout << tempo;
    

    getline(inFile, fileNote);
    int i = 0;

    //Loop to read each line of the file, convert string data to struct data and pass to wavemaker.cpp.
    while (!inFile.eof()) {
        getline(inFile, fileNote);
        //Test istringstream
        //cout << fileNote << '\n';
        inSS.str(fileNote);

        //Clear vectors before inner loop.
        convertedNotes.clear();
        convertedSample.clear();
        
        //While loop to parse getline data from file and convert to struct data.
        while (inSS >> temp) {
            //Test stringstream.
            //cout << temp; 
            
            //Call to function, return values saved to datamembers.
            notes.pitch = getPitch(temp);
            notes.octave = getOctave(temp);
            notes.duration = getDuration(temp);

            //Struct data added to vector. 
            convertedNotes.push_back(notes);

            //Test ouput.
           // cout << notes.pitch << ' ' << notes.octave << ' ' << notes.duration << '\n';
        }
    //Call to wavemaker.cpp.    
    convertedSample = convertNotesToSamples(convertedNotes, tempo);
    overlay(&empty, &convertedSample);
    
    //Counter
    i++;
    //Clear string stream after each iteration.
    inSS.str("");
    inSS.clear();
    }
    //Close file.
    inFile.close();

    //Test times looped.
    //cout << i; 
    
    //Call for output file creation. 
    writeToWAV("output.wav", &empty);


    return 0;
}