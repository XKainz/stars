#include "BinFiles.h"
unsigned int getCellNumber(const char* in, char seperator) {
    std::fstream fileIn(in,std::ios::in);
    std::string value;
    const char* cvalue;
    unsigned int lengthArray(0);
    while(fileIn.good()){
        if(fileIn.get()==seperator){
            lengthArray++;
        }
    }
    fileIn.clear();
    fileIn.seekg(0,std::ios::beg);
    fileIn.close();

    return lengthArray;
}

const std::vector<float> readCSVFileVBO(const char* in, char seperator)
{
    unsigned int lengthArray(getCellNumber(in, seperator));

    std::fstream fileIn(in,std::ios::in);
    unsigned int i = 0;
    std::vector<float> array(lengthArray);
    const char* cvalue;
    std::string value;
    while( i<lengthArray){
        getline(fileIn,value,seperator);
        cvalue = value.c_str();
        array[i] = atof(cvalue);
        i++;
    }
    return array;
}

void makeBinaryFileVBO(const char* in, char seperator,const char* out){
    unsigned int lengthArray(getCellNumber(in, seperator));

    std::fstream fileIn(in,std::ios::in);
    unsigned int i = 0;
    float* array= new float[lengthArray];
    const char* cvalue;
    std::string value;
    while( i<lengthArray){
        getline(fileIn,value,seperator);
        cvalue = value.c_str();
        array[i] = atof(cvalue);
        i++;
    }
    std::fstream fileOut(out, std::ios::binary | std::ios::trunc | std::ios::out);
    fileOut.write((char*)array,sizeof(float)*lengthArray);
    delete [] array;
    array = 0;

    fileOut.close();
    fileIn.close();
}

const float* readBinaryFileVBO(const char* in){
    std::fstream file(in, std::ios::binary | std::ios::in | std::ios::ate);
    unsigned int size = file.tellg();
    file.clear();
    file.seekg(0);
    std::cout << size/sizeof(float) << std::endl;
    float * array = new float[(size/sizeof(float))];
    file.read((char*)array,size);
    file.close();
    return array;
}

unsigned int readSize( const char* in){
    std::fstream file(in, std::ios::binary | std::ios::in | std::ios::ate);
    unsigned int size = file.tellg();
    file.close();
    return size;
}

void makeBinaryFileEBO(const char* in, char seperator,const char* out){
    std::fstream fileIn(in,std::ios::in);
    std::string value;
    const char* cvalue;
    unsigned int lengthArray(getCellNumber(in,seperator));

    unsigned int i = 0;
    unsigned int* array= new unsigned int[lengthArray];
    while( i<lengthArray){
        getline(fileIn,value,seperator);
        cvalue = value.c_str();
        array[i] = atof(cvalue);
        i++;
    }
    std::fstream fileOut(out, std::ios::binary | std::ios::trunc | std::ios::out);
    fileOut.write((char*)array,sizeof(unsigned int)*lengthArray);
    delete [] array;
    array = 0;

    fileOut.close();
    fileIn.close();
}

const unsigned int* readBinaryFileEBO(const char* in){
    std::fstream file(in, std::ios::binary | std::ios::in | std::ios::ate);
    unsigned int size = file.tellg();
    file.clear();
    file.seekg(0);
    unsigned int* array = new unsigned int[size/sizeof(unsigned int)];
    file.read((char*)array,size);
    file.close();
    return array;
}
