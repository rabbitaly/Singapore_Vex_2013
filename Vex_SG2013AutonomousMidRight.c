#pragma config(Sensor, in1,    firstTierLeft,  sensorPotentiometer)
#pragma config(Sensor, in2,    secondTier,     sensorPotentiometer)
#pragma config(Sensor, in3,    leftLight,      sensorLineFollower)
#pragma config(Sensor, in4,    rightLight,     sensorLineFollower)
#pragma config(Sensor, in5,    backLight,      sensorLineFollower)
#pragma config(Sensor, dgtl3,  led,            sensorLEDtoVCC)
#pragma config(Sensor, dgtl6,  backRight,      sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  backLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl10, bumperRight,    sensorTouch)
#pragma config(Sensor, dgtl11, bumperLeft,     sensorTouch)
#pragma config(Motor,  port1,           leftBack,      tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port2,           leftMiddle,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port3,           leftFront,     tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port4,           firstTierLeft, tmotorVex393, openLoop)
#pragma config(Motor,  port5,           secondTier,    tmotorVex393, openLoop)
#pragma config(Motor,  port6,           intakeRollers, tmotorVex269, openLoop)
#pragma config(Motor,  port7,           firstTierRight, tmotorVex393, openLoop)
#pragma config(Motor,  port8,           rightFront,    tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port9,           rightMiddle,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port10,          rightBack,     tmotorVex393HighSpeed, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "FnLibSingaporeVex2013.h";

task main()
{
	/* Starting at top left position, push ball to scoring zone */
	// Deploy - Second tier up until it is 90 degree
	moveSecondTierUp(127,450);
	// Rest second tier
	moveSecondTierDown(-127,50);
	// Deploy big ball intake
	moveFirstTierUp(127,1200);
	// Rest first tier
	moveFirstTierDown(127,50);
	// Align to line
	moveStraightLight(127,50);
	moveStraightDistance(127,1000);
	// Turn 90 degrees, perpendicular to bridge
	turnLeft(127,300);
	// Move forward for 2000, then raise arm to *900 while pushing forward at 20, then move back
	pushBridge(127,2000,900);
	// Turn and face parallel to bridge
	turnRight(127,300);
	// Align to next line
	moveStraightLight(127,1000);
	// Turn to face ramp with balls
	turnRight(127,300);
	// Angle of lift to cross ramp is 400*
	crossRamp(127,1000,400);
}
