/*!
 * @brief Class that defines a Keno bet.
 *
 * @author João Pedro Fonseca Dantas
 * @author João Guilherme Alves Lopes da Costa
 * @file keno_bet.cpp
 */

#include "keno_bet.h"

namespace keno {
  
  bool KenoBet::AddSpot(keno::number_type spot) {
    if (binary_search(KenoBet::m_spots.begin(), KenoBet::m_spots.end(), spot)) {
      return false;
    } else {
      KenoBet::m_spots.push_back(spot);
      return true;
    }
  }

  bool KenoBet::set_wage(keno::cash_type wage) {
    if (wage <= 0) return false;
    else KenoBet::m_wage = wage;
    return true;
      // spots.erase(last, spots.end());
  }

  void KenoBet::reset(void) {
    KenoBet::m_spots.erase(KenoBet::m_spots.begin(), KenoBet::m_spots.end());
    KenoBet::m_wage = 0;
  }

  keno::cash_type KenoBet::get_wage(void) const {
    return m_wage;
  }

  size_t KenoBet::Size(void) const {
    return m_spots.size();
  }

  keno::set_of_numbers_type
  KenoBet::FindHits(const keno::set_of_numbers_type &draw) const {
    // This container will store all common elements, if any exists.
    keno::set_of_numbers_type intersection;

    for (unsigned short i = 0; i < draw.size(); i++) {
      if (binary_search(KenoBet::m_spots.begin(),
                        KenoBet::m_spots.end(),
                        draw[i])) {
        intersection.push_back(draw[i]);
      }
    }

    return intersection;
  }

  keno::set_of_numbers_type
  KenoBet::get_spots(void) const {
    return m_spots;
  }

}

