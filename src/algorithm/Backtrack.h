#ifndef OCGL_ALGORITHM_BACKTRACK_H
#define OCGL_ALGORITHM_BACKTRACK_H

#include <functional>

namespace ocgl {

  namespace algorithm {

    // isGoal()
    // solution()
    // isDead()
    // local()
    // next(local)
    // backtrack(local)

    template<typename State>
    bool backtrack(State &state, std::function<bool(const typename State::Solution&)> visitor)
    {
      // found a solution?
      if (state.isGoal())
        return visitor(state.solution());

      // early backtrack if needed
      if (state.isDead())
        return false;

      // local stack state
      auto local = State::local();

      // try all next states
      while (state.next(local)) {
        if (backtrack(state, visitor)) {
          state.backtrack(local);
          return true;
        }
        state.backtrack(local);
      }

      return false;
    }

  } // namespace algorithm

} // namespace ocgl

#endif // OCGL_ALGORITHM_BACKTRACK_H
