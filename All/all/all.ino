#include <FastLED.h>
#include <WiFi.h>
#include <PubSubClient.h>

struct ColorSet {
	CRGB whole      = CRGB::Black;
	CRGB hat        = CRGB::Black;
	CRGB hatMark    = CRGB::Black;
	CRGB collar     = CRGB::Black;
	CRGB beforeHatMark = CRGB::Black;
	CRGB afterHatMark = CRGB::Black;
	CRGB lowerShirt = CRGB::Black;
	CRGB leftZipper = CRGB::Black;
	CRGB rightZipper= CRGB::Black;
	CRGB leftShirt  = CRGB::Black;
	CRGB rightShirt = CRGB::Black;
	CRGB shirt      = CRGB::Black;
	CRGB leftUpperArm = CRGB::Black;
	CRGB leftLowerArm = CRGB::Black;
	CRGB rightUpperArm= CRGB::Black;
	CRGB rightLowerArm= CRGB::Black;
	CRGB leftArm    = CRGB::Black;
	CRGB rightArm   = CRGB::Black;
	CRGB arms       = CRGB::Black;
	CRGB leftHand   = CRGB::Black;
	CRGB rightHand  = CRGB::Black;
	CRGB hands      = CRGB::Black;
	CRGB body       = CRGB::Black;
	CRGB leftLeg    = CRGB::Black;
	CRGB rightLeg   = CRGB::Black;
	CRGB leftCrotch = CRGB::Black;
	CRGB rightCrotch= CRGB::Black;
	CRGB crotch     = CRGB::Black;
	CRGB legs       = CRGB::Black;
	CRGB leftFoot   = CRGB::Black;
	CRGB rightFoot  = CRGB::Black;
	CRGB feet       = CRGB::Black;
};

// 函數宣告
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void setupPart_LTDO(int partNumber);
void setupPart_shutUAD(int partNumber);
void runAllAnimations();
void danceWhatMYB();
void stopEffect();
void playIntro();
void playMain1();
void playMain5();
void playMain9();
void playMain13();
void playMain17();
void playMain21();
void playMain25();
void playMain29();
bool shouldContinueDance();

// WiFi 設定
const char* ssid = "IMPR";
const char* password = "pierre2001";

// MQTT 伺服器設定
const char* mqtt_server = "192.168.31.209";  // 請確認MQTT伺服器IP
const char* mqtt_topic = "LED_TOPIC";

WiFiClient espClient;
PubSubClient client(espClient);

// 全局變量用於控制舞蹈
volatile bool danceRunning = false;
unsigned long nextBeatMillis = 0;

// 第三首歌--舞者編號
// 0號 全體test
// 1號 花花
// 2號 徐舒庭
// 3號 小米
// 4號 許晉誠
// 5號 蔡冠毅
// 6號 蔡仁瑋
// 7號 蔡承佑
const int DANCER = 2;
#define PERSON 2            // 1: 花 2: 徐 3: 米 4: 瑋 5: 毅 6: 許 7: 佑
#define ROLE 3 // 1: 花花 2: 小米 3: 徐舒庭 4: 蔡仁瑋 5: 許晉誠 6: 蔡冠毅 7: 蔡承佑

// LED 燈條設定
#define LED_PIN 13             // LED 燈條 Data Pin (可改成你的 GPIO)
#define NUM_LEDS 1000           // LED 顆數（請根據你的 LED 燈條數量設定）
#define BRIGHTNESS 7        // 亮度 (0~255) default 10
#define LED_TYPE WS2812       // 燈條類型
#define COLOR_ORDER GRB       // 顏色順序 整首隨機淺色亮色系

CRGB leds[NUM_LEDS];

// **148 BPM 拍子設定**
#define BPM 148
#define BEAT_TIME (60000 / BPM)  // 每拍時間 (毫秒)
#define BAR_TIME (BEAT_TIME * 4) // 每小節時間 (毫秒)

// **128 BPM 拍子設定**
#define BPM_2 128
#define BEAT_TIME_2 (60000 / BPM_2)  // 每拍時間 (毫秒)

// **BPM_3 拍子設定**
// BPM 125
#define BPM_3 125
#define BEAT_TIME_3 (60000 / BPM_3)  // 每拍時間 (毫秒)

#pragma region BodyPart definition
 
// 定義部位
struct LedRange { // 注意是 start 跟 **length**
	int start;
	int length;
	// Constructor that defaults start to 0
	LedRange(int length) : start(0), length(length) {}

	// Constructor with explicit start and length
	LedRange(int start, int length) : start(start), length(length) {}
};

struct BodyPart {
	const LedRange* ranges;
	int numRanges;
};

// === WHOLE ===
const LedRange wholeRanges[] = { {NUM_LEDS} };
BodyPart whole ;

// === HAT === 共 131
const LedRange beforeHatMarkRanges[] = { {50} }; // Before the hat mark
const LedRange hatMarkRanges[] = { {34} }; // 帽子上的圈圈
const LedRange afterHatMarkRanges[] = { {47} }; // After the hat mark

BodyPart beforeHatMark;
BodyPart hatMark;
BodyPart afterHatMark;
BodyPart hat;

// === SHIRT === // 不包含袖子
const LedRange lowerShirtRanges[] = { {62} }; 
const LedRange leftZipperRanges[] = { {30} };
const LedRange collarRanges[] = { {90} };
const LedRange rightZipperRanges[] = { {30} };

BodyPart lowerShirt;
BodyPart leftZipper;
BodyPart collar;
BodyPart rightZipper;
BodyPart shirt; 

// === ARMS === // 袖子
const LedRange leftUpperArmRanges[] = { {60} }; // Upper 包含袖口
const LedRange leftLowerArmRanges[] = { {41} };
const LedRange rightUpperArmRanges[] = { {60} }; // Upper 包含袖口
const LedRange rightLowerArmRanges[] = { {41} };

BodyPart leftUpperArm;
BodyPart leftLowerArm;
BodyPart rightUpperArm;
BodyPart rightLowerArm;
BodyPart leftArm;
BodyPart rightArm;
BodyPart arms;

// === BODY === 衣服+袖子
BodyPart body;

// === HANDS ===
const LedRange leftHandRanges[] = { {61} };
const LedRange rightHandRanges[] = { {61} };

BodyPart leftHand;
BodyPart rightHand;
BodyPart hands;

// === LEGS ===
const LedRange leftLegRanges[] = { {52} };
const LedRange rightLegRanges[] = { {52} };
const LedRange leftCrotchRanges[] = { {38} };
const LedRange rightCrotchRanges[] = { {38} };

BodyPart leftLeg;
BodyPart rightLeg;
BodyPart leftCrotch;
BodyPart rightCrotch;
BodyPart crotch;
BodyPart legs;

// === FEET ===
const LedRange leftFootRanges[] = { {30} };
const LedRange rightFootRanges[] = { {30} };

BodyPart leftFoot;
BodyPart rightFoot;
BodyPart feet;

// LED ranges in order of start values
std::vector<LedRange> ledRanges = {
	lowerShirtRanges[0],      
	leftZipperRanges[0],      
	collarRanges[0],          
	beforeHatMarkRanges[0],   
	hatMarkRanges[0],         
	afterHatMarkRanges[0],    
	rightZipperRanges[0],     
	rightLowerArmRanges[0],   
	rightHandRanges[0],       
	rightUpperArmRanges[0],   
	leftUpperArmRanges[0],    
	leftHandRanges[0],        
	leftLowerArmRanges[0],    
	leftLegRanges[0],         
	leftFootRanges[0],        
	leftCrotchRanges[0],      
	rightCrotchRanges[0],     
	rightFootRanges[0],       
	rightLegRanges[0]         
};

// Composite ranges that use other ranges
std::vector<LedRange> hatRangesVec;
std::vector<LedRange> shirtRangesVec;
std::vector<LedRange> leftArmRangesVec;
std::vector<LedRange> rightArmRangesVec;
std::vector<LedRange> armsRangesVec;
std::vector<LedRange> handsRangesVec;
std::vector<LedRange> bodyRangesVec;
std::vector<LedRange> crotchRangesVec;
std::vector<LedRange> legsRangesVec;
std::vector<LedRange> feetRangesVec;
std::vector<LedRange> wholeRangesVec;
// Body parts array
BodyPart bodyParts[19]; // All individual body parts

