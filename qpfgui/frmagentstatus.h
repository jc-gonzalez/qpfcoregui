/******************************************************************************
 * File:    frmagentstatus.h
 *          Declaration of class FrmAgentStatus
 *
 * Domain:  QPF.qpfgui.frmagentstatus
 *
 * Version:  1.1
 *
 * Date:    2016-11-03
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015,2016 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Declaration of class FrmAgentStatus
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   none
 *
 * Files read / modified:
 *   none
 *
 * History:
 *   See <ChangeLog>
 *
 * About: License Conditions
 *   See <License>
 *
 ******************************************************************************/

#ifndef FRMAGENTSTATUS_H
#define FRMAGENTSTATUS_H

#include <QFrame>
#include "datatypes.h"

namespace Ui {
class FrmAgentStatus;
}

namespace QPF {

class FrmAgentStatus : public QFrame
{
    Q_OBJECT

public:
    explicit FrmAgentStatus(QWidget *parent = 0);
    ~FrmAgentStatus();

    void updateInfo(TaskAgentInfo &d);

private:
    Ui::FrmAgentStatus *ui;
};

}

#endif // FRMAGENTSTATUS_H
