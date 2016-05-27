typedef struct { float t, deltat, previoust;
    } Time;
extern Time time;

typedef struct { int frames;
	float frameRate, frameRateInterval, lastFrameRateT;
	} Fps;
extern Fps fps;

extern int globalSegments;