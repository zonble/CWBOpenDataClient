#import "CWBOpenDataClient.h"

NSString *const CWBOpenDataClientErrorDomain = @"CWBOpenDataClientErrorDomain";
static NSInteger CWBOpenDataClientErrorNoImageURL = 0;

@interface CWBTaskCompletionSource : BFTaskCompletionSource
+ (CWBTaskCompletionSource *)taskCompletionSource;
@property (strong, nonatomic) NSURLSessionTask *connectionTask;
@end

@implementation CWBTaskCompletionSource

+ (CWBTaskCompletionSource *)taskCompletionSource
{
	return [[CWBTaskCompletionSource alloc] init];
}

- (void)dealloc
{
	[self.connectionTask cancel];
	self.connectionTask = nil;
}

- (void)cancel
{
	[self.connectionTask cancel];
	[super cancel];
}

@end

CWBOpenDataClient *CWBSharedClient()
{
	return [CWBOpenDataClient sharedClient];
}


@implementation CWBOpenDataClient

+ (instancetype)sharedClient
{
	static dispatch_once_t onceToken;
	static CWBOpenDataClient *shareClient;
	dispatch_once(&onceToken, ^{
		shareClient = [[CWBOpenDataClient alloc] init];
	});
	return shareClient;
}

+ (NSString *)version
{
	return @"0.1.0";
}

- (id)init
{
	self = [super initWithBaseURL:[NSURL URLWithString:@"http://opendata.cwb.gov.tw/"]];
	if (self) {
		AFHTTPRequestSerializer *requestSerializer = [AFHTTPRequestSerializer serializer];
		AFHTTPResponseSerializer *responseSerializer = [AFHTTPResponseSerializer serializer];
		responseSerializer.acceptableContentTypes = [NSSet setWithObjects:@"text/xml", nil];
		self.responseSerializer = responseSerializer;
		self.requestSerializer = requestSerializer;
	}
	return self;
}

- (BFTask *)_taskWithPath:(NSString *)inPath
{
	CWBTaskCompletionSource *source = [CWBTaskCompletionSource taskCompletionSource];
	source.connectionTask = [self GET:inPath parameters:Nil success:^(NSURLSessionDataTask *task, id responseObject) {
		if (responseObject) {
			NSError *error = nil;
			NSString *xmlString = [[NSString alloc] initWithData:responseObject encoding:NSUTF8StringEncoding];
			DDXMLDocument *xmlDocument = [[DDXMLDocument alloc] initWithXMLString:xmlString options:0 error:&error];
			if (error) {
				[source setError:error];
			}
			else {
				[source setResult:xmlDocument];
			}
		}
	} failure:^(NSURLSessionDataTask *task, NSError *error) {
		[source setError:error];
	}];
	return source.task;
}

- (BFTask *)_download:(NSURL *)inURL
{
	CWBTaskCompletionSource *source = [CWBTaskCompletionSource taskCompletionSource];
	NSURLSessionDownloadTask *downloadTask = [[NSURLSession sharedSession] downloadTaskWithURL:inURL completionHandler:^(NSURL *location, NSURLResponse *response, NSError *error) {
		if (error) {
			[source setError:error];
		}
		else {
			[source setResult:location];
		}
	}];
	source.connectionTask = downloadTask;
	[downloadTask resume];
	return source.task;
}

@end


@implementation CWBOpenDataClient (Forecasts)

- (BFTask *)get36HoursForecastAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-001.xml"];
}

- (BFTask *)get7DaysForecastAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-003.xml"];
}

- (BFTask *)getWeekForecastAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-005.xml"];
}

- (BFTask *)getGlablCitiesForecastAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-007.xml"];
}

- (BFTask *)getCoastalWatersForecastAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-A0012-001.xml"];
}

- (BFTask *)getWaveForecastAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-A0020-001.xml"];
}

- (BFTask *)getMonthlyTidePredictionAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-A0021-001.xml"];
}

- (BFTask *)getNextYearTidePredictionAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-A0023-001.xml"];
}

@end

