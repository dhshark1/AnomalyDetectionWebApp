//Tom Magdaci 316603604

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
	DefaultIO* dio;
	Command** cmdsArr;
	size_t cmdsArrSize;

    ClientData* c;
    // you can add data members
public:
    HybridAnomalyDetector* hAD;
	CLI(DefaultIO* dio);
    CLI(DefaultIO* dio, bool is_simple);
	void start();
	void setIO(DefaultIO* newDio);
	virtual ~CLI();
private:
    void helperCreateAndInsertCmdsToArr(bool is_simple);
    void helperCreateAndInsertCmdsToArr();
    string menuCreate();
};

#endif /* CLI_H_ */
