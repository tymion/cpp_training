#ifndef __SIMILAR_REGION_SEARCH__
#define __SIMILAR_REGION_SEARCH__

using namespace std;

class SimilarRegionSearch
{
    protected:
        shared_ptr<RegionFactory> _rbuffer;
        shared_ptr<RegionFactory> _lbuffer;

    public:
        SimilarRegionSearch(string lname, string rname);

        void search(uint8_t rsize, uint32_t similarity, double jacardThreshold,
                    shared_ptr<Mask> &mask);

        void search(uint8_t rsize, uint32_t similarity, double jacardThreshold);

}

#endif /* __SIMILAR_REGION_SEARCH__ */
