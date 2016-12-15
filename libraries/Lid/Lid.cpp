// source file with all of the Lid object functions

//#include <Servo.h>
#include <Lid.h>


float Lid::angleCalc(float in) {
	return 180 - in;
}

// constructor
Lid::Lid(int _pin, int size) {	
	//s = Servo();
	//s.attach(_pin);

	 pin = _pin;

	 attached = false;

	 //small
	 if (size == 0) {
	 	curr = 80;
	 }
	 //big
	 else {
	 	curr = angleCalc(80);
	 }
	 
	 desired = 0;
	 jump = 0;
	 dur = 1;
};


Lid::Lid() {

}

void Lid::setup() {
	s = Servo(pin);
	s.attach(pin);

	// Serial.println("attached?: ");
	// Serial.println( s.attached());


	//attached = true;
	//s.write(100);
	//Serial.println("setup");
	//Serial.println(pin);

}

bool Lid::isEqual(float f1, float f2, float epsilon) {
	float diff = fabs(f1 - f2);
	return diff < epsilon;
}

// this function calculates an updated position for a
// lid based on the duration and distance that it needs
// to travel
//
// this should be run only when a new speed needs to be set
void Lid::stepCalc() {
	float dist = desired - curr;
	jump = (dist / dur);
}

// this function changes the curr value by the step amount
void Lid::updatePos() {
	if (!(isEqual(curr, desired, 0.1))) {
		curr = curr + jump;
	}
}

// this function actually moves the servo's position
void Lid::set(float pos) {
	s.write(pos);
	//Serial.println("set attached?: ");
	//Serial.println(s.attached());
}