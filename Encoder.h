#define NUM_ENCODERS 1

struct Encoder {
    int pinA;
    int pinB;
    volatile int oldTurn;
    volatile int turnCount;
    volatile int oldPos;
    void (*onLeft)();
    void (*onRight)();
};

class EncoderManager {
    public:
        static void registerEncoder(int pinA, int pinB, void(*)(), void(*)());
        static void onInterrupt();
    private:
        static Encoder mEncoders[NUM_ENCODERS];
        static int mPinA[NUM_ENCODERS];
        static int mPinB[NUM_ENCODERS];
        static volatile int mPrevPinAVal[NUM_ENCODERS];
        static volatile int mPrevPinBVal[NUM_ENCODERS];
        static int mNumEncoders;

};

