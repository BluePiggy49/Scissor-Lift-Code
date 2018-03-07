#include "WPILib.h"
#include "ctre/Phoenix.h"
#include <iostream>
#include <math.h>
#include <scissor.h>

#define TALON_TIMEOUT_MILLISECONDS 10

// TODO: Set the SRX up as a regular talon...?
// Set up velocity controls
// Set the feedback device to the encoder

class Robot : public IterativeRobot {
	private:

		TalonSRX *talon_left_noenc, *talon_left_enc, *talon_right_enc, *talon_right_noenc;
		Joystick *joystick;
		ScissorLift *scissor;

		bool buttonstate_Y = false;
        bool Y_Button = false;
        bool Turning_Y_Button_On = false;
        bool Toggle_On_Variable_Y = false;
        bool Turning_Y_Button_Off = false;
        bool Toggle_Off_Variable_Y = false; 


/*		float Finding_the_position_value_left;
		float Finding_the_position_value_right;
		float Finding_the_position_value_left_f;
		float Finding_the_position_value_right_f;
		float Finding_the_position_value_left_i;
		float Finding_the_position_value_right_i;
		
		float StartingPosLeft = 0;
		float StartingPosRight = 0;
		int EndLoopNumber;
		float Error;
		double ErrorPercentage;
		double ErrorPercentageLeft;
		double ErrorPercentageRight;
		int Mode = 1;
		float velocity_left;
		float velocity_right;
		

		//Distance Stuff
		float one_rotation_encoder_counts = 4096;
		float rotations_per_inch = 5;
		float input_height = -18;
		float original_percent_output_left = 1;
		float original_percent_output_right = -1;
		float travel_distance_for_scissor_lift = (20.5 - (20.5 * cos(asin(input_height/(20.5*5)))));
		float actual_rotations_for_scissor_lift_scale = (one_rotation_encoder_counts * rotations_per_inch * travel_distance_for_scissor_lift);
		float encoder_counts_per_loop_left = 10;
		float encoder_counts_per_loop_right = -10;
		float WantedPosition = actual_rotations_for_scissor_lift_scale;

*/
		void RobotInit() { 

			talon_left_enc = new TalonSRX(7);
			talon_right_enc = new TalonSRX(2);
			joystick = new Joystick(0);
			scissor = new ScissorLift(talon_left_enc, talon_right_enc);


			std::cout<<"Oh la la! Un cochon. Il est tres beau. Il est plus beau que des cochons! Je s'adore!"<<std::endl;
			std::cout<<"Blue Pig!"<<std::endl;

		}

		void TeleopInit() {
			talon_left_enc->SetSelectedSensorPosition(0, 0, TALON_TIMEOUT_MILLISECONDS);
			talon_right_enc->SetSelectedSensorPosition(0, 0, TALON_TIMEOUT_MILLISECONDS);
			
			//	talon_left_enc->ConfigPeakOutputForward(0.6, TALON_TIMEOUT_MILLISECONDS);
			//	talon_right_enc->ConfigPeakOutputForward(0.6, TALON_TIMEOUT_MILLISECONDS);   
			std::cout<<"I'm a PIGGGGGGGGGGG!"<<std::endl;
		}

		void TeleopPeriodic() {
			scissor->set_position(-8, 1);
			
 			talon_left_enc->Config_kF(0, 0, TALON_TIMEOUT_MILLISECONDS);
			talon_left_enc->Config_kP(0, 2.55, TALON_TIMEOUT_MILLISECONDS);
			talon_left_enc->Config_kI(0, 0, TALON_TIMEOUT_MILLISECONDS);
			talon_left_enc->Config_kD(0, 0, TALON_TIMEOUT_MILLISECONDS);

			talon_right_enc->Config_kF(0, 0, TALON_TIMEOUT_MILLISECONDS);
			talon_right_enc->Config_kP(0, 2.6, TALON_TIMEOUT_MILLISECONDS);
			talon_right_enc->Config_kI(0, 0, TALON_TIMEOUT_MILLISECONDS);
			talon_right_enc->Config_kD(0, 0, TALON_TIMEOUT_MILLISECONDS);

		}

		void AutonomousInit() {}

		void AutonomousPeriodic() {}

		void DisabledInit() {
			scissor->stop_loop();
			std::cout<<"Hi, I'm a pig. Oink"<<std::endl;
		}

		void TestInit(){

		}

		void TestPeriodic() {

		}
		
};

START_ROBOT_CLASS(Robot);