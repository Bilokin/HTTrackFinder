#include "Pad.hh"
#include "Track.hh"
#ifndef _TransformOperator_hh
#define _TransformOperator_hh
namespace HTransform 
{
	class TransformOperator 
	{
	public:
		//
		//	Constructor & Destructor
		//
		TransformOperator ();
		virtual ~TransformOperator () 
		{ 
			delete myTracks;
		};
		//
		//	Methods
		//
		void Process(const std::vector< Pad * > * pads, const Pad * interactionPad);
		std::vector<float> * GetSolidAngles();
		std::vector<float> * GetHoughModules();
		std::vector< Track * > * GetTracks();
	private:
		//
		//	Methods
		//
		bool addLineToTracks(Line * line, bool add);
		bool filter(Track * track);
		
		//
		//	Data
		//
		std::vector< Track * > * myTracks;
		int myGroupesCutoff;
		float myPrecision;
	};
} /* HTransform */
#endif
