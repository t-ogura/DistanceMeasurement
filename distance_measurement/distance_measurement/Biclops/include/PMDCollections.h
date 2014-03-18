#if !defined PMDCollections_H
#define PMDCollections_H

#include <map>              // data structure used to hold collections
using std::map;
#include <string>           // key data type for collection
using std::string;

#include "PMDNetwork.h"     // for collection of networks
#include "PMDController.h"  // for collection of controllers
#include "PMDAxisControl.h" // for collection of axes
#include "Sequencing.h"     // for collection of sequences
#include "Compass.h"        // for collection of compasses
#include "Kinematics.h"     // for collection of kinematic solutions
#include "singleton.h"      // to enforce single instance of each collection

// A collection of networks and the associated class to enforce singletonism.
//typedef map<string,PortableSerial*> NetworkCollection;
typedef map<string,PMDNetwork*> NetworkCollection;
class PMDNetworks: public CSingleton<NetworkCollection> {
    friend class CSingleton<NetworkCollection>;
 
private:
    PMDNetworks();
    ~PMDNetworks();
};

// A collection of controllers and the associated class to enforce singletonism.
typedef map<string,PMDController*> ControllerCollection;
class PMDControllers: public CSingleton<ControllerCollection> {
    friend class CSingleton<ControllerCollection>;
 
private:
    PMDControllers();
    ~PMDControllers();
};

// A collection of axes and the associated class to enforce singletonism.
typedef map<string,PMDAxisControl*> AxisCollection;
class PMDAxes: public CSingleton<AxisCollection> {
    friend class CSingleton<AxisCollection>;
 
private:
    PMDAxes();
    ~PMDAxes();
};

// A collection of sequences and the associated class to enforce singletonism.
typedef map<string,Sequence*> SequenceCollection;
class Sequences: public CSingleton<SequenceCollection> {
    friend class CSingleton<SequenceCollection>;
 
private:
    Sequences();
    ~Sequences();
};

// A collection of compasses and the associated class to enforce singletonism.
typedef map<string,Compass*> CompassCollection;
class Compasses: public CSingleton<CompassCollection> {
    friend class CSingleton<CompassCollection>;
 
private:
    Compasses();
    ~Compasses();
};

// A collection of the defined kinematic models available.
typedef map<string,Kinematics*> KinematicsCollection;
class KinematicSolutions: public CSingleton<KinematicsCollection> {
    friend class CSingleton<KinematicsCollection>;
 
private:
    KinematicSolutions();
    ~KinematicSolutions();
};


#endif

