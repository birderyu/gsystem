template<gsize DIMENSION>
class CsDoubleCoordinates
{
public:
	enum { COORD_VALUE_SIZE = DIMENSION * 2, };

public:
	greal &FirstX();
	greal  FirstX() const;
	greal &FirstY();
	greal  FirstY() const;
	greal &FirstZ();
	greal  FirstZ() const;
	CsCoordinate FirstCoordinate() const;

	greal &SecondX();
	greal  SecondX() const;
	greal &SecondY();
	greal  SecondY() const;
	greal &SecondZ();
	greal  SecondZ() const;
	CsCoordinate SecondCoordinate() const;

	gvoid SetFirstX(greal x);
	gvoid SetFirstY(greal y);
	gvoid SetFirstZ(greal z);
	gvoid SetFirstCoordinate(const CsCoordinate &c);

	gvoid SetSecondX(greal x);
	gvoid SetSecondY(greal y);
	gvoid SetSecondZ(greal z);
	gvoid SetSecondCoordinate(const CsCoordinate &c);

private:
	greal m_aCoord[COORD_VALUE_SIZE];
};