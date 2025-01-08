#include "numerics.h"



namespace numeric{
	//#######################################
	//#   UTILITY FUNCTIONS FOR VECTOR      #
	//#######################################
	void vector_dot(double& dot_product, const Vd *const v1, const Vd *const v2){

		if (v1->v.size() != v2->v.size()){
			LOG("???");
			throw std::exception();
		}

		dot_product = 0;

		for (uint64_t i = 0; i < v1->v.size(); i++)
		{
			dot_product += v1->v[i]*v2->v[i];
		}
	}

	void vector_max_cap(Vd& vect_out, const Vd *const vect, const double value){

		if (vect_out.v.size() != vect->v.size()){
			vect_out.fill(vect->v.size(), 0);
		}		

		for (uint64_t i = 0; i < vect->v.size(); i++)
		{
			vect_out.v[i] = MIN(vect->v[i], value);
		}
	}
	
	void vector_min_cap(Vd& vect_out, const Vd *const vect, const double value){

		if (vect_out.v.size() != vect->v.size()){
			vect_out.fill(vect->v.size(), 0);
		}

		for (uint64_t i = 0; i < vect->v.size(); i++)
		{
			vect_out.v[i] = MAX(vect->v[i], value);
		}
	}

	void vector_clip(Vd& vect_out, const Vd *const vect, const double min_value, const double max_value){

		if (vect_out.v.size() != vect->v.size()){
			vect_out.fill(vect->v.size(), 0);
		}

		for (uint64_t i = 0; i < vect->v.size(); i++){
			vector_max_cap(vect_out, vect, max_value);
			vector_min_cap(vect_out, &vect_out, min_value);
		}
	}

	void vector_normalize(Vd& vect_out, const Vd *const vect, const double value){

		double vect_sum = vect->get_sum();

		for (uint64_t i = 0; i < vect->v.size(); i++){
			vect_out.v[i] = vect->v[i]/vect_sum;
		}
	}

	//#######################################
	//#   UTILITY FUNCTIONS FOR Matrix      #
	//#######################################
	void matrix_fill_RNG(Md& M, const double min, const double max){
		for (uint64_t i = 0; i < M.m.size(); i++){
			for (uint64_t j = 0; j < M.m[0].v.size(); j++){
				M.m[i].v[j] = random(min, max);
			}
		}
	}

