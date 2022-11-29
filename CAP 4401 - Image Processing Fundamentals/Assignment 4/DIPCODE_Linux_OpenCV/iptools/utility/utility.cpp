#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

#define MAXH 359
#define MINH 0

#define MAXS 100
#define MINS 0

using namespace cv;

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

int utility::checkValueH(int value)
{
	if (value > MAXH)
		return MAXH;
	if (value < MINH)
		return MINH;
	return value;
}
int utility::checkValueS(int value)
{
	if (value > MAXS)
		return MAXS;
	if (value < MINS)
		return MINS;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::rgbtohsi(float &Rf, float &Gf, float &Bf)
{

	float r, g, b, H, S, I, h, s, i, pi;
	pi = atan(1)*4;

	//normalize rgb	
	r = (Rf)/(Rf+Gf+Bf);
	g = (Gf)/(Rf+Gf+Bf);
	b = (Bf)/(Rf+Gf+Bf);
	
	
	//float test = r+g+b; 
	
	//cout << r << " " << g << " " << b << endl;
	//cout << test << endl;
	//cout << pi << endl;
	


	if (b <= g){
		h = acos((0.5*((r-g)+(r-b))/pow(pow((r-g),2)+(r-b)*(g-b), 0.5)));

	}
	else {
		h = 2*pi - acos((0.5*((r-g)+(r-b))/pow(pow((r-g),2)+(r-b)*(g-b), 0.5)));

	}

	s = 1 - 3*min(min(r,g),b);
	i = (Rf+Gf+Bf)/(3*255);

	if (isnan(h)) {
		h = 0;
	}

	if (isnan(s)) {
		s = 0;
	}

	if (isnan(i)) {
		i = 0;
	}


	H = h*(180/pi);
	S = s*100;
	I = i*255;

	//cout << pi << " " << r << " " << g << " " << b << endl;
	//cout << "h: " << h << " s: " << s << " i: " << i << endl;
	//cout << "H: " << H << " S: " << S << " I: " << I << endl;
	
	if (!(0 <= H <= 360)){
		cout << "Error: H out of range: ";
		cout << H;
		exit(-1);
	}
	if (!(0 <= S <= 100)){
		cout << "Error: S out of range: ";
		cout << S;
		exit(-1);
	}
	if (!(0 <= I <= 255)){
		cout << "Error: I out of range: ";
		cout << I;
		exit(-1);
	}

	//cout << "==RGB TO HSI==" << endl;
	//cout << "RGB: (" << Rf << "," << Gf << "," << Bf << ")" << endl;
	//cout << "HSI: (" << H << "," << S << "," << I << ")" << endl;
	//cout << "==============" << endl;

	Rf = H;
	Gf = S;
	Bf = I;

}

void utility::hsitorgb(float &H, float &S, float &I)
{
	//cout << "start hsi" << endl;
	float r, g, b, Rf, Gf, Bf, h, s, i, pi;
	pi = atan(1)*4;
		
	h = H * (pi/180);
	s = S / 100;
	i = I / 255;
	
	if ( 0 <= h < (2*pi/3)) {

		b = i * (1 - s);
		r = i * (1 + ((s*cos(h))/(cos(pi/(3-h)))));
		g = (3*i) - (b+r);


	}
	else if ((2*pi/3) <= h < (4*pi/3)) {
		
		h = h - (2*pi/3);	

		r = i * (1 - s);
		g = i * (1 + ((s*cos(h))/(cos(pi/(3-h)))));
		b = (3*i) - (g+r);
		
	}

	else if ((4*pi/3) <= h < (2*pi)){
		
		h = h - (4*pi/3);

		g = i * (1 - s);
		b = i * (1 + ((s*cos(h))/(cos(pi/(3-h)))));
		r = (3*i) - (b+g);

	}

	else {
		cout << "this shouldn't happen" << endl;
	}


	Rf = r * 255;
	Gf = g * 255;
	Bf = b * 255;

	if (!(0 <= Rf <= 360)){
		cout << "Error: Rf out of range: ";
		cout << Rf;
		exit(-1);
	}
	if (!(0 <= Gf <= 100)){
		cout << "Error: Gf out of range: ";
		cout << Gf;
		exit(-1);
	}
	if (!(0 <= Bf <= 255)){
		cout << "Error: Bf out of range: ";
		cout << Bf;
		exit(-1);
	}
	//cout << "h: " << h << " s: " << s << " i: " << i << endl;
	//cout << "H: " << H << " S: " << S << " I: " << I << endl;
	//cout << "==HSI TO RGB==" << endl;
	//cout << "HSI: (" << H << "," << S << "," << I << ")" << endl;
	//cout << "RGB: (" << Rf << "," << Gf << "," << Bf << ")" << endl;
	//cout << "=============" << endl;

	H = Rf;
	S = Gf;
	I = Bf;

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
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
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

/*-----------------------------------------------------------------------**/
void utility::histostretch(image &src, image &tgt, int A, int B)
{
	auto start = chrono::steady_clock::now();

	int histCount[256] = {};
	float hcNorm[256] = {};
	int Imin = 255;
	int Imax = 0;
	int intensity;
	int highestCount;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			//Get intensity
			intensity = src.getPixel(i,j);

			//Increment count
			histCount[intensity] += 1;
			

			//Compare for new max, min, and highest frequency.
			if (intensity > Imax) {
				Imax = intensity;
			}
			
			if (intensity < Imin) {
				Imin = intensity;
			}
			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}

			
		}
	}

	//histogram stretching
	
	//cout << "min: " << Imin << " | max: " << Imax << endl;
	//cout << highestCount << endl;
	int newP;
	int p;
	float Af = A;
	float Bf = B;
	float Cf = Imin;
	float Df = Imax;
	float Pf, newPf;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			p = src.getPixel(i,j);
			
			Pf = p;
				
			newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
			newP = newPf;
	
			//cout << p << ":" << newP << endl;

			tgt.setPixel(i,j,checkValue(newP));

	
		}
	}

	//cout << "A: " << A << " B: " << B << " C: " << Imin << " D: " << Imax << endl;
    auto end = chrono::steady_clock::now();
 
    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;
 
	
	
}


