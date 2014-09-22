#ifndef _HTTrackFinder_hh
#define _HTTrackFinder_hh
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <string>
#include <cstdlib>
#include <iostream>
#include <marlin/Processor.h>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include <EVENT/LCIO.h>
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/CalorimeterHit.h>
#include <IMPL/CalorimeterHitImpl.h>
#include <UTIL/CellIDDecoder.h>
#include "Track.hh"
#include "CalorimeterBuilder.hh"
#include "TransformOperator.hh"
namespace CALICE 
{
	class HTTrackFinder : public marlin::Processor 
	{
	public:
		//
		//	Constructor & Destructor
		//
		HTTrackFinder ();
		virtual ~HTTrackFinder () {};
		//
		//	Methods
		//
		Processor*  newProcessor() { return new HTTrackFinder(); }
		/** Called at the begin of the job before anything is read.
		 *  *  * Use to initialize the processor, e.g. book histograms.
		 *   *   */
		void init();
		/** Called for every run, e.g. overwrite to initialize run dependent 
		 *  *  *  histograms.
		 *   *   */
		void processRunHeader( LCRunHeader* run);

		/** Called for every event - the working horse. 
		 *  *  */
		void processEvent( LCEvent * evtP );

		//Called at the end of the job
		void end();

	private:
		//
		//	Methods
		//
		void writeCalorimeter(int n);
		//
		//	Data
		//
		int _granularity;
		std::string _colName;
		TFile * hfile;
		TTree* _Tree;
		static const int MAXN = 5000000;
		static const int MINN = 10000;
		int _ntracks;

		int _tracks[1000][70];	
		int _eventNumber;
		int _nlines;
		float _solid[MAXN];
		float _module[MAXN];
		int _nhits;
		int _posx[MINN];   // hit position x, in mm, 0 is the center of ECAL
		int _posy[MINN];   // hit position y, in mm, 0 is the center of ECAL
		int _posz[MINN];   // hit position z, in mm, starting at the frount of ECAL
		int _nspads;
		int _posx2[MINN];   // hit position x, in mm, 0 is the center of ECAL
		int _posy2[MINN];   // hit position y, in mm, 0 is the center of ECAL
		int _posz2[MINN];   // hit position z, in mm, starting at the frount of ECAL
		float _energyHit[MINN];

		HTransform::CalorimeterBuilder * myBuilder;
		HTransform::Calorimeter * myECal;
		/* data */
	};
} /* CALICE */
#endif
