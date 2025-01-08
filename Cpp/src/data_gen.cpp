#include "data_gen.h"

void spiral_data(const uint64_t& points, const uint64_t& classes, numeric::Md& matr_out, numeric::Vd& vec_out){
	matr_out.fill(points*classes, 2, 0);
	vec_out.fill(points*classes, 0);

	double r, t;
	uint64_t row_index;

	for (uint64_t i = 0; i < classes; i++){
		for (uint64_t j = 0; j < points; j++){
			r = double(j)/double(points);
			t = i*4.0 + (4.0+r);
			row_index = (i * points) + j;

			matr_out.m[row_index].v[0] = r*cos(t*2.5) + numeric::random(-0.15, 0.15);
			matr_out.m[row_index].v[1] = r*sin(t*2.5) + numeric::random(-0.15, 0.15);
			vec_out.v[row_index] = i;
		}
	}
}
