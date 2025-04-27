
#include <FastLED.h>

// LED 燈條設定
#define LED_PIN 4             // LED 燈條 Data Pin (可改成你的 GPIO)
#define NUM_LEDS 1500           // LED 顆數（請根據你的 LED 燈條數量設定）
#define BRIGHTNESS 10        // 亮度 (0~255)
#define LED_TYPE WS2812       // 燈條類型
#define COLOR_ORDER GRB       // 顏色順序

CRGB leds[NUM_LEDS];

// **120 BPM 拍子設定**
#define BPM 120
#define BEAT_TIME (60000 / BPM)  // 每拍時間 (毫秒)
#define BAR_TIME (BEAT_TIME * 4) // 每小節時間 (毫秒)
#define TOTAL_BARS 8             // 總小節數
#define ROLE 4

void stopEffect();
void showLightforBeats(CRGB color, unsigned long duration);

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
const LedRange hatMarkRanges[] = { {0, 5} }; // 帽子上的圈圈
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

// 先沿用第一首顏色
#define RED_1 CRGB(253, 4, 10)
#define PURPLE_1 CRGB(221, 47, 247)
#define YELLOW_1 CRGB(253, 220, 6)
#define WHITE_1 CRGB(255, 255, 255)
#define BLACK_1 CRGB(0, 0, 0)

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

const ColorSet COLORSET_2_1 = []() {
  ColorSet c;
  c.feet = PURPLE_1;
  c.legs = WHITE_1;
  c.body = RED_1;
  c.hat = PURPLE_1;
  c.hands = PURPLE_1;
  return c;
}();

const ColorSet COLORSET_2_2 = []() {
  ColorSet c;
  c.feet = WHITE_1;
  c.legs = PURPLE_1;
  c.body = WHITE_1;
  c.hat = RED_1;
  c.hands = RED_1;
  return c;
}();

const ColorSet COLORSET_2_3 = []() {
  ColorSet c;
  c.feet = RED_1;
  c.legs = WHITE_1;
  c.body = RED_1;
  c.hat = PURPLE_1;
  c.hands = PURPLE_1;
  return c;
}();

const ColorSet COLORSET_2_4 = []() {
  ColorSet c;
  c.feet = BLACK_1;
  c.legs = BLACK_1;
  c.body = BLACK_1;
  c.hat = BLACK_1;
  c.hands = BLACK_1;
  return c;
}();

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
  fillBlack();
  fillBodyPart(part, color);
  FastLED.show();
  delay(beat_time);
}
 
void fillColorSet(const ColorSet& color) {
  // === HAT ===
if (color.hatMark != CRGB::Black) fillBodyPart(hatMark, color.hatMark);
if (color.hat != CRGB::Black) fillBodyPart(hat, color.hat);
 
// === SHIRT === // 
if (color.lowerShirt != CRGB::Black) fillBodyPart(lowerShirt, color.lowerShirt);
if (color.leftZipper != CRGB::Black) fillBodyPart(leftZipper, color.leftZipper);
if (color.rightZipper != CRGB::Black) fillBodyPart(rightZipper, color.rightZipper);
if (color.collar != CRGB::Black) fillBodyPart(collar, color.collar);
if (color.shirt != CRGB::Black) fillBodyPart(shirt, color.shirt);
 
// === ARMS ===
if (color.leftUpperArm != CRGB::Black) fillBodyPart(leftUpperArm, color.leftUpperArm);
if (color.leftLowerArm != CRGB::Black) fillBodyPart(leftLowerArm, color.leftLowerArm);
if (color.rightUpperArm != CRGB::Black) fillBodyPart(rightUpperArm, color.rightUpperArm);
if (color.rightLowerArm != CRGB::Black) fillBodyPart(rightLowerArm, color.rightLowerArm);
if (color.leftArm != CRGB::Black) fillBodyPart(leftArm, color.leftArm);
if (color.rightArm != CRGB::Black) fillBodyPart(rightArm, color.rightArm);
if (color.arms != CRGB::Black) fillBodyPart(arms, color.arms);
 
// === BODY ===
if (color.body != CRGB::Black) fillBodyPart(body, color.body);
 
// === HANDS ===
if (color.leftHand != CRGB::Black) fillBodyPart(leftHand, color.leftHand);
if (color.rightHand != CRGB::Black) fillBodyPart(rightHand, color.rightHand);
if (color.hands != CRGB::Black) fillBodyPart(hands, color.hands);
 
// === LEGS ===
if (color.leftLeg != CRGB::Black) fillBodyPart(leftLeg, color.leftLeg);
if (color.rightLeg != CRGB::Black) fillBodyPart(rightLeg, color.rightLeg);
if (color.leftCrotch != CRGB::Black) fillBodyPart(leftCrotch, color.leftCrotch);
if (color.rightCrotch != CRGB::Black) fillBodyPart(rightCrotch, color.rightCrotch);
if (color.crotch != CRGB::Black) fillBodyPart(crotch, color.crotch);
if (color.legs != CRGB::Black) fillBodyPart(legs, color.legs);
 
// === FEET ===
if (color.leftFoot != CRGB::Black) fillBodyPart(leftFoot, color.leftFoot);
if (color.rightFoot != CRGB::Black) fillBodyPart(rightFoot, color.rightFoot);
if (color.feet != CRGB::Black) fillBodyPart(feet, color.feet);
}
 
