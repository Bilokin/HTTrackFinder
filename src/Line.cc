#include <Line.hh>
using std::vector;
using std::sqrt;
namespace HTransform 
{
	 const float Line::PRECISION = 0.02;
	 Line::Line (const vector< int > * point, vector< float > * lineVector, float hough, int id)
	 {
		myPadID = 0;
		myID = id;
		myPoint = point;
		myVector = lineVector;
		myParameters.push_back(hough);
		/*for (int i = 0; i < 3; i++) 
		{
		        myParameters.push_back(lineVector->at(i));
		}*/
	 }
	 void Line::AddPadID(int pad)
	 {
	 	myPadID = pad;
	 }
	 int Line::GetPadID() const
	 {
	 	return myPadID;
	 }
	 int Line::GetID() const
	 {
	 	return myID;
	 }

	 bool Line::EqualTo(const Line & another, float precision)
	 {
	 	if (another.GetVector()->at(0) != myVector->at(0) || another.GetVector()->at(1) != myVector->at(1) || another.GetVector()->at(2) != myVector->at(2)  ) 
	 	{
	 		return false;
	 	}
		//float precision =  PRECISION;// + sin(myParameters[1]) *sin(myParameters[1])*0.1;
		if (another.GetParameters()[0] < myParameters[0] + precision && another.GetParameters()[0] > myParameters[0] - precision) 
		{
			return true;
		}
		return false;
	 }
	 const vector<float> & Line::GetParameters() const
	 {
	 	return myParameters;
	 }
	 const vector< int > * Line::GetPoint() const
	 {
		return myPoint;
	 }
	 const vector< float > * Line::GetVector() const
	 {
	 	return myVector;
	 }
	 float Line::GetModuleHough() const
	 {
	 	return myParameters[0];
	 }
} /* HTransform */
