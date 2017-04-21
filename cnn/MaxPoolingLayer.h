#pragma once
class MaxPoolingLayer
{

	int input_width;
	int input_height;
	int channel_number;
	int fiter_width;
	int filter_height;
	int stride;

public:
	MaxPoolingLayer();
	~MaxPoolingLayer();
	MaxPoolingLayer(int input_width,int input_height,int channel_number,
		int fiter_width,int filter_height,int stride);

};

