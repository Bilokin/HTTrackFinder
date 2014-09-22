#include "Line.hh"
#include <vector>
namespace HTransform 
{
	#ifndef _Track_hh
	#define _Track_hh
	class Track 
	{
	public:
		//
		//	Constructor & Destructor
		//
		Track ();
		virtual ~Track () {};
		//
		//	Methods
		//
		void AddLine(Line * line);
		bool CheckMatch(Line * line, float precision);
		int GetSize();
		int GetID() const;
		std::vector< float > * GetModules();
		const std::vector< float > * GetVector() const;
		//float GetTeta();
		//float GetPhi();
		const std::vector< Line * > * GetLines() const;
		const std::vector< int > * GetPadIDs() const;

	private:
		//
		//	Methods
		//
	
		//
		//	Data
		//
		std::vector< Line * > myLines;
		std::vector< int > myPadIDs;
		/* data */
	};
	#endif
} /* HTransform */
