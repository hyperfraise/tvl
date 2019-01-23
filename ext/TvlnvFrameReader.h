#pragma once

#include <cuda.h>
#include <queue>

#include "NvDecoder/NvDecoder.h"
#include "Utils/FFmpegDemuxer.h"

#include "MemManager.h"

class TvlnvFrameReader
{
public:
    TvlnvFrameReader(MemManager* mem_manager, std::string video_file_path, int gpu_index, Rect* crop_rect=NULL, Dim* resize_dim=NULL);
    ~TvlnvFrameReader();

    std::string get_filename();
    int get_width();
    int get_height();
    int get_frame_size();
    double get_duration();
    double get_frame_rate();
    void seek(float time_secs);
    uint8_t* read_frame();

private:
    CUdevice _cu_device;
    MemManager* _mem_manager;
    std::string _filename;
    CUcontext _cu_context = NULL;
    FFmpegDemuxer* _demuxer;
    NvDecoder* _decoder;
    std::queue<uint8_t*> frame_buf;
};
