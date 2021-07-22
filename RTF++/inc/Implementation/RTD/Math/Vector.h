#include <utility>
#include <Implementation/RTD/Strings/String.h>

//
// Created by kiper220 on 14.06.2021.
//

#ifndef REDTEXTAPPLICATION_MATH_VECTOR_H
#define REDTEXTAPPLICATION_MATH_VECTOR_H


namespace RTF{
    namespace Math {
        template<typename T>
        class Vector2 {
        public:
            Vector2(const Vector2 &vector2) : x(vector2.x), y(vector2.y) {}

            Vector2(T x, T y) : x(x), y(y) {}


            T &GetFirstVector() {
                return this->x;
            }

            T &GetSecondVector() {
                return this->y;
            }


            T &SetFirstVector(T &x) {
                this->x = x;
                return this->x;
            }

            T &SetSecondVector(T &y) {
                this->y = y;
                return this->y;
            }


            Vector2 &operator()(T &x, T &y) {
                this->x = x;
                this->y = y;

                return *this;
            }

            Vector2 &operator()(const Vector2 &vector2) {
                this->x = vector2.x;
                this->y = vector2.y;

                return *this;
            }

            virtual bool operator==(const Vector2 &vector2) {
                return
                        this->x == vector2.x &&
                        this->y == vector2.y;
            }

            bool operator!=(const Vector2 &vector2) {
                return !this->operator==(vector2);
            }

            Vector2 &operator=(const Vector2 &vector2) {
                this->x = vector2.x;
                this->y = vector2.y;
                return *this;
            }

            T x, y;
        };

        template<typename T>
        class Vector3 {
        public:
            Vector3(const Vector3 &vector3) : x(vector3.x), y(vector3.y), z(vector3.z) {}

            Vector3(T x, T y, T z) : x(x), y(y), z(z) {}


            T &GetFirstVector() {
                return this->x;
            }

            T &GetSecondVector() {
                return this->y;
            }

            T &GetThirdVector() {
                return this->z;
            }


            T &SetFirstVector(T &x) {
                this->x = x;
                return this->x;
            }

            T &SetSecondVector(T &y) {
                this->y = y;
                return this->y;
            }

            T &SetThirdVector(T &z) {
                this->z = z;
                return this->z;
            }


            Vector3 &operator()(T &x, T &y, T &z) {
                this->x = x;
                this->y = y;
                this->z = z;

                return *this;
            }

            Vector3 &operator()(const Vector3 &vector3) {
                this->x = vector3.x;
                this->y = vector3.y;
                this->z = vector3.z;

                return *this;
            }

            virtual bool operator==(const Vector3 &vector3) {
                return
                        this->x == vector3.x &&
                        this->y == vector3.y &&
                        this->z == vector3.z;
            }

            bool operator!=(const Vector3 &vector3) {
                return !this->operator==(vector3);
            }

            Vector3 &operator=(const Vector3 &vector3) {
                this->x = vector3.x;
                this->y = vector3.y;
                this->z = vector3.z;
                return *this;
            }

            T x, y, z;
        };

        template<typename T>
        class Vector4 {
        public:
            Vector4(const Vector4 &vector4) : x(vector4.x), y(vector4.y), z(vector4.z), s(vector4.s) {}

            Vector4(T x, T y, T z, T s) : x(x), y(y), z(z), s(s) {}


            T &GetFirstVector() {
                return this->x;
            }

            T &GetSecondVector() {
                return this->y;
            }

            T &GetThirdVector() {
                return this->z;
            }

            T &GetFourthVector() {
                return this->s;
            }


            T &SetFirstVector(const T &x) {
                this->x = x;
                return this->x;
            }

            T &SetSecondVector(const T &y) {
                this->y = y;
                return this->y;
            }

            T &SetThirdVector(const T &z) {
                this->z = z;
                return this->z;
            }

            T &SetFourthVector(const T &s) {
                this->s = s;
                return this->s;
            }


            Vector4 &operator()(const T &x, const T &y, const T &z, const T &s) {
                this->x = x;
                this->y = y;
                this->z = z;
                this->s = s;

                return *this;
            }

            Vector4 &operator()(const Vector4 &vector4) {
                this->x = vector4.x;
                this->y = vector4.y;
                this->z = vector4.z;
                this->s = vector4.s;

                return *this;
            }

            virtual bool operator==(const Vector4 &vector4) {
                return
                        this->x == vector4.x &&
                        this->y == vector4.y &&
                        this->z == vector4.z &&
                        this->s == vector4.s;
            }

