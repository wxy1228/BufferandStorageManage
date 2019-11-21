#include "disk.hpp"
#include <buffer.hpp>

disk::disk(void)
{
    init_disk();
    cout<<"disk has been created"<<endl;
}

disk::~disk()
{
    input.close();
    output.close();
    log.close();
    cout<<"disk has been dropped"<<endl;
}

void disk::init_disk()
{
    ofstream disk_file;
    disk_file.open(DBF_FILE_NAME);
    char data[DataNum*FrameSize];       //存储.dbf文件中的数据，最大50000行，每个数据最大4096
    disk_file.write(data, sizeof(data));
    disk_file.close();

    disk_file.open(DBF_LOG_NAME);
    disk_file.close();

    input.open(DBF_FILE_NAME, ios::binary);
    output.open(DBF_FILE_NAME, ios::binary);
    log.open(DBF_LOG_NAME, ios::binary);
}

void disk::disk_input(int pageID)
{
    input.seekg((pageID * FrameSize), ios::beg);
    input.read(frame_data, FrameSize);
}

void disk::disk_output(int pageID)
{
    output.seekp((pageID * FrameSize), ios::beg);
    output.write(frame_data, FrameSize);
}