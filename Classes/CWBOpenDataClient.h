#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>
#import <Bolts/Bolts.h>
#import <KissXML/DDXML.h>

extern NSString *const CWBOpenDataClientErrorDomain;

typedef enum {
	CWBAreaTaipeiCity = 0,
	CWBAreaNewTaipeiCity = 1,
	CWBAreaKeelung = 2,
	CWBAreaHualien = 3,
	CWBAreaYilan = 4,
	CWBAreaKinmen = 5,
	CWBAreaPenghu = 6,
	CWBAreaTainan = 7,
	CWBAreaKaohsiung = 8,
	CWBAreaChiayi = 9,
	CWBAreaChiayiCity = 10,
	CWBAreaMiaoli = 11,
	CWBAreaTaichung = 12,
	CWBAreaTaoyuan = 13,
	CWBAreaHsinchu = 14,
	CWBAreaHsinchuCity = 15,
	CWBAreaPingtung = 16,
	CWBAreaNantou = 17,
	CWBAreaTaitung = 18,
	CWBAreaChanghua = 19,
	CWBAreaYunlin = 20,
	CWBAreaLienchian = 21
} CWBArea;

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
+ (NSString *)version;
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
/*! Fetches the forecast for all major cities around the world
    (全球都市天氣預報). */
- (BFTask *)getGlablCitiesForecastAsync;

/*! Fetches coastal waters forecasts (海面天氣預報). */
- (BFTask *)getCoastalWatersForecastAsync;
/*! Fetches wave forecast (波浪預報模式資料-台灣海域預報資料) */
- (BFTask *)getWaveForecastAsync;
/*! Fetchese tide prediction for the next month (未來1個月潮汐預報). */
- (BFTask *)getMonthlyTidePredictionAsync;
/*! Fetchese tide prediction for the next year (明年高低潮時潮高預報). */
- (BFTask *)getNextYearTidePredictionAsync;
@end

/*! The category helps to fetch weather tips (天氣小幫手) for each are
    in Taiwan from CWB. */
@interface CWBOpenDataClient (Tips)
/*! Fetches weather tips (天氣小幫手). Results for the task returned
    from the method contained are XML documents.
    @param inArea the area code. */
- (BFTask *)getTipsAsyncForArea:(CWBArea)inArea;
@end

@interface CWBOpenDataClient (TownLevelForecasts)
/*! 2 天天氣預報
 @param inArea the area code. */
- (BFTask *)getTownLevelForecastsForTwoDaysAsyncForArea:(CWBArea)inArea;
- (BFTask *)getAllTownLevelForecastsForTwoDaysAsync;
/*! 1 周天氣預報
 @param inArea the area code. */
- (BFTask *)getTownLevelForecastsForOneWeekAsyncForArea:(CWBArea)inArea;
- (BFTask *)getAllTownLevelForecastsForOneWeekAsync;
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
/*! 黑白一週預測天氣圖 */
- (BFTask *)getBlackAndWhiteWeeklyWeatherPCXImageMetadataAsync;

/*! 滿潮預報影像圖 1-7 */
- (BFTask *)getWeeklyTidePredictionJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex; // 1-7
- (BFTask *)getWeeklyTidePredictionJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex; // 1-7

/*! 中文定量降水預報圖(I) */
- (BFTask *)getPrecipitationAmount1JpegImageMetadataAsync;
- (BFTask *)getPrecipitationAmount1JpegImageAsync;
/*! 中文定量降水預報圖(II) */
- (BFTask *)getPrecipitationAmount2JpegImageMetadataAsync;
- (BFTask *)getPrecipitationAmount2JpegImageAsync;

/*! 波浪分析圖 */
- (BFTask *)getWavePCXImageMetadataAsync;

/*! 24 小時波浪預報圖 */
- (BFTask *)getWaveForcast24HoursJpegImageMetadataAsync;
- (BFTask *)getWaveForcast24HoursJpegImageAsync;
/*! 36 小時波浪預報圖 */
- (BFTask *)getWaveForcast36HoursJpegImageMetadataAsync;
- (BFTask *)getWaveForcast36HoursJpegImageAsync;
/*! 48 小時波浪預報圖 */
- (BFTask *)getWaveForcast48HoursJpegImageMetadataAsync;
- (BFTask *)getWaveForcast48HoursJpegImageAsync;
@end

