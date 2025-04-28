#include <FastLED.h>
#include <vector>

// LED 燈條設定
#define LED_PIN 13          // LED 燈條 Data Pin (可改成你的 GPIO)
#define NUM_LEDS 910           // LED 顆數（請根據你的 LED 燈條數量設定）
#define BRIGHTNESS 5        // 亮度 (0~255)
#define LED_TYPE WS2812       // 燈條類型
#define COLOR_ORDER GRB       // 顏色順序
#define PERSON 1 // 1: 花 2: 徐 3: 米 4: 瑋 5: 毅 6: 許 7: 佑

CRGB leds[NUM_LEDS];

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

// === WHOLE ===
const LedRange wholeRanges[] = { {0, NUM_LEDS} };
BodyPart whole = {wholeRanges, 1};

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

#pragma endregion

#pragma region Color definition

struct ColorSet {
	CRGB whole      = CRGB::Black;
	CRGB hat        = CRGB::Black;
	CRGB hatMark    = CRGB::Black;
	CRGB lowerShirt = CRGB::Black;
	CRGB leftZipper = CRGB::Black;
	CRGB rightZipper= CRGB::Black;
	CRGB collar     = CRGB::Black;
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

// 第一首顏色
#define RED_1 CRGB(253, 4, 10)
#define PURPLE_1 CRGB(221, 47, 247)
#define YELLOW_1 CRGB(253, 220, 6)
#define WHITE_1 CRGB(255, 255, 255)
#define GREEN_1 CRGB(126, 217, 87)
#define LIGHT_BLUE_1 CRGB(9, 210, 255)

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
// 那時候沒討論色碼QQ

// 第三首顏色
#define RED_3 CRGB(255, 10, 10) 
#define YELLOW_3 CRGB(255, 230, 25)
#define WHITE_3 CRGB(255, 255, 255)

// 特殊顏色
const ColorSet ALL_BLACK = []() {
	ColorSet c;
	return c;
}();

const ColorSet ALL_WHITE = []() {
	ColorSet c;
	c.whole = WHITE_3;
	return c;
}();

// 彩虹色系
#define RAINBOW_RED CRGB(255, 0, 0)       // 紅色
#define RAINBOW_ORANGE CRGB(255, 165, 0)   // 橙色
#define RAINBOW_YELLOW CRGB(255, 255, 0)   // 黃色
#define RAINBOW_GREEN CRGB(0, 255, 0)      // 綠色
#define RAINBOW_BLUE CRGB(0, 0, 255)       // 藍色
#define RAINBOW_INDIGO CRGB(75, 0, 130)    // 靛色
#define RAINBOW_VIOLET CRGB(238, 130, 238) // 紫色
#define RAINBOW_PINK CRGB(255, 192, 203)   // 粉紅色
#define RAINBOW_CYAN CRGB(0, 255, 255)     // 青色
#define RAINBOW_MAGENTA CRGB(255, 0, 255)  // 洋紅色
#define RAINBOW_LIME CRGB(50, 205, 50)     // 萊姆色
#define RAINBOW_TEAL CRGB(0, 128, 128)     // 青色
#define RAINBOW_PURPLE CRGB(128, 0, 128)   // 紫色
#define RAINBOW_MAROON CRGB(128, 0, 0)     // 栗色
#define RAINBOW_NAVY CRGB(0, 0, 128)       // 海軍藍
#define RAINBOW_OLIVE CRGB(128, 128, 0)    // 橄欖色
#define RAINBOW_AQUA CRGB(0, 255, 255)     // 水色
#define RAINBOW_FUCHSIA CRGB(255, 0, 255)  // 紫紅色

const ColorSet COLORSET_RAINBOW = []() {
    ColorSet c;
    // 帽子
    c.hat = RAINBOW_RED;        // 紅色
    c.hatMark = RAINBOW_ORANGE; // 橙色
    
    // 衣服
    c.collar = RAINBOW_YELLOW;    // 黃色
    c.leftZipper = RAINBOW_GREEN; // 綠色
    c.rightZipper = RAINBOW_BLUE; // 藍色
    c.lowerShirt = RAINBOW_INDIGO; // 靛色
    
    // 手臂
    c.leftUpperArm = RAINBOW_VIOLET; // 紫色
    c.leftLowerArm = RAINBOW_PINK;   // 粉紅色
    c.rightUpperArm = RAINBOW_CYAN;  // 青色
    c.rightLowerArm = RAINBOW_MAGENTA; // 洋紅色
    
    // 手
    c.leftHand = RAINBOW_LIME; // 萊姆色
    c.rightHand = RAINBOW_TEAL; // 青色
    
    // 腿
    c.leftLeg = RAINBOW_PURPLE; // 紫色
    c.rightLeg = RAINBOW_MAROON; // 栗色
    c.leftCrotch = RAINBOW_NAVY; // 海軍藍
    c.rightCrotch = RAINBOW_OLIVE; // 橄欖色
    
    // 腳
    c.leftFoot = RAINBOW_AQUA; // 水色
    c.rightFoot = RAINBOW_FUCHSIA; // 紫紅色
    
    return c;
}();

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
  FastLED.show();
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
  FastLED.show();
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
  FastLED.show();
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
  FastLED.show();
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
	int leftDur = duration / 5;

