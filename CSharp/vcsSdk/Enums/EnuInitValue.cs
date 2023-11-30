using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Enums
{
    public enum EnuInitValue
    {
        VoiceExci,              //语音激励上报,   类型int     默认1 ,1打开 0关闭
        Xdelay,                 //自适应延迟      类型int     默认1
        OutputAgc,              //agc             类型int     默认16000
        OutputAec,              //aec             类型int     默认10
        AudioSample,            //采样频率        类型int     默认48000
        AudioChannels,          //通道数          类型int     默认1
        ShowOutput,             //图像绘制        类型int     默认1 ,1打开 0关闭
        MultiTrack,             //双流            类型int     默认1 ,1打开 0关闭
        RoomPlc,                //网络抗抖动      类型int(0-3) 越大抖动网络越差， 默认 1(不建议修改)   
        SendVideo,              //上传视频        类型int     默认0 ,1打开 0关闭
        SendAudio,              //上传音频        类型int     默认0 ,1打开 0关闭
        RoomXBitrate,           //码率自适应      类型int     默认10
        StatInterval,           //网络获取间隔(s) 类型int     默认10
        OutPutSizeWidth,        //输出分辨率-宽   类型int     默认1280
        OutPutSizeHeight,       //输出分辨率-高   类型int     默认720
    }
}
