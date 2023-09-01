#include <stdio.h>
#include <math.h>

#define MEAN_FUNCTIONS\
	MEAN_GEN(int)\
	MEAN_GEN(float)

#define MEAN_GEN(T)\
	float T##Mean(T* values, int numValues)\
	{\
		float m = 0.0;\
		for (size_t i = 0; i < numValues; i++)\
		{\
			m += (float)values[i];\
		}\
		m /= numValues;\
		return m;\
	}
MEAN_FUNCTIONS
#undef MEAN_GEN

#define NUM_GRADES 10
int main(void)
{
	int grades[NUM_GRADES] = {85, 82, 88, 86, 85, 93, 98, 40, 73, 83};
	float mean = intMean(grades, NUM_GRADES);
	
	float squaredDevs[NUM_GRADES];
	for (size_t i = 0; i < NUM_GRADES; i++)
	{
		float diff = (mean - (float)grades[i]);
		squaredDevs[i] = diff * diff;
	}
	
	float averageVariance = floatMean(squaredDevs, NUM_GRADES);
	float standardDeviation = sqrtf(averageVariance);

	for (size_t i = 0; i < NUM_GRADES; i++)
	{
		printf("Grade: %3d\tVariance: %.2f\n", grades[i], squaredDevs[i]);
	}
	printf("Standard Deviation: %.2f", standardDeviation);

	return(0);
}