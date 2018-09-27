#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <cstdint>

class Configuration
{
    private:
        static double _jacardThreshold;
        static uint32_t _similarityThreshold;

        Configuration() {}

    public:
        static Configration& getInstance()
        {
            static Configuration instance;
            return instance;
        }
        static double getJacardThreshold();
        static void setJacardThreshold(double new_threshold);

        static uint32_t getSimilarityThreshold();
        static void setSimilarityThreshold(uint32_t new_threshold);

        Configuration(Configuration const&) = delete;
        void operator=(Configuration const&) = delete;

};

#endif /* _CONFIG_H_ */