            bool operator!=(const Vector4 &vector4) {
                return !this->operator==(vector4);
            }

            Vector4 &operator=(const Vector4 &vector4) {
                this->x = vector4.x;
                this->y = vector4.y;
                this->z = vector4.z;
                this->s = vector4.s;
                return *this;
            }

            T x, y, z, s;
        };


        class BVector2 : public Vector2<bool> {
        public:
            BVector2();
            BVector2(bool x, bool y);
        };

        class BVector3 : public Vector3<bool> {
        public:
            BVector3();
            BVector3(bool x, bool y, bool z);
        };

        class BVector4 : public Vector4<bool> {
        public:
            BVector4();
            BVector4(bool x, bool y, bool z, bool s);
        };


        class SVector2 : public Vector2<Strings::String> {
        public:
            SVector2();
            SVector2(Strings::String x, Strings::String y);
        };

        class SVector3 : public Vector3<Strings::String>{
        public:
            SVector3();
            SVector3(Strings::String x, Strings::String y, Strings::String z);
        };

        class SVector4 : public Vector4<Strings::String>{
        public:
            SVector4();
            SVector4(Strings::String x, Strings::String y, Strings::String z, Strings::String s);
        };


        class IVector2 : public Vector2<int>{
        public:
            IVector2();
            IVector2(int x, int y);

            IVector2 operator+(const IVector2& vector2);
            IVector2 operator+(int i);

            IVector2 operator-(const IVector2& vector2);
            IVector2 operator-(int i);

            IVector2 operator*(const IVector2& vector2);
            IVector2 operator*(int i);

            IVector2 operator/(const IVector2& vector2);
            IVector2 operator/(int i);

            IVector2& operator+=(const IVector2& vector2);
            IVector2& operator+=(int i);

            IVector2& operator-=(const IVector2& vector2);
            IVector2& operator-=(int i);

            IVector2& operator*=(const IVector2& vector2);
            IVector2& operator*=(int i);

            IVector2& operator/=(const IVector2& vector2);
            IVector2& operator/=(int i);
        };
        class IVector3 : public Vector3<int>{
        public:
            IVector3();
            IVector3(int x, int y, int z);

            IVector3 operator+(const IVector3& vector3);
            IVector3 operator+(int i);

            IVector3 operator-(const IVector3& vector3);
            IVector3 operator-(int i);

            IVector3 operator*(const IVector3& vector3);
            IVector3 operator*(int i);

            IVector3 operator/(const IVector3& vector3);
            IVector3 operator/(int i);

            IVector3& operator+=(const IVector3& vector3);
            IVector3& operator+=(int i);

            IVector3& operator-=(const IVector3& vector3);
            IVector3& operator-=(int i);

            IVector3& operator*=(const IVector3& vector3);
            IVector3& operator*=(int i);

            IVector3& operator/=(const IVector3& vector3);
            IVector3& operator/=(int i);

        };
        class IVector4 : public Vector4<int>{
        public:
            IVector4();
            IVector4(int x, int y, int z, int s);

            IVector4 operator+(const IVector4& vector4);
            IVector4 operator+(int i);

            IVector4 operator-(const IVector4& vector4);
            IVector4 operator-(int i);

            IVector4 operator*(const IVector4& vector4);
            IVector4 operator*(int i);

            IVector4 operator/(const IVector4& vector4);
            IVector4 operator/(int i);

            IVector4& operator+=(const IVector4& vector4);
            IVector4& operator+=(int i);

            IVector4& operator-=(const IVector4& vector4);
            IVector4& operator-=(int i);

            IVector4& operator*=(const IVector4& vector4);
            IVector4& operator*=(int i);

            IVector4& operator/=(const IVector4& vector4);
            IVector4& operator/=(int i);
        };


        class FVector2 : public Vector2<float>{
        public:
            FVector2();
            FVector2(float x, float y);

            FVector2 operator+(const FVector2 &vector2);
            FVector2 operator+(int i);

            FVector2 operator-(const FVector2& vector2);
            FVector2 operator-(int i);

            FVector2 operator*(const FVector2& vector2);
            FVector2 operator*(int i);

            FVector2 operator/(const FVector2& vector2);
            FVector2 operator/(int i);

            FVector2& operator+=(const FVector2& vector2);
            FVector2& operator+=(int i);

            FVector2& operator-=(const FVector2& vector2);
            FVector2& operator-=(int i);

