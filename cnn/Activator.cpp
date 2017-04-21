#include "stdafx.h"
#include "Activator.h"


Activator::Activator()
{
}


Activator::~Activator()
{
}
double Activator::forward(double weight_input){
	return weight_input > 0 ? weight_input : 0;

}
double Activator::back(double out_put){

	return out_put>0?1:0;
}