#ifndef JSONHANDLER_H
#define JSONHANDLER_H 

class jsonHandler {
public:
	jsonHandler() { };
	// the function module for processing JSON
	bool processJSON(const char* jsonFile);
};

#endif