#include "MathOperator.hh"
using std::vector;
namespace HTransform 
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
	
	float MathOperator::getModule(const vector< int > & v)
	{
	       float module = 0.0;
	       for (int i = 0; i < v.size(); i++)
	       {
	               module += v[i]*v[i];
	       }
	       module = sqrt(module);
	       return module;
	}
	
	float MathOperator::getModule(const vector< float > & v)
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

	vector< float > * MathOperator::vectorProduct(const vector< float > & v1, const vector< float > & v2)
	{
		vector<float> * result = new vector<float>();
		result->push_back(v1[1]*v2[2]-v1[2]*v2[1]);
		result->push_back(v1[2]*v2[0]-v1[0]*v2[2]);
		result->push_back(v1[0]*v2[1]-v1[1]*v2[0]);
		return result;
	}

	float MathOperator::getDistanceTo( const vector< int > & vectorPoint1, const vector< float > & vector1,const vector< int > * point )
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
	vector< vector< int > * > * MathOperator::GetMagicNumbers()
	{
		vector< vector< int > * > * result = new vector< vector< int > * >();
		for (int x = -2; x < 3; x++)
		{
		        for (int y = -2; y < 3; y++)
			{
			        int z = 2;
				result->push_back(getPoint(x,y,z));
			}
			for (int y = -2; y < 3; y+=4)
			{
			        int z = 1;
				result->push_back(getPoint(x,y,z));
			}
			int y = -2;
			int z = 0;
			result->push_back(getPoint(x,y,z));

		}
		for (int x = -2; x < 3; x+=4)
		{
		        for (int y = -1; y < 2; y++)
			{
				int z = 1;
				result->push_back(getPoint(x,y,z));

			}
			int y = -1;
			int z = 0;
			result->push_back(getPoint(x,y,z));
		}
		result->push_back(getPoint(2,0,0));
		/*vector<int> additional = *getPoint(3,4,6);
		for (int i = 0; i < 3; i++) 
		{
			for (int j = -1; j < 2; j+=2) 
			{
				result->push_back(getPoint(additional[i],j,0));
				result->push_back(getPoint(additional[i],0,j));
				result->push_back(getPoint(0,additional[i],j));
				result->push_back(getPoint(j,additional[i],0));
				result->push_back(getPoint(j,0,additional[i]));
				result->push_back(getPoint(0,j,additional[i]));
			}
		}*/
		int z = 3;
		for (int y = -2; y < 3; y++) 
		{
			for (int x = -2; x < 3; x++) 
			{
				if (x == 0 && y == 0) 
				{
					continue;
				}
				result->push_back(getPoint(x,y,z));
			}
		}
		z = 4;
		for (int y = -1; y < 2; y++) 
		{
			for (int x = -1; x < 2; x++) 
			{
				if (x == 0 && y == 0) 
				{
					continue;
				}
				result->push_back(getPoint(x,y,z));
			}
		}
		return result;
	}
	vector< int > * MathOperator::getPoint(int x, int y, int z)
	{
		vector< int > * point = new vector< int >();
		point->push_back(x);
		point->push_back(y);
		point->push_back(z);
		return point;
	}
}
