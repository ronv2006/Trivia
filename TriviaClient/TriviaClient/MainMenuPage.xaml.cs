using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainMenuPage.xaml
    /// </summary>
    public partial class MainMenuPage : Page
    {
        String username;
        public MainMenuPage(String username)
        {
            this.username = username;
            InitializeComponent();

            WelcomeBlock.Text = "Welcome " + username;
        }

        void Logout_Click(Object sender, RoutedEventArgs e)
        {
            StatusResponse response = Communicator.Logout();
            if(response.Status == 1)
            {
                NavigationService.Navigate(new MenuPage());
            }


        }

        void HighScores_Click(Object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new HighScorePage());


        }

        void Statistics_Click(Object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new StatisticsPage());
        }

        void CreateRoom_Click(Object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new CreateRoomPage(username));


        }

        void JoinRoom_Click(Object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new JoinRoomPage(username));
        }

            void Exit_click(Object sender, RoutedEventArgs e)
        {
            Communicator.Logout();
            MainWindow mainWindow = Application.Current.MainWindow as MainWindow;
            mainWindow.Close();

        }

    }
}
