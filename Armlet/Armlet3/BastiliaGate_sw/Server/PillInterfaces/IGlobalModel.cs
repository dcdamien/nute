﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PillInterfaces
{
    public interface IGlobalModel
    {
        IEnumerable<IArmletInfo> GetArmlets();
    }
}
