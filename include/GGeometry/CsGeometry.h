/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	CsGeometry.h
** @brief	基础几何接口的定义
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _GEOMETRY_GEOMETRY_H_
#define _GEOMETRY_GEOMETRY_H_

#include "CsGeometryGlobal.h"
#include "GCore/gobject.h"

class CsGeometry;
class CsGeometryFactory;
class CsEnvelope;
class CsCoordinate;
class CsCoordinateSequence;
typedef GSharedPointer<CsGeometry> CsGeometryP;

/****************************************************************************
**
** CsGeometry.h
**
** @class		CsGeometry
** @brief		基础几何接口
** @module		CsCore
**
** 基础几何类型是所有几何对象接口的基类，采用要素模型的思想进行了一层接口封装。
**
****************************************************************************/
class GAPI CsGeometry 
	: public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_GEOMETRY, };

public:
	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	~CsGeometry
	** @brief	析构函数（destructor）
	**
	** 析构函数应该是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~CsGeometry() = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	GeometryFactory
	** @brief	获取当前几何对象的工厂
	** @return	{const CsGeometryFactory *} 几何工厂
	**
	****************************************************************************/
	virtual const CsGeometryFactory *GeometryFactory() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	Valid
	** @brief	当前实例是否有效
	** @return	{cs_bool} 有效则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Valid() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	GeometryType
	** @brief	获取当前对象的几何类型
	** @return	{cs_int} 几何类型，其值等于枚举 {CS_GEOMETRY_TYPE}
	** @see		{CS_GEOMETRY_TYPE}
	**
	****************************************************************************/
	virtual gint GeometryType() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	Dimension
	** @brief	获取当前对象的维度
	** @return	{cs_int} 维度，其值等于枚举 {CS_GEOMETRY_DIMENSION}
	** @see		{CS_GEOMETRY_DIMENSION}
	**
	****************************************************************************/
	virtual guint Dimension() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	Envelope
	** @brief	获取当前几何对象的外包
	** @return	{CsEnvelope} 外包
	** @see		{CsEnvelope}
	**
	****************************************************************************/
	virtual CsEnvelope Envelope() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	CoordinateSequence
	** @brief	获取当前几何对象的坐标序列
	** @return	{CsCoordinateSequence} 坐标序列
	** @see		{CsCoordinateSequence}
	**
	****************************************************************************/
	virtual CsCoordinateSequence CoordinateSequence() const = 0;
	
	//virtual cs_bool IsEmpty() const = 0;
	//virtual cs_bool IsSimple() const = 0;
	//virtual cs_bool Clear() = 0;
	//virtual CsGeometryP Flatten() const = 0; // 从三维变成二维

	//virtual cs_real Distance(const CsGeometry &geo) const = 0;
	//virtual cs_bool Touches(const CsGeometry &geo) const = 0;
	//virtual cs_bool Intersects(const CsGeometry &geo) const = 0;
	//virtual cs_bool Disjoint(const CsGeometry &geo) const = 0;
	//virtual cs_bool Crosses(const CsGeometry &geo) const = 0;
	//virtual cs_bool Within(const CsGeometry &geo) const = 0;
	//virtual cs_bool Contains(const CsGeometry &geo) const = 0;
	//virtual cs_bool Overlaps(const CsGeometry &geo) const = 0;
	//virtual cs_bool Covers(const CsGeometry &geo) const = 0;
	//virtual cs_bool CoveredBy(const CsGeometry &geo) const = 0;

	//virtual CsGeometryP Buffer() const = 0;
	//virtual CsGeometryP Intersection(const CsGeometry &geo) const = 0;
	//virtual CsGeometryP Union(const CsGeometry &geo) const = 0;
	//virtual CsGeometryP Difference(const CsGeometry &geo) const = 0;
};

#endif // _GEOMETRY_GEOMETRY_H_