/*-----------------------------------------------------------------------**/
void utility::althistostretch(image &src, image &tgt, int A, int B)
{

	int histCount[256] = {};
	float hcNorm[256] = {};
	int Imin = 255;
	int Imax = 0;
	int intensity;
	int highestCount;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			//Get intensity
			intensity = src.getPixel(i,j);

			//Increment count
			histCount[intensity] += 1;
			

			//Compare for new max, min, and highest frequency.
			if (intensity > Imax) {
				Imax = intensity;
			}
			
			if (intensity < Imin) {
				Imin = intensity;
			}
			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}

			
		}
	}

	//histogram stretching
	
	//cout << "min: " << Imin << " | max: " << Imax << endl;
	//cout << highestCount << endl;
	int newP;
	int p;
	float Af = A;
	float Bf = B;
	float Cf = Imin * 1.05;
	float Df = Imax * 0.95;
	float Pf, newPf;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			p = src.getPixel(i,j);
			
			Pf = p;
				
			newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
			newP = newPf;
	
			//cout << p << ":" << newP << endl;

			tgt.setPixel(i,j,checkValue(newP));

	
		}
	}

	//cout << "A: " << A << " B: " << B << " C: " << Imin << " D: " << Imax << endl;
 

}


/*-----------------------------------------------------------------------**/
void utility::histothres(image &src, image &tgt, int threshold, char* bf, int A, int B)
{

	int histCount[256] = {};
	float hcNorm[256] = {};
	int IminF = 255;
	int ImaxF = 0;
	int IminB = 255;
	int ImaxB = 0;
	int Imin = 255;
	int Imax = 0;

	int intensity;
	int highestCount;
	
	image backFore;
	backFore.copyImage(src);
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			//Get intensity
			intensity = src.getPixel(i,j);

			//Increment count
			histCount[intensity] += 1;
			//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}
	
			if (intensity >= threshold) {
				backFore.setPixel(i,j,0);
				//Compare for new max, min, and highest frequency.
				if (intensity > ImaxF) {
					ImaxF = intensity;
				}
			
				if (intensity < IminF) {
					IminF = intensity;
				}
			
			}
			else{
				backFore.setPixel(i,j,255);
				//Compare for new max, min, and highest frequency.
				if (intensity > ImaxB) {
					ImaxB = intensity;
				}
			
				if (intensity < IminB) {
					IminB = intensity;
				}

		
			}

			
		}
	}

	//histogram stretching
	
	//cout << "min: " << Imin << " | max: " << Imax << endl;
	//cout << highestCount << endl;
	int newP;
	int p;
	float Af = A;
	float Bf = B;
	float Cf;
	float Df;
	float Pf, newPf;

	if (bf[0] == 'F') {
		Cf = IminF;
		Df = ImaxF;
		Imax = ImaxF;
		Imin = IminF;
	}
	if (bf[0] == 'B') {
		Cf = IminB;
		Df = ImaxB;
		Imax = ImaxB;
		Imin = IminB;

	}


	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			if (bf[0] == 'F') {
				if (backFore.getPixel(i,j) == 255) {
		

					p = src.getPixel(i,j);
			
					Pf = p;
				
					newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
					newP = newPf;
	
					//cout << p << ":" << newP << endl;

					tgt.setPixel(i,j,checkValue(newP));

				}
			}

			if (bf[0] == 'B') {
				if (backFore.getPixel(i,j) == 0) {
		

					p = src.getPixel(i,j);
			
					Pf = p;
				
					newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
					newP = newPf;
	
					//cout << p << ":" << newP << endl;

					tgt.setPixel(i,j,checkValue(newP));
				}
			}

	
		}
	}

	//cout << "A: " << A << " B: " << B << " C: " << Imin << " D: " << Imax << endl;


	backFore.save("BFmap.pgm");

}


