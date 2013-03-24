#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofImage.h"

#define NUM_OF_ITEMS   5

class shelfApp : public ofSimpleApp{

public:

	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
		
	void setupArduino(const int & version);
	void updateArduino();
    

	ofTrueTypeFont		font;
    ofTrueTypeFont		fontSmall;
    
	ofArduino	ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once
    
    enum {
        PRICE = 0,
        CALORIES,
        FATRATE,
        LAST
    };
    int mode;
    
    int threshold;

    
    void initValues();
    
    float item1_price[NUM_OF_ITEMS];
    int item1_calories[NUM_OF_ITEMS];
    int item1_fatrate[NUM_OF_ITEMS];
    
    float item1_price_value0;
    float item1_price_value1;
    float item1_price_value2;
    float item1_price_value3;
    float item1_price_value4;
    
    int item1_calories_value0;
    int item1_calories_value1;
    int item1_calories_value2;
    int item1_calories_value3;
    int item1_calories_value4;
    
    int item1_fatrate_value0;
    int item1_fatrate_value1;
    int item1_fatrate_value2;
    int item1_fatrate_value3;
    int item1_fatrate_value4;
    
    float item2_price[NUM_OF_ITEMS];
    int item2_calories[NUM_OF_ITEMS];
    int item2_fatrate[NUM_OF_ITEMS];
    
    float item2_price_value0;
    float item2_price_value1;
    float item2_price_value2;
    float item2_price_value3;
     float item2_price_value4;
    
    int item2_calories_value0;
    int item2_calories_value1;
    int item2_calories_value2;
    int item2_calories_value3;
    int item2_calories_value4;
    
    int item2_fatrate_value0;
    int item2_fatrate_value1;
    int item2_fatrate_value2;
    int item2_fatrate_value3;
    int item2_fatrate_value4;
    
    float lastTime;
    
    // colors
    ofColor color0;
    ofColor color1;
    ofColor color2;
    ofColor color3;
    ofColor color4;

};

