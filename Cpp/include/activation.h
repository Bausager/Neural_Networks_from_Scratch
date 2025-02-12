#ifndef _activation_h_
#define _activation_h_

#include "numerics.h"

namespace NN{
	//#######################################
	//#          Activation_ReLU            #
	//#######################################
	class Activation_ReLU{


	public:
		Activation_ReLU();
		~Activation_ReLU();
		void forward(numeric::Md inputs);
		void backward(numeric::Md dvalues);


		numeric::Md get_output();


	private:
		numeric::Md _inputs;
		numeric::Md _dinputs;
		numeric::Md _outputs;
	};

	//#######################################
	//#         Activation_Softmax          #
	//#######################################
	class Activation_Softmax{


	public:
		Activation_Softmax();
		~Activation_Softmax();
		void forward(numeric::Md inputs);
		numeric::Md& get_output();


	private:
		numeric::Md _inputs;
		numeric::Md _dinputs;
		numeric::Md _outputs;
		numeric::Md _matrix_temp;
		numeric::Vd _vector_temp;
	};

}

#endif // _activation_h_