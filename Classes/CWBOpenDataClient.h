#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>
#import <Bolts/Bolts.h>
#import <KissXML/DDXML.h>

extern NSString *const CWBOpenDataClientErrorDomain;

/*!
 @enum CWBArea
 @constant CWBAreaTaipeiCity Taipei City (台北市)
 @constant CWBAreaNewTaipeiCity New Taipei City (新北市)
 @constant CWBAreaKeelung Keelung (基隆市)
 @constant CWBAreaHualien Hualien (花蓮縣)
 @constant CWBAreaYilan Yilan (宜蘭縣)
 @constant CWBAreaKinmen Kinmen (金門縣)
 @constant CWBAreaPenghu Penghu (澎湖縣)
 @constant CWBAreaTainan Tainan (台南市)
 @constant CWBAreaKaohsiung Kaohsiung (高雄市)
 @constant CWBAreaChiayi Chiayi (嘉義縣)
 @constant CWBAreaChiayiCity Chiayi City (嘉義市)
 @constant CWBAreaMiaoli Miaoli (苗栗縣)
 @constant CWBAreaTaichung Taichung (台中市)
 @constant CWBAreaTaoyuan Taoyuan (桃園縣)
 @constant CWBAreaHsinchu Hsinchu (新竹縣)
 @constant CWBAreaHsinchuCity Hsinchu City (新竹市)
 @constant CWBAreaPingtung Pingtung (屏東縣)
 @constant CWBAreaNantou Nantou (南投縣)
 @constant CWBAreaTaitung Taitung (台東縣)
 @constant CWBAreaChanghua Changhua (彰化縣)
 @constant CWBAreaYunlin Yunlin (雲林縣)
 @constant CWBAreaLienchian Lienchian (連江縣)
 */
typedef NS_ENUM(NSUInteger, CWBArea) {
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
};

/*! @enum CWBRadarImageRegion
@constant CWBRadarImageRegionTaiwan Taiwan (台灣)
@constant CWBRadarImageRegionNorthTaiwan North Taiwan (北台灣)
@constant CWBRadarImageRegionSouthTaiwan South Taiwan (南台灣) */
typedef NS_ENUM(NSUInteger, CWBRadarImageRegion) {
	CWBRadarImageRegionTaiwan = 0,
	CWBRadarImageRegionNorthTaiwan = 1,
	CWBRadarImageRegionSouthTaiwan = 2
};

/*! @enum CWBSatelliteImageRegion
@constant CWBSatelliteImageRegionGlobal Taiwan (台灣)
@constant CWBSatelliteImageRegionEastAsia East Asia (東亞)
@constant CWBSatelliteImageRegionTaiwan Taiwan (台灣) */
typedef NS_ENUM(NSUInteger, CWBSatelliteImageRegion) {
	CWBSatelliteImageRegionGlobal = 0,
	CWBSatelliteImageRegionEastAsia = 1,
	CWBSatelliteImageRegionTaiwan = 2
};

/*! @enum CWBSatelliteImageType
@constant CWBSatelliteImageTypeColorfulInfraredSatellite 紅外線彩色衛星雲圖
@constant CWBSatelliteImageTypeBlackAndWhiteInfraredSatellite 紅外線黑白衛星雲圖
@constant CWBSatelliteImageTypeColorfulEnhancedInfraredSatellite 紅外線色調強化衛星雲圖
@constant CWBSatelliteImageTypeVisibleSatellite 可見光衛星雲圖 */
typedef NS_ENUM(NSUInteger, CWBSatelliteImageType) {
	CWBSatelliteImageTypeColorfulInfraredSatellite = 0,
	CWBSatelliteImageTypeBlackAndWhiteInfraredSatellite = 1,
	CWBSatelliteImageTypeColorfulEnhancedInfraredSatellite = 2,
	CWBSatelliteImageTypeVisibleSatellite = 3
};

/*! CWBOpenDataClient is a library which helps to access forecasts and
various open data provided by Central Weather Bureau.

The class provides several caterories, and each category contains
methods to help fetching data asynchronously. CWBOpenDataClient uses
Bolts framework to do these asynchronous tasks, so you will get a
BFTask object after calling any method, and you can then provide a
callack block by calling `continueWithBlock:`.

To know more about Bolts framework and the idea of "Promises", please
visit Bolts' webpage <https://github.com/BoltsFramework/Bolts-iOS>.

For furthur information, please visit <http://opendata.cwb.gov.tw>. */

@interface CWBOpenDataClient : AFHTTPSessionManager
/*! The singleton object. */
+ (instancetype)sharedClient;
/*! Version of the library. */
+ (NSString *)version;
@end

@interface CWBOpenDataClient (Forecasts)
/*! Fetches the forecast for all areas in Taiwan within 36 hours (今明
	36 小時天氣預報). */
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

@interface CWBOpenDataClient (ForecastImages)
/*! Fetches the metadata of the current ground weather image
	(中文彩色合成地面天氣圖). */
- (BFTask *)getGroundWeatherJpegImageMetadataAsync;
/*! Fetches the current ground weather image in JPEG format
	(中文彩色合成地面天氣圖). */
- (BFTask *)getGroundWeatherJpegImageAsync;
/*! Fetches the newest weather image (最新天氣圖) in PDF format */
- (BFTask *)getNewestWeatherPDFDocumentMetadataAsync;
/*! Fetches the metadata of the image for weather prediction with 24
	hours (中文彩色合成24小時預測天氣圖) */
