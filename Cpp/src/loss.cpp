#include "loss.h"



namespace NN{
	//#######################################
	//#            Class: Loss              #
	//#######################################

	void Loss::calculate(const numeric::Md& y_pred, const numeric::Md& y){
		forward(y_pred, y);
		//data_loss = sample_loss.get_mean();
	}

	//#######################################
	//# Class: Loss_CategoricalCrossentropy #
	//#######################################


	void Loss_CategoricalCrossentropy::forward(const numeric::Md& y_pred, const numeric::Md& y_true){
	
		if (_vector_temp.v.size() != y_true.m[0].v.size()){
			_vector_temp.fill(y_true.m[0].v.size(), 0);
		}

		_matrix_temp = matrix_clip(y_pred, 1e-7 , 1-1e-7);

		if (y_true.m.size() == 1){
			for (uint64_t i = 0; i < y_true.m[0].v.size(); i++){
				_vector_temp.v[i] = _matrix_temp.m[i].v[y_true.m[0].v[i]];
			}
		}
		else{
			for (uint64_t i = 0; i < y_true.m.size(); i++){
				_vector_temp.v[i] = vector_dot(_matrix_temp.m[i], y_true.m[i]);
			}
		}

		for (uint64_t i = 0; i < _vector_temp.v.size(); i++){
			_vector_temp.v[i] = -log(_vector_temp.v[i]);
		}

		_loss = _vector_temp.get_mean();
	}

	void Loss_CategoricalCrossentropy::backward(const numeric::Md& dvalue, const numeric::Md& y_true){

		uint64_t samples = dvalue.m.size();
		uint64_t labels = dvalue.m[0].v.size();

		if(y_true.m[0].v.size() == 1){
			_matrix_temp.fill(samples, labels, 0);
			for (uint64_t i = 0; i < samples; i++){
				_matrix_temp.m[i].v[y_true.m[i].v[0]] = 1;
			}
		}
		else{
			_matrix_temp = y_true;
		}
		_dinputs = numeric::matrix_element_wise_division(numeric::matrix_sign(_matrix_temp), dvalue);
		_dinputs = numeric::matrix_scalar_element_wise_division(_dinputs, static_cast<double>(samples));


	}


	double& Loss_CategoricalCrossentropy::get_output(){
		return _loss;
	}



}
