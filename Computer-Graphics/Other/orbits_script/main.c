
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float radianos(float graus) {
	return (graus * M_PI) / 180;
}

int main (int argc, char const *argv[]) {

	if (argc < 3) {
		printf("./main RADIUS TIME OFFSET\n");
		return 0;
	}

	float OFFSET = atof(argv[3]);
	float R = atof(argv[1]) + OFFSET;
	float T = atof(argv[2]);

	float sin_45 = sin(radianos(45));
	float cos_45 = cos(radianos(45));

	printf("\t\t\t<translate time=\"%.02f\">\n", T);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n", R        , 0.0,       0.0);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n",  R*cos_45, 0.0, -R*sin_45);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n",  0.0     , 0.0,        -R);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n", -R*cos_45, 0.0, -R*sin_45);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n", -R       , 0.0,       0.0);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n", -R*cos_45, 0.0,  R*sin_45);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n",  0.0     , 0.0,         R);
	printf("\t\t\t\t<point X=\"%.02f\" Y=\"%.02f\" Z=\"%.02f\" />\n",  R*cos_45, 0.0,  R*sin_45);
	printf("\t\t\t</translate>\n");

	return 0;
}