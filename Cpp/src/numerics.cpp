#include "numerics.h"



namespace numeric{
	//#######################################
	//#   UTILITY FUNCTIONS FOR VECTOR      #
	//#######################################
	Vd vector_fill_RNG(const Vd& vect, const double min, const double max){

		Vd vect_out;
		vect_out.fill(vect_out.v.size(), 0);

		for (uint64_t i = 0; i < vect_out.v.size(); i++){
				vect_out.v[i] = random(min, max);
		}
		return vect_out;
	}

	double vector_dot(const Vd& v1, const Vd& v2){

		double dot_product = 0;

		if (v1.v.size() != v2.v.size()){
			LOG("numerics::vector_dot");
			throw std::exception();
		}
		else{
			for (uint64_t i = 0; i < v1.v.size(); i++){
				dot_product += v1.v[i]*v2.v[i];
			}
		}
		return dot_product;
	}

	Vd vector_max_cap(const Vd& vect, const double value){

		Vd vect_out;
		vect_out.fill(vect.v.size(), 0);	

		for (uint64_t i = 0; i < vect.v.size(); i++){
			vect_out.v[i] = MIN(vect.v[i], value);
		}
		return vect_out;
	}
	
	Vd vector_min_cap(const Vd& vect, const double value){

		Vd vect_out;
		vect_out.fill(vect.v.size(), 0);

		for (uint64_t i = 0; i < vect.v.size(); i++){
			vect_out.v[i] = MAX(vect.v[i], value);
		}
		return vect_out;
	}

	Vd vector_clip(const Vd& vect, const double min_value, const double max_value){

		Vd vect_out;
		vect_out.fill(vect.v.size(), 0);

		for (uint64_t i = 0; i < vect.v.size(); i++){
			vect_out = vector_max_cap(vect, max_value);
			vect_out = vector_min_cap(vect_out, min_value);
		}
		return vect_out;
	}

	Vd vector_normalize(const Vd& vect, const double value){

		Vd vect_out;
		vect_out.fill(vect.v.size(), 0);

		double vect_sum = vect.get_sum();

		for (uint64_t i = 0; i < vect.v.size(); i++){
			vect_out.v[i] = vect.v[i]/vect_sum;
		}
		return vect_out;
	}

	//#######################################
	//#   UTILITY FUNCTIONS FOR Matrix      #
	//#######################################