// Function to initialize LED ranges with proper start values
void initializeLedRangeStarts() {
	int currentStart = 0;
	
	// Initialize the start value for each LED range based on the previous range's start and length
	for (size_t i = 0; i < ledRanges.size(); i++) {
		ledRanges[i].start = currentStart;
		currentStart += ledRanges[i].length;
		
		// Print debug info
		Serial.print("Range ");
		Serial.print(i);
		Serial.print(": start=");
		Serial.print(ledRanges[i].start);
		Serial.print(", length=");
		Serial.print(ledRanges[i].length);
		Serial.print(", end=");
		Serial.println(ledRanges[i].start + ledRanges[i].length - 1);
	}
	
	// Update bodyParts array with the corresponding ranges from ledRanges
	// Use a for loop to initialize bodyParts array
	for (size_t i = 0; i < ledRanges.size(); i++) {
		bodyParts[i] = {&ledRanges[i], 1};
	}
	// Initialize individual hat parts
	beforeHatMark = {&ledRanges[3], 1};
	hatMark = {&ledRanges[4], 1};
	afterHatMark = {&ledRanges[5], 1};
	
	// Initialize lowerShirt, leftZipper, collar, rightZipper
	lowerShirt = {&ledRanges[0], 1};
	leftZipper = {&ledRanges[1], 1};
	collar = {&ledRanges[2], 1};
	rightZipper = {&ledRanges[6], 1};
	
	// Initialize arms
	rightLowerArm = {&ledRanges[7], 1};
	rightHand = {&ledRanges[8], 1};
	rightUpperArm = {&ledRanges[9], 1};
	leftUpperArm = {&ledRanges[10], 1};
	leftHand = {&ledRanges[11], 1};
	leftLowerArm = {&ledRanges[12], 1};
	
	// Initialize legs and feet
	leftLeg = {&ledRanges[13], 1};
	leftFoot = {&ledRanges[14], 1};
	leftCrotch = {&ledRanges[15], 1};
	rightCrotch = {&ledRanges[16], 1};
	rightFoot = {&ledRanges[17], 1};
	rightLeg = {&ledRanges[18], 1};
	
	// Initialize composite ranges
	
	// Hat ranges (combining the three hat parts)
	hatRangesVec = {ledRanges[3], ledRanges[4], ledRanges[5]};
	hat = {hatRangesVec.data(), 3};
	
	// Shirt ranges
	shirtRangesVec = {ledRanges[0], ledRanges[2], ledRanges[1], ledRanges[6]};
	shirt = {shirtRangesVec.data(), 4};
	
	// Arm ranges
	leftArmRangesVec = {ledRanges[10], ledRanges[12]};
	leftArm = {leftArmRangesVec.data(), 2};
	
	rightArmRangesVec = {ledRanges[9], ledRanges[7]};
	rightArm = {rightArmRangesVec.data(), 2};
	
	armsRangesVec = {ledRanges[10], ledRanges[9], ledRanges[12], ledRanges[7]};
	arms = {armsRangesVec.data(), 4};
	
	// Hand ranges
	handsRangesVec = {ledRanges[11], ledRanges[8]};
	hands = {handsRangesVec.data(), 2};
	
	// Body ranges (shirt + arms)
	bodyRangesVec = {ledRanges[0], ledRanges[2], ledRanges[1], ledRanges[6], 
					ledRanges[10], ledRanges[9], ledRanges[12], ledRanges[7]};
	body = {bodyRangesVec.data(), 8};
	
	// Crotch ranges
	crotchRangesVec = {ledRanges[15], ledRanges[16]};
	crotch = {crotchRangesVec.data(), 2};
	
	// Legs ranges
	legsRangesVec = {ledRanges[13], ledRanges[18], ledRanges[15], ledRanges[16]};
	legs = {legsRangesVec.data(), 4};
	
	// Feet ranges
	feetRangesVec = {ledRanges[14], ledRanges[17]};
	feet = {feetRangesVec.data(), 2};
	
	// Whole range
	wholeRangesVec = {{0, NUM_LEDS}};
	whole = {wholeRangesVec.data(), 1};
	
	// Verify the total LEDs matches our expected count
	int totalLEDs = 0;
	for (const auto& range : ledRanges) {
		totalLEDs += range.length;
	}
	
	Serial.print("Total LEDs calculated: ");
	Serial.print(totalLEDs);
	Serial.print(" vs defined NUM_LEDS: ");
	Serial.println(NUM_LEDS);
	
	if (totalLEDs != NUM_LEDS) {
		Serial.println("WARNING: Calculated LED count doesn't match NUM_LEDS!");
	}
}
#pragma endregion

#pragma region Color definition
 
 // 特殊顏色
const ColorSet ALL_BLACK = []() {
	ColorSet c;
    c.whole = CRGB::Black;
	return c;
}();

const ColorSet ALL_WHITE = []() {
	ColorSet c;
	c.whole = CRGB::White;
	return c;
}();

// 第一首顏色
#define RED_1 CRGB(253, 4, 10)
#define PURPLE_1 CRGB(221, 47, 247)
#define YELLOW_1 CRGB(253, 220, 6)
#define WHITE_1 CRGB(255, 255, 255)
#define GREEN_1 CRGB(126, 217, 87)
#define LIGHT_BLUE_1 CRGB(9, 210, 255)
#define BLACK_1 CRGB(0, 0, 0)

const ColorSet COLORSET_1_FRONT = []() {
	ColorSet c;
	c.feet = PURPLE_1;
	c.legs = WHITE_1;
	c.body = RED_1;
	c.hat = PURPLE_1;
	c.hands = PURPLE_1;
	return c;
}();

const ColorSet COLORSET_1_BACK = []() {
		ColorSet c;
		c.feet = PURPLE_1;
		c.legs = WHITE_1;
		c.body = YELLOW_1;
		c.hat = PURPLE_1;
		c.hands = PURPLE_1;
		return c;
	}();

// 第二首顏色
#define RED_1 CRGB(253, 4, 10)
#define YELLOW_2 CRGB(253, 220, 6)
#define WHITE_1 CRGB(255, 255, 255)
#define GREEN_1 CRGB(126, 217, 87)
#define BLACK_2 CRGB(0, 0, 0)
#define GREEN_2 CRGB(126, 217, 87)
#define PURPLE_2 CRGB(116, 95, 200)
#define LIGHT_BLUE_2 CRGB(9, 210, 255)
#define DARK_BLUE_2 CRGB(0, 74, 173)
#define PINK_3 CRGB(255, 100, 100)
#define LIGHT_GREEN_3 CRGB(100, 255, 100)
#define LIGHT_BLUE_3 CRGB(100, 100, 255)

const ColorSet COLORSET_2_1 = []() {
    ColorSet c;
    c.feet = DARK_BLUE_2;
    c.legs = PURPLE_2;
    c.body = LIGHT_BLUE_2;
    c.hat = GREEN_1;
    c.hands = YELLOW_2;
    return c;
  }();
  
  const ColorSet COLORSET_2_2 = []() {
    ColorSet c;
	c.feet = PURPLE_1;
	c.legs = WHITE_1;
	c.body = RED_1;
	c.hat = PURPLE_1;
	c.hands = PURPLE_1;
    return c;
  }();
  
  const ColorSet COLORSET_2_3 = []() {
    ColorSet c;
    c.feet = YELLOW_1;
    c.legs = LIGHT_YELLOW_3;
    c.body = LIGHT_GREEN_3;
    c.hat = PINK_3;
    c.hands = LIGHT_BLUE_3;
    return c;
  }();

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

#pragma region Fill and show original functions
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
if (color.beforeHatMark != CRGB::Black) fillBodyPart(beforeHatMark, color.beforeHatMark);
if (color.hatMark != CRGB::Black) fillBodyPart(hatMark, color.hatMark);
if (color.afterHatMark != CRGB::Black) fillBodyPart(afterHatMark, color.afterHatMark);

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
    if (currentTime >= endTime) return;
    
    // 檢查是否應該繼續動畫
    if (!danceRunning) return;

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(startHue + frame + i * hueStep, sat, val);
    }

    FastLED.show();

    // Wait until the right time for the next frame
    unsigned long targetTime = startTime + ((unsigned long)duration * frame / steps);
    while (millis() < targetTime) {
      // Check for MQTT messages and dance stop flag
      client.loop();
      if (!danceRunning) return;
      if (millis() >= endTime) return;
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
   if (currentTime >= endTime) return;
  
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
    if (millis() >= endTime) return;
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
        if (currentTime >= endTime) return;
        
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
            if (millis() >= endTime) return;
            delay(1);
        }
    }
}

#pragma endregion

#pragma region Function declaration

