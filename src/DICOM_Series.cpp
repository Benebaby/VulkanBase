#include "DICOM_Series.hpp"

DICOM_Series::DICOM_Series(std::string file_directory, std::string filename, uint32_t seriesIndex){
    m_file_directory = file_directory;
    m_filename = filename;
    m_seriesIndex = seriesIndex;
}
void DICOM_Series::Read(){
    m_data = std::vector<uint16_t>(0);
    m_absoluteDimensions = glm::vec3(0);
    m_relativeDimensions = glm::vec3(0);

    std::string DICOMDIR_file_path = m_file_directory+m_filename;
    gdcm::Reader reader;
    reader.SetFileName(DICOMDIR_file_path.c_str());
    if (!reader.Read()){
        std::cerr << "Could not read: " << DICOMDIR_file_path << std::endl;
        return;
    }
    std::stringstream strm;
    gdcm::File &file = reader.GetFile();
    gdcm::DataSet &ds = file.GetDataSet();
    gdcm::FileMetaInformation &fmi = file.GetHeader();

    gdcm::MediaStorage ms;
    ms.SetFromFile(file);
    if( ms != gdcm::MediaStorage::MediaStorageDirectoryStorage )
    {
        std::cout << "This file is not a DICOMDIR" << std::endl;
    }
    
    if (fmi.FindDataElement( gdcm::Tag (0x0002, 0x0002))) {
        strm.str("");
        fmi.GetDataElement( gdcm::Tag (0x0002, 0x0002) ).GetValue().Print(strm);
    } else {
        std::cerr << " Media Storage Sop Class UID not present" << std::endl;
    }

    if ("1.2.840.10008.1.3.10"!=strm.str()) {
        std::cout << "This file is not a DICOMDIR" << std::endl;
    }

    if(fmi.FindDataElement(gdcm::Tag(0x10, 0x10))){
        strm.str("");
        fmi.GetDataElement( gdcm::Tag (0x10, 0x10) ).GetValue().Print(strm);
        int test = 0;
    }

    gdcm::DataSet::DataElementSet::const_iterator it = ds.GetDES().begin();

    std::vector<std::string> all_paths(0);
    std::vector<std::vector<std::string>> seriespaths(0);

    for (; it != ds.GetDES().end(); ++it)
    {
        if (it->GetTag() == gdcm::Tag(0x0004, 0x1220))
        {
            const gdcm::DataElement &de = (*it);
            // ne pas utiliser GetSequenceOfItems pour extraire les items
            gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = de.GetValueAsSQ();
            unsigned int itemused = 1;
            while (itemused <= sqi->GetNumberOfItems())
            {
                strm.str("");

                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                //TODO il faut trimer strm.str() avant la comparaison
                while ((strm.str() == "PATIENT") || ((strm.str() == "PATIENT ")))
                {
                    std::cout << strm.str() << std::endl;
                    strm.str("");
                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0010, 0x0010)))
                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0010, 0x0010)).GetValue().Print(strm);
                    std::cout << "PATIENT NAME : " << strm.str() << std::endl;

                    //PATIENT ID
                    strm.str("");
                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0010, 0x0020)))
                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0010, 0x0020)).GetValue().Print(strm);
                    std::cout << "PATIENT ID : " << strm.str() << std::endl;

                    /*ADD TAG TO READ HERE*/
                    std::cout << "=========================== " << std::endl;
                    itemused++;
                    strm.str("");
                    if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                        sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                    //TODO il faut trimer strm.str() avant la comparaison
                    while ((strm.str() == "STUDY") || ((strm.str() == "STUDY ")))
                    {
                        std::cout << "  " << strm.str() << std::endl;
                        //UID
                        strm.str("");
                        if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0020, 0x000d)))
                            sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0020, 0x000d)).GetValue().Print(strm);
                        std::cout << "      STUDY UID : " << strm.str() << std::endl;

                        //STUDY DATE
                        strm.str("");
                        if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0008, 0x0020)))
                            sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0008, 0x0020)).GetValue().Print(strm);
                        std::cout << "      STUDY DATE : " << strm.str() << std::endl;

                        std::cout << "      =========================== " << std::endl;

                        itemused++;
                        strm.str("");
                        if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                            sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                        while ((strm.str() == "SERIES") || ((strm.str() == "SERIES ")))
                        {
                            std::cout << "      " << strm.str() << std::endl;
                            strm.str("");
                            if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0020, 0x000e)))
                                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0020, 0x000e)).GetValue().Print(strm);

                            //SERIE MODALITY
                            strm.str("");
                            if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0008, 0x0060)))
                                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0008, 0x0060)).GetValue().Print(strm);
                            std::cout << "          SERIE MODALITY " << strm.str() << std::endl;

                            itemused++;
                            strm.str("");
                            if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                                sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);

                            uint32_t imagecount = 0;
                            std::vector<std::string> tempseriespaths(0);

                            while ((strm.str() == "IMAGE") || ((strm.str() == "IMAGE "))) {
                                imagecount++;
                                //std::cout << "          " << strm.str() << std::endl;

                                //IMAGE UID
                                strm.str("");
                                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1511)))
                                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1511)).GetValue().Print(strm);

                                //IMAGE PATH
                                strm.str("");
                                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1500)))
                                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1500)).GetValue().Print(strm);

                                tempseriespaths.push_back(strm.str());

                                if (itemused < sqi->GetNumberOfItems())
                                    itemused++;
                                else
                                    break;

                                strm.str("");
                                if (sqi->GetItem(itemused).FindDataElement(gdcm::Tag(0x0004, 0x1430)))
                                    sqi->GetItem(itemused).GetDataElement(gdcm::Tag(0x0004, 0x1430)).GetValue().Print(strm);
                            }
                            std::cout << "          SERIE IMAGECOUNT " << std::to_string(imagecount) << std::endl;
                            seriespaths.push_back(tempseriespaths);
                        }
                    }
                }
                itemused++;
            }
        }
    }
    m_absoluteDimensions.z = (unsigned int)seriespaths[m_seriesIndex].size();
    std::cout << std::endl;
    if(seriespaths[m_seriesIndex].size() > 1){
        double spacingx = 1.0;
        double spacingy = 1.0;
        double spacingz = 1.0;
        double positionfirst = 0.0;
        double positionsecond = 1.0;
        {
            std::string imageFileName = m_file_directory;
            imageFileName += seriespaths[m_seriesIndex][0];
            gdcm::ImageReader reader;
            reader.SetFileName(imageFileName.c_str());
            if (!reader.Read()){
                std::cerr << "Could not read: " << imageFileName << std::endl;
                return;
            }
            gdcm::Image image = reader.GetImage();
            const unsigned int *dims = image.GetDimensions();
            m_absoluteDimensions.x = dims[0];
            m_absoluteDimensions.y = dims[1];
            const double *spacing = image.GetSpacing();
            spacingx = spacing[0] * 2.0;
            spacingy = spacing[1] * 2.0;
            gdcm::DataSet ds = reader.GetFile().GetDataSet();
            if(ds.FindDataElement( gdcm::Tag(0x0020, 0x1041))){
                strm.str("");
                ds.GetDataElement(gdcm::Tag(0x0020, 0x1041)).GetValue().Print(strm);
                positionfirst = std::stod(strm.str(), nullptr);

            }
        }
        {
            std::string imageFileName = m_file_directory;
            imageFileName += seriespaths[m_seriesIndex][1];
            gdcm::ImageReader reader;
            reader.SetFileName(imageFileName.c_str());
            if (!reader.Read()){
                std::cerr << "Could not read: " << imageFileName << std::endl;
                return;
            }
            gdcm::DataSet ds = reader.GetFile().GetDataSet();
            if(ds.FindDataElement( gdcm::Tag(0x0020, 0x1041))){
                strm.str("");
                ds.GetDataElement(gdcm::Tag(0x0020, 0x1041)).GetValue().Print(strm);
                positionsecond = std::stod(strm.str(), nullptr);
            }
            if((abs(positionsecond - positionfirst) < 0.3 || abs(positionsecond - positionfirst) > 5) && ds.FindDataElement( gdcm::Tag(0x0018, 0x0050))){
                strm.str("");
                ds.GetDataElement(gdcm::Tag(0x0018, 0x0050)).GetValue().Print(strm);
                spacingz = std::stod(strm.str(), nullptr);
            }else{
                spacingz = abs(positionsecond - positionfirst);
            }
        }
        std:: cout << "Spacing: " << spacingx << ", " << spacingy << ", " << spacingz << std::endl;
        m_relativeDimensions = glm::vec3(spacingx * (m_absoluteDimensions.x - 1), spacingy * (m_absoluteDimensions.y - 1), spacingz * (m_absoluteDimensions.z - 1));
        if(m_relativeDimensions.x >= m_relativeDimensions.y && m_relativeDimensions.x >= m_relativeDimensions.z)
            m_relativeDimensions = glm::vec3(1.0, m_relativeDimensions.y / m_relativeDimensions.x, m_relativeDimensions.z / m_relativeDimensions.x);
        else if(m_relativeDimensions.y >= m_relativeDimensions.x && m_relativeDimensions.y >= m_relativeDimensions.z)
            m_relativeDimensions = glm::vec3(m_relativeDimensions.x / m_relativeDimensions.y, 1.0 ,m_relativeDimensions.z / m_relativeDimensions.y);
        else if(m_relativeDimensions.z >= m_relativeDimensions.x && m_relativeDimensions.z >= m_relativeDimensions.y)
            m_relativeDimensions = glm::vec3(m_relativeDimensions.x / m_relativeDimensions.z, m_relativeDimensions.y / m_relativeDimensions.z, 1.0);
        else
            m_relativeDimensions = glm::vec3(1.0);
        std:: cout << "Relative Spacing: " << m_relativeDimensions.x << ", " << m_relativeDimensions.y << ", " << m_relativeDimensions.z << std::endl;
    }else{
        m_relativeDimensions = glm::vec3(1.0);
    }
    
    for (size_t i = 0; i < seriespaths[m_seriesIndex].size(); i++){
        std::string imageFileName = m_file_directory;
        imageFileName += seriespaths[m_seriesIndex][i];
        gdcm::ImageReader reader;
        reader.SetFileName(imageFileName.c_str());
        if (!reader.Read()){
            std::cerr << "Could not read: " << imageFileName << std::endl;
            return;
        }
        gdcm::Image image = reader.GetImage();
        unsigned long len = image.GetBufferLength();

        std::vector<uint8_t> tempImage8Bit(len, 0x00);
        image.GetBuffer(reinterpret_cast<char*>(tempImage8Bit.data()));
        for (size_t j = 0; j < tempImage8Bit.size(); j += 2)
        {
            uint16_t r = 0x0000;
            uint16_t g = 0x0000;
            r = tempImage8Bit[j] << 0;
            g = tempImage8Bit[j+1] << 8;
            uint16_t result = g | r;
            m_data.push_back(result);
        }
    }
}
glm::vec3 DICOM_Series::GetDimensionsAbsolute(){
    return m_absoluteDimensions;
}
glm::vec3 DICOM_Series::GetDimensionsRelative(){
    return m_relativeDimensions;
}
vk::DeviceSize DICOM_Series::getBufferSize(){
    return (uint64_t) (m_data.size() * 2);
}
void* DICOM_Series::getBufferData(){
    return m_data.data();
}
DICOM_Series::~DICOM_Series(){
    
}