using Avalonia;
using Avalonia.ReactiveUI;
using System;
using Avalonia.NETCoreMVVMApp1.Classes;
using Newtonsoft.Json;


namespace Avalonia.NETCoreMVVMApp1
{
    class Program
    {
        
        // Initialization code. Don't use any Avalonia, third-party APIs or any
        // SynchronizationContext-reliant code before AppMain is called: things aren't initialized
        // yet and stuff might break.
        [STAThread]
        public static void Main(string[] args) { 
            BuildAvaloniaApp()
            .StartWithClassicDesktopLifetime(args);
            string json = @"{
          'Name': 'Bad Boys',
          'ReleaseDate': '1995-4-7T00:00:00',
          'Genres': [
            'Action',
            'Comedy'
          ]
        }";

            

            
        }

        // Avalonia configuration, don't remove; also used by visual designer.
        public static AppBuilder BuildAvaloniaApp()
            => AppBuilder.Configure<App>()
                .UsePlatformDetect()
                .LogToTrace()
                .UseReactiveUI();
    }
    
    }