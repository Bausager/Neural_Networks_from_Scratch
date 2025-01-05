#include "numerics.h"
#include "layers.h"
#include "activation.h"
#include "data_gen.h"
#include "loss.h"


#include <vector>
#include <iostream>

int main(int argc, char const *argv[])
{


	numeric::Md X;
	numeric::Vd y;
	
	

	numeric::Vd temp;

	spiral_data(5, 3, X, y);

	NN::Layer_Dense dense1(2, 3);
	numeric::Md output1;
	NN::Activation_ReLU Activation1;
	numeric::Md activation_output1;

	NN::Layer_Dense dense2(3, 3);
	numeric::Md output2;
	NN::Activation_Softmax Activation2;
	numeric::Md activation_output2;

	dense1.forward(X);
	//std::cout << dense1.Output() << std::endl << std::endl;
	Activation1.forward(dense1.Output());
	//std::cout << Activation1.Output() << std::endl << std::endl;
	dense2.forward(Activation1.Output());
	//std::cout << dense2.Output() << std::endl << std::endl;
	Activation2.forward(dense2.Output());
	std::cout << Activation2.Output() << std::endl << std::endl;
	



	//
	/* code */
	return 0;
}