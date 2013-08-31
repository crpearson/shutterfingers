// shutterfingers
//
// Positions a servo to depress the shutter button of a camera when triggered 
// from a remote shutter release cable. See URL below for pinouts:
// http://www.doc-diy.net/photo/remote_pinout/#canon

#include <Servo.h> 

Servo shutter_servo;  // create servo object to control a servo 

// trigger inputs and corresponding servo positions
const int shutter_pin = 0;  // pin on which the shutter signal is received
const int shutter_pos = 0;  // position at which the camera's shutter is release
int shutter_state;          // status of the shutter signal
const int focus_pin   = 0;  // pin on which the focus signal is received
const int focus_pos   = 0;  // position at which the camera's autofocus is triggered
int focus_state;            // status of the focus signal
const int safety_pos  = 0;  // safety position away from the shutter button

// shutter servo details
const int shutter_servo_pin   = 0;  // pin on which the servo is attached
int shutter_servo_state;            // current state/position of the shutter servo

void setup() 
{ 
  shutter_servo.attach( shutter_servo_pin );  // attaches the servo on the defined pin to the servo object
  pinMode( focus_pin, INPUT );
  pinMode( focus_pin, INPUT );
} 

void loop() 
{
  // read the inputs
  shutter_state = digitalRead( shutter_pin );
  focus_state   = digitalRead( focus_pin );

  // determine where to send the servo
  // only reposition the servo if the new position is different from the previous
  if ( HIGH == shutter_state )
  {
    if ( shutter_servo_state != shutter_pos )
    {
      shutter_servo.write( shutter_pos );
      shutter_servo_state = shutter_pos;
    }
  }
  else if ( HIGH == focus_pin )
  {
    if ( shutter_servo_state != focus_pos )
    {
      shutter_servo.write( focus_pos );
      shutter_servo_state = focus_pos;
    }
  }
  else
  {
    if ( shutter_servo_state != safety_pos )
    {
      shutter_servo.write( safety_pos );
      shutter_servo_state = safety_pos;
    }
  }

  // sleep for some number of milliseconds, have some patience
  delay(15);
}
