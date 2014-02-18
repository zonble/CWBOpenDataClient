#import <XCTest/XCTest.h>
#import <XCTest/XCTest.h>
#import <Bolts/Bolts.h>
#import "CWBOpenDataClient.h"

@interface CWBOpenDataClientTests : XCTestCase

@end

@implementation CWBOpenDataClientTests

- (void)setUp
{
	[super setUp];
}

- (void)tearDown
{
	[super tearDown];
}

- (NSDateFormatter *)dateFormatter
{
	NSDateFormatter *inputFormatter = [[NSDateFormatter alloc] init];
	[inputFormatter setDateFormat:@"yyyy-MM-dd'T'HH:mm:ssZZZ"];
	return inputFormatter;
}

- (void)validateTimeItem:(DDXMLElement *)time
{
	NSString *start = [[time attributeForName:@"start"] stringValue];
	NSString *end = [[time attributeForName:@"end"] stringValue];
	NSDate *startTime = [[self dateFormatter] dateFromString:start];
	NSDate *endTime = [[self dateFormatter] dateFromString:end];
	XCTAssertNotNil(start, @"There should be a start.");
	XCTAssertNotNil(end, @"There should be an end.");
	XCTAssertNotNil(startTime, @"There should be a startTime.");
	XCTAssertNotNil(endTime, @"There should be an endTime.");
}

- (void)testGet36HoursForecastAsync
{
	__block BOOL looping = YES;
	[CWBSharedClient().get36HoursForecastAsync continueWithBlock:^id(BFTask *task) {
		looping = NO;
		XCTAssertNil(task.error, @"There should not be any error");
		XCTAssertNotNil(task.result, @"There should be a result.");
		DDXMLDocument *xmlDocument = (DDXMLDocument *)task.result;
		NSString *title = [[xmlDocument nodesForXPath:@"//fifowml//head//product//title" error:nil][0] stringValue];
		XCTAssertNotNil(title, @"There should be a title.");
		NSString *issueTimeString = [[xmlDocument nodesForXPath:@"//fifowml//head//issue-time" error:nil][0] stringValue];
		NSLog(@"issueTimeString:%@", issueTimeString);
		NSDate *issueTime = [[self dateFormatter] dateFromString:issueTimeString];
		XCTAssertNotNil(issueTime, @"There should be an issue time.");
		NSLog(@"issueTime:%@", issueTime);

		NSString *updateTimeString = [[xmlDocument nodesForXPath:@"//fifowml//head//updated" error:nil][0] stringValue];
		NSDate *updateTime = [[self dateFormatter] dateFromString:updateTimeString];
		XCTAssertNotNil(updateTime, @"There should be an issue time.");

		NSArray *locations = [xmlDocument nodesForXPath:@"//fifowml//data//location" error:nil];
		for (DDXMLElement *node in locations) {
			NSString *name = [[node elementsForName:@"name"][0] stringValue];
			XCTAssertNotNil(name, @"There should be a name.");
			NSArray *wx = [[[node elementsForName:@"weather-elements"][0] elementsForName:@"Wx"][0] elementsForName:@"time"];
			XCTAssertTrue([wx count], @"count must be larger than 0");
			for (DDXMLElement *time in wx) {
				[self validateTimeItem:time];
				NSString *t = [[time elementsForName:@"text"][0] stringValue];
				NSString *v = [[time elementsForName:@"value"][0] stringValue];
				XCTAssertNotNil(t, @"There should be a text.");
				XCTAssertNotNil(v, @"There should be a value.");
			}

			NSArray *maxT = [[[node elementsForName:@"weather-elements"][0] elementsForName:@"MaxT"][0] elementsForName:@"time"];
			XCTAssertTrue([maxT count], @"count must be larger than 0");
			for (DDXMLElement *time in maxT) {
				[self validateTimeItem:time];
				NSString *v = [[time elementsForName:@"value"][0] stringValue];
				XCTAssertNotNil(v, @"There should be a value.");
			}

			NSArray *ci = [[[node elementsForName:@"weather-elements"][0] elementsForName:@"CI"][0] elementsForName:@"time"];
			XCTAssertTrue([maxT count], @"count must be larger than 0");
			for (DDXMLElement *time in ci) {
				[self validateTimeItem:time];
				NSString *t = [[time elementsForName:@"text"][0] stringValue];
				XCTAssertNotNil(t, @"There should be a text.");
			}

			NSArray *pop = [[[node elementsForName:@"weather-elements"][0] elementsForName:@"PoP"][0] elementsForName:@"time"];
			XCTAssertTrue([maxT count], @"count must be larger than 0");
			for (DDXMLElement *time in pop) {
				[self validateTimeItem:time];
				NSString *value = [[time elementsForName:@"value"][0] stringValue];
				XCTAssertNotNil(value, @"There should be a value.");
			}
		}
		return nil;
	}];

	while (looping) {
		[[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.2]];
	}
}

- (void)testGetGroundWeatherJpegImageMetadataAsync
{
	__block BOOL looping = YES;
	[CWBSharedClient().getGroundWeatherJpegImageMetadataAsync continueWithBlock:^id(BFTask *task) {
		looping = NO;
		XCTAssertNil(task.error, @"There should not be any error");
		XCTAssertNotNil(task.result, @"There should be a result.");
		NSLog(@"%@", task.result);
		return nil;
	}];

	while (looping) {
		[[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
	}

	looping = YES;
	[CWBSharedClient().getGroundWeatherJpegImageAsync continueWithBlock:^id(BFTask *task) {
		looping = NO;
		XCTAssertNil(task.error, @"There should not be any error");
		UIImage *image = task.result;
		XCTAssertTrue([image isKindOfClass:[UIImage class]], @"Must be an image");
		return nil;
	}];

	while (looping) {
		[[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.2]];
	}
}

- (void)testgetWeeklyWeatherJpegImageMetadataAsyncWithDayIndex
{
	for (NSInteger i = 0; i < 8; i++) {
		__block BOOL looping = YES;
		[[CWBSharedClient() getWeeklyWeatherJpegImageAsyncWithDayIndex:i] continueWithBlock:^id(BFTask *task) {
			looping = NO;
			XCTAssertNil(task.error, @"There should not be any error");
			UIImage *image = task.result;
			XCTAssertTrue([image isKindOfClass:[UIImage class]], @"Must be an image %d", i);
			return nil;
		}];

		while (looping) {
			[[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.2]];
		}
	}
}

@end
