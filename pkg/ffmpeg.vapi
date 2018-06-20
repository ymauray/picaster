namespace FFMpeg
{
    [CCode (cname = "AVInputFormat")]
    [Compact]
    public class InputFormat {
        
    }

    [CCode (cname = "AVDictionary")]
    [Compact]
    public class Dictionary {
        
    }
}

[CCode (cheader_filename = "libavformat/avformat.h")]
namespace AVFormat
{
    [CCode (cname = "av_register_all")]
    void register_all();

    [CCode (cname = "avformat_open_input")]
    public int open_input(ref AVFormat.Context ps, string filename, FFMpeg.InputFormat? fmt, [CCode (array_length = false)] FFMpeg.Dictionary[]? options);

    [CCode (cname = "AVFormatContext", cprefix = "avformat_", free_function = "avformat_free_context")]
    [Compact]
    public class Context
    {
        public int64 duration;
        public uint nb_streams;
        [CCode (array_length = false)]
        public AVFormat.Stream[] streams;

        [CCode (cname = "avformat_alloc_context")]
        public Context();

        public int find_stream_info([CCode (array_length = false)] FFMpeg.Dictionary[]? options);
        [CCode (cname = "av_dump_format")]
        public void dump_format(int index, string url, int is_output);
    }

    [CCode (cname = "AVStream")]
    [Compact]
    public class Stream
    {
        public CodecContext codec;
    }

    [CCode (cname = "AVCodecContext")]
    [Compact]
    public class CodecContext
    {
        public MediaType codec_type;
    }

    [CCode (cname = "enum AVMediaType", cprefix = "AVMEDIA_TYPE_")]
    public enum MediaType
    {
        UNKNOWN,
        VIDEO,
        AUDIO,
        DATA,
        SUBTITLE,
        ATTACHMENT,
        NB,
    }
}

[CCode (cheader_filename = "libavcodec/avcodec.h")]
namespace AVCodec
{

}

[CCode (cheader_filename = "libswresample/swresample.h")]
namespace SWResample
{

}
