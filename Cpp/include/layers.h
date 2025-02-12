#ifndef _layers_h_
#define _layers_h_

#include "numerics.h"

namespace NN{
	class Layer_Dense{
	public:
		Layer_Dense(uint64_t n_inputs, uint64_t n_neurons);
		~Layer_Dense();

		void forward(numeric::Md inputs);
		void backward(numeric::Md dvalues);


		numeric::Md get_output();
		numeric::Md get_weights();
		numeric::Vd get_biases();

		void set_weights(const numeric::Md& new_weights);
		void set_biases(const numeric::Vd& new_biases);


	private:
		numeric::Md _weights;
		numeric::Md _dweights;
		numeric::Vd _biases;
		numeric::Vd _dbiases;

		numeric::Md _inputs;
		numeric::Md _dinputs;
		numeric::Md _output;

		numeric::Md _matrix_temp;
		numeric::Vd _vector_temp;
	};
}




#endif // _layers_h_