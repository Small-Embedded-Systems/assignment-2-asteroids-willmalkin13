/* Asteroids Model */
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some insitial struct types if you want to usd them */
struct ship {
    coordinate_t p;
    vector_t     v;
};

/* initial struts for building linked lists */
struct rock {
    coordinate_t p;
    struct rock *next;
};

struct missile {
    coordinate_t p;
    struct missile *next;
};

void physics(void);
