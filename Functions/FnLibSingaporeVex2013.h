// Move forward = positive power, Move backward = negative power
// Move straight until the distance is met
#define lightfrwhite 2500
#define lightflwhite 2400
#define lightmidwhite 2400
int stopat;
void moveStraightDistance(int power, int distance)
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
	}
	stopat = (abs(SensorValue[backRight])+abs(SensorValue[backLeft]))/2;
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move straight and align to line
// Stops when either or both sensors detect white line
// Auto align to position both sensors to detect white line

void stopPid(float p,float d)
{
	float error;
	float olderror=0;
	int adjust = 127;

	while(adjust>15||adjust<-15)
	{
		error = stopat-((abs(SensorValue[backRight])+abs(SensorValue[backLeft]))/2);
		float p_error = error*p;
		float d_error = (error-olderror)*d;
		adjust = (int)p_error+d_error;
		motor[leftBack] = adjust;
		motor[leftMiddle] = adjust;
		motor[leftFront] = adjust;
		motor[rightBack] = adjust;
		motor[rightMiddle] = adjust;
		motor[rightFront] = adjust;
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
void align()
{
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
void alignFoward(int power)
{
	string detected;
	while(SensorValue[leftLight] > lightflwhite||SensorValue[rightLight] > lightfrwhite)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;

		if (SensorValue[leftLight] <= lightflwhite)
		{
			detected = "left";
			break;
		}
		else if (SensorValue[rightLight] <= lightfrwhite)
		{
			detected = "right";
			break;
		}
		else
		{
			detected = "none";

		}
	}

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
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack]=0;
	motor[rightMiddle]=0;
	motor[rightFront]=0;

}
void moveStraight(int power)
{
	motor[leftBack] = power;
	motor[leftMiddle] = power;
	motor[leftFront] = power;
	motor[rightBack] = power;
	motor[rightMiddle] = power;
	motor[rightFront] = power;
}

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
// Move straight before ramp
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
		motor[firstTierLeft] = 40;
		motor[firstTierRight] = 40;
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

// Push ball off bridge *MAKE SURE POSITIONED PERPENDICULAR TO BRIDGE*
void pushBridge(int power, int angle)
{
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
	motor[leftBack] = 127;
	motor[leftMiddle] = 127;
	motor[leftFront] = 127;
	motor[rightBack] = 127;
	motor[rightMiddle] = 127;
	motor[rightFront] = 127;
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
void moveSharpRight(int power, int secondPower, int distance)
{
	SensorValue[backLeft] = 0;
	while (abs(SensorValue[backLeft]) < distance)
	{
		motor[leftBack] = abs(power);
		motor[leftMiddle] = abs(power);
		motor[leftFront] = abs(power);
		motor[rightBack] = abs(secondPower);
		motor[rightMiddle] = abs(secondPower);
		motor[rightFront] = abs(secondPower);
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move Sharp Left
void moveSharpLeft(int power, int distance)
{
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backRight]) < distance)
	{
		motor[leftBack] = 0;
		motor[leftMiddle] = 0;
		motor[leftFront] = 0;
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
void intakeSuckTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		// motor[intakeRollers] = -1 * abs(power);
		// intake = 1;
	}
	// motor[intakeRollers] = 0;
	// intake = 0;
}

// Intake Push Out [Time]
void intakePushTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		// motor[intakeRollers] = abs(power);
		// intake = -1;
	}
	// motor[intakeRollers] = 0;
	// intake = 0;
}

// Intake Suck In
void intakeSuck(int power)
{
	// motor[intakeRollers] = -abs(power);
	// intake = 1;
}

// Intake Push Out
void intakePush(int power)
{
	// motor[intakeRollers] = abs(power);
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
