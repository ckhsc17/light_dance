#include <FastLED.h>
#include <vector>

// LED 燈條設定
#define LED_PIN 4             // LED 燈條 Data Pin (可改成你的 GPIO)
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
	CRGB whole		  = CRGB::Black;
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

#pragma endregion

#pragma region Function declaration

enum AnimKind {
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

  // rainbow params
  uint8_t         startHue, hueStep, sat, val;
  // color-set
  const ColorSet* cs;
  // fill effects
  const BodyPart* part;
  CRGB            color;

	std::vector<const BodyPart*> extraParts;
	std::vector<CRGB>            extraColors;

  // — begin methods —
  void beginRainbow(int dur, uint8_t sH, uint8_t hS, uint8_t S, uint8_t V) {
    kind      = AnimKind::RAINBOW;
    startHue  = sH; hueStep = hS; sat = S; val = V;
    duration  = dur;
    startMs   = millis();
    active    = true;
  }
  void beginColorSet(const ColorSet& _cs, int dur) {
		
    kind      = AnimKind::COLORSET_BEAT;
    cs        = &_cs;
    duration  = dur;
    startMs   = millis();

    paintColorSet();
    active    = true;
  }
  void beginLTR(const BodyPart& P, CRGB c, int dur) {
    kind      = AnimKind::LTR;
    part      = &P;
    color     = c;
    duration  = dur;
    startMs   = millis();
    active    = true;
  }
  void beginRTL(const BodyPart& P, CRGB c, int dur) {
    kind      = AnimKind::RTL;
    part      = &P;
    color     = c;
    duration  = dur;
    startMs   = millis();
    active    = true;
  }
  void beginCenter(const BodyPart& P, CRGB c, int dur) {
    kind      = AnimKind::CENTER_OUT;
    part      = &P;
    color     = c;
    duration  = dur;
    startMs   = millis();
    active    = true;
  }
  void beginColorSetPlusParts(const ColorSet& colorset, const std::vector<const BodyPart*>& extraBodyPart, const std::vector<CRGB>& extraColor, int dur){
		kind        = AnimKind::COLORSET_PLUS_PARTS;
		cs          = &colorset;
		extraParts  = extraBodyPart;
		extraColors = extraColor;
		duration    = dur;
		startMs     = millis();
		// paint ColorSet
		paintColorSet();
		// paint each extra in order
		for (size_t i = 0; i < extraParts.size(); i++) {
			showBodyPartNoDelay(*extraParts[i], extraColors[i]);
		}
		FastLED.show();
		active = true;
	}
	void beginShowColor(const BodyPart& P, CRGB c, int dur) {
		kind      = SHOW_COLOR;
		part      = &P;
		color     = c;
		duration  = dur;
		startMs   = millis();
		showBodyPartNoDelay(P, c);
		FastLED.show();
		active    = true;
	}
	void begin() {
    startMs = millis();
    active  = true;
    switch(kind) {
      case COLORSET_BEAT:
        paintColorSet();
        break;
      case COLORSET_PLUS_PARTS:
        paintColorSet();
        for (size_t i = 0; i < extraParts.size(); i++)
          showBodyPartNoDelay(*extraParts[i], extraColors[i]);
        FastLED.show();
        break;
      case SHOW_COLOR:
        showBodyPartNoDelay(*part, color);
        FastLED.show();
        break;
      default:
        // RAINBOW, LTR, RTL, CENTER_OUT animate in update()
        break;
    }
  }