@implementation CWBOpenDataClient (Tips)
- (BFTask *)getTipsAsyncForArea:(CWBArea)inArea
{
	NSDictionary *map = @{@(CWBAreaTaipeiCity): @"/opendata/MFC/F-C0032-009.xml",
						  @(CWBAreaNewTaipeiCity): @"/opendata/MFC/F-C0032-010.xml",
						  @(CWBAreaKeelung): @"/opendata/MFC/F-C0032-011.xml",
						  @(CWBAreaHualien): @"/opendata/MFC/F-C0032-012.xml",
						  @(CWBAreaYilan): @"/opendata/MFC/F-C0032-013.xml",
						  @(CWBAreaKinmen): @"/opendata/MFC/F-C0032-014.xml",
						  @(CWBAreaPenghu): @"/opendata/MFC/F-C0032-015.xml",
						  @(CWBAreaTainan): @"/opendata/MFC/F-C0032-016.xml",
						  @(CWBAreaKaohsiung): @"/opendata/MFC/F-C0032-017.xml",
						  @(CWBAreaChiayi): @"/opendata/MFC/F-C0032-018.xml",
						  @(CWBAreaChiayiCity): @"/opendata/MFC/F-C0032-019.xml",
						  @(CWBAreaMiaoli): @"/opendata/MFC/F-C0032-020.xml",
						  @(CWBAreaTaichung): @"/opendata/MFC/F-C0032-021.xml",
						  @(CWBAreaTaoyuan): @"/opendata/MFC/F-C0032-022.xml",
						  @(CWBAreaHsinchu): @"/opendata/MFC/F-C0032-023.xml",
						  @(CWBAreaHsinchuCity): @"/opendata/MFC/F-C0032-024.xml",
						  @(CWBAreaPingtung): @"/opendata/MFC/F-C0032-025.xml",
						  @(CWBAreaNantou): @"/opendata/MFC/F-C0032-026.xml",
						  @(CWBAreaTaitung): @"/opendata/MFC/F-C0032-027.xml",
						  @(CWBAreaChanghua): @"/opendata/MFC/F-C0032-028.xml",
						  @(CWBAreaYunlin): @"/opendata/MFC/F-C0032-029.xml",
						  @(CWBAreaLienchian): @"/opendata/MFC/F-C0032-030.xml"};
	return [self _taskWithPath:map[@(inArea)]];
}
@end

@implementation CWBOpenDataClient (TownLevelForecasts)
- (BFTask *)getTownLevelForecastsForTwoDaysAsyncForArea:(CWBArea)inArea
{
	NSDictionary *map = @{@(CWBAreaTaipeiCity): @"/opendata/MFC/F-D0047-061.xml",
						  @(CWBAreaNewTaipeiCity): @"/opendata/MFC/F-D0047-069.xml",
						  @(CWBAreaKeelung): @"/opendata/MFC/F-D0047-049.xml",
						  @(CWBAreaHualien): @"/opendata/MFC/F-D0047-041.xml",
						  @(CWBAreaYilan): @"/opendata/MFC/F-D0047-001.xml",
						  @(CWBAreaKinmen): @"/opendata/MFC/F-D0047-085.xml",
						  @(CWBAreaPenghu): @"/opendata/MFC/F-D0047-045.xml",
						  @(CWBAreaTainan): @"/opendata/MFC/F-D0047-077.xml",
						  @(CWBAreaKaohsiung): @"/opendata/MFC/F-D0047-065.xml",
						  @(CWBAreaChiayi): @"/opendata/MFC/F-D0047-029.xml",
						  @(CWBAreaChiayiCity): @"/opendata/MFC/F-D0047-057.xml",
						  @(CWBAreaMiaoli): @"/opendata/MFC/F-D0047-013.xml",
						  @(CWBAreaTaichung): @"/opendata/MFC/F-D0047-073.xml",
						  @(CWBAreaTaoyuan): @"/opendata/MFC/F-D0047-005.xml",
						  @(CWBAreaHsinchu): @"/opendata/MFC/F-D0047-009.xml",
						  @(CWBAreaHsinchuCity): @"/opendata/MFC/F-D0047-053.xml",
						  @(CWBAreaPingtung): @"/opendata/MFC/F-D0047-033.xml",
						  @(CWBAreaNantou): @"/opendata/MFC/F-D0047-021.xml",
						  @(CWBAreaTaitung): @"/opendata/MFC/F-D0047-037.xml",
						  @(CWBAreaChanghua): @"/opendata/MFC/F-D0047-017.xml",
						  @(CWBAreaYunlin): @"/opendata/MFC/F-D0047-025.xml",
						  @(CWBAreaLienchian): @"/opendata/MFC/F-D0047-081.xml"};
	return [self _taskWithPath:map[@(inArea)]];
}

- (BFTask *)getAllTownLevelForecastsForTwoDaysAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-D0047-089.xml"];
}

