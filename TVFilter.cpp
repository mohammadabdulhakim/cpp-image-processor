#include "TVFilter.h"

void TVFilter::apply()
{
    try {
        for (int i = 0; i < image.height - 1; i += 2)
        {
            for (int j = 0; j < image.width; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image(j, i, k) = 0.5 * image(j, i, k);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

void TVFilter::getNeeds()
{

}
