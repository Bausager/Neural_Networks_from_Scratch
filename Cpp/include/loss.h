#ifndef _loss_h_
#define _loss_h_

#include "numerics.h"


namespace NN{
	class Loss{
	public:
		Loss() = default; // <- delete default if you intend to write the constructor's implementation
		virtual ~Loss() = default;

		void calculate(const numeric::Md *const y_pred, const numeric::Md *const y);

		virtual void forward(const numeric::Md *const y_pred, const numeric::Md *const y_true) = 0;

	private:
		numeric::Md data_loss;
		double loss;
	};


	class Loss_CategoricalCrossentropy: public Loss{
	public:
		Loss_CategoricalCrossentropy() = default;
		~Loss_CategoricalCrossentropy() override = default;


		void forward(const numeric::Md *const y_pred, const numeric::Md *const y_true) override;
		double& Output();
	private:
		numeric::Md data_loss;
		numeric::Vd vect_helper;
		double loss;
	};
}

#endif // _loss_h_