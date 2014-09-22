#include "Pad.hh"
#include "MathOperator.hh"
#include <vector>
#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES
#ifndef _PadBuilder_hh
#define _PadBuilder_hh
namespace HTransform 
{
	class PadBuilder 
	{
	public:
		
		//
		//	Constructor & Destructor
		//
		PadBuilder (int granularity);
		virtual ~PadBuilder () {};
		//
		//	Methods
		//
		Pad * Build(int x, int y, int z, int id);
	private:
		//
		//	Methods
		//
		void insertLines(Pad & pad);
		Line * build(Pad & pad, std::vector< float > * magic, int id);
		//
		//	Data
		//
		int myGranularity;
		std::vector< std::vector< float > * > * myMagicVectors;
		std::vector< int > * null;
		/* data */
	};
} /* HTransform */
#endif
