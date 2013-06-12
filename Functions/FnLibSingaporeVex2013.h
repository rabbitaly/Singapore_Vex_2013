// Move forward = positive power, Move backward = negative power
// Move straight until the distance is met
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
void moveStraightLight(int power, int whiteLineVal)
{
	while (SensorValue[leftLight] > whiteLineVal && SensorValue[rightLight] > whiteLineVal)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
	}
	if (SensorValue[leftLight] < whiteLineVal)
	{
		while (SensorValue[rightLight] < whiteLineVal)
		{
			motor[leftBack] = 0;
			motor[leftMiddle] = 0;
			motor[leftFront] = 0;
			motor[rightBack] = power;
			motor[rightMiddle] = power;
			motor[rightFront] = power;
		}
	}
	else if (SensorValue[rightLight] < whiteLineVal)
	{
		while (SensorValue[leftLight] < whiteLineVal)
		{
			motor[leftBack] = power;
			motor[leftMiddle] = power;
			motor[leftFront] = power;
			motor[rightBack] = 0;
			motor[rightMiddle] = 0;
			motor[rightFront] = 0;
		}
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
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
	while (abs(SensorValue[backLeft]) < 100 && abs(SensorValue[backRight]) < 100)
	{
		motor[firstTierLeft] = power;
		motor[firstTierRight] = power;
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
void pushBridge(int power, int distanceBeforeBridge, int angle)
{
	SensorValue[backLeft] = 0;
	SensorValue[backRight] = 0;
	while (abs(SensorValue[backLeft]) < distanceBeforeBridge && abs(SensorValue[backRight]) < distanceBeforeBridge)
	{
		motor[leftBack] = power;
		motor[leftMiddle] = power;
		motor[leftFront] = power;
		motor[rightBack] = power;
		motor[rightMiddle] = power;
		motor[rightFront] = power;
	}
	while (abs(SensorValue[firstTierLeft]) < angle)
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
	while (abs(SensorValue[firstTierLeft]) > 100)
	{
		motor[firstTierLeft] = -127;
		motor[firstTierRight] = -127;
		motor[leftBack] = -20;
		motor[leftMiddle] = -20;
		motor[leftFront] = -20;
		motor[rightBack] = -20;
		motor[rightMiddle] = -20;
		motor[rightFront] = -20;
	}
	motor[firstTierLeft] = 0;
	motor[firstTierRight] = 0;
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
void moveSharpRight(int power, int distance)
{
	SensorValue[backLeft] = 0;
	while (abs(SensorValue[backLeft]) < distance)
	{
		motor[leftBack] = abs(power);
		motor[leftMiddle] = abs(power);
		motor[leftFront] = abs(power);
		motor[rightBack] = 0;
		motor[rightMiddle] = 0;
		motor[rightFront] = 0;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
}

// Move Sharp Left
void moveSharpRight(int power, int distance)
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
	while (abs(SensorValue[firstTierLeft]) < angle)
	{
		motor[firstTierLeft] = abs(power);
		motor[firstTierRight] = abs(power);
	}
	motor[firstTierLeft] = 0;
	motor[firstTierRight] = 0;
}

void moveFirstTierDown(int power, int angle)
{
	while(abs(SensorValue[firstTierLeft]) > angle)
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
	motor[secondTier] = power;
	wait10Msec(50);
	while(true)
	{
		if(SensorValue[secondTier] > angle)
		{
			//break;
		}
	}
	motor[secondTier] = 0;
}

void moveSecondTierDown(int power, int angle)
{
	while(abs(SensorValue[secondTier]) > abs(angle))
	{
		motor[secondTier] = -abs(power);
	}
	motor[secondTier] = 0;
}

// Intake Suck In [Time]
void intakeSuckTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		motor[intakeRollers] = -1 * abs(power);
	}
	motor[intakeRollers] = 0;
}

// Intake Push Out [Time]
void intakePushTime(int power, int time)
{
	ClearTimer(T1);
	while (time1[T1] < time)
	{
		motor[intakeRollers] = abs(power);
	}
	motor[intakeRollers] = 0;
}

// Intake Suck In
void intakeSuck(int power)
{
	motor[intakeRollers] = -abs(power);
}

// Intake Push Out
void intakePush(int power)
{
	motor[intakeRollers] = abs(power);
}

// Intake while moving
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
		motor[intakeRollers] = -127;
	}
	motor[leftBack] = 0;
	motor[leftMiddle] = 0;
	motor[leftFront] = 0;
	motor[rightBack] = 0;
	motor[rightMiddle] = 0;
	motor[rightFront] = 0;
	motor[intakeRollers] = 0;
}

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
