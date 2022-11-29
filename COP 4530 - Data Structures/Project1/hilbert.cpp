// COP 4530
// IGLI DURO U#3376-6202 (NAVIGATOR) 
// AUSTYN MIKOLON (DRIVER)

#include "hilbert.h"
#include <math.h> 


HilbertCurve::HilbertCurve(int level, int size) : turtle(size, size)
{

//this function initializes an InstructionList and Turtle to draw a Hilbert curve of the given level and size.  
//The level represents the number of times to apply the substitution rules (starting from the list [ODD]),
//While the size represents the total size (in pixels) of the Hilbert curve to output.  
//When drawing a Hilbert curve to fit a certain size, a level 1 curve moves forward a distance equal to half the size, 
//and each successive level moves forward half as much.  For example, if we want a level 3 Hilbert curve of size 200, the forward instructions should move forward 25 pixels 
//(100 divided by 2 twice).  You can use the InstructionList::setDistance() function to specify how far the Turtle should move on a FORWARD instruction.

    rules.append(ODD);
    
    unordered_map<hilbert_t, const InstructionList*> subRules;
    
    InstructionList odd;
    const InstructionList* oddPtr = &odd;
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

    InstructionList even;
    const InstructionList* evenPtr = &even;
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

    subRules[ODD] = oddPtr;
    subRules[EVEN] = evenPtr;


    for (int i = 0; i < level; i++)
    {
        cout << " test: " << i << endl;
        rules.substitute(subRules);
        //cout << rules << endl;
    }

    double d = (static_cast<double>(size) / (pow(2.0,(static_cast<double>(level)))));

    cout << d << endl; 
    rules.setDistance(d);
   
    turtle.follow(rules);
    cout << "test";
}
