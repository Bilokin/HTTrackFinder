#include <Pad.hh>
using std::vector;
namespace HTransform 
{
	 Pad::Pad (int x, int y, int z, int id)
	 {
	 	neighbours = NULL;
		isShowerPad = false;
		myLines = NULL;
		myEnergy = 0.0;
		myID = id;
		myCoordinates.push_back(x);
		myCoordinates.push_back(y);
		myCoordinates.push_back(z);
	 }
	 const vector<int> & Pad::GetCoordinates() const
	 {
	 	return myCoordinates;
	 }
	 int Pad::GetCoordinate(int axis)
	 {
	 	return (axis > -1 && axis < 3) ? myCoordinates[axis] : 0;
	 }
	 float Pad::GetEnergy() const
	 {
	 	return myEnergy;
	 }

	int Pad::GetID() const
	{
		return myID;
	}

	 void Pad::SetEnergy(float energy)
	 {
	 	if (energy > 0.0) 
	 	{
	 		myEnergy = energy;
	 	}
	 }
	 void Pad::Dim()
	 {
	 	myEnergy = 0.0;
		isShowerPad = false;
	 }
	 void Pad::SetLines(vector< Line * > * lines)
	 {
	 	myLines = lines;
	 }
	 void Pad::SetIsShowerPad(bool value)
	 {
	 	isShowerPad = value;
	 }
	 const vector< Line * > * Pad::GetLines() const
	 {
	 	return myLines;
	 }
	 void Pad::AddLine(Line * line)
	 {
	 	if (myLines) 
	 	{
	 		myLines->push_back(line);
	 	}
		else 
		{
			myLines = new vector< Line * >();
			myLines->push_back(line);
		}
	 }
	const vector< Pad * > * Pad::GetNeighbours() const
	{
		return neighbours;
	}
	bool Pad::IsActive() const
	{
		return myEnergy > 0.0 && !isShowerPad;
	}
	void Pad::AddNeighbours(vector< Pad * > * array )
	{
		neighbours = array;
	}
} /* HTransform Pad (int x, int y, int z); */
