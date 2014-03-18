#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <set>      // needed to support coordinate validation structure
using std::set;     // (see SequenceAction constructor)

#include "../include/Sequencing.h"
#include "../include/PMDCollections.h"
#include "../include/PMDUtils.h"

const char SequenceAction::TokenMoveStart[] = "[move]";
const char SequenceAction::TokenMoveEnd[] = "[/move]";
const char SequenceAction::TokenPause[] = "pause";
const char SequenceAction::TokenHome[] = "home";
const char SequenceAction::TokenRepeat[] = "repeat";
const char SequenceAction::TokenPark[] = "park";

//----------------------------------------------------------------------------
SequenceAction::
SequenceAction(unsigned int period) {
    this->actionType = Pause;
    this->period = period;
}

//----------------------------------------------------------------------------
SequenceAction::
SequenceAction(PMDAxisControl *axis) {
    this->actionType = Home;
    this->axis = axis;
}

//----------------------------------------------------------------------------
SequenceAction::
SequenceAction(Sequence *repeatSequence, 
             unsigned int repeatCount) {
    this->actionType = Repeat;
    this->repeatSequence = repeatSequence;
    this->repeatCount = repeatCount;
}

//----------------------------------------------------------------------------
SequenceAction::
SequenceAction(FILE *file, char *token) {

    // Instruction type is Move.
    actionType = Move;

    // Load default values for case where values don't occur during parse.
    period = 0;
    coordinated = false;

    const char TokenWaitPeriod[] = "waitPeriod";
    const char TokenCoordinated[] = "coordinated";
    const char TokenKinematics[] = "kinematics";

    unsigned int val;

    kinematics = NULL;

    // Define stucture for validating world-space coordinate values.
    // (Populated only when a valid kinematics set is identified from the file)
    typedef set<string> StringSet;
    StringSet validCoords;

    // Get direct access to the needed collections
    AxisCollection *axes = PMDAxes::Instance();

    // Prime token stream.
    bool tokenRecognized = true;
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,TokenWaitPeriod)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            period = val;
        } else if (!strcmp(token,TokenCoordinated)) {
            tokenRecognized = 
                PMDUtils::ReadBool(file,token,coordinated);
        } else if (!strcmp(token,TokenKinematics)) {
            PMDUtils::ReadToken(file,token);
            KinematicsCollection* kinematicsCollection = 
                KinematicSolutions::Instance();
            KinematicsCollection::iterator kit = kinematicsCollection->find(token);
            if (kit != kinematicsCollection->end()) {
                kinematics = kit->second;
                //Populate the world-coordinate validation structure
                char *coordList[] = {"X", "Y", "Z", "yaw", "pitch", "roll", "orbit", NULL};
                for (int i=0;coordList[i] != NULL;i++)
                    validCoords.insert(coordList[i]);
            } else
                tokenRecognized = false;

        } else if (kinematics != NULL) {
            // Must be reading world-space values.

            // Get dimension of world-space coordinate and verify it's authenticity
//            PMDUtils::ReadToken(file,token);
            StringSet::iterator it = validCoords.find(token);
            if (it != validCoords.end()) {
                double dval;
                if (it == validCoords.find("X") || 
                    it == validCoords.find("Y") || 
                    it == validCoords.find("Z"))
                    tokenRecognized = PMDUtils::ReadLength(file,token,dval);
                else
                    tokenRecognized = PMDUtils::ReadAngle(file,token,dval);
                if (tokenRecognized) coordinates[*it] = dval;
            } else
                tokenRecognized = false;

        } else {
            // Must be reading joint-space commands
            // Verify the authenticity of the axis by checking to see if it exists.
            AxisCollection::iterator axIt = axes->find(token);
            if (axIt != axes->end()) {

                // Store the goal position for this axis.
                double angle;
                char axisToken[40];
                strcpy_s(axisToken,token);
                tokenRecognized = axIt->second->ReadAngle(file,token,angle);
                if (tokenRecognized) coordinates[axisToken] = angle;

            } else
                tokenRecognized = false;
        }
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
SequenceAction::SequenceAction(PMDAxisControl *axis, bool parkIt) {
    actionType = Park;
    this->axis = axis;
    this->parkIt = parkIt;
}

