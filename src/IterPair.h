#ifndef OCGL_ITER_PAIR_H
#define OCGL_ITER_PAIR_H

namespace ocgl {

  /**
   * @brief Iterator pair (i.e. range).
   */
  template<typename Iterator>
  class IterPair
  {
    public:
      /**
       * @brief Constructor.
       *
       * @param begin The begin iterator.
       * @param end The end iterator.
       */
      IterPair(Iterator begin, Iterator end)
        : m_begin(begin), m_end(end)
      {
      }

      /**
       * @brief Get the begin iterator.
       */
      const Iterator& begin() const
      {
        return m_begin;
      }

      /**
       * @brief Get the begin iterator.
       */
      Iterator& begin()
      {
        return m_begin;
      }

      /**
       * @brief Get the end iterator.
       */
      const Iterator& end() const
      {
        return m_end;
      }

      /**
       * @brief Get the end iterator.
       */
      Iterator& end()
      {
        return m_end;
      }

    private:
      Iterator m_begin; //!< The begin iterator.
      Iterator m_end; //!< The end iterator.
  };

  /**
   * @brief Helper function to create iterator pair.
   *
   * @param begin The begin iterator.
   * @param end The end iterator.
   */
  template<typename Iterator>
  IterPair<Iterator> makeIterPair(const Iterator &begin,
      const Iterator &end)
  {
    return IterPair<Iterator>(begin, end);
  }

} // namespace ocgl

#endif // OCGL_ITER_PAIR_H