- (BFTask *)getTownLevelForecastsForOneWeekAsyncForArea:(CWBArea)inArea
{
	NSDictionary *map = @{@(CWBAreaTaipeiCity): @"/opendata/MFC/F-D0047-063.xml",
						  @(CWBAreaNewTaipeiCity): @"/opendata/MFC/F-D0047-071.xml",
						  @(CWBAreaKeelung): @"/opendata/MFC/F-D0047-051.xml",
						  @(CWBAreaHualien): @"/opendata/MFC/F-D0047-043.xml",
						  @(CWBAreaYilan): @"/opendata/MFC/F-D0047-003.xml",
						  @(CWBAreaKinmen): @"/opendata/MFC/F-D0047-087.xml",
						  @(CWBAreaPenghu): @"/opendata/MFC/F-D0047-047.xml",
						  @(CWBAreaTainan): @"/opendata/MFC/F-D0047-079.xml",
						  @(CWBAreaKaohsiung): @"/opendata/MFC/F-D0047-067.xml",
						  @(CWBAreaChiayi): @"/opendata/MFC/F-D0047-031.xml",
						  @(CWBAreaChiayiCity): @"/opendata/MFC/F-D0047-059.xml",
						  @(CWBAreaMiaoli): @"/opendata/MFC/F-D0047-015.xml",
						  @(CWBAreaTaichung): @"/opendata/MFC/F-D0047-075.xml",
						  @(CWBAreaTaoyuan): @"/opendata/MFC/F-D0047-007.xml",
						  @(CWBAreaHsinchu): @"/opendata/MFC/F-D0047-011.xml",
						  @(CWBAreaHsinchuCity): @"/opendata/MFC/F-D0047-055.xml",
						  @(CWBAreaPingtung): @"/opendata/MFC/F-D0047-035.xml",
						  @(CWBAreaNantou): @"/opendata/MFC/F-D0047-023.xml",
						  @(CWBAreaTaitung): @"/opendata/MFC/F-D0047-039.xml",
						  @(CWBAreaChanghua): @"/opendata/MFC/F-D0047-019.xml",
						  @(CWBAreaYunlin): @"/opendata/MFC/F-D0047-027.xml",
						  @(CWBAreaLienchian): @"/opendata/MFC/F-D0047-083.xml"};
	return [self _taskWithPath:map[@(inArea)]];
}

- (BFTask *)getAllTownLevelForecastsForOneWeekAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-D0047-091.xml"];
}
@end

@implementation CWBOpenDataClient (ForecastImages)

- (NSString *)_imageURLFromXMLDocument:(DDXMLDocument *)inXMLDocument
{
	NSArray *datasets = [[inXMLDocument rootElement] elementsForName:@"dataset"];
	if (![datasets count]) {
		return nil;
	}
	NSArray *resources = [datasets[0] elementsForName:@"resource"];
	if (![resources count]) {
		return nil;
	}
	NSArray *uri = [resources[0] elementsForName:@"uri"];
	if (![uri count]) {
		return nil;
	}
	return [uri[0] stringValue];
}

- (BFTask *)_imageTaskWithTask:(BFTask *)inTask
{
	return [[inTask continueWithSuccessBlock:^id(BFTask *inMetadataTask) {
		DDXMLDocument *xmlDocument = (DDXMLDocument *)inMetadataTask.result;
		NSString *URLString = [self _imageURLFromXMLDocument:xmlDocument];
		NSURL *URL = [NSURL URLWithString:URLString];
		if (URL) {
			return [self _download:URL];
		}
		NSError *error = [NSError errorWithDomain:CWBOpenDataClientErrorDomain code:CWBOpenDataClientErrorNoImageURL userInfo:@{NSLocalizedDescriptionKey:NSLocalizedString(@"No URL for the desired image found!", @"")}];
		return [BFTask taskWithError:error];
	}] continueWithSuccessBlock:^id(BFTask *task) {
		BFTaskCompletionSource *source = [BFTaskCompletionSource taskCompletionSource];
		NSURL *URL = (NSURL *)task.result;
		UIImage *image = [[UIImage alloc] initWithContentsOfFile:[URL path]];
		[source setResult:image];
		return source.task;
	}];
}

- (BFTask *)getGroundWeatherJpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-001.xml"];
}

- (BFTask *)getGroundWeatherJpegImageAsync
{
	return [self _imageTaskWithTask:[self getGroundWeatherJpegImageMetadataAsync]];
}

- (BFTask *)getNewestWeatherPDFDocumentMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-003.xml"];
}

- (BFTask *)get24HoursWeatherJpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-004.xml"];
}

- (BFTask *)get24HoursWeatherJpegImageAsync
{
	return [self _imageTaskWithTask:[self get24HoursWeatherJpegImageMetadataAsync]];
}

