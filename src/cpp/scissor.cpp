#include <scissor.h>

#define TALON_TIMEOUT_MILLISECONDS 10

void ScissorLift::set_position(float input_height, float percent_output_from_user){
	std::cout<<"Input height: "<<input_height<<std::endl;
	original_percent_output_left = percent_output_from_user;
	input_height_in_inches = input_height;

	run_loop();
}
void ScissorLift::stop_loop(){
	talon_left_enc->Set(ControlMode::PercentOutput, 0);
	talon_right_enc->Set(ControlMode::PercentOutput, 0);
}

inline float ScissorLift::input_height_function(){
		travel_distance_for_scissor_lift = (20.5 - (20.5 * cos(asin(input_height_in_inches/(20.5*5)))));
		actual_rotations_for_scissor_lift_scale = (one_rotation_encoder_counts * rotations_per_inch * travel_distance_for_scissor_lift);
		negative_actual_rotations_for_scissor_lift_scale = -1 * actual_rotations_for_scissor_lift_scale;

		input_height_NU = actual_rotations_for_scissor_lift_scale;
		std::cout<<"Pigs are so AWESOME!!!!!!!!!!!!"<<std::endl;
		std::cout<<"Input Height Native Encoder Units: "<<input_height_NU<<std::endl;
		return input_height_NU;
}

