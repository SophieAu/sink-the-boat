int globalSegments;

typedef struct { float t, deltat, previoust;
    } Time;
Time time;

typedef struct { int frames;
	float frameRate, frameRateInterval, lastFrameRateT;
	} Fps;
Fps fps;