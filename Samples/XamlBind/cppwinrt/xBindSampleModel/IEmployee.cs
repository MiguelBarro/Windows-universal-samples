using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.UI.Xaml.Data;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Collections.ObjectModel;

using Windows.Foundation.Collections;
using System.Collections;
using System.Collections.Specialized;
using Microsoft.UI.Xaml;
using Windows.UI.Popups;

namespace xBindSampleModel
{
    public interface IEmployee
    {
        string FirstName { get; set; }
        string LastName { get; set; }
        Manager DirectManager { get; set; }
        bool IsManager { get; }
        string Title { get; }
        string Name { get; }
        bool Visibility { get; set; }
        string NullStringProperty { get; set; }
        Microsoft.UI.Xaml.Media.ImageSource NullImageSource { get; set; }
        void Poke(object sender, RoutedEventArgs e);
        string FullName();
    }
}