	void matrix_dot(Md& matr_out, const Md *const M, const Md *const N){

		if (matr_out.m.size() != M->m.size() || matr_out.m[0].v.size() != N->m[0].v.size()){
			matr_out.fill(M->m.size(),N->m[0].v.size(),0);
		}

		if (M->m[0].v.size() != N->m.size()){
			LOG("???");
			throw std::exception();
		}
		else{
			for (uint64_t i = 0; i < M->m.size(); i++){
				for (uint64_t j = 0; j < N->m[0].v.size(); j++){
					for (uint64_t k = 0; k < N->m.size(); k++)
					{
						matr_out.m[i].v[j] += M->m[i].v[k] * N->m[k].v[j];
					}
				}
			}
		}
	}
	void matrix_add_vector(Md& matr_out, const Md *const M, const Vd *const vect, bool axis){

		if (matr_out.m.size() != M->m.size() || matr_out.m[0].v.size() != M->m[0].v.size()){
			matr_out.fill(M->m.size(), M->m[0].v.size(), 0);
		}


		if (axis == 0 && matr_out.m[0].v.size() == vect->v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M->m[i].v[j] + vect->v[j];
				}
			}
		}
		else if (axis == 1 && matr_out.m.size() == vect->v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M->m[i].v[j] + vect->v[i];
				}
			}
		}
		else{
			LOG("???");
			throw std::exception();
		}
	}


	void matrix_sub_vector(Md& matr_out, const Md *const M, const Vd *const vect, bool axis){

		if (matr_out.m.size() != M->m.size() || matr_out.m[0].v.size() != M->m[0].v.size()){
			matr_out.fill(M->m.size(), M->m[0].v.size(), 0);
		}


		if (axis == 0 && matr_out.m[0].v.size() == vect->v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M->m[i].v[j] - vect->v[j];
				}
			}
		}
		else if (axis == 1 && matr_out.m.size() == vect->v.size()){
			for (uint64_t i = 0; i < matr_out.m.size(); i++){
				for (uint64_t j = 0; j < matr_out.m[0].v.size(); j++){
					matr_out.m[i].v[j] = M->m[i].v[j] - vect->v[i];
				}
			}
		}
		else{
			LOG("???");
			throw std::exception();
		}
	}

	void matrix_max_cap(Md& matr_out, const Md *const M, const double value){

		if (matr_out.m.size() != M->m.size() || matr_out.m[0].v.size() != M->m[0].v.size()){
			matr_out.fill(M->m.size(),M->m[0].v.size(),0);
		}

		for (uint64_t i = 0; i < M->m.size(); i++){
			for (uint64_t j = 0; j < M->m[0].v.size(); j++){
				matr_out.m[i].v[j] = MIN(M->m[i].v[j], value);
			}
		}
	}

	void matrix_min_cap(Md& matr_out, const Md *const M, const double value){

		if (matr_out.m.size() != M->m.size() || matr_out.m[0].v.size() != M->m[0].v.size()){
			matr_out.fill(M->m.size(),M->m[0].v.size(),0);
		}

		for (uint64_t i = 0; i < M->m.size(); i++){
			for (uint64_t j = 0; j < M->m[0].v.size(); j++){
				matr_out.m[i].v[j] = MAX(M->m[i].v[j], value);
			}
		}
	}

	void matrix_clip(Md& matr_out, const Md *const M, const double min_value, const double max_value){

		if (matr_out.m.size() != M->m.size() || matr_out.m[0].v.size() != M->m[0].v.size()){
			matr_out.fill(M->m.size(),M->m[0].v.size(),0);
		}

		for (uint64_t i = 0; i < M->m.size(); i++){
			for (uint64_t j = 0; j < M->m[0].v.size(); j++){
				matr_out.m[i].v[j] = MAX(M->m[i].v[j], min_value);
				matr_out.m[i].v[j] = MIN(M->m[i].v[j], max_value);
			}
		}
	}

	void matrix_get_max(Vd& vect_out, const Md *const M, bool axis){
		if (axis == 0 && M->m[0].v.size() != vect_out.v.size()){
			vect_out.fill(M->m[0].v.size(), 0);

			for (uint64_t i = 0; i < M->m.size(); i++){
				for (uint64_t j = 0; j < M->m[0].v.size(); j++){
					vect_out.v[j] = MAX(vect_out.v[j], M->m[i].v[j]);
				}
			}
		}
		else if(axis == 1 && M->m.size() != vect_out.v.size()){
			vect_out.fill(M->m.size(), 0);

			for (uint64_t i = 0; i < M->m.size(); i++){
				for (uint64_t j = 0; j < M->m[0].v.size(); j++){
					vect_out.v[i] = MAX(vect_out.v[i], M->m[i].v[j]);
				}
			}
		}
		else{
			LOG("???");
			throw std::exception();
		}
	}

	void matrix_get_min(Vd& vect_out, const Md *const M, bool axis){
		if (axis == 0 && M->m[0].v.size() != vect_out.v.size()){
			vect_out.fill(M->m[0].v.size(), 0);

			for (uint64_t i = 0; i < M->m.size(); i++){
				for (uint64_t j = 0; j < M->m[0].v.size(); j++){
					vect_out.v[j] = MAX(vect_out.v[j], M->m[i].v[j]);
				}
			}
		}
		else if(axis == 1 && M->m.size() != vect_out.v.size()){
			vect_out.fill(M->m.size(), 0);

			for (uint64_t i = 0; i < M->m.size(); i++){
				for (uint64_t j = 0; j < M->m[0].v.size(); j++){
					vect_out.v[i] = MIN(vect_out.v[i], M->m[i].v[j]);
				}
			}
		}
		else{
			LOG("???");
			throw std::exception();
		}
	}

	void matrix_get_sum(Vd& vect_out, const Md *const M, bool axis){
		if (axis == 0 && M->m[0].v.size() != vect_out.v.size()){
			vect_out.fill(M->m[0].v.size(), 0);

			for (uint64_t i = 0; i < M->m.size(); i++){
				for (uint64_t j = 0; j < M->m[0].v.size(); j++){
					vect_out.v[j] += M->m[i].v[j];
				}
			}
		}
		else if(axis == 1 && M->m.size() != vect_out.v.size()){
			vect_out.fill(M->m.size(), 0);

			for (uint64_t i = 0; i < M->m.size(); i++){
				vect_out.v[i] = 0;
				for (uint64_t j = 0; j < M->m[0].v.size(); j++){
					vect_out.v[i] += M->m[i].v[j];
				}
			}
		}
		else{
			LOG("???");
			throw std::exception();
		}
	}

	void matrix_normalize(Md& M, bool axis){

		Vd vect_sum;
		matrix_get_sum(vect_sum, &M, axis);

		if (axis == 0){
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					M.m[i].v[j] /= vect_sum.v[j];
				}
			}
		}
		else if(axis == 1){
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					M.m[i].v[j] /= vect_sum.v[i];
				}
			}
		}
		else{
			LOG("???");
			throw std::exception();
		}
	}

	void matrix_exp(Md& M){
			for (uint64_t i = 0; i < M.m.size(); i++){
				for (uint64_t j = 0; j < M.m[0].v.size(); j++){
					M.m[i].v[j] = pow(EULERS_NUMBER, M.m[i].v[j]);
				}
			}
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