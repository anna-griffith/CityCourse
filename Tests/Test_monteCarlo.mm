//
//  Tests.m
//  Tests
//
//  Created by Anna Griffith on 05/10/2023.
//

#import <XCTest/XCTest.h>
#import "../src/MonteCarlo/PathDependentOption.h"

@interface MCTests : XCTestCase

@end

@implementation MCTests

- (void)testGenerateSamplePath{
    double S0 = 100;
    double sigma = 0.2;
    double r = 0.02;

    MCBlackScholes mcBlackScholes(S0, sigma, r);
    
    double T = 1.0;
    int m = 100;
    SamplePath S(m);
    XCTAssertNoThrow(mcBlackScholes.generateSamplePath(T, m, S));
}

- (void)testAsianCallOption{
    double S0 = 100;
    double sigma = 0.2;
    double r = 0.02;

    MCBlackScholes mcBlackScholes(S0, sigma, r);
    
    double T = 1.0 / 12.0;
    double K = 100.0;
    int m = 30;
    
    ArthmAsianCall option(T, K, m);
    
    long N = 30000;
    XCTAssertEqualWithAccuracy(option.priceByMC(mcBlackScholes, N), 1.4012, 0.0001);
    
}

@end
