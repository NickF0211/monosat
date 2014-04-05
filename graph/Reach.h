/*
 * Reach.h
 *
 *  Created on: 2013-07-26
 *      Author: sam
 */

#ifndef REACH_H_
#define REACH_H_

#include "mtl/Vec.h"

class Reach{
public:






	virtual ~Reach(){};

	virtual void setSource(int s)=0;
	virtual int getSource()=0;
	//virtual addSource(int s)=0;

	virtual void update( )=0;

	virtual bool connected_unsafe(int t)=0;
	virtual bool connected_unchecked(int t)=0;
	virtual bool connected( int t)=0;
	virtual int distance( int t)=0;
	virtual int distance_unsafe(int t)=0;

	virtual int previous( int t)=0;
};

#endif /* REACH_H_ */