	Md matrix_dot(const Md& M, const Md& N){

		Md matr_out;
		matr_out.fill(M.m.size(), N.m[0].v.size(),0);

		if (M.m[0].v.size() != N.m.size()){
			LOG("numerics::matrix_dot");
			throw std::exception();
		}
		else{
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < N.m[0].v.size(); j++){
					for (uint64_t k = 0; k < N.m.size(); k++)
					{
						matr_out.m[i].v[j] += M.m[i].v[k] * N.m[k].v[j];
					}
				}
			}
		}
		return matr_out;
	}

	Md matrix_add_vector(const Md& M, const Vd& vect, bool axis){

		Md matr_out;
		matr_out.fill(M.m.size(), vect.v.size(), 0);

		if (axis == 0 && matr_out.m[0].v.size() == vect.v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M.m[i].v[j] + vect.v[j];
				}
			}
		}
		else if (axis == 1 && matr_out.m.size() == vect.v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M.m[i].v[j] + vect.v[i];
				}
			}
		}
		else{
			LOG("numerics::matrix_add_vector");
			throw std::exception();
		}

		return matr_out;
	}

	Md matrix_add_matrix(const Md& M, const Md& N){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		for (uint64_t i = 0; i < matr_out.m.size(); i++){
			for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
				matr_out.m[i].v[j] = M.m[i].v[j] + N.m[i].v[j];
			}
		}
		return matr_out;
	}

	Md matrix_sub_vector(const Md& M, const Vd& vect, bool axis){
		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		if (axis == 0 && matr_out.m[0].v.size() == vect.v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M.m[i].v[j] - vect.v[j];
				}
			}
		}
		else if (axis == 1 && matr_out.m.size() == vect.v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M.m[i].v[j] - vect.v[i];
				}
			}
		}
		else{
			LOG("numerics::matrix_sub_vector");
			throw std::exception();
		}
		return matr_out;
	}

	Md matrix_max_cap(const Md& M, const double value){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);


		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = MIN(M.m[i].v[j], value);
			}
		}
		return matr_out;
	}

	Md matrix_min_cap(const Md& M, const double value){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = MAX(M.m[i].v[j], value);
			}
		}
		return matr_out;
	}

	Md matrix_clip(const Md& M, const double min_value, const double max_value){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);


		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = MAX(M.m[i].v[j], min_value);
				matr_out.m[i].v[j] = MIN(M.m[i].v[j], max_value);
			}
		}
		return matr_out;
	}

	Vd matrix_get_max(const Md& M, bool axis){

		Vd vect_out;

		if (axis == 0){
			if(M.m[0].v.size() != vect_out.v.size()){
				vect_out.fill(M.m[0].v.size(), 0);
			}
			
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					vect_out.v[j] = MAX(vect_out.v[j], M.m[i].v[j]);
				}
			}
		}
		else if(axis == 1){
			if (M.m.size() != vect_out.v.size()){
				vect_out.fill(M.m.size(), 0);
			}
			
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					vect_out.v[i] = MAX(vect_out.v[i], M.m[i].v[j]);
				}
			}
		}
		else{
			LOG("numerics::matrix_get_max");
			throw std::exception();
		}
		return vect_out;
	}

	Vd matrix_get_min(const Md& M, bool axis){

		Vd vect_out;

		if (axis == 0 && M.m[0].v.size() != vect_out.v.size()){
			vect_out.fill(M.m[0].v.size(), 0);

			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					vect_out.v[j] = MAX(vect_out.v[j], M.m[i].v[j]);
				}
			}
		}
		else if(axis == 1 && M.m.size() != vect_out.v.size()){
			vect_out.fill(M.m.size(), 0);

			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					vect_out.v[i] = MIN(vect_out.v[i], M.m[i].v[j]);
				}
			}
		}
		else{
			LOG("numerics::matrix_get_min");
			throw std::exception();
		}
		return vect_out;
	}

	Vd matrix_get_sum(const Md& M, bool axis){

		Vd vect_out;

		if (axis == 0 && M.m[0].v.size() != vect_out.v.size()){
			vect_out.fill(M.m[0].v.size(), 0);

			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					vect_out.v[j] += M.m[i].v[j];
				}
			}
		}
		else if(axis == 1 && M.m.size() != vect_out.v.size()){
			vect_out.fill(M.m.size(), 0);

			for (uint64_t i = 0; i < M.m.size(); i++){
				vect_out.v[i] = 0;
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					vect_out.v[i] += M.m[i].v[j];
				}
			}
		}
		else{
			LOG("numerics::matrix_get_sum");
			throw std::exception();
		}
		return vect_out;
	}

	Md matrix_normalize(const Md& M, bool axis){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		Vd vect_sum;
		vect_sum = matrix_get_sum(M, axis);

		if (axis == 0){
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M.m[i].v[j] / vect_sum.v[j];
				}
			}
		}
		else if(axis == 1){
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M.m[i].v[j] / vect_sum.v[i];
				}
			}
		}
		else{
			LOG("numerics::matrix_normalize");
			throw std::exception();
		}
		return matr_out;
	}

	Md matrix_exp(const Md& M){
		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = pow(EULERS_NUMBER, M.m[i].v[j]);
			}
		}
		return matr_out;
	}

	Vd matrix_argmax(const Md& M){

		Vd vect_out;
		vect_out.fill(M.m.size(), 0);


		uint64_t idx = 0;

		for (uint64_t i = 0; i < M.m.size(); i++){
			idx = 0;
			for (uint64_t j = 1; j < M.m[0].v.size(); j++){
				if (M.m[i].v[j-1] < M.m[i].v[j]){
					idx = j;
				}
			}
			vect_out.v[i] = idx;
		}
		return vect_out;
	}

	Md matrix_transpose(const Md& M){

		Md matr_out;

		uint64_t rows = M.m.size();
		uint64_t cols = M.m[0].v.size();

		for (uint64_t i = 0; i < cols; i++){
			Vd temp_vec;
			for (uint64_t j = 0; j < rows; j++){
				temp_vec.v.push_back(M.m[j].v[i]);
			}
			matr_out.m.push_back(temp_vec);
		}
		return matr_out;
    }

   	double matrix_determinant(const Md& M){
   		//https://stackoverflow.com/questions/60300482/c-calculating-the-inverse-of-a-matrix

   		if (M.m.size() != M.m[0].v.size()){
   			throw std::runtime_error("numeric::matrix_determinant - Matrix is not quadratic");
   		}

		uint64_t dims = M.m.size();
		double determinant = 0;
		double sign = 1;
		uint64_t temp = 0;


		if(dims == 0){
			determinant = 1.0f;
		}
		else if(dims == 1){
			determinant = M.m[0].v[0];
		}
		else if(dims == 2){
			determinant = (M.m[0].v[0]*M.m[1].v[1] - M.m[0].v[1]*M.m[1].v[0]);
		}
		else{

			Md matr_temp;
			matr_temp.fill(dims-1, dims-1, 0);

			for (uint64_t i = 0; i < dims; i++){
				
				for (uint64_t m = 1; m < dims; m++){
					temp = 0;
					for (uint64_t n = 0; n < dims; n++){						
						if(n != i){
							matr_temp.m[m-1].v[temp] = M.m[m].v[n];
							temp++;
						}
					}
				}
				// recursice call
				determinant += sign * M.m[0].v[i] * matrix_determinant(matr_temp);
				sign = -sign;
			}
		}
		return determinant;
    }

   	Md matrix_cofactor(const Md& M){
   		//https://stackoverflow.com/questions/60300482/c-calculating-the-inverse-of-a-matrix

   		if (M.m.size() != M.m[0].v.size()){
   			throw std::runtime_error("numeric::matrix_determinant - Matrix is not quadratic");
   		}

		uint64_t dims = M.m.size();
		Md cofactor;
		Md matr_temp;
		uint64_t temp_p = 0;
		uint64_t temp_q = 0;


		cofactor.fill(dims, dims, 0);
		matr_temp.fill(dims-1, dims-1, 0);

		for (uint64_t i = 0; i < dims; i++){
			for(uint64_t j = 0; j < dims; j++){
				temp_p = 0;
				for (uint64_t x = 0; x < dims; x++){
					if(x == i){
						continue;
					}
					temp_q = 0;
					for (uint64_t y = 0; y < dims; y++){
						if (y == j){
							continue;
						}
						matr_temp.m[temp_p].v[temp_q] = M.m[x].v[y];
						temp_q++; 
					}
					temp_p++;
				}
				cofactor.m[i].v[j] = pow(-1, (i + j)) * matrix_determinant(matr_temp);
			}
		}
		return cofactor;
    }

   	Md matrix_inverse(const Md& M){
   		//https://stackoverflow.com/questions/60300482/c-calculating-the-inverse-of-a-matrix

   		if (M.m.size() != M.m[0].v.size()){
   			throw std::runtime_error("numeric::matrix_determinant - Matrix is not quadratic");
   		}

   		double det = 1.0/matrix_determinant(M);
   		uint64_t dims = M.m.size();

		Md matr_out;
		matr_out.fill(dims, dims, 0);

		for (uint64_t i = 0; i < dims; i++){
			for (uint64_t j = 0; j < dims; j++){
				matr_out.m[i].v[j] = M.m[i].v[j] * det;
			}
		}

		return matrix_transpose(matrix_cofactor(matr_out));
    }

   	Md matrix_scalar_element_wise_division(const Md& M, const double& C){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = M.m[i].v[j] / C;
			}
		}
		return matr_out;
    }


   	Md matrix_element_wise_division(const Md& M, const Md& N){

   		if (M.m.size() != N.m.size() || M.m[0].v.size() != N.m[0].v.size()){
   			throw std::runtime_error("numeric::matrix_element_wise_division - Matrix is not same size");
   		}

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = M.m[i].v[j] / N.m[i].v[j];
			}
		}
		return matr_out;
    }

   	Md matrix_sign(const Md& M){

		Md matr_out;
		matr_out.fill(M.m.size(), M.m[0].v.size(), 0);

		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				matr_out.m[i].v[j] = -M.m[i].v[j];
			}
		}
		return matr_out;
    }

	double random(const double& min, const double& max){
    std::mt19937_64 rng{}; 
    rng.seed( std::random_device{}());
    return std::uniform_real_distribution<>{min, max}(rng);
	}









}




























































