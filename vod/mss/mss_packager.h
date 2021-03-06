#ifndef __MSS_PACKAGER_H__
#define __MSS_PACKAGER_H__

// includes
#include "../mp4_builder.h"
#include "../mp4_parser.h"
#include "../segmenter.h"
#include "../common.h"

// constants
#define MSS_STREAM_TYPE_VIDEO "video"
#define MSS_STREAM_TYPE_AUDIO "audio"

// macros
// Note: in order to be able to process fragment requests efficiently, we need to know the file index and track index
//		of the fragment. since we only have the bitrate on the URL, we encode this parameters on the bitrate.
//		since both parameters are limited to 32, this results in a maximum of 1kpbs diviation from the real bitrate.
#define MSS_ENCODE_INDEXES(bitrate, file_index, track_index) (((bitrate) & ~0x3FF) | (((file_index) & 0x1F) << 5) | ((track_index) & 0x1F))
#define MSS_FILE_INDEX(bitrate)	(((bitrate) >> 5) & 0x1F)
#define MSS_TRACK_INDEX(bitrate)	((bitrate) & 0x1F)

// functions
bool_t mss_packager_compare_streams(void* context, const media_info_t* mi1, const media_info_t* mi2);

vod_status_t mss_packager_build_manifest(
	request_context_t* request_context,
	segmenter_conf_t* segmenter_conf,
	mpeg_metadata_t* mpeg_metadata,
	vod_str_t* result);

vod_status_t mss_packager_build_fragment_header(
	request_context_t* request_context,
	mpeg_stream_metadata_t* stream_metadata,
	uint32_t segment_index,
	bool_t size_only,
	vod_str_t* result,
	size_t* total_fragment_size);

#endif // __MSS_PACKAGER_H__
