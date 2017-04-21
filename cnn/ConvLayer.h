#pragma once

#include<vector>
#include"commom.h"
#include"Activator.h"
using namespace std;
typedef vector<vector<vector<double>>> array3;
class ConvLayer
{
private:
	int input_width;
	int input_height;
	int channel_number;
	int filter_number;
	int filter_width;
	int filter_height;
	int zero_padding;
	int stride;
	int output_width;
	int output_height;
	Activator activator;
	double learning_rate;
	array3 input_array;
	array3 output_array;
	array3 padded_input_array;
	vector<Filter> Filters;
	array3 delta_array;

public:
	ConvLayer();
	~ConvLayer();
	ConvLayer(int input_width,int input_height,\
		int channel_number,int filter_number,\
		int filter_width,int filter_height,\
		int zero_padding,int stride,Activator activator,\
		double learning_rate);
	void forward(array3 input_array);
	void bp_sensitivity_map(array3 sneditivity_array,Activator activate);
	array3 expand_sensitivity_map(array3 sensitivity_array);
	array3 create_delta_array(){
		return zero(\
			this->input_array, this->input_width, \
			this->input_height, this->channel_number);
	}
	array3 matrix_rot180(array3 input_array);
	void bp_gradient(array3 sensitivity_array);
	void update();

};
   





	/*
	对卷积神经网络，channelnumber等于输入的维度
	output输出为二维数组
	输出个数等于卷积核心的个数
	
	
	*/