#pragma config(Sensor, S1,     Bump,           sensorEV3_Touch)
#pragma config(Sensor, S2,     Touch,          sensorEV3_Touch)
#pragma config(Sensor, S3,     Color,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     Angle,          sensorEV3_Gyro)
#pragma config(Motor,  motorA,          engineA,       tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          engineB,       tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          SengineC,      tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void driveWithSensor(int duration);
void Trackcorrection();
void turn90Degrees();
void rotateMotorD();
void turnBack ();
void driveBackWithSensor(int duration);

task main(){
	short currentColour;
	bool isTouchSensorPressed;
	resetGyro(S4);


	while (true)
	{
		// Colours range from 0 to 7
		// None    = 0
		// Black   = 1
		// Blue    = 2
		// Green   = 3
		// Yellow  = 4
		// Red     = 5
		// White   = 6
		// Brown   = 7

		currentColour = SensorValue[Color];
		isTouchSensorPressed = SensorValue(S2) == 1;

		if (currentColour != 0 && isTouchSensorPressed) {

			clearTimer(T1);

			switch(currentColour)
			{
			case 1:
				displayCenteredBigTextLine(4, "black");
				break;
			case 2:
				displayCenteredBigTextLine(4, "blue");
				driveWithSensor(11000);
				Trackcorrection();
				turn90Degrees();
				rotateMotorD();
				turnBack();
				driveBackWithSensor (11000);
				break;
			case 3:
				displayCenteredBigTextLine(4, "green");
				driveWithSensor(5000);
				Trackcorrection();
				turn90Degrees();
				rotateMotorD();
				turnBack();
				driveBackWithSensor (5000);
				break;
			case 4:
				displayCenteredBigTextLine(4, "yellow");
				driveWithSensor(8000);
				Trackcorrection();
				turn90Degrees();
				rotateMotorD();
				turnBack();
				driveBackWithSensor (8000);
				break;
			case 5:
				displayCenteredBigTextLine(4, "red");
				driveWithSensor(14000);
				Trackcorrection();
				turn90Degrees();
				rotateMotorD();
				turnBack();
				driveBackWithSensor (14000);
				break;
			case 6:
				displayCenteredBigTextLine(4, "white");
				driveWithSensor(17000);
				Trackcorrection();
				turn90Degrees();
				rotateMotorD();
				turnBack();
				driveBackWithSensor (17000);break;
			case 7:
				displayCenteredBigTextLine(4, "brown"); break;
			default:
				displayCenteredBigTextLine(4, "unknown");
			}
			displayCenteredBigTextLine(6, "Time: %d ms", time1[T1]);

			// 20ms warten
			sleep(20);
		}
	}
}
void driveWithSensor(int duration) {
	int startTime = time1[T1];
	int remainingDuration = duration;

	while (time1[T1] - startTime < duration) {
		setMotor(motorA, 20);
		setMotor(motorB, 20);

		if (SensorValue(S1)==1) {
			// Motoren stoppen
			stopMotor(motorA);
			stopMotor(motorB);
		}
		while((SensorValue(S1) == 0) && getButtonPress(buttonAny))
		// motorische Bewegung wieder aufnehmen
		setMotor(motorA, 20);
		setMotor(motorB, 20);

		// verbleibende Zeitdauer aktualisieren
		remainingDuration = duration - (startTime-time1[T1]  );
	}

	//Motoren am Ende der Funktion stoppen
	stopMotor(motorA);
	stopMotor(motorB);
}
void Trackcorrection(){
	if (SensorValue[S4]<-2){
		// Wenn der Sensorwert von Sensor S3 gleich 3 ist oder der Sensorwert von Sensor S4 kleiner als -3 ist
		setMotor(motorA,20);
		setMotor(motorB,-20);
	}
	else if(SensorValue[S4] > 2) {
		// Wenn der Sensorwert von Sensor S4 gr��er als 3 ist
		setMotor(motorA,-20);
		setMotor(motorB,20);
	}
}
void turn90Degrees() {
	repeatUntil(getGyroHeading(S4) == 89) {
		setMotor(motorA, 5);
		setMotor(motorB, -5);
	}
	stopMotor(motorA);
	stopMotor(motorB);
}
void rotateMotorD() {
	// Motor D um 90 Grad drehen
	moveMotorTarget(motorD, 90, 10);
	sleep(1000);
	//Motor D zur�ck in die Ausgangsposition drehen
	moveMotorTarget(motorD, 90, -10);
	waitUntilMotorStop(motorD);
}

void turnBack() {
	//Drehen bis der Kurs des Gyrosensor -2 ist
	repeatUntil(getGyroHeading(S4) == -2) {
		setMotor(motorA, -5);
		setMotor(motorB, 5);
	}
	//Motoren nach dem Zur�ckdrehen stoppen
	stopMotor(motorA);
	stopMotor(motorB);
}

void driveBackWithSensor(int duration) {
	int startTime = time1[T1];
	while (time1[T1] - startTime < duration) {
		setMotor(motorA,-20);
		setMotor(motorB,-20);
	}
	if (SensorValue[S4]<-2){
		// Wenn der Sensorwert von Sensor S4 gleich 3 ist oder der Sensorwert von Sensor S4 kleiner als -3 ist
		setMotor(motorA,20);
		setMotor(motorB,-20);
	}

	else if(SensorValue[S4] > 2) {
		// Wenn der Sensorwert von Sensor S4 gr��er als 3 ist
		setMotor(motorA,-20);
		setMotor(motorB,20);
	}
	stopMotor(motorA);
	stopMotor(motorB);
}