/*-----------------------------------------------------------------------**/
void utility::colorstretch(image &src, image &tgt, char* c, int A, int B)
{

	int histCount[256] = {};
	float hcNorm[256] = {};
	int Imin = 255;
	int Imax = 0;
	int channel;
	int intensity;
	int highestCount;

	cout << "Channel: " << c << " equals ";

	if (c[0] == 'R'){
		channel = 0;
	cout << "RED" << endl;
	}
	else if (c[0] == 'G'){
		channel = 1;
	cout << "GREEN" << endl;
	}
	else if (c[0] == 'B'){
		channel = 2;
	cout << "BLUE" << endl;
	}
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			if (channel == 0) {

				//Get intensity
				intensity = src.getPixel(i,j,RED);
			
				//Increment count
				histCount[intensity] += 1;

				//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

				
			}

			if (channel == 1) {

				//Get intensity
				intensity = src.getPixel(i,j,GREEN);
			
				//Increment count
				histCount[intensity] += 1;

				//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

				
			}

			if (channel == 2) {

				//Get intensity
				intensity = src.getPixel(i,j,BLUE);
			
				//Increment count
				histCount[intensity] += 1;

				//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

				
			}

			
			//Increment count
			histCount[intensity] += 1;

			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}
			
		}
	}

	//histogram stretching
	
	//cout << "min: " << Imin << " | max: " << Imax << endl;
	//cout << highestCount << endl;
	int newP;
	int p;
	float Af = A;
	float Bf = B;
	float Cf = Imin;
	float Df = Imax;
	float Pf, newPf;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			if (channel == 0) {

	
				p = src.getPixel(i,j,RED);
			
				Pf = p;
				
				newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
				newP = newPf;
	
				//cout << p << ":" << newP << endl;

				tgt.setPixel(i,j,RED, checkValue(newP));
				tgt.setPixel(i,j,GREEN, src.getPixel(i,j,GREEN));
				tgt.setPixel(i,j,BLUE, src.getPixel(i,j,BLUE));

			}

			if (channel == 1) {

	
				p = src.getPixel(i,j,GREEN);
			
				Pf = p;
				
				newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
				newP = newPf;
	
				//cout << p << ":" << newP << endl;

				tgt.setPixel(i,j,GREEN, checkValue(newP));
				tgt.setPixel(i,j,RED, src.getPixel(i,j,RED));
				tgt.setPixel(i,j,BLUE, src.getPixel(i,j,BLUE));

			}


			if (channel == 2) {

	
				p = src.getPixel(i,j,BLUE);
			
				Pf = p;
				
				newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
				newP = newPf;
	
				//cout << p << ":" << newP << endl;

				tgt.setPixel(i,j,BLUE, checkValue(newP));
				tgt.setPixel(i,j,GREEN, src.getPixel(i,j,GREEN));
				tgt.setPixel(i,j,RED, src.getPixel(i,j,RED));

			}


		
	
		}
	}

	cout << "A: " << A << " B: " << B << " C: " << Imin << " D: " << Imax << endl;

}



