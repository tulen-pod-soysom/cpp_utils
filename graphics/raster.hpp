#include <cstdlib>
#include <utility>

template<typename Func>
auto brezenhem_algorithm(int x0,int y0, int x1, int y1, Func f)
{
  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);
  int err = 0;
  int d_err;
  int dir;

  if (dx >= dy)
  {
    if (x1 < x0) {std::swap(x1,x0); std::swap(y1,y0);}
    d_err = (dy + 1);
    dir = (y1 - y0 > 0)? 1: -1;

    int y = y0;
    for (int i = 0; i < dx; ++i)
    {
        f(x0 + i, y);
        err += d_err;
        if (err >= dx +1)
        {
            y += dir;
            // y++;
            err -= dx + 1;
        }
    }
  }
  else
  {
    if (y1 < y0) {std::swap(y1,y0); std::swap(x1,x0);};
    d_err = (dx + 1);
    dir = (x1 - x0 > 0)? 1: -1;

    int x = x0;
    for (int j = 0; j < dy; ++j)
    {
        f(x,y0 + j);
        err += d_err;
        if (err >= dy + 1)
        {
            x += dir;
            // x++;
            err -= dy + 1;
        }
    }
  }
}


template <typename Func>
void circle_raster(int x1, int y1, double R, Func func)
{
    int x = 0;
    int y = R;
    int delta = 1 - 2 * R;
    int error = 0;
    while (y >= x)
    {
        func(x1 + x, y1 + y);
        func(x1 + x, y1 - y);
        func(x1 - x, y1 + y);
        func(x1 - x, y1 - y);
        func(x1 + y, y1 + x);
        func(x1 + y, y1 - x);
        func(x1 - y, y1 + x);
        func(x1 - y, y1 - x);
        delta += delta < 0 ? 4 * x + 6 : 4 * (x - y--) + 10;
        ++x;
    }
}