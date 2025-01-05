#ifndef _numerics_n_
#define _numerics_n_

#include "iostream"
#include <vector>
#include <random>

//Set debug to 0 to disable logging

#define DEBUG 1
#if DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

#define EULERS_NUMBER 2.718281828459

namespace numeric{
	//#######################################
	//#            VECTOR TYPE             #
	//#######################################
	template<typename T>
	struct Vector{
		std::vector<T> v;

		void fill(const uint64_t size, const T num){
			v.clear();
			for (uint64_t i = 0; i < size; i++)
			{
				v.push_back(num);
			}
		}

		void fill_RNG(const uint64_t size, const double min, const double max){
			v.clear();
			
			std::mt19937_64 rng{}; 
			rng.seed( std::random_device{}());

			for (uint64_t i = 0; i < size; i++){

				v.push_back(std::uniform_real_distribution<>{min, max}(rng));
			}
		}

		double get_max(){
			double max_value = v[0];

			for (uint64_t i = 1; i < v.size(); i++){
				max_value = MAX(max_value, v[i]);
			}
			return max_value;
		}

		double get_min(){
			double min_value = v[0];

			for (uint64_t i = 1; i < v.size(); i++){
				min_value = MIN(min_value, v[i]);
			}
			return min_value;
		}

		double get_sum(){
			double sum_value = 0;

			for (uint64_t i = 0; i < v.size(); i++){
				sum_value += v[i];
			}
			return sum_value;
		}

		double get_mean(){
			double mean_value = get_sum()/v.size();
			return mean_value;
		}



		inline friend std::ostream& operator << (std::ostream& out, const Vector& vec){
			out << "[";
			for (uint64_t i = 0; i < vec.v.size(); i++)
			{
				if (i % vec.v.size() == vec.v.size() - 1){
					out << vec.v[i] << "]" << std::endl;
				}
				else{
					out << vec.v[i] << ", ";
				}
			}
			return out;
		}
	};

	typedef Vector<int> Vi;
	typedef Vector<float> Vf;
	typedef Vector<double> Vd;

	//#######################################
	//#            MATRIX TYPE              #
	//#######################################
	template <typename T>
	struct Matrix{
		std::vector<T> m;

		using vector_type = typename decltype(std::declval<T>().v)::value_type;

		void fill(uint64_t rows, uint64_t cols, const vector_type num){
			m.clear();
			for (uint64_t i = 0; i < rows; i++){
				T temp_vec;

				for (uint64_t j = 0; j < cols; j++){
					temp_vec.v.push_back(num);
				}
				m.push_back(temp_vec);
			}
		}

		void fill_RNG(const uint64_t rows, const uint64_t cols, const double min, const double max){
				m.clear();

				std::mt19937_64 rng{}; 
    			rng.seed( std::random_device{}());
    
				for (uint64_t i = 0; i < rows; i++){
					T temp_vec;
					for (uint64_t j = 0; j < cols; j++){
						temp_vec.v.push_back(std::uniform_real_distribution<>{min, max}(rng));
					}
					m.push_back(temp_vec);
				}
			}

		inline friend std::ostream& operator << (std::ostream& out, const Matrix& mat){
			out << "[";
			for (uint64_t i = 0; i < mat.m.size(); i++){
				out << "[";
				for (uint64_t j = 0; j < mat.m[i].v.size(); j++){
					if (j % mat.m[i].v.size() == mat.m[i].v.size() -1 && i == mat.m.size()-1){
						out << mat.m[i].v[j] << "]";
					}
					else if ((j % mat.m[i].v.size() == mat.m[i].v.size() -1)){
						out << mat.m[i].v[j] << "]," << std::endl;
					}
					else{
						out << mat.m[i].v[j] << ", ";
					}
				}
			}
			out << "]";
			return out;
		}

		void transpose(){
			std::vector<T> temp_m = m;
			m.clear();

			uint64_t rows = temp_m.size();
			uint64_t cols = temp_m[0].v.size();

			for (uint64_t i = 0; i < cols; i++){
				T temp_vec;
				for (uint64_t j = 0; j < rows; j++){
					temp_vec.v.push_back(temp_m[j].v[i]);
				}
				m.push_back(temp_vec);
			}
	    }
	};

	typedef Matrix<Vi> Mi;
	typedef Matrix<Vf> Mf;
	typedef Matrix<Vd> Md;

	//#######################################
	//#   UTILITY FUNCTIONS FOR VECTOR      #
	//#######################################
	double vector_dot(const Vd *const v1, const Vd *const v2);
	Vd vector_max_cap(const Vd *const vec, const double value);
	Vd vector_min_cap(const Vd *const vec, const double value);
	Vd vector_normalize(const Vd *const vec, const double value);

	//#######################################
	//#   UTILITY FUNCTIONS FOR MATRIX      #
	//#######################################
	void matrix_fill_RNG(Md& matr_out, const double min, const double max);
	void matrix_dot(Md& matr_out, const Md *const M, const Md *const N);
	void matrix_add_vector(Md& matr_out, const Md *const M, const Vd *const vect, bool axis);
	void matrix_sub_vector(Md& matr_out, const Md *const M, const Vd *const vect, bool axis);
	void matrix_max_cap(Md& matr_out, const Md *const M, const double value);
	void matrix_min_cap(Md& matr_out, const Md *const M, const double value);
	void matrix_clip(Md& matr_out, const Md *const M, const double min_value, const double max_value);
	void matrix_get_max(Vd& vect_out, const Md *const M, bool axis);
	void matrix_get_min(Vd& vect_out, const Md *const M, bool axis);
	void matrix_get_sum(Vd& vect_out, const Md *const M, bool axis);
	void matrix_normalize(Md& M, bool axis);
	void matrix_exp(Md& M);







	double random(const double& min, const double& max);
}


#endif // _numerics_n_