- (BFTask *)getWeeklyWeatherJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex
{
	NSParameterAssert(inDayIndex >= 0 && inDayIndex <= 7);
	NSArray *map = @[@"/opendata/MFC/F-C0035-006.xml",
					 @"/opendata/MFC/F-C0035-007.xml",
					 @"/opendata/MFC/F-C0035-008.xml",
					 @"/opendata/MFC/F-C0035-009.xml",
					 @"/opendata/MFC/F-C0035-010.xml",
					 @"/opendata/MFC/F-C0035-011.xml",
					 @"/opendata/MFC/F-C0035-012.xml",
					 @"/opendata/MFC/F-C0035-013.xml"];
	return [self _taskWithPath:map[inDayIndex]];
}

- (BFTask *)getWeeklyWeatherJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex
{
	return [self _imageTaskWithTask:[self getWeeklyWeatherJpegImageMetadataAsyncWithDayIndex:inDayIndex]];
}

- (BFTask *)getBlackAndWhiteWeeklyWeatherPCXImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-014.xml"];
}

- (BFTask *)getWeeklyTidePredictionJpegImageMetadataAsyncWithDayIndex:(NSInteger)inDayIndex
{
	NSParameterAssert(inDayIndex >= 1 && inDayIndex <= 7);
	NSArray *map = @[@"", @"/opendata/MFC/F-A0022-001.xml",
					 @"/opendata/MFC/F-A0022-002.xml",
					 @"/opendata/MFC/F-A0022-003.xml",
					 @"/opendata/MFC/F-A0022-004.xml",
					 @"/opendata/MFC/F-A0022-005.xml",
					 @"/opendata/MFC/F-A0022-006.xml",
					 @"/opendata/MFC/F-A0022-007.xml"];
	return [self _taskWithPath:map[inDayIndex]];
}

- (BFTask *)getWeeklyTidePredictionJpegImageAsyncWithDayIndex:(NSInteger)inDayIndex
{
	return [self _imageTaskWithTask:[self getWeeklyTidePredictionJpegImageMetadataAsyncWithDayIndex:inDayIndex]];
}

- (BFTask *)getPrecipitationAmount1JpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-015.xml"];
}

- (BFTask *)getPrecipitationAmount1JpegImageAsync
{
	return [self _imageTaskWithTask:[self getPrecipitationAmount1JpegImageMetadataAsync]];
}

- (BFTask *)getPrecipitationAmount2JpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-017.xml"];
}

- (BFTask *)getPrecipitationAmount2JpegImageAsync
{
	return [self _imageTaskWithTask:[self getPrecipitationAmount2JpegImageMetadataAsync]];
}

- (BFTask *)getWavePCXImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-019.xml"];
}

- (BFTask *)getWaveForcast24HoursJpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-020.xml"];
}

- (BFTask *)getWaveForcast24HoursJpegImageAsync
{
	return [self _imageTaskWithTask:[self getWaveForcast24HoursJpegImageMetadataAsync]];
}

- (BFTask *)getWaveForcast36HoursJpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-021.xml"];
}

- (BFTask *)getWaveForcast36HoursJpegImageAsync
{
	return [self _imageTaskWithTask:[self getWaveForcast36HoursJpegImageMetadataAsync]];
}

- (BFTask *)getWaveForcast48HoursJpegImageMetadataAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0035-022.xml"];
}

- (BFTask *)getWaveForcast48HoursJpegImageAsync
{
	return [self _imageTaskWithTask:[self getWaveForcast48HoursJpegImageMetadataAsync]];
}

@end


@implementation CWBOpenDataClient (WeatherObserving)

- (BFTask *)getWeatherObservingDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0001-001.xml"];
}

- (BFTask *)getPrecipitationObservingDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0002-001.xml"];
}

- (BFTask *)getCurrentWeatherObservingDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0003-001.xml"];
}

- (BFTask *)getDailyAcidRainPHScaleDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0004-001.xml"];
}

- (BFTask *)getDailyUltravioletDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0005-001.xml"];
}

- (BFTask *)getOzoneObservingDataInChengkungAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0006-001.xml"];
}

- (BFTask *)getOzoneObservingDataInTaipeiAsync
{
	return [self _taskWithPath:@"/opendata/DIV2/O-A0006-002.xml"];
}

- (BFTask *)getTideLevelObervingDataAsync
{
	return [self _taskWithPath:@"/opendata/MMC/O-A0017-001.xml"];
}

- (BFTask *)getSeaSurfaceTemperatureFromBuoysAndCoastalStationsAsync
{
	return [self _taskWithPath:@"/opendata/MMC/O-A0019-001.xml"];
}

