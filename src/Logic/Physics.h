#ifndef PHYSICS_H_
#define PHYSICS_H_
namespace Logic {
class Physics {
  private:
    int speed;
    float turnSpeed;

  public:
    void SetSpeed(int speed) { this->speed = speed; };
    void SetTurnSpeed(float turnSpeed) { this->turnSpeed = turnSpeed; };
    int GetSpeed() { return speed; };
    float GetTurnSpeed() { return turnSpeed; };
};
} // namespace Logic

#endif
