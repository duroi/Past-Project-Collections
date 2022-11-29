//COP 4530
//IGLI DURO (NAVIGATOR)
//AUSTYN MIKOLON (DRIVER)

#include "hilbert.h"
#include<math.h>


//This function initializes an InstructionListand Turtle to draw a Hilbert curve of the given leveland size.
//The level represents the number of times to apply the substitution rules(starting from the list[ODD]), while the size represents the total size(in pixels) of the Hilbert curve to output.
//When drawing a Hilbert curve to fit a certain size, a level 1 curve moves forward a distance equal to half the size, and each successive level moves forward half as much.
//For example, if we want a level 3 Hilbert curve of size 200, the forward instructions should move forward 25 pixels(100 divided by 2 twice).
//You can use the InstructionList::setDistance() function to specify how far the Turtle should move on a FORWARD instruction. 
HilbertCurve::HilbertCurve(int level, int size) : turtle(size, size)
{
    //Append move ODD to InstructionList rules.
    rules.append(ODD);

    //Variables used for calculations. Needed to be type double.
    double l = level;
    double s = size;

    //Create unordered map with hilbert_t move as key and Instructionlist as mapped value. 
    unordered_map<hilbert_t, const InstructionList *> subRules;

    //InstructionList to hold odd substitution rules.
    InstructionList odd;
    const InstructionList *oddPtr = &odd;
    //O -> L, E, F, R, O, F, O, R, F, E, L
    odd.append(TURN_LEFT);
    odd.append(EVEN);
    odd.append(FORWARD);
    odd.append(TURN_RIGHT);
    odd.append(ODD);
    odd.append(FORWARD);
    odd.append(ODD);
    odd.append(TURN_RIGHT);
    odd.append(FORWARD);
    odd.append(EVEN);
    odd.append(TURN_LEFT);

    
    //InstructionList to hold even substitution rules.
    InstructionList even;
    const InstructionList *evenPtr = &even;
    //E -> R, O, F, L, E, F, E, L, F, O, R
    even.append(TURN_RIGHT);
    even.append(ODD);
    even.append(FORWARD);
    even.append(TURN_LEFT);
    even.append(EVEN);
    even.append(FORWARD);
    even.append(EVEN);
    even.append(TURN_LEFT);
    even.append(FORWARD);
    even.append(ODD);
    even.append(TURN_RIGHT);

    //Map odd list to hilbert_t enum ODD 
    //Map even list to hilber_t enum EVEN
    subRules[ODD] = oddPtr;
    subRules[EVEN] = evenPtr;

    //For loop to control how many times the substitution rules are applied. 
    for (int i = 0; i < level; i++)
    {
        rules.substitute(subRules);
    }

    //Set distance to (size/2^level).
    //For example, if we want a level 3 Hilbert curve of size 200, the forward instructions should move forward 25 pixels (100 divided by 2 twice).
    rules.setDistance(s/(pow (2, l)));
 
    //Call turtle follow passing the rules. 
    //Turle will follow the instructions and draw the curve.  
    turtle.follow(rules);

}

