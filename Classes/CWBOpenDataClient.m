#import "CWBOpenDataClient.h"

@interface CWBTaskCompletionSource : BFTaskCompletionSource
+ (CWBTaskCompletionSource *)taskCompletionSource;
@property (strong, nonatomic) NSURLSessionDataTask *dataTask;
@end

@implementation CWBTaskCompletionSource

+ (CWBTaskCompletionSource *)taskCompletionSource
{
	return [[CWBTaskCompletionSource alloc] init];
}

- (void)dealloc
{
	[self.dataTask cancel];
	self.dataTask = nil;
}

- (void)cancel
{
	[self.dataTask cancel];
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

- (id)init
{
	self = [super initWithBaseURL:[NSURL URLWithString:@"http://opendata.cwb.gov.tw/"]];
	if (self) {
		AFHTTPRequestSerializer * requestSerializer = [AFHTTPRequestSerializer serializer];
		AFHTTPResponseSerializer * responseSerializer = [AFHTTPResponseSerializer serializer];
		responseSerializer.acceptableContentTypes = [NSSet setWithObjects:@"text/xml", nil];
		self.responseSerializer = responseSerializer;
		self.requestSerializer = requestSerializer;
	}
	return self;
}

- (BFTask *)_taskWithPath:(NSString *)inPath
{
	CWBTaskCompletionSource *source = [CWBTaskCompletionSource taskCompletionSource];
	source.dataTask = [self GET:inPath parameters:Nil success:^(NSURLSessionDataTask *task, id responseObject) {
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
@end

@implementation CWBOpenDataClient (Tips)

- (BFTask *)getTipsTaipeiCityAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-009.xml"];
}

- (BFTask *)getTipsNewTaipeiCityAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-010.xml"];
}

- (BFTask *)getTipsKeelungAsync;
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-011.xml"];
}

- (BFTask *)getTipsHualienAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-012.xml"];
}

- (BFTask *)getTipsYilanAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-013.xml"];
}

- (BFTask *)getTipsKinmenAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-014.xml"];
}

- (BFTask *)getTipsPenghuAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-015.xml"];
}

- (BFTask *)getTipsTainanAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-016.xml"];
}

- (BFTask *)getTipsKaohsiungAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-017.xml"];
}

- (BFTask *)getTipsChiayiAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-018.xml"];
}

- (BFTask *)getTipsChiayiCityAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-019.xml"];
}

- (BFTask *)getTipsMiaoliAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-020.xml"];
}

- (BFTask *)getTipsTaichungAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-021.xml"];
}

- (BFTask *)getTipsTaoyuanAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-022.xml"];
}

- (BFTask *)getTipsHsinchuAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-023.xml"];
}

- (BFTask *)getTipsHsinchuCityAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-024.xml"];
}

- (BFTask *)getTipsPingtungAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-025.xml"];
}

- (BFTask *)getTipsNantouAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-026.xml"];
}

- (BFTask *)getTipsTaitungAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-027.xml"];
}

- (BFTask *)getTipsChanghuaAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-028.xml"];
}

- (BFTask *)getTipsYunlinAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-029.xml"];
}

- (BFTask *)getTipsLienchiangAsync
{
	return [self _taskWithPath:@"/opendata/MFC/F-C0032-030.xml"];
}

@end
