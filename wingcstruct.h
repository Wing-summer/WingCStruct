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

#ifndef WINGCSTRUCT_H
#define WINGCSTRUCT_H

#include "iwingplugin.h"

class WingCStruct final : public WingHex::IWingPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.wingsummer.iwingplugin" FILE "WingCStruct.json")
    Q_INTERFACES(WingHex::IWingPlugin)

public:
    explicit WingCStruct();
    virtual ~WingCStruct();

public:
    virtual int sdkVersion() const override;
    virtual const QString signature() const override;
    virtual bool init(const std::unique_ptr<QSettings> &set) override;
    virtual void unload(std::unique_ptr<QSettings> &set) override;
    virtual const QString pluginName() const override;
    virtual const QString pluginAuthor() const override;
    virtual uint pluginVersion() const override;
    virtual const QString pluginComment() const override;

private:
    // Your private member
};

#endif // WINGCSTRUCT_H
