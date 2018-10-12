#pragma once
#include <memory>
#include "region_coordinates.h"
#include "region_factory.h"
#include "region.h"
#include "iimage.h"
#include "mask.h"

class SimilarRegionSearch
{
    protected:
        std::shared_ptr<RegionFactory> _rbuffer;
        std::shared_ptr<RegionFactory> _lbuffer;
        uint32_t _height;
        uint32_t _width;

    public:
        SimilarRegionSearch(std::shared_ptr<IImage>& lImage, std::shared_ptr<IImage>& rImage);
        SimilarRegionSearch(std::string lname, std::string rname);

        void search(uint8_t rsize, uint32_t similarity, double jacardThreshold,
                    std::shared_ptr<Mask> const& mask, RegionMap& map);

        void search(uint8_t rsize, uint32_t similarity, double jacardThreshold,
                    RegionMap& map);

    private:
        void search_common(uint32_t rsize, std::unique_ptr<RegionBase>& lregion,
                            std::unique_ptr<RegionBase>& rregion, RegionMap& map);

};
