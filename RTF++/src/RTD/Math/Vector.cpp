//
// Created by kiper220 on 06.07.2021.
//

#include <Implementation/RTD/Math/Vector.h>

namespace RTF {
    namespace Math{

        BVector2::BVector2() : Vector2<bool>(false, false) {};
        BVector2::BVector2(bool x, bool y) : Vector2<bool>(x, y) {};

        BVector3::BVector3() : Vector3<bool>(false, false, false) {};
        BVector3::BVector3(bool x, bool y, bool z) : Vector3<bool>(x, y, z) {};

        BVector4::BVector4() : Vector4<bool>(false, false, false, false) {};
        BVector4::BVector4(bool x, bool y, bool z, bool s) : Vector4<bool>(x, y, z, s) {};


        SVector2::SVector2() : Vector2<std::string>("", "") {};
        SVector2::SVector2(std::string x, std::string y): Vector2<std::string>(std::move(x), std::move(y)) {};


        SVector3::SVector3(): Vector3<std::string>("", "", ""){};
        SVector3::SVector3(std::string x, std::string y, std::string z): Vector3<std::string>(std::move(x), std::move(y), std::move(z)) {}


        SVector4::SVector4(): Vector4<std::string>("", "", "", ""){};
        SVector4::SVector4(std::string x, std::string y, std::string z, std::string s): Vector4<std::string>(std::move(x), std::move(y), std::move(z), std::move(s)) {}



        IVector2::IVector2() : Vector2<int>(0, 0) {};
        IVector2::IVector2(int x, int y) : Vector2<int>(x, y) {}

        IVector2 IVector2::operator+(const IVector2& vector2){
            return {this->x + vector2.x, this->y + vector2.y};
        }
        IVector2 IVector2::operator+(int i){
            return {this->x + i, this->y + i};
        }

        IVector2 IVector2::operator-(const IVector2& vector2){
            return {this->x - vector2.x, this->y - vector2.y};
        }
        IVector2 IVector2::operator-(int i){
            return {this->x - i, this->y - i};
        }

        IVector2 IVector2::operator*(const IVector2& vector2){
            return {this->x * vector2.x, this->y * vector2.y};
        }
        IVector2 IVector2::operator*(int i){
            return {this->x * i, this->y * i};
        }

        IVector2 IVector2::operator/(const IVector2& vector2){
            return {this->x / vector2.x, this->y / vector2.y};
        }
        IVector2 IVector2::operator/(int i){
            return {this->x / i, this->y / i};
        }

        IVector2& IVector2::operator+=(const IVector2& vector2){
            this->x += vector2.x;
            this->y += vector2.y;
            return *this;
        }
        IVector2& IVector2::operator+=(int i){
            this->x += i;
            this->y += i;
            return *this;
        }

        IVector2& IVector2::operator-=(const IVector2& vector2){
            this->x -= vector2.x;
            this->y -= vector2.y;
            return *this;
        }
        IVector2& IVector2::operator-=(int i){
            this->x -= i;
            this->y -= i;
            return *this;
        }

        IVector2& IVector2::operator*=(const IVector2& vector2){
            this->x *= vector2.x;
            this->y *= vector2.y;
            return *this;
        }
        IVector2& IVector2::operator*=(int i){
            this->x *= i;
            this->y *= i;
            return *this;
        }

        IVector2& IVector2::operator/=(const IVector2& vector2){
            this->x /= vector2.x;
            this->y /= vector2.y;
            return *this;
        }
        IVector2& IVector2::operator/=(int i){
            this->x /= i;
            this->y /= i;
            return *this;
        }


        IVector3::IVector3() : Vector3<int>(0, 0, 0) {};
        IVector3::IVector3(int x, int y, int z) : Vector3<int>(x, y, z) {}

        IVector3 IVector3::operator+(const IVector3& vector3){
            return {this->x + vector3.x, this->y + vector3.y, this->z + vector3.z};
        }
        IVector3 IVector3::operator+(int i){
            return {this->x + i, this->y + i, this->z + i};
        }