/*-----------------------------------------------------------------------**/
void utility::hsistretch(image &src, image &tgt, char* c, int A, int B)
{

	int histCount[256] = {};
	float hcNorm[256] = {};
	int Imin = 255;
	int Imax = 0;
	int channel;
	int intensity;
	int highestCount;

	cout << "Channel: " << c << " equals ";

	if (c[0] == 'H'){
		channel = 0;
	cout << "HUE" << endl;
	}
	else if (c[0] == 'S'){
		channel = 1;
	cout << "SATURATION" << endl;
	}
	else if (c[0] == 'I'){
		channel = 2;
	cout << "INTENSITY" << endl;
	}

	image temp;
	temp.copyImage(src);

	float Hf, Sf, If;
	int H, S, I;
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			Hf = src.getPixel(i,j,RED);
			Sf = src.getPixel(i,j,GREEN);
			If = src.getPixel(i,j,BLUE);
			
			rgbtohsi(Hf,Sf,If);
			H = Hf;
			S = Sf;
			I = If;
	
			temp.setPixel(i,j,RED, H);
			temp.setPixel(i,j,GREEN, S);
			temp.setPixel(i,j,BLUE, I);

			if (channel == 0) {

				//Get intensity
				intensity = temp.getPixel(i,j,RED);
			
				//Increment count
				histCount[intensity] += 1;

				//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

				
			}

			if (channel == 1) {

				//Get intensity
				intensity = temp.getPixel(i,j,GREEN);
			
				//Increment count
				histCount[intensity] += 1;

				//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

				
			}

			if (channel == 2) {

				//Get intensity
				intensity = temp.getPixel(i,j,BLUE);
			
				//Increment count
				histCount[intensity] += 1;

				//Compare for new max, min, and highest frequency.
				if (intensity > Imax) {
					Imax = intensity;
				}
			
				if (intensity < Imin) {
					Imin = intensity;
				}

				
			}

			
			//Increment count
			histCount[intensity] += 1;

			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}
			
		}
	}

	//histogram stretching
	
	cout << "min: " << Imin << " | max: " << Imax << endl;
	cout << highestCount << endl;
	int newP;
	int p;
	float Af = A;
	float Bf = B;
	float Cf = Imin;
	float Df = Imax;
	float Pf, newPf;
	int red, green, blue;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			if (channel == 0) {

	
				p = temp.getPixel(i,j,RED);
			
				Pf = p;
				
				newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
				newP = newPf;
				
				newP = checkValueH(newP);
				
				Hf = newP;
				Sf = temp.getPixel(i,j,GREEN);
				If = temp.getPixel(i,j,BLUE);
				hsitorgb(Hf,Sf,If);
				red = Hf;
				green = Sf;
				blue = If;
		
				
				//cout << p << ":" << newP << endl;

				tgt.setPixel(i,j,RED, checkValue(red));
				tgt.setPixel(i,j,GREEN, checkValue(green));
				tgt.setPixel(i,j,BLUE, checkValue(blue));

			}

			if (channel == 1) {

	
				p = temp.getPixel(i,j,GREEN);
			
				Pf = p;
				
				newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
				newP = newPf;
	
				newP = checkValueS(newP);
				
				Hf = newP;
				Sf = temp.getPixel(i,j,GREEN);
				If = temp.getPixel(i,j,BLUE);
				hsitorgb(Hf,Sf,If);
				red = Hf;
				green = Sf;
				blue = If;
		
				
				//cout << p << ":" << newP << endl;

				tgt.setPixel(i,j,RED, checkValue(red));
				tgt.setPixel(i,j,GREEN, checkValue(green));
				tgt.setPixel(i,j,BLUE, checkValue(blue));

			}


			if (channel == 2) {

	
				p = temp.getPixel(i,j,BLUE);
			
				Pf = p;
				
				newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
				newP = newPf;
	
				newP = checkValue(newP);
				
				Hf = newP;
				Sf = temp.getPixel(i,j,GREEN);
				If = temp.getPixel(i,j,BLUE);
				hsitorgb(Hf,Sf,If);
				red = Hf;
				green = Sf;
				blue = If;
		
				
				//cout << p << ":" << newP << endl;

				tgt.setPixel(i,j,RED, checkValue(red));
				tgt.setPixel(i,j,GREEN, checkValue(green));
				tgt.setPixel(i,j,BLUE, checkValue(blue));
			}


		
	
		}
	}

	cout << "A: " << A << " B: " << B << " C: " << Imin << " D: " << Imax << endl;

}



