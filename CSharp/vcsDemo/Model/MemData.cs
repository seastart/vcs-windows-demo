using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsDemo.Model
{
    class MemData: INotifyPropertyChanged
    {
        private int id = 0;
        public int ID { get{ return id; } set {
                if(id != value)
                {
                    id = value; 
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("ID"));
                    }
                }
            }
        }

        private string name;
        public string Name { get { return name; } set { 
                if(name != value)
                {
                    name = value;
                    if(PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Name"));
                    }
                }
            }
        }

        private int camState;
        public int CamState
        {
            get { return camState; }
            set
            {
                if (camState != value)
                {
                    camState = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("CamState"));
                    }
                }
            }
        }

        private int micState;
        public int MicState
        {
            get { return micState; }
            set
            {
                if (micState != value)
                {
                    micState = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("MicState"));
                    }
                }
            }
        }

        private int db;
        public int DB
        {
            get { return db; }
            set
            {
                if (db != value)
                {
                    db = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("DB"));
                    }
                }
            }
        }

        private int network;
        public int Network
        {
            get { return network; }
            set
            {
                if (network != value)
                {
                    network = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Network"));
                    }
                }
            }
        }

        private double serverLose;
        public double ServerLose
        {
            get { return serverLose; }
            set
            {
                if (serverLose != value)
                {
                    serverLose = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("ServerLose"));
                    }
                }
            }
        }

        private double clientLose;
        public double ClientLose
        {
            get { return clientLose; }
            set
            {
                if (clientLose != value)
                {
                    clientLose = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("ClientLose"));
                    }
                }
            }
        }

        private int videoPack;
        public int VideoPack
        {
            get { return videoPack; }
            set
            {
                if (videoPack != value)
                {
                    videoPack = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("VideoPack"));
                    }
                }
            }
        }

        private int audioPack;
        public int AudioPack
        {
            get { return audioPack; }
            set
            {
                if (audioPack != value)
                {
                    audioPack = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("AudioPack"));
                    }
                }
            }
        }

        private int allPack;
        public int AllPack
        {
            get { return allPack; }
            set
            {
                if (allPack != value)
                {
                    allPack = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("AllPack"));
                    }
                }
            }
        }

        private int allLosePack;
        public int AllLosePack
        {
            get { return allLosePack; }
            set
            {
                if (allLosePack != value)
                {
                    allLosePack = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("AllLosePack"));
                    }
                }
            }
        }

        private int gaer;
        public int Gaer
        {
            get { return gaer; }
            set
            {
                if (gaer != value)
                {
                    gaer = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Gaer"));
                    }
                }
            }
        }

        private int reLoaePack;
        public int ReLoaePack
        {
            get { return reLoaePack; }
            set
            {
                if (reLoaePack != value)
                {
                    reLoaePack = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("ReLoaePack"));
                    }
                }
            }
        }

        private int handUp;
        public int HandUp
        {
            get { return handUp; }
            set
            {
                if (handUp != value)
                {
                    handUp = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("HandUp"));
                    }
                }
            }
        }

        private int role;
        public int Role
        {
            get { return role; }
            set
            {
                if (role != value)
                {
                    role = value;
                    if (PropertyChanged != null)
                    {
                        PropertyChanged(this, new PropertyChangedEventArgs("Role"));
                    }
                }
            }
        }



        public event PropertyChangedEventHandler PropertyChanged;
    }
}