void fillBlack() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
}
 
void showColorSetForBeats(const ColorSet& color, int beat_time) {
  fillBlack();
  fillColorSet(color);
  FastLED.show();
  delay(beat_time);
}
 
// Simple Light showing for whole LED strip
void showLightforBeats(const ColorSet& color, int beat_time){
  fillBlack();
  //fill_solid(leds, NUM_LEDS, color);
  fillColorSet(color);
  FastLED.show();
  delay(beat_time);
}
 
// Smooth rainbow showing for whole LED strip
void rainbowAllLeds(int duration, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t sat = 255, uint8_t val = 255) {
  const int steps = 256;
  int delayPerStep = duration / steps;
 
  for (int frame = 0; frame < steps; frame++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(startHue + frame + i * hueStep, sat, val);
    }
    FastLED.show();
    delay(delayPerStep);
  }
}
/*
void fillFromBottomToTop(const BodyPart* parts, int partCount, CRGB color, int duration) {
  // Collect all LEDs from all body parts
  std::vector<int> ledIndices;

  for (int p = 0; p < partCount; p++) {
    for (int r = 0; r < parts[p].numRanges; r++) {
      const LedRange& range = parts[p].ranges[r];
      for (int i = 0; i < range.length; i++) {
        ledIndices.push_back(range.start + i);
      }
    }
  }

  // Sort LED indices from low to high (bottom to top)
  std::sort(ledIndices.begin(), ledIndices.end());

  // Calculate delay per LED
  int delayPerLed = duration / ledIndices.size();

  // Fill LEDs one by one
  for (size_t i = 0; i < ledIndices.size(); i++) {
    leds[ledIndices[i]] = color;
    FastLED.show();
    delay();
  }
}
  */

  void fillFromBottomToTop(const BodyPart* parts, int partCount, CRGB color, unsigned long duration) {
    // 1) Gather and sort all LED indices
    std::vector<int> ledIndices;
    for (int p = 0; p < partCount; p++) {
      for (int r = 0; r < parts[p].numRanges; r++) {
        const LedRange &range = parts[p].ranges[r];
        for (int i = 0; i < range.length; i++) {
          ledIndices.push_back(range.start + i);
        }
      }
    }
    if (ledIndices.empty()) return;
    std::sort(ledIndices.begin(), ledIndices.end());
  
    // 2) Compute timing
    size_t totalSteps    = ledIndices.size();
    unsigned long stepTime = duration / totalSteps;
    unsigned long nextShow = millis() + stepTime;
  
    // 3) Animate, batching writes until it's time to show
    for (size_t i = 0; i < totalSteps; i++) {
      leds[ ledIndices[i] ] = color;
  
      // if we've reached or passed our next scheduled show time,
      // update the LEDs all at once
      if ((long)(millis() - nextShow) >= 0) {
        FastLED.show();
        nextShow += stepTime;
      }
    }
  
    // 4) Final catch‐up show to light any remaining LEDs
    FastLED.show();
  }


