#pragma once
//we need to create vactors,by default 
//basic maths : add,subract,multiply,divide
//here we use SUPRAINCARCAREA OPERATORILOR INVATATA LA POO LA CURS :)
//the vector works with FLOATS
#include <iostream>
class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& vec);
	//la Vector2D& , punem "&" so it can return a refference (&)
	//la parametrii , punem "&" pt ca vrem o referinta,pt ca nu vrem o copie,pt ca atunci cand lucram in functii cu parametrii , se ia de fapt o copie
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	//generating an easy way to print a vector
	//ostream - OUTPUTstream
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
	
};