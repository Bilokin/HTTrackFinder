#include "Calorimeter.hh"
namespace HTransform 
{
	Calorimeter::Calorimeter(int x, int y, int z)
	{
		myPositiveEnergyPads = new vector< Pad * >();
		myTrackPads = new vector< Pad * >();
		myShowerLimit = 6;
		myPadSystem = NULL;
		myDimensions.push_back(x);
		myDimensions.push_back(y);
		myDimensions.push_back(z);
	}
	void Calorimeter::AddPadSystem(vector< vector< vector< Pad *> > > * pads)
	{
		myPadSystem = pads;
		assertNeighboursSystem();
	}
	const Pad * Calorimeter::GetPad(int x, int y, int z) const
	{
		return getPad(x,y,z);
	}
	const vector< int > & Calorimeter::GetDimensions() const
	{
		return myDimensions;
	}
	const vector< Pad* > * Calorimeter::GetPads() const
	{
		return myPositiveEnergyPads;
	}
	const vector< Pad* > * Calorimeter::GetTrackPads() const
	{
		if (myTrackPads->size() == 0) 
		{
			setTrackPads();
		}
	        return myTrackPads;
	}

	const Pad * Calorimeter::GetPeakFromLayer(int z) const
	{
		float energy = 0.0;
		Pad * result = NULL;
		if (z < 0 || z > myDimensions[2]) 
		{
			return myPositiveEnergyPads->front();
		}
		for (int i = 0; i < myPositiveEnergyPads->size(); i++) 
		{
			Pad * pad = myPositiveEnergyPads->at(i);
			if (pad->GetCoordinates()[2] == z && pad->GetEnergy() >energy) 
			{
				result = pad;
				energy = pad->GetEnergy();
			}
		}
		if (result == NULL) 
		{
			return myPositiveEnergyPads->front();
		}
		return result;
	}

	void Calorimeter::DimAllPads()
	{
		for (int i = 0; i < myPositiveEnergyPads->size(); i++) 
		{
			myPositiveEnergyPads->at(i)->Dim();
		}
		myPositiveEnergyPads->clear();
		myTrackPads->clear();
	}

	void Calorimeter::LightThePad(int x, int y, int z, float energy)
	{
		Pad * pad = myPadSystem->at(x).at(y).at(z);
		if(pad->GetEnergy()==0.0) 
		{
			myPositiveEnergyPads->push_back(pad);
		}
		pad->SetEnergy(energy);
	}

	void Calorimeter::setTrackPads() const
	{
		for (int i = 0; i < myPositiveEnergyPads->size(); i++) 
		{
			Pad * pad = myPositiveEnergyPads->at(i);
			const vector< Pad * > * neighbours = pad->GetNeighbours();
			vector< Pad * > active;
			for (int j = 0; j < neighbours->size(); j++) 
			{
				if (neighbours->at(j)->GetEnergy() > 0.0) 
				{
					active.push_back(neighbours->at(j));
				}
			}
			if (active.size() > myShowerLimit) 
			{
				for (int j = 0; j < active.size(); j++) 
				{
					active[j]->SetIsShowerPad(true);
				}
			}
		}
		for (int i = 0; i < myPositiveEnergyPads->size(); i++) 
		{
			if (myPositiveEnergyPads->at(i)->IsActive()) 
			{
				myTrackPads->push_back(myPositiveEnergyPads->at(i));
			}
		}
	}

	void Calorimeter::assertNeighboursPadsTo(int x, int y, int z)
	{
		int count = 0;
		//vector< vector< vector< Pad * > >  > * neighbours = new vector< vector< vector< Pad *> >  >();
		vector< Pad * > * neighbours = new vector< Pad * >();
		Pad * targetPad = getPad(x,y,z);
		for (int k = ZNEIGHBOURS; k < 1-ZNEIGHBOURS; k++)
		{
			//vector< vector< Pad  *> > vv;
			for (int i = XNEIGHBOURS; i < 1-XNEIGHBOURS; i++)
			{
				//vector< Pad *> v;
				for (int j = YNEIGHBOURS; j < 1-YNEIGHBOURS; j++)
				{
					//std::cout << "Pad #" << x+i << '.'<< y+j << '.' << z+k << ": " << HasPad(x+i,y+j,z+k) << '\n';
					//if (HasPad(x+i,y+j,z+k))
					//{
					Pad * neighbour = getPad(x+i,y+j,z+k);
					if (neighbour) 
					{
						count++;
						neighbours->push_back(neighbour);
					}
					//}
				}
				//vv.push_back(v);
			}
			//neighbours->push_back(vv);
		};
		//std::cout << count << " neighbours asserted;\n";
		targetPad->AddNeighbours(neighbours);
	}
	void Calorimeter::assertNeighboursSystem()
	{
		for (int i = 0; i < myDimensions[0]; i++)
		{
			for (int j = 0; j < myDimensions[1]; j++)
			{
				for (int k = 0; k < myDimensions[2]; k++)
				{
					assertNeighboursPadsTo(i,j,k);
				}
			}
		}
	}	
	Pad * Calorimeter::getPad(int x, int y, int z) const
	{
	        if ((x>=0 && x < myDimensions[0]) && (y>=0 && y < myDimensions[1]) && (z>=0 && z < myDimensions[2])) 
	        {
	        	return myPadSystem->at(x).at(y).at(z);
	        }
		return NULL;
	}
} /* HTransform */
