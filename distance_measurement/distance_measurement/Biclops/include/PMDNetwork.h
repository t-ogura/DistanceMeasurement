#if !defined PMDNETWORK_H
#define PMDNETWORK_H

#include <map>              // data structure used to hold collections
#include <string>           // key data type for collection
using namespace std;        // MSVC++6 needs this to compile

#include "PortableSerial.h" 
class PMDController;
class Compass;

class PMDNetwork {
public:

    // Define start/stop tokens for configuration file parsing.
    static const char StartToken[];
    static const char StopToken[];

    char uniqueID[50];

    // Type definitions of collections contained in a network.
    typedef map<string,PMDController*> ControllerCollection;
    typedef map<string,Compass*> CompassCollection;

    PMDNetwork(const char *uniqueID, PortableSerial *comm);
    PMDNetwork(FILE *file, char *token); // Constructor using configuration file.
	virtual ~PMDNetwork();

    // Accessors
    PortableSerial *GetSerial() {return comm;};
    bool AddController(char *str, PMDController* controller);
    bool AddCompass(char *str, Compass* compass);
    bool OnlyOneDeviceIsOnNetwork();
    ControllerCollection *GetControllerCollection() {return controllers;};
    CompassCollection *GetCompassCollection() {return compasses;};

private:

    // The implementation of this network
    PortableSerial *comm;

    // The collection of attached controllers.
    ControllerCollection *controllers;
    CompassCollection *compasses;

    void ReadConfig(FILE *file, char *token);
};

#endif
