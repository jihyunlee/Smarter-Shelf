#include "shelfApp.h"


void shelfApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	ofBackground(0,0,0);
    
	font.loadFont("digital7.ttf", 60);
    fontSmall.loadFont("digital7.ttf", 20);
    
    ofSetColor(255,0,0);
    
	ard.connect("/dev/tty.usbmodemfd131", 57600);
	//ard.connect("/dev/ttyUSB0", 57600);
	
	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &shelfApp::setupArduino);

	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
        
    threshold = 300;
    mode = PRICE;
    
    // default framerate = 60
    ofSetFrameRate(45);
    
    
    // ITEM 1: MILK
    
    item1_price[0] = 1.99;
    item1_price[1] = 3.49;
    item1_price[2] = 3.99;
    item1_price[3] = 2.99;
    item1_price[4] = 2.99;
    
    item1_calories[0] = 200;
    item1_calories[1] = 900;
    item1_calories[2] = 378;
    item1_calories[3] = 506;
    item1_calories[4] = 506;
    
    item1_fatrate[0] = 20;
    item1_fatrate[1] = 14;
    item1_fatrate[2] = 40;
    item1_fatrate[3] = 70;
    item1_fatrate[4] = 70;
    
    item1_price_value0 = 0;
    item1_price_value1 = 0;
    item1_price_value2 = 0;
    item1_price_value3 = 0;
    item1_price_value4 = 0;
    
    item1_calories_value0 = 0;
    item1_calories_value1 = 0;
    item1_calories_value2 = 0;
    item1_calories_value3 = 0;
    item1_calories_value4 = 0;
    
    item1_fatrate_value0 = 0;
    item1_fatrate_value1 = 0;
    item1_fatrate_value2 = 0;
    item1_fatrate_value3 = 0;
    item1_fatrate_value4 = 0;
    
    // ITEM 2: RAMEN
    
    item2_price[0] = 1.99;
    item2_price[1] = 2.99;
    item2_price[2] = 2.49;
    item2_price[3] = 2.49;
    item2_price[4] = 2.49;
    
    item2_calories[0] = 200;
    item2_calories[1] = 900;
    item2_calories[2] = 378;
    item2_calories[3] = 378;
    item2_calories[4] = 378;
    
    item2_fatrate[0] = 20;
    item2_fatrate[1] = 14;
    item2_fatrate[2] = 40;
    item2_fatrate[3] = 40;
    item2_fatrate[4] = 40;
    
    item2_price_value0 = 0;
    item2_price_value1 = 0;
    item2_price_value2 = 0;
    item2_price_value3 = 0;
    item2_price_value4 = 0;
    
    item2_calories_value0 = 0;
    item2_calories_value1 = 0;
    item2_calories_value2 = 0;
    item2_calories_value3 = 0;
     item2_calories_value4 = 0;
    
    item2_fatrate_value0 = 0;
    item2_fatrate_value1 = 0;
    item2_fatrate_value2 = 0;
    item2_fatrate_value3 = 0;
    item2_fatrate_value4 = 0;
    
        
    ///////////////////////////////////////////////
    // colors
    
    color0.set(205,26,38);
    color1.set(101,16,40);
    color2.set(205,18,74);
    color3.set(234,144,146);
    color4.set(20,137,68);
    
}

//--------------------------------------------------------------
void shelfApp::update(){

	updateArduino();
}

//--------------------------------------------------------------
void shelfApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &shelfApp::setupArduino);

	// this is where you setup all the pins and pin modes, etc
	for (int i = 0; i < 13; i++){
		ard.sendDigitalPinMode(i, ARD_OUTPUT);
	}

	ard.sendDigitalPinMode(13, ARD_OUTPUT);
	ard.sendAnalogPinReporting(0, ARD_ANALOG);	// AB: report data
	ard.sendDigitalPinMode(11, ARD_PWM);		// on diecimelia: 11 pwm?*/
	
	bSetupArduino = true;
}

//--------------------------------------------------------------
void shelfApp::updateArduino(){
    
	// update the arduino, get any data or messages.
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}
}