enum class AnimKind {
    RAINBOW,
    COLORSET_BEAT,
    COLORSET_PLUS_PARTS, 
    LTR,
    RTL,
    CENTER_OUT,
    SHOW_COLOR,
    MULTI,
    SEQUENTIAL
  };
  
  struct Animation {
    AnimKind        kind;
    bool            active   = false;
    uint32_t        startMs;
    int             duration;
    uint8_t         startHue, hueStep, sat, val;
    const ColorSet* cs;
    const BodyPart* part;
    CRGB            color;
    std::vector<const BodyPart*> extraParts;
    std::vector<CRGB>            extraColors;
    std::vector<Animation>       subAnimations;
    int sequentialIndex = 0;
  
    // 宣告所有成員函式
    static Animation Rainbow(int dur, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t SAT = 255, uint8_t VAL = 255);
    static Animation showColorSet(const ColorSet& colorset, int duration);
    static Animation LTR(const BodyPart& P, CRGB color, int duration);
    static Animation RTL(const BodyPart& bodyPart, CRGB color, int duration);
    static Animation Center(const BodyPart& bodyPart, CRGB color, int duration);
    static Animation showColorSetPlusParts(const ColorSet& colorset, const std::vector<const BodyPart*>& extraBodyParts, const std::vector<CRGB>& extraColor, int duration);
    static Animation ShowColor(const BodyPart& P, CRGB c, int dur);
    static Animation Multi(const std::vector<Animation>& anims);
    static Animation Sequential(const std::vector<Animation>& anims);
    void begin();
    bool update();
  private:
    void updateRainbow(uint32_t el);
    void updateLTR(uint32_t el);
    void updateRTL(uint32_t el);
    void updateCenter(uint32_t el);
    void showBodyPartNoDelay(const BodyPart& part, CRGB color);
    void paintColorSet();
  };
  
  // 定義所有成員函式
  Animation Animation::Rainbow(int dur, uint8_t startHue, uint8_t hueStep, uint8_t SAT, uint8_t VAL) {
    Animation a;
    a.kind      = AnimKind::RAINBOW;
    a.startHue  = startHue;
    a.hueStep   = hueStep;
    a.sat       = SAT;
    a.val       = VAL;
    a.duration  = dur;
    return a;
  }
  
  Animation Animation::showColorSet(const ColorSet& colorset, int duration) {
    Animation a;
    a.kind      = AnimKind::COLORSET_BEAT;
    a.cs        = &colorset;
    a.duration  = duration;
    return a;
  }
  
  Animation Animation::LTR(const BodyPart& P, CRGB color, int duration) {
    Animation a;
    a.kind      = AnimKind::LTR;
    a.part      = &P;
    a.color     = color;
    a.duration  = duration;
    return a;
  }
  
  Animation Animation::RTL(const BodyPart& bodyPart, CRGB color, int duration) {
    Animation a;
    a.kind      = AnimKind::RTL;
    a.part      = &bodyPart;
    a.color     = color;
    a.duration  = duration;
    return a;
  }
  
  Animation Animation::Center(const BodyPart& bodyPart, CRGB color, int duration) {
    Animation a;
    a.kind      = AnimKind::CENTER_OUT;
    a.part      = &bodyPart;
    a.color     = color;
    a.duration  = duration;
    return a;
  }
  
  Animation Animation::showColorSetPlusParts(const ColorSet& colorset, const std::vector<const BodyPart*>& extraBodyParts, const std::vector<CRGB>& extraColor, int duration) {
    Animation a;
    a.kind       = AnimKind::COLORSET_PLUS_PARTS;
    a.cs         = &colorset;
    a.extraParts = extraBodyParts;
    a.extraColors = extraColor;
    a.duration   = duration;
    return a;
  }
  
  Animation Animation::ShowColor(const BodyPart& P, CRGB c, int dur) {
    Animation a;
    a.kind     = AnimKind::SHOW_COLOR;
    a.part     = &P;
    a.color    = c;
    a.duration = dur;
    return a;
  }
  
  Animation Animation::Multi(const std::vector<Animation>& anims) {
    Animation a;
    a.kind = AnimKind::MULTI;
    a.subAnimations = anims;
    return a;
  }
  
  Animation Animation::Sequential(const std::vector<Animation>& anims) {
    Animation a;
    a.kind = AnimKind::SEQUENTIAL;
    a.subAnimations = anims;
    a.sequentialIndex = 0;
    return a;
  }
  
  void Animation::begin() {
    startMs = millis();
    active = true;
    switch(kind) {
      case AnimKind::RAINBOW:
        break;
      case AnimKind::COLORSET_BEAT:
        paintColorSet();
        break;
      case AnimKind::LTR:
        break;
      case AnimKind::RTL:
        break;
      case AnimKind::CENTER_OUT:
        break;
      case AnimKind::COLORSET_PLUS_PARTS:
        paintColorSet();
        for (size_t i = 0; i < extraParts.size(); i++) {
          showBodyPartNoDelay(*extraParts[i], extraColors[i]);
        }
        FastLED.show();
        break;
      case AnimKind::SHOW_COLOR:
        showBodyPartNoDelay(*part, color);
        FastLED.show();
        break;
      case AnimKind::MULTI:
        for (auto& subAnim : subAnimations) {
          subAnim.begin();
        }
        break;
      case AnimKind::SEQUENTIAL:
        sequentialIndex = 0;
        if (!subAnimations.empty()) {
          subAnimations[0].begin();
        }
        break;
    }
  }
  
  bool Animation::update() {
    if (!active) return false;
    uint32_t now = millis();
    uint32_t el  = now - startMs;
    if (el >= (uint32_t)duration) {
      active = false;
      return false;
    }
    switch(kind) {
      case AnimKind::RAINBOW:      updateRainbow(el);  break;
      case AnimKind::LTR:          updateLTR(el);      break;
      case AnimKind::RTL:          updateRTL(el);      break;
      case AnimKind::CENTER_OUT:   updateCenter(el);   break;
      case AnimKind::COLORSET_BEAT:                    break;
      case AnimKind::COLORSET_PLUS_PARTS:              break;
      case AnimKind::SHOW_COLOR:                       break;
      case AnimKind::MULTI: {
        bool subActive = false;
        for (auto& subAnim : subAnimations) {
          if (subAnim.update()) {
            subActive = true;
          }
        }
        active = subActive;
        break;
      }
      case AnimKind::SEQUENTIAL: {
        while (sequentialIndex < subAnimations.size()) {
          if (subAnimations[sequentialIndex].update()) {
            break;
          } else {
            sequentialIndex++;
            if (sequentialIndex < subAnimations.size()) {
              subAnimations[sequentialIndex].begin();
            }
          }
        }
        if (sequentialIndex >= subAnimations.size()) {
          active = false;
          return false;
        }
        break;
      }
    }
    return active;
  }
  
  void Animation::updateRainbow(uint32_t el) {
    uint8_t frame = (uint32_t)el * 255 / duration;
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(startHue + frame + i * hueStep, sat, val);
    //   FastLED.show();
  }
  
  void Animation::updateLTR(uint32_t el) {
    int maxLen = 0;
    for (int r = 0; r < part->numRanges; r++)
      maxLen = max(maxLen, part->ranges[r].length);
  
    int step = (uint32_t)el * maxLen / duration;
    
    for (int r = 0; r < part->numRanges; r++) {
      auto& L = part->ranges[r];
      int fillLen = min(step + 1, L.length);
      for (int i = 0; i < fillLen; i++) {
        leds[L.start + i] = color;
      }
    }
    // FastLED.show();
  }
  
  void Animation::updateRTL(uint32_t el) {
    int maxLen = 0;
    for (int r = 0; r < part->numRanges; r++)
      maxLen = max(maxLen, part->ranges[r].length);
  
    int step = (uint32_t)el * maxLen / duration;
  
    for (int r = 0; r < part->numRanges; r++) {
      auto& L = part->ranges[r];
      int fillLen = min(step + 1, L.length);
      for (int i = 0; i < fillLen; i++) {
        leds[L.start + (L.length - 1 - i)] = color;
      }
    }
    // FastLED.show();
  }
  
  void Animation::updateCenter(uint32_t el) {
    for (int r = 0; r < part->numRanges; r++) {
      auto& L = part->ranges[r];
      int half = L.length / 2;
      int fillSize = (uint32_t)el * (half + 1) / duration;
      fillSize = min(fillSize, half);
  
      int mid = L.start + half;
      
      for (int i = 0; i <= fillSize; i++) {
        int leftIdx  = mid - i;
        int rightIdx = mid + i + (L.length % 2 == 0 ? 1 : 0);
  
        if (leftIdx >= L.start && leftIdx < L.start + L.length)
          leds[leftIdx] = color;
        if (rightIdx >= L.start && rightIdx < L.start + L.length)
          leds[rightIdx] = color;
      }
    }
    // FastLED.show();
  }
  
  void Animation::showBodyPartNoDelay(const BodyPart& part, CRGB color) {
    if (color == CRGB::Black && cs != &ALL_BLACK) return;
    for (int i = 0; i < part.numRanges; i++) {
      fill_solid(&leds[part.ranges[i].start], part.ranges[i].length, color);
    }
  }
  
  void Animation::paintColorSet() {
	showBodyPartNoDelay(whole, cs->whole);
	showBodyPartNoDelay(hat, cs->hat);
	showBodyPartNoDelay(hatMark, cs->hatMark);
	showBodyPartNoDelay(beforeHatMark, cs->beforeHatMark);
	showBodyPartNoDelay(afterHatMark, cs->afterHatMark);
	showBodyPartNoDelay(body, cs->body);
	showBodyPartNoDelay(shirt, cs->shirt);
	showBodyPartNoDelay(lowerShirt, cs->lowerShirt);
	showBodyPartNoDelay(leftZipper, cs->leftZipper);
	showBodyPartNoDelay(rightZipper, cs->rightZipper);
	showBodyPartNoDelay(collar, cs->collar);
	showBodyPartNoDelay(leftArm, cs->leftArm);
	showBodyPartNoDelay(rightArm, cs->rightArm);
	showBodyPartNoDelay(leftUpperArm, cs->leftUpperArm);
	showBodyPartNoDelay(leftLowerArm, cs->leftLowerArm);
	showBodyPartNoDelay(rightUpperArm, cs->rightUpperArm);
	showBodyPartNoDelay(rightLowerArm, cs->rightLowerArm);
	showBodyPartNoDelay(hands, cs->hands);
	showBodyPartNoDelay(leftHand, cs->leftHand);
	showBodyPartNoDelay(rightHand, cs->rightHand);
	showBodyPartNoDelay(legs, cs->legs);
	showBodyPartNoDelay(leftLeg, cs->leftLeg);
	showBodyPartNoDelay(rightLeg, cs->rightLeg);
	showBodyPartNoDelay(crotch, cs->crotch);
	showBodyPartNoDelay(leftCrotch, cs->leftCrotch);
	showBodyPartNoDelay(rightCrotch, cs->rightCrotch);
	showBodyPartNoDelay(feet, cs->feet);
	showBodyPartNoDelay(leftFoot, cs->leftFoot);
	showBodyPartNoDelay(rightFoot, cs->rightFoot);
	FastLED.show();
}

  
  // ————— PLAYSTEP QUEUE —————
  struct PlayStep {
    Animation animation;
  
    static PlayStep Create(const Animation& anim) {
      PlayStep p;
      p.animation = anim;
      return p;
    }
  };
  
  std::vector<Animation> LEFT_TO_RIGHT(CRGB color, int duration){
      std::vector<Animation> animations;
      // Redistribute timing to ensure full duration is used
      int leftDur = duration / 6;
      int midDur = duration * 3 / 6;
      int halfMidDur = midDur / 2;
      int rightDur = duration * 2 / 6;
      
      // 左手臂
      animations.push_back(Animation::Center(leftHand, color, leftDur));
      animations.push_back(Animation::Multi({
              Animation::RTL(leftUpperArm, color, leftDur),
              Animation::RTL(leftLowerArm, color, leftDur),}
      ));
  
      // 身體  
      animations.push_back(Animation::Multi({
          // 部位範圍為左到右 跑完整個 midDur
          Animation::RTL(hat, color, midDur),
          Animation::RTL(collar, color, midDur),
          Animation::RTL(lowerShirt, color, midDur),
  
          Animation::Sequential({
              // 部位範圍為左半 跑半個 midDur
              Animation::Multi({
                      Animation::RTL(leftZipper, color, halfMidDur),
                      Animation::LTR(leftLeg, color, halfMidDur),
                      Animation::LTR(leftCrotch, color, halfMidDur),
                      Animation::RTL(leftFoot, color, halfMidDur/2),
                  }),
  
              // 部位範圍為右半 跑半個 midDur
              Animation::Multi({
                  Animation::RTL(rightZipper, color, halfMidDur),
                  Animation::LTR(rightLeg, color, halfMidDur),
                  Animation::LTR(rightCrotch, color, halfMidDur),
                  Animation::RTL(rightFoot, color, halfMidDur/2),
                  }),
              }),
          }));
      // 右手臂
      animations.push_back(Animation::Multi({
              Animation::RTL(rightUpperArm, color, rightDur/2),
              Animation::LTR(rightLowerArm, color, rightDur/2),
          }
      ));
      animations.push_back(Animation::Center(rightHand, color, rightDur/2));
      return animations;
  }	
  
