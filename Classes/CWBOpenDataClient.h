#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>
#import <Bolts/Bolts.h>
#import <KissXML/DDXML.h>

extern NSString *const CWBOpenDataClientErrorDomain;

/*!
 CWBOpenDataClient is a library which helps to access forecasts and
 various open data provided by Central Weather Bureau.

 The class provides several caterories, and each category contains
 methods to help fetching data asynchronously. CWBOpenDataClient uses
 Bolts framework to do these asynchronous tasks, so you will get a
 BFTask object after calling any method, and you can then provide a
 callack block by calling `continueWithBlock:`.

 To know more about Bolts framework and the idea of "Promises", please
 visit Bolts' webpage <https://github.com/BoltsFramework/Bolts-iOS>.

 For furthur information, please visit <http://opendata.cwb.gov.tw>.
*/

@interface CWBOpenDataClient : AFHTTPSessionManager
/*! The singleton object. */
+ (instancetype)sharedClient;
@end

/*! An alias to [CWBOpenDataClient sharedClient]. */
CWBOpenDataClient *CWBSharedClient();

/*! The category helps to fetch forecasts from CWB. Results for all
    tasks returned from the methods contained in the catetory are XML
    documents. */
@interface CWBOpenDataClient (Forecasts)
/*! Fetches the forecast for all areas in Taiwan within 36 hours
    (今明 36 小時天氣預報). */
- (BFTask *)get36HoursForecastAsync;
/*! Fetches the forecast for all areas in Taiwan within 7 days
    (七天天氣預報). */
- (BFTask *)get7DaysForecastAsync;
/*! Fetches the forecast for all areas in Taiwan for this week
    (一週縣市天氣預報). */
- (BFTask *)getWeekForecastAsync;
/*! Fetches the forecast for all major cities around the world.
    (全球都市天氣預報). */
- (BFTask *)getGlablCitiesForecastAsync;

// 海面天氣預報
- (BFTask *)getCoastalWatersForecastAsync;
// 波浪預報模式資料-台灣海域預報資料
- (BFTask *)getWaveForecastAsync;
// 未來1個月潮汐預報
- (BFTask *)getMonthlyTidePredictionAsync;

@end

/*! The category helps to fetch weather tips for each are in Taiwan
    from CWB. Results for all tasks returned from the methods
    contained in the catetory are XML documents. */
@interface CWBOpenDataClient (Tips)
/*! Fetchese the weather tips for Taipei City (台北市天氣小幫手). */
- (BFTask *)getTipsTaipeiCityAsync;
/*! Fetchese the weather tips for New Taipei City (新北市天氣小幫手). */
- (BFTask *)getTipsNewTaipeiCityAsync;
/*! Fetchese the weather tips for Keelung City (基隆市天氣小幫手). */
- (BFTask *)getTipsKeelungAsync;
/*! Fetchese the weather tips for Hualien County (花蓮縣天氣小幫手). */
- (BFTask *)getTipsHualienAsync;
/*! Fetchese the weather tips for Yilan County (宜蘭縣天氣小幫手). */
- (BFTask *)getTipsYilanAsync;
/*! Fetchese the weather tips for Kinmen County (金門縣天氣小幫手). */
- (BFTask *)getTipsKinmenAsync;
/*! Fetchese the weather tips for Penghu County (澎湖縣天氣小幫手). */
- (BFTask *)getTipsPenghuAsync;
/*! Fetchese the weather tips for Tainan City (台南市天氣小幫手). */
- (BFTask *)getTipsTainanAsync;
/*! Fetchese the weather tips for Kaohsiung City (高雄市天氣小幫手). */
- (BFTask *)getTipsKaohsiungAsync;
/*! Fetchese the weather tips for Chiayi County (嘉義縣天氣小幫手). */
- (BFTask *)getTipsChiayiAsync;
/*! Fetchese the weather tips for Chiayi City (嘉義市天氣小幫手). */
- (BFTask *)getTipsChiayiCityAsync;
/*! Fetchese the weather tips for Miaoli County (苗栗縣天氣小幫手). */
- (BFTask *)getTipsMiaoliAsync;
/*! Fetchese the weather tips for Taichung County (台中市天氣小幫手). */
- (BFTask *)getTipsTaichungAsync;
/*! Fetchese the weather tips for Taoyuan County (桃園縣天氣小幫手). */
- (BFTask *)getTipsTaoyuanAsync;
/*! Fetchese the weather tips for Hsinchu County (新竹縣天氣小幫手). */
- (BFTask *)getTipsHsinchuAsync;
/*! Fetchese the weather tips for Hsinchu City (新竹市天氣小幫手). */
- (BFTask *)getTipsHsinchuCityAsync;
/*! Fetchese the weather tips for Pingtung County (屏東縣天氣小幫手). */
- (BFTask *)getTipsPingtungAsync;
/*! Fetchese the weather tips for Nantou County (南投縣天氣小幫手). */
- (BFTask *)getTipsNantouAsync;
/*! Fetchese the weather tips for Taitung County (台東縣天氣小幫手). */
- (BFTask *)getTipsTaitungAsync;
/*! Fetchese the weather tips for Changhua County (彰化縣天氣小幫手). */
- (BFTask *)getTipsChanghuaAsync;
/*! Fetchese the weather tips for Yunlin County (雲林縣天氣小幫手). */
- (BFTask *)getTipsYunlinAsync;
/*! Fetchese the weather tips for Lienchiang County (連江縣天氣小幫手). */
- (BFTask *)getTipsLienchiangAsync;
@end

/*! The category helps to fetch satellite images.  */
@interface CWBOpenDataClient (ForecastImages)
/*! 中文彩色合成地面天氣圖 */
- (BFTask *)getGroundWeatherJpegImageMetadataAsync;
- (BFTask *)getGroundWeatherJpegImageAsync;

/*! 最新天氣圖 */
- (BFTask *)getNewestWeatherPDFDocumentMetadataAsync;

/*! 中文彩色合成24小時預測天氣圖 */
- (BFTask *)get24HoursWeatherJpegImageMetadataAsync;
- (BFTask *)get24HoursWeatherJpegImageAsync;

/*! 一週天氣預測圖 */
- (BFTask *)getWeeklyWeatherJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex; // 0-7
- (BFTask *)getWeeklyWeatherJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex; // 0-7

/*! 滿潮預報影像圖 1-7 */
- (BFTask *)getWeeklyTidePredictionJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex; // 1-7
- (BFTask *)getWeeklyTidePredictionJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex; // 1-7

/*! 中文定量降水預報圖(I) */
- (BFTask *)getPrecipitationAmount1JpegImageMetadataAsync;
- (BFTask *)getPrecipitationAmount1JpegImageAsync;
/*! 中文定量降水預報圖(II) */
- (BFTask *)getPrecipitationAmount2JpegImageMetadataAsync;
- (BFTask *)getPrecipitationAmount2JpegImageAsync;
@end



