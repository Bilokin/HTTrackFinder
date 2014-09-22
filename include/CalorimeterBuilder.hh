#include "PadBuilder.hh"
#include "Calorimeter.hh"
#ifndef _CalorimeterBuilder_hh
#define _CalorimeterBuilder_hh
namespace HTransform 
{
	class CalorimeterBuilder 
	{
	public:
		//
		//	Constructor & Destructor
		//
		CalorimeterBuilder (int granularity);
		virtual ~CalorimeterBuilder () { delete myBuilder; };
		//
		//	Methods
		//
		Calorimeter * Build(int x_pads, int y_pads, int z_pads);
	private:
		//
		//	Methods
		//
	
		//
		//	Data
		//
		PadBuilder * myBuilder;
		static int myPadNumber;
		/* data */
	};
} /* HTransform */
#endif