#pragma endregion

bool isMe(std::initializer_list<int> people) { // Bowen 判斷舞者
    for (int p : people) {
        if (ROLE == p) return true;
    }
    return false;
}

// 裝置就緒指示燈
void showReadySignal() {
    // 確保陣列索引在有效範圍內
    int secondLedIndex = 799;  // 對應第800顆LED (索引從0開始)
    if (secondLedIndex >= NUM_LEDS) {
        secondLedIndex = NUM_LEDS - 1;  // 如果超出範圍，使用最後一顆
    }
    
    // 清除所有燈
    FastLED.clear();
    
    // 亮起第1顆和第800顆LED
    leds[0] = CRGB(255, 255, 255);  // 第1顆LED (索引為0)亮白色
    leds[secondLedIndex] = CRGB(255, 255, 255);  // 第800顆LED亮白色
    
    // 顯示
    FastLED.setBrightness(50);  // 設定較高亮度以便明顯看到
    FastLED.show();
    
    // 等待1秒
    delay(1000);
    
    // 熄滅全部
    FastLED.clear();
    FastLED.show();
    
    // 恢復原始亮度設定
    FastLED.setBrightness(BRIGHTNESS);
}


int totalSteps = 0;
int stepIndex  = 0;
int secondSongIndex = 0;
Animation anim;
std::vector<PlayStep> sequence;



void setup() {
    Serial.begin(115200);
    
    // 設置WiFi和MQTT
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    
    // 設置LED
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();

    Serial.println("設備就緒，等待MQTT命令...");

    Serial.println("✨ 載入第二首歌曲");
	initializeLedRangeStarts(); 
    // sequence.push_back(PlayStep::Create(Animation::Sequential(LEFT_TO_RIGHT(PURPLE_1, BEAT_TIME*8))));
    for (int i = 1; i <= 76; i++){
		setupPart_LTDO(i);
	}
    secondSongIndex = sequence.size(); // 記錄第二首歌的起始索引

    for (int i = 1; i <= 100; i++){
        setupPart_shutUAD(i);
    }

    totalSteps = sequence.size();
}

// WiFi 連接設定
void setup_wifi() {
    delay(10);
    Serial.println("連接至 WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi 連接成功！");
    Serial.print("ESP32 IP 地址: ");
    Serial.println(WiFi.localIP());
}

// MQTT 訊息回調函數
void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("收到 MQTT 訊息: ");
    String messageTemp;
    
    for (int i = 0; i < length; i++) {
        messageTemp += (char)message[i];
    }
    Serial.println(messageTemp);

    if (messageTemp == "ON") {
        Serial.println("開始 LED 表演...");
        FastLED.setBrightness(7);
        // 開始舞蹈特效
        danceRunning = true;
        stepIndex = 0;
        delay(1750);
        runAllAnimations();
        danceWhatMYB();
    }
    else if (messageTemp == "ON2") {
        Serial.println("開始 LED 表演...");
        FastLED.setBrightness(7);

        // 開始舞蹈特效
        danceRunning = true;
        stepIndex = secondSongIndex;
        delay(BEAT_TIME_2);
        runAllAnimations();
        danceWhatMYB();
    }
    else if (messageTemp == "ON3") {
        Serial.println("開始 LED 表演...");
        FastLED.setBrightness(7);
        // 開始舞蹈特效
        delay(25);
        danceRunning = true;
        danceWhatMYB();
    }
    else if (messageTemp == "OFF") {
        Serial.println("停止 LED 表演...");
        stepIndex = 200;
        danceRunning = false;  // 設置標誌以中斷舞蹈
        stopEffect();
    }
    
    else if (messageTemp == "READY") {
        Serial.println("顯示就緒訊號...");
        showReadySignal();
    }
    else if (messageTemp == "TEST") {
        Serial.println("開始 LED 測試...");
        // 開始舞蹈特效
        showColorSetForBeats(COLORSET_3_1_1, 800000);
    }
}

// MQTT 連接函數
void reconnect() {
    while (!client.connected()) {
        Serial.print("連接 MQTT 伺服器...");

        // 產生唯一 Client ID
        String clientId = "ESP32_Client_" + String(random(0xffff), HEX);

        if (client.connect(clientId.c_str())) {
            Serial.println("連接成功！");
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("失敗，錯誤碼 = ");
            Serial.print(client.state());
            Serial.println(" 5 秒後重試...");
            delay(5000);
        }
    }
}

// 檢查是否應該繼續舞蹈
bool shouldContinueDance() {
    // 處理MQTT消息
    client.loop();
    return danceRunning;
}

void startTimeline() {
  nextBeatMillis = millis();
}

void timelineDelay(unsigned long interval) {
  // 推進到下一個節拍時間點
  nextBeatMillis += interval;
  // 如果還沒到時間，就持續處理 MQTT loop，保持連線與可中斷
  long remain;
  while ((remain = (long)(nextBeatMillis - millis())) > 0 && danceRunning) {
    client.loop();
    // 如果真的要更「精準」，可以在這裡檢查更細微的邏輯或接收中控指令
  }
  // 一旦 millis() 超過 nextBeatMillis，就會自動跳過剩餘等待，直接進入下一個動作
}

void loop() {
    // 保持MQTT連接
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    
}

