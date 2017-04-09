class v2f {
public:
    f32 x = 0, y = 0;

    v2f() {}
    v2f(f32 x, f32 y) :
        x{x},
        y{y} {}

    v2f(f32 v) :
        v2f{v, v} {}

    const char* str() {
        sprintf(buf, "(%g %g)", x, y);
        return buf;
    }

    f32 len() const {
        return sqrt(x * x + y * y);
    }

#define do_op(o) \
    inline void operator o##= (const v2f& v) { x o##= v.x; y o##= v.y; }       \
    inline void operator o##= (f32 f)        { x o##= f; y o##= f; }           \
    v2f operator o (const v2f& v) const      { return v2f{x o v.x, y o v.y}; } \
    v2f operator o (f32 f) const             { return v2f{x o f, y o f}; }

    do_op(+)
    do_op(-)
    do_op(*)
    do_op(/)

#undef do_op

protected:
    // this is used for formatting with str()
    // without having to pass copies of the string around
    // obviously not thread safe
    char buf[42] = { 0 };
};

