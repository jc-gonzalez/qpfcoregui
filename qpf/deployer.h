/******************************************************************************
 * File:    deployer.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.QPF.Deployer
 *
 * Version:  1.1
 *
 * Date:    2015/07/01
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015,2016 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Declare Deployer class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   CommNode
 *
 * Files read / modified:
 *   none
 *
 * History:
 *   See <Changelog>
 *
 * About: License Conditions
 *   See <License>
 *
 ******************************************************************************/

#ifndef DEPLOYER_H
#define DEPLOYER_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   - map
//   - vector
//   - fstream
//------------------------------------------------------------

#include <iostream>
#include <atomic>

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

//------------------------------------------------------------
// Topic: Project headers
//   none
//------------------------------------------------------------

#include "evtmng.h"
#include "datamng.h"
#include "logmng.h"
#include "taskmng.h"
#include "taskagent.h"
#include "taskorc.h"
#include "config.h"
#include "tools.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
namespace QPF {

//==========================================================================
// Class: Deployer
//==========================================================================
class Deployer {

public:

    //----------------------------------------------------------------------
    // Constructor: Deployer
    //----------------------------------------------------------------------
    Deployer(int argc, char *argv[]);

    //----------------------------------------------------------------------
    // Destructor: ~Deployer
    //----------------------------------------------------------------------
    ~Deployer();

    //----------------------------------------------------------------------
    // Method: run
    // Minimal working example
    // The elements are launched and wait for the start from the
    // Event Manager.
    // Then the systems starts the normal operational cycle.
    // Current version of Event Manager takes external events from
    // the HMI (simulated external events)
    //----------------------------------------------------------------------
    int run();

    //----------------------------------------------------------------------
    // Method: mustLaunchHMI
    // Returns true if the application must launch the HMI
    //----------------------------------------------------------------------
    bool mustLaunchHMI();

    //----------------------------------------------------------------------
    // Method: getConfigFileName
    // Returns the name of the configuration file name used
    //----------------------------------------------------------------------
    char * getConfigFileName();

    //----------------------------------------------------------------------
    // Method: getConfigHandler
    // Returns the configuration handler
    //----------------------------------------------------------------------
    Configuration * getConfigHandler();

    //----------------------------------------------------------------------
    // Method: actionOnSigInt
    // Actions to be performed when capturing SigInt
    //----------------------------------------------------------------------
    void actionOnSigInt();

private:

    //----------------------------------------------------------------------
    // Method: processCmdLineOpts
    // Processes command line options to configure execution
    //----------------------------------------------------------------------
    bool processCmdLineOpts(int argc, char * argv[]);

    //----------------------------------------------------------------------
    // Method: prepareSystem
    // Prepares environment and do initial checks
    //----------------------------------------------------------------------
    void prepareSystem();

    //----------------------------------------------------------------------
    // Function: launchQPFHMI
    // Launches (fork) HMI as a separate process
    //----------------------------------------------------------------------
    pid_t launchQPFHMI();

    //----------------------------------------------------------------------
    // Function: readConfig
    // Reads configuration file
    //----------------------------------------------------------------------
    void readConfig(const char * configFile = 0);

    //----------------------------------------------------------------------
    // Function: launchPeerNodes
    // Launches the different nodes execution, either by creating a new
    // thread or by spawning a new process
    //----------------------------------------------------------------------
    void launchPeerNodes();

    //----------------------------------------------------------------------
    // Function: start
    // Starts the entire system execution
    //----------------------------------------------------------------------
    void start();

    //----------------------------------------------------------------------
    // Function: cleanUp
    // Removes any remaining children
    //----------------------------------------------------------------------
    void cleanUp();

    //----------------------------------------------------------------------
    // Function: fexists
    // Checks that a file exists
    //----------------------------------------------------------------------
    bool fexists(const char * name);

    //----------------------------------------------------------------------
    // Function: waitingForGoAhead
    // Returns true if the "Go ahead" message (existence of a given file)
    // is received
    //----------------------------------------------------------------------
    bool waitingForGoAhead();

    //----------------------------------------------------------------------
    // Function: removeOldFiles
    // Removes old log and msg files
    //----------------------------------------------------------------------
    void removeOldFiles();

    //----------------------------------------------------------------------
    // Method: existsDir
    // Removes old log and msg files
    //----------------------------------------------------------------------
    bool existsDir(std::string pathName);

    //----------------------------------------------------------------------
    // Method: installSignalHandlers
    // Install signal handlers
    //----------------------------------------------------------------------
    void installSignalHandlers();

private:

    //----------------------------------------------------------------------
    // Flags: Execution options
    //   spawnPeerProcesses - Used to create the components as processes
    //                        instead of threads
    //   waitingForSignalToGo - Control flag to start execution
    //   verboseOutput - Controls if log messages are dumped to console
    //----------------------------------------------------------------------
    bool        spawnPeerProcesses;
    bool        waitingForSignalToGo;
    bool        verboseOutput;

    //----------------------------------------------------------------------
    // Variable: usec
    // Time lapse in microseconds from the launch of one component until the
    // launch of the next component
    //----------------------------------------------------------------------
    useconds_t  usec;

    //----------------------------------------------------------------------
    // Variable: usecStart
    // Time lapse in microseconds before generating the GO signal
    //----------------------------------------------------------------------
    useconds_t  usecStart;

    //----------------------------------------------------------------------
    // Variable: startImmediately
    // Flag to start only when an external source produces the GO event
    //----------------------------------------------------------------------
    bool startDetached;

    //----------------------------------------------------------------------
    // Variable: newConfigFile
    // Holds the file name of the configuration file where the new configuration
    // is stored (in case of reconfiguration, =-c newConfigFile= is used)
    //----------------------------------------------------------------------
    std::string newConfigFile;

    //----------------------------------------------------------------------
    // Variable: configFile
    // Constant pointer to the name of the config.file, or zero if config.
    // must be acquired from the central DB
    //----------------------------------------------------------------------
    const char * configFile;

    //----------------------------------------------------------------------
    // Variable: cfg
    // Configuration object (pointer)
    //----------------------------------------------------------------------
    Configuration * cfg;

    //----------------------------------------------------------------------
    // Variable: childrenPids
    // Vector with PIDs of deployer children commnodes
    //----------------------------------------------------------------------
    std::vector<pid_t> childrenPids;

    //----------------------------------------------------------------------
    // Variable: evtMng
    // Pointer to the CommNode for the Event Manager (main component)
    //----------------------------------------------------------------------
    EventManager * evtMng;

    //----------------------------------------------------------------------
    // Variable: hmiNeeded
    // Set to TRUE when the machine is the one hosting the HMI
    //----------------------------------------------------------------------
    bool hmiNeeded;

    //----------------------------------------------------------------------
    // Variable: deploymentCompleted
    // Set to TRUE when the deployment (launch of nodes) is finished
    //----------------------------------------------------------------------
    bool deploymentCompleted;

    //----------------------------------------------------------------------
    // Variable: sigIntHandler
    // Standard structure for signal handling
    //----------------------------------------------------------------------
    struct sigaction sigIntHandler;

};

}

#endif  /* DEPLOYER_H */