// What Makes You Beautiful 的 LED 執行串
void danceWhatMYB() {
    Serial.println("What Makes You Beautiful 開始！");
    startTimeline();
    danceRunning = true;

    // test color
    // rainbowAllLeds(5000, 0, 2, 100, 250); // duration, startHue, hueStep, sat, val
    // showColorSetForBeats(COLORSET_3_1_1, 8000);
    // showColorSetForBeats(COLORSET_3_1_2, 8000);
    // showColorSetForBeats(COLORSET_3_2, 8000);
    // showColorSetForBeats(COLORSET_3_3, 8000);
    // showColorSetForBeats(whiteAndColorSet(ORANGE_3), 8000);

    // delay(30);

    playIntro(); // 前奏
    if (!shouldContinueDance()) { stopEffect(); return; }

    playMain1();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain5();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain9();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain13();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain17();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain21();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain25();
    if (!shouldContinueDance()) { stopEffect(); return; }
    
    playMain29(); // 尾奏
    
    stopEffect();
}

#pragma region What Makes You Beautiful Actions
// **前奏** 七個人站定位擺pose 對拍隨機亮
void playIntro() {
    Serial.println("🎵 Intro 1");
    for (int beat = 1; beat <= 1; beat++) { // Bar 1
        // 亮燈
        if( DANCER == 3){ // 3號 小米
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if( DANCER == 3){ // 3號 小米
            fill_solid(leds, NUM_LEDS, LIGHT_BLUE_3); // 亮藍色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_PURPLE_3); // 亮紫色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Intro 2");
    for (int beat = 2; beat <= 2; beat++) { // Bar 2
        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, PINK_3); // 亮粉色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if( DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, SKY_BLUE_3); // 亮天藍色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if( DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, LIGHT_PURPLE_3); // 亮紫色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if( DANCER == 7){ // 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, PINK_3); // 亮粉色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Intro 3");
    for (int beat = 3; beat <= 3; beat++) { // Bar 3
        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2){ // 2號 徐舒庭
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if( DANCER == 2){ // 2號 徐舒庭
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_BLUE_3); // 亮藍色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 熄燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈
        if( DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Intro 4");
    for (int beat = 4; beat <= 4; beat++) { // Bar 4
        // 亮燈
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // 熄燈(蔡仁瑋)
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_YELLOW_3); // 亮黃色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈(蔡仁瑋)
        if( DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_GREEN_3); // 亮綠色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
        
        // 熄燈(蔡仁瑋)
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, SKY_BLUE_3); // 亮綠色
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  // **每拍熄燈時間**

        // 亮燈(蔡仁瑋)
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // You're
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2){ // 2號 徐舒庭
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // in-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // -se-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 3){ // 3號 小米
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
}

// **第一段**
void playMain1() {
    Serial.println("🎵 Main 1");
    for (int beat = 1; beat <= 1; beat++) { // Bar 1
        // -cure ~~
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 7){ // 7號 蔡承佑
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(5 * BEAT_TIME_3 / 2);   

        // Don't
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 3){ // 3號 小米
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // know
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // what
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2){ // 2號 徐舒庭
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 2");
    for (int beat = 2; beat <= 2; beat++) { // Bar 2
        // for ~~
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(5 * BEAT_TIME_3 / 2);   

        // You're
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2){ // 2號 徐舒庭
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // turn-
        if( DANCER == 1){                     // 1號 花花
            fillColorSet(COLORSET_3_1_1);                   // 1號 花花
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // -ning
        if( DANCER == 1){                     // 1號 花花
            fillColorSet(COLORSET_3_1_1);                   // 1號 花花
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 3");
    for (int beat = 3; beat <= 3; beat++) { // Bar 3
        // heads when you
        if( DANCER == 1){                     // 1號 花花
            fillColorSet(COLORSET_3_1_2);                   // 1號 花花
            FastLED.show();
            rainbowBodyPart(hat, 4, 2 * BEAT_TIME_3, 0, 2, 120);
            nextBeatMillis += 2 * BEAT_TIME_3;
        }
        else{
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            FastLED.show();
            timelineDelay(2 * BEAT_TIME_3);
        } 

        // walk through the
        if( DANCER == 1){                     // 1號 花花
            fillColorSet(COLORSET_3_1_2);                   // 1號 花花
            FastLED.show();
            rainbowBodyPart(hands, 4, 2 * BEAT_TIME_3, 0, 2, 120);
            nextBeatMillis += 2 * BEAT_TIME_3;
        }
        else{
            fill_solid(leds, NUM_LEDS, CRGB::Black);
            FastLED.show();
            timelineDelay(2 * BEAT_TIME_3);
        } 
    }
    Serial.println("🎵 Main 4");
    for (int beat = 4; beat <= 4; beat++) { // Bar 4
        // do-
        if( DANCER == 1){                     // 1號 花花
            fillColorSet(COLORSET_3_1_1);                   // 1號 花花
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // -o-
        if( DANCER == 1){                     // 1號 花花
            fillColorSet(COLORSET_3_1_1);                   // 1號 花花
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // -or
        if( DANCER == 1 or DANCER == 2 or DANCER == 3){ // 1號 花花 or 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_1_1);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        if( DANCER == 1 or DANCER == 6 or DANCER == 7){ // 1號 花花 or 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_1);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  

        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);  

        // Don't
        if( DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // need
        if( DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);    

        // make
        if( DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);    
    }
}

// **第五段**
void playMain5() {
    Serial.println("🎵 Main 5");
    for (int beat = 5; beat <= 5; beat++) { // Bar 5
        // up
        if( DANCER == 1 or DANCER == 2 or DANCER == 6){ // 1號 花花 or 2號 徐舒庭 or 6號 蔡仁瑋
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(5 * BEAT_TIME_3 / 2);  

        // To
        if( DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // co-
        if( DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);    

        // -ver
        if( DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);    
    }
    Serial.println("🎵 Main 6");
    for (int beat = 6; beat <= 6; beat++) { // Bar 6
        // up
        if( DANCER == 1 or DANCER == 3 or DANCER == 7){ // 1號 花花 or 3號 小米 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(5 * BEAT_TIME_3 / 2);   

        // be-
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, PINK_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // ing
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, LIGHT_PURPLE_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // the
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, SKY_BLUE_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 7");
    for (int beat = 7; beat <= 7; beat++) { // Bar 7
        // way
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, LIGHT_BLUE_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3);   

        // that
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, PINK_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // you
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, LIGHT_PURPLE_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // are
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, SKY_BLUE_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3);   

        // is
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, PINK_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // e-
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
            fillBodyPart(hatMark, LIGHT_PURPLE_3);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   
    }
    Serial.println("🎵 Main 8");
    for (int beat = 8; beat <= 8; beat++) { // Bar 8
        // -nough
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // -ou-
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);   

        // -ough
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        else{fill_solid(leds, NUM_LEDS, CRGB::Black);}
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 2);   

        // 熄燈
        FastLED.setBrightness(3);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 2);  
        FastLED.setBrightness(10); 

    }
}

// **第九段**
void playMain9() {
    Serial.println("🎵 Main 9");
    for (int beat = 9; beat <= 9; beat++) { // Bar 9
        // every one else in the
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();
            
            rainbowBodyPart(feet, 4 * BEAT_TIME_3, 0, 2, 120);
            nextBeatMillis += 4 * BEAT_TIME_3;
        } else {
            FastLED.show();
            timelineDelay(4 * BEAT_TIME_3);
        }
    }
    Serial.println("🎵 Main 10");
    for (int beat = 10; beat <= 10; beat++) { // Bar 10
        // room can see it
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();
            
            BodyPart rainbowParts[] = {feet, legs};
            rainbowMultipleBodyParts(rainbowParts, 2, 4 * BEAT_TIME_3, 0, 2, 120);
            nextBeatMillis += 4 * BEAT_TIME_3;
        } else {
            FastLED.show();
            timelineDelay(4 * BEAT_TIME_3);
        }
    }
    Serial.println("🎵 Main 11");
    for (int beat = 11; beat <= 11; beat++) { // Bar 11
        // every one
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();

            BodyPart rainbowParts2[] = {feet, legs, hands};
            rainbowMultipleBodyParts(rainbowParts2, 3, 2 * BEAT_TIME_3, 0, 2, 120);
            nextBeatMillis += 2 * BEAT_TIME_3;
        } else {
            FastLED.show();
            timelineDelay(2 * BEAT_TIME_3);
        }


        // else but
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();

            BodyPart rainbowParts3[] = {feet, legs, hands, hat};
            rainbowMultipleBodyParts(rainbowParts3, 4, 2 * BEAT_TIME_3, 0, 2, 120);
            nextBeatMillis += 2 * BEAT_TIME_3;
        } else {
            FastLED.show();
            timelineDelay(2 * BEAT_TIME_3);
        }
    }
    Serial.println("🎵 Main 12");
    for (int beat = 12; beat <= 12; beat++) { // Bar 12
        // you
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
            FastLED.show();
            
            rainbowAllLeds(5 * BEAT_TIME_3 / 2, 0, 2, 120);
            nextBeatMillis += 5 * BEAT_TIME_3 / 2;
        } else {
            FastLED.show();
            timelineDelay(5 * BEAT_TIME_3 / 2);
        }

        // Ba-
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // -by
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 3){ // 3號 小米
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // you
        fillColorSet(COLORSET_3_2);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

    }
}

// **第13段-副歌**
void playMain13() {
    Serial.println("🎵 Main 13");
    for (int beat = 13; beat <= 13; beat++) { // Bar 13
        // light up
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        // my world
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if( DANCER == 6 or DANCER == 4){ // 6號 蔡仁瑋 or 4號 許晉誠
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        // like
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if( DANCER == 6 or DANCER == 4 or DANCER == 1){ // 6號 蔡仁瑋 or 4號 許晉誠 or 1號 花花
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        // no
        fillColorSet(COLORSET_3_2); // 第三首歌-第二套顏色(黃色+綠色)
        if( DANCER == 6 or DANCER == 4 or DANCER == 1 or DANCER == 5){ // 6號 蔡仁瑋 or 4號 許晉誠 or 1號 花花 or 5號 蔡冠毅
            fillColorSet(whiteAndColorSet(GREEN_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

    }
    Serial.println("🎵 Main 14");
    for (int beat = 14; beat <= 14; beat++) { // Bar 14
        // -bo-
        fillColorSet(whiteAndColorSet(GREEN_3));
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        // -dy else
        // 1/7 1/7 1/7 1/7 1/7 1/7 1/7 閃電！！！！！！！！！！
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 7 or DANCER == 3){ // 7號 蔡承佑 or 3號 小米
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 5 or DANCER == 7){ // 5號 蔡冠毅 or 7號 蔡承佑
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1 or DANCER == 5){ // 1號 花花 or 5號 蔡冠毅
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 4 or DANCER == 1){ // 4號 許晉誠 or 1號 花花
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6 or DANCER == 4){ // 6號 蔡仁瑋 or 4號 許晉誠
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2 or DANCER == 6){ // 2號 徐舒庭 or 4號 許晉誠
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(body, YELLOW_3);
            fillBodyPart(rightHand, YELLOW_3);
            fillBodyPart(hat, YELLOW_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 7 );

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(body, ORANGE_3);
            fillBodyPart(hands, ORANGE_3);
            fillBodyPart(legs, ORANGE_3);
            fillBodyPart(feet, ORANGE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 3 );

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(body, ORANGE_3);
            fillBodyPart(hands, ORANGE_3);
            fillBodyPart(legs, ORANGE_3);
            fillBodyPart(feet, ORANGE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 3 );

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 4){ // 4號 許晉誠
            fillBodyPart(body, ORANGE_3);
            fillBodyPart(hands, ORANGE_3);
            fillBodyPart(legs, ORANGE_3);
            fillBodyPart(feet, ORANGE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 3 );

        // way
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        fillBodyPart(hands, ORANGE_3);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);
    }

    Serial.println("🎵 Main 15");
    for (int beat = 15; beat <= 15; beat++) { // Bar 15
        // you flip your
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 4){ // 4號 許晉誠
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);

        
        // back
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 4){ // 4號 許晉誠
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);

        // hair get me
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if( DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if( DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        if( DANCER == 3){ // 3號 小米
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);

        //
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 3){ // 3號 小米
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        else if( DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(rightLeg, WHITE_3);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if( DANCER == 1){ // 1號 花花
            fillColorSet(whiteAndColorSet(ORANGE_3));
        }
        
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        
    }
    Serial.println("🎵 Main 16");
    for (int beat = 16; beat <= 16; beat++) { // Bar 16
        // overwhelmed
        fillBodyPart(legs, WHITE_3);
        fillBodyPart(feet, WHITE_3);
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        fillBodyPart(arms, WHITE_3);
        fillBodyPart(hat, WHITE_3);
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        // But when you
        fill_solid(leds, NUM_LEDS, WHITE_3);
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

    }
}

// **第17段-副歌**
void playMain17() {
    Serial.println("🎵 Main 17");
    for (int beat = 17; beat <= 17; beat++) { // Bar 17
        // smile
        fillBodyPart(rightArm, RED_3);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // at
        fillBodyPart(rightHand, PINK_3);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // the
        timelineDelay(BEAT_TIME_3 / 2);

        // ground
        fillBodyPart(leftArm, RED_3);
        fillBodyPart(leftHand, PINK_3);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // it
        fillBodyPart(leftLeg, PINK_3);
        fillBodyPart(rightLeg, PINK_3);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // aint
        fillBodyPart(feet, RED_3);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 18");
    for (int beat = 18; beat <= 18; beat++) { // Bar 18
        // hard to
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 3){ // 3號 小米
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 1){ // 1號 花花
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 4){ // 4號 許晉誠
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        if( DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(hat, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(hat, WHITE_3);
        fillBodyPart(feet, RED_3);
        if( DANCER == 2){ // 2號 徐舒庭
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if( DANCER == 6){ // 6號 蔡仁瑋
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if( DANCER == 4){ // 4號 許晉誠
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if( DANCER == 1){ // 1號 花花
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if( DANCER == 5){ // 5號 蔡冠毅
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if( DANCER == 7){ // 7號 蔡承佑
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        fillBodyPart(feet, RED_3);
        if( DANCER == 3){ // 3號 小米
            fillBodyPart(feet, GREEN_3);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4 / 7);
        
        

        // tell.
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 4 or DANCER == 5){ // 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_1_1);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);

        // You
        timelineDelay(BEAT_TIME_3 / 2);

        // don't
        timelineDelay(2 * BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 19");
    for (int beat = 19; beat <= 19; beat++) { // Bar 19
        // know
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 4 or DANCER == 5){ // 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_1_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);


        // know
        timelineDelay(BEAT_TIME_3);

        // know
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 4 or DANCER == 5){ // 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);
        if( DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 4);

        timelineDelay(BEAT_TIME_3);
    }
    Serial.println("🎵 Main 20");
    for (int beat = 20; beat <= 20; beat++) { // Bar 20
        // You don't know you're bu...
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(5 *BEAT_TIME_3 / 2);

        // Ba-
        if( DANCER == 2 or DANCER == 3){ // 2號 徐舒庭 or 3號 小米
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // -by
        if( DANCER == 6 or DANCER == 7){ // 6號 蔡仁瑋 or 7號 蔡承佑
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // you
        if( DANCER == 1 or DANCER == 4 or DANCER == 5){ // 1號 花花 or 4號 許晉誠 or 5號 蔡冠毅
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

    }
}

// **第21段-副歌**
void playMain21() {
    Serial.println("🎵 Main 21");
    for (int beat = 21; beat <= 21; beat++) { // Bar 21
        // light
        fillColorSet(whiteAndColorSet(CRGB(255, 15, 15)));
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // up
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // my
        timelineDelay(BEAT_TIME_3 / 2);

        // world
        fillColorSet(whiteAndColorSet(CRGB(255, 55, 15)));
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // like
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // no-
        timelineDelay(BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 22");
    for (int beat = 22; beat <= 22; beat++) { // Bar 22
        // -bo-
        fillColorSet(whiteAndColorSet(CRGB(255, 255, 15)));
        FastLED.show();
        timelineDelay(BEAT_TIME_3);

        // -dy else
        fillBodyPart(hands, CRGB(255, 255, 15));
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);
        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // The way that
        fillColorSet(whiteAndColorSet(CRGB(55, 255, 15)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);
    }
    Serial.println("🎵 Main 23");
    for (int beat = 23; beat <= 23; beat++) { // Bar 23
        // you
        fillColorSet(whiteAndColorSet(CRGB(15, 255, 15)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // flip

        // your

        // hair
        fillColorSet(whiteAndColorSet(CRGB(15, 255, 55)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // get

        // me
    }
    Serial.println("🎵 Main 24");
    for (int beat = 24; beat <= 24; beat++) { // Bar 24
        // o-
        fillColorSet(whiteAndColorSet(CRGB(15, 255, 255)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // -ver-

        // -whelmed.

        // 熄燈
        fillColorSet(whiteAndColorSet(CRGB(15, 55, 255)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

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
        timelineDelay(2 * BEAT_TIME_3);

        // at

        // the

        // ground
        fillColorSet(whiteAndColorSet(CRGB(55, 15, 255)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // it

        // aint
    }
    Serial.println("🎵 Main 26");
    for (int beat = 26; beat <= 26; beat++) { // Bar 26
        // hard
        fillColorSet(whiteAndColorSet(CRGB(255, 15, 255)));
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // to

        // tell.


        // You
        fillColorSet(whiteAndColorSet(CRGB(255, 15, 55)));
        fillBodyPart(rightHand, WHITE_3);
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // don't

    }
    Serial.println("🎵 Main 27");
    for (int beat = 27; beat <= 27; beat++) { // Bar 27
        // know
        fillColorSet(COLORSET_3_1_2);
        fillBodyPart(rightHand, WHITE_3);
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // know


        // know
        fillColorSet(COLORSET_3_1_2);
        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);
    }
    Serial.println("🎵 Main 28");
    for (int beat = 28; beat <= 28; beat++) { // Bar 28
        // You
        fillColorSet(COLORSET_3_1_2);
        fillBodyPart(hands, WHITE_3);
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

        // don't


        // know


        // you're
        fillColorSet(COLORSET_3_1_2);
        FastLED.show();
        timelineDelay(2 * BEAT_TIME_3);

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
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(5);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 2);

        // know
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(20);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // know
        if( DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(40);
        FastLED.show();
        timelineDelay(4 * BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 30");
    for (int beat = 30; beat <= 30; beat++) { // Bar 30
        // You
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // don't
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // know
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // you're
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // beau-
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // ti-
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // -ful.
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 31");
    for (int beat = 31; beat <= 31; beat++) { // Bar 31
        // know
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(5);
        FastLED.show();
        timelineDelay(3 * BEAT_TIME_3 / 2);

        // know
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(20);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // know
        if(DANCER == 0 or DANCER == 1){ // 1號 花花
            fillColorSet(COLORSET_3_2);
        }
        FastLED.setBrightness(40);
        FastLED.show();
        timelineDelay(4 * BEAT_TIME_3 / 2);
    }
    Serial.println("🎵 Main 32");
    for (int beat = 32; beat <= 32; beat++) { // Bar 32
        // That's
        // fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        timelineDelay(BEAT_TIME_3 / 2);

        // what
        timelineDelay(BEAT_TIME_3 / 2);

        // makes
        timelineDelay(BEAT_TIME_3 / 2);

        // you
        timelineDelay(BEAT_TIME_3 / 2);

        // beau-
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // ti-
        timelineDelay(3 * BEAT_TIME_3 / 4);

        // -ful.
        if(DANCER == 0 or DANCER == 1 or DANCER == 2){ // 1號 花花 or 2號 徐舒庭
            fill_solid(leds, NUM_LEDS, BLUE_3);
        }
        if(DANCER == 0 or DANCER == 4){ // 4號 許晉誠
            fill_solid(leds, NUM_LEDS, LIGHT_PURPLE_3);
        }
        if(DANCER == 0 or DANCER == 3){ // 3號 小米
            fill_solid(leds, NUM_LEDS, PINK_3);
        }
        if(DANCER == 0 or DANCER == 6){ // 6號 蔡仁瑋
            fill_solid(leds, NUM_LEDS, LIGHT_BLUE_3);
        }
        if(DANCER == 0 or DANCER == 5 or DANCER == 7){ // 5號 蔡冠毅 or 7號 蔡承佑
            fill_solid(leds, NUM_LEDS, SKY_BLUE_3);
        }
        FastLED.setBrightness(80);
        FastLED.show();
        timelineDelay(9 * BEAT_TIME_3);

    }
}

#pragma endregion



// 預寫好sequence 第二首
void setupPart_shutUAD(int partNumber) {
    Serial.println(partNumber);

    switch (partNumber) {
        case 1:
            // "Ooh, shut up and dance with me" 開頭 12拍
            sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*11)) );

            sequence.push_back(
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back(
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back(
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
            break;

        case 2:
            // "We were victims of the night" 8拍
            sequence.push_back( //1,2
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2*2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*2)
                )
            );
            // sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back( //3
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::LTR(whole, LIGHT_GREEN_3 BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //4
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::RTL(whole, YELLOW_3, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //5
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::LTR(body, PURPLE_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //6
                PlayStep::Create(
                    isMe({4, 2, 1, 3, 7}) ? Animation::RTL(body, PURPLE_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            //sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            //sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            //sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME_2*2, 100, 1, 150)) );
            sequence.push_back( //7
                PlayStep::Create(
                    isMe({1, 2, 3, 7}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //8
                PlayStep::Create(
                    isMe({1, 3, 7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            break;

        case 3:
            // "The chemical, physical, kryptonite" 8拍
            sequence.push_back( //1
                PlayStep::Create(
                    isMe({1,3}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( //2-4
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*3)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*3)
                )
            );
            sequence.push_back( //5-5.5
                PlayStep::Create(
                    isMe({1,2,3}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );
            sequence.push_back( //5.5-6
                PlayStep::Create(
                    isMe({1,4,7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );  
            sequence.push_back( //6-8
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            break;

        case 4:
            // "Helpless to the bass and faded light" 8拍
            // 1~2拍：繞一圈
            // 3~4拍：隨機亮
            {
                std::vector<int> circle = {1,3,7,6,5,4,2};
                std::vector<int> random = {4,2,5,1,6,3,7};

                for (int i = 0; i < 7; i++) {
                    sequence.push_back( PlayStep::Create(
                        isMe({circle[i]}) 
                            ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                            : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                    ));
                }
                for (int i = 0; i < 7; i++) {
                    sequence.push_back( PlayStep::Create(
                        isMe({rightToLeft[i]}) 
                            ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                            : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                    ));
                }
            }

            sequence.push_back( PlayStep::Create(Animation::LTR(body, RED_1, BEAT_TIME_2*2)) ); //5-6

            sequence.push_back( //6-7.5
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*1.5)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*1.5)
                )
            );

            sequence.push_back( //7.5-8 (bound)
                PlayStep::Create(
                    isMe({1,2}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );
            break;

        case 5:
            // "Oh, we were bound to get together, bound to get together"
            sequence.push_back( //1-3.5
                PlayStep::Create(
                    isMe({1,2,4}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*3.5)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*3.5)
                )
            );  
            sequence.push_back( //3.5-4
                PlayStep::Create(
                    isMe({1,3}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
                )
            );
            sequence.push_back( //5-7
                PlayStep::Create(
                    isMe({1,3,7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*4)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*4)
                )
            );

            std::vector<int> random2 = {1,2,3};
            for (int i = 0; i < 3; i++) {
                sequence.push_back( PlayStep::Create(
                    isMe({random2[i]}) 
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3)
                ));
            }

            break;

        case 6:
            // "She took my arm, I don't know how it happened"

            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) ); //1
            for (int i = 0; i < 7; i++) {
                sequence.push_back(
                    PlayStep::Create(
                        isMe({1,3,7,6,5,4,2}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/7)
                                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/7)
                    )
                );
            }
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) ); //3
            sequence.push_back(
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            sequence.push_back(
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );

            break;

        // 7-11跟前面同邏輯！要繼續我可以馬上幫你補上
        case 7:
        // "We took the floor and she said"
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );

        // 5～8拍：快速閃爍
        for (int i = 0; i < 12; i++) {
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/12)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/12)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/12)) );
        }
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        break;

    case 8:
        // "Oh, don't you dare look back, just keep your eyes on me"
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );

        // 5～8拍：左到右、右到左波浪效果
        {
            std::vector<int> leftToRight = {7,3,6,1,5,2,4};
            std::vector<int> rightToLeft = {4,2,5,1,6,3,7};

            for (int i = 0; i < 7; i++) {
                sequence.push_back( PlayStep::Create(
                    isMe({leftToRight[i]}) 
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }
            
            for (int i = 0; i < 7; i++) {
                sequence.push_back( PlayStep::Create(
                    isMe({rightToLeft[i]}) 
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }
        }
        break;

    case 9:
        // "I said, 'You're holding back', she said, 'Shut up and dance with me'"
        {
            std::vector<int> leftToRight = {7,3,6,1,5,2,4};

            for (int i = 0; i < 7; i++) { //1,2
                sequence.push_back( PlayStep::Create(
                    isMe({leftToRight[i]})
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }

            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*2)) ); //3,4
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*2)) ); //5,6
            // "dance with me" 快速閃爍
            for (int i = 0; i < 8; i++) { //7-8
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/12)) );
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/12)) );
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/12)) );
            }

            //sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        }
        break;

    case 10:
        // "This woman is my destiny, she said"
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        /*
        sequence.push_back( PlayStep::Create(
            isMe({2,3})
                ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
        ));
        */
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
        break;

    case 11:
        // 1-4 "Ooh, shut up and dance with me"
        sequence.push_back( PlayStep::Create(
            isMe({4})
                ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2*4)
                : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*4)
        ));
        // 5-8
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2 * 2)) );
        break;

        default:
            stopEffect();
            break;
    }
}
// 1
void setupPart_LTDO(int partNumber) {
    Serial.println(partNumber);
    switch(partNumber)
		{
				case 1: 
					sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME*7, 0, 1, 150)) );
					break;
				case 2: // 登登登登登登登
					sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME*6, 255, 1, 150)) );
					break;
				case 3: // 1號亮
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 4: // 全亮
						sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME*10, 120, 1, 150)) );
					break;
				case 5:
					break;
				case 6: // Said baby 4567暗 
					if (PERSON >= 4 && PERSON <= 7)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;
				case 7: // Said baby 全暗 
					sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1)) );
					break;
				case 8: // Said baby 全亮 
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1)) );
					break;
				case 9: 
					sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1.7)) );
					break;
				case 10: // What you doing?
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1.3)) );
					break;
				case 11: // (What you doing?)
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;      
				case 12: // Where you at?
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;
				case 13: // (Where you at?)
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;              
				case 14: // Oh, you got plans?
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;
				case 15: // (You got plans?)
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;      
				case 16: // Don't say that
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;
				case 17: // (shut your trap)
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					break;
				case 18: // I'm sippin' wine 1 亮 頭黃
					if (PERSON == 1) {
						sequence.push_back( PlayStep::Create(Animation::showColorSetPlusParts(ALL_WHITE, { &hat }, {YELLOW_1}, BEAT_TIME*1)) );
					}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1)) );
					break;
				case 19: // (sip sip) 1 亮 領子黃、衣服黃
					if (PERSON == 1) {
						sequence.push_back( PlayStep::Create(Animation::showColorSetPlusParts(ALL_WHITE, { &collar }, {YELLOW_1}, BEAT_TIME*1)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSetPlusParts(ALL_WHITE, { &lowerShirt, &leftZipper, &rightZipper, &arms }, {YELLOW_1, YELLOW_1, YELLOW_1, YELLOW_1}, BEAT_TIME*1)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1)) );
					}
					else 
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3)) );
					break;
				case 20: // in a robe
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;    
				case 21: // (drip, drip)
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 22: // I look too good
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 23: // (look too good)
					if (PERSON == 1)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
							sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 24: // to be alone
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1)) );
					break;
				case 25: // (woo woo) 全亮
					sequence.push_back( PlayStep::Create(Animation::showColorSetPlusParts(ALL_WHITE, { &hands }, {YELLOW_1}, BEAT_TIME*2)) );
					sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;  
				case 26: // My house clean 1亮
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 27: // (house clean)
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 28: // My pool warm 全亮
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1)) );
					break;
				case 29: // (pool warm) 4 2 5 1 6 3 7
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					if (PERSON == 2)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					if (PERSON == 5)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					break;
				case 30: // Just shaved
					if (PERSON == 6)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					if (PERSON == 3)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					if (PERSON == 7)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2)) );
					break;
				case 31: // (smooth like a newborn) // 1亮
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*7)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*7)) );					
					break;
				case 32: // We should be dancing 1 3 7亮
					if (PERSON == 1 || PERSON == 3 || PERSON == 7)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 33: // romancing 1 2 4亮
					if (PERSON == 1 || PERSON == 2 || PERSON == 4)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 34: // In the east wing 4亮
					if (PERSON == 1 || PERSON == 2 || PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					if (PERSON == 4)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 35: // and the west wing（三連音） 4亮
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*4/3)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*4/3)) );
					break;
				case 36: // and the west wing（三連音）
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*4/3)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*4/3)) );
					break;
				case 37: // and the west wing（三連音）
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*4/3)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*4/3)) );
					break;
				case 38: // Of this mansion
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 39: // what's happening?
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
				break;
				case 40: // I aint playing 4 7 亮 3 被敲兩下 // 3 YELLOW
					if (PERSON == 4 || PERSON == 7)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 3)
						for (int i = 0; i < 2; i++){
							sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, YELLOW_1, BEAT_TIME/2)) );
							sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
						}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 41: // no games 1 被敲一下 // 1 PURPLE
					if (PERSON == 4 || PERSON == 7)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 1 | PERSON == 3){
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, PURPLE_1, BEAT_TIME/2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
					}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 42: // Every word that 3 被敲兩下 // 3 YELLOW
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 3)
						for (int i = 0; i < 2; i++){
							sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, YELLOW_1, BEAT_TIME/2)) );
							sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
						}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 43: // I say 1 被敲一下 // 1 PURPLE
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 1 | PERSON == 3){
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, PURPLE_1, BEAT_TIME/2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
					}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 44: // Is  6 被敲兩下 // 6 RED
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 6)
						for (int i = 0; i < 2; i++){
							sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, RED_1, BEAT_TIME/2)) );
							sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
						}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 45: // coming straight 2 被敲一下 // 2 BLUE
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 2){
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, LIGHT_BLUE_1, BEAT_TIME/2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
					}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 46: // from the 5 被敲四下, 2 6 3/2拍後被敲一下 // 5 GREEN
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 5){
						for (int i = 0; i < 4; i++){
							sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, GREEN_1, BEAT_TIME/4)) );
							sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/4)) );
						}
					}
					else if (PERSON == 2){
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, LIGHT_BLUE_1, BEAT_TIME/2)) );
					}
					else if (PERSON == 6){
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, RED_1, BEAT_TIME/2)) );
					}
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 47: // heart 1 3 正拍被敲一下
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
					else if (PERSON == 1) {
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, PURPLE_1, BEAT_TIME/2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
					} 
					else if (PERSON == 3) {
						sequence.push_back( PlayStep::Create(Animation::ShowColor(whole, YELLOW_1, BEAT_TIME/2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*3/2)) );
					} 
					else 
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 48: // So if you  全亮
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					break;
				case 49: // tryna 
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					break;
				case 50: // lay in 
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					break;
				case 51: // these arms 4亮 其他閃爍 Total:Beat Time*4
					for (int i = 0; i < 16; i++){
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/8)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/8)) );
					}
					break;
				case 52: // 
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					break;
				case 53: // I'ma 4亮 其他暗
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2/3)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2/3)) );
					break;
				case 54: // leave the 
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2/3)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2/3)) );
					break;
				case 55: // door
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2/3)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2/3)) );
					break;
				case 56: // open
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*6)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*6)) );
					break;
				case 57: // (I'ma leave  4 亮，向右踏全亮，轉身暗
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
					break;
				case 58: // the door open)   第3拍對到彈指 => 每拍向右亮 6 3 7
					if (PERSON == 4 || PERSON == 6)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*4)) );
					else if (PERSON == 3)
					{
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*3)) );
					} else if (PERSON == 7)
					{
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					} else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*4)) );
					break;
				case 59: // I'ma leave the   第3拍對到彈指 => 每拍向左亮 5 2 1
					if (PERSON == 4 || PERSON == 6 || PERSON == 3 || PERSON == 7 || PERSON == 5)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*4)) );
					else if (PERSON == 2)
					{
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*3)) );
					} else if (PERSON == 1)
					{
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*2)) );
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*2)) );
					}
					break;
				case 60: // door open, girl
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*4)) );
					break;
				case 61: // (I'ma leave the
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*4)) );
					break;
				case 62: // door open   手向左揮可以加特效
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*4)) );
					break;
				case 63: // hoping)    手向右揮可以加特效
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*4)) );
					break;
				case 64: // That you  七個人交互著閃爍四拍
					// 
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
				
					if (PERSON == 5)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					break;
				case 65: // feel the
					if (PERSON == 2)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );

					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					break;
				case 66: // way I
					if (PERSON == 3)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );

					if (PERSON == 7)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					break;
				case 67: // feel And
					if (PERSON == 1)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );

					if (PERSON == 5)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME/2)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME/2)) );
					break;
				case 68: // you 4 亮
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					break;
				case 69: // want me　
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					break;
				case 70: // like I
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					break;
				case 71: // want  
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					break;
				case 72: // tonight,
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					break;
				case 73: // bae-
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME)) );
					break;
				case 74: // be 第一拍全亮
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*6)) );
					break;
				case 75: // (Tell me that you're coming through)
					sequence.push_back( PlayStep::Create(Animation::Rainbow(BEAT_TIME*8, 0, 1, 150)) );
					break;
				case 76: // ooh 4 亮
					if (PERSON == 4)
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_BACK, BEAT_TIME*7.7)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*7.7)) );
					break;
				default:
					stopEffect();
					break;
		}

}


// 執行所有動畫序列
void runAllAnimations() {
    while (stepIndex < totalSteps) {
        auto &s = sequence[stepIndex++];
        anim = s.animation;
        Serial.println("執行動畫序列: " + String(stepIndex) + " / " + String(totalSteps));
        client.loop();
        if (!danceRunning)
            continue;
        anim.begin();
        FastLED.show();
        // 等待當前動畫完成
        while (anim.update()) {
            // After updating animations, show the LED changes
            if (!(anim.kind == AnimKind::SHOW_COLOR || anim.kind == AnimKind::COLORSET_BEAT || anim.kind == AnimKind::COLORSET_BEAT)) {
                FastLED.show();
            }
            client.loop();
            if (!danceRunning)
                break;
        }
    }
    
    // 所有動畫完成
    stopEffect();
    Serial.println("所有動畫序列已完成");
}

// **🔥 LED 停止**
void stopEffect() {
    Serial.println("✨ 完成，LED 停止！");
    FastLED.clear();
    FastLED.show();
}
