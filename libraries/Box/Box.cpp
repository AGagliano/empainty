// this is the source file that contains functions to manipulate the
// Box objects

//#include <Servo.h>
#include "Lid.h"
#include "Box.h"
#include "MemoryFree.h"


// constructor
Box::Box(int _p1, int _p2, int _p3, int _p4, int _p5, int _p6) {

	// make six Lid objects which belong to the Box
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	p4 = _p4;
	p5 = _p5;
	p6 = _p6;

	// lid1 = Lid(p1);
	// lid2 = Lid(p2);
	// lid3 = Lid(p3);
	// lid4 = Lid(p4);
	// lid5 = Lid(p5);
	// lid6 = Lid(p6);

	// lid1.setup();
	// lid2.setup();
	// lid3.setup();
	// lid4.setup();
	// lid5.setup();
	// lid6.setup();

}

Box::Box() {

}

void Box::setup() {
	// lid1 = Lid(p1);
	// lid2 = Lid(p2);
	// lid3 = Lid(p3);
	// lid4 = Lid(p4);
	// lid5 = Lid(p5);
	//lid6 = Lid(p6);

	// lid1.setup();
	// lid2.setup();
	// lid3.setup();
	// lid4.setup();
	// lid5.setup();
	// lid6.setup();
}

bool Box::isEqual(float f1, float f2, float epsilon) {
	float diff = fabs(f1 - f2);
	return diff < epsilon;
}

// this function should be used by the empainty.ino sketch to change the desired locations and durs
// of the box.
//
// each time the empainty.ino loops, it should run this function, setting the six desired
// values for each lid, and 6 desired amts of time to arrive there
//
// it also changes the value of dist, dur, and step based on the new desired dur values
void Box::setDesired(float newDesiredArray[6], float newDurArray[6]) {

	tooClosedFix(newDesiredArray);

	// change the desired values
	lid1.desired = (newDesiredArray[0]);
	lid2.desired = (newDesiredArray[1]);
	lid3.desired = (newDesiredArray[2]);
	lid4.desired = (newDesiredArray[3]);
	lid5.desired = (newDesiredArray[4]);
	lid6.desired = (newDesiredArray[5]);

	// change the dur values
	lid1.dur = (newDurArray[0]);
	lid2.dur = (newDurArray[1]);
	lid3.dur = (newDurArray[2]);
	lid4.dur = (newDurArray[3]);
	lid5.dur = (newDurArray[4]);
	lid6.dur = (newDurArray[5]);

	// based on these new desired and dur values, run stepCalc, which will change both
	// the dist and step values for each lid
	lid1.stepCalc();
	lid2.stepCalc();
	lid3.stepCalc();
	lid4.stepCalc();
	lid5.stepCalc();
	lid6.stepCalc();

}

// function that moves each lid by one step amount
// to be called in empainty.ino
void Box::setInMotion() {
	// make an array that has the current positions of the box
	float currentPosArray[6];
	currentPosArray[0] = lid1.curr;
	currentPosArray[1] = lid2.curr;
	currentPosArray[2] = lid3.curr;
	currentPosArray[3] = lid4.curr;
	currentPosArray[4] = lid5.curr;
	currentPosArray[5] = lid6.curr;

	// change the currentPosArray by the current step amount
	updatePosArray(currentPosArray);



	// ACTUALLY move the lids-- finally
	move(currentPosArray);
}


// this function updates the posArray by the appropriate
// step amounts (it only changes the lids by one step amount)

// this function happens as the box is sweeping toward desired locations
void Box::updatePosArray(float posArray[6]) {

	// change the value of curr appropriately
	lid1.updatePos();
	lid2.updatePos();
	lid3.updatePos();
	lid4.updatePos();
	lid5.updatePos();
	lid6.updatePos();

	// change the posArray appropriately (next we'll use move() to actually
	// move the servos by the step amount)
	posArray[0] = lid1.curr;
	posArray[1] = lid2.curr;
	posArray[2] = lid3.curr;
	posArray[3] = lid4.curr;
	posArray[4] = lid5.curr;
	posArray[5] = lid6.curr;
	// now the PosArray (that was passed into this function) has been changed
	// by the amount of 'step.' sweet.
}

// this function simply sets each of the lids to a position that is
// given in an array of 6 position numbers
void Box::move(float newPosArray[6]) {

	lid1.set(newPosArray[0]);
	lid2.set(newPosArray[1]);
	lid3.set(newPosArray[2]);
	lid4.set(newPosArray[3]);
	lid5.set(newPosArray[4]);
	lid6.set(newPosArray[5]);
}


