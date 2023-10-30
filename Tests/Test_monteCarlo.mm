//
//  Tests.m
//  Tests
//
//  Created by Anna Griffith on 05/10/2023.
//

#import <XCTest/XCTest.h>
#import "../src/BinomialModel/BinomialModel.h"
#import "../src/Options/OptionPricer.h"
#import "../src/MonteCarlo/PathDependentOption.h"
#import "../src/MonteCarlo/EuropeanOption.h"

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
    double epsilon = 0.01;
    XCTAssertEqualWithAccuracy(option.priceByMC(mcBlackScholes, N, epsilon), 1.4012, 0.0001);
    XCTAssertEqualWithAccuracy(option.getPrice(), 1.4012, 0.0001);
    XCTAssertEqualWithAccuracy(option.getPricingError(), 0.0119, 0.0001);
    XCTAssertEqualWithAccuracy(option.getDelta(), 0.5726, 0.0001);
}

- (void)testEuropeanOption{
    double S0 = 100.0;
    double sigma = 0.1;
    double r = 0.02;
    MCBlackScholes mcBlackScholes(S0, sigma, r);
    
    double T = 5.0;
    double K = 100.0;
    EuropeanCall option(T, K);
    
    long N = 1000000;
    XCTAssertEqualWithAccuracy(option.priceByMC(mcBlackScholes, N), 14.07, 0.05); // answer from online calculator
    
    // Compare to binomial model
    int num_steps = 100;
    BinomialModel binModel = BinomialModel(S0, sigma, T, num_steps, r);
    CallOptionPricer optionsPricer = CallOptionPricer(num_steps, K, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 14.07, 0.05); // answer from online calculator
    XCTAssertEqualWithAccuracy(optionsPricer.priceAnalytic(), 14.07, 0.05);
}

@end
