#include"stdafx.h"
#include"commom.h"
array3 padding(array3 input_array, int zero_padding_num){//dim1为深度 dim2为高度 dim3为深度
	if (zero_padding_num == 0)return input_array;
	array3 output_array;
	
	output_array = zero(output_array, input_array.size() + 2 * zero_padding_num, input_array[0].size() + 2 * zero_padding_num, input_array[0][0].size());//长度、宽度、深度

	for (size_t i = 0; i < input_array.size(); i++)
	{
		for (size_t j = 0; j < input_array[0].size(); j++)
		{
			for (size_t k = 0; k < input_array[0][0].size(); k++)
			{
				output_array[i][j + zero_padding_num][k + zero_padding_num] = input_array[i][j][k];
			}
			
		}
		
	}
	return output_array;
}
array3 resize(array3 input_array, int width, int height, int depth){//重置矩阵大小
	input_array.resize(depth);
	for (size_t i = 0; i < depth; i++)
	{
		input_array[i].resize(height);
		for (size_t j = 0; j < height; j++)
		{
			input_array[i][j].resize(width);
		}

	}
	return input_array;

}
array3 zero(array3 input_array, int width, int height, int depth){//矩阵归0

	input_array.resize(depth);
	for (size_t i = 0; i < depth; i++)
	{
		input_array[i].resize(height);
		for (size_t j = 0; j < height; j++)
		{
			input_array[i][j].resize(width);
			for (size_t k = 0; k < width; k++)
			{
				input_array[i][j][k]=0;
			}
		}

	}
	return input_array;

}
void print_matrxi(array3 input_array){//打印矩阵元素信息,三维
	for (size_t i = 0; i < input_array.size(); i++)
	{//打印第i个二维矩阵
		cout << "第" << i << "个矩阵" << endl;
		for (size_t j = 0; j < input_array[0].size(); j++)
		{
			for (size_t k = 0; k <input_array[0][0].size(); k++)
			{
				cout << input_array[i][j][k] << " ";
			}
			cout << endl;

		}

	}

}
array3 init_matrix_random(array3 input_array){//对一个3维矩阵随机赋值
	for (size_t i = 0; i < input_array.size(); i++)
	{
		for (size_t j = 0; j < input_array[0].size(); j++)
		{
			for (size_t k = 0; k < input_array[0][0].size(); k++)
			{
				input_array[i][j][k]=(double)rand()/(double)RAND_MAX;
			}
		}
	}
	return input_array;


}
array3 conv(array3 input_array, array3 kernel_array,\
	array3& output_array,int stride, double bias){//使用该函数前，确保output.size()==1.
	/////this fuction is pass;
	//实现 2维3维数组的卷积
	//输出的feature map
	int output_height=output_array[0].size();
	//输出feature map的高度
	int output_width = output_array[0][0].size();
	//输出feature map的宽度
	int output_depth = output_array.size();
	//通常为1，也就是二维
	///设置卷积核大小
	int kernel_width = kernel_array[0][0].size();
	int kernel_depth = kernel_array.size();
	int kernel_height = kernel_array[0].size();
	//通常kernel_width和kernel_height相等
	/////
	if (output_array.size()==1)//维度为2。
	{
		for (size_t i = 0; i < output_array.size(); i++)
			//卷积深度方向
		{
			for (size_t j = 0; j < output_array[0].size(); j ++)
				//卷积高度方向
			{
				for (size_t k = 0; k < output_array[0][0].size(); k ++)
					//卷积宽度方向
				{
					output_array[i][j][k] = conv_kernel(input_array, kernel_array, j+stride, k+stride, bias);//计算卷卷积核和input特定区域的卷积
				}
			}
		}

	}
	else
	{
		cout << "output.size()!=1,检查output的维度" << endl;

	}
	return output_array;//二维数组。

}
double conv_kernel(array3 input_array,array3 kernel_array,\
	int ref_x,int ref_y,double bias){//一次卷积运算.test is pass

	double sum = 0;
	for (size_t i = 0; i < kernel_array.size(); i++)
	{
		for (size_t j = 0; j < kernel_array[0].size(); j++)
		{
			for (size_t k = 0; k < kernel_array[0][0].size(); k++)
			{
				sum+=kernel_array[i][j][k] *input_array[i][ref_y+j][ref_y+k];
			}
		}

	}
	Activator act;
	return act.forward(sum + bias);

}
 int calculate_output_size(int input_size,int filter_size,int zero_padding,int stride){
	return (input_size - filter_size + 2 * zero_padding) / stride + 1;// this funtion test is pass;

}
array3 matrix_rot180(array3 input_array){
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