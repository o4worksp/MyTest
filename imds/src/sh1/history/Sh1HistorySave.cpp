/*
 * Sh1HistorySave.cpp
 *
 *  Created on: 2016年10月25日
 *      Author: user
 */

#include "Sh1HistoryQuotHandle.h"
#include "../../public/stream/FileStream.h"
#include "../../public/protocolfactory/ProtocolFactory.h"
#include "../../public/messagereader/MessageReader.h"
#include "../../public/program/Profile.h"

int main(int argc, char* argv[])
{
	Profile* pf=Profile::Instance("sh1transfer");

	char rawdata_path[256];
	memset(rawdata_path, 0, 256);
	char his_path[256];
	memset(his_path, 0, 256);
	char template_path[256];
	memset(template_path, 0, 256);
	int mode = 0;
	char securityType[256];
	memset(securityType, 0, 256);
	char msgType[256];
	memset(msgType, 0, 256);
	char upstream[256];
	memset(upstream, 0, 256);
	const char* v = NULL;

	if (argc == 1) {
		v = pf->getEnv("sh1_data_path");
		if (v == NULL) {
			ERROR("sh1_data_path not found");
			exit(1);
		}
		strcpy(rawdata_path, v);

		v = pf->getEnv("sh1_his_path");
		if (v == NULL) {
			ERROR("sh1_his_path not found");
			exit(1);
		}
		strcpy(his_path, v);
	}
	else if (argc == 2) {
		strcpy(rawdata_path, argv[1]);

		v = pf->getEnv("sh1_his_path");
		if (v == NULL) {
			ERROR("sh1_his_path not found");
			exit(1);
		}
		strcpy(his_path, v);
	}
	else if (argc == 3) {
		strcpy(rawdata_path, argv[1]);
		strcpy(his_path, argv[2]);
	}
	else {
		ERROR("usage: ./Sh1HistorySave <raw_data_path> <his_file_path>");
		exit(1);
	}

	v = pf->getEnv("sh1_template_path");
	if (v == NULL) {
		ERROR("sh1_template_path not found");
		exit(1);
	}
	strcpy(template_path, v);

	v = pf->getEnv("sh1_mode");
	if (v == NULL) {
		ERROR("sh1_mode not found");
		exit(1);
	}
	mode = atoi(v);

	v = pf->getEnv("sh1_msg_type");
	if (v == NULL) {
		ERROR("sh1_msg_type not found");
		exit(1);
	}
	strcpy(msgType, v);

	v = pf->getEnv("sh1_security_type");
	if (v == NULL) {
		ERROR("sh1_security_type not found");
		exit(1);
	}
	strcpy(securityType, v);

	v = pf->getEnv("sh1_upstream_type");
	if (v == NULL) {
		ERROR("sh1_upstream_type not found");
		exit(1);
	}
	strcpy(upstream, v);

	//get the date
	string strRawPath(rawdata_path);
	int pos1 = strRawPath.rfind('_');
	int pos2 = strRawPath.rfind('.');
	if (pos1 == string::npos || pos2 == string::npos) {
		ERROR("The rawdata is not correct!");
		return -1;
	}
	string strDate = strRawPath.substr(pos1 + 1, pos2 - pos1 -1);
	uint32_t date = atoi(strDate.c_str());

	IDataHandle* sh1History = new Sh1HistoryQuotHandle(his_path, date);
	if (sh1History == NULL) {
		ERROR("create object failed!");
		return -1;
	}

	IStream *stream = new FileStream(rawdata_path);
	if (stream == NULL) {
		ERROR("create object failed!");
		return -1;
	}

	ProtocolFactory* pFactory = new ProtocolFactory();
	if (pFactory == NULL)
	{
		ERROR("create protocol factory failed!");
		return -1;
	}
	PROTOCOL_CONFIG config;
	config.mode = mode;
	config.msgType = msgType;
	config.securityType = securityType;
	config.templateName = template_path;
	config.upstream = upstream;

	IProtocol* protocol = pFactory->createProtocol(&config);
	if (protocol == NULL)
	{
		ERROR("create protocol failed");
		return -1;
	}

	MessageReader msgReader;
	while (msgReader.read(protocol, stream)) {
		sh1History->handle(msgReader.getMessage());
	}

	return 0;
}