            FVector2& operator*=(const FVector2& vector2);
            FVector2& operator*=(int i);

            FVector2& operator/=(const FVector2& vector2);
            FVector2& operator/=(int i);
        };
        class FVector3 : public Vector3<float>{
        public:
            FVector3();
            FVector3(float x, float y, float z);

            FVector3 operator+(const FVector3& vector3);
            FVector3 operator+(int i);

            FVector3 operator-(const FVector3& vector3);
            FVector3 operator-(int i);

            FVector3 operator*(const FVector3& vector3);
            FVector3 operator*(int i);

            FVector3 operator/(const FVector3& vector3);
            FVector3 operator/(int i);

            FVector3& operator+=(const FVector3& vector3);
            FVector3& operator+=(int i);

            FVector3& operator-=(const FVector3& vector3);
            FVector3& operator-=(int i);

            FVector3& operator*=(const FVector3& vector3);
            FVector3& operator*=(int i);

            FVector3& operator/=(const FVector3& vector3);
            FVector3& operator/=(int i);
        };
        class FVector4 : public Vector4<float>{
        public:
            FVector4();
            FVector4(float x, float y, float z, float s);

            FVector4 operator+(const FVector4& vector4);
            FVector4 operator+(int i);

            FVector4 operator-(const FVector4& vector4);
            FVector4 operator-(int i);

            FVector4 operator*(const FVector4& vector4);
            FVector4 operator*(int i);

            FVector4 operator/(const FVector4& vector4);
            FVector4 operator/(int i);

            FVector4& operator+=(const FVector4& vector4);
            FVector4& operator+=(int i);

            FVector4& operator-=(const FVector4& vector4);
            FVector4& operator-=(int i);

            FVector4& operator*=(const FVector4& vector4);
            FVector4& operator*=(int i);

            FVector4& operator/=(const FVector4& vector4);
            FVector4& operator/=(int i);
        };


        class DVector2 : public Vector2<double>{
        public:
            DVector2();
            DVector2(double x, double y);

            DVector2 operator+(const DVector2& vector2);
            DVector2 operator+(int i);

            DVector2 operator-(const DVector2& vector2);
            DVector2 operator-(int i);

            DVector2 operator*(const DVector2& vector2);
            DVector2 operator*(int i);

            DVector2 operator/(const DVector2& vector2);
            DVector2 operator/(int i);

            DVector2& operator+=(const DVector2& vector2);
            DVector2& operator+=(int i);

            DVector2& operator-=(const DVector2& vector2);
            DVector2& operator-=(int i);

            DVector2& operator*=(const DVector2& vector2);
            DVector2& operator*=(int i);

            DVector2& operator/=(const DVector2& vector2);
            DVector2& operator/=(int i);
        };
        class DVector3 : public Vector3<double>{
        public:
            DVector3();
            DVector3(double x, double y, double z);

            DVector3 operator+(const DVector3& vector3);
            DVector3 operator+(int i);

            DVector3 operator-(const DVector3& vector3);
            DVector3 operator-(int i);

            DVector3 operator*(const DVector3& vector3);
            DVector3 operator*(int i);

            DVector3 operator/(const DVector3& vector3);
            DVector3 operator/(int i);

            DVector3& operator+=(const DVector3& vector3);
            DVector3& operator+=(int i);

            DVector3& operator-=(const DVector3& vector3);
            DVector3& operator-=(int i);

            DVector3& operator*=(const DVector3& vector3);
            DVector3& operator*=(int i);

            DVector3& operator/=(const DVector3& vector3);
            DVector3& operator/=(int i);
        };
        class DVector4 : public Vector4<double>{
        public:
            DVector4();
            DVector4(double x, double y, double z, double s);

            DVector4 operator+(const DVector4& vector4);
            DVector4 operator+(int i);

            DVector4 operator-(const DVector4& vector4);
            DVector4 operator-(int i);

            DVector4 operator*(const DVector4& vector4);
            DVector4 operator*(int i);

            DVector4 operator/(const DVector4& vector4);
            DVector4 operator/(int i);

            DVector4& operator+=(const DVector4& vector4);
            DVector4& operator+=(int i);

            DVector4& operator-=(const DVector4& vector4);
            DVector4& operator-=(int i);

            DVector4& operator*=(const DVector4& vector4);
            DVector4& operator*=(int i);

            DVector4& operator/=(const DVector4& vector4);
            DVector4& operator/=(int i);
        };
    }
}

#endif //REDTEXTAPPLICATION_MATH_VECTOR_H
