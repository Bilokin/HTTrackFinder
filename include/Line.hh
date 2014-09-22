#include <vector>
#include <cmath>
#include "Pad.hh" 
#ifndef _Line_hh
#define _Line_hh
namespace HTransform 
{
	class Line 
	{
	public:
		static const float PRECISION;
		//
		//	Constructor & Destructor
		//
		Line (const std::vector< int > * point, std::vector< float > * lineVector, float hough, int id);
		virtual ~Line () {};
		//
		//	Methods
		//
		const std::vector< int > * GetPoint() const;
		const std::vector< float > * GetVector() const;
		int GetID() const;
		void AddPadID(int padID);
		int GetPadID() const;
		bool EqualTo(const Line & another, float precision);
		//std::vector<float> GetHoughParameters();
		float GetModuleHough() const;
		const std::vector<float> & GetParameters() const;
	private:
		//
		//	Methods
		//
	
		//
		//	Data
		//
		int myID;
		int myPadID;
		std::vector<float> myParameters;
		const std::vector< int > * myPoint;
		std::vector< float > * myVector;

		/* data */
	};
} /* HTransform */
#endif
