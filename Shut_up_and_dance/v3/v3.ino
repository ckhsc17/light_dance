#include <FastLED.h>
#include <vector>

// LED 燈條設定
#define LED_PIN 13             // LED 燈條 Data Pin (可改成你的 GPIO)
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
  MULTI
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

  static Animation Rainbow(int dur, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t SAT = 255, uint8_t VAL = 255) {
    Animation a;
    a.kind      = AnimKind::RAINBOW;
    a.startHue  = startHue;
    a.hueStep   = hueStep;
    a.sat       = SAT;
    a.val       = VAL;
    a.duration  = dur;
    return a;
  }
  static Animation showColorSet(const ColorSet& colorset, int duration) {
    Animation a;
    a.kind      = AnimKind::COLORSET_BEAT;
    a.cs        = &colorset;
    a.duration  = duration;
    return a;
    Serial.println("showColorSet");
  }
  static Animation LTR(const BodyPart& P, CRGB color, int duration) {
    Animation a;
    a.kind      = AnimKind::LTR;
    a.part      = &P;
    a.color     = color;
    a.duration  = duration;
    return a;
  }
  static Animation RTL(const BodyPart& bodyPart, CRGB color, int duration) {
    Animation a;
    a.kind      = AnimKind::RTL;
    a.part      = &bodyPart;
    a.color     = color;
    a.duration  = duration;
    return a;
  }
  static Animation Center(const BodyPart& bodyPart, CRGB color, int duration) {
    Animation a;
    a.kind      = AnimKind::CENTER_OUT;
    a.part      = &bodyPart;
    a.color     = color;
    a.duration  = duration;
    return a;
  }
  static Animation showColorSetPlusParts(const ColorSet& colorset, const std::vector<const BodyPart*>& extraBodyParts, const std::vector<CRGB>& extraColor, int duration) {
    Animation a;
    a.kind       = AnimKind::COLORSET_PLUS_PARTS;
    a.cs         = &colorset;
    a.extraParts = extraBodyParts;
    a.extraColors = extraColor;
    a.duration   = duration;
    return a;
  }
  static Animation ShowColor(const BodyPart& P, CRGB c, int dur) {
    Animation a;
    a.kind     = AnimKind::SHOW_COLOR;
    a.part     = &P;
    a.color    = c;
    a.duration = dur;
    return a;
  }
  static Animation Multi(const std::vector<Animation>& anims, int dur) {
    Animation a;
    a.kind = AnimKind::MULTI;
    a.duration = dur;
    a.subAnimations = anims;
    return a;
  }

void begin() {
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
	}
}
  bool update() {
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
	  case AnimKind::SHOW_COLOR:				       break;
	case AnimKind::MULTI:
		bool subActive = false;
		for (auto& subAnim : subAnimations) {
			if (subAnim.update()) {
				subActive = true;
			}
		}
		active = subActive; // If no sub-animations are active, mark this animation as inactive too
		break;
    }
    return true;
  }

private:
  // — rainbow sweep —
  void updateRainbow(uint32_t el) {
    uint8_t frame = (uint32_t)el * 255 / duration;
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(startHue + frame + i * hueStep, sat, val);
    Serial.println("updateRainbow");
    FastLED.show();

  }
  // — left→right fill —
  void updateLTR(uint32_t el) {
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
        Serial.println("LTR");
		FastLED.show();
	}
	
  // — right→left fill —
  void updateRTL(uint32_t el) {
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
        Serial.println("RTL");
		FastLED.show();
	}
	

  // — center-out bloom —
  void updateCenter(uint32_t el) {
		for (int r = 0; r < part->numRanges; r++) {
			auto& L = part->ranges[r];
			int half = L.length / 2;
			int fillSize = (uint32_t)el * (half + 1) / duration;
			fillSize = min(fillSize, half);
	
			int mid = L.start + half;
			
			// Fill from center outward
			for (int i = 0; i <= fillSize; i++) {
				int leftIdx  = mid - i;
				int rightIdx = mid + i + (L.length % 2 == 0 ? 1 : 0);
	
				if (leftIdx >= L.start && leftIdx < L.start + L.length)
					leds[leftIdx] = color;
				if (rightIdx >= L.start && rightIdx < L.start + L.length)
					leds[rightIdx] = color;
			}
		}
        Serial.println("Center");
		FastLED.show();
	}

	// ————— non-blocking single-part fill helper —————
	void showBodyPartNoDelay(const BodyPart& part, CRGB color) {
		if (color == CRGB::Black && cs != &ALL_BLACK) return;
		for (int i = 0; i < part.numRanges; i++) {
			fill_solid(&leds[part.ranges[i].start], part.ranges[i].length, color);
		}
        Serial.println("showBodyPartNoDelay");
	}
	void paintColorSet() {
		// Whole
		showBodyPartNoDelay(whole, cs->whole);

		// Hat
		showBodyPartNoDelay(hat, cs->hat);
		showBodyPartNoDelay(hatMark, cs->hatMark);

		// Body (shirt + arms)
		showBodyPartNoDelay(body, cs->body);

		// Shirt
		showBodyPartNoDelay(shirt, cs->shirt);
		showBodyPartNoDelay(lowerShirt, cs->lowerShirt);
		showBodyPartNoDelay(leftZipper, cs->leftZipper);
		showBodyPartNoDelay(rightZipper, cs->rightZipper);
		showBodyPartNoDelay(collar, cs->collar);

		// Arms
		showBodyPartNoDelay(leftArm, cs->leftArm);
		showBodyPartNoDelay(rightArm, cs->rightArm);
		showBodyPartNoDelay(leftUpperArm, cs->leftUpperArm);
		showBodyPartNoDelay(leftLowerArm, cs->leftLowerArm);
		showBodyPartNoDelay(rightUpperArm, cs->rightUpperArm);
		showBodyPartNoDelay(rightLowerArm, cs->rightLowerArm);

		// Hands
		showBodyPartNoDelay(hands, cs->hands);
		showBodyPartNoDelay(leftHand, cs->leftHand);
		showBodyPartNoDelay(rightHand, cs->rightHand);

		// Legs
		showBodyPartNoDelay(legs, cs->legs);
		showBodyPartNoDelay(leftLeg, cs->leftLeg);
		showBodyPartNoDelay(rightLeg, cs->rightLeg);
		showBodyPartNoDelay(crotch, cs->crotch);
		showBodyPartNoDelay(leftCrotch, cs->leftCrotch);
		showBodyPartNoDelay(rightCrotch, cs->rightCrotch);

		// Feet
		showBodyPartNoDelay(feet, cs->feet);
		showBodyPartNoDelay(leftFoot, cs->leftFoot);
		showBodyPartNoDelay(rightFoot, cs->rightFoot);
    Serial.println("paintColorSet");
    FastLED.show();
  }
};

