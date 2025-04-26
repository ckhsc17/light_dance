#include <FastLED.h>

// 第三首歌--舞者編號
// 1號 花花
// 2號 徐舒庭
// 3號 小米
// 4號 許晉誠
// 5號 蔡冠毅
// 6號 蔡仁瑋
// 7號 蔡承佑
const int DANCER = 1;

// LED 燈條設定
#define LED_PIN 4             // LED 燈條 Data Pin (可改成你的 GPIO)
#define NUM_LEDS 1000           // LED 顆數（請根據你的 LED 燈條數量設定）
#define BRIGHTNESS 10        // 亮度 (0~255)
#define LED_TYPE WS2812       // 燈條類型
#define COLOR_ORDER GRB       // 顏色順序 整首隨機淺色亮色系

CRGB leds[NUM_LEDS];

// **BPM_3 拍子設定**
#define BPM_3 125
#define BEAT_TIME_3 (60000 / BPM_3)  // 每拍時間 (毫秒)

#pragma region BodyPart definition
 
// 定義部位
struct LedRange { // 注意是 start 跟 **length**
  int start;
  int length;
};
 
struct BodyPart {
  const LedRange* ranges;
  int numRanges;
};
 
// === HEAD ===
const LedRange hatRanges[] = { {182, 131} }; // 整個帽子
const LedRange hatMarkRanges[] = { {280, 28} }; // 帽子上的圈圈
BodyPart hat = {hatRanges, 1};
BodyPart hatMark = {hatMarkRanges, 1};

// === SHIRT === // 不包含袖子
const LedRange lowerShirtRanges[] = { {0, 62} }; 
const LedRange leftZipperRanges[] = { {62, 30} };
const LedRange collarRanges[] = { {92, 90} };
const LedRange rightZipperRanges[] = { {313, 30} };
const LedRange shirtRanges[] = {lowerShirtRanges[0], collarRanges[0], leftZipperRanges[0], rightZipperRanges[0]};

BodyPart lowerShirt = {lowerShirtRanges, 1};
BodyPart leftZipper = {leftZipperRanges, 1};
BodyPart collar = {collarRanges, 1};
BodyPart rightZipper = {rightZipperRanges, 1};
BodyPart shirt = {shirtRanges, 4}; 

// === ARMS === // 袖子
const LedRange leftUpperArmRanges[] = { {505, 60} }; // Upper 包含袖口
const LedRange leftLowerArmRanges[] = { {626, 41} };
const LedRange rightUpperArmRanges[] = { {445, 60} }; // Upper 包含袖口
const LedRange rightLowerArmRanges[] = { {343, 41} };
const LedRange leftArmRanges[] = {leftUpperArmRanges[0], leftLowerArmRanges[0]}; // Upper 包含袖口
const LedRange rightArmRanges[] = {rightUpperArmRanges[0], rightLowerArmRanges[0]}; // Upper 包含袖口
const LedRange armsRanges[] = {leftUpperArmRanges[0], rightUpperArmRanges[0], leftLowerArmRanges[0], rightLowerArmRanges[0] };
BodyPart leftUpperArm = {leftUpperArmRanges, 1};
BodyPart leftLowerArm = {leftLowerArmRanges, 1};
BodyPart rightUpperArm = {rightUpperArmRanges, 1};
BodyPart rightLowerArm = {rightLowerArmRanges, 1};
BodyPart leftArm = {leftArmRanges, 2};
BodyPart rightArm = {rightArmRanges, 2};
BodyPart arms = {armsRanges, 4};

// === BODY === 衣服+袖子
const LedRange bodyRanges[] = {lowerShirtRanges[0], collarRanges[0], leftZipperRanges[0], rightZipperRanges[0] , leftUpperArmRanges[0], rightUpperArmRanges[0], leftLowerArmRanges[0], rightLowerArmRanges[0] };
BodyPart body = {bodyRanges, 8};

// === HANDS ===
const LedRange leftHandRanges[] = { {565, 61} };
const LedRange rightHandRanges[] = { {384, 61} };
const LedRange handsRanges[] = {leftHandRanges[0], rightHandRanges[0] };
BodyPart leftHand = {leftHandRanges, 1};
BodyPart rightHand = {rightHandRanges, 1};
BodyPart hands = {handsRanges, 2};

