/* COP3331
 * IGLI DURO
 * U33766202 */

/* In this lab, you will implement a program with the same purpose as Lab 2, 
 * but using an object-oriented approach and adding some display functionality for the note data.  
 * Specifically, your program should open up the file input.txt, 
 * read the music described there, print the music, transform the data into a .wav file, and generate output.wav.  
 * However, rather than using structs and functions, you will implement 3 classes:  Song, Voice, and Note.  
 * Specifically, you will implement the constructors for these 3 functions and 3 overloaded print functions, 
 * which are described below: */

/* Portions of code reused from Lab 2 */

/* Code compliles with the argument "g++ -g song-driver.cpp song.cpp wavfilewriter.cpp" however no output.wav file is created. 
 * When testing constructors with cout lines for variables no output is displayed. Code essentially accomplishes nothing. 
 * Somewhere along the line data isn't being passed forward. Following the logic by hand I feel that I'm on the right track with setting up Vector<Note> and Vector<Voice>.
 * But it appears I'm missing something when it comes to working with classes & constructors. Need to follow up and get this working before moving forward */ 


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "wavfilewriter.h"
#include "song.h"
#include <string>
#include <cctype>

using namespace std;


/* This constructor uses the given string to initialize the pitch, octave, and duration of this note.  
 * The format of this string will be the same as the input file (see Lab 2 for more details). */

Note::Note(const string str) {

//====================================PITCH====================================//

    int i = 0;
    string noteType;
    //Max note length is 2, if a digit is encountered it will be ignored. 
    for (i = 0; i < 2; i++ ) {

        if (!(isdigit(str[i]))) {
            noteType += str[i];
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



//====================================OCTAVE====================================//

    string holdInt;
    //There will only be one digit in the word. Loop through string to find digit index.
    for (int j = 1; i < 3; j++) {
        if (isdigit(str[j])) {
            //Copy value at index containing digit to second string.
            holdInt = str[j];
        }
    }

    //Turn string value into int.
    octave = stoi(holdInt);


//====================================DURATION====================================//

    int k = 2;
    string holdDuration;

    //Loop till end of string, ignore digit, copy to second string.
    while (!str[k] == '\0') {
        if (!isdigit(str[k])) {
            holdDuration += str[k];
        }
        k++;
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
    
    
    //Test note data.
    //cout << "Pitch: " << pitch << " Octave: " << octave << " Duration: " << duration << endl;
}


/* This constructor takes in a line of the input file (the first argument) and uses it to initialize a vector of Notes.  
 * It should use the second and third arguments to initialize the volume and instrument.  
 * (Instruments are a new feature to the code relative to Lab 2; you can play around with using different instruments, 
 * though they are not required for solving this lab.)  
 * When calling this constructor, you should use the default values in the provided header. */

Voice::Voice(const string& str, double vol, instrument_t instr) {
    //Default values for volume and instrument
    volume = DEFAULT_VOLUME;
    instrument = DEFAULT_INSTRUMENT;

    istringstream inSS;

    inSS.str(str);


    string tempString;

    //Parse string into notes 
    while(inSS >> tempString) {


        Note temp(tempString);

        //Add note to vector of notes 
        addNote(temp);
    }


}

/* This constructor opens the file with the given name 
 * and reads in the tempo and note information to initialize the song */
Song::Song(const string& file){
    
    //Open file
    ifstream inFile;
    string fileNote;

    //open input.txt
    inFile.open(file);

    //Get tempo from first line 
    inFile >> tempo;

    //Test
    //getline(inFile, fileNote);

    //Loop to add voice to vector of voice's 
    while (!inFile.eof()) {
        getline(inFile, fileNote);

        
        Voice temp(fileNote);
        addVoice(temp);
    }

    inFile.close();
}
/* Prints the given note to out, in the same format as it is stored in the file. 
 * For example, a C on octave 3 with duration 1.0 should be printed as "C3q".  (See Lab 2 for details on format.) */
ostream& operator<<(ostream& out, const Note& n) {
   out << n.getPitch() << n.getOctave() << n.getDuration();
    return out;
}

/* Prints all of the Notes in the given Voice to out, separated by spaces. */
ostream& operator<<(ostream& out, const Voice& v) {
    
    
   // for (int l = 0; l < v.getNotes(); l++) {
       // out << v.getNotes[l].pitch << v.getNotes[l].octave << v.getNotes[l].duration " ";
//    }

    return out;
}

/* Prints to out the tempo on a line, followed by each Voice in the Song, one per line.  
 * The output should be identical to the input file, with the exception that sharp notes (A#, C#, etc.) 
 * should be replaced with their equivalent flat notes (Bb, Db, etc.) */

ostream& operator<<(ostream& out, const Song& s) {
    return out;
}