  // — update (call in loop) —
  bool update() {
    if (!active) return false;
    uint32_t now = millis();
    uint32_t el  = now - startMs;
    if (el >= (uint32_t)duration) {
      active = false;
      return false;
    }
    switch(kind) {
      case RAINBOW:      updateRainbow(el);  break;
      case LTR:          updateLTR(el);      break;
      case RTL:          updateRTL(el);      break;
      case CENTER_OUT:   updateCenter(el);   break;
			case COLORSET_BEAT: 					         break; // Static doesn't need update
			case COLORSET_PLUS_PARTS:							 break;
			case SHOW_COLOR:   							       break;
			
    }
    return true;
  }

private:
  // — rainbow sweep —
  void updateRainbow(uint32_t el) {
    uint8_t frame = (uint32_t)el * 255 / duration;
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i] = CHSV(startHue + frame + i * hueStep, sat, val);
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
		FastLED.show();
	}

	// ————— non-blocking single-part fill helper —————
	void showBodyPartNoDelay(const BodyPart& part, CRGB color) {
		if (color == CRGB::Black && cs != &ALL_BLACK) return;
		for (int i = 0; i < part.numRanges; i++) {
			fill_solid(&leds[part.ranges[i].start], part.ranges[i].length, color);
		}
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
    FastLED.show();
  }
};

// ————— PLAYSTEP QUEUE —————
struct PlayStep {
	AnimKind        kind;
	int             duration;
	uint8_t         startHue, hueStep, sat, val;
	const ColorSet* cs;
	const BodyPart* part;
	CRGB            color;

	std::vector<const BodyPart*> extraParts;
	std::vector<CRGB>            extraColors;

  std::vector<Animation> subAnimations;
private:
	// private default ctor so users can't accidentally bypass our factories
	PlayStep() : kind(RAINBOW), duration(0), startHue(0), hueStep(1), sat(255), val(255),
							 cs(nullptr), part(nullptr), color(CRGB::Black) {}

public:
	// ——— Rainbow factory ———
	static PlayStep Rainbow(int dur, uint8_t startHue = 0, uint8_t hueStep = 1, uint8_t SAT = 255, uint8_t VAL = 255)
	{
		PlayStep p;
		p.kind      = AnimKind::RAINBOW;
		p.duration  = dur;
		p.startHue  = startHue;
		p.hueStep   = hueStep;
		p.sat       = SAT;
		p.val       = VAL;
		return p;
	}

	// ——— ColorSet hold factory ———
	static PlayStep showColorSet(const ColorSet& colorset, int duration)
	{
		PlayStep p;
		p.kind      = AnimKind::COLORSET_BEAT;
		p.duration  = duration;
		p.cs        = &colorset;
		return p;
	}

	// ——— Left-to-Right factory ———
	static PlayStep LTR(const BodyPart& P, CRGB color, int duration)
	{
		PlayStep p;
		p.kind      = AnimKind::LTR;
		p.duration  = duration;
		p.part      = &P;
		p.color     = color;
		return p;
	}

	// ——— Right-to-Left factory ———
	static PlayStep RTL(const BodyPart& bodyPart, CRGB color, int duration)
	{
		PlayStep p;
		p.kind      = AnimKind::RTL;
		p.duration  = duration;
		p.part      = &bodyPart;
		p.color     = color;
		return p;
	}

	// ——— Center-Out factory ———
	static PlayStep Center(const BodyPart& bodyPart, CRGB color, int duration)
	{
		PlayStep p;
		p.kind      = AnimKind::CENTER_OUT;
		p.duration  = duration;
		p.part      = &bodyPart;
		p.color     = color;
		return p;
	}

	// ——— ColorSet + extras factory ———
	static PlayStep showColorPlusParts(const ColorSet& colorset, const std::vector<const BodyPart*>& extraBodyParts, const std::vector<CRGB>& extraColor, int duration)
	{
		PlayStep p;
		p.kind       = AnimKind::COLORSET_PLUS_PARTS;
		p.duration   = duration;
		p.cs         = &colorset;
		p.extraParts = extraBodyParts;
		p.extraColors = extraColor;
		return p;
	}
	static PlayStep showColor(const BodyPart& P, CRGB c, int dur) {
		PlayStep p;
		p.kind     = SHOW_COLOR;
		p.part     = &P;
		p.color    = c;
		p.duration = dur;
		return p;
	}