// === LEGS ===
const LedRange leftLegRanges[] = { {667, 52} };
const LedRange rightLegRanges[] = { {855, 52} };
const LedRange leftCrotchRanges[] = { {749, 38} };
const LedRange rightCrotchRanges[] = { {787, 38} };
const LedRange crotchRanges[] = {leftCrotchRanges[0], rightCrotchRanges[0] };
const LedRange legsRanges[] = {leftLegRanges[0], rightLegRanges[0], leftCrotchRanges[0], rightCrotchRanges[0] };
BodyPart leftLeg = {leftLegRanges, 1};
BodyPart rightLeg = {rightLegRanges, 1};
BodyPart leftCrotch = {leftCrotchRanges, 1};
BodyPart rightCrotch = {rightCrotchRanges, 1};
BodyPart crotch = {crotchRanges, 1};
BodyPart legs = {legsRanges, 4};

// === FEET ===
const LedRange leftFootRanges[] = { {719, 30} };
const LedRange rightFootRanges[] = { {825, 30} };
const LedRange feetRanges[] = {leftFootRanges[0], rightFootRanges[0] };
BodyPart leftFoot = {leftFootRanges, 1};
BodyPart rightFoot = {rightFootRanges, 1};
BodyPart feet = {feetRanges, 2};

#pragma endregion

#pragma region Color definition

struct ColorSet {
  // HAT
  CRGB hat        = CRGB::Black;
  CRGB hatMark    = CRGB::Black;

  // SHIRT
  CRGB lowerShirt     = CRGB::Black;
  CRGB leftZipper     = CRGB::Black;
  CRGB rightZipper    = CRGB::Black;
  CRGB collar         = CRGB::Black;
  CRGB leftShirt      = CRGB::Black;
  CRGB rightShirt     = CRGB::Black;
  CRGB shirt          = CRGB::Black;

  // ARMS
  CRGB leftUpperArm   = CRGB::Black;
  CRGB leftLowerArm   = CRGB::Black;
  CRGB rightUpperArm  = CRGB::Black;
  CRGB rightLowerArm  = CRGB::Black;
  CRGB leftArm        = CRGB::Black;
  CRGB rightArm       = CRGB::Black;
  CRGB arms           = CRGB::Black;

  // HANDS
  CRGB leftHand       = CRGB::Black;
  CRGB rightHand      = CRGB::Black;
  CRGB hands          = CRGB::Black;

  // BODY (shirt + arms)
  CRGB body           = CRGB::Black;

  // LEGS
  CRGB leftLeg        = CRGB::Black;
  CRGB rightLeg       = CRGB::Black;
  CRGB leftCrotch     = CRGB::Black;
  CRGB rightCrotch    = CRGB::Black;
  CRGB crotch         = CRGB::Black;
  CRGB legs           = CRGB::Black;

  // FEET
  CRGB leftFoot       = CRGB::Black;
  CRGB rightFoot      = CRGB::Black;
  CRGB feet           = CRGB::Black;
};
 
 
// 第一首顏色
#define RED_1 CRGB(253, 4, 10)
#define PURPLE_1 CRGB(221, 47, 247)
#define YELLOW_1 CRGB(253, 220, 6)
#define WHITE_1 CRGB(255, 255, 255)
 
const ColorSet COLORSET_1 = []() {
  ColorSet c;
  c.feet = PURPLE_1;
  c.legs = WHITE_1;
  c.body = RED_1;
  c.hat = PURPLE_1;
  c.hands = PURPLE_1;
  return c;
}();
 
// 第二首顏色
// 那時候沒討論色碼QQ
 
// 第三首顏色
#define RED_3 CRGB(255, 10, 10) 
#define YELLOW_3 CRGB(255, 230, 25)
#define GREEN_3 CRGB(10, 255, 10)
#define BLUE_3 CRGB(10, 10, 255)
#define ORANGE_3 CRGB(255, 55, 5)
#define WHITE_3 CRGB(255, 255, 255)
#define PINK_3 CRGB(255, 100, 100)
#define LIGHT_GREEN_3 CRGB(100, 255, 100)
#define LIGHT_BLUE_3 CRGB(100, 100, 255)
#define LIGHT_YELLOW_3 CRGB(255, 255, 100)
#define SKY_BLUE_3 CRGB(100, 255, 255)
#define LIGHT_PURPLE_3 CRGB(255, 100, 255)