	int midDur = duration * 2 / 5;
	int halfMidDur = midDur / 2;

	int rightDur = duration / 5;
	
	// 左手臂
	animations.push_back(Animation::Center(leftHand, color, leftDur));
	animations.push_back(Animation::Multi(
		{
			Animation::RTL(leftUpperArm, color, leftDur),
			Animation::RTL(leftLowerArm, color, leftDur),
		}
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
					Animation::Sequential({
							Animation::RTL(leftLeg, color, halfMidDur/2),
							Animation::RTL(leftCrotch, color, halfMidDur/2),
						}
					),
					Animation::RTL(leftFoot, color, halfMidDur/2),
				}
			),

			// 部位範圍為右半 跑半個 midDur
			Animation::Multi(
				{
				Animation::RTL(rightZipper, color, halfMidDur),
				Animation::Sequential({
						Animation::RTL(rightLeg, color, halfMidDur/2),
						Animation::RTL(rightCrotch, color, halfMidDur/2),
					}
				),
				Animation::RTL(rightFoot, color, halfMidDur/2),
				}
				),
			}
		),
		}
	));
	// 右手臂
	animations.push_back(Animation::Center(rightHand, color, rightDur));
	animations.push_back(Animation::Multi({
			Animation::RTL(rightUpperArm, color, rightDur),
			Animation::RTL(rightLowerArm, color, rightDur),
		}
	));
	
	return animations;
}	


#pragma endregion


// **🔥 LED 停止**
void stopEffect() {
	FastLED.clear();
	FastLED.show();
}

// **148 BPM 拍子設定**
#define BPM 148
#define BEAT_TIME (60000 / BPM)  // 每拍時間 (毫秒)
#define BAR_TIME (BEAT_TIME * 4) // 每小節時間 (毫秒)

int totalSteps = 0;
int stepIndex  = 0;
Animation anim;
std::vector<PlayStep> sequence;

// HIGHLIGHT:
void setup() {
		Serial.begin(115200);
		FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
		FastLED.setBrightness(BRIGHTNESS);
		FastLED.clear();
		FastLED.show();

		Serial.println("✨ LED 147 BPM 拍子開始！");
		//sequence.push_back( PlayStep::Create(Animation::LTR(whole, WHITE_1, BEAT_TIME*8)) );
		
		/*std::vector<Animation> animations;
		animations.push_back(Animation::Center(hat, RED_1, BEAT_TIME*4));
		animations.push_back(Animation::LTR(legs, YELLOW_1, BEAT_TIME*4));
		animations.push_back(Animation::RTL(hands, PURPLE_1, BEAT_TIME*4));
		sequence.push_back(PlayStep::Create(Animation::Multi(animations)));
		

		for (int i = 1; i <= 100; i++){
				setupPart_LTDO(i);
		}
		*/
		sequence.push_back(PlayStep::Create(Animation::Sequential(LEFT_TO_RIGHT(WHITE_1, BEAT_TIME*4))));

		sequence.push_back(PlayStep::Create(Animation::showColorSet(COLORSET_RAINBOW, 15000)));
		totalSteps = sequence.size();
}

// HIGHLIGHT:

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
					sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*1)) );
					break;
				case 10: // What you doing?
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
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
					sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
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
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2)) );
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
						sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_1_FRONT, BEAT_TIME*6)) );
					else
						sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME*6)) );					
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
					else if (PERSON == 1){
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
					else if (PERSON == 1){
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

void loop() {
  if (!anim.update()) {
    if (stepIndex < totalSteps) {
      auto &s = sequence[stepIndex++];
      anim = s.animation;
      anim.begin();
    } else {
      // all done
      stopEffect();
      while(true) delay(1000);
    }
  }

  // you can do other non-blocking work here…
}

