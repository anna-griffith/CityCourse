//
//  Tests.m
//  Tests
//
//  Created by Anna Griffith on 05/10/2023.
//

#import <XCTest/XCTest.h>
#import "../src/BinomialModel/BinomialModel.h"
#import "../src/Options/OptionPricer.h"
#import "../src/Options/BarrierOptionPricer.h"

@interface Tests : XCTestCase

@end

@implementation Tests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testArbitrage{
    double S0 = 4.0;
    double U = 0.1;
    double D = -0.1;
    double R = 0.2;
    XCTAssertThrows(BinomialModel(S0, U, D, R));
}

- (void)testIllegalInputs{
    double S0 = -4.0;
    double U = 0.1;
    double D = -0.1;
    double R = 0.05;
    XCTAssertThrows(BinomialModel(S0, U, D, R));
}

- (void)testValidInputs{
    double S0 = 10.0;
    double U = 0.1;
    double D = -0.1;
    double R = 0.05;
    XCTAssertNoThrow(BinomialModel(S0, U, D, R));
}

- (void)testRiskNeutralProb{
    double S0 = 100.0;
    double U = 0.05;
    double D = -0.05;
    double R = 0.0;
    BinomialModel binModel = BinomialModel(S0, U, D, R);
    XCTAssertEqual(binModel.calculateRiskNeutralProbability(), 0.5);
}

- (void)testStockPrice{
    double S0 = 100.0;
    double U = 0.05;
    double D = -0.05;
    double R = 0.0;
    int n = 3;
    int i = 2;
    BinomialModel binModel = BinomialModel(S0, U, D, R);
    XCTAssertEqual(binModel.calculateStockPrice(n, i), 104.7375);
}

- (void)testIllegalOptionsInputs{
    double S0 = 100.0;
    double U = 0.05;
    double D = -0.05;
    double R = 0.0;
    BinomialModel binModel = BinomialModel(S0, U, D, R);
    
    int N = -4;
    double K = 102.0;
    XCTAssertThrows(CallOptionPricer(N, K, binModel));
}

- (void)testCallOptionPrice{
    double S0 = 100.0;
    double U = 0.1;
    double D = -0.1;
    double R = 0.0;
    BinomialModel binModel = BinomialModel(S0, U, D, R);
    
    int N = 15;
    double K = 100.0;
    CallOptionPricer optionsPricer = CallOptionPricer(N, K, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 15.3504, 0.0001);
    XCTAssertEqualWithAccuracy(optionsPricer.priceAnalytic(), 15.3504, 0.0001);
    XCTAssertEqualWithAccuracy(optionsPricer.priceBySnell(), 15.3504, 0.0001);
}

- (void)testPutOptionPrice{
    double S0 = 100.0;
    double U = 0.1;
    double D = -0.1;
    double R = 0.02;
    BinomialModel binModel = BinomialModel(S0, U, D, R);
    
    int N = 15;
    double K = 110.0;
    PutOptionPricer optionsPricer = PutOptionPricer(N, K, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 6.5933, 0.0001);
    XCTAssertEqualWithAccuracy(optionsPricer.priceAnalytic(), 6.5933, 0.0001);
    XCTAssertEqualWithAccuracy(optionsPricer.priceBySnell(), 12.4476, 0.0001);
}

- (void)testDigitalCallOptionPrice{
    double S0 = 100.0;
    double sigma = 0.1;
    double T = 1.0;
    int N = 100;            // num steps
    double r = 0.02;

    BinomialModel binModel = BinomialModel(S0, sigma, T, N, r);
    
    double K = 100.0;
    DigitalCallOptionPricer optionsPricer = DigitalCallOptionPricer(N, K, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 0.5676, 0.0001);
    
    double K2 = 75.0;
    DigitalCallOptionPricer optionsPricer2 = DigitalCallOptionPricer(N, K2, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer2.priceByCRR(), 0.9790, 0.0001);
    
    double K3 = 125.0;
    DigitalCallOptionPricer optionsPricer3 = DigitalCallOptionPricer(N, K3, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer3.priceByCRR(), 0.0221, 0.0001);
}

- (void)testDoubleDigitalOptionPrice{
    double S0 = 100.0;
    double sigma = 0.2;
    double T = 1.0;
    int N = 100;
    double r = 0.02;

    BinomialModel binModel = BinomialModel(S0, sigma, T, N, r);
    
    double lowerBarrier = 75.0;
    double upperBarrier = 125.0;
    DoubleDigitalOptionPricer optionsPricer = DoubleDigitalOptionPricer(N, lowerBarrier, upperBarrier, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 0.7821, 0.0001);
    XCTAssertEqualWithAccuracy(optionsPricer.priceAnalytic(), 0.7821, 0.0001);
    XCTAssertEqualWithAccuracy(optionsPricer.priceBySnell(), 1.0, 0.0001);
}

- (void)testSingleKOBarrierOptionPrice{
    double S0 = 100.0;
    double sigma = 0.2;
    double T = 1.0;
    int N = 10;
    double r = 0.0;

    BinomialModel binModel = BinomialModel(S0, sigma, T, N, r);
    
    double barrier = 80.0;
    KOBarrierOptionPricer optionsPricer = KOBarrierOptionPricer(N, barrier, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 0.7121, 0.0001);
}

- (void)testSingleKIBarrierOptionPrice{
    double S0 = 100.0;
    double sigma = 0.2;
    double T = 1.0;
    int N = 500;
    double r = 0.0;

    BinomialModel binModel = BinomialModel(S0, sigma, T, N, r);
    
    double barrier = 110.0;
    DigitalCallOptionPricer optionsPricer = DigitalCallOptionPricer(N, barrier, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 0.273, 0.001);
    
    // reflection principle
    KIBarrierOptionPricer barrierOptionsPricer = KIBarrierOptionPricer(N, barrier, binModel);
    XCTAssertEqualWithAccuracy(barrierOptionsPricer.priceByCRR(), 2.0 * 0.273, 0.2);
}

- (void)testDoubleKOBarrierOptionPrice{
    double S0 = 100.0;
    double sigma = 0.4;
    double T = 0.5;
    int N = 10;
    double r = 0.02;

    BinomialModel binModel = BinomialModel(S0, sigma, T, N, r);
    
    double lowerBarrier = 50.0;
    double upperBarrier = 150.0;
    KOBarrierOptionPricer optionsPricer = KOBarrierOptionPricer(N, lowerBarrier, upperBarrier, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 0.8699, 0.0001);
}

- (void)testBlackScholesTransition{
    double S0 = 100.0;
    double sigma = 0.1;
    double T = 5.0;
    int N = 100;            // num steps
    double r = 0.02;

    BinomialModel binModel = BinomialModel(S0, sigma, T, N, r);
    
    double K = 100.0;
    CallOptionPricer optionsPricer = CallOptionPricer(N, K, binModel);
    XCTAssertEqualWithAccuracy(optionsPricer.priceByCRR(), 14.07, 0.005); // answer from online calculator
    XCTAssertEqualWithAccuracy(optionsPricer.priceAnalytic(), 14.07, 0.005);
}

@end