/*-----------------------------------------------------------------------**/
void utility::sobel3(image &src, image &tgt)
{

	image temp;
	temp.copyImage(src);


	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    	int border = 1;
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
            
            		if ((i > border ) && (i < (src.getNumberOfRows() - border)) && (j > border) && (j < (src.getNumberOfColumns() - border)))
			{
                			int Gx = 0;
				int Gy = 0;
				unsigned int intensity = 0;

				//left column
				intensity = src.getPixel(i-1,j-1);
				Gx += -intensity;
				Gy += -intensity;
			
				intensity = src.getPixel(i-1,j);
				Gx += -2*intensity;
			
				intensity = src.getPixel(i-1,j+1);
				Gx += -intensity;
				Gy += intensity;
			

				//center column
				intensity = src.getPixel(i,j-1);
				Gy += -2*intensity;
			
				intensity = src.getPixel(i,j+1);
				Gy += 2*intensity;

				//right column
				intensity = src.getPixel(i+1,j-1);
				Gx += intensity;
				Gy += -intensity;
			
				intensity = src.getPixel(i+1,j);
				Gx += 2*intensity;
			
				intensity = src.getPixel(i+1,j+1);
				Gx += intensity;
				Gy += intensity;
				
				unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
				length = (unsigned int)((float)length/5.7);	
				//cout << length << endl;		
               			temp.setPixel(i,j,(int)length);
				
			}
			else 
			{
                		tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
            			}
		}
	}



	int histCount[256] = {};
	float hcNorm[256] = {};
	int Imin = 255;
	int Imax = 0;
	int intensity;
	int highestCount;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			//Get intensity
			intensity = temp.getPixel(i,j);

			//Increment count
			histCount[intensity] += 1;
			

			//Compare for new max, min, and highest frequency.
			if (intensity > Imax) {
				Imax = intensity;
			}
			
			if (intensity < Imin) {
				Imin = intensity;
			}
			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}

			
		}
	}

	//histogram stretching
	
	cout << "min: " << Imin << " | max: " << Imax << endl;
	//cout << highestCount << endl;
	int newP;
	int p;
	float Af = 0;
	float Bf = 255;
	float Cf = Imin;
	float Df = Imax;
	float Pf, newPf;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			p = temp.getPixel(i,j);
			
			Pf = p;
				
			newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
			newP = newPf;
	
			//cout << p << ":" << newP << endl;

			tgt.setPixel(i,j,checkValue(newP));

	
		}
	}
}




