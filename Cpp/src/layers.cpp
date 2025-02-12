#include "layers.h"

namespace NN{
	Layer_Dense::Layer_Dense(uint64_t n_inputs, uint64_t n_neurons){
		_weights.fill_RNG(n_inputs, n_neurons, -1, 1);
		_biases.fill_RNG(n_neurons, -1, 1);
	}



	void Layer_Dense::forward(numeric::Md inputs){
		_inputs = inputs;
		_matrix_temp = numeric::matrix_dot(_inputs, _weights);
		_output = numeric::matrix_add_vector(_matrix_temp, _biases, 0);
	}

	void Layer_Dense::backward(numeric::Md dvalues){
		
		_dweights = numeric::matrix_dot(numeric::matrix_transpose(_inputs), dvalues);
		std::cout << "Before:" << std::endl;
		std::cout << _dbiases << std::endl;
		_dbiases = numeric::matrix_get_sum(dvalues, 0);
		std::cout << "After:" << std::endl;
		std::cout << _dbiases << std::endl;

		_dinputs = numeric::matrix_dot(dvalues, numeric::matrix_transpose(_weights));
	}





	numeric::Md Layer_Dense::get_output(){
		return _output;
	}
	numeric::Md Layer_Dense::get_weights(){
		return _weights;
	}
	numeric::Vd Layer_Dense::get_biases(){
		return _biases;
	}

	void Layer_Dense::set_weights(const numeric::Md& new_weights){
		if (new_weights.m.size() == _weights.m.size() && new_weights.m[0].v.size() == _weights.m[0].v.size()){
			_weights = new_weights;
		}
		else{
			LOG("Layer_Dense::set_weights");
			throw std::exception();
		}
	}

	void Layer_Dense::set_biases(const numeric::Vd& new_biases){
		if (new_biases.v.size() == _biases.v.size()){
			_biases = new_biases;
		}
		else{
			LOG("Layer_Dense::set_biases");
			throw std::exception();
		}
	}

	Layer_Dense::~Layer_Dense(){

	}

}