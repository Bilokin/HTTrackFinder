#include "TransformOperator.hh"
#include <iostream>
using std::cout;
using std::vector;
namespace HTransform 
{
	TransformOperator:: TransformOperator()
	{
		myGroupesCutoff = 4;
		myPrecision = 0.1;
		myTracks = new vector< Track * >();
		myNonfilteredTracks = new vector< Track * >();
	}

	void TransformOperator::Process(const vector< Pad * > * pads, const Pad * interactionPad)
	{
		if (interactionPad) 
		{
			
			cout << "int ID: " <<  interactionPad->GetID() << '\n';
			for (int i = 0; i < interactionPad->GetLines()->size(); i++) 
			{
				Track * track = new Track();
				track->AddLine(interactionPad->GetLines()->at(i));
				myNonfilteredTracks->push_back(track);
			}
		}
		for (int i = 0; i < pads->size(); i++) 
		{
			const Pad * pad = pads->at(i);
			for (int j = 0; j < pad->GetLines()->size(); j++) 
			{
				Line * line = pad->GetLines()->at(j);
				addLineToTracks(line, !interactionPad);
			}
		}
		for (int i = 0; i < myNonfilteredTracks->size(); i++) 
		{
			if (filter(myNonfilteredTracks->at(i))) 
			{
				myTracks->push_back(myNonfilteredTracks->at(i));
			}
		}
	}
	bool TransformOperator::addLineToTracks(Line * line, bool add)
	{
		bool added = false;
		for (int i = 0; i < myNonfilteredTracks->size(); i++) 
		{
			Track * track = myNonfilteredTracks->at(i);
			if (track->CheckMatch(line, myPrecision)) 
			{
				track->AddLine(line);
				added = true;
				//break;
			}
		}
		if (!added && add)
		{
			Track * track = new Track();
			track->AddLine(line);
			myNonfilteredTracks->push_back(track);
		}
		return added;
	}
	

	vector<float> * TransformOperator::GetSolidAngles()
	{
		vector<float> * result = new vector<float>();
		int number = myTracks->size();
		for (int i = 0; i < number; i++) 
		{
			Track * track = myTracks->at(i);
			//if (filter(track)) 
			{
				int size = track->GetSize();
				float solid_angle = track->GetID();//track->GetVector()->at(0) + 10 * track->GetVector()->at(1) + 100*track->GetVector()->at(2);
				for (int j = 0; j < size; j++) 
				{
					result->push_back(solid_angle);
				}
			}
		}
		return result;
	}
	std::vector<float> * TransformOperator::GetHoughModules()
	{
		vector<float> * result = new vector<float>();
		//cout << "Modules:\n";
		int number = myTracks->size();
		for (int i = 0; i < number; i++)
		{
			Track * track = myTracks->at(i);
			//if (filter(track))
			{
			        int size = track->GetSize();
				vector< float > * modules = track->GetModules();
				for (int j = 0; j < size; j++) 
				{
				        result->push_back(modules->at(j));
					//cout << modules->at(j) << " , " << track->GetPhi()  <<  " , " << track->GetTeta() <<" : " << track->GetSize() << '\n';
				}
				//cout << '\n';
			}

		}
		return result;
	}
	vector< Track * > * TransformOperator::GetTracks()
	{
		vector< Track * > * result = new vector< Track * >();
		int number = myTracks->size();
		for (int i = 0; i < number; i++)
		{
		        Track * track = myTracks->at(i);
			//if (filter(track))
			{
				result->push_back(track);
			}
		}
		return result;
	}
	bool TransformOperator::filter(Track * track)
	{
		if (track->GetSize() < myGroupesCutoff) 
		{
			return false;
		}
		float weight = 0.0;
		const vector<int> * point = track->GetLines()->front()->GetPoint();
		const vector< float > * vec = track->GetLines()->front()->GetVector();
		int number = track->GetSize();
		for (int i = 0; i < number; i++) 
		{
			const vector<int> * another =  track->GetLines()->at(i)->GetPoint();
			float module =  MathOperator::getDistanceTo(*another,*vec,point);
			weight += module/number;
		}
		if (weight > 1.0) 
		{
			return false;
		}
		std::cout << "ID: " << track->GetID() << " Size: " << number << " Weight: " << weight << '\n';
		/*if (track->GetSize() < myGroupesCutoff * 2 && track->GetVector()->at(0) == 0.0 && track->GetVector()->at(1) == 0.0) 
		{
			return false;
		}*/
		return true;
	}
} /* HTransform */
