#ifndef BUTTERFLY_H_
#define BUTTERFLY_H_
#include "Enemy.h"

namespace Components {
class Butterfly : public Enemy {
  private:
    void UpdateAttackPath() override;

  public:
    void LoadTexture() override;
    Butterfly(Levels::LocationInGrid, Vector2);
    void Draw() override;
};
} // namespace Components

#endif
