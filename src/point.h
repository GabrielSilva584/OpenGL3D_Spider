#ifndef POINT
#define POINT

#define PI 3.14159265359

class Point{
    private:
        //Coordenadas
        GLfloat X, Y, Z;

    public:
        //Construtores
        Point();
        Point(GLfloat x, GLfloat y, GLfloat z);

        //Transformações úteis
        void translate(GLfloat delX, GLfloat delY, GLfloat delZ);
        void rotate(Point O, GLfloat rad, Point dir);

        //Sets e Gets úteis
        void setX(GLfloat x);
        void setY(GLfloat y);
        void setZ(GLfloat z);
        GLfloat getX();
        GLfloat getY();
        GLfloat getZ();
        void print();
};

#endif
