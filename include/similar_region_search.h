#ifndef __SIMILAR_REGION_SEARCH__
#define __SIMILAR_REGION_SEARCH__
#include <memory>
#include "region_coordinates.h"
#include "region_factory.h"
#include "region.h"
#include "iimage.h"
#include "mask.h"

using namespace std;

class SimilarRegionSearch
{
    protected:
        shared_ptr<RegionFactory> _rbuffer;
        shared_ptr<RegionFactory> _lbuffer;
        uint32_t _height;
        uint32_t _width;

    public:
        SimilarRegionSearch(shared_ptr<IImage>& lImage, shared_ptr<IImage>& rImage);
        SimilarRegionSearch(string lname, string rname);

        void search(uint8_t rsize, uint32_t similarity, double jacardThreshold,
                    shared_ptr<Mask> const& mask, RegionMap& map);

        void search(uint8_t rsize, uint32_t similarity, double jacardThreshold,
                    RegionMap& map);

    private:
        void search_common(uint32_t rsize, unique_ptr<RegionBase>& lregion,
                            unique_ptr<RegionBase>& rregion, RegionMap& map);

};

#endif /* __SIMILAR_REGION_SEARCH__ */
