// this header file contains the Lid class


#ifndef Lid_h
#define Lid_h

#include <Arduino.h>
#include <Servo.h>


		

class Lid
{
	public:
		float angleCalc(float in);

		Lid(int _pin, int size);
		Lid();
		
		void setup();
		
		bool isEqual(float f1, float f2, float epsilon);
		void stepCalc();
		void updatePos();
		void set(float pos);

		int pin;

		bool attached;

		Servo s;
		float curr;
		float desired;
		float jump;
		float dur;

		//int pin;

	private:

};

#endif