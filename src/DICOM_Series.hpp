#include <gdcmScanner.h>
#include <gdcmTesting.h>
#include <gdcmIPPSorter.h>
#include <gdcmDirectionCosines.h>
#include <gdcmDirectory.h>
#include <gdcmImageReader.h>
#include <gdcmReader.h>

#include "globalDefs.hpp"
#include "globalIncludes.hpp"

class DICOM_Series
{
private:
    std::vector<uint16_t> m_data;
    glm::vec3 m_absoluteDimensions;
    glm::vec3 m_relativeDimensions;
    std::string m_file_directory;
    std::string m_filename;
    uint32_t m_seriesIndex;
public:
    DICOM_Series(std::string file_directory, std::string filename, uint32_t seriesIndex);
    ~DICOM_Series();
    void Read();
    glm::vec3 DICOM_Series::GetDimensionsAbsolute();
    glm::vec3 DICOM_Series::GetDimensionsRelative();
    vk::DeviceSize getBufferSize();
    void* getBufferData();
};
