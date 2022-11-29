#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}
/*-----------------------------------------------------------------------**/
void utility::dualthres(image &src, image &tgt, int threshold, int v1, int v2)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i,j)-v2));
			}
			else if (src.getPixel(i,j) > threshold) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+v1));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::colorbright(image &src, image &tgt, int DR, int DG, int DB)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			
			tgt.setPixel(i,j,RED,checkValue(src.getPixel(i,j,0) * DR));
			tgt.setPixel(i,j,GREEN,checkValue(src.getPixel(i,j,1) * DG));
			tgt.setPixel(i,j,BLUE,checkValue(src.getPixel(i,j,2) * DB));

		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::colorvisual(image &src, image &tgt, int threshold, int v1)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (abs(v1 - (src.getPixel(i,j))) < threshold) {
				tgt.setPixel(i,j,RED,255);
				tgt.setPixel(i,j,GREEN,0);
				tgt.setPixel(i,j,BLUE,0);
			}else {
				tgt.setPixel(i,j,RED,src.getPixel(i,j));
				tgt.setPixel(i,j,GREEN,src.getPixel(i,j));
				tgt.setPixel(i,j,BLUE,src.getPixel(i,j));
			}
		}
	}
}


/*-----------------------------------------------------------------------**/
void utility::reg2dsmooth(image &src, image &tgt, int ws)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    	int border = (ws-1)/2;
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
            
            if ((i > border ) && (i < (src.getNumberOfRows() - border)) && (j > border) && (j < (src.getNumberOfColumns() - border))){
                int sum = 0;
                for(int k = (i - border); k < (i + border); k++){
                    for(int l = (j - border); l < (j + border); l++){
                        sum = sum + src.getPixel(i,j);
                    }
                }
                tgt.setPixel(i,j,checkValue(sum/(ws*ws)));
			}
            else {
                tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
            }
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::sep2dsmooth(image &src, image &tgt, int ws)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    	int border = (ws-1)/2;
        image temp;
        temp.copyImage(tgt);
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
            
            if ((i > border ) && (i < (src.getNumberOfRows() - border)) && (j > border) && (j < (src.getNumberOfColumns() - border))){
                int sum = 0;
                for(int k = (i - border); k < (i + border); k++){
                        sum = sum + src.getPixel(i,j);
                    }
                temp.setPixel(i,j,checkValue(sum/(ws)));
			}
            else {
                temp.setPixel(i,j,checkValue(src.getPixel(i,j)));
            }
	}
	

    for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
            
            if ((i > border ) && (i < (src.getNumberOfRows() - border)) && (j > border) && (j < (src.getNumberOfColumns() - border))){
                int sum = 0;
                for(int l = (j - border); l < (j + border); l++){
                        sum = sum + temp.getPixel(i,j);
                }

                tgt.setPixel(i,j,checkValue(sum/(ws)));
			}
            else {
                tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
            }
		}
	}
}
}
