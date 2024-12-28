/*==============================================================================
** Copyright (C) 2024-2027 WingSummer
**
** This program is free software: you can redistribute it and/or modify it under
** the terms of the GNU Affero General Public License as published by the Free
** Software Foundation, version 3.
**
** This program is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
** details.
**
** You should have received a copy of the GNU Affero General Public License
** along with this program. If not, see <https://www.gnu.org/licenses/>.
** =============================================================================
*/

#include "wingcstruct.h"

WingCStruct::WingCStruct() : WingHex::IWingPlugin() {}

WingCStruct::~WingCStruct() {}

int WingCStruct::sdkVersion() const { return WingHex::SDKVERSION; }

const QString WingCStruct::signature() const { return WingHex::WINGSUMMER; }

bool WingCStruct::init(const std::unique_ptr<QSettings> &set) {
    // Your codes there
    return true;
}

void WingCStruct::unload(std::unique_ptr<QSettings> &set) {
    // Your unloading codes here
}

const QString WingCStruct::pluginName() const { return tr("WingCStruct"); }

const QString WingCStruct::pluginAuthor() const { return WingHex::WINGSUMMER; }

uint WingCStruct::pluginVersion() const { return 1; }

const QString WingCStruct::pluginComment() const {
    return tr("Providing basic support for analyzing file structures%");
}
