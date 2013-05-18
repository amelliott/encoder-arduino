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
        // TODO: Allow NULL for onLeft and onRight
        static Encoder * registerEncoder(int pinA, int pinB, void(*)() = 0, void(*)() = 0);
        static void onInterrupt();
    private:
        static Encoder mEncoders[NUM_ENCODERS];
        static int mNumEncoders;

};