/*-----------------------------------------------------------------------**/
void utility::sobel5(image &src, image &tgt)
{

	image temp;
	temp.copyImage(src);


	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
    	int border = 2;
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
            
            		if ((i > border ) && (i < (src.getNumberOfRows() - border)) && (j > border) && (j < (src.getNumberOfColumns() - border)))
			{
                			int Gx = 0;
				int Gy = 0;
				unsigned int intensity = 0;

				//1st column
				intensity = src.getPixel(i-2,j-2);
				Gx += -5*intensity;
				Gy += -5*intensity;
				
				intensity = src.getPixel(i-2,j-1);
				Gx += -8*intensity;
				Gy += -4*intensity;

				intensity = src.getPixel(i-2,j);
				Gx += -10*intensity;

				intensity = src.getPixel(i-2,j+1);
				Gx += -8*intensity;
				Gy += 4*intensity;

				intensity = src.getPixel(i-2,j+2);
				Gx += -5*intensity;
				Gy += 5*intensity;

				//2nd column
				intensity = src.getPixel(i-1,j-2);
				Gx += -4*intensity;
				Gy += -8*intensity;
				
				intensity = src.getPixel(i-1,j-1);
				Gx += -10*intensity;
				Gy += -10*intensity;

				intensity = src.getPixel(i-1,j);
				Gx += -20*intensity;

				intensity = src.getPixel(i-1,j+1);
				Gx += -10*intensity;
				Gy += 10*intensity;

				intensity = src.getPixel(i-1,j+2);
				Gx += -4*intensity;
				Gy += 8*intensity;

				//3rd column
				intensity = src.getPixel(i,j-2);
				Gy += -10*intensity;
				
				intensity = src.getPixel(i,j-1);
				Gy += -20*intensity;

				intensity = src.getPixel(i,j+1);
				Gy += 20*intensity;

				intensity = src.getPixel(i,j+2);
				Gy += 10*intensity;

				//4th column
				intensity = src.getPixel(i+1,j-2);
				Gx += 4*intensity;
				Gy += -8*intensity;
				
				intensity = src.getPixel(i+1,j-1);
				Gx += 10*intensity;
				Gy += -10*intensity;

				intensity = src.getPixel(i+1,j);
				Gx += 20*intensity;

				intensity = src.getPixel(i+1,j+1);
				Gx += 10*intensity;
				Gy += 10*intensity;

				intensity = src.getPixel(i+1,j+2);
				Gx += 4*intensity;
				Gy += 8*intensity;

				//5th column
				intensity = src.getPixel(i+2,j-2);
				Gx += 5*intensity;
				Gy += -5*intensity;
				
				intensity = src.getPixel(i+2,j-1);
				Gx += 8*intensity;
				Gy += -4*intensity;

				intensity = src.getPixel(i+2,j);
				Gx += 10*intensity;

				intensity = src.getPixel(i+2,j+1);
				Gx += 8*intensity;
				Gy += 4*intensity;

				intensity = src.getPixel(i+2,j+2);
				Gx += 5*intensity;
				Gy += 5*intensity;
			
				
				unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
				length = (unsigned int)((float)length/118.8);	
				//cout << length << endl;		
               			temp.setPixel(i,j,(int)length);
				
			}
			else 
			{
                		tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
            			}
		}
	}



	int histCount[256] = {};
	float hcNorm[256] = {};
	int Imin = 255;
	int Imax = 0;
	int intensity;
	int highestCount;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{

			//Get intensity
			intensity = temp.getPixel(i,j);

			//Increment count
			histCount[intensity] += 1;
			

			//Compare for new max, min, and highest frequency.
			if (intensity > Imax) {
				Imax = intensity;
			}
			
			if (intensity < Imin) {
				Imin = intensity;
			}
			
			if (histCount[intensity] > highestCount) {
				highestCount = histCount[intensity];
			}

			
		}
	}

	//histogram stretching
	
	cout << "min: " << Imin << " | max: " << Imax << endl;
	//cout << highestCount << endl;
	int newP;
	int p;
	float Af = 0;
	float Bf = 255;
	float Cf = Imin;
	float Df = Imax;
	float Pf, newPf;

	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			p = temp.getPixel(i,j);
			
			Pf = p;
				
			newPf = ((Pf - Cf)*((Bf-Af)/(Df-Cf)) + Af);
			
			newP = newPf;
	
			//cout << p << ":" << newP << endl;

			tgt.setPixel(i,j,checkValue(newP));

	
		}
	}
}



