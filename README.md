# CWBOpenDataClient

[![Version](http://cocoapod-badges.herokuapp.com/v/CWBOpenDataClient/badge.png)](http://cocoadocs.org/docsets/CWBOpenDataClient)
[![Platform](http://cocoapod-badges.herokuapp.com/p/CWBOpenDataClient/badge.png)](http://cocoadocs.org/docsets/CWBOpenDataClient)

CWBOpenDataClient is an iOS library which helps to access forecasts
and various open data provided by
[Central Weather Bureau](http://www.cwb.gov.tw) (中央氣象局).

The class provides several caterories, and each category contains
methods to help fetching data asynchronously. CWBOpenDataClient uses
Bolts framework to do these asynchronous tasks, so you will get a
BFTask object after calling any method, and you can then provide a
callack block by calling `continueWithBlock:`.

To know more about Bolts framework and the idea about "Promises",
please visit [Bolts' webpage](https://github.com/BoltsFramework/Bolts-iOS).

For furthur information about CWB's open data, please visit
<http://opendata.cwb.gov.tw>.

## Usage

To run the example project; clone the repo, and run `pod install` from
the Project directory first.

## Requirements

CWBOpenDataClient depends on NSURLSession, thus, it required iOS 7 or
above.

## Installation

CWBOpenDataClient is available through
[CocoaPods](http://cocoapods.org), to install it simply add the
following line to your Podfile:

    pod "CWBOpenDataClient"

## Author

Weizhong Yang, a.k.a zonble. <zonble@gmail.com>

## License

CWBOpenDataClient is available under the MIT license. See the LICENSE
file for more info.
