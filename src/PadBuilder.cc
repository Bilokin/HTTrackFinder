#include "PadBuilder.hh"
using std::vector;
namespace HTransform 
{
	PadBuilder::PadBuilder (int granularity)
	{
		myGranularity = granularity;
		myMagicVectors = new vector< vector< float > * >();
		null = MathOperator::getPoint(0,0,0);
		vector< vector< int > * > * magic = MathOperator::GetMagicNumbers();
		for (int i = 0; i < magic->size(); i++) 
		{
			vector< int > * numbers = magic->at(i);
			vector< float > * lineVector = new vector<float>(MathOperator::getDirection(*numbers, *null));
			myMagicVectors->push_back(lineVector);
		}
	}

	Pad * PadBuilder::Build(int x, int y, int z, int id)
	{
		if (x < 0 || y < 0 || z < 0) 
		{
			return NULL;
		}
		Pad * result = new Pad(x,y,z, id);
		insertLines(*result);
		return result;
	}

	void PadBuilder::insertLines(Pad & pad)
	{
		vector<Line * > * lines = new vector< Line * >();
		//std::cout<< "Pad: " << pad.GetCoordinates()[0] << ' ' << pad.GetCoordinates()[1] << ' '<< pad.GetCoordinates()[2] << '\n';
		for (int i = 0; i < myMagicVectors->size(); i++) 
		{
			Line * line = build(pad, myMagicVectors->at(i), i);
			lines->push_back(line);
		}
		pad.SetLines(lines);
	}

	Line * PadBuilder::build(Pad & pad, vector< float > * magic, int id)
	{
		/*vector< int > null;
		vector< float > lineVector = MathOperator::getDirection(*magic, null);*/
		//std::cout<< "Magic: " << magic->at(0) << ' ' << magic->at(1) << ' ' << magic->at(2) << '\n';
		float hough = MathOperator::getDistanceTo(*null, *magic, &pad.GetCoordinates());
		//std::cout<< "Hough: " << hough << '\n';
		Line * result = new Line(&pad.GetCoordinates(), magic, hough, id);
		//std::cout<< "ID: " << pad.GetID() << '\n';
		result->AddPadID(pad.GetID());
		return result;
	}

} /* HTransform */