        IVector3 IVector3::operator-(const IVector3& vector3){
            return {this->x - vector3.x, this->y - vector3.y, this->z - vector3.z};
        }
        IVector3 IVector3::operator-(int i){
            return {this->x - i, this->y - i, this->z - i};
        }

        IVector3 IVector3::operator*(const IVector3& vector3){
            return {this->x * vector3.x, this->y * vector3.y, this->z * vector3.z};
        }
        IVector3 IVector3::operator*(int i){
            return {this->x * i, this->y * i, this->z * i};
        }

        IVector3 IVector3::operator/(const IVector3& vector3){
            return {this->x / vector3.x, this->y / vector3.y, this->z / vector3.z};
        }
        IVector3 IVector3::operator/(int i){
            return {this->x / i, this->y / i, this->z / i};
        }

        IVector3& IVector3::operator+=(const IVector3& vector3){
            this->x += vector3.x;
            this->y += vector3.y;
            this->z += vector3.z;
            return *this;
        }
        IVector3& IVector3::operator+=(int i){
            this->x += i;
            this->y += i;
            this->z += i;
            return *this;
        }

        IVector3& IVector3::operator-=(const IVector3& vector3){
            this->x -= vector3.x;
            this->y -= vector3.y;
            this->z -= vector3.z;
            return *this;
        }
        IVector3& IVector3::operator-=(int i){
            this->x -= i;
            this->y -= i;
            this->z -= i;
            return *this;
        }

        IVector3& IVector3::operator*=(const IVector3& vector3){
            this->x *= vector3.x;
            this->y *= vector3.y;
            this->z *= vector3.z;
            return *this;
        }
        IVector3& IVector3::operator*=(int i){
            this->x *= i;
            this->y *= i;
            this->z *= i;
            return *this;
        }

        IVector3& IVector3::operator/=(const IVector3& vector3){
            this->x /= vector3.x;
            this->y /= vector3.y;
            this->z /= vector3.z;
            return *this;
        }
        IVector3& IVector3::operator/=(int i){
            this->x /= i;
            this->y /= i;
            this->z /= i;
            return *this;
        }


        IVector4::IVector4() : Vector4<int>(0, 0, 0, 0) {};
        IVector4::IVector4(int x, int y, int z, int s) : Vector4<int>(x, y, z, s) {}

        IVector4 IVector4::operator+(const IVector4& vector4){
            return {this->x + vector4.x, this->y + vector4.y, this->z + vector4.z, this->s + vector4.s};
        }
        IVector4 IVector4::operator+(int i){
            return {this->x + i, this->y + i, this->z + i, this->s + i};
        }

        IVector4 IVector4::operator-(const IVector4& vector4){
            return {this->x - vector4.x, this->y - vector4.y, this->z - vector4.z, this->s - vector4.s};
        }
        IVector4 IVector4::operator-(int i){
            return {this->x - i, this->y - i, this->z - i, this->s - i};
        }

        IVector4 IVector4::operator*(const IVector4& vector4){
            return {this->x * vector4.x, this->y * vector4.y, this->z * vector4.z, this->s * vector4.s};
        }
        IVector4 IVector4::operator*(int i){
            return {this->x * i, this->y * i, this->z * i, this->s * i};
        }

        IVector4 IVector4::operator/(const IVector4& vector4){
            return {this->x / vector4.x, this->y / vector4.y, this->z / vector4.z, this->s / vector4.s};
        }
        IVector4 IVector4::operator/(int i){
            return {this->x / i, this->y / i, this->z / i, this->s / i};
        }

        IVector4& IVector4::operator+=(const IVector4& vector4){
            this->x += vector4.x;
            this->y += vector4.y;
            this->z += vector4.z;
            this->s += vector4.s;
            return *this;
        }
        IVector4& IVector4::operator+=(int i){
            this->x += i;
            this->y += i;
            this->z += i;
            this->s += i;
            return *this;
        }

        IVector4& IVector4::operator-=(const IVector4& vector4){
            this->x -= vector4.x;
            this->y -= vector4.y;
            this->z -= vector4.z;
            this->s -= vector4.s;
            return *this;
        }
        IVector4& IVector4::operator-=(int i){
            this->x -= i;
            this->y -= i;
            this->z -= i;
            this->s -= i;
            return *this;
        }

