// empainty.ino

#include <QueueArray.h>
#include <Box.h>
#include <Lid.h>
#include <MemoryFree.h>


// create the Box objects and 6 lid objects
// this code should be fine.
Box myBox = Box(3,9,6,8,10,11);
Lid myLid1(3, 0);
Lid myLid2(9, 0);
Lid myLid3(6, 1);
Lid myLid4(8, 1);
Lid myLid5(10, 0);
Lid myLid6(11, 0);

// fwd declaration
bool isEqual(float f1, float f2, float epsilon);
float angleCalc(float in) {
  return 180 - in;
}

// -------------------------------------------------------------------
// the number of most recent gestures to remember and then compare
#define memory 8

// the number of different preprogrammed gestures
#define numberOfGestures 3

// these are the two queues with all the most recent gesture values.
// will have to modify later when we figure out how to grab the gesture values
// from the Serial Port!
QueueArray <int> mostRecentQ1;
QueueArray <int> mostRecentQ2;

// two arrays that will be the recipients of the queue values
int mostRecentA1[memory] = {0, 0, 0, 0, 0, 0, 0, 0};
int mostRecentA2[memory] = {0, 0, 0, 0, 0, 0, 0, 0};

int tally1[numberOfGestures];
int tally2[numberOfGestures];

int matchCount;
float percentage;
// ------------------------------------------------------------------
// test brush as char and not int 
int brush;
int aVal = 0;
int bVal = 0;
int i = 0;
int counter = 0;


void setup() {

    Serial.begin(9600);
//    while (!Serial) {}
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    
    myLid1.setup();
    myLid1.set(0);
    myLid1.curr = 0;
  
    myLid2.setup();
    myLid2.set(0);
    myLid2.curr = 0;
  
    myLid3.setup();
    myLid3.set(angleCalc(0));
    myLid3.curr = angleCalc(0);
  
    myLid4.setup();
    myLid4.set(0);
    myLid4.curr = 0;

  
    myLid5.setup();
    myLid5.set(0);
    myLid5.curr = 0;
 
    myLid6.setup();
    myLid6.set(0);
    myLid6.curr = 0;

    
    myBox.lid1 = myLid1;
    myBox.lid2 = myLid2;
    myBox.lid3 = myLid3;
    myBox.lid4 = myLid4;
    myBox.lid5 = myLid5;
    myBox.lid6 = myLid6;

////    digitalWrite(13, LOW);
//    Serial.print("freeMemory()=");
//    Serial.println(freeMemory());
    
  // -----------------------------------------------------------------
  myBox.boxOpen();
}


// move all of the existing array values left and add new value to the end
void pushToArray(int A[memory], int newValue) {
  for (int i=0; i < memory - 1; i++) {
    A[i] = A[i+1];
  }
  A[memory-1] = newValue;
}

 
// function that moves each of the values of 2 queues into two corresponding
// arrays
void populateArrays(QueueArray <int> Q1, QueueArray <int> Q2, int A1[memory], int A2[memory]) {
  
  // populate the first array
  int i = 0;
  while (!Q1.isEmpty()) {
    A1[i] = Q1.pop();
    i++;
  }
  i = 0; // reset the counter

  // populate the second array
  while (!Q2.isEmpty()) {
    A2[i] = Q2.pop();
    i++;
  }
    
  // repopulate the queues
  for (int j = 0; j < i; j++){
    addToQueue(Q1, A1[j]);
    addToQueue(Q2, A2[j]);
  }
}


// function that creates frequency (or tally) arrays that represent how many
// instances of each gesture occur in the one of the mostRecent[A1/A2] arrays
// 
// s.t. tallyArray[i] = the number of instances of gesture i
void tally(int mosRec[memory], int tallyArray[numberOfGestures]) {
  // first put 0s in all the tallyArray slots
  for (int i = 0; i < numberOfGestures; i++) {
    tallyArray[i] = 0;
  }
  // then go through each element of the mostRecent 'mosRec' array and count
  // the instances of each gesture in the 'tally' array
  for (int i = 0; i < memory; i++) {
    tallyArray[mosRec[i]]++;
  }
}

// this function compares two frequency (tally) arrays and then returns the
// number of matches. This # of matches will be between 0 and 'memory' (the # of 
// gestures remembered and compared)
int compareTally(int tally1[numberOfGestures], int tally2[numberOfGestures]) {
  
  int m = 0;

  // loop through each gesture type
  for (int i = 0; i < numberOfGestures; i++) {
    // if the freq of both are > 0 then we got a match!
    while (tally1[i] != 0 && tally2[i] != 0) {
      tally1[i]--;
      tally2[i]--;
      m++;
    }
  }
//Serial.println(matchCount);
return m;
}

// this function takes in two floats and an epsilon value and returns
// true if the the two floats are equal (or closer to each other than epsilon)
// and false otherwise
bool isEqual(float f1, float f2, float epsilon) {
  float diff = fabs(f1 - f2);
  return diff < epsilon;
}

void addToQueue(QueueArray <int> Q, int newVal) {
  if (Q.count() == memory) {
    Q.pop();
    Q.push(newVal);
  }
  else {
    Q.push(newVal);
  }
}

 void loop() {
//    myBox.boxOpen();
//    delay(1000);
////    myBox.boxClose();
////    delay(1000);
//
//    myBox.warmest();
//    myBox.warm();
//    myBox.cold();
//    myBox.coldest();

  // run this if there's a new gesture available
  
  while (Serial.available() > 0) {
//    if (int counter%3 == 
    brush = Serial.read();

    // snag brush1 data
    if (brush == 97) {
      aVal = Serial.read();
      aVal = aVal - 1;
//      addToQueue(mostRecentQ1, aVal);
//      digitalWrite(13, HIGH);
//    populateArrays(mostRecentQ1, mostRecentQ2, mostRecentA1, mostRecentA2);
      pushToArray(mostRecentA1, aVal);

    }
    
    // snag brush2 data
    if (brush == 98) {
      bVal = Serial.read();
      bVal = bVal - 1;
//    populateArrays(mostRecentQ1, mostRecentQ2, mostRecentA1, mostRecentA2);
      pushToArray(mostRecentA2, bVal);

//      addToQueue(mostRecentQ2, bVal);
//      digitalWrite(13, LOW);
    }
  }
    // calculate frequency arrays "tally1" and "tally2"
    tally(mostRecentA1, tally1);
    tally(mostRecentA2, tally2);

    // count the # of matching gestures
    matchCount = compareTally(tally1, tally2);
    for (int i=0; i < matchCount; i++) {
      digitalWrite(13, HIGH);
      delay(1);
      digitalWrite(13, LOW);
      delay(1);
    }
    percentage = matchCount / memory;
    
   if (matchCount >= 7) {
    myBox.warmest();
   }
   else if (matchCount < 7 && matchCount > 5) {
    myBox.warm();
   }
   else if (matchCount == 5) {
    myBox.warm();
    myBox.warmest();
    myBox.warm();
   }
   else if (matchCount < 5 && matchCount > 3) {
    myBox.cold();
   }
   else if (matchCount == 3) {
    myBox.cold();
    myBox.coldest();
    myBox.cold();
   }
   else if (matchCount < 3) {
    myBox.coldest();
   }
   else {
    myBox.boxOpen();
   }
delay(500);
 }





