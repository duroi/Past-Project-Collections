#include <iostream>
#include <unordered_map>
#include <cstring>
using namespace std;

#include "hilbert.h"
#include "hilbert.cpp"
#include "instruction_list.cpp"
#include "turtle.cpp"

const int HILBERT_LEVEL = 3;
const int IMAGE_SIZE = 200;
const string OUTPUT_FILE = "hilbert.bmp";

int main()
{
  HilbertCurve curve(HILBERT_LEVEL, IMAGE_SIZE);
  curve.writeToFile(OUTPUT_FILE);

  return 0;
}


 // g++ hilbert-driver.cpp hilbert.cpp hilbert.h turtle.cpp turtle.h instruction_list.cpp instruction_list.h