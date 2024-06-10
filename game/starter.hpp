#ifndef __STARTER_HPP
#define __STARTER_HPP

#include <olcTemplate/game/src/state/state.hpp>

namespace stemaj {

class Starter : public State
{
public:
  explicit Starter() {}
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override 
  {
    return nullptr;
  }
};

} // namespace stemaj

#endif // __STARTER_HPP