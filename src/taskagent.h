/******************************************************************************
 * File:    taskagent.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.TaskAgent
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
 *   Declare TaskAgent class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   Component
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

#ifndef TASKAGENT_H
#define TASKAGENT_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   - thread
//------------------------------------------------------------

#include <thread>
#include <mutex>

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   - component.h
//------------------------------------------------------------

#include "component.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
namespace QPF {

class ProcessingElement;

//==========================================================================
// Class: TaskAgent
//==========================================================================
class TaskAgent : public Component {

public:
    TaskAgent(const char * name = 0);

    Property(TaskAgent, std::string, workDir,    WorkDir);
    Property(TaskAgent, std::string, sysDir,     SysDir);
    Property(TaskAgent, bool,        remote,     Remote);
    Property(TaskAgent, std::string, agentAddress,  AgentAddress);
    Property(TaskAgent, std::string, masterAddress, MasterAddress);

    //----------------------------------------------------------------------
    // Method: sendTaskResMsg
    //----------------------------------------------------------------------
    bool sendTaskResMsg(TaskInfo & task);

    //----------------------------------------------------------------------
    // Method: checkProcessingElements
    // Check list of processing elements
    //----------------------------------------------------------------------
    void procElemFinished(ProcessingElement * p);

protected:

    //----------------------------------------------------------------------
    // Method: fromRunningToOperational
    //----------------------------------------------------------------------
    virtual void fromRunningToOperational();

    //----------------------------------------------------------------------
    // Method: fromRunningToOff
    //----------------------------------------------------------------------
    virtual void fromRunningToOff();

protected:

    //----------------------------------------------------------------------
    // Method: processTASK_PROC
    //----------------------------------------------------------------------
    virtual void processTASK_PROC();

    //----------------------------------------------------------------------
    // Method: processCMD
    //----------------------------------------------------------------------
    virtual void processCMD();

    //----------------------------------------------------------------------
    // Method: execAdditonalLoopTasks
    //----------------------------------------------------------------------
    virtual void execAdditonalLoopTasks();

private:

    //----------------------------------------------------------------------
    // Method: checkProcessingElements
    // Check list of processing elements
    //----------------------------------------------------------------------
    void checkProcessingElements();

    //----------------------------------------------------------------------
    // Method: sendMonitInfo
    //----------------------------------------------------------------------
    bool sendMonitInfo();

    //----------------------------------------------------------------------
    // Method: timeTag
    //----------------------------------------------------------------------
    std::string timeTag();

private:
    std::vector<std::thread *> procTasks;
    std::vector<ProcessingElement*> processingElements;
    std::vector<ProcessingElement*> finishedProcessingElements;

    std::atomic<bool> stopTasks;
    std::atomic<int> numTasks;
    std::atomic<int> numRunningTasks;
    std::atomic<int> numWaitingTasks;
    std::atomic<int> maxRunningTasks;
    std::mutex sendMsgsMutex;
};

}

#endif  /* TASKAGENT_H */
