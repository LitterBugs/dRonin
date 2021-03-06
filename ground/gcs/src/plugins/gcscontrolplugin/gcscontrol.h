/**
 ******************************************************************************
 * @file       gcscontrol.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2013
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup GCSControl
 * @{
 * @brief GCSReceiver API
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#ifndef GCSCONTROL_H
#define GCSCONTROL_H

#include <extensionsystem/iplugin.h>

#include "gcscontrol_global.h"
#include "manualcontrolsettings.h"
#include "uavobjects/uavobjectmanager.h"
#include "gcsreceiver.h"
#include "extensionsystem/pluginmanager.h"
#include "QTimer"
#include "gcscontrolgadgetfactory.h"

class GCSCONTROLSHARED_EXPORT GCSControl : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.dronin.plugins.GCSControlPlugin")
public:
    GCSControl();
    ~GCSControl();
    void extensionsInitialized();
    bool initialize(const QStringList &arguments, QString *errorString);
    void shutdown();

#if defined(USE_SDL)
    SDLGamepad *sdlGamepad;
#endif
public slots:
    bool beginGCSControl();
    bool endGCSControl();
    bool setFlightMode(ManualControlSettings::FlightModePositionOptions flightMode);
    bool setThrottle(float value);
    bool setRoll(float value);
    bool setPitch(float value);
    bool setYaw(float value);
    bool setChannel(quint8 channel, float value);

private:
    ManualControlSettings *manControlSettingsUAVO;
    GCSReceiver *m_gcsReceiver;
    static bool firstInstance;
    ManualControlSettings::DataFields dataBackup;
    ManualControlSettings::Metadata metaBackup;
    bool hasControl;
    QTimer receiverActivity;

    GCSControlGadgetFactory *mf;
private slots:
    void objectsUpdated(UAVObject *);
    void receiverActivitySlot();
};

#endif // GCSCONTROL_H
