#include "activation.h"


namespace NN{
	//#######################################
	//#          Activation_ReLU            #
	//#######################################
	Activation_ReLU::Activation_ReLU(){}



	void Activation_ReLU::forward(numeric::Md inputs){
		_inputs = inputs;
		_outputs = numeric::matrix_min_cap(_inputs, 0);
	}

	void Activation_ReLU::backward(numeric::Md dvalues){
		_dinputs = dvalues;
		_dinputs = numeric::matrix_min_cap(_dinputs, 0);
	}




	numeric::Md Activation_ReLU::get_output(){
		return _outputs;
	}
	Activation_ReLU::~Activation_ReLU(){}

	//#######################################
	//#         Activation_Softmax          #
	//#######################################
	Activation_Softmax::Activation_Softmax(){}
	void Activation_Softmax::forward(numeric::Md inputs){
		_inputs = inputs;
		_vector_temp = numeric::matrix_get_max(_inputs, 1);
		_matrix_temp = numeric::matrix_sub_vector(_inputs, _vector_temp, 1);
		_matrix_temp = numeric::matrix_exp(_matrix_temp);

		_outputs = numeric::matrix_normalize(_matrix_temp, 1);
	}

	void Activation_Softmax::backward(numeric::Md dvalues){
		_dinputs.fill(dvalues.m.size(), dvalues.m[0].v.size(), 0);
		
	}



	numeric::Md& Activation_Softmax::get_output(){
		return _outputs;
	}
	Activation_Softmax::~Activation_Softmax(){}





}