const ColorSet COLORSET_3_1_1 = []() { // 第三首歌-第一套顏色 淺綠衣服、淺藍褲子、淺黃配件
  ColorSet c;
  c.feet = YELLOW_3;
  c.legs = LIGHT_BLUE_3;
  c.body = LIGHT_GREEN_3;
  c.hat = LIGHT_YELLOW_3;
  c.hands = LIGHT_YELLOW_3;
  return c;
}();

const ColorSet COLORSET_3_1_2 = []() { // 第三首歌-第一套顏色 天空藍衣服、粉紅褲子、淺黃配件
  ColorSet c;
  c.feet = YELLOW_3;
  c.legs = PINK_3;
  c.body = SKY_BLUE_3;
  c.hat = LIGHT_YELLOW_3;
  c.hands = LIGHT_YELLOW_3;
  return c;
}();

const ColorSet COLORSET_3_2 = []() { // 第三首歌-第二套顏色(黃色+綠色)
  ColorSet c;
  c.feet = WHITE_3;
  c.legs = LIGHT_GREEN_3;
  c.body = YELLOW_3;
  c.hat = LIGHT_YELLOW_3;
  c.hands = WHITE_3;
  c.lowerShirt = GREEN_3;
  c.hatMark = GREEN_3;
  return c;
}();

const ColorSet COLORSET_3_3 = []() { // 第三首歌-第三套顏色(紅色+白色)
  ColorSet c;
  c.feet = RED_3;  // 紅色鞋子
  c.legs = WHITE_3;
  c.body = RED_3;  // 紅色衣服
  c.hat = WHITE_3;
  c.hands = WHITE_3;
  c.lowerShirt = WHITE_3;
  c.leftLowerArm = WHITE_3;
  c.rightLowerArm = WHITE_3;
  c.collar = WHITE_3;
  c.hatMark = RED_3;
  return c;
}();

ColorSet whiteAndColorSet(CRGB color) { // 白色、指定顏色（衣服、帽子標誌）
  ColorSet c;
  c.feet = color;
  c.legs = WHITE_3;
  c.body = color;
  c.hat = WHITE_3;
  c.hands = WHITE_3;
  c.hatMark = color;
  return c;
}
 
#pragma endregion
 
 
/*
  要讓 LED 亮起來有三個步驟： 1. 填入顏色，也就是 fillBodyPart() 或是 fillColorSet() 2. 顯示顏色，也就是 FastLED.show() 3. 等待時間，也就是 delay()
  注意在 FastLED.show() 之前先把所有顏色填好，否則會有明顯的延遲。
  showBodyPartForBeats() 或是 showColorSetForBeats() 是結合這三個步驟的函式。
*/
 
void fillBodyPart(BodyPart part, CRGB color) {
  for (int i = 0; i < part.numRanges; i++) {
    fill_solid(&leds[part.ranges[i].start], part.ranges[i].length, color);
  }
}
 
void showBodyPartForBeats(BodyPart part, CRGB color, int beat_time){
  fillBodyPart(part, color);
  FastLED.show();
  delay(beat_time);
}
 
