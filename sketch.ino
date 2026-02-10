#define RED_LED     25
#define YELLOW_LED  26
#define GREEN_LED   27

#define PED_BUTTON  33
#define EMG_BUTTON  32

enum State {
  RED,
  GREEN,
  YELLOW,
  PEDESTRIAN,
  EMERGENCY
};

State currentState = RED;
unsigned long stateStartTime = 0;

volatile bool pedRequest = false;
volatile bool emgRequest = false;

// ---------- INTERRUPTS ----------
void IRAM_ATTR handlePedestrian() {
  pedRequest = true;
}

void IRAM_ATTR handleEmergency() {
  emgRequest = true;
}

// ---------- SETUP ----------
void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(PED_BUTTON, INPUT_PULLUP);
  pinMode(EMG_BUTTON, INPUT_PULLUP);

  attachInterrupt(PED_BUTTON, handlePedestrian, FALLING);
  attachInterrupt(EMG_BUTTON, handleEmergency, FALLING);

  stateStartTime = millis();
}

// ---------- HELPERS ----------
void setLights(bool r, bool y, bool g) {
  digitalWrite(RED_LED, r);
  digitalWrite(YELLOW_LED, y);
  digitalWrite(GREEN_LED, g);
}

// ---------- LOOP ----------
void loop() {
  unsigned long now = millis();

  // 🚑 Emergency has HIGHEST priority
  if (emgRequest && currentState != EMERGENCY) {
    emgRequest = false;
    currentState = EMERGENCY;
    stateStartTime = now;
  }

  switch (currentState) {

    case RED:
      setLights(HIGH, LOW, LOW);
      if (now - stateStartTime >= 5000) {
        currentState = GREEN;
        stateStartTime = now;
      }
      break;

    case GREEN:
      setLights(LOW, LOW, HIGH);

      if (pedRequest) {
        pedRequest = false;
        currentState = PEDESTRIAN;
        stateStartTime = now;
      }
      else if (now - stateStartTime >= 5000) {
        currentState = YELLOW;
        stateStartTime = now;
      }
      break;

    case YELLOW:
      setLights(LOW, HIGH, LOW);
      if (now - stateStartTime >= 2000) {
        currentState = RED;
        stateStartTime = now;
      }
      break;

    case PEDESTRIAN:
      setLights(LOW, HIGH, LOW);
      if (now - stateStartTime >= 2000) {
        currentState = RED;
        stateStartTime = now;
      }
      break;

    case EMERGENCY:
      setLights(HIGH, LOW, LOW);
      if (now - stateStartTime >= 8000) {
        currentState = GREEN;
        stateStartTime = now;
      }
      break;
  }
}