void setup() {
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();

    Serial.println("✨ LED 120 BPM 拍子開始！");

    // **執行 8 小節**
    //for (int bar = 1; bar <= TOTAL_BARS; bar++) {
    //    playBar(bar);
    //}

    //playBar_1(9);
    //playBar_1(10);
    
    BodyPart fillParts[] = { feet, legs, hands, arms, shirt, hat };
    fillFromBottomToTop(fillParts, sizeof(fillParts)/sizeof(fillParts[0]), CRGB::Red, BEAT_TIME*8);
    
    /*
    for (int i = 1; i <= 100; i++){
        playPart(i);
    }
        */


    stopEffect(); // 10 小節後停止
}

/*
// **🎵 單個小節（4/4 拍）**
void playBar(int barNumber) {
    Serial.print("🎵 小節 ");
    Serial.println(barNumber);

    for (int beat = 1; beat <= 4; beat++) {
        Serial.print("拍子 ");
        Serial.println(beat);

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::White);
        FastLED.show();
        delay(BEAT_TIME / 2);  // **每拍亮燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, COLORSET_2_4);
        FastLED.show();
        delay(BEAT_TIME / 2);  // **每拍熄燈時間**
    }
}
*/

/*
void playBar_1(int barNumber) {
    Serial.print("🎵 小節 ");
    Serial.println(barNumber);

    for (int beat = 0; beat < 2; beat++) {
        Serial.print("拍子 ");
        Serial.println(beat + 1);

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB(255, 100, 100));
        FastLED.show();
        delay(BEAT_TIME);  // **每拍亮燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB(100, 255, 100));
        FastLED.show();
        delay(BEAT_TIME);  // **每拍熄燈時間**
    }
}
*/

/*
"Ooh, shut up and dance with me"
We were victims of the night
The chemical, physical, kryptonite
Helpless to the bass and faded light
Oh, we were bound to get together, bound to get together
She took my arm, I don't know how it happened
We took the floor and she said
"Oh, don't you dare look back, just keep your eyes on me"
I said, "You're holding back, " she said, "Shut up and dance with me"
This woman is my destiny, she said
"Ooh, shut up and dance with me"
*/

// 主要就分亮時間差、亮部位
// 要「閃爍」還是「不斷切換顏色」？



