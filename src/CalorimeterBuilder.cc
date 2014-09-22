#include "CalorimeterBuilder.hh"
namespace HTransform 
{
	int CalorimeterBuilder::myPadNumber = 0;
	CalorimeterBuilder :: CalorimeterBuilder(int granularity)
	{
		myBuilder = new PadBuilder(granularity);
	}

	Calorimeter * CalorimeterBuilder::Build(int x_pads, int y_pads, int z_pads)
	{
		if (x_pads < 1 || y_pads < 1 || z_pads < 1) 
		{
			return NULL;
		}
		Calorimeter * result = new Calorimeter(x_pads,y_pads,z_pads);
		vector< vector< vector< Pad *> >  > * vvv = new vector< vector< vector< Pad * > > >();
		for(int i = 0; i < x_pads; i++)
		{
		        vector< vector< Pad  *> > vv;
			for (int j = 0; j < y_pads; j++)
			{
			        vector< Pad *> v;
				for (int k = 0; k < z_pads; k++)
				{
				        int id = i*10000 + j*100 + k;
					Pad * pad = myBuilder->Build(i,j,k, id);
					v.push_back(pad);
					myPadNumber++;
				}
				vv.push_back(v);
			}
			vvv->push_back(vv);
		}

		result->AddPadSystem(vvv);
		return result;
	}
} /* HTransform */
