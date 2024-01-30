using System;
using System.Collections.Generic;
using System.Linq;
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
using TriviaClient.img;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for StatisticsPage.xaml
    /// </summary>
    public partial class StatisticsPage : Page
    {
        public StatisticsPage()
        {
            InitializeComponent();
            StatisticsResponse response = Communicator.Statistics();
            AmountOfGames.Text = AmountOfGames.Text + " " + response.NumOfPlayerGames;
            AmountOfCorrectAnswers.Text = AmountOfCorrectAnswers.Text + " " + response.NumOfCorrectAnswers;
            AmountOfAnswers.Text = AmountOfAnswers.Text + " " + response.NumOfTotalAnswers;
            PlayerAverageTime.Text = PlayerAverageTime.Text + " " + response.PlayerAverageTime;
        }

        void Exit_click(Object sender, RoutedEventArgs e)
        {
            Communicator.Logout();
            MainWindow mainWindow = Application.Current.MainWindow as MainWindow;
            mainWindow.Close();

        }
        void Go_back_click(Object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();

        }
    }
}
