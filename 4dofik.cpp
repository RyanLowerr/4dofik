
/*
	gcc -o test ik.cpp -lm
	./test
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define COXA_LENGTH    46.0
#define FEMUR_LENGTH   70.0
#define TIBIA_LENGTH   68.0
#define TARSUS_LENGTH  83.0

struct angles
{
	double coxa;
	double femur;
	double tibia;
	double tarsus;
};

void ik(double x, double y, double z)
{
	angles result;
	double leg_length;
	double tarsus_offset_angle;
	double tarsus_offset_xy;
	double tarsus_offset_z;
	double theta;
	double side_a, side_b, side_c;
	double angle_a, angle_b, angle_c;
	double temp1, temp2;

	// Magnitude of the leg length along the ground from the coxa axis to the tip of the foot in the XY plane
	leg_length = sqrt(x*x + y*y);
	
	// Tarsus Offsets
	tarsus_offset_angle = 0.0; // 0.0 for now. will revisit later.
	tarsus_offset_xy = sin(tarsus_offset_angle) * TARSUS_LENGTH;
	tarsus_offset_z = cos(tarsus_offset_angle) * TARSUS_LENGTH;
	
	// Triangle formed by the femur, tibia and tarsus joints. Using the law of cosines to calculate all sides lengths and angles.
	temp1 = leg_length-COXA_LENGTH-tarsus_offset_xy;
	temp2 = z+tarsus_offset_z;
	side_a = FEMUR_LENGTH;
	side_b = TIBIA_LENGTH;
	side_c = sqrt(temp1*temp1+temp2*temp2);	
	angle_a = acos((-side_a*side_a+side_b*side_b+side_c*side_c)/(2*side_b*side_c)) * (180.0/3.14);
	angle_b = acos(( side_a*side_a-side_b*side_b+side_c*side_c)/(2*side_a*side_c)) * (180.0/3.14);
	angle_c = acos(( side_a*side_a+side_b*side_b-side_c*side_c)/(2*side_a*side_b)) * (180.0/3.14);
	
	// Angle of line between the femur and Tarsus joints with respect to ground
	theta = atan2(temp2,temp1) * (180.0/3.14);
	
	// Resulting joint angles
	result.coxa   = atan2(x,y) * (180.0/3.145);
	result.femur  = 90.0-theta-angle_b;
	result.tibia  = 90.0-angle_c;
	result.tarsus = tarsus_offset_angle+result.femur-result.tibia;
	
	// Print stuff!
	printf("\n");
	printf("leg_length: %.3f\n", leg_length);
	printf("tarsus_offset_xy: %.3f\n", tarsus_offset_xy);
	printf("tarsus_offset_z: %.3f\n", tarsus_offset_z);
	printf("side_a: %.3f\n", side_a);
	printf("side_b: %.3f\n", side_b);
	printf("side_c: %.3f\n", side_c);
	printf("theta: %.3f\n", theta);
	printf("angle_a: %.3f\n", angle_a);
	printf("angle_b: %.3f\n", angle_b);
	printf("angle_c: %.3f\n", angle_c);
	printf("\n");
	printf("coxa:   %.3f\n", result.coxa);
	printf("femur:  %.3f\n", result.femur);
	printf("tibia:  %.3f\n", result.tibia);
	printf("tarsus: %.3f\n", result.tarsus);
	printf("\n");
}

int main(void)
{
	ik(70.0, 70.0, -50.0);
	return(0);
}
