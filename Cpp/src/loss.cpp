#include "loss.h"



namespace NN{
	//#######################################
	//#          Activation_ReLU            #
	//#######################################
	Loss::Loss(){

	}
	
	Loss::~Loss(){

	}

	void Loss::forward(numeric::Md data_loss, const numeric::Md *const output, const numeric::Vd *const y){
		forward(sample_losses, &output, &y);
	}

}
