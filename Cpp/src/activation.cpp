#include "activation.h"


namespace NN{
	//#######################################
	//#          Activation_ReLU            #
	//#######################################
	Activation_ReLU::Activation_ReLU(){}
	void Activation_ReLU::forward(numeric::Md inputs){
		numeric::matrix_min_cap(output, &inputs, 0);
	}
	numeric::Md Activation_ReLU::Output(){
		return output;
	}
	Activation_ReLU::~Activation_ReLU(){}

	//#######################################
	//#         Activation_Softmax          #
	//#######################################
	Activation_Softmax::Activation_Softmax(){}
	void Activation_Softmax::forward(numeric::Md inputs){
		numeric::matrix_get_max(max_values, &inputs, 1);
		numeric::matrix_sub_vector(exp_values, &inputs, &max_values, 1);
		numeric::matrix_exp(exp_values);

		numeric::matrix_normalize(exp_values, 1);
		output = exp_values;


	}
	numeric::Md Activation_Softmax::Output(){
		return output;
	}
	Activation_Softmax::~Activation_Softmax(){}





}

