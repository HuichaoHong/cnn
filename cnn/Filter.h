#pragma once
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;
typedef vector<vector<vector<double>>> array3;

class Filter
{

private:
	int width;
	int height;
    int depth;
	array3 weights;
	double bias;
	array3 weights_grad;
	double bias_grad;
public:
	Filter();
	~Filter();
	array3 get_weights();
	double get_bias();
	void update(double learing_rate);
	Filter(int width,int height,int depth);

};

