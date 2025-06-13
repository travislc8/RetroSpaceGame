#ifndef CRAB_H_
#define CRAB_H_
#include "Enemy.h"

namespace Components {
class Crab : public Enemy {
  private:
    void UpdateAttackPath() override;

  public:
    void LoadTexture() override;
    Crab(Levels::LocationInGrid, Vector2);
    void Draw() override;
};
} // namespace Components

#endif
