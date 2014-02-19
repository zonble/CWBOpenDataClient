#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>
#import <Bolts/Bolts.h>
#import <KissXML/DDXML.h>

/*! http://opendata.cwb.gov.tw */
@interface CWBOpenDataClient : AFHTTPSessionManager
+ (instancetype)sharedClient;
@end

/*! A alias to [CWBOpenDataClient sharedClient]. */
CWBOpenDataClient *CWBSharedClient();

@interface CWBOpenDataClient (Forecasts)
- (BFTask *)get36HoursForecastAsync; // 今明36小時天氣預報
- (BFTask *)get7DaysForecastAsync; // 七天天氣預報
- (BFTask *)getWeekForecastAsync; // 一週縣市天氣預報
- (BFTask *)getGlablCitiesForecastAsync; // 全球都市天氣預報
@end

@interface CWBOpenDataClient (Tips)
/*! Fetchese the weather tips for Taipei City (台北市天氣小幫手). The
    result of the task returns an XML document. */
- (BFTask *)getTipsTaipeiCityAsync;
/*! Fetchese the weather tips for New Taipei City (新北市天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsNewTaipeiCityAsync;
/*! Fetchese the weather tips for Keelung City (基隆市天氣小幫手). The
    result of the task returns an XML document. */
- (BFTask *)getTipsKeelungAsync;
/*! Fetchese the weather tips for Hualien County (花蓮縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsHualienAsync;
/*! Fetchese the weather tips for Yilan County (宜蘭縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsYilanAsync;
/*! Fetchese the weather tips for Kinmen County (金門縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsKinmenAsync;
/*! Fetchese the weather tips for Penghu County (澎湖縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsPenghuAsync;
/*! Fetchese the weather tips for Tainan City (台南市天氣小幫手). The
    result of the task returns an XML document. */
- (BFTask *)getTipsTainanAsync;
/*! Fetchese the weather tips for Kaohsiung City (高雄市天氣小幫手). The
    result of the task returns an XML document. */
- (BFTask *)getTipsKaohsiungAsync;
/*! Fetchese the weather tips for Chiayi County (嘉義縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsChiayiAsync;
/*! Fetchese the weather tips for Chiayi City (嘉義市天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsChiayiCityAsync;
/*! Fetchese the weather tips for Miaoli County (苗栗縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsMiaoliAsync;
/*! Fetchese the weather tips for Taichung County (台中市天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsTaichungAsync;
/*! Fetchese the weather tips for Taoyuan County (桃園縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsTaoyuanAsync;
/*! Fetchese the weather tips for Hsinchu County (新竹縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsHsinchuAsync;
/*! Fetchese the weather tips for Hsinchu City (新竹市天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsHsinchuCityAsync;
/*! Fetchese the weather tips for Pingtung County (屏東縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsPingtungAsync;
/*! Fetchese the weather tips for Nantou County (南投縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsNantouAsync;
/*! Fetchese the weather tips for Taitung County (台東縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsTaitungAsync;
/*! Fetchese the weather tips for Changhua County (彰化縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsChanghuaAsync;
/*! Fetchese the weather tips for Yunlin County (雲林縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsYunlinAsync;
/*! Fetchese the weather tips for Lienchiang County (連江縣天氣小幫手).
    The result of the task returns an XML document. */
- (BFTask *)getTipsLienchiangAsync;
@end

@interface CWBOpenDataClient (ForecastImages)
- (BFTask *)getGroundWeatherJpegImageMetadataAsync; // 中文彩色合成地面天氣圖
- (BFTask *)getGroundWeatherJpegImageAsync;
- (BFTask *)getNewestWeatherPDFDocumentMetadataAsync; // 最新天氣圖
- (BFTask *)get24HoursWeatherJpegImageMetadataAsync; // 中文彩色合成24小時預測天氣圖
- (BFTask *)get24HoursWeatherJpegImageAsync;
- (BFTask *)getWeeklyWeatherJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex; // 一週天氣預測圖 0-7
- (BFTask *)getWeeklyWeatherJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex;
@end
