using System;
using System.Collections.Generic;
using System.Text;
using vcsSdk.Sdk;

namespace vcsSdk.Classes
{
    public class Input
    {
        public Input()
        {
            cameraInput = -1;
            audioInput = -1;
            screenInput = -1;
        }
        public int screenInput { get; set; }
        public int cameraInput { get; set; }
        public int audioInput { get; set; }

        public int OpenCamera(ref int CameraIndex, ref int CameraExIndex,IntPtr hwnd,ref VideoSize video)
        {
            List<VideoDevice> devices = EnumDevice.GetVideo();
            if (devices == null)
            {
                return -1;
            }
            if (devices.Count == 0) {
                return -1;
            }
             if (devices.Count < CameraIndex)//可能摄像头设备发生了改变了。
            {
                CameraIndex = 0;
            }
            VideoDevice videoDevice = devices[CameraIndex];
            Resolution resolution = videoDevice.GetResolution(ref CameraExIndex);

            if (cameraInput >= 0)
            {
                return -2;
            }
            video.width = resolution.Width;
            video.height = resolution.Height;

            resetCanvas(ref video,false);

            // 打开摄像头输入源
            cameraInput = VcsNative.VCS_CreateInputVideo(videoDevice.Name, video.width, video.height, video.fps, hwnd);
            if(cameraInput >= 0)
            {
                VcsNative.VCS_SetSrcStreamVisible(cameraInput, true);
            }

            return (cameraInput >= 0) ? 0 : -3;
        }

        internal int OpenMic(ref int micIndex,int audioChannel,int audioSample)
        {

            List<string> devices = EnumDevice.GetAudio();
            if (devices == null)
            {
                return -1;
            }
            if(micIndex < devices.Count)
            {
                micIndex = 0;
            }
            string device = devices[micIndex];
            if (audioInput >= 0)
            {
                return -2;
            }

            // 打开麦克风输入源
            audioInput = VcsNative.VCS_CreateInputAudio(device, audioChannel, audioSample);
            return 0;
        }

        internal int CloseMic()
        {
            if (audioInput < 0)
            {
                return -1;
            }

            // 关闭输入源
            VcsNative.VCS_CloseInput(audioInput);

            return 0;
        }

        private void resetCanvas(ref VideoSize video, bool isShare)
        {
            int xBitMode = 0;
            int prevpaused = 0;
            if (isShare)
            {
                video.fps = 10;
                xBitMode = 2;
                prevpaused = 1;
            }
            else
            {
                video.fps = 25;
            }
            // 动态适配码率
            if (video.height >= 1080)
            {
                video.bitrate = 2048;
            }
            else if (video.height >= 720)
            {
                video.bitrate = 1500;
            }
            else
            {
                video.bitrate = 800;
            }

            VcsNative.VCS_SetOptParams(VcsNative.VCS_OPT_XBITMODE, xBitMode, 0, IntPtr.Zero, IntPtr.Zero);

            // 重置帧率
            VcsNative.VCS_SetOptParams(VcsNative.VCS_RESET_CPARAM, VcsNative.VCS_PARAM_FRAMES, video.fps, IntPtr.Zero, IntPtr.Zero);

            // 重置码率
            VcsNative.VCS_SetOptParams(VcsNative.VCS_RESET_CPARAM, VcsNative.VCS_PARAM_BITRATE, video.bitrate, IntPtr.Zero, IntPtr.Zero);

            // 重置画布
            VcsNative.VCS_SetOptParams(VcsNative.VCS_RESET_SIZE, video.width, video.height, IntPtr.Zero, IntPtr.Zero);

            VcsNative.VCS_SetOptParams(VcsNative.VCS_OPT_PREVPAUSED, prevpaused, 0, IntPtr.Zero, IntPtr.Zero);

        }

        internal int CloseCamera()
        {
            if (cameraInput < 0)
            {
                return -1;
            }
            // 关闭输入源
            VcsNative.VCS_CloseInput(cameraInput);
            return 0;
        }

        internal int CloseShare()
        {
            if (screenInput < 0)
            {
                return -1;
            }

            // 关闭输入源
            VcsNative.VCS_CloseInput(screenInput);
            return 0;
        }

        internal int ScreenShare(WndCaptureItem data,ref VideoSize vSize)
        {
            if (screenInput > 0)
            {
                return -1;
            }

            screenInput = VcsNative.VCS_CreateInputScreen3(
                IntPtr.Zero,                  // 指定预览句柄，当ptr=NULL预览不显示
                data.Hwnd,                // 要截图的窗口句柄，NULL表示截取整个桌面
                data.Rect,
                "scan_frame=0");   // 窗口位置字符串，只有截取全屏时有效
            if(screenInput < 0 )
            {
                return -2;
            }
            vSize.width = data.CX;
            vSize.height = data.CY;
            resetCanvas(ref vSize,true);
            return 0;
        }

        internal int ShareRectChange(int x, int y, int width, int height)
        {
            if (screenInput < 0)
            {
                return -2;
            }
            VcsNative.VCS_ChangeShareRect(new IntPtr(screenInput), x + ","+ y + ","+ width + ","+ height);
            return 0;
        }
    }


}