        IVector4& IVector4::operator*=(const IVector4& vector4){
            this->x *= vector4.x;
            this->y *= vector4.y;
            this->z *= vector4.z;
            this->s *= vector4.s;
            return *this;
        }
        IVector4& IVector4::operator*=(int i){
            this->x *= i;
            this->y *= i;
            this->z *= i;
            this->s *= i;
            return *this;
        }

        IVector4& IVector4::operator/=(const IVector4& vector4){
            this->x /= vector4.x;
            this->y /= vector4.y;
            this->z /= vector4.z;
            this->s /= vector4.s;
            return *this;
        }
        IVector4& IVector4::operator/=(int i){
            this->x /= i;
            this->y /= i;
            this->z /= i;
            this->s /= i;
            return *this;
        }


        FVector2::FVector2() : Vector2<float>(0, 0) {};
        FVector2::FVector2(float x, float y) : Vector2<float>(x, y) {}

        FVector2 FVector2::operator+(const FVector2& vector2){
            return {this->x + vector2.x, this->y + vector2.y};
        }
        FVector2 FVector2::operator+(int i){
            return {this->x + i, this->y + i};
        }

        FVector2 FVector2::operator-(const FVector2& vector2){
            return {this->x - vector2.x, this->y - vector2.y};
        }
        FVector2 FVector2::operator-(int i){
            return {this->x - i, this->y - i};
        }

        FVector2 FVector2::operator*(const FVector2& vector2){
            return {this->x * vector2.x, this->y * vector2.y};
        }
        FVector2 FVector2::operator*(int i){
            return {this->x * i, this->y * i};
        }

        FVector2 FVector2::operator/(const FVector2& vector2){
            return {this->x / vector2.x, this->y / vector2.y};
        }
        FVector2 FVector2::operator/(int i){
            return {this->x / i, this->y / i};
        }

        FVector2& FVector2::operator+=(const FVector2& vector2){
            this->x += vector2.x;
            this->y += vector2.y;
            return *this;
        }
        FVector2& FVector2::operator+=(int i){
            this->x += i;
            this->y += i;
            return *this;
        }

        FVector2& FVector2::operator-=(const FVector2& vector2){
            this->x -= vector2.x;
            this->y -= vector2.y;
            return *this;
        }
        FVector2& FVector2::operator-=(int i){
            this->x -= i;
            this->y -= i;
            return *this;
        }

        FVector2& FVector2::operator*=(const FVector2& vector2){
            this->x *= vector2.x;
            this->y *= vector2.y;
            return *this;
        }
        FVector2& FVector2::operator*=(int i){
            this->x *= i;
            this->y *= i;
            return *this;
        }

        FVector2& FVector2::operator/=(const FVector2& vector2){
            this->x /= vector2.x;
            this->y /= vector2.y;
            return *this;
        }
        FVector2& FVector2::operator/=(int i){
            this->x /= i;
            this->y /= i;
            return *this;
        }


        FVector3::FVector3() : Vector3<float>(0, 0, 0) {};
        FVector3::FVector3(float x, float y, float z) : Vector3<float>(x, y, z) {}

        FVector3 FVector3::operator+(const FVector3& vector3){
            return {this->x + vector3.x, this->y + vector3.y, this->z + vector3.z};
        }
        FVector3 FVector3::operator+(int i){
            return {this->x + i, this->y + i, this->z + i};
        }

        FVector3 FVector3::operator-(const FVector3& vector3){
            return {this->x - vector3.x, this->y - vector3.y, this->z - vector3.z};
        }
        FVector3 FVector3::operator-(int i){
            return {this->x - i, this->y - i, this->z - i};
        }

        FVector3 FVector3::operator*(const FVector3& vector3){
            return {this->x * vector3.x, this->y * vector3.y, this->z * vector3.z};
        }
        FVector3 FVector3::operator*(int i){
            return {this->x * i, this->y * i, this->z * i};
        }

