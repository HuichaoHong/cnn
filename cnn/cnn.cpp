// cnn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include"Filter.h"
#include"Activator.h"
#include"commom.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Filter M(5, 5, 5);
	//Activator a;
	//test
	//cout<<a.forward(-5);
	//cout << a.back(2);
	//system("pause");
	//array3 a;
	//a=resize(a, 10, 10, 10);
	//a = init_matrix_random(a);
	//a=padding(a,2);
	//print_matrxi(a);
	//system("pause");
	/*test 函数 ：double conv_kernel(array3 input_array,array3 kernel_array,\
	int ref_x,int ref_y,double bias)*/
	array3 input_array;
	input_array=zero(input_array,3,3,2);
	input_array = init_matrix_random(input_array);
	print_matrxi(input_array);
	system("pause");
	array3 kernel = zero(kernel, 2, 2, 2);
	kernel = init_matrix_random(kernel);
	cout << "frist" << endl;

	print_matrxi(kernel);
	//cout<<"卷积结果:"<<conv_kernel(input_array, kernel, 0, 0, 0);//test is pass;
	system("pause");
	cout << "second" << endl;

	array3 kernel_rot;
	kernel_rot= matrix_rot180(kernel);
	print_matrxi(kernel_rot);
	system("pause");

}

