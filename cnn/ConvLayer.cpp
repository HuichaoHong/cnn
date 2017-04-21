#include "stdafx.h"
#include "ConvLayer.h"

ConvLayer::ConvLayer()
{
}
ConvLayer::~ConvLayer()
{
}
ConvLayer::ConvLayer(int input_width, int input_height, \
	int channel_number, int filter_number, \
	int filter_width, int filter_height, \
	int zero_padding, int stride, Activator activator, \
	double learning_rate)
{
	this->input_width = input_width;
	this->input_height = input_height;
	this->channel_number = channel_number;//指示输入为3维或者二维
	this->filter_number = filter_number;
	this->filter_height = filter_height;
	this->filter_width = filter_width;
	this->zero_padding = zero_padding;
	this->stride = stride;
	this->activator = activator;
	this->output_height = calculate_output_size(input_height, filter_height, zero_padding, stride);
	this->output_width = calculate_output_size(input_width,filter_width,zero_padding,stride);


	//初始化input_array大小：input_width*input_height*channnelnumber
	input_array.resize(channel_number);
	for (size_t i = 0; i < input_height; i++)
	{
		input_array[i].resize(input_height);
		for (size_t j = 0; j < input_width; j++)
		{
			input_array[i][j].resize(input_width);
		}

	}//
	//卷积核初始化
	this->filter_number = filter_number;
	this->filter_height = filter_height;
	this->filter_width = filter_width;
	for (size_t i = 0; i < filter_number; i++)
	{
		Filters[i] = Filter(filter_width, filter_height, channel_number);
	}


}

void ConvLayer::forward(array3 input_array) { //this function test is pass
	this->input_array = input_array;
	this->padded_input_array = padding(input_array,this->zero_padding);//test is ok
	for (size_t f = 0; f < this->filter_number; f++)
	{
		conv(this->padded_input_array,Filters[f].get_weights(),this->output_array,this->stride,Filters[f].get_bias());
	}

////this function test is pass
}
void ConvLayer::bp_sensitivity_map(array3 sneditivity_array, Activator activate){
	//处理卷积步长，对原始sensitivity进行扩张
	array3 expand_sensitivity_array = expand_sensitivity_map(sneditivity_array);
	//full卷积，对sensitivitymap进行zeropadding
	int expand_width=expand_sensitivity_array[0][0].size();//扩张完的expand_sensitivity_map的宽度
	int zp = (this->input_width + this->filter_width - 1 - expand_width) / 2;
	array3 padded_array = padding(expand_sensitivity_array,zp);//对expand_sensitive_map进行zero padding
	//初始化delta——array，用于保存传递到上一层的sensitivity map
	this->delta_array = create_delta_array();//
	//对于具有多个filter的卷基层来说，最终传递到上一层的sensitivity map之和

	for (size_t f = 0; f < this->filter_number; f++)
	{
		Filter filter = this->Filters[f];
		array3 flipped_weights = this->\
			matrix_rot180(filter.get_weights());//三维，
		array3 delta = this->create_delta_array();//创建保存误差项的数组
		//对具有多个的filter的卷积层来说，最总传递
		//到上一层的sensitivity map相当于所有filter的 sensitivity map
		//之和
		array3 delta_array = this->create_delta_array();
		for (size_t d = 0; d < filter.get_weights().size(); d++)
		{
			///卷积的维度
			



		}
		

	}

}

array3 ConvLayer::expand_sensitivity_map(array3 sensitivity_array){
	int depth = sensitivity_array.size();
	//确定扩展后sensitivity map的大小
 //计算stride为1时，sensitivity map的大小
	int expand_width = this->input_width -\
		this->filter_width + 2 * this->zero_padding + 1;
	int expand_height = this->input_height - \
		this->filter_height + 2 * this->zero_padding + 1;
	array3 expand_array = zero(expand_array,expand_width,expand_height,depth);
	////
	for (size_t d = 0; d < depth; d++)
	{

		for (size_t i = 0; i < this->output_height; i++)
		{
			for (size_t j = 0; j < this->output_width; i++)
			{
				int i_pos = i*this->stride;
				int j_pos = j*this->stride;
				expand_array[d][i_pos][j_pos] = sensitivity_array[d][i][j];

			}
		}
	}


	return expand_array;


}
array3 ConvLayer::matrix_rot180(array3 input_array){//this function test is pass，实现功能矩阵的元素翻转180°
	array3 output_array = input_array;
	for (size_t i = 0; i < input_array.size(); i++)
	{
		for (size_t j = 0; j < input_array[0].size(); j++)
		{
			for (size_t k = 0; k < input_array[0][0].size(); k++)
			{
				output_array[i][input_array[0].size()-1 - j][input_array[0][0].size()-1 - k] = input_array[i][j][k];

			}
			
		}
	}
	return output_array;

}
void ConvLayer::bp_gradient(array3 sensitivity_array){
//处理卷积步长，对原始的sensitivity map进行扩展
	array3 expanded_array = expand_sensitivity_map(sensitivity_array);
	for (size_t f = 0; f < this->filter_number; f++)
	{
		Filter fliter = this->Filters[f];
		//for (size_t j = 0; j < length; j++)
		//{

		//}
	}




}
void ConvLayer::update(){
	for (size_t i = 0; i < this->filter_number; i++)
	{
		this->Filters[i].update(this->learning_rate);

	}
}



