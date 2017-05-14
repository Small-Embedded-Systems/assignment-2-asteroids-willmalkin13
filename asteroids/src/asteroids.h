/* Game state */

extern float Elapsed_time; /* Time this ship has been active */
extern int   Score;        /* Total Score so far */
extern int   Lives;        /* Lives remaining */
extern int Shield;				 /* Hits that can be taken before death */
extern bool Pause;				 /* Stops play when true */
extern struct ship player; /* The players position and movement */

extern const float Dt; /* Time step for physics, needed for consistent motion */
