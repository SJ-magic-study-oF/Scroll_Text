/************************************************************
************************************************************/
#include <new> // placement new

#include "Light.h"

/************************************************************
************************************************************/
/********************
********************/
static ODE ode[] = {
	ODE("10.7.162.176"),
	ODE("10.7.153.16"),
	ODE("10.7.164.56"),
};
static const int NUM_ODES = sizeof(ode) / sizeof(ode[0]);

/********************
********************/
static LED_LIGHT LedLight[] = {
//				ODE id		AddressFrom				Pan_min		Pan_max		Tilt_min		Tilt_max			Hardware(Start Address) setting 
/*	0	*/	LED_LIGHT(	0	,	0	,	LED_DEVICE_TYPE_MOVING	,	36408	,	50970	,	0	,	28086	),	//	1
/*	1	*/	LED_LIGHT(	0	,	13	,	LED_DEVICE_TYPE_MOVING	,	36408	,	50970	,	0	,	28086	),	//	14
/*	2	*/	LED_LIGHT(	0	,	26	,	LED_DEVICE_TYPE_MOVING	,	36408	,	50970	,	0	,	28086	),	//	27
/*	3	*/	LED_LIGHT(	0	,	39	,	LED_DEVICE_TYPE_MOVING	,	36408	,	50970	,	0	,	28086	),	//	40
/*	4	*/	LED_LIGHT(	0	,	52	,	LED_DEVICE_TYPE_MOVING	,	36408	,	50970	,	0	,	28086	),	//	53
/*	5	*/	LED_LIGHT(	0	,	65	,	LED_DEVICE_TYPE_MOVING	,	36408	,	50970	,	0	,	28086	),	//	66
/*	6	*/	LED_LIGHT(	1	,	0	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	1
/*	7	*/	LED_LIGHT(	1	,	6	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	7
/*	8	*/	LED_LIGHT(	2	,	0	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	1
/*	9	*/	LED_LIGHT(	2	,	6	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	7
/*	10	*/	LED_LIGHT(	1	,	12	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	13
/*	11	*/	LED_LIGHT(	1	,	18	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	19
/*	12	*/	LED_LIGHT(	1	,	24	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	25
/*	13	*/	LED_LIGHT(	1	,	30	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	31
/*	14	*/	LED_LIGHT(	1	,	36	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	37
/*	15	*/	LED_LIGHT(	1	,	42	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	43
/*	16	*/	LED_LIGHT(	1	,	48	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	49
/*	17	*/	LED_LIGHT(	1	,	54	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	55
/*	18	*/	LED_LIGHT(	2	,	12	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	13
/*	19	*/	LED_LIGHT(	2	,	18	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	19
/*	20	*/	LED_LIGHT(	2	,	24	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	25
/*	21	*/	LED_LIGHT(	2	,	30	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	31
/*	22	*/	LED_LIGHT(	2	,	36	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	37
/*	23	*/	LED_LIGHT(	2	,	42	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	43
/*	24	*/	LED_LIGHT(	2	,	48	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	49
/*	25	*/	LED_LIGHT(	2	,	54	,	LED_DEVICE_TYPE_FIXED	,	-1	,	1	,	-1	,	1	),	//	55
};

static const int NUM_LEDS = sizeof(LedLight) / sizeof(LedLight[0]);

/********************
********************/
static LED_BLOCK LedBlock[] = {				
	{ // block[0]			
		{ // LogicalCh		
			{0, 	-1},
			{1, 	-1},
			{2, 	-1},
			{	-1},
		},		
	},			
	{ // block[1]			
		{ // LogicalCh		
			{3, 	-1},
			{4, 	-1},
			{5, 	-1},
			{	-1},
		},		
	},			
	{ // block[2]			
		{ // LogicalCh		
			{14, 18,  	-1},
			{13, 19,  	-1},
			{12, 20, 	-1},
			{11, 21, 	-1},
			{10, 22, 	-1},
			{	-1},
		},		
	},			
	{ // block[3]			
		{ // LogicalCh		
			{17, 23,  	-1},
			{16, 24,  	-1},
			{15, 25,	-1},
			{	-1},
		},		
	},			
	{ // block[4]			
		{ // LogicalCh		
			{6, 	-1},
			{7, 	-1},
			{8, 	-1},
			{9, 	-1},
			{	-1},
		},		
	},			
};				