// ————— PLAYSTEP QUEUE —————
struct PlayStep {
  Animation animation;

  static PlayStep Create(const Animation& anim) {
    PlayStep p;
    p.animation = anim;
    return p;
  }
};


#pragma endregion

bool isMe(std::initializer_list<int> people) {
    for (int p : people) {
        if (PERSON == p) return true;
    }
    return false;
}

// **🔥 LED 停止**
void stopEffect() {
	FastLED.clear();
	FastLED.show();
}

// **120 BPM 拍子設定**
#define BPM 120
#define BEAT_TIME_2 (60000 / BPM)  // 每拍時間 (毫秒)

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

		Serial.println("✨ LED 120 BPM 拍子開始！");
		
		for (int i = 1; i <= 100; i++){
			setupPart_shutUAD(i);
		}
		
		totalSteps = sequence.size();
}

// 預寫好sequence 第二首
void setupPart_shutUAD(int partNumber) {
    Serial.println(partNumber);

    switch (partNumber) {
        case 1:
            // "Ooh, shut up and dance with me" 開頭 12拍
            for (int i = 0; i < 8; i++) {
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2)) );
            }
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            break;

        case 2:
            // "We were victims of the night" 8拍
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back(
                PlayStep::Create(
                    isMe({4}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2)
                )
            );
            sequence.push_back(
                PlayStep::Create(
                    isMe({2}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2)
                )
            );
            break;

        case 3:
            // "The chemical, physical, kryptonite" 8拍
            sequence.push_back(
                PlayStep::Create(
                    isMe({7}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2)
                )
            );
            sequence.push_back(
                PlayStep::Create(
                    isMe({3}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)
                              : Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back(
                PlayStep::Create(
                    isMe({2, 3}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                                 : Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2/2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            break;

        case 4:
            // "Helpless to the bass and faded light" 8拍
            sequence.push_back( PlayStep::Create(Animation::LTR(body, RED_1, BEAT_TIME_2*2)) );
            sequence.push_back( PlayStep::Create(Animation::RTL(body, PURPLE_1, BEAT_TIME_2*2)) );
            for (int p = 1; p <= 7; p++) {
                sequence.push_back(
                    PlayStep::Create(
                        isMe({p}) ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/7)
                                  : Animation::showColorSet(COLORSET_2_4, BEAT_TIME_2/7)
                    )
                );
            }
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/2)) );
            break;

        case 5:
            // "Oh, we were bound to get together, bound to get together"
            sequence.push_back(
                PlayStep::Create(
                    isMe({4,2,1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*3)
                                  : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*3)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
            sequence.push_back(
                PlayStep::Create(
                    isMe({7,3,1}) ? Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2*3)
                                  : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*3)
                )
            );
            break;

        case 6:
            // "She took my arm, I don't know how it happened"
            sequence.push_back(
                PlayStep::Create(
                    isMe({1}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)
                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)
                )
            );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
            for (int i = 0; i < 7; i++) {
                sequence.push_back(
                    PlayStep::Create(
                        isMe({1,3,7,6,5,4,2}) ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/7)
                                              : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/7)
                    )
                );
            }
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
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
            break;

        // 7-11跟前面同邏輯！要繼續我可以馬上幫你補上
        case 7:
        // "We took the floor and she said"
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );

        // 5～8拍：快速閃爍
        for (int i = 0; i < 16; i++) {
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/12)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/12)) );
            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/12)) );
        }
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

            for (int i = 0; i < 7; i++) {
                sequence.push_back( PlayStep::Create(
                    isMe({leftToRight[i]})
                        ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/3.5)
                        : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/3.5)
                ));
            }

            sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2*2)) );

            // "dance with me" 快速閃爍
            for (int i = 0; i < 8; i++) {
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/12)) );
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2/12)) );
                sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2/12)) );
            }

            sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        }
        break;

    case 10:
        // "This woman is my destiny, she said"
        sequence.push_back( PlayStep::Create(Animation::showColorSet(ALL_BLACK, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(
            isMe({2,3})
                ? Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2/2)
                : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2/2)
        ));
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_2, BEAT_TIME_2)) );
        sequence.push_back( PlayStep::Create(Animation::showColorSet(COLORSET_2_1, BEAT_TIME_2)) );
        break;

    case 11:
        // "Ooh, shut up and dance with me"
        sequence.push_back( PlayStep::Create(
            isMe({4})
                ? Animation::showColorSet(COLORSET_2_3, BEAT_TIME_2*4)
                : Animation::showColorSet(ALL_BLACK, BEAT_TIME_2*4)
        ));
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
}
  