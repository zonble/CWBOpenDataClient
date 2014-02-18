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
- (BFTask *)getTipsTaipeiCityAsync; // 台北市天氣小幫手
- (BFTask *)getTipsNewTaipeiCityAsync; // 新北市天氣小幫手
- (BFTask *)getTipsKeelungAsync; // 基隆市天氣小幫手
- (BFTask *)getTipsHualienAsync; // 花蓮縣天氣小幫手
- (BFTask *)getTipsYilanAsync; // 宜蘭縣天氣小幫手
- (BFTask *)getTipsKinmenAsync; // 金門縣天氣小幫手
- (BFTask *)getTipsPenghuAsync; // 澎湖縣天氣小幫手
- (BFTask *)getTipsTainanAsync; // 台南市天氣小幫手
- (BFTask *)getTipsKaohsiungAsync; // 高雄市天氣小幫手
- (BFTask *)getTipsChiayiAsync; //  嘉義縣天氣小幫手
- (BFTask *)getTipsChiayiCityAsync; // 嘉義市天氣小幫手
- (BFTask *)getTipsMiaoliAsync; // 苗栗縣天氣小幫手
- (BFTask *)getTipsTaichungAsync; // 台中市天氣小幫手
- (BFTask *)getTipsTaoyuanAsync; // 桃園縣天氣小幫手
- (BFTask *)getTipsHsinchuAsync; // 新竹縣天氣小幫手
- (BFTask *)getTipsHsinchuCityAsync; // 新竹市天氣小幫手
- (BFTask *)getTipsPingtungAsync; // 屏東縣天氣小幫手
- (BFTask *)getTipsNantouAsync; // 南投縣天氣小幫手
- (BFTask *)getTipsTaitungAsync; // 台東縣天氣小幫手
- (BFTask *)getTipsChanghuaAsync; // 彰化縣天氣小幫手
- (BFTask *)getTipsYunlinAsync; // 雲林縣天氣小幫手
- (BFTask *)getTipsLienchiangAsync; // 連江縣天氣小幫手
@end