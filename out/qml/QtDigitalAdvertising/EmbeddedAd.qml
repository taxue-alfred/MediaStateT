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
import QtMultimedia 5.4
import QtDigitalAdvertising 1.1

/*!
\qmltype QtDigitalAdvertising
\inherits Item
\inqmlmodule QtDigitalAdvertising
\brief Advertisement item designed for embedded applications.

The Qt Digital Advertising module offers easy to include advertisement content in your application.
To use this module in your Qt Quick application, add the following import statement to your QML file

\code
    import QtDigitalAdvertising 1.1
\endcode

The advertisement requested from a media server are based on the set up properties. Bare-minimum plugin properties set-up:

\code
EmbeddedAd {
    anchors.centerIn:  parent

    width: 1920
    height: 1080
    playMode: QtDigitalAdvertising.AutoPlay
    displayMode: QtDigitalAdvertising.Loop
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


\section2 Advertisement size
The size of the advertisement is based on the exact width and height of the the plugin:
\code
width: 1920
height: 1080
\endcode

It can be requested with the different size than the plugin size by setting \c mediaWidth and \c mediaHeight parameters.

\code
mediaWidth: 1920
mediaHeight: 1080
\endcode

In this case the advertisement content will be adjusted to the \c width and \c height of the placeholder.

\note If your placeholder dimensions are different than advertisement size then you are obligated to specify \c mediaWidth and \c mediaHeight.
In this case, the advertisement will be scaled to fit your placeholder. Otherwise, it could lead to not receiving the media from the media server.

\section2 Error handling
In case incorrect of missing advertisement request \c onAdvRequestFailed signal will be emitted.
In case when there is no qualifying ad to be returned based on your campaign targeting parameters, no ad will be displayed and \c AdvNoAvailable signal will be emitted.
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
    \qmlproperty string QtDigitalAdvertising::currentMediaType

    This property holds the current handled media type information. By default it is set to
    \c Invalid.

    \table
    \header
    \li Value
    \li Description
    \row
    \li \c Image
    \li The advertisement content is an image.
    \row
    \li \c Video
    \li The advertisement content is a video.
    \row
    \li \c HTML
    \li The advertisement is an HTML page or flash application.
    \endtable
    */
    property alias currentMediaType: embeddedAdBackend.currentMediaType

    /*!
    \include includes/play_mode.qdocincl
    */
    property alias playMode: embeddedAdBackend.playMode

    /*!
    \include includes/inactivity_time.qdocincl
    */
    property alias inactivityTime: embeddedAdBackend.inactivityTime

    /*!
    \include includes/display_mode.qdocincl
    */
    property alias displayMode: embeddedAdBackend.displayMode

    /*!
       \qmlproperty int QtDigitalAdvertising::mediaWidth

       This property holds exact requested media width.
       This media width will be requested from media server.
       If not set up or 0, \c QtDigitalAdvertising::width will be requested.
       */
    property alias mediaWidth: embeddedAdBackend.mediaWidth


    /*!
    \qmlproperty int QtDigitalAdvertising::mediaHeight

    This property holds exact requested media height.
    This media height will be requested from media server.
    If not set up or 0, \c QtDigitalAdvertising::height will be requested.
    */
    property alias mediaHeight: embeddedAdBackend.mediaHeight


    /*!
    \qmlproperty string QtDigitalAdvertising::deviceId

    This property holds any string, including an empty string, as long as it is unique for each network_id.
    Set up property is REQUIRED to properly display the advertisements.
    */
    property alias deviceId: embeddedAdBackend.deviceId

    //    /*!
    //    \qmlproperty string QtDigitalAdvertising::displayTime

    //    This property holds time in the future at which you expect to show the ad in UTC epoch seconds.
    //    Set up property is REQUIRED to properly display the advertisements.
    //    */
    //    property alias displayTime: backend.displayTime

    /*!
    \qmlproperty string QtDigitalAdvertising::displayAreaId

    This property holds the id, it is important in the context of a request with multiple display areas, as each returned advertisement will have a display_area_id corresponding to the display area ID you requested.
    Set up property is REQUIRED to properly display the advertisements.
    */
    property alias displayAreaId: embeddedAdBackend.displayAreaId

    /*!
    \qmlproperty int QtDigitalAdvertising::minDuration

    This property holds minimum acceptable asset duration, in seconds.
    Set up property is OPTIONAL but it is RECOMMENDED to properly display the advertisements.
    */
    property alias minDuration: embeddedAdBackend.minDuration

    /*!
    \qmlproperty int QtDigitalAdvertising::maxDuration

    This property holds maximum acceptable asset duration, in seconds.
    Set up property is OPTIONAL but it is RECOMMENDED to properly display the advertisements.
    */
    property alias maxDuration: embeddedAdBackend.maxDuration

    /*!
    \qmlproperty int QtDigitalAdvertising::staticDuration

    This property holds supported duration (in seconds) for static creatives. All static assets will be returned with the duration set to this value.
    Set up property is OPTIONAL but it is RECOMMENDED to properly display the advertisements.
    */
    property alias staticDuration: embeddedAdBackend.staticDuration

    /*!
    \qmlproperty bool QtDigitalAdvertising::allowAudio

    This property holds information indicates whether the audio is allowed.
    By default, it is set to \c false.
    Set up property is OPTIONAL.
    */
    property alias allowAudio: embeddedAdBackend.allowAudio

    /*!
    \qmlproperty string QtDigitalAdvertising::orderId

    This property holds specifying the contract number of an order in this field will only return advertisements for that order.
    Set up property is OPTIONAL.
   */
    property alias orderId: embeddedAdBackend.orderId

    /*!
    \qmlproperty int QtDigitalAdvertising::maxFileSizeBytes

    This property holds maximum file size (in bytes) that is supported by the device.
    Set up property is OPTIONAL.
    */
    property alias maxFileSizeBytes: embeddedAdBackend.maxFileSizeBytes

    /*!
    \qmlproperty double QtDigitalAdvertising::latitude

    This property holds degrees north.
    Set up property is OPTIONAL.
    */
    property alias latitude: embeddedAdBackend.latitude

    /*!
    \qmlproperty double QtDigitalAdvertising::longitude

    This property holds degrees east.
    Set up property is OPTIONAL.
    */
    property alias longitude: embeddedAdBackend.longitude

    /*!
    \qmlproperty double QtDigitalAdvertising::lastImpressions

    This property holds the last impression value reached from server
    */
    property alias lastImpressions: embeddedAdBackend.lastImpressions

    /*!
    \qmlproperty double QtDigitalAdvertising::lastMediaCost

    This property holds the last media cost value reached from server.
    The unit is nano dollar.
    */
    property alias lastMediaCost: embeddedAdBackend.lastMediaCost

    /*!
    \qmlproperty string QtDigitalAdvertising::supportedImageFormats

    This property holds audio formats that are requested from media server. Media formates need to be coma separated.
    By default, it is set to \c"".

    The following are the possible values:

    \table
    \header
    \li Value
    \row
    \li \c jpeg
    \row
    \li \c png
    \endtable
    */
    property alias supportedImageFormats: embeddedAdBackend.supportedImageFormats

    /*!
    \qmlproperty string QtDigitalAdvertising::supportedVideoFormats

    This property holds video formats that are requested from media server. Media formates need to be coma separated.
    By default, it is set to \c"".

    The following are the possible values:

    \table
    \header
    \li Value
    \row
    \li \c mp4
    \row
    \li \c mpeg
    \row
    \li \c mpg
    \row
    \li \c quicktime
    \row
    \li \c webm
    \row
    \li \c x_flvx_flv
    \row
    \li \c x_ms_wmv
    \row
    \li \c x_msvideo
    \endtable
    */
    property alias supportedVideoFormats: embeddedAdBackend.supportedVideoFormats

    /*!
    \qmlproperty string QtDigitalAdvertising::adPropertiesId

    This property indicates which ad properties to load from the file.
    For more information please visit the \l{Configure Advertisements} section.
    */
    property alias adPropertiesId: embeddedAdBackend.adPropertiesId

    /*!
    \qmlmethod QtDigitalAdvertising::play()
     Triggers playing advertisements if plugin not displaying advs currently.
    */
    function play() {
        embeddedAdBackend.play()
    }

    /*!
    \qmlmethod QtDigitalAdvertising::stop()
     Stops displaying advertisements and all jobs in related.
     Also triggers expiration procedure for all requested advertisements
    */
    function stop() {
        embeddedAdBackend.stop()
    }

    QEmbeddedAd {
        id: embeddedAdBackend

        Connections {
            target: embeddedAdBackend
            function onAdRequested() {root.adRequested()}
            function onAdStarted() {root.adStarted()}
            function onAdEnded() {root.adEnded()}
            function onAdClicked() {root.adClicked()}
            function onAdError(error) {root.adError(error)}
        }
    }
}