- (BFTask *)get24HoursWeatherJpegImageMetadataAsync;
/*! Fetches the image for weather prediction with 24 hours in JPEG
	format. (中文彩色合成24小時預測天氣圖) */
- (BFTask *)get24HoursWeatherJpegImageAsync;
/*! Fetches the metadata of the image for weather prediction for a
	week. (一週天氣預測圖)
	@param inDayIndex index of the day. 0-7 */
- (BFTask *)getWeeklyWeatherJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex;
/*! Fetches image for weather prediction for a week in JPEG format.
	(一週天氣預測圖)
	@param inDayIndex index of the day. 0-7 */
- (BFTask *)getWeeklyWeatherJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex;
/*! 黑白一週預測天氣圖 */
- (BFTask *)getBlackAndWhiteWeeklyWeatherPCXImageMetadataAsync;
/*! Fetches the metadata of the image for tide prediction within a
	week (滿潮預報影像圖).
	@param inDayIndex index of the day. 1-7 */
- (BFTask *)getWeeklyTidePredictionJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex;
/*! Fetches the image for tide prediction within a week in JPEG format
	(滿潮預報影像圖).
	@param inDayIndex index of the day. 1-7 */
- (BFTask *)getWeeklyTidePredictionJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex;
/*! Fetches the metadata of the image for precipitation amount part 1.
	(中文定量降水預報圖 I) */
- (BFTask *)getPrecipitationAmount1JpegImageMetadataAsync;
/*! Fetches the image for precipitation amount part 1 in JPEG format.
	(中文定量降水預報圖 I) */
- (BFTask *)getPrecipitationAmount1JpegImageAsync;
/*! Fetches the metadata of the image for precipitation amount part 2.
	(中文定量降水預報圖 II) */
- (BFTask *)getPrecipitationAmount2JpegImageMetadataAsync;
/*! Fetches the image for precipitation amount part 2 in JPEG format.
	(中文定量降水預報圖 II) */
- (BFTask *)getPrecipitationAmount2JpegImageAsync;
/*! Fetches the metadata of the image for wave analysis (波浪分析圖).  */
- (BFTask *)getWavePCXImageMetadataAsync;
/*! Fetches the metadata of the image for wave forcast within 24 hours
	in JPEG format. (24 小時波浪預報圖) */
- (BFTask *)getWaveForcast24HoursJpegImageMetadataAsync;
/*! Fetches the image for wave forcast within 24 hours in JPEG format.
	(24 小時波浪預報圖) */
- (BFTask *)getWaveForcast24HoursJpegImageAsync;
/*! Fetches the metadata of the image for wave forcast within 36 hours
	in JPEG format. (36 小時波浪預報圖) */
- (BFTask *)getWaveForcast36HoursJpegImageMetadataAsync;
/*! Fetches the image for wave forcast within 36 hours in JPEG format.
	(36 小時波浪預報圖) */
- (BFTask *)getWaveForcast36HoursJpegImageAsync;
/*! Fetches the metadata of the image for wave forcast within 48 hours
	in JPEG format. (48 小時波浪預報圖) */
- (BFTask *)getWaveForcast48HoursJpegImageMetadataAsync;
/*! Fetches the image for wave forcast within 48 hours in JPEG format.
	(48 小時波浪預報圖) */
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

@interface CWBOpenDataClient (WeatherObservingImages)
/*! Fetches the metadata of a radio mosaic image for a desired region.
	@param inRegion the region
	@param inBlackAndWhite is the image in black and white or
	colorful. */
- (BFTask *)getRadarMosaicJpegImageMetadataForRegion:(CWBRadarImageRegion)inRegion blackAndWhite:(BOOL)inBlackAndWhite;
/*! Fetches a radio mosaic image for a desired region.
	@param inRegion the region
	@param inBlackAndWhite is the image in black and white or
	colorful. */
- (BFTask *)getRadarMosaicJpegImageForRegion:(CWBRadarImageRegion)inRegion blackAndWhite:(BOOL)inBlackAndWhite;
/*! Fetches the metadata of a satellite image for a desired region.
	@param inRegion the region
	@param inType type of the image. */
- (BFTask *)getSatelliteImageMetadataForRegion:(CWBSatelliteImageRegion)inRegion type:(CWBSatelliteImageType)inType;
/*! Fetches a satellite image for a desired region.
    @param inRegion the region
    @param inType type of the image. */
- (BFTask *)getSatelliteImageForRegion:(CWBSatelliteImageRegion)inRegion type:(CWBSatelliteImageType)inType;
/*! Fetches the metadata of a high-definition satellite image for a
    desired region.
    @param inType type of the image. */
- (BFTask *)getHighDefinitionSatelliteImageMetadataWithType:(CWBSatelliteImageType)inType;
/*! Fetches a high-definition satellite image for a desired region.
    @param inType type of the image. */
- (BFTask *)getHighDefinitionSatelliteImageWithType:(CWBSatelliteImageType)inType;
@end

@interface CWBOpenDataClient (Climate)
/*! 觀測網旬資料-一級農業氣象站觀測資料 */
- (BFTask *)getAgriculturalMeteoroDataFor10DaysAsync;
/*! 觀測網月資料-一級農業氣象站觀測資料 */
- (BFTask *)getAgriculturalMeteoroDataForMonthAsync;

@end

/*! An alias to [CWBOpenDataClient sharedClient]. */
CWBOpenDataClient *CWBSharedClient();
