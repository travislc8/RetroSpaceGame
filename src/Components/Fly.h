#ifndef FLY_H_
#define FLY_H_
#include "Enemy.h"

namespace Components {
class Fly : public Enemy {
  private:
    void UpdateAttackPath() override;

  public:
    void LoadTexture() override;
    Fly(Levels::LocationInGrid, Vector2);
    void Draw() override;
};
} // namespace Components

#endif
