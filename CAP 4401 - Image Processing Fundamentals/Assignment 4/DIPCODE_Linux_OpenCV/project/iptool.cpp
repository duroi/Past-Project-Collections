#include "../iptools/core.h"
#include <string.h>

using namespace std;

#define MAXLEN 256

struct ROI_s{
	int x;
	int y;
	int Sx;
	int Sy;
};

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	char str[MAXLEN];
	char infile[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	cout << "Here 1" << endl;

	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}
	
	while(fgets(str,MAXLEN,fp) != NULL) {
		if (strncmp(str,"#",1)==0) continue;
		int NumParameters = 0;
		
		pch = strtok(str, " ");
		strcpy(infile, pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		pch = strtok(NULL, " ");
		if (strncmp(pch,"opencv",6)==0) {
			cv::Mat I = cv::imread(infile);
			cv::Mat I2;
			
			if( I.empty()) {
				cout << "Could not open or find the image: " << infile << endl;
				return -1;
			}
			
			cv::Mat temp = I.clone();
			cv::cvtColor(temp, temp, cv::COLOR_BGR2GRAY);
			int roiCount = atoi(strtok(NULL, " "));
			cv::Mat regions[roiCount];
			ROI_s roi[roiCount];
			for (int s = 0; s < roiCount; s++) {
				roi[s].x = atoi(strtok(NULL, " "));
				roi[s].y = atoi(strtok(NULL, " "));
				roi[s].Sx = atoi(strtok(NULL, " "));
				roi[s].Sy = atoi(strtok(NULL, " "));
				regions[s] = temp(cv::Rect(roi[s].x,roi[s].y,roi[s].Sx,roi[s].Sy)).clone();
				I = regions[s].clone();
			
				pch = strtok(NULL, " ");
				if (strncmp(pch,"gray",4)==0) {
					utility::cv_gray(I, I2);
				}
				else if (strncmp(pch,"blur_avg",8)==0) {
					pch = strtok(NULL, " ");
					utility::cv_avgblur(I, I2, atoi(pch));
				}
				else if (strncmp(pch,"histostretchcv",14)==0) { 
					pch = strtok(NULL, " ");
					utility::histostretchcv(I, I2);
				}
				else if (strncmp(pch,"histoequalcv",12)==0) {
					pch = strtok(NULL, " ");
					utility::histoequalcv(I, I2);
				}
				else if (strncmp(pch,"houghtrans",10)==0) { 
					pch = strtok(NULL, " ");
					utility::houghtrans(I, I2);
				}
				else if (strncmp(pch,"hesobel",7)==0) {
					pch = strtok(NULL, " ");
					utility::hesobel(I, I2);
				}
				else if (strncmp(pch,"hecanny",7)==0) { 
					pch = strtok(NULL, " ");
					utility::hecanny(I, I2);
				}
				else if (strncmp(pch,"sobelcv",7)==0) {
					pch = strtok(NULL, " ");
					utility::sobelcv(I, I2);
				}
				else if (strncmp(pch,"cannycv",7)==0) { 
					pch = strtok(NULL, " ");
					utility::cannycv(I, I2);
				}

				else if (strncmp(pch,"hesobeldiff",11)==0) {
					pch = strtok(NULL, " ");
					utility::hesobeldiff(I, I2);
				}
				else if (strncmp(pch,"hecannydiff",11)==0) { 
					pch = strtok(NULL, " ");
					utility::hecannydiff(I, I2);
				}

				else if (strncmp(pch,"qrdecode",8)==0) { 
					pch = strtok(NULL, " ");
					utility::qrdecode(I, I2);
				}
				else {
					printf("No function: %s\n", pch);
					continue;
				}
				regions[s] = I2.clone();
			}
			//cout<< "test" << endl;
			I2 = temp.clone();
			//cout << I2.channels() << endl;
			for(int s = roiCount-1; s >= 0; s--){
				regions[s].copyTo(I2(cv::Rect(roi[s].x,roi[s].y,roi[s].Sx,roi[s].Sy)));
				//cout <<regions[s].channels() <<endl;
			}
			
			cout << "write file: start" << endl;
			cv::imwrite(outfile, I2);
			cout << "write file: end" << endl;
		}
		else {
			src.read(infile);
			if (strncmp(pch,"add",3)==0) {
				pch = strtok(NULL, " ");
				utility::addGrey(src,tgt,atoi(pch));
			}

			else if (strncmp(pch,"binarize",8)==0) {
				pch = strtok(NULL, " ");
				utility::binarize(src,tgt,atoi(pch));
			}

			else if (strncmp(pch,"scale",5)==0) {
				pch = strtok(NULL, " ");
				utility::scale(src,tgt,atof(pch));
			}
 			else if (strncasecmp(pch,"histostretch",13)==0){
                    		/* Histogram Stretching */
                    		int A = 0;                  		
				int B = 255;
                    		utility::histostretch(src, tgt, A, B);
			}
			else {
				printf("No function: %s\n", pch);
				continue;
			}
			
			tgt.save(outfile);
		}
	}
	fclose(fp);
	return 0;
}