        FVector3 FVector3::operator/(const FVector3& vector3){
            return {this->x / vector3.x, this->y / vector3.y, this->z / vector3.z};
        }
        FVector3 FVector3::operator/(int i){
            return {this->x / i, this->y / i, this->z / i};
        }

        FVector3& FVector3::operator+=(const FVector3& vector3){
            this->x += vector3.x;
            this->y += vector3.y;
            this->z += vector3.z;
            return *this;
        }
        FVector3& FVector3::operator+=(int i){
            this->x += i;
            this->y += i;
            this->z += i;
            return *this;
        }

        FVector3& FVector3::operator-=(const FVector3& vector3){
            this->x -= vector3.x;
            this->y -= vector3.y;
            this->z -= vector3.z;
            return *this;
        }
        FVector3& FVector3::operator-=(int i){
            this->x -= i;
            this->y -= i;
            this->z -= i;
            return *this;
        }

        FVector3& FVector3::operator*=(const FVector3& vector3){
            this->x *= vector3.x;
            this->y *= vector3.y;
            this->z *= vector3.z;
            return *this;
        }
        FVector3& FVector3::operator*=(int i){
            this->x *= i;
            this->y *= i;
            this->z *= i;
            return *this;
        }

        FVector3& FVector3::operator/=(const FVector3& vector3){
            this->x /= vector3.x;
            this->y /= vector3.y;
            this->z /= vector3.z;
            return *this;
        }
        FVector3& FVector3::operator/=(int i){
            this->x /= i;
            this->y /= i;
            this->z /= i;
            return *this;
        }


        FVector4::FVector4() : Vector4<float>(0, 0, 0, 0) {};
        FVector4::FVector4(float x, float y, float z, float s) : Vector4<float>(x, y, z, s) {}

        FVector4 FVector4::operator+(const FVector4& vector4){
            return {this->x + vector4.x, this->y + vector4.y, this->z + vector4.z, this->s + vector4.s};
        }
        FVector4 FVector4::operator+(int i){
            return {this->x + i, this->y + i, this->z + i, this->s + i};
        }

        FVector4 FVector4::operator-(const FVector4& vector4){
            return {this->x - vector4.x, this->y - vector4.y, this->z - vector4.z, this->s - vector4.s};
        }
        FVector4 FVector4::operator-(int i){
            return {this->x - i, this->y - i, this->z - i, this->s - i};
        }

        FVector4 FVector4::operator*(const FVector4& vector4){
            return {this->x * vector4.x, this->y * vector4.y, this->z * vector4.z, this->s * vector4.s};
        }
        FVector4 FVector4::operator*(int i){
            return {this->x * i, this->y * i, this->z * i, this->s * i};
        }

        FVector4 FVector4::operator/(const FVector4& vector4){
            return {this->x / vector4.x, this->y / vector4.y, this->z / vector4.z, this->s / vector4.s};
        }
        FVector4 FVector4::operator/(int i){
            return {this->x / i, this->y / i, this->z / i, this->s / i};
        }

        FVector4& FVector4::operator+=(const FVector4& vector4){
            this->x += vector4.x;
            this->y += vector4.y;
            this->z += vector4.z;
            this->s += vector4.s;
            return *this;
        }
        FVector4& FVector4::operator+=(int i){
            this->x += i;
            this->y += i;
            this->z += i;
            this->s += i;
            return *this;
        }

        FVector4& FVector4::operator-=(const FVector4& vector4){
            this->x -= vector4.x;
            this->y -= vector4.y;
            this->z -= vector4.z;
            this->s -= vector4.s;
            return *this;
        }
        FVector4& FVector4::operator-=(int i){
            this->x -= i;
            this->y -= i;
            this->z -= i;
            this->s -= i;
            return *this;
        }

        FVector4& FVector4::operator*=(const FVector4& vector4){
            this->x *= vector4.x;
            this->y *= vector4.y;
            this->z *= vector4.z;
            this->s *= vector4.s;
            return *this;
        }
        FVector4& FVector4::operator*=(int i){
            this->x *= i;
            this->y *= i;
            this->z *= i;
            this->s *= i;
            return *this;
        }

