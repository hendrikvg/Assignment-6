#include "KeyboardInput.h"


KeyboardInput::KeyboardInput() {
    u = Matrix(2, 1, 0.0);
    keystates = SDL_GetKeyboardState(NULL); // Argument is the number of keys available, since we don't care it's set to NULL.
}

KeyboardInput::~KeyboardInput()
{
    std::cout << "Destorying KeyboardInput object. Also destorying parent object: ";
}



Matrix KeyboardInput::getU(double time) {
    time = NULL;
    return this->u;
}


void KeyboardInput::setThrust(double thrust) {
    this->u(1, 1) = thrust;
}

void KeyboardInput::setAngularVelocity(double angularVelocity) {
    this->u(2, 1) = angularVelocity;
}


void KeyboardInput::scanKeys(bool& quit, double inputAngularVelocity, double inputThrust, Matrix x0, Matrix& x, SDL_Event event) {
    setThrust(0);
    setAngularVelocity(0);


    if (keystates[SDL_SCANCODE_ESCAPE])
    {
        quit = true;
    }

    if (keystates[SDL_SCANCODE_LEFT])
    {
        setAngularVelocity(inputAngularVelocity);
    }

    if (keystates[SDL_SCANCODE_RIGHT])
    {
        setAngularVelocity(-inputAngularVelocity);
    }

    if (keystates[SDL_SCANCODE_UP])
    {
        setThrust(inputThrust);
    }
    if (keystates[SDL_SCANCODE_SPACE])
    {
        x = x0;
    }
}