//--------------------------------------------------------------
void shelfApp::draw(){
    bool bTest = true;
    
    if(bTest) {
        if(bSetupArduino) {

            // background            
            ofSetColor(160,204,234);
            ofFill();
            ofRect(0,0,ofGetWindowWidth(),140);
            ofRect(0,ofGetScreenHeight()-100-90,ofGetWindowWidth(),140);
            
                        
            ///////////////////////////////////////////////////////
            // Left bar 
            
            int barWidth = 124;
            int barHeight = 28;

            ofSetColor(color0);
            ofFill();
            ofRect(900,0,barWidth,barHeight);
            ofSetColor(0,0,0); 
            fontSmall.drawString("+", 900, barHeight-5);
            
            ofSetColor(color1);
            ofFill();
            ofRect(900,barHeight,barWidth,barHeight);
            ofSetColor(0,0,0); 
            
            ofSetColor(color2);
            ofFill();
            ofRect(900,barHeight*2,barWidth,barHeight);
            ofSetColor(0,0,0); 
            
            ofSetColor(color3);
            ofFill();
            ofRect(900,barHeight*3,barWidth,barHeight);
            ofSetColor(0,0,0); 

            ofSetColor(color4);
            ofFill();
            ofRect(900,barHeight*4,barWidth,barHeight);
            ofSetColor(0,0,0); 
            fontSmall.drawString("-", 900, barHeight*5-5);
            
            
            ///////////////////////////////////////////////////////
            // right side - category area

          
            int upperShelfPosY = 100;
            int lowerShelfPosY = ofGetScreenHeight()-90;
        
            switch(mode) {
                case PRICE: {
                    ofSetColor(0,0,0);
                    fontSmall.drawString("PRICE", 45, 40);
                    font.drawString("$", 30, 110);
                    
                    ofSetFrameRate(25);
                    
                    item1_price_value0 += 0.17;
                    item1_price_value1 += 0.17;
                    item1_price_value2 += 0.17;
                    item1_price_value3 += 0.17;
                    item1_price_value4 += 0.17;
                    
                    if(item1_price_value0 > item1_price[0]) item1_price_value0 = item1_price[0];    
                    if(item1_price_value1 > item1_price[1]) item1_price_value1 = item1_price[1];
                    if(item1_price_value2 > item1_price[2]) item1_price_value2 = item1_price[2];
                    if(item1_price_value3 > item1_price[3]) item1_price_value3 = item1_price[3];
                    if(item1_price_value4 > item1_price[4]) item1_price_value4 = item1_price[4];
     
                    
                    //ofSetColor(255,0,130); // pink
                    char strItem[255];
                    ofSetColor(color0);
                    sprintf(strItem, "  %.2f", item1_price_value0);
                    font.drawString(strItem, 190, upperShelfPosY);
                    ofSetColor(color1);
                    sprintf(strItem, "  %.2f", item1_price_value1);
                    font.drawString(strItem, 340, upperShelfPosY);
                    ofSetColor(color2);
                    sprintf(strItem, "  %.2f", item1_price_value2);
                    font.drawString(strItem, 500, upperShelfPosY);
                    ofSetColor(color3);
                    sprintf(strItem, "  %.2f", item1_price_value3);
                    font.drawString(strItem, 660, upperShelfPosY);
                    ofSetColor(color4);
                    sprintf(strItem, "  %.2f", item1_price_value4);
                    font.drawString(strItem, 820, upperShelfPosY);                    
 

                    ofSetColor(color0);
                    sprintf(strItem, "  %.2f", item2_price_value0);
                    font.drawString(strItem, 190, lowerShelfPosY);
                    ofSetColor(color1);
                    sprintf(strItem, "  %.2f", item2_price_value1);
                    font.drawString(strItem, 340, lowerShelfPosY);
                    ofSetColor(color2);
                    sprintf(strItem, "  %.2f", item2_price_value2);
                    font.drawString(strItem, 500, lowerShelfPosY);
                    ofSetColor(color3);
                    sprintf(strItem, "  %.2f", item2_price_value3);
                    font.drawString(strItem, 660, lowerShelfPosY);
                    ofSetColor(color4);
                    sprintf(strItem, "  %.2f", item2_price_value4);
                    font.drawString(strItem, 820, lowerShelfPosY);           
                } break;
                    
                case CALORIES: {
                    ofSetColor(0,0,0);
                    fontSmall.drawString("CALORIES", 40, 35);
                    font.drawString("kcal", 30, 100);

                    ofSetFrameRate(60);
                    
                    item1_calories_value0 += 8;
                    item1_calories_value1 += 8;
                    item1_calories_value2 += 8;
                    item1_calories_value3 += 8;
                    item1_calories_value4 += 8;
                    
                    if(item1_calories_value0 > item1_calories[0]) item1_calories_value0 = item1_calories[0];
                    if(item1_calories_value1 > item1_calories[1]) item1_calories_value1 = item1_calories[1];
                    if(item1_calories_value2 > item1_calories[2]) item1_calories_value2 = item1_calories[2];
                    if(item1_calories_value3 > item1_calories[3]) item1_calories_value3 = item1_calories[3];
                    if(item1_calories_value4 > item1_calories[4]) item1_calories_value4 = item1_calories[4];
                    
                    char strItem[255];
                    ofSetColor(color0);
                    sprintf(strItem, "  %d", item1_calories_value0);
                    font.drawString(strItem, 160, upperShelfPosY);
                    ofSetColor(color1);
                    sprintf(strItem, "  %d", item1_calories_value1);
                    font.drawString(strItem, 320, upperShelfPosY);
                    ofSetColor(color2);
                    sprintf(strItem, "  %d", item1_calories_value2);
                    font.drawString(strItem, 420, upperShelfPosY);
                    ofSetColor(color3);
                    sprintf(strItem, "  %d", item1_calories_value3);
                    font.drawString(strItem, 580, upperShelfPosY);
                    ofSetColor(color4);
                    sprintf(strItem, "  %d", item1_calories_value4);
                    font.drawString(strItem, 740, upperShelfPosY);                                  
                                        
                    ofSetColor(color0);
                    sprintf(strItem, "  %d", item2_calories_value0);
                    font.drawString(strItem, 160, lowerShelfPosY);
                    ofSetColor(color1);
                    sprintf(strItem, "  %d", item2_calories_value1);
                    font.drawString(strItem, 320, lowerShelfPosY);
                    ofSetColor(color2);
                    sprintf(strItem, "  %d", item2_calories_value2);
                    font.drawString(strItem, 420, lowerShelfPosY);
                    ofSetColor(color3);
                    sprintf(strItem, "  %d", item2_calories_value3);
                    font.drawString(strItem, 580, lowerShelfPosY);
                    ofSetColor(color4);
                    sprintf(strItem, "  %d", item2_calories_value4);
                    font.drawString(strItem, 740, lowerShelfPosY);                                  

                } break;
                    
                case FATRATE: {
                    ofSetColor(0,0,0);
                    fontSmall.drawString("FAT", barWidth+40, 40);
                    font.drawString("%", barWidth+50, 110);

                    ofSetFrameRate(30);
                    
                    item1_fatrate_value0 += 1;
                    item1_fatrate_value1 += 1;
                    item1_fatrate_value2 += 1;
                    item1_fatrate_value3 += 1;
                    item1_fatrate_value4 += 1;
                    
                    if(item1_fatrate_value0 > item1_fatrate[0]) item1_fatrate_value0 = item1_fatrate[0];
                    if(item1_fatrate_value1 > item1_fatrate[1]) item1_fatrate_value1 = item1_fatrate[1];
                    if(item1_fatrate_value2 > item1_fatrate[2]) item1_fatrate_value2 = item1_fatrate[2];
                    if(item1_fatrate_value3 > item1_fatrate[3]) item1_fatrate_value3 = item1_fatrate[3];
                    if(item1_fatrate_value4 > item1_fatrate[4]) item1_fatrate_value4 = item1_fatrate[4];
                   
                    char strItem[255];
                    ofSetColor(color3);
                    sprintf(strItem, "   %d", item1_fatrate_value0);
                    font.drawString(strItem, 190, upperShelfPosY);
                    ofSetColor(color1);
                    sprintf(strItem, "   %d", item1_fatrate_value1);
                    font.drawString(strItem, 340, upperShelfPosY);
                    ofSetColor(color0);
                    sprintf(strItem, "   %d", item1_fatrate_value2);
                    font.drawString(strItem, 500, upperShelfPosY);
                    ofSetColor(color2);
                    sprintf(strItem, "   %d", item1_fatrate_value3);
                    font.drawString(strItem, 660, upperShelfPosY);
                    ofSetColor(color4);
                    sprintf(strItem, "   %d", item1_fatrate_value4);
                    font.drawString(strItem, 820, upperShelfPosY);             
                    
                    ofSetColor(color3);
                    sprintf(strItem, "   %d", item2_fatrate_value0);
                    font.drawString(strItem, 190, lowerShelfPosY);
                    ofSetColor(color1);
                    sprintf(strItem, "   %d", item2_fatrate_value1);
                    font.drawString(strItem, 340, lowerShelfPosY);
                    ofSetColor(color0);
                    sprintf(strItem, "   %d", item2_fatrate_value2);
                    font.drawString(strItem, 500, lowerShelfPosY);
                    ofSetColor(color2);
                    sprintf(strItem, "   %d", item2_fatrate_value3);
                    font.drawString(strItem, 660, lowerShelfPosY);
                    ofSetColor(color4);
                    sprintf(strItem, "   %d", item2_fatrate_value4);
                    font.drawString(strItem, 820, lowerShelfPosY);                         
                } break;
                    
            } // end of switch
            
            
//            printf("Analog Value: %d\n", ard.getAnalog(0));
            if(ard.getAnalog(0) > threshold) {               
                if(ofGetSystemTime() - lastTime > 2000) {
//                    printf(" mode CHANGED \n");                    
                    initValues();
                    
                    lastTime = ofGetSystemTime();
                    
                    mode++;
                    if(mode == LAST)
                        mode = PRICE;                    
                }
            }
        }
        
        return;
    }

	if (!bSetupArduino){
		font.drawString("arduino not ready\n", 545, 40);       
	} else {
		font.drawString("analog pin 0: " + ofToString(ard.getAnalog(0)), 545, 80);
	}
}

