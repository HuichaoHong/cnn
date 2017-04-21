#include "stdafx.h"
#include "Filter.h"
Filter::Filter()
{
}
Filter::~Filter()
{
}
Filter::Filter(int width, int height, int depth){
	this->width = width;
	this->height=height;
	this->depth = depth;
	//初始化weights[][][]
	weights.resize(depth);
	for (size_t i = 0; i < this->depth; i++)
	{
		weights[i].resize(this->height);
		for (size_t j = 0; j < this->height; j++)
		{
			weights[i][j].resize(this->width);
			for (size_t k = 0; k < this->width; k++)
			{
				weights[i][j][k] = -powf(10, -4) + powf(10, -4)*(rand() / (double)RAND_MAX);
				//cout << weights[i][j][k];
				//system("pause");

			}
		}
	}
	//初始化weights_grad[][][]=0
	weights_grad.resize(this->depth);
	for (size_t i = 0; i < this->depth; i++)
	{
		weights_grad[i].resize(this->height);
		for (size_t j = 0; j < this->height; j++)
		{
			weights_grad[i][j].resize(this->width);
			for (size_t k = 0; k < this->width; k++)
			{
				weights_grad[i][j][k] = 0;
			}
		}
	}

	//设置初始bias
	bias = 0;
	bias_grad = 0;

}
array3 Filter::get_weights(){
	return weights;
}
double Filter::get_bias(){
	return bias;
}
void Filter::update(double learning_rate){
	//更新weights的值
	for (size_t i = 0; i < this->depth; i++)
	{
		for (size_t j = 0; j < this->height; j++)
		{
			for (size_t k = 0; k < this->width; k++)
			{
				this->weights[i][j][k]-= learning_rate*this->weights_grad[i][j][k];
			}
		
		}
	}
	//
	//
	this->bias -= learning_rate*this->bias_grad;
}