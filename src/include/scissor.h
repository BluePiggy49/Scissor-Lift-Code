#ifndef SCISSOR_LIFT_H
#define SCISSOR_LIFT_H

#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <iostream>

class ScissorLift
{
public:
	ScissorLift(TalonSRX *talon_left_enc, TalonSRX *talon_right_enc) : talon_right_enc(talon_right_enc), talon_left_enc(talon_left_enc) {
	
	};

	/*	
		float Finding_the_position_value_left;
		float Finding_the_position_value_right;
		float Finding_the_position_value_left_f;
		float Finding_the_position_value_right_f;
		float Finding_the_position_value_left_i;
		float Finding_the_position_value_right_i;
			
		float StartingPosLeft = 0;
		float StartingPosRight = 0;
		
		float Error;
		double ErrorPercentage;
		double ErrorPercentageLeft;
		double ErrorPercentageRight;
		int Mode = 1;
		float velocity_left;
		float velocity_right;
		float input_height;
		const float one_rotation_encoder_counts = 4096;
		const float rotations_per_inch = 5;
		const float original_percent_output_left = 1;
		const float original_percent_output_right = -1;
		float travel_distance_for_scissor_lift = (20.5 - (20.5 * cos(asin(input_height/(20.5*5)))));
		float actual_rotations_for_scissor_lift_scale = (one_rotation_encoder_counts * rotations_per_inch * travel_distance_for_scissor_lift);
		float negative_actual_rotations_for_scissor_lift_scale = -1 * actual_rotations_for_scissor_lift_scale;
		const float encoder_counts_per_loop_left = 10;
		const float encoder_counts_per_loop_right = -10;
		float WantedPosition = actual_rotations_for_scissor_lift_scale;
		int EndLoopNumber = abs(actual_rotations_for_scissor_lift_scale/encoder_counts_per_loop_left);
	
	inline float set_position(float input_height);
	*/
		bool moving = true;
		enum SL_Mode
		{
			going_up,
			going_down,
			idle,
		}scissor_lift_mode;
		int index = 1;
		const float one_rotation_encoder_counts = 4096;
		const float rotations_per_inch = 5;
		float original_percent_output_left = 1;
		float original_percent_output_right = -1;
		const float encoder_counts_per_loop_left = 10;
		const float encoder_counts_per_loop_right = -10;
		float travel_distance_for_scissor_lift;
		float actual_rotations_for_scissor_lift_scale;
		float negative_actual_rotations_for_scissor_lift_scale = -1 * actual_rotations_for_scissor_lift_scale;
		float Finding_the_position_value_left;
		float Finding_the_position_value_right;
		float Finding_the_position_value_left_f;
		float Finding_the_position_value_right_f;
		float Finding_the_position_value_left_i;
		float Finding_the_position_value_right_i;
		float Error;
		float ErrorPercentage;
			
		float input_height_in_inches;
		float input_height_NU;
		int EndLoopNumber;
		int loop_number;


		void set_position(float input_height, float percent_output_from_user);
		void run_loop();
		void stop_loop();


private:
	TalonSRX *talon_left_enc, *talon_right_enc;
	
	inline float input_height_function ();

		
};

#endif