void print_matrix(const std::vector<std::vector<double>> *const M){

	uint64_t rows = (*M).size();
	uint64_t cols = (*M)[0].size();
	//printf("Rows: %ld\r\n", rows);
	//printf("Cols:%ld\r\n", cols);

	if (cols == 1)
	{	
		printf("[");
		for (uint64_t i = 0; i < rows; ++i)
		{
			if (i == rows-1)
			{
				printf("[%f]]\r\n", (*M)[i][0]);
			}
			else
			{
				printf("[%f]\r\n", (*M)[i][0]);
			}
			

		}

	}
	else
	{
		for (uint64_t i = 0; i < rows; ++i)
		{
			for (uint64_t j = 0; j < cols; ++j)
			{
				if (j == cols-1 && i == rows-1)
				{
					printf("%f]]\r\n", (*M)[rows-1][cols-1]);
				}
				else if (j == 0 && i == 0)
				{
					printf("[[%f, ", (*M)[i][j]);
				}
				else if (j == 0)
				{
					printf("[%f, ", (*M)[i][j]);
				}
				else if (j == cols-1)
				{
					printf("%f]\r\n", (*M)[i][cols-1]);
				}
				else
				{
					printf("%f, ", (*M)[i][j]);
				}
			}
			
		}
	}
}


