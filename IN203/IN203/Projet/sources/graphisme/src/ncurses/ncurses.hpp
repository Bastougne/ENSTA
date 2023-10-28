#ifndef _NCURSES_NCURSES_HPP_
#define _NCURSES_NCURSES_HPP_
#include "keyboard.hpp"
#include "palette.hpp"
#include "style.hpp"
#include "window.hpp"

namespace ncurses {
void init();
void finalize();
} // namespace ncurses

#endif
