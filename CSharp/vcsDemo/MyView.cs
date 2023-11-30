using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace vcsDemo
{
    class MyView: FlowLayoutPanel
    {
        const int WS_CLIPCHILDREN = 0x02000000;
        const int WS_CLIPSIBLINGS = 0x04000000;
        protected override CreateParams CreateParams {
            get
            {
                new SecurityPermission(SecurityPermissionFlag.UnmanagedCode).Demand();

                // Extend the CreateParams property of the Button class.
                CreateParams cp = base.CreateParams;
                // Update the button Style.
                cp.Style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS; // BS_ICON value

                return cp;
            }
        }
    }
}
