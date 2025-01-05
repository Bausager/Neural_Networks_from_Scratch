#ifndef _loss_h_
#define _loss_h_

#include "numerics.h"


namespace NN{
	class Loss
	{
	public:
		Loss();
		~Loss();

	private:
		numeric::Md sample_losses;
		
	};



	class Loss_CategoricalCrossentropy
	{
	public:
		Loss_CategoricalCrossentropy(Loss);
		~Loss_CategoricalCrossentropy();


		void forward(numeric::Md data_loss, const numeric::Md *const output, const numeric::Vd *const y);
		
	};
}



#endif // _loss_h_