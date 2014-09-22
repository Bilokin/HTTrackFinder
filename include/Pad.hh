#ifndef _Pad_hh
#define _Pad_hh
#include <vector>
#include <Line.hh>
namespace HTransform 
{
	class Pad 
	{
	public:
		//
		//	Constructor & Destructor
		//
		Pad (int x, int y, int z, int id);

		virtual ~Pad () { delete myLines; };
		//
		//	Methods
		//
		const std::vector<int> & GetCoordinates() const;
		int GetCoordinate(int axis);
		float GetEnergy() const;
		int GetID() const;
		void Dim();
		void SetEnergy(float energy);
		void SetIsShowerPad(bool value);
		void SetLines(std::vector< Line * > * lines);
		void AddLine(Line * line);
		const std::vector<Line * > * GetLines() const;
		const std::vector< Pad * > * GetNeighbours() const;
		bool IsActive() const;
		void AddNeighbours(std::vector< Pad * > * array );
	private:
		//
		//	Methods
		//
	
		//
		//	Data
		//
		int myID;
		std::vector<int> myCoordinates;
		std::vector<Line * > * myLines;
		float myEnergy;
	  	bool isShowerPad;
		std::vector< Pad * > * neighbours;
		/* data */
	};
} /* HTransform */
#endif
