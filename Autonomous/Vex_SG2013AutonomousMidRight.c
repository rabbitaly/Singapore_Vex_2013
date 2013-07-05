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
	/*Mid Right*/
	StartTask(intakeStart);
		ClearTimer(T4);
		moveSecondTierUp(127,450);
		moveSecondTierDown(127,50);
		intake = 1;
		motor[secondTier]=-127;
		wait10Msec(50);
		motor[secondTier]=0;
		moveStraightDistance(127,350);
		alignFoward(127);
		stopPid(0.6,0.3);
		moveStraightDistance(100,100);
		stopPid(0.6,0.3);
		intake = 0;
		wait10Msec(10);
		turnLeft(100,250);
		stopTurn(0.6,0.3);
		moveStraightDistance(100,1450);
		stopPid(0.6,0.3);
		moveFirstTierUp(127,1200);
		motor[firstTierLeft] = 10;
		motor[firstTierRight] = 10;
		moveStraightDistance(100,200);
		turnRight(50,25);
		stopTurn(0.6,0.3);
		moveStraightTime(50,500);
		intake = -1;
		wait10Msec(300);
		intake = 0;
		moveStraightDistance(-50,250);
		moveFirstTierDown(127,50);
		turnRight(127,40);
		moveStraightDistance(-100, 1400);
		while(SensorValue[bumperLeft]==0)
		{
		}
		moveStraightDistance(127,300);
		pushBridge(80,900);
		moveStraightDistance(100,200);
		moveStraightDistance(-100,420);
		stopPid(0.6,0.3);
		while(SensorValue[bumperLeft]==0)
		{
		}
		moveStraightDistance(100,300);
		stopPid(0.6,0.3);
		alignFoward(100);
		turnLeft(127,250);
		moveFirstTierUp(127,900);
		moveStraightDistance(100,800);
		stopPid(0.6,0.3);
		stopLift();
		moveStraightDistance(-100,100);
		stopPid(0.6,0.3);
}