void ScissorLift::run_loop(){

			EndLoopNumber = abs(input_height_NU/encoder_counts_per_loop_left);
			float original_percent_output_right = original_percent_output_left * -1;
			talon_left_enc->ConfigPeakOutputForward(original_percent_output_left, TALON_TIMEOUT_MILLISECONDS);
			talon_right_enc->ConfigPeakOutputForward(original_percent_output_right, TALON_TIMEOUT_MILLISECONDS);  
			Finding_the_position_value_left_f = talon_left_enc->GetSelectedSensorPosition(0);
			Finding_the_position_value_right_f = talon_right_enc->GetSelectedSensorPosition(0);
			if (input_height_function() > (abs(Finding_the_position_value_left_f) || abs(Finding_the_position_value_right_f) ))
			{
				scissor_lift_mode = SL_Mode::going_up;
			}
			else if (input_height_function() < (abs(Finding_the_position_value_left_f) || abs(Finding_the_position_value_right_f) ))
			{
				scissor_lift_mode = SL_Mode::going_down;
			}
			else {
				scissor_lift_mode = SL_Mode::idle;
			}
			switch(scissor_lift_mode){
				case SL_Mode::going_up:
					loop_number = 1;
					if (EndLoopNumber > loop_number)
					{
						while (EndLoopNumber > loop_number){
									Finding_the_position_value_left_i = talon_left_enc->GetSelectedSensorPosition(0);
									Finding_the_position_value_right_i = talon_right_enc->GetSelectedSensorPosition(0);
									std::cout<<"Happy National Pig Day!!!!!!!!!!!!!"<<std::endl;
									if (Finding_the_position_value_left_i > (encoder_counts_per_loop_left * loop_number))
									{
									talon_left_enc->Set(ControlMode::Position, Finding_the_position_value_left_i + encoder_counts_per_loop_left);
									}
									else{
									talon_left_enc->Set(ControlMode::Position, encoder_counts_per_loop_left * loop_number);
									std::cout<<"If you like pigs you say oink!"<<std::endl;
									}

									if (Finding_the_position_value_left_i < (encoder_counts_per_loop_right * loop_number))
									{
									talon_right_enc->Set(ControlMode::Position, Finding_the_position_value_right_i + encoder_counts_per_loop_right);
									}
									else{
									talon_right_enc->Set(ControlMode::Position, encoder_counts_per_loop_right * loop_number);
									}
											
									Finding_the_position_value_left_f = talon_left_enc->GetSelectedSensorPosition(0);
									Finding_the_position_value_right_f = talon_right_enc->GetSelectedSensorPosition(0);
									Error = abs(abs(Finding_the_position_value_left_f) - abs(Finding_the_position_value_right_f));
									ErrorPercentage = ((Error)/(std::max(abs(Finding_the_position_value_right_f), abs(Finding_the_position_value_left_f))));
									if (ErrorPercentage > 0.03)
											{
												if(ErrorPercentage > 0.2){
												  std::cout<<"Emergency!"<<std::endl;
												  talon_left_enc->Set(ControlMode::PercentOutput, 0);
												  talon_right_enc->Set(ControlMode::PercentOutput, 0);
												  
												  } 
												if (abs(Finding_the_position_value_right_f) >= abs(Finding_the_position_value_left_f))
												{
													talon_left_enc->ConfigPeakOutputForward(original_percent_output_left, TALON_TIMEOUT_MILLISECONDS);
													talon_right_enc->ConfigPeakOutputForward((original_percent_output_right * (1 - ErrorPercentage)), TALON_TIMEOUT_MILLISECONDS);
												}
												else
												{
													talon_left_enc->ConfigPeakOutputForward((original_percent_output_left * (1 - ErrorPercentage)), TALON_TIMEOUT_MILLISECONDS);
													talon_right_enc->ConfigPeakOutputForward(original_percent_output_right , TALON_TIMEOUT_MILLISECONDS);
												}

											
											}
											
												loop_number = loop_number + 1;		
											
											std::cout<<"Right Encoder Position: "<<Finding_the_position_value_right_f<<std::endl;
											std::cout<<"Left Encoder Position: "<<Finding_the_position_value_left_f<<std::endl;
											std::cout<<"Right Encoder Supposed to be Position: "<<(encoder_counts_per_loop_right * loop_number)<<std::endl;
											std::cout<<"Left Encoder Supposed to be Position: "<<(encoder_counts_per_loop_left * loop_number)<<std::endl;
											std::cout<<"Loops: "<<loop_number<<std::endl;
											std::cout<<"End Loop Number: "<<EndLoopNumber<<std::endl;
											std::cout<<"Error: "<<Error<<std::endl;
											std::cout<<"Error Percentage: "<<ErrorPercentage * 100<<"%"<<std::endl;
											std::cout<<" "<<std::endl;
										}
					}
					else{
						talon_left_enc->Set(ControlMode::PercentOutput, 0);
						talon_right_enc->Set(ControlMode::PercentOutput, 0);
						loop_number = 1;
					}
					break;
					
				case SL_Mode::going_down:
				loop_number = 1;
				if (EndLoopNumber > loop_number)
					{
							while (EndLoopNumber > loop_number){			
										if (Finding_the_position_value_left_i < (encoder_counts_per_loop_left * (-1 * loop_number)))
										{
										talon_left_enc->Set(ControlMode::Position, Finding_the_position_value_left_i - encoder_counts_per_loop_left);
										}
										else{
										talon_left_enc->Set(ControlMode::Position, encoder_counts_per_loop_left * (-1 * loop_number));
										}

										if (Finding_the_position_value_right_i > (encoder_counts_per_loop_right * (-1 * loop_number)))
										{
										talon_right_enc->Set(ControlMode::Position, Finding_the_position_value_right_i - encoder_counts_per_loop_right);
										}
										else{
										talon_right_enc->Set(ControlMode::Position, encoder_counts_per_loop_right * (-1 * loop_number));
										}
												
										Finding_the_position_value_left_f = talon_left_enc->GetSelectedSensorPosition(0);
										Finding_the_position_value_right_f = talon_right_enc->GetSelectedSensorPosition(0);
										Error = abs(abs(Finding_the_position_value_left_f) - abs(Finding_the_position_value_right_f));
										ErrorPercentage = ((Error)/(std::max(abs(Finding_the_position_value_right_f), abs(Finding_the_position_value_left_f))));
										if (ErrorPercentage > 0.03)
												{
													if(ErrorPercentage > 0.2){
													  std::cout<<"Emergency!"<<std::endl;
													//  talon_left_enc->Set(ControlMode::Position, 0);
													 // talon_right_enc->Set(ControlMode::Position, 0);
													  } 
													if (abs(Finding_the_position_value_right_f) >= abs(Finding_the_position_value_left_f))
													{
														talon_left_enc->ConfigPeakOutputForward(-1 * original_percent_output_left, TALON_TIMEOUT_MILLISECONDS);
														talon_right_enc->ConfigPeakOutputForward((-1 * original_percent_output_right * (1 - ErrorPercentage)), TALON_TIMEOUT_MILLISECONDS);
													}
													else
													{
														talon_left_enc->ConfigPeakOutputForward((-1 * original_percent_output_left * (1 - ErrorPercentage)), TALON_TIMEOUT_MILLISECONDS);
														talon_right_enc->ConfigPeakOutputForward(-1 * original_percent_output_right , TALON_TIMEOUT_MILLISECONDS);
													}

												
												}
											loop_number = loop_number ++;
											std::cout<<"Right Encoder Position: "<<Finding_the_position_value_right_f<<std::endl;
											std::cout<<"Left Encoder Position: "<<Finding_the_position_value_left_f<<std::endl;
											std::cout<<"Right Encoder Supposed to be Position: "<<(encoder_counts_per_loop_right * loop_number)<<std::endl;
											std::cout<<"Left Encoder Supposed to be Position: "<<(encoder_counts_per_loop_left * loop_number)<<std::endl;
											std::cout<<"Loops: "<<loop_number<<std::endl;
											std::cout<<"Error: "<<Error<<std::endl;
											std::cout<<"Error Percentage: "<<ErrorPercentage * 100<<"%"<<std::endl;
											std::cout<<" "<<std::endl;
											}
					}
					else{
						talon_left_enc->Set(ControlMode::PercentOutput, 0);
						talon_right_enc->Set(ControlMode::PercentOutput, 0);
						loop_number = 1;
					}
					break;

					case SL_Mode::idle:
					std::cout<<"#ILovePigs"<<std::endl;
					talon_right_enc->Set(ControlMode::PercentOutput, 0);
					talon_left_enc->Set(ControlMode::PercentOutput, 0);
					break;
			}
		}