#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"

int main(void)
{
	uint32_t t,i=0;

	TFC_Init();

	int Line[128];
	int maxVal = 0;
	int minVal = 0;
	int i;

	// Edge detection default
	int center = 64;
	int Redge = 123;
	int Ledge = 10;

	float ServoVal0 = 0.0;
	float ServoVal1 = 0.0;

	float MotorVal0 = 0.8;
	float MotorVal1 = -1 * MotorVal0;

	for(;;)
	{
		//TFC_Task must be called in your main loop.  This keeps certain processing happy (I.E. Serial port queue check)
			TFC_Task();

			//This Demo program will look at the middle 2 switch to select one of 4 demo modes.
			//Let's look at the middle 2 switches
			switch((TFC_GetDIP_Switch()>>1)&0x03)
			{
			default:
			case 0 :
				//Demo mode 0 just tests the switches and LED's
				if(TFC_PUSH_BUTTON_0_PRESSED)
					TFC_BAT_LED0_ON;
				else
					TFC_BAT_LED0_OFF;

				if(TFC_PUSH_BUTTON_1_PRESSED)
					TFC_BAT_LED3_ON;
				else
					TFC_BAT_LED3_OFF;


				if(TFC_GetDIP_Switch()&0x01)
					TFC_BAT_LED1_ON;
				else
					TFC_BAT_LED1_OFF;

				if(TFC_GetDIP_Switch()&0x08)
					TFC_BAT_LED2_ON;
				else
					TFC_BAT_LED2_OFF;

				break;

			/*case 1:

				//Demo mode 1 will just move the servos with the on-board potentiometers
				if(TFC_Ticker[0]>=20)
				{
					TFC_Ticker[0] = 0; //reset the Ticker
					//Every 20 mSeconds, update the Servos
					TFC_SetServo(0,TFC_ReadPot(0));
					TFC_SetServo(1,TFC_ReadPot(1));
				}

				//Let's put a pattern on the LEDs
				if(TFC_Ticker[1] >= 125)
				{
					TFC_Ticker[1] = 0;
					t++;
					if(t>4)
					{
						t=0;
					}
					TFC_SetBatteryLED_Level(t);
				}

				TFC_SetMotorPWM(0,0); //Make sure motors are off
				TFC_HBRIDGE_DISABLE;


				break;*/

			case 1:

			// EDGE DETECTION BEGIN //////////////////////////////
			LineScanImage0 = Line;			// copy line image

			for (i = 2; i < 125; i++) {
				// find max dip
				if ((Line[i] - Line[i-1]) > maxVal)
					maxVal = Line[i];
				// find min dip
				else if ((Line[i] - Line[i-1]) > minVal)
					minVal = Line[i];
			}

			// get edge indices
			for (i = 0; i < 127; i++) {
				// left edge
				if (Line[i] > 0.8 * maxVal)
					Ledge = i;
				// right edge
				else if (Line[i] < 0.8 * minVal)
					Redge = i;
			}
			// EDGE DETECTION END ////////////////////////////////

			// ADJUST CENTER //////////////////////////////////////////
			if (Redge <= 5)
				// car too far right
				center = Redge - 40;
			else if (Ledge >= 123)
			  // car too far left
				center = Ledge + 40;
			else
				// car in acceptable range
				center = (Ledge + Redge) / 2;
			// ADJUST CENTER END //////////////////////////////////////

			// ADJUST SERVO POS BEGIN ///////////////////////////////
			if (center > 66) {
				ServoVal0 = ServoVal0 + 0.10;			//turn right (must fine-tune)
				ServoVal1 = ServoVal1 + 0.10;
			} else if (center < 62) {
				ServoVal0 = ServoVal0 - 0.10;			// turn left (must fine-tune)
				ServoVal1 = ServoVal1 - 0.10;
			} else if ((center >= 62) && (center <= 66)) {
				ServoVal0 = 0.0;									// keep servos straight
				ServoVal1 = 0.0;
			}
			// ADJUST SERVO POS END /////////////////////////////////

			// ADJUST MOTOR SPEED BEGIN /////////////////////////////
			if (((center >= 0) && (center < 16)) || ((center >= 112) && (center <= 127))) {
				// way to the left
				MotorVal0 = 0.2;
			} else if (((center >= 16) && (center < 32)) || ((center >= 96) && (center < 112))) {
				// pretty far left OR pretty far right
				MotorVal0 = 0.4;
			} else if (((center >= 32) && (center < 48)) || ((center >= 80) && (center < 96))) {
				// kind of to the left OR kind of to the right
				MotorVal0 = 0.6;
			} else if ((center >= 48) && (center < 80)) {
				// centered! yay!
				MotorVal0 = 0.8;
			}
			MotorVal1 = -1.0 * MotorVal0;
			// ADJUST MOTOR SPEED END ///////////////////////////////

				if(TFC_Ticker[0]>=20)
				{
					TFC_Ticker[0] = 0; //reset the Ticker
					//Every 20 mSeconds, update the Servos
					TFC_SetServo(0,ServoVal0);
					TFC_SetServo(1,ServoVal1);
				}

				TFC_HBRIDGE_ENABLE;
				TFC_SetMotorPWM(MotorVal0,MotorVal1);

				//Let's put a pattern on the LEDs
				if(TFC_Ticker[1] >= 125)
				{
						TFC_Ticker[1] = 0;
						t++;
						if(t>4)
						{
								t=0;
						}
						TFC_SetBatteryLED_Level(t);
				}

				//TFC_SetMotorPWM(0,0); //Make sure motors are off
				//TFC_HBRIDGE_DISABLE;


				break;

			case 2 :

				//Demo Mode 2 will use the Pots to make the motors move
				TFC_HBRIDGE_ENABLE;
				TFC_SetMotorPWM(TFC_ReadPot(0),TFC_ReadPot(1));

				//Let's put a pattern on the LEDs
				if(TFC_Ticker[1] >= 125)
					{
						TFC_Ticker[1] = 0;
							t++;
							if(t>4)
							{
								t=0;
							}
						TFC_SetBatteryLED_Level(t);
					}
				break;

			case 3 :

				//Demo Mode 3 will be in Freescale Garage Mode.  It will beam data from the Camera to the
				//Labview Application


				if(TFC_Ticker[0]>100 && LineScanImageReady==1)
					{
					 TFC_Ticker[0] = 0;
					 LineScanImageReady=0;
					 TERMINAL_PRINTF("\r\n");
					 TERMINAL_PRINTF("L:");

					 	if(t==0)
					 		t=3;
					 	else
					 		t--;

						 TFC_SetBatteryLED_Level(t);

						 for(i=0;i<128;i++)
						 {
								 TERMINAL_PRINTF("%X,",LineScanImage0[i]);
						 }

						 for(i=0;i<128;i++)
						 {
								 TERMINAL_PRINTF("%X",LineScanImage1[i]);
								 if(i==127)
									 TERMINAL_PRINTF("\r\n",LineScanImage1[i]);
								 else
									 TERMINAL_PRINTF(",",LineScanImage1[i]);
						}

					}



				break;
			}
	}

	return 0;
}
