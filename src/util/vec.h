#ifndef VEC_INCLUDED
#define VEC_INCLUDED

class vec2
{
public:
    vec2();
    vec2(float x, float y);
    vec2(const vec2 &v);

    float length() const;
    float angle() const;

    void operator+=(const vec2 &v);
    void operator-=(const vec2 &v);
    void operator*=(float f);
    void operator/=(float f);
    vec2 operator/(float f) const;
    vec2 operator*(float f) const;

    vec2 proj(const vec2 &v) const;
    vec2 proj(const vec2 &v1, const vec2 &v2) const;
    vec2 rot(float angle) const;

    bool isInside(vec2 pos, vec2 dim) const;

    vec2 getVectWithLength(float norm) const;
    float distLine(const vec2 &A, const vec2 &B) const;
    float distSegt(const vec2 &A, const vec2 &B) const;

    vec2 normalize() const;

    float x, y;
};

vec2 operator+(const vec2 &v1, const vec2 &v2);
vec2 operator-(const vec2 &v1, const vec2 &v2);
vec2 operator*(const vec2 &v1, const vec2 &v2);
vec2 operator/(const vec2 &v1, const vec2 &v2);
float scal(const vec2 &v1, const vec2 &v2);
float vect(const vec2 &v1, const vec2 &v2);
bool operator!=(const vec2 &v1, const vec2 &v2);
bool operator==(const vec2 &v1, const vec2 &v2);

#endif
