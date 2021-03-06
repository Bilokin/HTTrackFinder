#ifndef _MathOperator_hh_
#define _MathOperator_hh_
#include <stdlib.h>
#include <cmath>
#include <vector>
namespace HTransform 
{
	class MathOperator 
	{
		public:
		//
		//	Constants
		//
	
		//
		//	Constructors
		//
			MathOperator ();
			virtual ~MathOperator ();
		//
		//	Methods
		//
			static float getModule(const std::vector< int > & v);
			static float getModule(const std::vector< float > & v);

			static bool approximatelyEqual(const double * start1, const double * end);
			static float getDistance(const double * start, const double * end);
			static std::vector< float > * vectorProduct(const std::vector< float > & v1,const std::vector< float > & v2);
			
			static float getDistanceTo(const std::vector< int > & vectorPoint1,const std::vector< float > & vector1, const std::vector< int > * pointOfLine );
			static float getDistanceTo(const double * vectorPoint1, std::vector< float > & vector1,const double * pointOfLine );
			
			static std::vector< float > getDirection(std::vector< int > & vectorPoint1, std::vector< int > & vectorPoint2);
			static std::vector< float > getDirection(const double * vectorPoint1, const double * vectorPoint2);
			
			static std::vector< std::vector< int > * > * GetMagicNumbers();
			static std::vector< int > * getPoint(int x, int y, int z);
		private:
		//
		//	Data
		//
			/* data */
		//
		//	Private methods
		//
			static double * castIntToDouble(int * array);
	};
}
#endif
