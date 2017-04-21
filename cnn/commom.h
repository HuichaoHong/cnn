#include<vector>
#include<iostream>
#include"Filter.h"
#include"Activator.h"
using namespace std;
typedef vector<vector<vector<double>>> array3;
array3 padding(array3 input_array, int zero_padding_num);
array3 resize(array3 input_array,int width,int height,int depth);
array3 zero(array3 input_array, int width, int height, int depth);
void print_matrxi(array3 input_array);
array3 init_matrix_random(array3 input_array);
array3 conv(array3 input_array, array3 kernel_array, \
	array3& output_array, int stride, double);
double conv_kernel(array3 input_array, array3 kernel_array, \
	int ref_x, int ref_y, double bias);
 int calculate_output_size(int input_size, int filter_size, int zero_padding, int stride);
array3 matrix_rot180(array3 input_array);