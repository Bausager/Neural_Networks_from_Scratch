#include "numerics.h"
#include "layers.h"
#include "activation.h"
#include "data_gen.h"
#include "loss.h"


#include <vector>
#include <iostream>



int main(int argc, char const *argv[])
{

	//output up to 10 digits
	std::cout.precision(10);
	numeric::Md X;
	numeric::Md y;
	double loss;
	double acc;
	numeric::Vd ytemp;


	//vertical_data(100, 3, X, ytemp);
	spiral_data(100, 3, X, ytemp);
	y.m.push_back(ytemp);



	NN::Layer_Dense dense1(2, 3);
	NN::Activation_ReLU Activation1;

	NN::Layer_Dense dense2(3, 3);
	NN::Activation_Softmax Activation2;

	NN::Loss_CategoricalCrossentropy loss_function;

	double lowest_loss = 9999999;

	numeric::Md best_dense1_weights = dense1.get_weights();
	numeric::Vd best_dense1_biases = dense1.get_biases();
	numeric::Md best_dense2_weights = dense2.get_weights();
	numeric::Vd best_dense2_biases = dense2.get_biases();

	numeric::Md temp_weights;
	numeric::Vd temp_biases;


	for (uint64_t iteration = 0; iteration < 100; iteration++){

		temp_weights = dense1.get_weights();
		temp_weights.disturbance(0.95, 1.05);
		dense1.set_weights(temp_weights);

		temp_biases = dense1.get_biases();
		temp_biases.disturbance(0.95, 1.05);
		dense1.set_biases(temp_biases);

		temp_weights = dense2.get_weights();
		temp_weights.disturbance(0.95, 1.05);
		dense2.set_weights(temp_weights);

		temp_biases = dense2.get_biases();
		temp_biases.disturbance(0.95, 1.05);
		dense2.set_biases(temp_biases);


		dense1.forward(X);
		Activation1.forward(dense1.get_output());
		dense2.forward(Activation1.get_output());
		Activation2.forward(dense2.get_output());

		loss_function.calculate(Activation2.get_output(), y);

		loss = loss_function.get_output();

	 	// Predictions
		ytemp = numeric::matrix_argmax(Activation2.get_output());

		acc = 0.0;
		if (y.m.size() == 1){
			for (uint64_t i = 0; i < Activation2.get_output().m.size(); i++){
				if (y.m[0].v[i] == ytemp.v[i]){
					acc += 1;
				}
			}
			acc /= y.m[0].v.size();
		}
		else{
			
			for (uint64_t i = 0; i < Activation2.get_output().m.size(); i++){
				std::cout << y.m[i].v[ytemp.v[i]] << std::endl << std::endl;

				if (y.m[i].v[ytemp.v[i]]){
					acc += 1;
				}
			}
			acc /= y.m.size();
		}


		if (loss < lowest_loss){
			//std::cout << "New set of wieght found, iteration: " << iteration << std::endl;
			//std::cout << "Loss: " << loss << ", acc: " << acc << std::endl << std::endl;

			best_dense1_weights = dense1.get_weights();
			best_dense1_biases = dense1.get_biases();
			best_dense2_weights = dense2.get_weights();
			best_dense2_biases = dense2.get_biases();
			lowest_loss = loss;
		}	

	}



	numeric::Md matrix0;
	matrix0.fill(0, 0, 0);
	numeric::Md matrix1;
	matrix1.fill(1, 1, 0);

	numeric::Md matrix2;
	matrix2.fill(2, 2, 0);
	matrix2.m[0].v[0] = 3;
	matrix2.m[0].v[1] = 3.5;

	matrix2.m[1].v[0] = 3.2;
	matrix2.m[1].v[1] = 3.6;


	numeric::Md matrix3;
	matrix3.fill(3, 3, 0);

	matrix3.m[0].v[0] = 1;
	matrix3.m[0].v[1] = 0;
	matrix3.m[0].v[2] = 3;

	matrix3.m[1].v[0] = -1;
	matrix3.m[1].v[1] = -1;
	matrix3.m[1].v[2] = -3;

	matrix3.m[2].v[0] = 0;
	matrix3.m[2].v[1] = 0;
	matrix3.m[2].v[2] = 6;


	numeric::Md matrix4;
	matrix4.fill(4, 4, 0);


	std::cout << matrix2 << std::endl << std::endl;
	numeric::Md det;
	det = numeric::matrix_inverse(matrix2);
	std::cout << det << std::endl << std::endl;

















	return 0;
}