void fillColorSet(const ColorSet& color) {
  // === HAT ===
if (color.hat != CRGB::Black) fillBodyPart(hat, color.hat);
if (color.hatMark != CRGB::Black) fillBodyPart(hatMark, color.hatMark);

// === BODY ===
if (color.body != CRGB::Black) fillBodyPart(body, color.body);

// === SHIRT === // 
if (color.shirt != CRGB::Black) fillBodyPart(shirt, color.shirt);
if (color.collar != CRGB::Black) fillBodyPart(collar, color.collar);
if (color.lowerShirt != CRGB::Black) fillBodyPart(lowerShirt, color.lowerShirt);
if (color.leftZipper != CRGB::Black) fillBodyPart(leftZipper, color.leftZipper);
if (color.rightZipper != CRGB::Black) fillBodyPart(rightZipper, color.rightZipper);

// === ARMS ===
if (color.arms != CRGB::Black) fillBodyPart(arms, color.arms);
if (color.rightArm != CRGB::Black) fillBodyPart(rightArm, color.rightArm);
if (color.leftArm != CRGB::Black) fillBodyPart(leftArm, color.leftArm);
if (color.rightLowerArm != CRGB::Black) fillBodyPart(rightLowerArm, color.rightLowerArm);
if (color.rightUpperArm != CRGB::Black) fillBodyPart(rightUpperArm, color.rightUpperArm);
if (color.leftLowerArm != CRGB::Black) fillBodyPart(leftLowerArm, color.leftLowerArm);
if (color.leftUpperArm != CRGB::Black) fillBodyPart(leftUpperArm, color.leftUpperArm);

// === HANDS ===
if (color.hands != CRGB::Black) fillBodyPart(hands, color.hands);
if (color.leftHand != CRGB::Black) fillBodyPart(leftHand, color.leftHand);
if (color.rightHand != CRGB::Black) fillBodyPart(rightHand, color.rightHand);

// === LEGS ===
if (color.legs != CRGB::Black) fillBodyPart(legs, color.legs);
if (color.crotch != CRGB::Black) fillBodyPart(crotch, color.crotch);
if (color.leftCrotch != CRGB::Black) fillBodyPart(leftCrotch, color.leftCrotch);
if (color.rightCrotch != CRGB::Black) fillBodyPart(rightCrotch, color.rightCrotch);
if (color.leftLeg != CRGB::Black) fillBodyPart(leftLeg, color.leftLeg); // No Crotch
if (color.rightLeg != CRGB::Black) fillBodyPart(rightLeg, color.rightLeg); // No Crotch

// === FEET ===
if (color.feet != CRGB::Black) fillBodyPart(feet, color.feet);
if (color.leftFoot != CRGB::Black) fillBodyPart(leftFoot, color.leftFoot);
if (color.rightFoot != CRGB::Black) fillBodyPart(rightFoot, color.rightFoot);
}

void fillBlack() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
}
 
void showColorSetForBeats(const ColorSet& color, int beat_time) {
  fillColorSet(color);
  FastLED.show();
  delay(beat_time);
}
 
// Simple Light showing for whole LED strip
void showLightforBeats(CRGB color, int beat_time){
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(beat_time);
}
 
// Smooth rainbow showing for whole LED strip
void rainbowAllLeds(int duration, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t sat = 255, uint8_t val = 255) {
  const int steps = 256;
  unsigned long startTime = millis();
  unsigned long endTime = startTime + duration;

  for (int frame = 0; frame < steps; frame++) {
    unsigned long currentTime = millis();
    if (currentTime >= endTime) break;

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(startHue + frame + i * hueStep, sat, val);
    }

    FastLED.show();

    // Wait until the right time for the next frame
    unsigned long targetTime = startTime + ((unsigned long)duration * frame / steps);
    while (millis() < targetTime) {
      // Just wait without wasting CPU
      delay(1);
    }
  }
}

void rainbowBodyPart(const BodyPart& part, int duration, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t sat = 255, uint8_t val = 255) {
 const int steps = 256;
 unsigned long startTime = millis();
 unsigned long endTime = startTime + duration;
  
 for (int frame = 0; frame < steps; frame++) {
   unsigned long currentTime = millis();
   if (currentTime >= endTime) break;
  
   for (int r = 0; r < part.numRanges; r++) {
    const LedRange& range = part.ranges[r];
    for (int i = 0; i < range.length; i++) {
      int ledIndex = range.start + i;
      leds[ledIndex] = CHSV(startHue + frame + i * hueStep, sat, val);
    }
   }
  
   FastLED.show();
  
   unsigned long targetTime = startTime + ((unsigned long)duration * frame / steps);
   while (millis() < targetTime) {
    delay(1);
   }
  }
}

void rainbowMultipleBodyParts(const BodyPart parts[], int numParts, int duration, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t sat = 255, uint8_t val = 255) {
    const int steps = 256;
    unsigned long startTime = millis();
    unsigned long endTime = startTime + duration;
    
    for (int frame = 0; frame < steps; frame++) {
        unsigned long currentTime = millis();
        if (currentTime >= endTime) break;
        
        // 先清除所有LED（可選，看需求是否要先清除）
        // fill_solid(leds, NUM_LEDS, CRGB::Black);
        
        // 對每個身體部位應用彩虹效果
        for (int p = 0; p < numParts; p++) {
            const BodyPart& part = parts[p];
            for (int r = 0; r < part.numRanges; r++) {
                const LedRange& range = part.ranges[r];
                for (int i = 0; i < range.length; i++) {
                    int ledIndex = range.start + i;
                    leds[ledIndex] = CHSV(startHue + frame + i * hueStep, sat, val);
                }
            }
        }
        
        FastLED.show();
        
        unsigned long targetTime = startTime + ((unsigned long)duration * frame / steps);
        while (millis() < targetTime) {
            delay(1);
        }
    }
}


