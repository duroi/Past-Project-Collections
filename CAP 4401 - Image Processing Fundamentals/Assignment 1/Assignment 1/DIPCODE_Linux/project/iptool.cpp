/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "../iptools/core.h"
#include <strings.h>
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
	char outfile[MAXLEN];
	char *pch;
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	
	while(fgets(str,MAXLEN,fp) != NULL) {
		pch = strtok(str, " ");
		src.read(pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		//get #roi
		int roiCount = atoi(strtok(NULL, " "));

		image temp;

		temp.copyImage(src);
		image regions[roiCount];
		ROI_s roi[roiCount];
		for (int s = 0; s < roiCount; s++) {
			

			//get x, y, Sx, Sy
			roi[s].x = atoi(strtok(NULL, " "));
			roi[s].y = atoi(strtok(NULL, " "));
			roi[s].Sx = atoi(strtok(NULL, " "));
			roi[s].Sy = atoi(strtok(NULL, " "));
			
			regions[s].resize(roi[s].Sx, roi[s].Sy);

			for (int i = 0; i < roi[s].Sx; i++){
				for(int j = 0; j < roi[s].Sy; j++){
					//copy pixel from temp using x and y as offset
					regions[s].setPixel(i,j,RED,temp.getPixel(i+roi[s].x,j+roi[s].y,RED));
					regions[s].setPixel(i,j,GREEN,temp.getPixel(i+roi[s].x,j+roi[s].y,GREEN));
					regions[s].setPixel(i,j,BLUE,temp.getPixel(i+roi[s].x,j+roi[s].y,BLUE));
				}
			}

			//roi copied to src, program behaves as before
			src.copyImage(regions[s]);
		
			//get function
			pch = strtok(NULL, " ");
			if (strncasecmp(pch,"add",MAXLEN)==0) {
				/* Add Intensity */
				pch = strtok(NULL, " ");
					utility::addGrey(src,tgt,atoi(pch));
			}

			else if (strncasecmp(pch,"colorbright",MAXLEN)==0){
				/* colorbright Smoothing */
				int DR = atoi(strtok(NULL, " "));
				int DG = atoi(strtok(NULL, " "));
				int DB = atoi(strtok(NULL, " "));
				utility::colorbright(src, tgt, DR, DG, DB);
			}

			else if (strncasecmp(pch,"colorvisual",MAXLEN)==0){
				/* colorvisual  */
				int t = atoi(strtok(NULL, " "));
				int v1 = atoi(strtok(NULL, " "));
				utility::colorvisual(src, tgt, t, v1);
			}

			else if (strncasecmp(pch,"reg2dsmooth",MAXLEN)==0){
				/* regular 2d smoothing */
				int ws = atoi(strtok(NULL, " "));
				utility::reg2dsmooth(src, tgt, ws);
			}
			else if (strncasecmp(pch,"sep2dsmooth",MAXLEN)==0){
				/* seperable 2d smoothing */
				int ws = atoi(strtok(NULL, " "));
				utility::sep2dsmooth(src, tgt, ws);
			}
			else if (strncasecmp(pch,"binarize",MAXLEN)==0) {
				/* Thresholding */
				pch = strtok(NULL, " ");
				utility::binarize(src,tgt,atoi(pch));
			}

			else if (strncasecmp(pch,"scale",MAXLEN)==0) {
				/* Image scaling */
				pch = strtok(NULL, " ");
				utility::scale(src,tgt,atof(pch));
			}

			else {
				printf("No function: %s\n", pch);
				continue;
			}
			//copy tgt to regions array
			regions[s].copyImage(tgt);
		}

		tgt.copyImage(temp);

		for(int s = roiCount-1; s >= 0; s--){
			for(int i = 0; i < roi[s].Sx; i++){
				for(int j = 0; j < roi[s].Sy; j++){
					tgt.setPixel(i+roi[s].x,j+roi[s].y,RED,regions[s].getPixel(i,j,RED));	
					tgt.setPixel(i+roi[s].x,j+roi[s].y,GREEN,regions[s].getPixel(i,j,GREEN));	
					tgt.setPixel(i+roi[s].x,j+roi[s].y,BLUE,regions[s].getPixel(i,j,BLUE));	
				}
			}
		}

       
		tgt.save(outfile);
	}
		
      	fclose(fp);
	return 0;
}

