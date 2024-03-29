/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtDigitalAdvertising module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
import QtQuick 2.0
import QtDigitalAdvertising 1.1

Item {
    /*!
    \qmlproperty string MobileConfig::qdaApiKey

    This property holds qdaApiKey
    */
    property alias qdaApiKey: mobileConfig.qdaApiKey

    /*!
    \qmlproperty string MobileConfig::dnt

    This property holds the dnt status
    */
    property alias dnt: mobileConfig.dnt

    /*!
    \qmlproperty string MobileConfig::networkId

    This property holds networkId
    */
    property alias networkId: mobileConfig.networkId

    /*!
    \qmlproperty string MobileConfig::siteId

    This property holds siteId
    */
    property alias siteId: mobileConfig.siteId

    /*!
    \qmlproperty string MobileConfig::appName

    This property holds appName
    */
    property alias appName: mobileConfig.appName

    /*!
    \qmlproperty string MobileConfig::bundleId

    This property holds bundleId
    */
    property alias bundleId: mobileConfig.bundleId

    /*!
    \qmlproperty string MobileConfig::adDomainUrl

    [Desktop only] This property holds the ad domain url
    */
    property alias adDomainUrl: mobileConfig.adDomainUrl

    /*!
    \qmlproperty string MobileConfig::showAdLoadingAnimation

    [Desktop only] This property indicates is the ad loading animation is present
    */
    property alias showAdLoadingAnimation: mobileConfig.showAdLoadingAnimation

    /*!
    \qmlproperty string EmbeddedConfig::windowsPreferredMultimediaPlugin

    This property indicates windows multimedia plugin will be used (https://doc.qt.io/qt-5/qtmultimedia-windows.html).
    Available options are: windowsmediafoundation and directshow
    windowsmediafoundation is set by default
    */
    property alias windowsPreferredMultimediaPlugin: mobileConfig.windowsPreferredMultimediaPlugin

    function requestTrackingAuthorization(){
        mobileConfig.requestTrackingAuthorization()
    }

    QMobileConfig{
        id: mobileConfig
    }
}
