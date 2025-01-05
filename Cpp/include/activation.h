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
		numeric::Md Output();
	private:
		numeric::Md output;
	};

	//#######################################
	//#         Activation_Softmax          #
	//#######################################
	class Activation_Softmax{
	public:
		Activation_Softmax();
		~Activation_Softmax();
		void forward(numeric::Md inputs);
		numeric::Md Output();
	private:
		numeric::Md output;
		numeric::Md exp_values;
		numeric::Vd max_values;
		numeric::Vd matr_sum;
	};

}

#endif // _activation_h_