@end


@implementation CWBOpenDataClient (WeatherObservingImages)

- (BFTask *)getRadarMosaicForTaiwanJpegImageMetaDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV4/O-A0011-001.xml"];
}
- (BFTask *)getRadarMosaicForTaiwanJpegImageAsync
{
	return [self _imageTaskWithTask:[self getRadarMosaicForTaiwanJpegImageMetaDataAsync]];
}

- (BFTask *)getRadarMosaicForNorthTaiwanJpegImageMetaDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV4/O-A0011-002.xml"];
}
- (BFTask *)getRadarMosaicForNorthTaiwanJpegImageAsync
{
	return [self _imageTaskWithTask:[self getRadarMosaicForNorthTaiwanJpegImageMetaDataAsync]];
}

- (BFTask *)getRadarMosaicForSouthTaiwanJpegImageMetaDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV4/O-A0011-003.xml"];
}
- (BFTask *)getRadarMosaicForSouthTaiwanJpegImageAsync
{
	return [self _imageTaskWithTask:[self getRadarMosaicForSouthTaiwanJpegImageMetaDataAsync]];
}

- (BFTask *)getRadarMosaicForTaiwanWithTerrianJpegImageMetaDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV4/O-A0011-004.xml"];
}
- (BFTask *)getRadarMosaicForTaiwanWithTerrianJpegImageAsync
{
	return [self _imageTaskWithTask:[self getRadarMosaicForTaiwanWithTerrianJpegImageMetaDataAsync]];
}

- (BFTask *)getRadarMosaicForNorthTaiwanWithTerrianJpegImageMetaDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV4/O-A0011-005.xml"];
}
- (BFTask *)getRadarMosaicForNorthTaiwanWithTerrianJpegImageAsync
{
	return [self _imageTaskWithTask:[self getRadarMosaicForNorthTaiwanWithTerrianJpegImageMetaDataAsync]];
}

- (BFTask *)getRadarMosaicForSouthTaiwanWithTerrianJpegImageMetaDataAsync
{
	return [self _taskWithPath:@"/opendata/DIV4/O-A0011-006.xml"];
}
- (BFTask *)getRadarMosaicForSouthTaiwanWithTerrianJpegImageAsync
{
	return [self _imageTaskWithTask:[self getRadarMosaicForSouthTaiwanWithTerrianJpegImageMetaDataAsync]];
}

- (BFTask *)getSatelliteImageMetadataForRegion:(CWBImageRegion)inRegion type:(CWBImageType)inType
{
	NSArray *map = nil;
	switch (inType) {
		case CWBImageTypeColorfulInfraredSatellite:
			map = @[@"/opendata/MSC/O-B0028-001.xml", @"/opendata/MSC/O-B0028-002.xml", @"/opendata/MSC/O-B0028-003.xml"];
			break;
		case CWBImageTypeBlackAndWhiteInfraredSatellite:
			map = @[@"/opendata/MSC/O-B0029-001.xml", @"/opendata/MSC/O-B0029-002.xml", @"/opendata/MSC/O-B0029-003.xml"];
			break;
		case CWBImageTypeColorfulEnhancedInfraredSatellite:
			map = @[@"/opendata/MSC/O-B0030-001.xml", @"/opendata/MSC/O-B0030-002.xml", @"/opendata/MSC/O-B0030-003.xml"];
			break;
		case CWBImageTypeVisibleSatellite:
			map = @[@"/opendata/MSC/O-B0031-001.xml", @"/opendata/MSC/O-B0031-002.xml", @"/opendata/MSC/O-B0031-003.xml"];
			break;
		default:
			break;
	}
	return [self _taskWithPath:map[inRegion]];
}

- (BFTask *)getSatelliteImageForRegion:(CWBImageRegion)inRegion type:(CWBImageType)inType
{
	return [self _imageTaskWithTask:[self getSatelliteImageMetadataForRegion:inRegion type:inType]];
}

- (BFTask *)getHighDefinitionSatelliteImageMetadataWithType:(CWBImageType)inType
{
	NSArray *map = @[@"/opendata/MSC/O-B0032-002.xml", @"/opendata/MSC/O-B0032-003.xml", @"/opendata/MSC/O-B0032-004.xml", @"/opendata/MSC/O-B0032-001.xml"];
	return [self _taskWithPath:map[inType]];
}

- (BFTask *)getHighDefinitionSatelliteImageWithType:(CWBImageType)inType
{
	return [self _imageTaskWithTask:[self getHighDefinitionSatelliteImageMetadataWithType:inType]];
}

@end

