#ifndef _loss_h_
#define _loss_h_

#include "numerics.h"


namespace NN{
	class Loss{
	public:
		Loss() = default; // <- delete default if you intend to write the constructor's implementation
		virtual ~Loss() = default;

		void calculate(const numeric::Md& y_pred, const numeric::Md& y);

		virtual void forward(const numeric::Md& y_pred, const numeric::Md& y_true) = 0;
		virtual void backward(const numeric::Md& dvalue, const numeric::Md& y_true) = 0;

	private:
		numeric::Md data_loss;
		double loss;
	};


	class Loss_CategoricalCrossentropy: public Loss{
	public:
		Loss_CategoricalCrossentropy() = default;
		~Loss_CategoricalCrossentropy() override = default;


		void forward(const numeric::Md& y_pred, const numeric::Md& y_true) override;
		void backward(const numeric::Md& dvalue, const numeric::Md& y_true) override;

		double& get_output();

	private:

		double _loss;
		numeric::Md _dinputs;
		numeric::Md _matrix_temp;
		numeric::Vd _vector_temp;
	};
}

#endif // _loss_h_