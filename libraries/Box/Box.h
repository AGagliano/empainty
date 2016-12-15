// This header file contains the construction of a "box" type and also a
// bunch of functions that will make moving the 6 lids of the box a little
// bit easier.

#ifndef Box_h
#define Box_h

//#include <Servo.h>
#include <Lid.h>


class Box 
{
	public:
		Box(int _p1, int _p2, int _p3, int _p4, int _p5, int _p6);

		Box();

		bool isEqual(float f1, float f2, float epsilon);

		void setDesired(float newDesiredArray[6], float newDurArray[6]);
		void setInMotion();
		void updatePosArray(float posArray[6]);
		void move(float newPosArray[6]);

		void tooClosedFix(float newDesiredArray[6]);

		void boxOpen();
		void boxClose();
		void warmest();
		void warm();
		void cold();
		void coldest();
		void wave();

		float angleCalc(float in);

		Lid getLid(int id);
		
		void setup();

		Lid lid1;
		Lid lid2;
		Lid lid3;
		Lid lid4;
		Lid lid5;
		Lid lid6;

		int p1;
		int p2;
		int p3;
		int p4;
		int p5;
		int p6;

	private:



};

#endif