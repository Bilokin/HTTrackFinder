#include "HTTrackFinder.hh"

#ifdef __CINT__
#pragma link C++ class vector<vector<int> >+;
#endif
using std::cout;
using std::vector;
using std::string;
using std::endl;
using HTransform::Pad;
using HTransform::Track;
using HTransform::PadBuilder;
using HTransform::Calorimeter;
using HTransform::CalorimeterBuilder;
using HTransform::TransformOperator;
using HTransform::Line;
namespace CALICE 
{
	HTTrackFinder a_HTTrackFinder_instance;
	
	HTTrackFinder::HTTrackFinder() : Processor("HTTrackFinder")
	{
		myBuilder = NULL;
		myECal = NULL;
	}
	void HTTrackFinder::init()
	{
		//cout << "init!!!\n";
		registerInputCollection( LCIO::CALORIMETERHIT,
		     "CalorimeterHitCollection",
		     "Name of the Calorimeter hit collection",
		      _colName,
		      std::string("ConvCalorimeterHits") ) ;
		_colName = "ECALConvCalorimeterHits";
		string _hfilename = "HoughTransform.root";
		hfile = new TFile( _hfilename.c_str(), "RECREATE", _hfilename.c_str() ) ;
		_Tree = new TTree( "HoughTransform", "Hough tree!" );
		_Tree->Branch("nlines", &_nlines, "nlines/I");
		_Tree->Branch("solid", _solid,"solid[nlines]/F");
		_Tree->Branch("module", _module,"module[nlines]/F");
		_Tree->Branch("nhits", &_nhits, "nhits/I");
		_Tree->Branch("posx", _posx,"posx[nhits]/I");
		_Tree->Branch("posy", _posy,"posy[nhits]/I");
		_Tree->Branch("posz", _posz,"posz[nhits]/I");
		_Tree->Branch("nspads", &_nspads, "nspads/I");
		_Tree->Branch("sposx", _posx2,"sposx[nspads]/I");
		_Tree->Branch("sposy", _posy2,"sposy[nspads]/I");
		_Tree->Branch("sposz", _posz2,"sposz[nspads]/I");
		_Tree->Branch("ntracks", &_ntracks, "ntracks/I");
		_Tree->Branch("tracks", _tracks, "tracks[ntracks][100]");
		_Tree->Branch("energy", _energyHit, "energy[nhits]/F");

		_eventNumber = 0;	
		_granularity = 8;
		myBuilder = new CalorimeterBuilder(_granularity);
		myECal = myBuilder->Build(18,18,30);
	}
	void HTTrackFinder::processRunHeader( LCRunHeader* run)
	{
	}
	void HTTrackFinder::processEvent( LCEvent * evtP )
	{
		if(evtP)
		{
			try
			{
				float energy = 0.0;
				int count = 0;

				LCCollection* col_hits = evtP->getCollection( _colName ) ;
				CellIDDecoder<CalorimeterHit> cd(col_hits);
				int numberOfHits = col_hits->getNumberOfElements();
				int IsInteraction = col_hits->parameters().getIntVal("isInteraction");
				int InteractionZ = col_hits->parameters().getIntVal("InteractionLayer");
				if (!IsInteraction) 
				{
					return;
				}
				cout << "Event #" << _eventNumber++ << '\n';
				for ( int hit_i = 0 ; hit_i < numberOfHits ; hit_i++ )
				{
				        vector< float > v;
					CalorimeterHit *aHit = dynamic_cast<CalorimeterHit*>( col_hits->getElementAt( hit_i ));
					int waferx = cd(aHit)["S-1"];
					int wafery = cd(aHit)["M"]-1;
					int padx = cd(aHit)["I"]-1;
					int pady = cd(aHit)["J"]-1;
					myECal->LightThePad(waferx * 6 + padx,wafery * 6 + pady, cd(aHit)["K-1"], aHit->getEnergy());
				}
				TransformOperator opera;
				cout << "IsInteraction: " << IsInteraction << ", InteractionZ: " << InteractionZ << '\n';
				//const Pad * intPad = myECal->GetPeakFromLayer(InteractionZ);
				opera.Process(myECal->GetTrackPads(), NULL);
				
				//vector< Track * > * tracks = opera.GetTracks();
				//_ntracks = tracks->size();
				//cout << "Number of tracks: " << _ntracks << '\n';
				/*for (int i = 0; i < _ntracks; i++) 
				{
					//int arr[100];
					for (int j = 0; j < tracks->at(i)->GetSize(); j++) 
					{
						_tracks[i][j] = (int)tracks->at(i)->GetPadIDs()->at(j);
					}
					//_tracks[i] = arr;
				}*/
				vector<float> * angles = opera.GetSolidAngles();
				vector<float> * hmodules = opera.GetHoughModules();
				_nlines = angles->size();
				std::cout << "Lines: " << _nlines << '\n';
				for (int i = 0; i < angles->size(); i++) 
				{
					_solid[i] = angles->at(i);
					_module[i] = hmodules->at(i);
				}
				writeCalorimeter(numberOfHits);
				_Tree->Fill();
				std::cout << "HERE222!\n";
				myECal->DimAllPads();
				/*for (int i = 0; i < _ntracks; i++) 
				{
					for (int j = 0; j < 70; j++) 
					{
						_tracks[i][j] = 0;
					}
				}*/
				delete angles;
				delete hmodules;
			}
			catch(lcio::DataNotAvailableException e)
			{
			        std::cout << "Error occurred!\n";
			}
		}
	}

	void HTTrackFinder::writeCalorimeter(int numberOfHits)
	{
		_nhits = numberOfHits;
		const vector< Pad * > * padsToWrite = myECal->GetPads();
		for (int i = 0; i < numberOfHits; i++)
		{
		        Pad * pad = padsToWrite->at(i);
			vector< int > points = pad->GetCoordinates();
			_energyHit[i] = pad->GetEnergy();
			_posx[i] = points.at(0);
			_posy[i] = points.at(1);
			_posz[i] = points.at(2);
		}
		const vector< Pad * > * pads = myECal->GetTrackPads();
		_nspads = pads->size();
		for (int i = 0; i < _nspads; i++) 
		{
			Pad * pad = pads->at(i);
			vector< int > points = pad->GetCoordinates();
			_posx2[i] = points.at(0);
			_posy2[i] = points.at(1);
			_posz2[i] = points.at(2);
		}
	}

	void HTTrackFinder::end()
	{
		hfile->cd();
		hfile->Write();
		hfile->Close();
	}
} /* CALICE */
