#ifndef _layers_h_
#define _layers_h_

#include "numerics.h"

namespace NN{
	class Layer_Dense{
	public:
		Layer_Dense(uint64_t n_inputs, uint64_t n_neurons);
		~Layer_Dense();

		void forward(numeric::Md inputs);


		numeric::Md Output();

	private:
		numeric::Md weights;
		numeric::Vd biases;
		numeric::Md output;
		numeric::Md dot_product;
	};
}




#endif // _layers_h_