std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>> *const M){
	try{

		if ((*M).size() != 0)
		{
			uint64_t rows = (*M).size();
			uint64_t cols = (*M)[0].size();

		    std::vector<std::vector<double>> trans_matr(cols, std::vector<double>(rows, 0));
		    
		    for (uint64_t i = 0; i < rows; i++)
		    {
		        for (uint64_t j = 0; j < cols; j++)
		        {
		            trans_matr[j][i] = ((*M)[i][j]);
		        }
		    }

		    return trans_matr;
		}
		else{
			throw std::invalid_argument("Dimensions in transpose is not valid");
		}
	}
    catch (std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        std::vector<std::vector<double>> trans_matr(1, std::vector<double>(1, -1));
        return trans_matr;
    }
}


//passing vectors by reference avoids unnecessary copies
std::vector<std::vector<double>> dot(const std::vector<std::vector<double>> *const M, const std::vector<std::vector<double>> *const N){
	try{
		uint64_t M_rows = (*M).size();
		uint64_t M_cols = (*M)[0].size();

		uint64_t N_rows = (*N).size();
		uint64_t N_cols = (*N)[0].size();

		if (M_cols == N_rows)
		{
		    std::vector<std::vector<double>> dot_matr(M_rows, std::vector<double>(N_cols, 0));
		    
		    // Loop over rows
		    for (uint64_t i = 0; i < M_rows; i++)
		    {
		    	// Loop over columns
		    	for (uint64_t j = 0; j < N_cols; j++)
		    	{
		    		for (uint64_t k = 0; k < M_cols; k++)
		    		{
		    			dot_matr[i][j] += (*M)[i][k] * (*N)[k][j];
		    		}
		    		
		    	}
		    }

		    return dot_matr;
		}
		else{
			throw std::invalid_argument("Dimensions in dot() does not match");
		}
	}
    catch (std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        std::vector<std::vector<double>> dot_matr(1, std::vector<double>(1, -1));
        return dot_matr;
    }
}

std::vector<std::vector<double>> matr_add(const std::vector<std::vector<double>> *const M, const std::vector<std::vector<double>> *const N){
	try{
		uint64_t M_rows = (*M).size();
		uint64_t M_cols = (*M)[0].size();

		uint64_t N_rows = (*N).size();
		uint64_t N_cols = (*N)[0].size();
		printf("cols :%ld\r\n", N_cols);


		if (M_rows == N_rows && M_cols == N_cols)
		{
		    std::vector<std::vector<double>> add_matr(M_rows, std::vector<double>(M_cols, 0));
		    
		    // Loop over rows
		    for (uint64_t i = 0; i < M_rows; i++)
		    {
		    	// Loop over columns
		    	for (uint64_t j = 0; j < M_cols; j++)
		    	{
		    			add_matr[i][j] += (*M)[i][j] + (*N)[i][j];
		    	}
		    }

		    return add_matr;
		}
		else{
			throw std::invalid_argument("Dimensions in matr_add() does not match");
		}
	}
    catch (std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        std::vector<std::vector<double>> add_matr(1, std::vector<double>(1, -1));
        return add_matr;
    }
}



std::vector<std::vector<double>> matr_add_vect(const std::vector<std::vector<double>> *const M, const std::vector<double> *const v){
	try{
		uint64_t M_rows = (*M).size();
		uint64_t M_cols = (*M)[0].size();

		uint64_t size = (*v).size();

		if (M_cols == size)
		{
			std::vector<std::vector<double>> matr_add_vect(M_rows, std::vector<double>(M_cols, 0));
		    
		    // Loop over columns
		    for (uint64_t i = 0; i < M_rows; i++)
		    {
			    for (uint64_t j = 0; j < M_cols; j++)
			    {
			    	matr_add_vect[i][j] += (*M)[i][j] + (*v)[j];
			    }
		    }

		    return matr_add_vect;
		}
		else{
			throw std::invalid_argument("Dimensions in matr_add_vect does not match");
		}
	}
    catch (std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        std::vector<std::vector<double>> matr_add_vect(1, std::vector<double>(1, -1));
        return matr_add_vect;
    }
}