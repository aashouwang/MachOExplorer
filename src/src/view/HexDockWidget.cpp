//
//  Created by everettjf
//  Copyright © 2017 everettjf. All rights reserved.
//
#include "HexDockWidget.h"


#include "src/utility/Utility.h"

HexDockWidget::HexDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle(tr("Hex"));

    hexEdit = new HexdumpWidget(this);
//    hexEdit->setMinimumWidth(528);

    setWidget(hexEdit);
}

void HexDockWidget::showViewData(moex::ViewData *data)
{
    moex::BinaryViewData *node = static_cast<moex::BinaryViewData*>(data);

    hexEdit->setAddressAs64Bit(true);
    hexEdit->loadAddress(node->start_value,(unsigned long long)node->offset,node->size);
    this->adjustSize();
}