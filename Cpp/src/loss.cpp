#include "loss.h"



namespace NN{
	//#######################################
	//#            Class: Loss              #
	//#######################################

	void Loss::calculate(const numeric::Md *const y_pred, const numeric::Md *const y){
		forward(y_pred, y);
		//data_loss = sample_loss.get_mean();
	}

	//#######################################
	//# Class: Loss_CategoricalCrossentropy #
	//#######################################


	void Loss_CategoricalCrossentropy::forward(const numeric::Md *const y_pred, const numeric::Md *const y_true){
	
		if (vect_helper.v.size() != y_true->m[0].v.size())
		{
			vect_helper.fill(y_true->m[0].v.size(), 0);
		}

		matrix_clip(data_loss, y_pred, 1e-7 , 1-1e-7);

		if (y_true->m.size() == 1){
			for (uint64_t i = 0; i < y_true->m[0].v.size(); i++){
				vect_helper.v[i] = data_loss.m[i].v[y_true->m[0].v[i]];
			}
		}
		else{
			for (uint64_t i = 0; i < y_true->m.size(); i++){
				vector_dot(vect_helper.v[i], &data_loss.m[i], &y_true->m[i]);
			}
		}

		for (uint64_t i = 0; i < vect_helper.v.size(); i++){
			vect_helper.v[i] = -log(vect_helper.v[i]);
		}

		loss = vect_helper.get_mean();
	}


	double& Loss_CategoricalCrossentropy::Output(){
		return loss;
	}



}
