/*
 * SimpleConvexHull.h
 *
 *  Created on: 2014-02-23
 *      Author: sam
 */


#ifndef QUICK_CONVEXHULL_H_
#define QUICK_CONVEXHULL_H_
#include "ConvexHull.h"
#include "PointSet.h"
#include "mtl/Sort.h"
#include "cevans/quickhull3D.h"
using namespace Minisat;

template<unsigned int D,class T=double>
class QuickConvexHull:public ConvexHull<D,T>{

	PointSet<D,T> & pointSet;
	ConvexPolygon<D,T> hull;
public:
	QuickConvexHull(PointSet<D,T> & p):pointSet(p){

	}

	void update();

	T getArea();

	ConvexPolygon<D> & getHull(){
		update();
		return hull;
	}

};
template<>
void QuickConvexHull<1,double>::update();
template<>
void QuickConvexHull<2,double>::update();
template<>
void QuickConvexHull<3,double>::update();

template<>
double QuickConvexHull<2,double>::getArea();
#endif