	static PlayStep multi(std::initializer_list<Animation> anims, int dur) {
    PlayStep p;
    p.kind = MULTI;
    p.duration = dur;
    p.subAnimations = anims;
    return p;
  }
};


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
#define TOTAL_BARS 8             // 總小節數

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
		sequence.push_back( PlayStep::LTR(whole, WHITE_1, BEAT_TIME*8) );
		/*
		
		for (int i = 1; i <= 100; i++){
				setupPart(i);
		}
				*/
		totalSteps = sequence.size();
}

// HIGHLIGHT:
/* Sequence Example
sequence.push_back( PlayStep::Rainbow(BEAT_TIME*7, 0,1,150,255) );
sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );

if (PERSON == 1) {
	sequence.push_back( PlayStep::showColorSet(COLORSET_1, BEAT_TIME*2) );
} else {
	sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
}
sequence.push_back( PlayStep::LTR(leftHand, CRGB::Blue, BEAT_TIME) );
*/

void setupPart(int partNumber) {
		Serial.println(partNumber);

		switch(partNumber)
		{
				case 1: 
					sequence.push_back( PlayStep::Rainbow(BEAT_TIME*7, 0, 1, 150) );
					break;
				case 2: // 登登登登登登登
					sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					sequence.push_back( PlayStep::Rainbow(BEAT_TIME*6, 255, 1, 150) );
					break;
				case 3: // 1號亮
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 4: // 全亮
						sequence.push_back( PlayStep::Rainbow(BEAT_TIME*10, 120, 1, 150) );
					break;
				case 5:
					break;
				case 6: // Said baby 4567暗 
					if (PERSON >= 4 && PERSON <= 7)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 7: // Said baby 全暗 
					sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*1) );
					break;
				case 8: // Said baby 全亮 
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1) );
					break;
				case 9: 
					sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*1) );
					break;
				case 10: // What you doing?
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 11: // (What you doing?)
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;      
				case 12: // Where you at?
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 13: // (Where you at?)
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;              
				case 14: // Oh, you got plans?
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 15: // (You got plans?)
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;      
				case 16: // Don't say that
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 17: // (shut your trap)
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 18: // I'm sippin' wine 1 亮 頭黃
					if (PERSON == 1) {
						sequence.push_back([&](){
							std::vector<const BodyPart*> extras = { &hat };
							std::vector<CRGB> colors = {YELLOW_1};
							return PlayStep::showColorPlusParts(ALL_WHITE, extras, colors, BEAT_TIME*1);
						}());
					}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*1) );
					break;
				case 19: // (sip sip) 1 亮 領子黃、衣服黃
					if (PERSON == 1) {
						sequence.push_back([&](){
							std::vector<const BodyPart*> extras = { &collar };
							std::vector<CRGB> colors = {YELLOW_1};
							return PlayStep::showColorPlusParts(ALL_WHITE, extras, colors, BEAT_TIME*1);
						}());
						sequence.push_back([&](){
							std::vector<const BodyPart*> extras = { &lowerShirt, &leftZipper, &rightZipper, &arms };
							std::vector<CRGB> colors = {YELLOW_1, YELLOW_1, YELLOW_1, YELLOW_1};
							return PlayStep::showColorPlusParts(ALL_WHITE, extras, colors, BEAT_TIME*1);
						}());
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1) );
					}
					else 
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3) );
					break;
				case 20: // in a robe
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;    
				case 21: // (drip, drip)
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 22: // I look too good
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 23: // (look too good)
					if (PERSON == 1)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
							sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 24: // to be alone
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*1) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*1) );
					break;
				case 25: // (woo woo) 全亮
					sequence.push_back([&](){
						std::vector<const BodyPart*> extras = { &hands };
						std::vector<CRGB> colors = {YELLOW_1};
						return PlayStep::showColorPlusParts(ALL_WHITE, extras, colors, BEAT_TIME*2);
					}());
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;  
				case 26: // My house clean 1亮
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 27: // (house clean)
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 28: // My pool warm 全亮
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					break;
				case 29: // (pool warm) 4 2 5 1 6 3 7
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					if (PERSON == 2)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					if (PERSON == 5)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					break;
				case 30: // Just shaved
					if (PERSON == 6)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					if (PERSON == 3)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					if (PERSON == 7)
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME/2) );
					break;
				case 31: // (smooth like a newborn) // 1亮
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*6) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*6) );					
					break;
				case 32: // We should be dancing 1 3 7亮
					if (PERSON == 1 || PERSON == 3 || PERSON == 7)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 33: // romancing 1 2 4亮
					if (PERSON == 1 || PERSON == 2 || PERSON == 4)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 34: // In the east wing 4亮
					if (PERSON == 1 || PERSON == 2 || PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					if (PERSON == 4)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 35: // and the west wing（三連音） 4亮
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*4/3) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*4/3) );
					break;
				case 36: // and the west wing（三連音）
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*4/3) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*4/3) );
					break;
				case 37: // and the west wing（三連音）
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*4/3) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*4/3) );
					break;
				case 38: // Of this mansion
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 39: // what's happening?
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
				break;
				case 40: // I aint playing 4 7 亮 3 被敲兩下 // 3 YELLOW
					if (PERSON == 4 || PERSON == 7)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 3)
						for (int i = 0; i < 2; i++){
							sequence.push_back( PlayStep::showColor(whole, YELLOW_1, BEAT_TIME/2) );
							sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
						}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 41: // no games 1 被敲一下 // 1 PURPLE
					if (PERSON == 4 || PERSON == 7)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 1){
						sequence.push_back( PlayStep::showColor(whole, PURPLE_1, BEAT_TIME/2) );
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
					}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 42: // Every word that 3 被敲兩下 // 3 YELLOW
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 3)
						for (int i = 0; i < 2; i++){
							sequence.push_back( PlayStep::showColor(whole, YELLOW_1, BEAT_TIME/2) );
							sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
						}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 43: // I say 1 被敲一下 // 1 PURPLE
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 1){
						sequence.push_back( PlayStep::showColor(whole, PURPLE_1, BEAT_TIME/2) );
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
					}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 44: // Is  6 被敲兩下 // 6 RED
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 6)
						for (int i = 0; i < 2; i++){
							sequence.push_back( PlayStep::showColor(whole, RED_1, BEAT_TIME/2) );
							sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
						}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 45: // coming straight 2 被敲一下 // 2 BLUE
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 2){
						sequence.push_back( PlayStep::showColor(whole, LIGHT_BLUE_1, BEAT_TIME/2) );
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
					}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 46: // from the 5 被敲四下, 2 6 3/2拍後被敲一下 // 5 GREEN
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 5){
						for (int i = 0; i < 4; i++){
							sequence.push_back( PlayStep::showColor(whole, GREEN_1, BEAT_TIME/4) );
							sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/4) );
						}
					}
					else if (PERSON == 2){
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
						sequence.push_back( PlayStep::showColor(whole, LIGHT_BLUE_1, BEAT_TIME/2) );
					}
					else if (PERSON == 6){
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
						sequence.push_back( PlayStep::showColor(whole, RED_1, BEAT_TIME/2) );
					}
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 47: // heart 1 3 正拍被敲一下
					if (PERSON == 4 || PERSON == 7)
							sequence.push_back( PlayStep::showColorSet(COLORSET_1_FRONT, BEAT_TIME*2) );
					else if (PERSON == 1) {
						sequence.push_back( PlayStep::showColor(whole, PURPLE_1, BEAT_TIME/2) );
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
					} 
					else if (PERSON == 3) {
						sequence.push_back( PlayStep::showColor(whole, YELLOW_1, BEAT_TIME/2) );
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*3/2) );
					} 
					else 
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 48: // So if you  全亮
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					break;
				case 49: // tryna 
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					break;
				case 50: // lay in 
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					break;
				case 51: // these arms 4亮 其他閃爍 Total:Beat Time*4
					for (int i = 0; i < 16; i++){
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/8) );
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/8) );
					}
					break;
				case 52: // 
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					break;
				case 53: // I'ma 4亮 其他暗
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2/3) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2/3) );
					break;
				case 54: // leave the 
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2/3) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2/3) );
					break;
				case 55: // door
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2/3) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2/3) );
					break;
				case 56: // open
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*6) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*6) );
					break;
				case 57: // (I'ma leave  4 亮，向右踏全亮，轉身暗
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
					break;
				case 58: // the door open)   第3拍對到彈指 => 每拍向右亮 6 3 7
					if (PERSON == 4 || PERSON == 6)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*4) );
					else if (PERSON == 3)
					{
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*1) );
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*3) );
					} else if (PERSON == 7)
					{
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					} else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*4) );
					break;
				case 59: // I'ma leave the   第3拍對到彈指 => 每拍向左亮 5 2 1
					if (PERSON == 4 || PERSON == 6 || PERSON == 3 || PERSON == 7 || PERSON == 5)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*4) );
					else if (PERSON == 2)
					{
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*1) );
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*3) );
					} else if (PERSON == 1)
					{
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*2) );
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*2) );
					}
					break;
				case 60: // door open, girl
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*4) );
					break;
				case 61: // (I'ma leave the
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*4) );
					break;
				case 62: // door open   手向左揮可以加特效
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*4) );
					break;
				case 63: // hoping)    手向右揮可以加特效
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*4) );
					break;
				case 64: // That you  七個人交互著閃爍四拍
					// 
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
				
					if (PERSON == 5)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					break;
				case 65: // feel the
					if (PERSON == 2)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );

					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					break;
				case 66: // way I
					if (PERSON == 3)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );

					if (PERSON == 7)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					break;
				case 67: // feel And
					if (PERSON == 1)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );

					if (PERSON == 5)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME/2) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME/2) );
					break;
				case 68: // you 4 亮
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					break;
				case 69: // want me　
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					break;
				case 70: // like I
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					break;
				case 71: // want  
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					break;
				case 72: // tonight,
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					break;
				case 73: // bae-
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME) );
					break;
				case 74: // be 第一拍全亮
					sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*6) );
					break;
				case 75: // (Tell me that you're coming through)
					sequence.push_back( PlayStep::Rainbow(BEAT_TIME*8, 0, 1, 150) );
					break;
				case 76: // ooh 4 亮
					if (PERSON == 4)
						sequence.push_back( PlayStep::showColorSet(COLORSET_1_BACK, BEAT_TIME*8) );
					else
						sequence.push_back( PlayStep::showColorSet(ALL_BLACK, BEAT_TIME*8) );
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
      switch(s.kind) {
        case RAINBOW:
          anim.beginRainbow(s.duration, s.startHue, s.hueStep, s.sat, s.val);
          break;
        case COLORSET_BEAT:
          anim.beginColorSet(*s.cs, s.duration);
          break;
        case LTR:
          anim.beginLTR(*s.part, s.color, s.duration);
          break;
        case RTL:
          anim.beginRTL(*s.part, s.color, s.duration);
          break;
        case CENTER_OUT:
          anim.beginCenter(*s.part, s.color, s.duration);
          break;
				case COLORSET_PLUS_PARTS:
          anim.beginColorSetPlusParts(
            *s.cs,
            s.extraParts,
            s.extraColors,
            s.duration
          );
          break;
		  	case SHOW_COLOR:
					anim.beginShowColor(*s.part, s.color, s.duration);
					break;
				default:
					stopEffect();
					break;
      }
    } else {
      // all done
      stopEffect();
      while(true) delay(1000);
    }
  }

  // you can do other non-blocking work here…
}