/*-----------------------------------------------------------------------**/
void utility::cv_gray(Mat &src, Mat &tgt)
{
	cvtColor(src, tgt, COLOR_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::cv_avgblur(Mat &src, Mat &tgt, int WindowSize)
{
	blur(src,tgt,Size(WindowSize,WindowSize));
}


/*-----------------------------------------------------------------------**/
void utility::histostretchcv(Mat &src, Mat &tgt)
{
	if (src.channels() > 1){
		cvtColor(src, src, COLOR_BGR2GRAY);
	}

    	auto start = chrono::steady_clock::now();
	normalize(src, tgt, 0.0, 255.0, NORM_MINMAX );
    	auto end = chrono::steady_clock::now();

    
    	cout << "Elapsed time in milliseconds: "
        	<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
        	<< " ms" << endl;
 
}
/*-----------------------------------------------------------------------**/
void utility::histoequalcv(Mat &src, Mat &tgt)
{
	if (src.channels() > 1){
		cvtColor(src, src, COLOR_BGR2GRAY);
	}
    	auto start = chrono::steady_clock::now();
	equalizeHist(src, tgt);
    	auto end = chrono::steady_clock::now();

     
    	cout << "Elapsed time in milliseconds: "
        	<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
        	<< " ms" << endl;
 

}
/*-----------------------------------------------------------------------**/
//Hough Circle Transform structrue sourced from OpenCV tutorial page 
// https://docs.opencv.org/4.x/da/d53/tutorial_py_houghcircles.html
void utility::houghtrans(Mat &src, Mat &tgt)
{
	cannycv(src,src);
	Mat gray = src.clone();


	GaussianBlur(gray, gray, Size(9,9), 2, 2);

	vector<Vec3f> circles;

	HoughCircles(gray, circles, HOUGH_GRADIENT, 2, gray.rows/4, 200, 100);
	for(size_t i =0; i < circles.size(); i++){
 		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         		int radius = cvRound(circles[i][2]);
        		 // draw the circle center
      		circle(src, center, 3, Scalar(255,255,255), -1, 8, 0 );
        		// draw the circle outline
         		circle(src, center, radius, Scalar(255,255,255), 3, 8, 0 );
    	}
	tgt = src.clone();
}
/*-----------------------------------------------------------------------**/
void utility::hesobel(Mat &src, Mat &tgt)
{
	Mat temp;
	histoequalcv(src, temp);
	Sobel(temp, tgt, CV_8U, 1, 1, 3);

}
/*-----------------------------------------------------------------------**/
void utility::sobelcv(Mat &src, Mat &tgt)
{
	if (src.channels() > 1){
		cvtColor(src, src, COLOR_BGR2GRAY);
	}

	Sobel(src, tgt, CV_8U, 1, 1, 3);

}

/*-----------------------------------------------------------------------**/
void utility::hecanny(Mat &src, Mat &tgt)
{
	Mat temp;
	histoequalcv(src, temp);
	Canny(temp, tgt, 100, 200, 3, false);
}
/*-----------------------------------------------------------------------**/
void utility::cannycv(Mat &src, Mat &tgt)
{
	if (src.channels() > 1){
		cvtColor(src, src, COLOR_BGR2GRAY);
	}
	Canny(src, tgt, 100, 200, 3, false);
}

/*-----------------------------------------------------------------------**/

void utility::qrdecode(Mat &src, Mat &tgt)
{

}


/*-----------------------------------------------------------------------**/

void utility::hesobeldiff(Mat &src, Mat &tgt)
{
	Mat src1 = src.clone();
	Mat src2 = src.clone();
	Mat empty;	
	Mat temp1;
	Mat temp2;
	hesobel(src1, temp1);
	sobelcv(src2, temp2);
	subtract(temp1, temp2, tgt, empty, -1);

}
/*-----------------------------------------------------------------------**/
void utility::hecannydiff(Mat &src, Mat &tgt)
{
	Mat src1 = src.clone();
	Mat src2 = src.clone();
	Mat empty;	
	Mat temp1;
	Mat temp2;
	hecanny(src1, temp1);
	cannycv(src2, temp2);
	subtract(temp1, temp2, tgt, empty, -1);
}

