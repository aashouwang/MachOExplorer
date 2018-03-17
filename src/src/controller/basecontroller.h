//
//  Created by everettjf
//  Copyright © 2017 everettjf. All rights reserved.
//
#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <libmoex/moex.h>
#include <libmoex/moex-view.h>
#include "stable.h"
#include "windowshareddata.h"

class BaseController : public WindowSharedData
{
public:
    BaseController();

    void log(const QString & log);
};

#endif // BASECONTROLLER_H