void setup() {
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();

    Serial.println("What Makes You Beautiful 開始！");

    // test color
    rainbowAllLeds(5000, 0, 2, 100, 250); // duration, startHue, hueStep, sat, val
    showColorSetForBeats(COLORSET_3_1_1, 8000);
    showColorSetForBeats(COLORSET_3_1_2, 8000);
    showColorSetForBeats(COLORSET_3_2, 8000);
    showColorSetForBeats(COLORSET_3_3, 8000);
    showColorSetForBeats(whiteAndColorSet(ORANGE_3), 8000);

    playIntro(); // 前奏

    playMain1();
    playMain5();
    playMain9();
    playMain13();
    playMain17();
    playMain21();
    playMain25();
    
    playMain29(); // 尾奏
    

    stopEffect();
}


// **前奏** 七個人站定位擺pose 對拍隨機亮
void playIntro() {
    Serial.println("🎵 Intro 1");
    for (int beat = 1; beat <= 1; beat++) { // Bar 1
        // 亮燈
        if(DANCER == 5){ // 5號 蔡冠毅
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if(DANCER == 5){ // 5號 蔡冠毅
            fill_solid(leds, NUM_LEDS, LIGHT_BLUE_3); // 亮藍色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_PURPLE_3); // 亮紫色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Intro 2");
    for (int beat = 2; beat <= 2; beat++) { // Bar 2
        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, PINK_3); // 亮粉色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if(DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, SKY_BLUE_3); // 亮天藍色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if(DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, LIGHT_PURPLE_3); // 亮紫色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if(DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, PINK_3); // 亮粉色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Intro 3");
    for (int beat = 3; beat <= 3; beat++) { // Bar 3
        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2){ // 2號 徐舒庭
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if(DANCER == 2){ // 2號 徐舒庭
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 3){ // 3號 小米
            fill_solid(leds, NUM_LEDS, LIGHT_BLUE_3); // 亮藍色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if(DANCER == 3){ // 3號 小米
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Intro 4");
    for (int beat = 4; beat <= 4; beat++) { // Bar 4
        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // 熄燈(蔡仁瑋)
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈(蔡仁瑋)
        if(DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
        
        // 熄燈(蔡仁瑋)
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈(蔡仁瑋)
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // You're
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2){ // 2號 徐舒庭
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // in-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // -se-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
}

// **第一段**
void playMain1() {
    Serial.println("🎵 Main 1");
    for (int beat = 1; beat <= 1; beat++) { // Bar 1
        // -cure ~~
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 7){ // 7號 蔡承佑
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(5 * BEAT_TIME_3 / 2);   

        // Don't
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 3){ // 3號 小米
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // know
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // what
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2){ // 2號 徐舒庭
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 2");
    for (int beat = 2; beat <= 2; beat++) { // Bar 2
        // for ~~
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(5 * BEAT_TIME_3 / 2);   

        // You're
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2){ // 2號 徐舒庭
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // turn-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // -ning
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 3");
    for (int beat = 3; beat <= 3; beat++) { // Bar 3
        // heads
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3);   

        // when
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // you
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // walk
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3);   

        // through
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // the
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 4");
    for (int beat = 4; beat <= 4; beat++) { // Bar 4
        // do-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // -o-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // -or
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 2 or DANCER == 3){ // 1號 花花 or 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 6 or DANCER == 7){ // 1號 花花 or 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);  

        // Don't
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // need
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);    

        // make
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);    
    }
}

// **第五段**
void playMain5() {
    Serial.println("🎵 Main 5");
    for (int beat = 5; beat <= 5; beat++) { // Bar 5
        // up
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(5 * BEAT_TIME_3 / 2);  

        // To
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // co-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);    

        // -ver
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);    
    }
    Serial.println("🎵 Main 6");
    for (int beat = 6; beat <= 6; beat++) { // Bar 6
        // up
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(5 * BEAT_TIME_3 / 2);   

        // be-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // ing
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // the
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 7");
    for (int beat = 7; beat <= 7; beat++) { // Bar 7
        // way
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3);   

        // that
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // you
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // are
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3);   

        // is
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // e-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 8");
    for (int beat = 8; beat <= 8; beat++) { // Bar 8
        // -nough
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // -ou-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);   

        // -ough
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 2);   

    }
}

// **第九段**
void playMain9() {
    Serial.println("🎵 Main 9");
    for (int beat = 9; beat <= 9; beat++) { // Bar 9
        // every one else in the
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();
            
            rainbowBodyPart(feet, 4 * BEAT_TIME_3, 0, 2, 120);
        } else {
            FastLED.show();
            delay(4 * BEAT_TIME_3);
        }
    }
    Serial.println("🎵 Main 10");
    for (int beat = 10; beat <= 10; beat++) { // Bar 10
        // room can see it
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();
            
            BodyPart rainbowParts[] = {feet, legs};
            rainbowMultipleBodyParts(rainbowParts, 2, 4 * BEAT_TIME_3, 0, 2, 120);

        } else {
            FastLED.show();
            delay(4 * BEAT_TIME_3);
        }
    }
    Serial.println("🎵 Main 11");
    for (int beat = 11; beat <= 11; beat++) { // Bar 11
        // every one
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();

            BodyPart rainbowParts[] = {feet, legs, hands};
            rainbowMultipleBodyParts(rainbowParts, 3, 2 * BEAT_TIME_3, 0, 2, 120);
            
        } else {
            FastLED.show();
            delay(2 * BEAT_TIME_3);
        }


        // else but
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();

            BodyPart rainbowParts[] = {feet, legs, hands, hat};
            rainbowMultipleBodyParts(rainbowParts, 4, 2 * BEAT_TIME_3, 0, 2, 120);
            
        } else {
            FastLED.show();
            delay(2 * BEAT_TIME_3);
        }
    }
    Serial.println("🎵 Main 12");
    for (int beat = 12; beat <= 12; beat++) { // Bar 12
        // you
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();
            
            rainbowAllLeds(5 * BEAT_TIME_3, 0, 2, 120);
        } else {
            FastLED.show();
            delay(5 * BEAT_TIME_3 / 2);
        }

        // Ba-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // -by
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 3){ // 3號 小米
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // you
        fillColorSet(COLORSET_3_2);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

    }
}

