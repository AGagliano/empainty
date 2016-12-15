   
import processing.net.*; 
import processing.serial.*;  

Server myServerA;
Server myServerB;
Client myClientA; 
Client myClientB;
Serial myPort;
String stringInA = "5"; //set as default
String stringInB = "4"; //set as default
int valA;
int valB;
String firstCharA;
String firstCharB;
 
void setup() { 
  
 // Serial.begin(9600);
  
  size(200, 200); 
  // Connect to the local machine at port 5203 and 5204.
  myServerA = new Server(this, 5203); //Server to read Brush A input; make sure IP address of this computer is put in ESP of the brushes
  myServerB = new Server(this, 5204); //Server to read Brush B input; make sure IP address of this computer is put in ESP of the brushes
  myPort = new Serial(this, "/dev/cu.usbmodem1441", 9600); //Set to the port arduino is on
  println(Server.ip()); //debugging
  print("connected to client and serial"); //debugging
} 
 
void draw() { 
  //Outputs brush A and B prediction values to serial to be read by Arduino
  //Example:
  //a
  //4
  //b
  //5

  myClientA = myServerA.available(); //create client
  delay(200);
  if (myClientA != null) {  //if client has something to read on server
    println(myClientA);     //debugging
    String stringInA = myClientA.readString();
    firstCharA = str(stringInA.charAt(0));
    valA = Integer.parseInt(firstCharA);
      
    println("a");         //debugging
    println(stringInA);
    myPort.write("a");
    myPort.write(valA);
  
    //if (stringInA != null) {
    //  firstCharA = str(stringInA.charAt(0));
    //  valA = Integer.parseInt(firstCharA);
      
    //  println("a");         //debugging
    //  println(stringInA);
    //  myPort.write("a");
    //  myPort.write(valA);
    //}
  } 
  
  myClientB = myServerB.available();
  delay(200);
  if (myClientB != null) {
    println(myClientB);
    String stringInB = myClientB.readString();
    
    firstCharB = str(stringInB.charAt(0));
    valB = Integer.parseInt(firstCharB);
    
    println("b");
    println(stringInB);
    myPort.write("b");
    myPort.write(valB);
    
    //if (stringInB != null) {
    //  firstCharB = str(stringInB.charAt(0));
    //  valB = Integer.parseInt(firstCharB);
      
    //  println("b");
    //  println(stringInB);
    //  myPort.write("b");
    //  myPort.write(valB);
    //}
  }
} 