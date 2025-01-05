#include "layers.h"

namespace NN{
	Layer_Dense::Layer_Dense(uint64_t n_inputs, uint64_t n_neurons){
		weights.fill_RNG(n_inputs, n_neurons, -1, 1);
		biases.fill_RNG(n_neurons, -1, 1);
	}



	void Layer_Dense::forward(numeric::Md inputs){
		numeric::matrix_dot(dot_product, &inputs, &weights);
		numeric::matrix_add_vector(output, &dot_product, &biases, 0);
	}


	numeric::Md Layer_Dense::Output(){
		return output;
	}

	Layer_Dense::~Layer_Dense(){

	}

}