// **第13段-副歌**
void playMain13() {
    Serial.println("🎵 Main 13");
    for (int beat = 13; beat <= 13; beat++) { // Bar 13
        // light up
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3);

        // my world
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if(DANCER == 6 or DANCER == 4){ // 6號 蔡仁瑋 or 4號 許晉誠
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3);

        // like
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if(DANCER == 6 or DANCER == 4 or DANCER == 1){ // 6號 蔡仁瑋 or 4號 許晉誠 or 1號 花花
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3);

        // no
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if(DANCER == 6 or DANCER == 4 or DANCER == 1 or DANCER == 5){ // 6號 蔡仁瑋 or 4號 許晉誠 or 1號 花花 or 5號 蔡冠毅
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3);

    }
    Serial.println("🎵 Main 14");
    for (int beat = 14; beat <= 14; beat++) { // Bar 14
        // -bo-
        fillColorSet(whiteAndColorSet(GREEN_3));
        FastLED.show();
        delay(BEAT_TIME_3);

        // -dy else
        // 1/7 1/7 1/7 1/7 1/7 1/7 1/7 閃電！！！！！！！！！！
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 7 or DANCER == 3){ // 7號 蔡承佑 or 3號 小米
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 5 or DANCER == 7){ // 5號 蔡冠毅 or 7號 蔡承佑
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1 or DANCER == 5){ // 1號 花花 or 5號 蔡冠毅
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 4 or DANCER == 1){ // 4號 許晉誠 or 1號 花花
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6 or DANCER == 4){ // 6號 蔡仁瑋 or 4號 許晉誠
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2 or DANCER == 6){ // 2號 徐舒庭 or 4號 許晉誠
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 7 );

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(body, ORANGE_3);
            fillBodyPart(hands, ORANGE_3);
            fillBodyPart(legs, ORANGE_3);
            fillBodyPart(feet, ORANGE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 3 );

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(body, ORANGE_3);
            fillBodyPart(hands, ORANGE_3);
            fillBodyPart(legs, ORANGE_3);
            fillBodyPart(feet, ORANGE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 3 );

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 4){ // 4號 許晉誠
            fillBodyPart(body, ORANGE_3);
            fillBodyPart(hands, ORANGE_3);
            fillBodyPart(legs, ORANGE_3);
            fillBodyPart(feet, ORANGE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 3 );

        // way
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fillBodyPart(hands, ORANGE_3);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);
    }

    Serial.println("🎵 Main 15");
    for (int beat = 15; beat <= 15; beat++) { // Bar 15
        // you flip your
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if(DANCER == 4){ // 4號 許晉誠
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if(DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3);

        // hair get me
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if(DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if(DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if(DANCER == 3){ // 3號 小米
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        delay(BEAT_TIME_3);
        
    }
    Serial.println("🎵 Main 16");
    for (int beat = 16; beat <= 16; beat++) { // Bar 16
        // overwhelmed
        fillBodyPart(legs, WHITE_3);
        fillBodyPart(feet, WHITE_3);
        FastLED.show();
        delay(BEAT_TIME_3);

        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        delay(BEAT_TIME_3);

        fillBodyPart(arms, WHITE_3);
        fillBodyPart(hat, WHITE_3);
        FastLED.show();
        delay(BEAT_TIME_3);

        // But when you
        fill_solid(leds, NUM_LEDS, WHITE_3);
        FastLED.show();
        delay(BEAT_TIME_3);

// current progress ------------------------------------------------------------

    }
}

// **第17段-副歌**
void playMain17() {
    Serial.println("🎵 Main 17");
    for (int beat = 17; beat <= 17; beat++) { // Bar 17
        // smile
        fillBodyPart(rightArm, RED_3);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // at
        fillBodyPart(rightHand, PINK_3);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // the
        delay(BEAT_TIME_3 / 2);

        // ground
        fillBodyPart(leftArm, RED_3);
        fillBodyPart(leftHand, PINK_3);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // it
        fillBodyPart(leftLeg, PINK_3);
        fillBodyPart(rightLeg, PINK_3);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // aint
        fillBodyPart(feet, RED_3);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 18");
    for (int beat = 18; beat <= 18; beat++) { // Bar 18
        // hard to
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 3){ // 3號 小米
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 1){ // 1號 花花
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 4){ // 4號 許晉誠
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if(DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        fillBodyPart(feet, RED_3);
        if(DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if(DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if(DANCER == 4){ // 4號 許晉誠
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if(DANCER == 1){ // 1號 花花
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if(DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if(DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if(DANCER == 3){ // 3號 小米
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4 / 7);
        
        

        // tell.
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 4 or DANCER == 5){ // 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);

        // You
        delay(BEAT_TIME_3 / 2);

        // don't
        delay(2 * BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 19");
    for (int beat = 19; beat <= 19; beat++) { // Bar 19
        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 4 or DANCER == 5){ // 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);


        // know
        delay(BEAT_TIME_3);

        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 4 or DANCER == 5){ // 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);
        if(DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 4);

        delay(BEAT_TIME_3);
    }
    Serial.println("🎵 Main 20");
    for (int beat = 20; beat <= 20; beat++) { // Bar 20
        // You don't know you're bu...
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(5 *BEAT_TIME_3 / 2);

        // Ba-
        if(DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // -by
        if(DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // you
        if(DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

    }
}

// **第21段-副歌**
void playMain21() {
    Serial.println("🎵 Main 21");
    for (int beat = 21; beat <= 21; beat++) { // Bar 21
        // light
        fillColorSet(whiteAndColorSet(CRGB(255, 15, 15)));
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // up
        delay(3 * BEAT_TIME_3 / 4);

        // my
        delay(BEAT_TIME_3 / 2);

        // world
        fillColorSet(whiteAndColorSet(CRGB(255, 55, 15)));
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // like
        delay(3 * BEAT_TIME_3 / 4);

        // no-
        delay(BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 22");
    for (int beat = 22; beat <= 22; beat++) { // Bar 22
        // -bo-
        fillColorSet(whiteAndColorSet(CRGB(255, 255, 15)));
        FastLED.show();
        delay(BEAT_TIME_3);

        // -dy else
        fillBodyPart(hands, CRGB(255, 255, 15));
        FastLED.show();
        delay(BEAT_TIME_3 / 2);
        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // The way that
        fillColorSet(whiteAndColorSet(CRGB(55, 255, 15)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);
    }
    Serial.println("🎵 Main 23");
    for (int beat = 23; beat <= 23; beat++) { // Bar 23
        // you
        fillColorSet(whiteAndColorSet(CRGB(15, 255, 15)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // flip

        // your

        // hair
        fillColorSet(whiteAndColorSet(CRGB(15, 255, 55)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // get

        // me
    }
    Serial.println("🎵 Main 24");
    for (int beat = 24; beat <= 24; beat++) { // Bar 24
        // o-
        fillColorSet(whiteAndColorSet(CRGB(15, 255, 255)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // -ver-

        // -whelmed.

        // 熄燈
        fillColorSet(whiteAndColorSet(CRGB(15, 55, 255)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // But

        // when

        // you

    }
}

// **第25段-副歌**
void playMain25() {
    Serial.println("🎵 Main 25");
    for (int beat = 25; beat <= 25; beat++) { // Bar 25
        // smile
        fillColorSet(whiteAndColorSet(CRGB(15, 15, 255)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // at

        // the

        // ground
        fillColorSet(whiteAndColorSet(CRGB(55, 15, 255)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // it

        // aint
    }
    Serial.println("🎵 Main 26");
    for (int beat = 26; beat <= 26; beat++) { // Bar 26
        // hard
        fillColorSet(whiteAndColorSet(CRGB(255, 15, 255)));
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // to

        // tell.


        // You
        fillColorSet(whiteAndColorSet(CRGB(255, 15, 55)));
        fillBodyPart(rightHand, WHITE_3);
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // don't

    }
    Serial.println("🎵 Main 27");
    for (int beat = 27; beat <= 27; beat++) { // Bar 27
        // know
        fillColorSet(COLORSET_3_1_2);
        fillBodyPart(rightHand, WHITE_3);
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // know


        // know
        fillColorSet(COLORSET_3_1_2);
        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        delay(2 * BEAT_TIME_3);
    }
    Serial.println("🎵 Main 28");
    for (int beat = 28; beat <= 28; beat++) { // Bar 28
        // You
        fillColorSet(COLORSET_3_1_2);
        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // don't


        // know


        // you're
        fillColorSet(COLORSET_3_1_2);
        FastLED.show();
        delay(2 * BEAT_TIME_3);

        // beau-


        // ti-


        // -ful.


    }
}

// **第29段-尾奏**
void playMain29() {
    Serial.println("🎵 Main 29");
    for (int beat = 29; beat <= 29; beat++) { // Bar 29
        // know
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(5);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 2);

        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(15);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(30);
        FastLED.show();
        delay(4 * BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 30");
    for (int beat = 30; beat <= 30; beat++) { // Bar 30
        // You
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // don't
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // you're
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // beau-
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // ti-
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 4);

        // -ful.
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        delay(BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 31");
    for (int beat = 31; beat <= 31; beat++) { // Bar 31
        // know
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(5);
        FastLED.show();
        delay(3 * BEAT_TIME_3 / 2);

        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(15);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // know
        if(DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(30);
        FastLED.show();
        delay(4 * BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 32");
    for (int beat = 32; beat <= 32; beat++) { // Bar 32
        // That's
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(BEAT_TIME_3 / 2);

        // what
        delay(BEAT_TIME_3 / 2);

        // makes
        delay(BEAT_TIME_3 / 2);

        // you
        delay(BEAT_TIME_3 / 2);

        // beau-
        delay(3 * BEAT_TIME_3 / 4);

        // ti-
        delay(3 * BEAT_TIME_3 / 4);

        // -ful.
        if(DANCER == 1 or DANCER == 2){ // 1號 花花 or 2號 徐舒庭
            fill_solid(leds, NUM_LEDS, BLUE_3);
        }
        if(DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_PURPLE_3);
        }
        if(DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_BLUE_3);
        }
        if(DANCER == 5 or DANCER == 7){ // 5號 蔡冠毅 or 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, SKY_BLUE_3);
        }
        FastLED.setBrightness(50);
        FastLED.show();
        delay(5 * BEAT_TIME_3);

    }
}

// **🔥 LED 停止**
void stopEffect() {
    Serial.println("✨ 完成，LED 停止！");
    FastLED.clear();
    FastLED.show();
}

void loop() {

}