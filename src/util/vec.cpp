#include "vec.h"
#include <cmath>

vec2::vec2() : x(0), y(0)
{

}

vec2::vec2(float a, float b) : x(a), y(b)
{

}

vec2::vec2(const vec2 &v) : x(v.x), y(v.y)
{

}


float vec2::length() const
{
    return sqrt(x*x+y*y);
}

float vec2::angle() const
{
    if(x == 0)
        return y>0 ? 3.14/2:-3.14/2;
    return x>0 ? atan(y/x) : atan(y/x)+3.14;
}

void vec2::operator+=(const vec2 &v)
{
    x += v.x;
    y += v.y;
}

void vec2::operator-=(const vec2 &v)
{
    x -= v.x;
    y -= v.y;
}

void vec2::operator*=(float f)
{
    x *= f;
    y *= f;
}

void vec2::operator/=(float f)
{
    x /= f;
    y /= f;
}

vec2 vec2::operator*(float f) const
{
    return vec2(x*f, y*f);
}

vec2 vec2::operator/(float f) const
{
    return vec2(x/f, y/f);
}

vec2 vec2::proj(const vec2 &v) const
{
    return v.getVectWithLength(scal(*this, v)/v.length());
}

vec2 vec2::proj(const vec2 &v1, const vec2 &v2) const
{
    return v1 + ((*this)-v1).proj(v2-v1);
}

vec2 vec2::rot(float angle) const
{
    return vec2(0, 0);
}

bool vec2::isInside(vec2 pos, vec2 dim) const
{
    return x >= pos.x && x < pos.x + dim.x && y > pos.y && y < pos.y + dim.y;
}

float scal(const vec2 &v1, const vec2 &v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}

float vect(const vec2 &v1, const vec2 &v2)
{
    return v1.x*v2.y-v1.y*v2.x;
}

vec2 operator+(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x+v2.x, v1.y+v2.y);
}

vec2 operator-(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x-v2.x, v1.y-v2.y);
}

vec2 operator*(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x*v2.x, v1.y*v2.y);
}

vec2 operator/(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x/v2.x, v1.y/v2.y);
}

vec2 vec2::getVectWithLength(float l) const
{
    return vec2(x, y)/length()*l;
}

float vec2::distLine(const vec2 &A, const vec2 &B) const
{
    return ((*this)-this->proj(A, B)).length();
}

float vec2::distSegt(const vec2 &A, const vec2 &B) const
{
    vec2 OA = A-(*this), OB = B-(*this), AB = B-A;
    if(scal(OA, AB) > 0)
        return OA.length();
    else if(scal(OB, AB) < 0)
        return OB.length();
    else return distLine(A, B);
}

bool operator==(const vec2 &v1, const vec2 &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const vec2 &v1, const vec2 &v2)
{
    return !(v1==v2);
}

vec2 vec2::normalize() const
{
    return vec2(x/length(), y/length());
}