void Box::tooClosedFix(float newDesiredArray[6]) {

	for (int i = 0; i <= 1; i++) {
		if (newDesiredArray[i] > 80) {
			newDesiredArray[i] = 80;
		}
	}
	for (int i = 4; i <= 5; i++) {
		if (newDesiredArray[i] > 80) {
			newDesiredArray[i] = 80;
		}
	}

}

void Box::boxOpen() {
	float desiredArray[6] = {0, 0, 0, 0, 0, 0};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);

	// lid1.s.write(0);
	// lid2.s.write(angleCalc(0));
	// lid3.s.write(angleCalc(0));
	// Serial.print("boxOpen freeMemory()=");
 //   	Serial.println(freeMemory());
	// lid4.s.write(0);
	// lid5.s.write(0);
	// lid6.s.write(0);


	while (!isEqual(lid1.curr, lid1.desired, 0.1) ||
			!isEqual(lid2.curr, lid2.desired, 0.1) ||
			!isEqual(lid3.curr, lid3.desired, 0.1) ||
			!isEqual(lid4.curr, lid4.desired, 0.1) ||
			!isEqual(lid5.curr, lid5.desired, 0.1) ||
			!isEqual(lid6.curr, lid6.desired, 0.1)) {
		setInMotion();
	}

}

void Box::boxClose() {
	float desiredArray[6] = {80, 80, 80, 80, 80, 80};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);

	while (!isEqual(lid1.curr, lid1.desired, 0.1) ||
			!isEqual(lid2.curr, lid2.desired, 0.1) ||
			!isEqual(lid3.curr, lid3.desired, 0.1) ||
			!isEqual(lid4.curr, lid4.desired, 0.1) ||
			!isEqual(lid5.curr, lid5.desired, 0.1) ||
			!isEqual(lid6.curr, lid6.desired, 0.1)) {
		setInMotion();
	}

}

void Box::warmest() {
	float desiredArray[6] = {0, 0, angleCalc(0), 80, 80, 80};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);

	while (!isEqual(lid1.curr, lid1.desired, 0.1) ||
			!isEqual(lid2.curr, lid2.desired, 0.1) ||
			!isEqual(lid3.curr, lid3.desired, 0.1) ||
			!isEqual(lid4.curr, lid4.desired, 0.1) ||
			!isEqual(lid5.curr, lid5.desired, 0.1) ||
			!isEqual(lid6.curr, lid6.desired, 0.1)) {
		setInMotion();
	}

}

void Box::warm() {
	float desiredArray[6] = {80, 0, angleCalc(0), 0, 80, 80};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);

	while (!isEqual(lid1.curr, lid1.desired, 0.1) ||
			!isEqual(lid2.curr, lid2.desired, 0.1) ||
			!isEqual(lid3.curr, lid3.desired, 0.1) ||
			!isEqual(lid4.curr, lid4.desired, 0.1) ||
			!isEqual(lid5.curr, lid5.desired, 0.1) ||
			!isEqual(lid6.curr, lid6.desired, 0.1)) {
		setInMotion();
		// Serial.print("freeMemory()=");
   	// Serial.println(freeMemory());
	}

}

void Box::cold() {
	float desiredArray[6] = {80, 80, angleCalc(0), 0, 0, 80};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);

	while (!isEqual(lid1.curr, lid1.desired, 0.1) ||
			!isEqual(lid2.curr, lid2.desired, 0.1) ||
			!isEqual(lid3.curr, lid3.desired, 0.1) ||
			!isEqual(lid4.curr, lid4.desired, 0.1) ||
			!isEqual(lid5.curr, lid5.desired, 0.1) ||
			!isEqual(lid6.curr, lid6.desired, 0.1)) {
		setInMotion();
	}

}

void Box::coldest() {
	float desiredArray[6] = {80, 80, angleCalc(80), 0, 0, 0};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);

	while (!isEqual(lid1.curr, lid1.desired, 0.1) ||
			!isEqual(lid2.curr, lid2.desired, 0.1) ||
			!isEqual(lid3.curr, lid3.desired, 0.1) ||
			!isEqual(lid4.curr, lid4.desired, 0.1) ||
			!isEqual(lid5.curr, lid5.desired, 0.1) ||
			!isEqual(lid6.curr, lid6.desired, 0.1)) {
		setInMotion();
	}

}

void Box::wave() {
	float desiredArray[6] = {0, 0, angleCalc(0), 0, 0, 0};
	float durArray[6] = {1500,1500,1500,1500,1500,1500};
	setDesired(desiredArray, durArray);
	while (!isEqual(lid1.curr, lid1.desired, 0.1)) {
		setInMotion();
	}

	desiredArray[0] = 80;
	setDesired(desiredArray, durArray);
	while (!isEqual(lid1.curr, lid1.desired, 0.1)) {
		setInMotion();
	}
}

float Box::angleCalc(float in) {
	return 180 - in;
}

