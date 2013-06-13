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

#include "FnLibSingaporeVex2013.h"

int intake = 0;

task intakeStart()
{
	while (true)
	{
		if (intake == 1)
		{
			motor[intakeRollers] = -127;
		}
		else if (intake == -1)
		{
			motor[intakeRollers] = 127;
		}
		else
		{
			motor[intakeRollers] = 0;
		}
	}
}

task main()
{
	StartTask(intakeStart);
	while(SensorValue[bumperLeft]==0)
	{
	}
	moveSecondTierUp(127,450);
	moveSecondTierDown(127,50);
	/*
	intake = 1;
	wait10Msec(50);
	moveStraightDistance(127,200);
	stopPid(0.6,0.3);
	wait10Msec(10);
  moveStraightDistance(30, 200);
  stopPid(0.6,0.3);
  wait10Msec(200);
  intake = 0;
	turnRight(100,250);
	moveStraightDistance(100,100);
	alignFoward(127);
	wait10Msec(5);
	stopDrive();
	moveSharpRight(127,600);
	moveStraightDistance(127,100);
	stopPid(0.6,0.3);
	*/
	//crossRamp(127,3000,400);
	//intakePushTime(127,3000);
  StopTask(intakeStart);

}
