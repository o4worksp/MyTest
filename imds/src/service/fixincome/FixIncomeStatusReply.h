/*
 * FixIncomeStatusReply.h
 *
 *  Created on: Nov 4, 2015
 *      Author: level2
 */

#ifndef FIXINCOMESTATUSREPLY_H_
#define FIXINCOMESTATUSREPLY_H_

#include "../../public/reply/StatusReply.h"

class FixIncomeStatusReply: public StatusReply {
public:
	FixIncomeStatusReply();
	virtual ~FixIncomeStatusReply();
	virtual int request(const char* script,const char* query,char* buffer,int& len);
protected:
	virtual int getSnapString(char* buffer,const char* select);
};

#endif /* FIXINCOMESTATUSREPLY_H_ */
