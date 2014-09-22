#include "Track.hh"
using std::vector;
namespace HTransform 
{
	Track:: Track(){}

	void Track::AddLine(Line * line)
	{
		myLines.push_back(line);
		myPadIDs.push_back(line->GetPadID());
	}
	bool Track::CheckMatch(Line * line, float precision)
	{
		if (myLines.size() == 0) 
		{
			return true;
		}
		return myLines.front()->EqualTo(*line, precision);
	}
	int Track::GetSize()
	{
		return myLines.size();
	}
	const std::vector< float > * Track::GetVector() const
	{
		return myLines.front()->GetVector();
	}
	int Track::GetID() const
	{
		return myLines.front()->GetID();
	}
	/*float Track::GetTeta()
	{
		return myLines.front()->GetParameters()[1];
	}
	float Track::GetPhi()
	{
		return myLines.front()->GetParameters()[0];
	}*/
	vector< float > * Track::GetModules()
	{
		vector<float> * result = new vector<float>();
		for (int i = 0; i < myLines.size(); i++) 
		{
			result->push_back(myLines[i]->GetParameters()[0]);
		}
		return result;
	}
	const vector< Line * > * Track::GetLines() const
	{
		return &myLines;
	}
	const vector< int > * Track::GetPadIDs() const
	{
		return &myPadIDs;
	}

} /* HTransform */
