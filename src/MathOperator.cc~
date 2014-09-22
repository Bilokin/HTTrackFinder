#include "MathOperator.hh"
#include <stdlib.h> 
#include <cmath>
namespace MyCalorimeter
{
	bool MathOperator::approximatelyEqual(const double * start1, const double * start2)
	{
		float distanceCut = 5.0;
		for (int i = 0; i < 3; i++)
		{
			int distanceBirth = abs(start1[i]-start2[i]);
			if (distanceBirth > distanceCut)
			{
			        //std::cout << "Distance: " << distanceBirth <<'\n';
			        return false;
			}
		}
		return true;
	}
	
	float MathOperator::getDistance(const double * start, const double * end)
	{
		vector<float> vec;
		for (int i = 0; i < 3; i++) 
		{
			vec.push_back(start[i] - end[i]);
		}
		float sqr = 0.0;
		for (int i = 0; i < 3; i++) 
		{
		        sqr += vec[i]*vec[i];
		}
		return sqrt(sqr);
	}
	
	float MathOperator::getModule(vector< int > & v)
	{
	       float module = 0.0;
	       for (int i = 0; i < v.size(); i++)
	       {
	               module += v[i]*v[i];
	       }
	       module = sqrt(module);
	       return module;
	}
	
	float MathOperator::getModule(vector< float > & v)
	{
		float module = 0.0;
		for (int i = 0; i < v.size(); i++)
		{
		        module += v[i]*v[i];
		}
		module = sqrt(module);
		return module;
	}

	vector< float > MathOperator::getDirection(vector< int > & vectorPoint1, vector< int > & vectorPoint2)
	{
		/*double * arr1 = MathOperator::castIntToDouble(&vectorPoint1[0]);
		double * arr2 = MathOperator::castIntToDouble(&vectorPoint2[0]);
		vector< float > result = MathOperator::getDirection(arr1,arr2);
		delete [] arr1;
		delete [] arr2;
		return result;*/
		vector< float > vector1;
		for (int i = 0; i < 3; i++)
		{
		        vector1.push_back((float)(vectorPoint1[i] - vectorPoint2[i]));
		}
		float module = getModule(vector1);
		for (int i = 0; i < 3; i++)
		{
		        vector1[i] = vector1[i]/module;
		}
		return vector1;
	}
	
	vector< float > MathOperator::getDirection(const double * vectorPoint1, const double * vectorPoint2)
	{
		vector< float > vector1;
		for (int i = 0; i < 3; i++)
		{
		        vector1.push_back(vectorPoint1[i] - vectorPoint2[i]);
		}
		float module = getModule(vector1);
		for (int i = 0; i < 3; i++)
		{
		        vector1[i] = vector1[i]/module;
		}
		return vector1;
	}

	vector< float > * MathOperator::vectorProduct(vector< float > & v1, vector< float > & v2)
	{
		vector<float> * result = new vector<float>();
		result->push_back(v1[1]*v2[2]-v1[2]*v2[1]);
		result->push_back(v1[2]*v2[0]-v1[0]*v2[2]);
		result->push_back(v1[0]*v2[1]-v1[1]*v2[0]);
		return result;
	}

	float MathOperator::getDistanceTo(vector< int > & vectorPoint1, vector< float > & vector1, vector< int > * point )
	{
		float result = 0.0;
		//vector< float > vector1 = getDirection(vectorPoint1,vectorPoint2);
		vector< float > vector2;
		for (int i = 0; i < 3; i++)
		{
		        vector2.push_back((float)(vectorPoint1[i] - point->at(i)));
		}
		vector< float > * product = vectorProduct(vector1,vector2);
		result = getModule(*product)/getModule(vector1);
		delete product;
		return result;
	}

	float MathOperator::getDistanceTo(const double * vectorPoint1, vector< float > & vector1,const double * point )
	{
		float result = 0.0;
		vector< float > vector2;
		for (int i = 0; i < 3; i++)
		{
		        vector2.push_back(vectorPoint1[i] - point[i]);
		}
		vector< float > * product = vectorProduct(vector1,vector2);
		result = getModule(*product)/getModule(vector1);
		delete product;
		return result;
	}


	double * MathOperator::castIntToDouble(int * array)
	{
		int size = (sizeof(array)/sizeof(*array));
		if (size < 1) 
		{
			return NULL;
		}
		double * arrPoint1 = new double[size];
		for (int i = 0; i < size; i++) 
		{
			arrPoint1[i] = array[i];
		}
		return arrPoint1;
	}
}