        FVector4& FVector4::operator/=(const FVector4& vector4){
            this->x /= vector4.x;
            this->y /= vector4.y;
            this->z /= vector4.z;
            this->s /= vector4.s;
            return *this;
        }
        FVector4& FVector4::operator/=(int i){
            this->x /= i;
            this->y /= i;
            this->z /= i;
            this->s /= i;
            return *this;
        }


        DVector2::DVector2() : Vector2<double>(0, 0) {};
        DVector2::DVector2(double x, double y) : Vector2<double>(x, y) {}

        DVector2 DVector2::operator+(const DVector2& vector2){
            return {this->x + vector2.x, this->y + vector2.y};
        }
        DVector2 DVector2::operator+(int i){
            return {this->x + i, this->y + i};
        }

        DVector2 DVector2::operator-(const DVector2& vector2){
            return {this->x - vector2.x, this->y - vector2.y};
        }
        DVector2 DVector2::operator-(int i){
            return {this->x - i, this->y - i};
        }

        DVector2 DVector2::operator*(const DVector2& vector2){
            return {this->x * vector2.x, this->y * vector2.y};
        }
        DVector2 DVector2::operator*(int i){
            return {this->x * i, this->y * i};
        }

        DVector2 DVector2::operator/(const DVector2& vector2){
            return {this->x / vector2.x, this->y / vector2.y};
        }
        DVector2 DVector2::operator/(int i){
            return {this->x / i, this->y / i};
        }

        DVector2& DVector2::operator+=(const DVector2& vector2){
            this->x += vector2.x;
            this->y += vector2.y;
            return *this;
        }
        DVector2& DVector2::operator+=(int i){
            this->x += i;
            this->y += i;
            return *this;
        }

        DVector2& DVector2::operator-=(const DVector2& vector2){
            this->x -= vector2.x;
            this->y -= vector2.y;
            return *this;
        }
        DVector2& DVector2::operator-=(int i){
            this->x -= i;
            this->y -= i;
            return *this;
        }

        DVector2& DVector2::operator*=(const DVector2& vector2){
            this->x *= vector2.x;
            this->y *= vector2.y;
            return *this;
        }
        DVector2& DVector2::operator*=(int i){
            this->x *= i;
            this->y *= i;
            return *this;
        }

        DVector2& DVector2::operator/=(const DVector2& vector2){
            this->x /= vector2.x;
            this->y /= vector2.y;
            return *this;
        }
        DVector2& DVector2::operator/=(int i){
            this->x /= i;
            this->y /= i;
            return *this;
        }


        DVector3::DVector3() : Vector3<double>(0, 0, 0) {};
        DVector3::DVector3(double x, double y, double z) : Vector3<double>(x, y, z) {}

        DVector3 DVector3::operator+(const DVector3& vector3){
            return {this->x + vector3.x, this->y + vector3.y, this->z + vector3.z};
        }
        DVector3 DVector3::operator+(int i){
            return {this->x + i, this->y + i, this->z + i};
        }

        DVector3 DVector3::operator-(const DVector3& vector3){
            return {this->x - vector3.x, this->y - vector3.y, this->z - vector3.z};
        }
        DVector3 DVector3::operator-(int i){
            return {this->x - i, this->y - i, this->z - i};
        }

        DVector3 DVector3::operator*(const DVector3& vector3){
            return {this->x * vector3.x, this->y * vector3.y, this->z * vector3.z};
        }
        DVector3 DVector3::operator*(int i){
            return {this->x * i, this->y * i, this->z * i};
        }

        DVector3 DVector3::operator/(const DVector3& vector3){
            return {this->x / vector3.x, this->y / vector3.y, this->z / vector3.z};
        }
        DVector3 DVector3::operator/(int i){
            return {this->x / i, this->y / i, this->z / i};
        }

        DVector3& DVector3::operator+=(const DVector3& vector3){
            this->x += vector3.x;
            this->y += vector3.y;
            this->z += vector3.z;
            return *this;
        }
        DVector3& DVector3::operator+=(int i){
            this->x += i;
            this->y += i;
            this->z += i;
            return *this;
        }

