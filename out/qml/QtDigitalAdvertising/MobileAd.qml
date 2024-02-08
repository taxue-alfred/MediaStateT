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
import QtQuick 2.2
import QtDigitalAdvertising 1.1
import QtMultimedia 5.4

/*!
\qmltype QtDigitalAdvertising
\inherits Item
\inqmlmodule QtDigitalAdvertising
\brief Advertisement item designed for mobile applications.

The Qt Digital Advertising module offers easy to include advertisement content in your application.
To use this module in your Qt Quick application, add the following import statement to your QML file

\code
    import QtDigitalAdvertising 1.1
\endcode

The advertisement requested from a media server are based on the set up properties. Bare-minimum plugin properties set-up:

\code
 MobileAd{
    anchors.fill:  parent

    playMode: QtDigitalAdvertising.AutoPlay
    displayMode: QtDigitalAdvertising.Singleshot

    pageId: "1515277"
    formatId: "104693"
}
\endcode

\section2 Advertisement play modes
According to \c displayMode an advertisement could be diplayed in two modes: \c SingleShot or \c Loop .

Triggering play of the advertisement is based on \c playMode property. It could be \c AutoPlay, \c OnRequest or \c

Examples:
Plugin playing advertisements in a loop automatically after item creation:
\code
displayMode: QtDigitalAdvertising.Loop
playMode: QtDigitalAdvertising.AutoPlay
\endcode

Plugin playing advertisements only once when user request it programmatically via play() method:
\code
displayMode: QtDigitalAdvertising.SingleShot
playMode: QtDigitalAdvertising.OnRequest
\endcode

Plugin playing advertisements in a loop when idle state is detected:
\code
displayMode: QtDigitalAdvertising.Loop
playMode: QtDigitalAdvertising.OnIdle
inactivityTime: 2000
\endcode

\section2 Error handling
In case incorrect of missing advertisement request \c AdvRequestFailed signal will be emitted.
This allows user to i.e. hide the advertisement placeholder.
*/
Item {
    id: root

    /*!
    \qmlsignal void QtDigitalAdvertising::adRequested

    This signal is emitted when the advertisement was requested.
    */

    signal adRequested

    /*!
    \qmlsignal void QtDigitalAdvertising::adStarted

    This signal is emitted when the advertisement started to play.
    */
    signal adStarted

    /*!
    \qmlsignal void QtDigitalAdvertising::adEnded

    This signal is emitted when the advertisement ends.
    */
    signal adEnded

    /*!
    \qmlsignal void QtDigitalAdvertising::adClicked

    This signal is emitted when the advertisement was clicked.
    */
    signal adClicked

    /*!
    \enum AdError

    This enum is used to communicate errors. Below are the types of errors that could occur

    \list
        \li \c ApiKeyError - Error is received when an incorrect API Key is used.
        \li \c ApiParamsError - Error is received if wrong parameters are sent.
        \li \c PluginError - Generic error related to connectivity issues.
        \li \c NoAdAvailable - This communicates that there are no ads available at this moment.

    \endlist

    \code
    Connections{
        target: root
        function onAdError(){
            if(error===root.AdError.ApiKeyError){
                //Handle ApiKeyError
            }else if(root.AdError.ApiParamsError){
                //Handle ApiParamsError
            }else if(root.AdError.PluginError){
                //Handle PluginError
            }else if(root.AdError.NoAdAvailable){
                //Handle NoAdAvailable
            }
        }
    }
    \endcode
    */
    enum AdError{
        ApiKeyError,
        ApiParamsError,
        PluginError,
        NoAdAvailable
    }

    /*!
    \qmlsignal void QtDigitalAdvertising::adError

    This signal is emitted when ad request parameters are missing or incorrect.
    */
    signal adError(string error)

    /*!
    \qmlsignal void QtDigitalAdvertising::idleState

    This signal is emitted when ad request parameters are missing or incorrect.
    */
    signal idleState(bool isActive)

    /*!
    \include includes/play_mode.qdocincl
    */
    property alias playMode: mobileAdBackend.playMode

    /*!
    \qmlproperty int QtDigitalAdvertising::adBackgroundColor

    [Dektop banner only] This property indicated the background color of the ad
    */
    property alias adBackgroundColor: mobileAdBackend.adBackgroundColor

    /*!
    \include includes/inactivity_time.qdocincl
    */
    property alias inactivityTime: mobileAdBackend.inactivityTime

    /*!
    \include includes/display_mode.qdocincl
    */
    property alias displayMode: mobileAdBackend.displayMode

    /*!
    \qmlproperty int QtDigitalAdvertising::pageId

    This property holds pageId Id
    */
    property alias pageId: mobileAdBackend.pageId

    /*!
    \qmlproperty int QtDigitalAdvertising::formatId

    This property holds format Id which indicates exact width and height
    */
    property alias formatId: mobileAdBackend.formatId

    /*!
    \qmlmethod QtDigitalAdvertising::play()
     Triggers playing advertisements if plugin not displaying advs currently.
    */
    function play() {
        mobileAdBackend.play()
    }

    /*!
    \qmlmethod QtDigitalAdvertising::stop()
     Stops displaying advertisements and all jobs in related.
     Also triggers expiration procedure for all requested advertisements
    */
    function stop() {
        mobileAdBackend.stop()
    }

    QMobileAd {
        id: mobileAdBackend

        Connections {
            target: mobileAdBackend
            function onAdRequested() {root.adRequested()}
            function onAdStarted() {root.adStarted()}
            function onAdEnded() {root.adEnded()}
            function onAdClicked() {root.adClicked()}
            function onAdError(error) {root.adError(error)}
        }
    }
}