//----------------------------------------------------------------------------
bool SequenceAction::
Execute() {
    bool status = true;

    // This has to be here instead of within the case statement because the 
    // compiler can't handle declaration of a variable within it.
    Coordinates::iterator coordIt;

    switch (actionType) {
    case Pause:
        PMDUtils::DoSleep(period);
        return true;
        break;
    case Move:
        

        // Is this move in joint space or world space?
        if (kinematics == NULL) {
            // Move is in joint space.
            // Build axis list from coordinates and do move.
            AxisCollection *axisCollection = PMDAxes::Instance();
            PMDUtils::AxisList axisList;
            for (coordIt = coordinates.begin();coordIt != coordinates.end(); coordIt++) {
                // Assume axis in coordinates collection is valid.
                PMDAxisControl *axis = (*axisCollection)[coordIt->first];
                PMDAxisControl::Profile profile;
                axis->GetProfile(profile);
                profile.pos = coordIt->second;
                axis->SetProfile(profile);
                axisList.push_back(axis);
            }

            // Coordinate the axes if desired
            if (coordinated) PMDUtils::Coordinate(axisList);

            // Execute the moves.
            return PMDUtils::Move(axisList,period);

        } else {
            // Move is in world space.
            // Get world-space coordinates into vector and do move.
            Kinematics::DoublesVector worldVector(8,0.0);
            for (coordIt = coordinates.begin();coordIt != coordinates.end(); coordIt++) {
            }

            // Coordinate the axes if desired
//            if (coordinated) PMDUtils::Coordinate(axisList);

            // Execute the moves.
//            return PMDUtils::Move(axisList,period);

        }

        break;
    case Repeat:
        if (repeatCount > 0) {
            for (unsigned int i = 0; i<repeatCount;i++) 
                status = status && repeatSequence->Execute();
            return status;
        } else {
            // Repeat forever or until an error occurs.
            while (status) {
                status = status && repeatSequence->Execute();
            }
            return status;
        }
        break;
    case Home:
        return axis->FindHome();
        break;
    case Park:
        if (parkIt) axis->Park();
        else axis->Unpark();
        return true;
        break;

    }
    return false;
}

const char Sequence::StartToken[] = "[sequence]";
const char Sequence::EndToken[] = "[/sequence]";

//----------------------------------------------------------------------------
Sequence::
Sequence(FILE *file, char *token) {

    bool tokenRecognized = true;
    unsigned int val;
    SequenceAction *action;

    // Get direct access to the needed collections
    AxisCollection *axes = PMDAxes::Instance();
    SequenceCollection *sequences = Sequences::Instance();

    // Prime token stream.
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,PMDUtils::TokenUniqueID)) {
            PMDUtils::ReadToken(file,token);
            strcpy_s(uniqueID,token);
        } else if (!strcmp(token,SequenceAction::TokenPause)) {
            // Get the pause duration and create the action.
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            action = new SequenceAction(val);
            sequence.push_back(action);
        } else if (!strcmp(token,SequenceAction::TokenHome)) {
            // Get the axis identifier, find it's 
            // reference and create the action.
            PMDUtils::ReadToken(file,token);
            AxisCollection::iterator axIt = axes->find(token);
            if (axIt != axes->end()) {
                action = new SequenceAction(axIt->second);
                sequence.push_back(action);
            }
        } else if (!strcmp(token,SequenceAction::TokenRepeat)) {
            // Get the sequence identifier, find it's 
            // reference and create the action.
            PMDUtils::ReadToken(file,token);
            Sequence *repeatSequence = (*sequences)[token];
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            if (repeatSequence != NULL) {
                action = new SequenceAction(repeatSequence,val);
                sequence.push_back(action);
            }
        } else if (!strcmp(token,SequenceAction::TokenMoveStart)) {
            action = new SequenceAction(file,token);
            if (!strcmp(token,SequenceAction::TokenMoveEnd))
                sequence.push_back(action);
            else tokenRecognized = false;
        } else if (!strcmp(token,SequenceAction::TokenPark)) {
            // Get the axis identifier, find it's 
            // reference and create the action.
            PMDUtils::ReadToken(file,token);
            PMDAxisControl *axis = (*axes)[token];
            if (axis != NULL) {
                bool parkIt;
                if (PMDUtils::ReadBool(file,token,parkIt)) {
                    action = new SequenceAction(axis,parkIt);
                    sequence.push_back(action);
                }
            }
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
bool Sequence::
Execute() {
    bool lastActionExecutedSuccessfully = true;

    // Execute each action in order.
    SequenceList::iterator action;
    for (action = sequence.begin(); 
         action != sequence.end() && lastActionExecutedSuccessfully; 
         action++)
        lastActionExecutedSuccessfully = (*action)->Execute();
    
    return lastActionExecutedSuccessfully;
}

