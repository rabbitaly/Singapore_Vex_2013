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

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "FnLibSingaporeVex2013.h";

int cubicMap(int x)
{
	return ((((x*3)/25)*((x*3)/25)*((x*3)/25)/27 + x/2)*2)/3;
}
int intake = 0;
task intakeBallOut()
{
	intake=-1;
	wait10Msec(100);
	intake = 0;
}

int armDelay=0;
int armPos=0;

task armToPos()
{
	wait1Msec(armDelay);
	if(armPos<SensorValue[in1])
	{
		while(SensorValue[in1]>armPos)
		{
			motor[firstTierLeft]=-127;
			motor[firstTierRight]=-127;
		}
		motor[firstTierLeft]=0;
		motor[firstTierRight]=0;
	}
	else if(armPos>SensorValue[in1])
	{
		while(SensorValue[in1]<armPos)
		{
			motor[firstTierLeft]=127;
			motor[firstTierRight]=127;
		}
		motor[firstTierLeft]=15;
		motor[firstTierRight]=15;
	}
}

int tierPos=0;
int tierDelay=0;
task tierToPos()
{
	wait1Msec(tierDelay);
	if(tierPos<SensorValue[in2])
	{
		while(SensorValue[in2]>tierPos)
		{
			motor[secondTier]=-127;
		}
		motor[secondTier]=0;
	}
	else if(tierPos>SensorValue[in2])
	{
		while(SensorValue[in2]<tierPos)
		{
			motor[secondTier]=127;
		}
		while(SensorValue[in2]>0)
		{
			motor[secondTier]=-127;
		}
		motor[secondTier]=0;
	}
}

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


int programs = 0;
task LED()
{
	while(true)
	{
		for(int i = 0;i<=programs;i++)
		{
			SensorValue[led]=1;
			wait1Msec(300);
			SensorValue[led]=0;
			wait1Msec(300);
		}
		wait1Msec(1000);
	}
}

