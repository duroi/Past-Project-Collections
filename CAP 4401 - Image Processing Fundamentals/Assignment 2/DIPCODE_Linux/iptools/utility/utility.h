#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static int checkValueH(int value);
		static int checkValueS(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		
		static void dualthres(image &src, image &tgt, int threshold, int v1, int v2);
		static void reg2dsmooth(image &src, image &tgt, int ws);
		static void sep2dsmooth(image &src, image &tgt, int ws);
		static void colorbright(image &src, image &tgt, int DR, int DG, int DB);
		static void colorvisual(image &src, image &tgt, int threshhold, int v1);

		static void histostretch(image &src, image &tgt, int A, int B);
		static void althistostretch(image &src, image &tgt, int A, int B);
		static void histothres(image &src, image &tgt, int threshold, char* bf, int A, int B);
		static void colorstretch(image &src, image &tgt, char* channel, int A, int B);
		static void rgbtohsi(float &R, float &G, float &B);
		static void hsitorgb(float &H, float &S, float &I);
		static void hsistretch(image &src, image &tgt, char* channel, int A, int B);
		static void fullhsistretch(image &src, image &tgt, int A, int B);
		
		
		
};

#endif

