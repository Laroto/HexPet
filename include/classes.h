#pragma once

enum Side : bool
{
    RIGHT, LEFT
};

enum Type
{
    COXA, FEMUR, TIBIA
};

enum Method
{
    INSTANT, LINEAR, EXPONENTIAL, SIGMOID
};

class Part
{
    private:
        int id;
        float offset;
        Type type;
        float pos;
        float temp;
        bool isMoving;

    public:
        Part(int id, Type type);
        ~Part();
        bool tooHot();
        float getTemp();
        int getID();
        Type getType();
        float getPos();
        void setOffset(float offset);
        bool goTo(float dest, Method method);
        bool isMoving();
};

class Leg
{
    private:
        float x,y,z;
        Side side;
        Part coxa;
        Part femur;
        Part tibia;
        bool isMoving;

    public:
        Leg(Part coxa, Part femur, Part tibia, Side side);
        ~Leg();
        Side getSide();
        bool isMoving();
        bool goTo(float dest_x, float dest_y, float dest_z, Method method);
};