task selector()
{
	while(true)
	{
		bool old1= false;
		bool pressed1;
		bool old2=false;
		bool pressed2;
		// Detect Plus Bumper Press
		if(SensorValue[bumperLeft]==1)
		{
			pressed1 = true;
		}
		else
		{
			pressed1 = false;
		}
		// Detect Minus Bumper Press
		if(SensorValue[bumperRight]==1)
		{
			pressed2 = true;
		}
		else
		{
			pressed2 = false;
		}

		if(!old1&&pressed1)
		{
			if(programs==3)
			{
				programs = 0;
			}
			else
			{
				programs++;
			}
		}
		else if(!old2&&pressed2)
		{
			if(programs == 0)
			{
				programs=3;
			}
			else
			{
				programs--;
			}
		}
		old1 = pressed1;
		old2 = pressed2;
		wait10Msec(30);
	}
}
void pre_auton()
{
	StartTask(LED);
	StartTask(selector);
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;




	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo  positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous T\ask
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	if(programs ==0)
	{
		/*Top Left*/
		StartTask(intakeStart);
		ClearTimer(T4);
		moveSecondTierUp(127,450);
		moveSecondTierDown(127,50);
		intake = 1;
		motor[secondTier]=-127;
		wait10Msec(50);
		motor[secondTier]=0;
		moveStraightDistance(127,200);
		stopPid(0.6,0.3);
		wait10Msec(10);
		moveStraightDistance(30, 200);
		stopPid(0.6,0.3);
		wait10Msec(150);
		intake = 0;
		turnRight(100,400);
		wait1Msec(200);
		moveStraightDistance(100,400);
		stopPid(0.6,0.3);
		moveStraightDistance(-127,100);
		stopPid(0.6,0.3);
		turnLeft(90, 200);
		moveStraightDistance(127,700);
		StopTask(intakeStart);
	}
	else if(programs ==1)
	{
		/*Top Right*/
		moveSecondTierUp(127,450);
		moveSecondTierDown(127,50);
		intake = 1;
		motor[secondTier]=-127;
		wait10Msec(50);
		motor[secondTier]=0;
		moveStraightDistance(127,200);
		stopPid(0.6,0.3);
		wait10Msec(10);
		moveStraightDistance(30, 200);
		stopPid(0.6,0.3);
		wait10Msec(150);
		intake = 0;
		turnLeft(100,400);
		wait1Msec(200);
		moveStraightDistance(100,400);
		stopPid(0.6,0.3);
		moveStraightDistance(-127,100);
		stopPid(0.6,0.3);
		turnRight(90, 200);
		moveStraightDistance(127,700);

		StopTask(intakeStart);
	}
	else if(programs ==2)
	{
		/*Mid Left*/
		StartTask(intakeStart);
		ClearTimer(T4);
		armPos = 900;
		armDelay = 0;
		//moveFirstTierUp(127,900);
		StartTask(armToPos);
		// Arm set to push bridge position
		wait10Msec(100);
		moveStraightDistance(127,600);
		stopPid(0.6,0.3);
		// Ram Bridge
		StopTask(armToPos);
		armPos=0;
		armDelay=0;
		StartTask(armToPos);
		tierPos=450;
		tierDelay=0;
		StartTask(tierToPos);
		intake = 1;
		moveStraightDistance(-127,400);
		while(SensorValue[bumperLeft]==0&&SensorValue[bumperRight]==0)
		{
			intake = 0;
		}
		StopTask(armToPos);
		armPos = 900;
		armDelay=0;
		StartTask(armToPos);
		moveStraightDistance(100,300);
		stopPid(0.6,0.3);
		alignFoward(100);
		turnRight(127,250);
		moveStraightDistance(100,900);
		stopPid(0.6,0.3);
		stopLift();
		moveStraightDistance(-100,100);
		stopLift();
		turnLeft(127,150);
		moveStraightDistance(-100,700);
		stopPid(0.6,0.3);

		while(SensorValue[bumperLeft]==0&&SensorValue[bumperRight]==0)
		{
			StartTask(intakeBallOut);
			if(time1[T4]>12000)
			{
				intake=-1;
				wait10Msec(50);
				moveStraightDistance(127,900);
				moveStraightDistance(-127,300);
				while(true)
				{
				}
			}
		}
		armDelay = 1500;
		armPos = 1100;
		StartTask(armToPos);
		moveStraightDistance(127,1100);
		intake = -1;
		wait10Msec(100);

		/*
		intake = 1;
		moveSecondTierUp(127,450);
		moveSecondTierDown(127,50);
		motor[secondTier]=-127;
		wait10Msec(50);
		motor[secondTier]=0;
		moveStraightDistance(100,50);
		stopPid(0.6,0.3);
		intake = 0;
		moveStraightDistance(127,1800);
		stopPid(0.6,0.3);
		moveFirstTierUp(127,1200);
		motor[firstTierLeft]=20;
		motor[firstTierRight]=20;
		moveStraightDistance(127,200);
		stopPid(0.6,0.3);
		intake = -1;
		wait10Msec(300);
		intake = 0;
		moveStraightDistance(-127,200);
		stopPid(0.6,0.3);
		moveFirstTierDown(127,20);
		turnRight(127,70);
		moveStraightDistance(-127,1500);
		while(SensorValue[bumperLeft]==0)
		{
		}
		moveStraightDistance(127,100);
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
		turnRight(127,250);
		moveFirstTierUp(127,900);
		moveStraightDistance(100,800);
		stopPid(0.6,0.3);
		stopLift();
		moveStraightDistance(-100,100);
		stopPid(0.6,0.3);
		*/
	}
	else if(programs ==3)
	{
		StartTask(intakeStart);
		ClearTimer(T4);
		armPos = 900;
		armDelay = 0;
		StartTask(armToPos);
		// Raise arm to push
		wait10Msec(100);
		moveStraightDistance(127,600);
		stopPid(0.6,0.3);
		StopTask(armToPos);
		armPos = 0;
		armDelay = 0;
		StartTask(armToPos);
		tierPos=450;
		tierDelay=0;
		StartTask(tierToPos);
		// Deploy
		intake = 1;
		moveStraightDistance(-127,300);
		stopPid(0.6,0.3);
		while(SensorValue[bumperLeft]==0&&SensorValue[bumperRight]==0)
		{
			intake = 0;
		}
		StopTask(armToPos);
		armPos = 900;
		armDelay=0;
		StartTask(armToPos);
		moveStraightDistance(100,300);
		stopPid(0.6,0.3);
		alignFoward(100);
		turnLeft(127,250);
		moveStraightDistance(100,900);
		stopPid(0.6,0.3);
		moveStraightDistance(-100,100);
		stopLift();
		turnRight(127,150);
		moveStraightDistance(-100,700);
		stopPid(0.6,0.3);
		while(SensorValue[bumperLeft]==0&&SensorValue[bumperRight]==0)
		{
			StartTask(intakeBallOut);
			if(time1[T4]>12000)
			{
				intake=-1;
				moveStraightDistance(127,900);
				moveStraightDistance(-127,300);
				while(true)
				{
				}
			}
		}
		armDelay=1500;
		armPos = 1100;
		StartTask(armToPos);
		moveStraightDistance(127,1100);
		intake = -1;
		wait10Msec(100);
		/*Mid Right*/
		/*
		StartTask(intakeStart);
		ClearTimer(T4);
		intake = 1;
		moveSecondTierUp(127,450);
		moveSecondTierDown(127,50);
		motor[secondTier]=-127;
		wait10Msec(50);
		motor[secondTier]=0;
		moveStraightDistance(100,50);
		stopPid(0.6,0.3);
		intake = 0;
		moveStraightDistance(127,1800);
		stopPid(0.6,0.3);
		moveFirstTierUp(127,1200);
		motor[firstTierLeft]=20;
		motor[firstTierRight]=20;
		moveStraightDistance(127,200);
		stopPid(0.6,0.3);
		intake = -1;
		wait10Msec(300);
		intake = 0;
		moveStraightDistance(-127,200);
		stopPid(0.6,0.3);
		moveFirstTierDown(127,20);
		turnLeft(127,70);
		moveStraightDistance(-127,1500);
		while(SensorValue[bumperLeft]==0)
		{
		}
		moveStraightDistance(127,100);
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
		*/
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{

		// Setting controller override
		// Default - two controller
		/* bool override = false;
		if (vexRT[Btn7U] == 1 && vexRT[Btn8U] == 1)
		{
		override = !override;
		}
		*/

		// Two controllers
		// if (override == false) // Button to override
		if (nVexRCReceiveState & vrXmit2)
		{
			{
				/* Left Drive */
				motor[leftFront] = vexRT[Ch3];
				motor[leftMiddle] = vexRT[Ch3];
				motor[leftBack] = vexRT[Ch3];

				/* Right Drive */
				motor[rightFront] = vexRT[Ch2];
				motor[rightMiddle] = vexRT[Ch2];
				motor[rightBack] = vexRT[Ch2];

				/* Intake and Lift [Controller 2] */
				// First Tier
				motor[firstTierLeft] = vexRT[Ch2Xmtr2];
				motor[firstTierRight] = vexRT[Ch2Xmtr2];

				// Second Tier
				motor[secondTier] = vexRT[Ch3Xmtr2];

				/* Intake Rollers [Controller 2] */
				// Intake push out
				if (vexRT[Btn6UXmtr2] == 1)
				{
					motor[intakeRollers] = -127;
				}
				// Intake suck in
				else if (vexRT[Btn5UXmtr2] == 1)
				{
					motor[intakeRollers] = 127;
				}
				// Unpressed
				else
				{
					motor[intakeRollers] = 0;
				}
			}
		}
		// One controller
		else
		{

			/* Drive //
			motor[leftBack] = cubicMap(vexRT[Ch2]+ vexRT[Ch4]);
			motor[leftMiddle] = cubicMap(vexRT[Ch2]+ vexRT[Ch4]);
			motor[leftFront] = cubicMap(vexRT[Ch2]+ vexRT[Ch4]);
			motor[rightBack] = cubicMap(vexRT[Ch2]- vexRT[Ch4]);
			motor[rightMiddle] = cubicMap(vexRT[Ch2]- vexRT[Ch4]);
			motor[rightFront] = cubicMap(vexRT[Ch2]- vexRT[Ch4]);
			*/
			/* Left Drive */
			motor[leftFront] = vexRT[Ch3];
			motor[leftMiddle] = vexRT[Ch3];
			motor[leftBack] = vexRT[Ch3];

			/* Right Drive */
			motor[rightFront] = vexRT[Ch2];
			motor[rightMiddle] = vexRT[Ch2];
			motor[rightBack] = vexRT[Ch2];

			/* First Tier */
			if (vexRT[Btn6U] == 1)
			{
				motor[firstTierLeft] = 127;
				motor[firstTierRight] = 127;
			}
			else if (vexRT[Btn6D] == 1)
			{
				motor[firstTierLeft] = -127;
				motor[firstTierRight] = -127;
			}
			else
			{
				motor[firstTierLeft] = 0;
				motor[firstTierRight] = 0;
			}

			/* Second Tier */
			if (vexRT[Btn8R] == 1)
			{
				motor[secondTier] = 127;
			}
			else if (vexRT[Btn8D] == 1)
			{
				motor[secondTier] = -127;
			}
			else
			{
				motor[secondTier] = 0;
			}

			/* Intake */
			if (vexRT[Btn5U] == 1)
			{
				motor[intakeRollers] = 127;
			}
			else if (vexRT[Btn5D] == 1)
			{
				motor[intakeRollers] = -127;
			}
			else
			{
				motor[intakeRollers] = 0;
			}
		}

		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.

		// .....................................................................................
		// Insert user code here. This is where you use the joystick values to update your motors, etc.
		// .....................................................................................

	}
}
