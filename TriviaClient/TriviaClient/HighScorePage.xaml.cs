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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for HighScorePage.xaml
    /// </summary>
    public partial class HighScorePage : Page
    {
        public HighScorePage()
        {
            InitializeComponent();
            String highScores = Communicator.HighScore().HighScore;
            String[] highScoresArray = highScores.Split(",");
            
            
            if (highScoresArray.Length > 0)
            {
                High1.Text = High1.Text + " " + highScoresArray[0];
            }
            if (highScoresArray.Length > 1)
            {
                High2.Text = High2.Text + " " + highScoresArray[1];
            }
            if (highScoresArray.Length > 2)
            {
                High3.Text = High3.Text + " " + highScoresArray[2];
            }
            if (highScoresArray.Length > 3)
            {
                High4.Text = High4.Text + " " + highScoresArray[3];
            }
            if (highScoresArray.Length > 4)
            {
                High5.Text = High5.Text + " " + highScoresArray[4];
            }




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