        DVector3& DVector3::operator-=(const DVector3& vector3){
            this->x -= vector3.x;
            this->y -= vector3.y;
            this->z -= vector3.z;
            return *this;
        }
        DVector3& DVector3::operator-=(int i){
            this->x -= i;
            this->y -= i;
            this->z -= i;
            return *this;
        }

        DVector3& DVector3::operator*=(const DVector3& vector3){
            this->x *= vector3.x;
            this->y *= vector3.y;
            this->z *= vector3.z;
            return *this;
        }
        DVector3& DVector3::operator*=(int i){
            this->x *= i;
            this->y *= i;
            this->z *= i;
            return *this;
        }

        DVector3& DVector3::operator/=(const DVector3& vector3){
            this->x /= vector3.x;
            this->y /= vector3.y;
            this->z /= vector3.z;
            return *this;
        }
        DVector3& DVector3::operator/=(int i){
            this->x /= i;
            this->y /= i;
            this->z /= i;
            return *this;
        }


        DVector4::DVector4() : Vector4<double>(0, 0, 0, 0) {};
        DVector4::DVector4(double x, double y, double z, double s) : Vector4<double>(x, y, z, s) {}


        DVector4 DVector4::operator+(const DVector4& vector4){
            return {this->x + vector4.x, this->y + vector4.y, this->z + vector4.z, this->s + vector4.s};
        }
        DVector4 DVector4::operator+(int i){
            return {this->x + i, this->y + i, this->z + i, this->s + i};
        }

        DVector4 DVector4::operator-(const DVector4& vector4){
            return {this->x - vector4.x, this->y - vector4.y, this->z - vector4.z, this->s - vector4.s};
        }
        DVector4 DVector4::operator-(int i){
            return {this->x - i, this->y - i, this->z - i, this->s - i};
        }

        DVector4 DVector4::operator*(const DVector4& vector4){
            return {this->x * vector4.x, this->y * vector4.y, this->z * vector4.z, this->s * vector4.s};
        }
        DVector4 DVector4::operator*(int i){
            return {this->x * i, this->y * i, this->z * i, this->s * i};
        }

        DVector4 DVector4::operator/(const DVector4& vector4){
            return {this->x / vector4.x, this->y / vector4.y, this->z / vector4.z, this->s / vector4.s};
        }
        DVector4 DVector4::operator/(int i){
            return {this->x / i, this->y / i, this->z / i, this->s / i};
        }

        DVector4& DVector4::operator+=(const DVector4& vector4){
            this->x += vector4.x;
            this->y += vector4.y;
            this->z += vector4.z;
            this->s += vector4.s;
            return *this;
        }
        DVector4& DVector4::operator+=(int i){
            this->x += i;
            this->y += i;
            this->z += i;
            this->s += i;
            return *this;
        }

        DVector4& DVector4::operator-=(const DVector4& vector4){
            this->x -= vector4.x;
            this->y -= vector4.y;
            this->z -= vector4.z;
            this->s -= vector4.s;
            return *this;
        }
        DVector4& DVector4::operator-=(int i){
            this->x -= i;
            this->y -= i;
            this->z -= i;
            this->s -= i;
            return *this;
        }

        DVector4& DVector4::operator*=(const DVector4& vector4){
            this->x *= vector4.x;
            this->y *= vector4.y;
            this->z *= vector4.z;
            this->s *= vector4.s;
            return *this;
        }
        DVector4& DVector4::operator*=(int i){
            this->x *= i;
            this->y *= i;
            this->z *= i;
            this->s *= i;
            return *this;
        }

        DVector4& DVector4::operator/=(const DVector4& vector4){
            this->x /= vector4.x;
            this->y /= vector4.y;
            this->z /= vector4.z;
            this->s /= vector4.s;
            return *this;
        }
        DVector4& DVector4::operator/=(int i){
            this->x /= i;
            this->y /= i;
            this->z /= i;
            this->s /= i;
            return *this;
        }
    }
}