@interface CWBOpenDataClient (WeatherObserving)
/*! 自動氣象站-氣象觀測資料 */
- (BFTask *)getWeatherObservingDataAsync;
/*! 自動雨量站-雨量觀測資料 */
- (BFTask *)getPrecipitationObservingDataAsync;
/*! 局屬氣象站-現在天氣觀測報告 */
- (BFTask *)getCurrentWeatherObservingDataAsync;
/*! 酸雨*/
- (BFTask *)getDailyAcidRainPHScaleDataAsync;
/*! 紫外線 */
- (BFTask *)getDailyUltravioletDataAsync;
/*! 臭氧總量觀測資料-成功站 */
- (BFTask *)getOzoneObservingDataInChengkungAsync;
/*! 臭氧總量觀測資料-台北站 */
- (BFTask *)getOzoneObservingDataInTaipeiAsync;
/*! 潮位-沿岸潮位站監測資料 */
- (BFTask *)getTideLevelObervingDataAsync;
- (BFTask *)getSeaSurfaceTemperatureFromBuoysAndCoastalStationsAsync;
@end

typedef enum {
	CWBImageRegionGlobal = 0,
	CWBImageRegionEastAsian = 1,
	CWBImageRegionTaiwan = 3
} CWBImageRegion;

typedef enum {
	CWBImageTypeColorfulInfraredSatellite = 0, // 紅外線彩色衛星雲圖
	CWBImageTypeBlackAndWhiteInfraredSatellite = 1, // 紅外線黑白衛星雲圖
	CWBImageTypeColorfulEnhancedInfraredSatellite = 2, // 紅外線色調強化衛星雲圖
	CWBImageTypeVisibleSatellite = 3 // 可見光衛星雲圖
} CWBImageType;

@interface CWBOpenDataClient (WeatherObservingImages)
/*! 雷達回波圖彩色產品-全台灣區域無地形雷達回波圖檔 */
- (BFTask *)getRadarMosaicForTaiwanJpegImageMetaDataAsync;
- (BFTask *)getRadarMosaicForTaiwanJpegImageAsync;

/*! 雷達回波圖彩色產品-北台灣區域無地形雷達回波圖檔 */
- (BFTask *)getRadarMosaicForNorthTaiwanJpegImageMetaDataAsync;
- (BFTask *)getRadarMosaicForNorthTaiwanJpegImageAsync;

/*! 雷達回波圖彩色產品-南台灣區域無地形雷達回波圖檔 */
- (BFTask *)getRadarMosaicForSouthTaiwanJpegImageMetaDataAsync;
- (BFTask *)getRadarMosaicForSouthTaiwanJpegImageAsync;

/*! 雷達回波圖彩色產品-全台灣區域有地形雷達回波圖檔 */
- (BFTask *)getRadarMosaicForTaiwanWithTerrianJpegImageMetaDataAsync;
- (BFTask *)getRadarMosaicForTaiwanWithTerrianJpegImageAsync;

/*! 雷達回波圖彩色產品-北台灣區域有地形雷達回波圖檔 */
- (BFTask *)getRadarMosaicForNorthTaiwanWithTerrianJpegImageMetaDataAsync;
- (BFTask *)getRadarMosaicForNorthTaiwanWithTerrianJpegImageAsync;

/*! 雷達回波圖彩色產品-南台灣區域有地形雷達回波圖檔 */
- (BFTask *)getRadarMosaicForSouthTaiwanWithTerrianJpegImageMetaDataAsync;
- (BFTask *)getRadarMosaicForSouthTaiwanWithTerrianJpegImageAsync;

- (BFTask *)getSatelliteImageMetadataForRegion:(CWBImageRegion)inRegion type:(CWBImageType)inType;
- (BFTask *)getSatelliteImageForRegion:(CWBImageRegion)inRegion type:(CWBImageType)inType;
- (BFTask *)getHighDefinitionSatelliteImageMetadataWithType:(CWBImageType)inType;
- (BFTask *)getHighDefinitionSatelliteImageWithType:(CWBImageType)inType;
@end

