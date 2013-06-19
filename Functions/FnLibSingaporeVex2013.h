// Constant definition
// lightfrwhite is the right light value of white lines
#define lightfrwhite 2500
// left light value
#define lightflwhite 2400
// mid white value
#define lightmidwhite 2400
int stopat;

void moveStraightDistance(int power, int distance)
{
	// Reset sensor values for further use
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	// Ignore error, old error, p, d and adjust for now, not implemented
	int error,olderror;
	float p = 0.9;
	float d=0.5;
	int adjust;
	// While either values of the sensor are below demand, it will continue to move according to power set
	// Absolute values are put in place as the encoders are not necessarily put correctly such that both are positive
	while (abs(SensorValue[backLeft]) < distance && abs(SensorValue[backRight]) < distance)
	{
		error = abs(SensorValue[backRight]) - abs(SensorValue[backLeft]);
		adjust = (int)(error*p+olderror*d);
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
	}
	// stopat is the average value of the encoders to know where to stop
	stopat = (abs(SensorValue[backRight])+abs(SensorValue[backLeft]))/2;
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// A function to stop where the robot is supposed to be and used in conjunction with moveStraightDistance
void stopPid(float p,float d)
{
	float error;
	float olderror=0;
	int adjust = 127;

	// While adjust, being the distance difference, is still greater than +- 15, it will continue to adjust
	while(adjust>15||adjust<-15)
	{
		// Error is the value of stopat minus the average of the values of the encoder now, knowing the error to fix, usually around or below 100
		error = stopat-((abs(SensorValue[backRight])+abs(SensorValue[backLeft]))/2);
		// P_error is the decimal value of error multiplied by p, a decimal value, basically the sensitivity of the error
		float p_error = error*p;
		// D_error is the error that still needs to be covered after adjusting, multiplied by d, another tuning value
		float d_error = (error-olderror)*d;
		// Adjust is set to the integer value of the sum of p_error and d_error
		adjust = (int)p_error+d_error;
		// Motor speed is then set to the adjust values, so to reduce error
		motor[leftBack] = adjust;
		motor[leftMiddle] = adjust;
		motor[leftFront] = adjust;
		motor[rightBack] = adjust;
		motor[rightMiddle] = adjust;
		motor[rightFront] = adjust;
		// Before the while loop ends, the old error is set to current error, then used in d_error to continue to reduce the error
		olderror = error;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

void moveStraightLight(int power)
{
	// while left sensor is greater than the light value of white (the less light detected, the higher the value) motor continues to move
	while (SensorValue[leftLight] > lightflwhite)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Function to align backwards to the line (Has greater errors)
void align()
{
	// Reverse until left light sensor detects white light
	while (SensorValue[leftLight] > lightflwhite)
	{
		motor[leftBack] = -40;
		motor[leftMiddle] = -40;
		motor[leftFront] = -40;
		motor[rightBack] = 0;
		motor[rightMiddle] = 0;
		motor[rightFront] = 0;
	}
	motor[rightBack] = 20;
	motor[rightMiddle] = 20;
	motor[rightFront] = 20;
	// Then reverse the other side until the other side also aligns to light
	while (SensorValue[rightLight] > lightfrwhite)
	{
		motor[leftBack] = 0;
		motor[leftMiddle] = 0;
		motor[leftFront] = 0;
		motor[rightBack] = -40;
		motor[rightMiddle] = -40;
		motor[rightFront] = -40;
	}
}

// Moves forward until detected light, then aligns properly to light
void alignFoward(int power)
{
	string detected;
	// Continues to move while either sees darker than light
	while(SensorValue[leftLight] > lightflwhite||SensorValue[rightLight] > lightfrwhite)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
		// If left sees white light or brighter, sets detected to left for further use
		if (SensorValue[leftLight] <= lightflwhite)
		{
			detected = "left";
			break;
		}
		// If right sees white light or brighter, sets detected to right for further use
		else if (SensorValue[rightLight] <= lightfrwhite)
		{
			detected = "right";
			break;
		}
		// If both don't detect, sets detected to none and continue to move
		else
		{
			detected = "none";
		}
	}
	// If detected is left, it will move right motors until it is also aligned to line
	if (detected == "left")
	{
		while (SensorValue[rightLight] > lightfrwhite)
		{
			motor[rightBack] = 60;
			motor[rightMiddle] = 60;
			motor[rightFront] = 60;
			motor[leftBack]=-30;
			motor[leftMiddle]=-30;
			motor[leftFront]=-30;
		}
	}
	// If detected is not left but is right, it will move left motors until it is also aligned to line
	else if (detected == "right")
	{
		while (SensorValue[leftLight] > lightflwhite)
		{
			motor[leftBack] = 60;
			motor[leftMiddle] = 60;
			motor[leftFront] = 60;
			motor[rightBack]=-30;
			motor[rightMiddle]=-30;
			motor[rightFront]=-30;
		}
	}
	// Stop all motors after aligning
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack]=0;
	motor[rightMiddle]=0;
	motor[rightFront]=0;
}

// Move all motors to power
void moveStraight(int power)
{
	motor[leftBack] = power;
	motor[leftMiddle] = power;
	motor[leftFront] = power;
	motor[rightBack] = power;
	motor[rightMiddle] = power;
	motor[rightFront] = power;
}

// Moves all motors to power for set amount of time
void moveStraightTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Cross Ramp
// Move straight until ramp
// Lift up first tier during ramp
// Drop first tier and move straight after ramp
void crossRamp(int power, int distance, int distanceBeforeRamp)
{
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < distanceBeforeRamp && abs(SensorValue[backRight]) < distanceBeforeRamp)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
	}
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < 600 && abs(SensorValue[backRight]) < 600)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
		motor[firstTierLeft] = 60;
		motor[firstTierRight] = 60;
	}
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < distance && abs(SensorValue[backRight]) < distance)
	{
		motor[firstTierLeft] = 0;
		motor[firstTierRight] = 0;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Push ball off bridge
void pushBridge(int power, int angle)
{
	// While first tier left potentiometer is below set angle, move motor forward slowly and raise arms
	while (abs(SensorValue[in1]) < angle)
	{
		motor[leftBack] = 20;
		motor[leftMiddle] = 20;
		motor[leftFront] = 20;
		motor[rightBack] = 20;
		motor[rightMiddle] = 20;
		motor[rightFront] = 20;
		motor[firstTierLeft] = power;
		motor[firstTierRight] = power;
	}
	// Motor of arm set to 20 to maintain position
	motor[firstTierLeft] = 20;
	motor[firstTierRight] = 20;
	wait10Msec(50);
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Turn right
void turnRight(int power, int distance)
{
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < distance && abs(SensorValue[backRight]) < distance)
	{
		motor[leftBack] = abs(power);
		motor[leftMiddle] = abs(power);
		motor[leftFront] = abs(power);
		motor[rightBack] = -abs(power);
		motor[rightMiddle] = -abs(power);
		motor[rightFront] = -abs(power);
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Turn left
void turnLeft(int power, int distance)
{
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < distance && abs(SensorValue[backRight
		]) < distance)
	{
		motor[leftBack] = -1 * abs(power);
		motor[leftMiddle] = -1 * abs(power);
		motor[leftFront] = -1 * abs(power);
		motor[rightBack] = abs(power);
		motor[rightMiddle] = abs(power);
		motor[rightFront] = abs(power);
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move Sharp Right
// More freedom with powers
void moveSharpRight(int power, int secondPower, int distance)
{
	SensorValue[backLeft] = 0;
	while (abs(SensorValue[backLeft]) < distance)
	{
		motor[leftBack] = abs(power);
		motor[leftMiddle] = abs(power);
		motor[leftFront] = abs(power);
		motor[rightBack] = secondPower;
		motor[rightMiddle] = secondPower;
		motor[rightFront] = secondPower;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move Sharp Left
// More freedom with powers
void moveSharpLeft(int power, int secondPower, int distance)
{
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backRight]) < distance)
	{
		motor[leftBack] = secondPower;
		motor[leftMiddle] = secondPower;
		motor[leftFront] = secondPower;
		motor[rightBack] = abs(power);
		motor[rightMiddle] = abs(power);
		motor[rightFront] = abs(power);
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move Gentle Right
void moveGentleRight(int power, int distance)
{
	SensorValue[backLeft] = 0;
	while (abs(SensorValue[backLeft]) < distance)
	{
		motor[leftBack] = abs(power);
		motor[leftMiddle] = abs(power);
		motor[leftFront] = abs(power);
		motor[rightBack] = abs(power) - 60;
		motor[rightMiddle] = abs(power) - 60;
		motor[rightFront] = abs(power) - 60;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move Gentle Left
void moveGentleRight(int power, int distance)
{
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backRight]) < distance)
	{
		motor[leftBack] = abs(power) - 60;
		motor[leftMiddle] = abs(power) - 60;
		motor[leftFront] = abs(power) - 60;
		motor[rightBack] = abs(power);
		motor[rightMiddle] = abs(power);
		motor[rightFront] = abs(power);
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move First Tier
// Raise first tier with power to desired angle
void moveFirstTierUp(int power, int angle)
{
	while (abs(SensorValue[in1]) < angle)
	{
		motor[firstTierLeft] = abs(power);
		motor[firstTierRight] = abs(power);
	}
	motor[firstTierLeft] = 0;
	motor[firstTierRight] = 0;
}
// Raise first tier with power to desired angle
void moveFirstTierDown(int power, int angle)
{
	while(abs(SensorValue[in1]) > angle)
	{
		motor[firstTierLeft] = -abs(power);
		motor[firstTierRight] = -abs(power);
	}
	motor[firstTierLeft] = 0;
	motor[firstTierRight] = 0;
}

// Move Second Tier
void moveSecondTierUp(int power, int angle)
{
	while(SensorValue[in2] < angle)
	{
		motor[secondTier] = power;
	}
	motor[secondTier] = 0;
}

void moveSecondTierDown(int power, int angle)
{
	while(SensorValue[in2] > angle)
	{
		motor[secondTier] = -power;
	}
	motor[secondTier] = 0;
}

// Intake Suck In [Time]
// Replaceable with the intake task
void intakeSuckTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		motor[intakeRollers] = abs(power);
	}
	motor[intakeRollers] = 0;
}

// Intake Push Out [Time]
// Replaceable with intake task
void intakePushTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		motor[intakeRollers] = abs(power);
		// intake = -1;
	}
	motor[intakeRollers] = 0;
	// intake = 0;
}

// Intake Suck In
// Replaceable with intake task
void intakeSuck(int power)
{
	motor[intakeRollers] = abs(power);
	// intake = 1;
}

// Intake Push Out
// Replaceable with intake task
void intakePush(int power)
{
	motor[intakeRollers] = -abs(power);
	// intake = -1;
}

/* Intake while moving
void intakeWhileMoving(int power, int distance)
{
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < distance && abs(SensorValue[backRight]) < distance)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
		// motor[intakeRollers] = -127;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
	// motor[intakeRollers] = 0;
}
*/

// Stop all
void stopAll()
{
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
	motor[firstTierLeft] = 0;
	motor[firstTierRight] = 0;
	motor[secondTier] = 0;
	motor[intakeRollers] = 0;
}

// Stop drive
void stopDrive()
{
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

void stopLift()
{
	motor[firstTierLeft] = 0;
	motor[firstTierRight] = 0;
	motor[secondTier] = 0;
}
