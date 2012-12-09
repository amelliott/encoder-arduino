#define NUM_ENCODERS 1

class Encoder {
    public:
        static void registerEncoder(int pinA, int pinB);
        static void deregisterEncoder(volatile Encoder *);
        static void onInterrupt();
    private:
        static int mPinA[NUM_ENCODERS];
        static int mPinB[NUM_ENCODERS];
        static volatile int mPrevPinAVal[NUM_ENCODERS];
        static volatile int mPrevPinBVal[NUM_ENCODERS];
        static int mNumEncoders;

};