void shelfApp::initValues()
{
    item1_price_value0 = 0;
    item1_price_value1 = 0;
    item1_price_value2 = 0;
    item1_price_value3 = 0;
    item1_price_value4 = 0;
    
    item1_calories_value0 = 0;
    item1_calories_value1 = 0;
    item1_calories_value2 = 0;
    item1_calories_value3 = 0;
    item1_calories_value4 = 0;
    
    item1_fatrate_value0 = 0;
    item1_fatrate_value1 = 0;
    item1_fatrate_value2 = 0;  
    item1_fatrate_value3 = 0;  
    item1_fatrate_value4 = 0; 
 
    item2_price_value0 = 0;
    item2_price_value1 = 0;
    item2_price_value2 = 0;
    item2_price_value3 = 0;
    item2_price_value4 = 0;
    
    item2_calories_value0 = 0;
    item2_calories_value1 = 0;
    item2_calories_value2 = 0;
    item2_calories_value3 = 0;
    item2_calories_value4 = 0;
    
    item2_fatrate_value0 = 0;
    item2_fatrate_value1 = 0;
    item2_fatrate_value2 = 0;
    item2_fatrate_value3 = 0;
    item2_fatrate_value4 = 0;

}

//--------------------------------------------------------------
void shelfApp::mousePressed(int x, int y, int button){
	ard.sendDigital(13, ARD_HIGH);
}

//--------------------------------------------------------------
void shelfApp::mouseReleased(int x, int y, int button){
	ard.sendDigital(13, ARD_LOW);
}

