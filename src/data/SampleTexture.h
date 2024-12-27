#pragma once
#include <vector>
#include <cmath>
namespace data
{
    static std::vector<uint8_t> GetSampleGradientTexture(int size)
    {
        std::vector<uint8_t> pixels(4 * size * size);
        for (int i = 0; i < size ; i++)
        {
            for (int j = 0; j < size; j++)
            {
                uint8_t *p = &pixels[4 * (j * size + i)];
                p[0] = (uint8_t) (((float)i / (float)size) * 255); // r
                p[1] = (uint8_t) (((float)j / (float)size) * 255); // g
                p[2] = 128; // b
                p[3] = 255; // a
            }
        }
        return pixels;
    }

    static void PaintCellToBlack(int x, int y, std::vector<uint8_t> &pixels, int step, int cellPerline, bool isBlack)
    {
        int pixel_per_cell = step * step * 4;
        int pixel_per_cell_edge = step * 4;
        int pixel_per_row = cellPerline * pixel_per_cell_edge;
        //int cell_index = (x * cellPerline + y);
        //int start_pixel = pixel_per_cell * cell_index;
        int start_row = y * pixel_per_cell;
        int color = isBlack ? 0 : 255;
        for (int i = 0; i < step ; i++)
        {
            int offset = x * pixel_per_cell_edge + i * pixel_per_row + start_row;
            uint8_t *p = &pixels[offset];
            p[0] = color;
            p[1] = color;
            p[2] = color;
            p[3] = 255;
        } 
    }
    static std::vector<uint8_t> GetSampleUVGridTexture(int size)
    {
        const int step = 64;
        const int doublestep = step * 2;
        std::vector<uint8_t> pixels(4 * size * size);

        int x_size = size / step + 1;
        int y_size = size / step + 1;

        
        for (int i = 0; i < x_size; i++)
        {
            for (int j = 0; j < y_size; j++)
            {
                if ((i + j) % 2 != 0) 
                {
                    PaintCellToBlack(i, j, pixels, step, x_size, true);
                } else {
                    PaintCellToBlack(i, j, pixels, step, x_size, false);
                }
            }
        }

        return pixels;
        
    }

}