void playPart(int partNumber) {
    Serial.println(partNumber);

    switch(partNumber)
    {
        case 1: 
          for (int i = 1; i <= 12; i++){
            //fillBlack();
            //FastLED.show();
            //delay(BEAT_TIME);
            showLightforBeats(COLORSET_2_3, BEAT_TIME);
          }
          showLightforBeats(COLORSET_2_1, BEAT_TIME);
          showLightforBeats(COLORSET_2_2, BEAT_TIME);
          showLightforBeats(COLORSET_2_3, BEAT_TIME);
          showLightforBeats(COLORSET_2_4, BEAT_TIME);

          break;
        case 2: // we were victims of the night
        // 第七拍4暗
        // 第八拍2暗
          showLightforBeats(COLORSET_2_1, BEAT_TIME);
          showLightforBeats(COLORSET_2_2, BEAT_TIME);
          showLightforBeats(COLORSET_2_3, BEAT_TIME);
          showLightforBeats(COLORSET_2_1, BEAT_TIME);
          showLightforBeats(COLORSET_2_2, BEAT_TIME);
          showLightforBeats(COLORSET_2_3, BEAT_TIME); //6
          if (ROLE == 4) {showLightforBeats(COLORSET_2_2, BEAT_TIME);} //4暗
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME);}
          if (ROLE == 2) {showLightforBeats(COLORSET_2_1, BEAT_TIME);} //2暗
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME);}
          break;
        case 3: // The chemical, physical, kryptonite
          if (ROLE == 7) {showLightforBeats(COLORSET_2_1, BEAT_TIME);} //7暗
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME);} //
          if (ROLE == 3) {showLightforBeats(COLORSET_2_2, BEAT_TIME);} //3暗
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME);}
          showLightforBeats(COLORSET_2_2, BEAT_TIME); //3
          showLightforBeats(COLORSET_2_3, BEAT_TIME); //4

          //night的時候射出
          if (ROLE == 2 || ROLE == 3) {showLightforBeats(COLORSET_2_1, BEAT_TIME/2);} //5、6

          showLightforBeats(COLORSET_2_2, BEAT_TIME); //7
          showLightforBeats(COLORSET_2_3, BEAT_TIME); //8

          break;
        case 4: // Helpless to the "bass" and faded light
          // 1376542
          showLightforBeats(COLORSET_2_1, BEAT_TIME*2); //1,2 由下亮到上彈bass
          showLightforBeats(COLORSET_2_2, BEAT_TIME*2); //3,4 由上亮到下彈bass

          //if (ROLE == beatPattern[currentBeatIndex]) {
          //  showLightforBeats(...);
          //}

          stopEffect(); //先全暗showLightforBeats
          if (ROLE == 1) showLightforBeats(COLORSET_2_3, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 3) showLightforBeats(COLORSET_2_1, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 7) showLightforBeats(COLORSET_2_2, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 6) showLightforBeats(COLORSET_2_3, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 5) showLightforBeats(COLORSET_2_1, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 4) showLightforBeats(COLORSET_2_2, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 2) showLightforBeats(COLORSET_2_3, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}

          //78推向右邊
          stopEffect(); //先全暗
          showLightforBeats(COLORSET_2_1, BEAT_TIME);
          showLightforBeats(COLORSET_2_2, BEAT_TIME/2);

          break;
        case 5: // Oh, we were "bound" to get together, bound to get together
          stopEffect(); //先全暗
          //delay(duration);
          if (ROLE == 4 || ROLE == 2 || ROLE == 1) showLightforBeats(COLORSET_2_1, BEAT_TIME*3); //弱起拍，到2.5拍
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME*3);}
          showLightforBeats(COLORSET_2_3, BEAT_TIME);
          if (ROLE == 7 || ROLE == 3 || ROLE == 1) showLightforBeats(COLORSET_2_2, BEAT_TIME*3);
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME*3);}



          break;
        case 6: // She took my arm, I don't know how it happened
          if (ROLE == 1) showLightforBeats(COLORSET_2_1, BEAT_TIME); //1
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME);}
          showLightforBeats(COLORSET_2_2, BEAT_TIME); //2

          //3 繞一圈
          stopEffect(); //先全暗
          if (ROLE == 1) showLightforBeats(COLORSET_2_1, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 3) showLightforBeats(COLORSET_2_1, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_4, BEAT_TIME/7);}
          if (ROLE == 7) showLightforBeats(COLORSET_2_2, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_3, BEAT_TIME/7);}
          if (ROLE == 6) showLightforBeats(COLORSET_2_3, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_3, BEAT_TIME/7);}
          if (ROLE == 5) showLightforBeats(COLORSET_2_1, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_3, BEAT_TIME/7);}
          if (ROLE == 4) showLightforBeats(COLORSET_2_2, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_3, BEAT_TIME/7);}
          if (ROLE == 2) showLightforBeats(COLORSET_2_3, BEAT_TIME/7); //56的時候繞一圈
          else {showLightforBeats(COLORSET_2_3, BEAT_TIME/7);}

            showLightforBeats(COLORSET_2_1, BEAT_TIME); //4

          if (ROLE == 1) showLightforBeats(COLORSET_2_1, BEAT_TIME); //5
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME);}

            showLightforBeats(COLORSET_2_1, BEAT_TIME); //6
          if (ROLE == 1) showLightforBeats(COLORSET_2_1, BEAT_TIME); //7
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME);}

            showLightforBeats(COLORSET_2_1, BEAT_TIME); //8

          break;
        case 7: // We took the floor and she "said"
            showLightforBeats(COLORSET_2_2, BEAT_TIME); //1
            showLightforBeats(COLORSET_2_1, BEAT_TIME); //2
            showLightforBeats(COLORSET_2_3, BEAT_TIME); //3
            showLightforBeats(COLORSET_2_2, BEAT_TIME); //4

            // 5678 閃閃閃閃
            for (int i = 1; i <= 16; i++){
              showLightforBeats(COLORSET_2_1, BEAT_TIME/12);
              showLightforBeats(COLORSET_2_3, BEAT_TIME/12);
              showLightforBeats(COLORSET_2_2, BEAT_TIME/12);
            }

          break;
        case 8: // "Oh, don't you dare look back, just keep your eyes on me"

            showLightforBeats(COLORSET_2_3, BEAT_TIME); //由下到上亮
            showLightforBeats(COLORSET_2_2, BEAT_TIME); //由下到上亮
            showLightforBeats(COLORSET_2_1, BEAT_TIME); //由下到上亮
            showLightforBeats(COLORSET_2_3, BEAT_TIME); //由下到上亮

            // 5678 從左到右再從右到左
            // 7361524
            // 4251637
            stopEffect(); //先全暗
            if (ROLE == 7) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 3) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 6) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 1) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 5) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 2) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 4) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            
            stopEffect(); //先全暗
            if (ROLE == 4) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 2) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 5) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 1) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 6) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 3) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 7) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}

          break;
        case 9: // I said, "You're holding back, " she said, "Shut up and "dance" with me"
            stopEffect(); //先全暗
            if (ROLE == 7) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 3) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 6) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 1) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 5) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 2) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 4) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //56的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}

            stopEffect(); //先全暗
            if (ROLE == 4) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 2) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 5) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 1) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 6) showLightforBeats(COLORSET_2_1, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 3) showLightforBeats(COLORSET_2_2, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
            if (ROLE == 7) showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5); //3.58的時候繞一圈
            else {showLightforBeats(COLORSET_2_3, BEAT_TIME/3.5);}
        
        
            showLightforBeats(COLORSET_2_1, BEAT_TIME*2); // 5 "shut up and"
            // 78 dance with me (如果要讓他亮的很亂怎麼辦)
            for (int i = 1; i <= 8; i++){
                showLightforBeats(COLORSET_2_1, BEAT_TIME/12);
                showLightforBeats(COLORSET_2_3, BEAT_TIME/12);
                showLightforBeats(COLORSET_2_2, BEAT_TIME/12);
            }
            showLightforBeats(COLORSET_2_4, BEAT_TIME); //and
           

          break;
        case 10: // This woman is my destiny, she said
          showLightforBeats(COLORSET_2_4, BEAT_TIME); //1
          if (ROLE == 2 || ROLE == 3) showLightforBeats(COLORSET_2_1, BEAT_TIME/2); // 亮後半拍
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME/2);}
          
            showLightforBeats(COLORSET_2_1, BEAT_TIME);
            showLightforBeats(COLORSET_2_3, BEAT_TIME); // woman
            showLightforBeats(COLORSET_2_2, BEAT_TIME); // is my
            showLightforBeats(COLORSET_2_1, BEAT_TIME); // destiny
          break;
        case 11: // "Ooh, shut up and dance with me"
          if (ROLE == 4) showLightforBeats(COLORSET_2_3, BEAT_TIME*4);
            else {showLightforBeats(COLORSET_2_4, BEAT_TIME*4);}
            
          break;      
        default:
          stopEffect();
          break;
    }

}

void loop() {
  // 主程式迴圈：不停執行
}

// 💡 停止效果：全部熄燈
void stopEffect() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  Serial.println("🛑 效果已停止");
}

/*
// 💡 顯示特定顏色並維持一段時間
void showLightforBeats(CRGB color, unsigned long duration) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(duration);
  fill_solid(leds, NUM_LEDS, COLORSET_2_4);
  FastLED.show();
}
  */

/*
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
*/