Igli Duro
U33766202

****This program was tested on the FSPrime Servers****

This software is architectured as follows. This software can work on grad server.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.



*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make

As a result you should get iptool in project/bin directory.

*** FUNCTIONS ***

1. Add intensity: add
Increase the intensity for a gray-level image.

2. Binarization: binarize
Binarize the pixels with the threshold.

3. Scaling: Scale
Reduce or expand the heigh and width with two scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.

4. Change color: colorbright
Multiples the rgb color channels based on input.
DR = red, DG = green, DB = blue

5. Add color: colorvisual
Change gray-level image pixels to red based off threshold and input value.
If |v1 - Intensity| < threshold, set pixel red channel to max

6. Smoothing: reg2dsmooth
Based on window sizee, ws, smoothen image by making pixel value = (sum of neighbors)/ws^2

7. Smoothing: sep2dsmooth
Different smoothing algorithm that does two passes of 1D smoothing, once across x axis and other across y with first pass feeding into second pass.


*** PARAMETERS FILE ***

There are for parameters:
1. the input file name;
2. the output file name;
3. the number of ROIs (regions of interest)
4. the starting pixel for ROI, x and y
5. the size of ROI, Sx and Sy
6. the name of the filter. Use "add", "binarize", "scale", "colorbright", "colorvisual", "reg2dsmooth", and "sep2dsmooth" for your filters;
7. the value for adding intensity, threshold value for binarize filter, the scaling factor for scale filter, the rgb multipliers for colorbright filter, 
the threshold and value for colorvisual filter, and the window size for smoothing filters


*** Run the program: ./iptool parameters.txt
