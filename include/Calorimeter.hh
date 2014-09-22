#include "Pad.hh"
#include <vector>
#ifndef _Calorimeter_hh
#define _Calorimeter_hh
using std::vector;
namespace HTransform 
{
	class Calorimeter 
	{
	public:
	  	static const int ZNEIGHBOURS=-1;
		static const int XNEIGHBOURS=-1;
		static const int YNEIGHBOURS=-1;
		//
		//	Constructor & Destructor
		//
		Calorimeter (int x, int y, int z);
		virtual ~Calorimeter () {};
		//
		//	Methods
		//
		void AddPadSystem(vector< vector< vector< Pad *> > > * pads);
		void LightThePad(int x, int y, int z, float energy);
		void DimAllPads();
		const Pad * GetPeakFromLayer(int z) const;
		const Pad * GetPad(int x, int y, int z) const;
		const vector< Pad* > * GetPads() const;
		const vector< Pad* > * GetTrackPads() const;
		const vector< int > & GetDimensions() const;
	private:
		//
		//	Methods
		//
	  	void assertNeighboursPadsTo(int x, int y, int z);
		void assertNeighboursSystem();
		Pad * getPad(int x, int y, int z) const;
		void setTrackPads() const;
		//
		//	Data
		//
		vector< Pad * > * myPositiveEnergyPads;
		vector< Pad * > * myTrackPads;
		vector< vector< vector< Pad * > > > * myPadSystem;
		vector< int > myDimensions;
		int myShowerLimit;
		/* data */
	};
} /* HTransform */
#endif
