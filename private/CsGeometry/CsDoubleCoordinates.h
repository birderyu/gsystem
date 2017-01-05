template<cs_size_t DIMENSION>
class CsDoubleCoordinates
{
public:
	enum { COORD_VALUE_SIZE = DIMENSION * 2, };

public:
	cs_real &FirstX();
	cs_real  FirstX() const;
	cs_real &FirstY();
	cs_real  FirstY() const;
	cs_real &FirstZ();
	cs_real  FirstZ() const;
	CsCoordinate FirstCoordinate() const;

	cs_real &SecondX();
	cs_real  SecondX() const;
	cs_real &SecondY();
	cs_real  SecondY() const;
	cs_real &SecondZ();
	cs_real  SecondZ() const;
	CsCoordinate SecondCoordinate() const;

	cs_void SetFirstX(cs_real x);
	cs_void SetFirstY(cs_real y);
	cs_void SetFirstZ(cs_real z);
	cs_void SetFirstCoordinate(const CsCoordinate &c);

	cs_void SetSecondX(cs_real x);
	cs_void SetSecondY(cs_real y);
	cs_void SetSecondZ(cs_real z);
	cs_void SetSecondCoordinate(const CsCoordinate &c);

private:
	cs_real m_aCoord[COORD_VALUE_SIZE];
};